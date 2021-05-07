//------------Electronica Digital II--------------------
//-----------------Laboratorio#6------------------------
//-------------Marco Juarez - 18516---------------------


//************************************************************************************************************
//LIBRERIAS
//************************************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.c"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.c"
#include "driverlib/sysctl.h"
//************************************************************************************************************
//Variables
//************************************************************************************************************
uint32_t segundos = 0 ;//Para el delay
//************************************************************************************************************
//Codigo principal
//************************************************************************************************************
int main(void){

    //Configuramos el reloj del sistema
    SysCtlClockSet ( SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ ) ;
    //Habilitamos los perifericos (GPIOF)
    SysCtlPeripheralEnable ( SYSCTL_PERIPH_GPIOF ) ;
    //Configuramos el boton 1 (SW1) como pullup
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE , GPIO_PIN_4 ) ;
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_4, GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU ) ;
    //Configuramos los leds como salidas
    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE,GPIO_PIN_1) ;//led rojo
    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_2) ;//led azul
    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_3) ;//led verde

    segundos = SysCtlClockGet() / 3 ;//Funcion para el tiempo de delay
    while(1){
        //Debido a que es pullup si entra 0 al if
        if((GPIOPinRead (GPIO_PORTF_BASE,GPIO_PIN_4 ) & 0x16)==0){
        //En el while al dejar de presionar el boton inica el semaforo
        while((GPIOPinRead (GPIO_PORTF_BASE,GPIO_PIN_4 ) & 0x16)==0){}//antirebote
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x08);//verde; 08 enciende solo el pin 3
        SysCtlDelay (segundos) ;//Mide en nanosegundos
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);//Se apagan los 3 pines
        SysCtlDelay (segundos) ;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x08);//Verde parapadeante
        SysCtlDelay (segundos) ;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
        SysCtlDelay (segundos) ;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x08);
        SysCtlDelay (segundos) ;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
        SysCtlDelay (segundos) ;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x08);
        SysCtlDelay (segundos) ;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
        SysCtlDelay (segundos) ;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x0A);//Amarillo; 0A enciende el pin 1 y 3
        SysCtlDelay (segundos) ;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
        SysCtlDelay (segundos) ;
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x02);//Rojo; 02 enciende el pin 1
    }
    }
}
