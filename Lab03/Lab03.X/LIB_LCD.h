/* 
 * File: LCD.h  
 * Se utilizó y se adaptaron las librerías de Ligo George 
 * de la página www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __LCD_H_
#define	__LCD_H_

#ifndef _XTAL_FREQ
define _XTAL_FREQ 8000000
#endif

#ifndef RS
#define RS RE0
#endif

#ifndef EN
#define EN RE1
#endif

#ifndef D0
#define D0 RD0
#endif

#ifndef D1
#define D1 RD1
#endif

#ifndef D2
#define D2 RD2
#endif

#ifndef D3
#define D3 RD3
#endif

#ifndef D4
#define D4 RD4
#endif

#ifndef D5
#define D5 RD5
#endif

#ifndef D6
#define D6 RD6
#endif

#ifndef D7
#define D7 RD7
#endif

#include <xc.h> // include processor files - each processor file is guarded.  
void Lcd_Port(char a) {
    if (a & 1)
        D0 = 1;
    else
        D0 = 0;

    if (a & 2)
        D1 = 1;
    else
        D1 = 0;

    if (a & 4)
        D2 = 1;
    else
        D2 = 0;

    if (a & 8)
        D3 = 1;
    else
        D3 = 0;

    if (a & 16)
        D4 = 1;
    else
        D4 = 0;

    if (a & 32)
        D5 = 1;
    else
        D5 = 0;

    if (a & 64)
        D6 = 1;
    else
        D6 = 0;

    if (a & 128)
        D7 = 1;
    else
        D7 = 0;

}

void Lcd_Cmd(char a) {
    RS = 0; // => RS = 0
    Lcd_Port(a);
    EN = 1; // => E = 1
    __delay_ms(4);
    EN = 0; // => E = 0
}

void Lcd_Clear(void) {
 //   Lcd_Cmd(0);
    Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b) {
    char temp, y, z;
    if (a == 1) {
        temp = 0x80 + b - 1;
        //  z = temp >> 4;
        //  y = temp & 0x0F;
        //  Lcd_Cmd(z);
        Lcd_Cmd(temp);
        //   Lcd_Cmd(y);
    } else if (a == 2) {
        temp = 0xC0 + b - 1;
        //  z = temp >> 4;
        //  y = temp & 0x0F;
        // Lcd_Cmd(z);
        Lcd_Cmd(temp);
        //  Lcd_Cmd(y);
    }
}

void Lcd_Init(void) {
    __delay_ms(20);
    Lcd_Cmd (0x30);
    __delay_ms(5);
    Lcd_Cmd (0x30);
    __delay_us(100);
    Lcd_Cmd (0x30);
    __delay_us(100);
    Lcd_Cmd (0x38);
    __delay_us(60);
    Lcd_Cmd (0x08);
    __delay_us(60);
    Lcd_Cmd (0x01);
    __delay_ms(5);
    Lcd_Cmd (0x06);
    __delay_us(60);
    Lcd_Cmd (0x0C);     
    __delay_us(60);
    

}

void Lcd_Write_Char(char a) {

    RS = 1; // => RS = 1
    Lcd_Port(a); //Data transfer
    EN = 1;
    __delay_us(40);
    EN = 0;
}

void Lcd_Write_String(char *a) {
    int i;
    for (i = 0; a[i] != '\0'; i++)
        Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right(void) {
    Lcd_Cmd(0x1C);
}

void Lcd_Shift_Left(void) {
    Lcd_Cmd(0x18);
}

#endif	/* __LCD_H_ */