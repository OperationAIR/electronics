#include "log_storage.h"
#include "board_GPIO_ID.h"
#include "SPI_flash.h"
#include "watchdog.h"

#include <string.h>
#include <c_utils/assert.h>
#include <c_utils/max.h>
#include <lpc_tools/boardconfig.h>
#include <lpc_tools/GPIO_HAL.h>
#include <mcu_timing/delay.h>


#define SPI_FLASH_PAGE_SIZE_BYTES           0x100
#define SPI_FLASH_ERASE_BLOCK_SIZE_BYTES    0x1000
#define SPI_FLASH_SIZE_BYTES                0x80000

// Sizes should be a multiple of the erase block size
// Of course don't configure more than SPI_FLASH_SIZE_BYTES
#define LOG_STORE_TEXT_SIZE 0x80000

typedef enum EraseMode {

    ERASE_NEVER,        // when full, all attempted writes fail
    ERASE_ON_INIT,      // erase the store when storage_init() is called
    ERASE_WHEN_FULL,    // when a store is full, completely erase it
    ERASE_OLDEST,       // when a store is full, erase the oldest block
                        //     and overwrite it with the new data
} EraseMode;

typedef struct StorageDescriptor {
    size_t offset;
    size_t size;
    EraseMode erase_mode;

} StorageDescriptor;

// Settings: describe all stores and their size.
// Note: regions should be listed in order of increasing offset.
// Also, offsets should be aligned to a multiple of the erase block size
static const StorageDescriptor g_stores[] = {
    [LOG_STORE_TEXT] = {
        .offset = 0,
        .size = 0x80000,
        .erase_mode = ERASE_OLDEST
    },
     [LOG_STORE_TRACE] = {
        .offset = 0x80000,
        .size = 0x00000,
        .erase_mode = ERASE_NEVER
    }
};

#define NUM_STORES (sizeof(g_stores)/sizeof(g_stores[0]))

// stores have an overhead of 1 erase block
#define MIN_STORE_SIZE (2*SPI_FLASH_ERASE_BLOCK_SIZE_BYTES)

typedef struct StorageState {
    size_t start_addr;
    size_t end_addr;
} StorageState; 

static struct {
    bool initialized;

    StorageState store[NUM_STORES];
    
} g_state;


static bool validate_stores(void)
{
    size_t min_offset = 0;
    for(size_t i=0;i<NUM_STORES;i++) {

        const size_t offset = g_stores[i].offset;
        const size_t size = g_stores[i].size;

        // section should be aligned to erase block size
        if(offset % SPI_FLASH_ERASE_BLOCK_SIZE_BYTES) {
            return false;
        }
        // section should not overlap previous section
        if(offset < min_offset) {
            return false;
        }

        // section should be large enough to be eraseable
        if(offset && offset < MIN_STORE_SIZE) {
            return false;
        }

        // section should fit in the flash memory
        if((size > SPI_FLASH_SIZE_BYTES) || (offset > (SPI_FLASH_SIZE_BYTES - size))) {
            return false;
        }

        min_offset = (offset + size);
    }

    return true;
}

/**
 * Wait up to timeout_ms for flash to become ready.
 *
 * @return  True if flash has become ready
 */
static bool flash_wait_ready(unsigned int timeout_ms)
{
    delay_timeout_t timeout;
    delay_timeout_set(&timeout, timeout_ms*1000);
    while(SPI_flash_is_busy()) {
        if(delay_timeout_done(&timeout)) {
            return false;
        }
    }
    return true;
}

/**
 * Try to erase a log store.
 *
 * NOTE: this may take a long time to complete!
 * Typical is 70 up to 300 ms per 4Kb!!
 */
static bool log_store_erase(LogStoreID ID)
{
    g_state.store[ID].start_addr = 0;
    g_state.store[ID].end_addr = 0;

    const size_t offset = g_stores[ID].offset;
    const size_t end = offset + g_stores[ID].size;
    for(size_t addr=offset;addr<end;addr+=SPI_FLASH_ERASE_BLOCK_SIZE_BYTES) {

        if(!flash_wait_ready(500)) {
            return false;
        }
        
        // Erase may take very long, so we need to feed the watchdog
        watchdog_feed();
        SPI_flash_erase_block(addr);
    }
    if(!flash_wait_ready(500)) {
        return false;
    }
    return true;
}

bool log_storage_erase_all(void)
{
    if(!g_state.initialized) {
        return false;
    }

    bool ok = true;
    for(size_t ID=0;ID<NUM_STORES;ID++) {
        if(!log_store_erase(ID)) {
            ok = false;
        }
    }
    return ok;
}


