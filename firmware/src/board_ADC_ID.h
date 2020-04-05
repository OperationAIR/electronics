#ifndef BOARD_ADC_ID_H
#define BOARD_ADC_ID_H

enum ADC_ID {
    ADC_ID_PRESSURE_MFC,
    ADC_ID_PRESSURE_1       = 1,
    ADC_ID_MFC_O2           = 1,    // Overlapping : re-use pressure channel for mfc feedback
    ADC_ID_PRESSURE_2       = 2,
    ADC_ID_MFC_AIR          = 2,    // Overlapping : re-use pressure channel for mfc feedback
    ADC_ID_PREG_PRESSURE,

    ADC_ID_MAX // This should be last: it is used to count
};

#endif

