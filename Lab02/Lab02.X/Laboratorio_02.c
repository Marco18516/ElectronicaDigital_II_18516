/* LABORATORIO #2
 * File:   Lab02.c
 * Author: Marco Juárez
 * Carné: 18516
 */


//******************************************************************************
// Configuración
//******************************************************************************
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)


//******************************************************************************
//Librerías
//******************************************************************************
#include <xc.h>
#include "LIB_ADC.h"//Libreria ADC
#include "LIB_Display.h"//Libreria Display
#define _XTAL_FREQ 4000000 //Libreria de Delay 

//******************************************************************************
// Variables
//******************************************************************************

int contador = 0;//Var para contador 8 bits
int cont = 0;//Var para contador TMR0
int BANDERAS = 0;//Var para multiplexado
unsigned int result_adc1;//Variable
unsigned int mas_sig;
unsigned int menos_sig;

void CONFIG_IO(void);
void CONFIG_INTERRUPT(void);
void separacion(void);
void banderas(void);
void Display_(void);
//******************************************************************************
// Interrupcion
//******************************************************************************

void __interrupt() isr(void) {
    //Interrupcion del PuertoB
    if (INTCONbits.RBIF) {
        INTCONbits.RBIF = 0;//Se apaga la bandera
        if (PORTBbits.RB0 == 1) { 
            __delay_ms(200);//Antirrebote
        }
        if (PORTBbits.RB0 == 0){
            contador++;//Se incrementa la variable
            PORTA = contador;
            __delay_ms(200);
        }
                if (PORTBbits.RB1 == 1) { //Antirrebote
            __delay_ms(200);
        }
                if (PORTBbits.RB1 == 0) { //Antirrebote si se presiona RB1
                contador--; //decrementa
                PORTA = contador;
                __delay_ms(200);
        }
        
    }
    //Interrupcion del ADC
    if (PIR1bits.ADIF) {
        PIR1bits.ADIF = 0;

        ADC_READ(8); //canal 8
        __delay_ms(2); //Delay para inicio de conversion ADC
        ADCON0bits.GO = 1; //Para habilitar el ciclo de conversion A/D
        while (ADCON0bits.GO != 0) { //Mientras el bit go sea distinto de cero entonces:
            result_adc1 = ADRESH; //Desplegar ADRESH en result_adc
            Display_();
        }
    }
    //Interrupcion TMR0
    if (TMR0IF) { 
        TMR0IF = 0;
        TMR0 = 4;// de 0.5 mS
        cont++;
    }
}


//******************************************************************************
// Funciones
//******************************************************************************
void main(void) {
    CONFIG_IO(); //Configuracion de puertos de entrada y salida   
    CONFIG_INTERRUPT(); //Configuracion de la interrupcion del puerto B
    ADC_INIT();//LLamo las funciones de mi libreria
    ADC_INTERRUPT();
    while (1) {
        if (cont >= 1) { //Si la variable es mayor igual a 1
            cont = 0;//La limpiara
            banderas();//y realizara la funcion
        }
        separacion(); //Separacion de Nibbles en mas sig y menos sig
        //Alarma
        if (result_adc1 > contador) {//Si el valor de los Displays es mayor
            PORTEbits.RE0 = 1;//Encendera la LED

        }else if (result_adc1 < contador) {
            PORTEbits.RE0 = 0;
        }
    }
    return;
}
//Configuracion de puertos de entrada y salida
void CONFIG_IO(void) { 
    TRISA = 0; //Salida.
    TRISB = 0b00000111; //Se declara como entrada RB0, RB1 Y RB2
    TRISD = 0; //Salida
    TRISE = 0; //Salida
    ANSEL = 0; 
    ANSELH = 0b00000000; //Se utiliza unicamente el canal AN8
    // Se limpian los puertos
    PORTA = 0; 
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
}

void CONFIG_INTERRUPT(void) {
    TMR0 = 4; // de 0.5 mS 
    OPTION_REG = 0b10000001;//TMR0 Rate de 1:4
    INTCON = 0b10101001;//GIE habilitadas
    IOCB = 0b00000011;
}

void Display_(void) {
    PORTE = 0;//Se limpia el puerto
    if (BANDERAS == 0) {
        Display(menos_sig);//Se asigna el valor de la variable
        PORTEbits.RE1 = 1;
    } else if (BANDERAS == 1) {
        Display(mas_sig);
        PORTEbits.RE2 = 1;
    }
}
//Apaga y enciende las banderas para realizar el multiplexado
void banderas(void) {
    if (BANDERAS == 1) {
        BANDERAS = 0;
    } else if (BANDERAS == 0) {
        BANDERAS = 1;

    }
}

void separacion(void) { 
    menos_sig = (0b11110000 & result_adc1);//& para realizar mascar
    mas_sig = (0b00001111 & result_adc1);
}