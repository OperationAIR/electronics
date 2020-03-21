#ifndef FAT_FS_EMULATION_H
#define FAT_FS_EMULATION_H

typedef enum {
    
    FILE_ATTR_READ_ONLY         = (1 << 0),
    FILE_ATTR_HIDDEN            = (1 << 1),
    FILE_ATTR_SYSTEM            = (1 << 2),
    FILE_ATTR_VOLUME_ID         = (1 << 3),
    FILE_ATTR_DIRECTORY         = (1 << 4),
    FILE_ATTR_ARCHIVE           = (1 << 5),
    FILE_ATTR_LONG_FILE_NAME    = (1 << 6),

} FileAttribute;

/**
 * This type of callback is called by the fatfs emulation when it wants to
 * read a given file:
 *
 * @param name              Name of the file that should be read
 * @param offset            Offset from the start of the file (in bytes)
 * @param buffer            Buffer where the requested data should be stored
 * @param sizeof_buffer     Amount of data to store in the buffer.
 *
 * @return                  Should return true if the buffer was updated.
 */
typedef bool (*FileReadCB)(const char *name, size_t offset,
        uint8_t *buffer, size_t sizeof_buffer);

/**
 * Initialze an emulated fatfs disk
 *
 * The emulated disk can be much larger than the available RAM or flash storage,
 * as the image is generated on the fly when it is accessed.
 *
 * The emulated disk is an empty disk, formatted as FAT16.
 *
 * @param disk_size             Total disk size in bytes. Recommended range is
 *                              16MB - 127MB. Outside this range,
 *                              init() may return false.
 *
 * @param volume_serial_number  Serial number to uniquely identify this volume,
 *                              similar to the volume_label. May be based on
 *                              a date+time, device serial no, or a dummy value.
 *
 * @param volume_label          Volume label: recognizable name for this disk.
 *                              This should be a string, max length=11.
 *                              Only A-Z, 0-9, '-', '_', ' ' is recommended.
 *
 * @return                      True on success. False if the disk size
 *                              results in a number of clusters outside the
 *                              range of FAT16.
 */
bool fat_fs_emulation_init(size_t disk_size, uint32_t volume_serial_number,
        const char *volume_label, FileReadCB read_cb);

/**
 * Add a file to the emulated fatfs disk
 *
 * If succesfull, the emulated fat_fs will pretend that the given file exists.
 * All reads to the file are redirected to the FileReadCB (see init()).
 *
 * @param file_name             Name of the file. This must be a valid FAT
 *                              filename: the filename will be truncated to fit
 *                              into 8 characters + 3 characters extension.
 *                              NOTE: file name + extension should be in
 *                              uppercase!
 *
 * @param file_size             Size of the file in bytes. Any size is ok,
 *                              as long as it does not exceed the free space
 *                              of the emulated disk. Note: a larger file_size
 *                              does not add any RAM overhead.
 *
 * @param attributes            One or more FileAttribute flags. For a typical
 *                              file, only the FILE_ATTR_ARCHIVE is required.
 *
 */
bool fat_fs_emulation_add_file(const char *file_name, size_t file_size,
        uint8_t attributes);
/**
 * Read a chunk of data from the (virtual) disk image.
 *
 * A disk image is generated on the fly, minimizing RAM overhead.
 *
 * @param offset            Offset address in bytes from start of the disk image.
 * @param result            Result buffer
 * @param sizeof_result     Amount of bytes requesed:
 *                          result buffer should be of this size
 */
void fat_fs_emulation_read(size_t offset, uint8_t *result, size_t sizeof_result);

#endif

