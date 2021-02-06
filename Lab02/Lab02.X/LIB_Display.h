/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __DISPLAY_H_
#define	__DISPLAY_H_

#include <xc.h> // include processor files - each processor file is guarded.  

void Display(uint8_t num);

void Display(uint8_t num) {
    TRISD = 0;
    PORTD = 0;
    switch (num) {
        //Menos significativos
        case 0:
            PORTD = 0x3F; //0
            break;
        case 1:
            PORTD = 0x06; //1
            break;
        case 2:
            PORTD = 0x5B; //2
            break;
        case 3:
            PORTD = 0x4F; //3
            break;
        case 4:
            PORTD = 0x66; //4
            break;
        case 5:
            PORTD = 0x6D; //5
            break;
        case 6:
            PORTD = 0x7D; //6
            break;
        case 7:
            PORTD = 0x07; //7
            break;
        case 8:
            PORTD = 0x7F; //8
            break;
        case 9:
            PORTD = 0x6F; //9
            break;
        case 10:
            PORTD = 0x77; //A
            break;
        case 11:
            PORTD = 0x1F; //B
            break;
        case 12:
            PORTD = 0x4E; //C
            break;
        case 13:
            PORTD = 0x3D; //D
            break;
        case 14:
            PORTD = 0x4F; //E
            break;
        case 15:
            PORTD = 0x47; //F
            break;
            //Mas significativos
        case 128:
            PORTD = 0x06; //1
            break;
        case 64:
            PORTD = 0x5B; //2
            break;
        case 192:
            PORTD = 0x4F; //3
            break;
        case 32:
            PORTD = 0x66; //4
            break;
        case 160:
            PORTD = 0x6D; //5
            break;
        case 96:
            PORTD = 0x7D; //6
            break;
        case 224:
            PORTD = 0x07; //7
            break;
        case 16:
            PORTD = 0x7F; //8
            break;
        case 144:
            PORTD = 0x6F; //9
            break;
        case 80:
            PORTD = 0x77; //A
            break;
        case 208:
            PORTD = 0x1F; //B
            break;
        case 48:
            PORTD = 0x4E; //C
            break;
        case 176:
            PORTD = 0x3D; //D
            break;
        case 112:
            PORTD = 0x4F; //E
            break;
        case 240:
            PORTD = 0x47; //F
            break;
        default:
            PORTD = 0x3F; //0
            break;
    }
}
#endif

