#include "settings.h"
#include <stdbool.h>
#include <string.h>



OperationSettings g_settings;


bool settings_update(OperationSettings *new_settings)
{


    // todo verify settings

    memcpy(&g_settings, new_settings, sizeof(OperationSettings));


    return true;

}