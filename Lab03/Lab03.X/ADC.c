/*
 * File:   ADC.c
 * Author: Marco
 *
 */


#include <xc.h>
#include <pic16f887.h>
#include "LIB_ADC.h"





/*unsigned ADC_VALUE(unsigned int *result_adc1) {
    __delay_ms(2); //Inicio de conversion ADC
    ADCON0bits.GO = 1;
    if (ADCON0bits.GO != 0) { //Mientras el bit go sea distinto de cero entonces:
        result_adc1 = ADRESH; //Desplegar ADRESH en result_adc
        __delay_ms(2); //Inicio de conversion ADC
        ADCON0bits.GO = 1;
        while (ADCON0bits.GO != 0) { //Mientras el bit go sea distinto de cero entonces:
 *result_adc1 = ADRESH; //Desplegar ADRESH en result_adc
        }
    }
}*/

/*void ADC_INTERRUPT() {
    PIE1bits.ADIE = 1;
    PIR1bits.ADIF = 1;
    OPTION_REG = 0b10000001;
    INTCON = 0b11000000;
}*/