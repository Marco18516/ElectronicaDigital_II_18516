/*
 * File:   Laboratorio_03.c
 * Author: Marco
 *
 * Created on 5 de febrero de 2021, 09:03 AM
 */
//******************************************************************************
// Configuración
//******************************************************************************
// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
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

#include <xc.h>
#include <pic16f887.h>
//******************************************************************************
// Definiciones y Librerias
//******************************************************************************
#define _XTAL_FREQ 8000000 //Libreria de Delay 
#define RS RE0
#define EN RE1
#define D0 RD0
#define D1 RD1
#define D2 RD2
#define D3 RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7
#include "LIB_LCD.h"
#include "LIB_ADC.h"
#include "LIB_USART.h"
//******************************************************************************
// Funciones
//******************************************************************************
void CONFIG_IO(void);
void OSCILADOR(void);
void ADC_INTERRUPT(void);
void ADC_1(void);//
void ADC_2(void);
void Mandar1(void);
void Mandar2(void);
//******************************************************************************
// Variables
//******************************************************************************
char data[16];//Variable para mostrar datos en LCD
float volt, volt2;//Variable para voltajes de POTs
//******************************************************************************
// Programa
//******************************************************************************
void main(void) {
    CONFIG_IO();
    OSCILADOR();
    ADC_INIT();
    ADC_INTERRUPT();
    Baudios();
    config_txsta();
    config_rcsta();
    Lcd_Init();
    //Se selecciona que se muestre en la primera fila de la LCD
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("S1:    S2:    S3:");
    
    while (1) {
        //Conversion de POT1
        ADC_1(); 
        Mandar1();
        __delay_ms(1);
        //Conversion de POT2
        ADC_2();
        Mandar2();
        __delay_ms(1);
        //Mostrara en dos decimales el voltaje de 0-5v
        sprintf(data, "%1.2f  " "%1.2f", volt, volt2);
        //Se selecciona que se muestre en la segunda fila de la LCD
        Lcd_Set_Cursor(2, 1); 
        //Muestra un string en la LCD
        Lcd_Write_String(data); 

    }

    return;
}

//Configuracion de Puertos
void CONFIG_IO(void) { 
    ANSEL = 0b00000011;//Se habilitan AN0 y AN1 para los canales del ADC
    ANSELH = 0;
    TRISA = 0b00000011;//RA0 como entrada
    TRISB = 0;
    TRISCbits.TRISC7 = 1;
    TRISCbits.TRISC6 = 0;
    TRISD = 0;
    TRISE = 0;
    //Se limpian los puertos
    PORTB = 0;
    PORTC = 0;
    PORTA = 0;
    PORTE = 0;
}

void OSCILADOR(void) {
    OSCCON = 0b01110001; //8MHz
}

//Se deshabilitan las interrupciones del ADC
void ADC_INTERRUPT() { 
    PIE1bits.ADIE = 0;
    PIR1bits.ADIF = 0;
    OPTION_REG = 0b00000000;
    INTCON = 0b00000000;
}

void ADC_1(void) {
    ADC_CHANNEL(0); //canal 0
    //Cinfiguracion bits ADCON0
    ADCON0bits.ADCS0 = 1;//Clock ADC conversion
    ADCON0bits.ADCS1 = 0;//Fosc/2
    ADCON0bits.ADON = 1;//Se habilita el ADC
    __delay_ms(0.25);//Para conversion
    ADCON0bits.GO = 1;  //Inicia la conversión
    while (ADCON0bits.GO == 1) {
        volt = ((ADRESH * 5.0) / 255); //CONVERSION DE  0-5V
    }

}
//Envia el valor del voltaje para pot1
void Mandar1(void){
    TXREG = volt;//Almacenamos el dato 
    while (TXSTAbits.TRMT == 1) { //Retornaba y enviaba el valor del volt
        return;
    }
}

void ADC_2(void) {
    ADC_CHANNEL(1); //Canal 1
    ADCON0bits.ADCS0 = 1;//
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.ADON = 1;
    __delay_ms(0.25);
    ADCON0bits.GO = 1;  //Inicia la conversión
    while (ADCON0bits.GO == 1) {
        volt2 = ((ADRESH * 5.0) / 255); //CONVERSION DE  0-5V
    }

}
//Envia el valor del voltaje para pot2
void Mandar2(void){
    TXREG = volt2; 
    while (TXSTAbits.TRMT == 1) { //retornaba y enviaba el voltaje del ADC2
        return;
    }
}



