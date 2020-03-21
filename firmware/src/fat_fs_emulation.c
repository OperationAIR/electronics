#include <stdint.h>
#include <stddef.h>
#include <string.h>

// When unit-testing on linux, we need bsd/string.h for strl* functions
#if defined(TEST) && defined(__linux__)
    #include <bsd/string.h>
#endif

#include <c_utils/max.h>
#include <c_utils/assert.h>
#include <c_utils/round.h>

#include "fat_fs_emulation.h"

// maximum amount of files that can be emulated (see add_file())
#ifndef FAT_FS_EMULATION_MAX_NUM_FILES
    #define FAT_FS_EMULATION_MAX_NUM_FILES (8)
#endif

// -- Bootsector metadata 
const char     *BS_OEMNAME                  = "emulated"; // OEM name: max 8 chars
const uint16_t  BPB_BYTES_PER_SECTOR        = 512;
const uint8_t   BPB_SECTORS_PER_CLUSTER     = 4;
const uint16_t  BPB_NUM_RESERVED_SECTORS    = 4;    // NOTE: chan recommends 1 for max compatibility
const uint8_t   BPB_NUM_FATS                = 2;    // NOTE: 1 would be fine as well
const uint16_t  BPB_NUM_ROOT_ENTRIES        = 512;
const uint8_t   BPB_MEDIA_TYPE              = 0xF8; // mkfs.vfat: 0xF8. for removable, maybe 0xF0 makes more sense?

const uint8_t   BS_EXTENDED_BOOT_SIGNATURE  = 0x29;
const char     *BS_FS_TYPE                  = "FAT16";

#define         BYTES_PER_CLUSTER (BPB_BYTES_PER_SECTOR * BPB_SECTORS_PER_CLUSTER)

typedef struct {
    const char *name;
    size_t size;
    uint16_t first_cluster;
    uint8_t attributes;

} File;

struct {
    FileReadCB read_cb;

    size_t offset_root;
    size_t num_sectors_per_fat;
    size_t num_sectors_root;
    size_t num_sectors_total;
    uint32_t volume_serial_number;
    const char *volume_label;

    size_t num_files;
    File files[FAT_FS_EMULATION_MAX_NUM_FILES];

} ctx;

// calculate the maximum cluster ID
static size_t max_cluster(void)
{
    const size_t start = ctx.offset_root + ctx.num_sectors_root;
    const size_t max_sectors = ctx.num_sectors_total - start;

    // cluster numbers start at 2
    return 2 + (max_sectors / BPB_SECTORS_PER_CLUSTER);
}

bool fat_fs_emulation_init(size_t disk_size, uint32_t volume_serial_number,
        const char *volume_label, FileReadCB read_cb)
{
    memset(&ctx, 0, sizeof(ctx));

    ctx.read_cb = read_cb;
    ctx.num_sectors_total = disk_size / BPB_BYTES_PER_SECTOR;

    // This implementation is FAT16 only.
    // For num_clusters outside this range, FAT12 or FAT32 would be required.
    const size_t num_clusters = ctx.num_sectors_total / BPB_SECTORS_PER_CLUSTER;
    if(num_clusters < 4086 || num_clusters > 65526) {
        return false;
    }

    // Calculate how many sectors to reserve for 2-byte FAT16 entries
    ctx.num_sectors_per_fat = (num_clusters * 2) / BPB_BYTES_PER_SECTOR;
    // Note: fat starts at offset BPB_NUM_RESERVED_SECTORS
    // Note: there are BPB_NUM_FATS: they should both be correct

    // Note: root dir starts at this offset:
    ctx.offset_root = BPB_NUM_RESERVED_SECTORS
        + (BPB_NUM_FATS * ctx.num_sectors_per_fat);

    // root directory contains 32-byte entries
    const size_t root_size = 32 * BPB_NUM_ROOT_ENTRIES;
    ctx.num_sectors_root = (root_size + BPB_BYTES_PER_SECTOR-1)/BPB_BYTES_PER_SECTOR;

    // Note: data starts at offset (offset_root + num_sectors_root)
    // Note: max data sector count is (num_sectors_total - data offset)

    ctx.volume_serial_number = volume_serial_number;
    ctx.volume_label = volume_label;

    return true;
}

