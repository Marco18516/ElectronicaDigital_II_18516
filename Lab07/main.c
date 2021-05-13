//------------Electrónica Digital II--------------------
//-----------------Laboratorio #7------------------------
//-------------Marco Juárez - 18516---------------------


//************************************************************************************************************
//LIBRERIAS
//************************************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/sysctl.c"
#include "driverlib/interrupt.h"
#include "driverlib/interrupt.c"
#include "driverlib/gpio.h"
#include "driverlib/gpio.c"
#include "driverlib/timer.h"
#include "driverlib/timer.c"
#include "driverlib/uart.h"
#include "driverlib/uart.c"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/rom.h"
#include "grlib/grlib.h"
#include <string.h>
//************************************************************************************************************
//Variables y funciones
//************************************************************************************************************
void UARTIntHandler(void);
void Timer0IntHandler(void);
void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count);

int LEDOn = false;
char color='o';

//************************************************************************************************************
//Codigo principal
//************************************************************************************************************

int main(void){
    //Configuraciones
    //Configuramos el reloj
    SysCtlClockSet ( SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ ) ;
    //Habilitamos puerto F
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOF ) ;

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){}

    //Habilitamos el UART0
    SysCtlPeripheralEnable (SYSCTL_PERIPH_UART0);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0)){}
    //Habilitamos puerto A
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    //Habilitamos los puertos RX y TX
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0))
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    IntMasterEnable();
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    //Configuramos el Baugrade
    UARTDisable(UART0_BASE);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntEnable (INT_UART0);

    UARTIntEnable (UART0_BASE, UART_INT_RX);
    UARTEnable (UART0_BASE);

    IntPrioritySet(INT_UART0, 0x0);
    IntRegister(INT_UART0, UARTIntHandler);
    UARTFIFOEnable(UART0_BASE);

    UARTFIFOLevelSet(UART0_BASE,UART_FIFO_TX1_8,UART_FIFO_RX1_8);
    SysCtlPeripheralEnable (SYSCTL_PERIPH_TIMER0);

    //Configurando Timer0
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)){}
    SysCtlPeripheralReset (SYSCTL_PERIPH_TIMER0);
    SysCtlDelay (5);
    TimerDisable(TIMER0_BASE, TIMER_A|TIMER_B);
    TimerConfigure (TIMER0_BASE,TIMER_CFG_PERIODIC);
    TimerLoadSet (TIMER0_BASE, TIMER_A, 20000000 -1);
    TimerEnable (TIMER0_BASE, TIMER_A|TIMER_B);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    //Establecemos la ISR
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);
    //Habilitamos interrupción por parte del NVIC
    IntEnable(INT_TIMER0A);
    //Habilitar temporizador
    TimerEnable(TIMER0_BASE, TIMER_A);

    //Configuración puertos salidas
    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3) ;    //Leds
    while(1){}

}

//Interrupción del Timer
void Timer0IntHandler(){
    TimerIntClear(TIMER0_BASE,  TIMER_TIMA_TIMEOUT);
        if (LEDOn){
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x0);
        }else{
            switch(color){
                            case 'r':
                                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x02);

                                break;
                            case 'v':
                                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x08);

                                break;
                            case 'a':
                                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x04);

                                break;
                            case 'o':
                                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x0);
                                break;
                                }

        }
        LEDOn = !LEDOn;


}

//Interrupción modulo UART
void UARTIntHandler(){
    uint32_t ui32Status;

        // Get the interrupt status
        ui32Status = UARTIntStatus(UART0_BASE, true);
        //UARTCharPutNonBlocking(UART0_BASE,ui32Status);
        //
        // Clear the asserted interrupts.
        //
        UARTIntClear(UART0_BASE, ui32Status);

        //
        // Loop while there are characters in the receive FIFO.
        //
        while(UARTCharsAvail(UART0_BASE))
        {

            color=UARTCharGet(UART0_BASE);
            UARTCharPutNonBlocking(UART0_BASE,color);

        }


}

//Envio de datos
void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count)
{

    while(ui32Count--)
    {

        UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
    }
}