/**
 * Search for the first addr in range [addr_start, addr_end) containing value.
 *
 * Returns addr_end if no match was found
 */
static size_t search_for(size_t addr_start, size_t addr_end, uint8_t value)
{
    uint8_t chunk[128];

    for(size_t addr=addr_start;addr<addr_end;addr+=sizeof(chunk)) {

        size_t len = sizeof(chunk);
        if((addr + len) >= addr_end) {
            len = addr_end - addr;
        }

        if(!SPI_flash_read(addr, chunk, len)) {
            return addr_end;
        }
        for(size_t i=0;i<len;i++) {
            if(chunk[i] == value) {
                return addr + i;
            }
        }
    }
    return addr_end;
}

/**
 * (re-)Initialize a given store
 *
 * The store is scanned to find the begin+end addresses of existing data:
 *
 * A store is backed by two or more erase blocks.
 * On first use, the store is initially fully erased (0xFF). All data is written
 * in a linear fashion and is assumed not to contain the value 0xFF.
 *
 * After a power cycle, the end of the store can then be found by searching for
 * the first 0xFF byte. To speed things up a bit, at least one 'erase block' 
 * is always kept fully erased. This leads to the following strategy:
 *
 * 1. Find the first erase block where the value at offset 0 == 0xFF
 * 2. Search the previous block for the first occurring 0xFF: this is the end.
 * 3. If the search in step 2 did not result in any 0xFF values, the end offset
 *      is the result from step 1.
 *
 * The begin is found using a similar strategy: search for the first block
 * starting with a non-FF value, where the previous value is FF.
 */
static bool log_store_init(LogStoreID ID)
{
    if(g_stores[ID].erase_mode == ERASE_ON_INIT) {
        log_store_erase(ID);
    }

    const size_t offset = g_stores[ID].offset;
    const size_t max_addr = offset + g_stores[ID].size;

    bool start_found = false;
    bool end_found = false;
    size_t start_addr = offset;
    size_t end_addr = offset;
    uint8_t block_edge[2]; // [0]: last byte of prev block, [1]: first byte of block


    for(size_t addr=offset;addr<max_addr;addr+=SPI_FLASH_ERASE_BLOCK_SIZE_BYTES) {

        // first time is special: prev block is the last block (wraparound)
        if(addr == offset) {
            if(!SPI_flash_read(max_addr-1, block_edge, 1)) {
                return false;
            }
            if(!SPI_flash_read(offset, block_edge+1, 1)) {
                return false;
            }

        // read last byte of prev block + first byte of this block
        } else if(!SPI_flash_read(addr-1, block_edge, sizeof(block_edge))) {
            return false;
        }
        
        // Edge from 0xFF to non-0xFF: start of data
        if(!start_found && (block_edge[0] == 0xFF) && (block_edge[1] != 0xFF)) {
            start_found = true;
            start_addr = addr;
        }

        // First value 0xFF: end of data
        if(!end_found && (block_edge[1] == 0xFF)) {
            end_found = true;
            end_addr = addr;
        }

        if(start_found && end_found) {
            break;
        }
    }

    // At this point we know the start_addr exactly, but the end_addr may be
    // off by up to 1 block; we need to search the previous block...
    size_t search_addr = end_addr - SPI_FLASH_ERASE_BLOCK_SIZE_BYTES;

    if(end_addr == offset) {
        // store empty: start == end == 0
        if(end_found && (start_addr == offset)) {
            end_found = true;
            g_state.store[ID].start_addr = start_addr;
            g_state.store[ID].end_addr = end_addr;
            return true;
        }

        // end == 0 or not found: search in last block
        search_addr = max_addr - SPI_FLASH_ERASE_BLOCK_SIZE_BYTES;

    }
    
    end_addr = search_for(search_addr,
            search_addr + SPI_FLASH_ERASE_BLOCK_SIZE_BYTES, 0xFF);

    end_found = true;
    g_state.store[ID].start_addr = start_addr;
    g_state.store[ID].end_addr = end_addr;
    return true;
}

bool log_storage_init(void)
{
    memset(&g_state, 0, sizeof(g_state));

    assert(SPI_flash_init(LPC_SSP1,
                board_get_GPIO(GPIO_ID_FLASH_CS),
                SPI_FLASH_PAGE_SIZE_BYTES,
                SPI_FLASH_ERASE_BLOCK_SIZE_BYTES,
                SPI_FLASH_SIZE_BYTES));

    JEDECID flash_ID;
    if(!SPI_flash_read_JEDEC_ID(&flash_ID)) {
        return false;
    }

    if(!validate_stores()) {
        return false;
    }

    for(size_t ID=0;ID<NUM_STORES;ID++) {
        if(!log_store_init(ID)) {
            return false;
        }
    }

    g_state.initialized = true;
    return true;
}