bool fat_fs_emulation_add_file(const char *file_name, size_t file_size,
        uint8_t attributes)
{
    if(ctx.num_files >= FAT_FS_EMULATION_MAX_NUM_FILES) {
        return false;
    }

    size_t available_cluster = 0;

    // start the file at the next free cluster,
    // if enough free clusters are available
    if(file_size) {
        available_cluster = 2;
        if(ctx.num_files) {
            File *prev = &ctx.files[ctx.num_files-1];
            const size_t prev_num_clusters = divide_round_up(prev->size, BYTES_PER_CLUSTER);
            available_cluster = prev->first_cluster + prev_num_clusters;
        }

        const size_t required_clusters = divide_round_up(file_size, BYTES_PER_CLUSTER);
        if((available_cluster + required_clusters) >= max_cluster()) {
            return false;
        }
    }

    File *file = &ctx.files[ctx.num_files];
    file->name = file_name;
    file->size = file_size;
    file->attributes = attributes;
    file->first_cluster = available_cluster;

    ctx.num_files++;
    return true;
}

// copy a c-style string to fat-style string
static void string_to_fat(uint8_t *dst, const char *string, size_t sizeof_dst)
{
    for(size_t i=0;i<sizeof_dst;i++) {
        if(!string[i]) {
            memset(dst+i,' ',sizeof_dst-i);
            break;
        }
        dst[i] = string[i];
    }

    // 0xE5 has special meaning in FAT and should be escaped as 0x05.
    if(dst[0] == 0xE5) {
        dst[0] = 0x05;
    }
}

// create a lookup array for the first 62 bytes of the bootsector
static void create_bootsector_lookup(uint8_t *lookup, size_t sizeof_lookup)
{
    memset(lookup, 0, sizeof_lookup);
    assert(sizeof_lookup >= 62);

    // BS_JMP_BOOT
    lookup[0] = 0xEB;
    lookup[1] = 0x3C;
    lookup[2] = 0x90;

    // offset 3-10: OEM string (padded with ' ')
    string_to_fat(&lookup[3], BS_OEMNAME, 8);

    lookup[11] = BPB_BYTES_PER_SECTOR & 0xFF;
    lookup[12] = (BPB_BYTES_PER_SECTOR >> 8) & 0xFF;

    lookup[13] = BPB_SECTORS_PER_CLUSTER;

    lookup[14] = BPB_NUM_RESERVED_SECTORS & 0xFF;
    lookup[15] = (BPB_NUM_RESERVED_SECTORS >> 8) & 0xFF;

    lookup[16] = BPB_NUM_FATS;

    lookup[17] = BPB_NUM_ROOT_ENTRIES & 0xFF;
    lookup[18] = (BPB_NUM_ROOT_ENTRIES >> 8) & 0xFF;

    lookup[19] = ctx.num_sectors_total & 0xFF;
    lookup[20] = (ctx.num_sectors_total >> 8) & 0xFF;

    lookup[21] = BPB_MEDIA_TYPE;

    lookup[22] = ctx.num_sectors_per_fat & 0xFF;
    lookup[23] = (ctx.num_sectors_per_fat >> 8) & 0xFF;

    // These offsets are left to default (0x00):
    // 24-25: sectors per track: skip
    // 26-27: number of heads
    // 28-31: number of hidden sectors
    // 32-35: 32-bit alternative for the 16-bit total at offset 19

    // 36   : drive number for MS-DOS
    // 37   : reserved
    lookup[38] = BS_EXTENDED_BOOT_SIGNATURE;

    // volume serial number
    lookup[39] = ctx.volume_serial_number & 0xFF;
    lookup[40] = (ctx.volume_serial_number >>  8) & 0xFF;
    lookup[41] = (ctx.volume_serial_number >> 16) & 0xFF;
    lookup[42] = (ctx.volume_serial_number >> 24) & 0xFF;

    // offset 43-53: volume label (padded with ' ')
    string_to_fat(&lookup[43], ctx.volume_label, 11);

    // offset 54-61: volume type string (padded with ' ')
    string_to_fat(&lookup[54], BS_FS_TYPE, 8);
}

static void read_bootsector(size_t offset, uint8_t *result, size_t sizeof_result)
{
    // 0x00 by default
    memset(result, 0, sizeof_result);

    // Bounds of addresses that are accessed within this call
    const size_t min_addr = offset;
    const size_t max_addr = offset+sizeof_result;
    
    const size_t LOOKUP_SIZE = 62;

    if(min_addr < LOOKUP_SIZE) {

        // calculate the first few bytes of the bootsector in a lookup table
        uint8_t lookup[62];
        create_bootsector_lookup(lookup, sizeof(lookup));

        size_t n_from_lookup = sizeof(lookup) - min_addr;
        if(n_from_lookup > sizeof_result) {
            n_from_lookup = sizeof_result;
        }
        memcpy(result, lookup+min_addr, n_from_lookup);
    }

    // boot signature
    if((min_addr <= 510) && (max_addr > 510)) {
        result[510-offset] = 0x55;
    }
    if((min_addr <= 511) && (max_addr > 511)) {
        result[511-offset] = 0xAA;
    }
}

