
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __UART_H_
#define	__UART_H_

#include <xc.h> // include processor files - each processor file is guarded.  

void Baudios(void){
    SPBRG = 12; //9600 baudios para 8MHZ
}

void config_txsta(void){
    TXSTAbits.CSRC = 0;//Clock external
    TXSTAbits.TX9 = 0;//8 bits de transmicion
    TXSTAbits.TXEN = 1;//Transmision habilitada
    TXSTAbits.SYNC = 0;//Modo asincrono
    TXSTAbits.BRGH = 0;//Low speed
    TXSTAbits.TRMT = 0;//TSR full
}

void config_rcsta(void){
    RCSTAbits.SPEN = 1;//Se habilita puerto serial
    RCSTAbits.RX9 = 0;//Se selecciona 8 bits de recepcion
    RCSTAbits.SREN = 0;//Disables single receive
    RCSTAbits.CREN = 1;//Recibir habilitado
    RCREG = 0; 
}

#endif	/* __UART_H_ */

