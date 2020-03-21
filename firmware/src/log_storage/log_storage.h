#ifndef LOG_STORAGE_H
#define LOG_STORAGE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


typedef enum LogStore {
    LOG_STORE_TEXT,
    LOG_STORE_TRACE

} LogStoreID;


/**
 * Initialize the log storage system
 *
 * Initialize is required before calling any of the other functions.
 */
bool log_storage_init(void);

/**
 * [DANGER] Erase all data in all stores.
 *
 * Only use this if you want to erase/reset all data.
 * Should not be required in most use cases.
 *
 * NOTE: may take very long to complete!
 * Depending on the storage size, may take tens of seconds!
 */
bool log_storage_erase_all(void);

/**
 * Calculate how many bytes are in use for the given store.
 * 
 * This is the amount of data currently stored and available for reading.
 */
size_t log_storage_bytes_used(LogStoreID store);

/**
 * Try to append data to the given store.
 *
 * Each store may have a different policy on when to erase data or what to
 * do when the store is full.
 */
void log_storage_append(LogStoreID store,
        const char *buffer, const size_t size);

/**
 * Read a chunk of data from the store.
 *
 * May be used to iterate over all content in a store, or to access a store
 * in a blockwise manner (like a disk). NOTE: data contained in a store does
 * not always start at offset 0 (e.g. ERASE_OLDEST behaves as a circular buffer).
 *
 * Note: the buffer content is not a null-terminated string!
 *
 * @return the amount of data placed in the buffer
 */
size_t log_storage_read(LogStoreID store, const size_t offset,
        uint8_t *buffer, const size_t size);


#endif