static size_t last_cluster_of_file(const File *file)
{
    size_t next = file->first_cluster + divide_round_up(file->size, BYTES_PER_CLUSTER);
    return next-1;
}

/**
 * Read the FAT.
 *
 * This same FAT appears BPB_NUM_FATS times in the FAT area of the disk.
 */
static void read_fat(size_t offset, uint8_t *result, size_t sizeof_result)
{
    // NOTE: result is already zero-initialized by read_all_fats()
    
    size_t current_index = 0;
    size_t last_cluster = 0;

    // skip to index of file matching the current cluster
    if(ctx.num_files) {

        current_index = ctx.num_files-1;
        const size_t first_cluster = offset / 2;
        while(ctx.files[current_index].first_cluster > first_cluster) {

            if(!current_index) {
                break;
            }
            --current_index;
        }
        File *file = &ctx.files[current_index];
        // last cluster belonging to the same file
        last_cluster = last_cluster_of_file(file);
    }


    const size_t max_offset = offset + sizeof_result;
    while(offset < max_offset) {

        // FAT entries are 16-bit: calculate the cluster number
        // and if this is byte 0 or 1
        const size_t cluster = offset / 2;
        const size_t second_byte = offset % 2;

        // reserved clusters 0,1: special values
        if(cluster < 2) {
            *result = (cluster == 0 && !second_byte) ? BPB_MEDIA_TYPE : 0xFF;

        
        // cluster belongs to a file: calculate the fat value
        } else if((cluster <= last_cluster) && (current_index < ctx.num_files)) {

            // Default: point to the next cluster (the fs is never fragmented)
            uint16_t fat_value = cluster+1;

            if(cluster == last_cluster) {
                fat_value = 0xFFFF; // End-Of-Cluster marker

                if(second_byte) {

                    // advance to next file
                    ++current_index;
                    if(current_index < ctx.num_files) {
                        File *file = &ctx.files[current_index];
                        last_cluster = last_cluster_of_file(file);
                    }

                }
            }
            *result = (fat_value >> (second_byte ? 8 : 0)) & 0xFF;

        // cluster is unused
        } else {
            *result = 0x00;
        }

        ++offset;
        ++result;
    }
}

/**
 * Read anywhere in the FAT area (which may contain multiple FAT's).
 */
static void read_all_fats(size_t offset, uint8_t *result, size_t sizeof_result)
{
    // 0x00 by default
    memset(result, 0, sizeof_result);

    const size_t fat_size = ctx.num_sectors_per_fat * BPB_BYTES_PER_SECTOR;

    const size_t max_offset = offset + sizeof_result;
    size_t fat = 0;
    while(offset < max_offset) {

        // limit maximum to end of current FAT
        const size_t fat_end = (fat+1)*fat_size;
        const size_t maximum = min(max_offset, fat_end);
        if(offset < maximum) {
            const size_t fat_offset = fat*fat_size;
            const size_t len = maximum - offset;

            // sanity check
            assert(offset >= fat_offset);

            read_fat(offset-fat_offset, result, len);
            offset+= len;
            result+= len;
        }
        if(offset >= fat_end) {
            ++fat;
        }
    }
}

// build a FAT16 directory entry in the supplied buffer
static void build_directory_entry(uint8_t *buffer, size_t sizeof_buffer,
        File *file)
{
    assert(sizeof_buffer >= 32);
    memset(buffer, 0, sizeof_buffer);

    // Split file_name in 'file' and 'ext' part.
    // 'file' is limited to 8 bytes, 'ext' to 3. If the supplied file_name
    // is longer, it is simpy truncated.
    size_t name_len = 0;
    const char *file_name = file->name;
    while(file_name[name_len] && file_name[name_len] != '.') {
        name_len++;
    }

    // file extension (if any): excluding the '.'
    const char *ext = file_name+name_len;
    if(*ext) {
        ++ext;
    }

    name_len = min(name_len, 8);
    char file_prefix[name_len+1];
    strlcpy(file_prefix, file_name, sizeof(file_prefix));

    string_to_fat(buffer, file_prefix, 8);
    string_to_fat(buffer+8, ext, 3);
    buffer[11] = file->attributes;

    // the first cluster containing the file data
    const uint16_t start_cluster = file->first_cluster;
    buffer[26] = start_cluster & 0xFF;
    buffer[27] = (start_cluster >> 8) & 0xFF;

    // file size in bytes
    const uint32_t file_size = file->size;
    buffer[28] = file_size & 0xFF;
    buffer[29] = (file_size >>  8) & 0xFF;
    buffer[30] = (file_size >> 16) & 0xFF;
    buffer[31] = (file_size >> 24) & 0xFF;
}

