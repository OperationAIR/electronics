#ifndef BOARD_ADC_ID_H
#define BOARD_ADC_ID_H

enum ADC_ID {
    ADC_ID_PRESSURE_MFC,
    ADC_ID_MFC_O2,
    ADC_ID_MFC_AIR,
    ADC_ID_PRESSURE_PATIENT,
    ADC_ID_BATTERY_LEVEL,

    ADC_ID_MAX // This should be last: it is used to count
};

#endif