void log_storage_append(LogStoreID store,
        const char *buffer, const size_t size)
{
    if(!g_state.initialized || (store > NUM_STORES)) {
        return;
    }

    const EraseMode erase_mode = g_stores[store].erase_mode;
    const size_t min_addr = g_stores[store].offset;
    const size_t max_addr = min_addr + g_stores[store].size;

    size_t w_addr = g_state.store[store].end_addr;
    size_t r_addr = g_state.store[store].start_addr;


    if((erase_mode == ERASE_NEVER) || (erase_mode == ERASE_ON_INIT)) {

        // store is full: nothing to be done
        if(w_addr >= max_addr) {
            return;
        }
    } else if(erase_mode == ERASE_WHEN_FULL) {

        // data is not going to fit: erase the store
        if(size > g_stores[store].size || ((w_addr + size) > max_addr)) {
            if(!log_store_erase(store)) {
                return;
            }
        }
    }

    // Write the buffer to storage
    size_t remaining = size;
    while(remaining)
    {
        // avoid writing across page boundary (assuming page size is a power of 2)
        const size_t page_offset = w_addr & (SPI_FLASH_PAGE_SIZE_BYTES-1);
        size_t to_write = min(remaining, (SPI_FLASH_PAGE_SIZE_BYTES - page_offset));
        
        // avoid writing >= max_addr
        to_write = min(to_write, (max_addr - w_addr));

        // write a chunk of data
        if(!SPI_flash_program(w_addr, buffer, to_write)) {
            break;
        }
        // Wait untill flash is done writing
        if(!flash_wait_ready(10)) {
            break;
        }
        w_addr+= to_write;
        remaining-= to_write;
        buffer+= to_write;

        // handle ERASE_OLDEST (behaves like a ringbuffer)
        if(erase_mode == ERASE_OLDEST) {

            // new w_addr is first byte of an erase block
            // (assuming erase block is a multiple of page size and that both
            // are powers of two).
            //
            // This new block should have already been erased,
            // but the 'padding' block after this block does need to be
            // erased (to be able to find the start/end on startup)
            if(!(w_addr & (SPI_FLASH_ERASE_BLOCK_SIZE_BYTES-1))) {
                // calculate address of the 'padding' block (with wraparound)
                size_t padding_addr = w_addr + SPI_FLASH_ERASE_BLOCK_SIZE_BYTES;
                if(padding_addr > max_addr) {
                    padding_addr = min_addr;
                }
                if(padding_addr == r_addr) {
                    if(!SPI_flash_erase_block(padding_addr)) {
                        break;
                    }
                    if(!flash_wait_ready(500)) {
                        break;
                    }

                    // increment r_addr (with wraparound)
                    r_addr+= SPI_FLASH_ERASE_BLOCK_SIZE_BYTES;
                    if(r_addr > max_addr) {
                        r_addr = min_addr;
                    }
                }
            }
        } else {
            if(w_addr >= max_addr) {
                break;
            }
        }

    }

    g_state.store[store].start_addr = r_addr;
    g_state.store[store].end_addr = w_addr; 
}

size_t log_storage_bytes_used(LogStoreID store)
{
    if(!g_state.initialized || (store > NUM_STORES)) {
        return 0;
    }

    const size_t start = g_state.store[store].start_addr;
    const size_t end = g_state.store[store].end_addr;
    
    const size_t store_size = g_stores[store].size;

    return ((start > end) ? (store_size - (start-end)) : (end-start));
}

// NOTE: this reads the raw storage data, including lots of 0xff bytes...
// TODO: only return data between start_addr and end_addr?
//
// TODO: verify if data is stored correctly without overlaps or missing bytes.
// Via usb it looks like there are some issues, but they may also be caused
// by the USB / fatfs emulation layer...
size_t log_storage_read(LogStoreID store, const size_t offset,
        uint8_t *buffer, const size_t size)
{
    if(!g_state.initialized || (store > NUM_STORES)) {
        return 0;
    }

    const size_t store_size = g_stores[store].size;

    // Don't allow reads past the end of the store
    if(offset > store_size) {
        return 0;
    }
    const size_t to_read = min(size, store_size - offset);
    const size_t addr = g_stores[store].offset + offset;
    if(SPI_flash_read(addr, buffer, to_read)) {
        return to_read;
    }

    return 0;
}

