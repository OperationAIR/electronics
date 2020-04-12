#include "storage.h"
#include <chip.h>
#include <c_utils/assert.h>
#include <c_utils/array.h>
#include <c_utils/static_assert.h>
#include <memory.h>

#include "eeprom.h"
#include "system_status.h"



enum {
    SIZE_OPERATION_SETTINGS     = 128,
    SIZE_APP_USE_COUNT          = sizeof(uint32_t),

};

enum {
    OFFSET_OPERATION_SETTINGS   = EEPROM_ADDR_MIN,
    OFFSET_APP_USE_COUNT        = OFFSET_OPERATION_SETTINGS + SIZE_OPERATION_SETTINGS,

};

typedef enum {
    FILE_APP_USE_COUNT,
    FILE_OPERATION_SETTINGS,


    // special value: used to count amount of files
    FILE__COUNT
} EEPROMFileID;

typedef struct {
    size_t address;
    size_t length;
} EEPROMFile;

static EEPROMFile files[] = {
    [FILE_APP_USE_COUNT] = {
        .address    = OFFSET_APP_USE_COUNT,
        .length     = SIZE_APP_USE_COUNT
    },
    [FILE_OPERATION_SETTINGS] = {
        .address    = OFFSET_OPERATION_SETTINGS,
        .length     = SIZE_OPERATION_SETTINGS
    },
};

STATIC_ASSERT(FILE__COUNT == (sizeof(files)/sizeof(files[0])));


static bool _read_file(EEPROMFileID file, void *buffer, size_t sizeof_buffer);
static bool _write_file(EEPROMFileID file_id, const void *buffer, size_t sizeof_buffer);


void storage_init(void)
{
    // validate files are defined correctly and non-overlapping.
    const size_t n_files = array_length(files);
    size_t offset = EEPROM_ADDR_MIN;
    for(size_t i=0;i<n_files;i++) {
        EEPROMFile file = files[i];
        assert(file.address >= offset);
        assert(file.address <= EEPROM_ADDR_MAX);
        offset = file.address + file.length;
        assert(offset <= EEPROM_ADDR_MAX);
    }
}

int32_t storage_read_app_use_count(void)
{
    int32_t count = 0;
    _read_file(FILE_APP_USE_COUNT, &count, sizeof(count));
    return count;
}

void storage_increment_app_use_count(void)
{
    int32_t use_count = storage_read_app_use_count() + 1;
    _write_file(FILE_APP_USE_COUNT, &use_count, sizeof(use_count));
}

bool storage_read_settings(OperationSettings *result)
{
    return _read_file(FILE_OPERATION_SETTINGS, result, sizeof(OperationSettings));
}
bool storage_write_settings(const OperationSettings *settings)
{
    return _write_file(FILE_OPERATION_SETTINGS, settings, sizeof(OperationSettings));
}



static bool _read_file(EEPROMFileID file_id, void *buffer, size_t sizeof_buffer)
{
    if(file_id < FILE__COUNT) {

        EEPROMFile file = files[file_id];
        if(sizeof_buffer <= file.length) {
            return eeprom_read(file.address, buffer, sizeof_buffer);
        }
    }
    memset(buffer, 0, sizeof_buffer);

    system_status_set(SYSTEM_STATUS_ERROR_EEPROM);
    return false;
}

static bool _write_file(EEPROMFileID file_id, const void *buffer, size_t sizeof_buffer)
{
    if(file_id < FILE__COUNT) {

        EEPROMFile file = files[file_id];
        if(sizeof_buffer <= file.length) {
            return eeprom_write(file.address, buffer, sizeof_buffer);
        }
    }

    system_status_set(SYSTEM_STATUS_ERROR_EEPROM);
    return false;
}