static void read_root(size_t offset, uint8_t *result, size_t sizeof_result)
{
    const size_t max_offset = offset + sizeof_result;
    while(offset < max_offset) {

        const size_t file_index = offset / 32;
        const size_t sub_offset = offset % 32;

        // 0x00 by default
        uint8_t entry[32] = {0};
        
        if(file_index < ctx.num_files) {

            File *file = &ctx.files[file_index];
            build_directory_entry(entry, sizeof(entry), file);


        }

        const size_t len = min((32-sub_offset), (max_offset - offset));
        memcpy(result, entry+sub_offset, len);
        offset+= len;
        result+= len;
    }
}


// try to read data from the given file.
static size_t try_read_from_file(File *file, size_t file_offset,
        uint8_t *result, size_t sizeof_result)
{
    // outside bound of current file: 0x00
    if(file_offset >= file->size) {
        memset(result, 0, sizeof_result);
        return sizeof_result;
    }

    // limit reads to the file size
    size_t num_bytes = min(sizeof_result, (file->size - file_offset));

    // call user callback to read data from file
    if(!ctx.read_cb(file->name, file_offset, result, num_bytes)) {
        memset(result, 0, num_bytes);
    }
    return num_bytes;
}

static size_t offset_to_cluster(size_t offset)
{
    return (offset / BYTES_PER_CLUSTER) + 2;
}

static void read_data(size_t offset, uint8_t *result, size_t sizeof_result)
{
    // non-file data defaults to 0x00
    if(!ctx.num_files) {
        memset(result, 0, sizeof_result);
        return;
    }

    size_t current_index = 0;
    size_t last_cluster = 0;


    // NOTE: this block of code is similar with read_fat().
    current_index = ctx.num_files-1;
    const size_t first_cluster = offset_to_cluster(offset);
    while(ctx.files[current_index].first_cluster > first_cluster) {

        if(!current_index) {
            break;
        }
        --current_index;
    }
    File *file = &ctx.files[current_index];
    last_cluster = last_cluster_of_file(file);


    const size_t max_offset = offset + sizeof_result;
    while(offset < max_offset) {

        const size_t cluster = offset_to_cluster(offset);
        const size_t sub_offset = offset % BYTES_PER_CLUSTER;

        // limit length to buffer size and cluster boundary
        size_t num_bytes = min(max_offset-offset, BYTES_PER_CLUSTER-sub_offset);

        // this data does not belong to any file: default to 0x00
        if((cluster > last_cluster)
                || (current_index >= ctx.num_files)
                || (cluster < file->first_cluster)) {
            memset(result, 0, num_bytes);
        }


        // read data from 'file'
        size_t file_offset = (cluster-(file->first_cluster)) * BYTES_PER_CLUSTER;
        file_offset+= sub_offset;
        num_bytes = try_read_from_file(file, file_offset, result, num_bytes);


        if((file_offset + num_bytes) >= file->size) {

            // advance to next file
            ++current_index;
            if(current_index < ctx.num_files) {
                file = &ctx.files[current_index];
                last_cluster = last_cluster_of_file(file);
            }

        }

        offset+= num_bytes;
        result+= num_bytes;
    }
}



void fat_fs_emulation_read(size_t offset, uint8_t *result, size_t sizeof_result)
{
    const size_t offset_fat = BPB_NUM_RESERVED_SECTORS * BPB_BYTES_PER_SECTOR;
    const size_t offset_root = ctx.offset_root * BPB_BYTES_PER_SECTOR;
    const size_t offset_data = offset_root + (ctx.num_sectors_root * BPB_BYTES_PER_SECTOR);

    const size_t max_offset = offset + sizeof_result;
    while(offset < max_offset) {

        size_t num_bytes = max_offset - offset;

        // read in bootsector / reserved area
        if(offset < offset_fat) {
            if(max_offset >= offset_fat) {
                num_bytes = (offset_fat - offset);
            }
            read_bootsector(offset, result, num_bytes);

        // read in FAT area
        } else if(offset < offset_root) {
            if(max_offset >= offset_root) {
                num_bytes = (offset_root - offset);
            }
            read_all_fats(offset-offset_fat, result, num_bytes);

        // read in root area
        } else if(offset < offset_data) {
            if(max_offset >= offset_data) {
                num_bytes = (offset_data - offset);
            }
            read_root(offset-offset_root, result, num_bytes);

        // read in data area
        } else {
            read_data(offset-offset_data, result, num_bytes);
        }
        offset+= num_bytes;
        result+= num_bytes;
    }
}

