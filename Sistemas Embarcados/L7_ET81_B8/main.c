#include "driverlib.h"
#define UCS_XT1_CRYSTAL_FREQUENCY ( 32768 )
#define UCS_XT2_CRYSTAL_FREQUENCY ( 4000000 )

#define UCS_XT1_TIMEOUT ( 50000 )
#define UCS_XT2_TIMEOUT ( 50000 )

#define MCLK_FREQ_KHZ     ( 8388 )
#define XT1CLK_KHZ        ( 32 )
#define MCLK_FLLREF_RATIO ( 256 ) //MCLK_FREQ_KHZ/XT1CLK_KHZ = 256

void myInitClock( void )
{
    //Select VCore = 1 for clock speed up to 12MHz
    PMM_setVCore( PMM_CORE_LEVEL_1 );

    //Select XT2IN (P5.2) and XT2OUT (P5.3), XIN (P5.4) and XOUT (P5.5) as oscillators pins
    GPIO_setAsPeripheralModuleFunctionInputPin( GPIO_PORT_P5,
                                                GPIO_PIN2 + GPIO_PIN3 + GPIO_PIN4 + GPIO_PIN5
                                                );

    //Initialize XT1 and XT2 source frequencies
    UCS_setExternalClockSource( UCS_XT1_CRYSTAL_FREQUENCY,
                                UCS_XT2_CRYSTAL_FREQUENCY
                                );

    //Initialize XT1 oscillator and wait until it starts or times out
    //Returns STATUS_SUCCESS in case of success
    UCS_turnOnLFXT1WithTimeout( UCS_XT1_DRIVE_0,
                                UCS_XCAP_3,
                                UCS_XT1_TIMEOUT
                                );

    //Initialize XT2 oscillator and wait until it starts or times out
    //Returns STATUS_SUCCESS in case of success
    UCS_turnOnXT2WithTimeout( UCS_XT2_DRIVE_4MHZ_8MHZ,
                              UCS_XT2_TIMEOUT
                              );

    //Config. DCO and FLL
    //Select XT1 as FLL source
    UCS_initClockSignal( UCS_FLLREF,          // Selec. FLLREFCLK
                         UCS_XT1CLK_SELECT,   // LFXT1
                         UCS_CLOCK_DIVIDER_1  // FLLREFDIV=1
                         );

    // Once stable DCO can be used as MCLK & SMCLK sources
    UCS_initFLLSettle( MCLK_FREQ_KHZ,
                       MCLK_FLLREF_RATIO
                       );

    //Select XT1 as ACLK source
    UCS_initClockSignal( UCS_ACLK,
                         UCS_XT1CLK_SELECT,
                         UCS_CLOCK_DIVIDER_1
                         );

    //Select XT2 as SMCLK source
    UCS_initClockSignal( UCS_SMCLK,
                         UCS_XT2CLK_SELECT,
                         UCS_CLOCK_DIVIDER_1
                         );

    //Select FLL as MCLK source
    UCS_initClockSignal( UCS_MCLK,
                         UCS_DCOCLKDIV_SELECT,
                         UCS_CLOCK_DIVIDER_1
                         );
}

int rxData;

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR (void)
{
switch (__even_in_range(UCA0IV,4)){
//Vector 2 - RXIFG

case 2:
    rxData = USCI_A_UART_receiveData(USCI_A0_BASE);
    USCI_A_UART_clearInterrupt(USCI_A0_BASE,USCI_A_UART_RECEIVE_INTERRUPT);
    switch (rxData){
        case '0':
            GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
            GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN7);
            break;
        case '1':
            GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
            GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN7);
            break;
        case '2':
            GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
            GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN7);
            break;
        case '3':
            GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
            GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN7);
            break;
    }
    break;

default: break;
}
}


void main(void) {

    WDT_A_hold(WDT_A_BASE);
    myInitClock();


    //P1.0 e P4.7 Como saídas do LED
    GPIO_setAsOutputPin (GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin (GPIO_PORT_P4, GPIO_PIN7);

    //P3.4,5 = USCI_A0 TXD/RXD
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3, GPIO_PIN4 + GPIO_PIN3);

    //Baudrate = 9600, clock freq = 1048000 Hz
    //UCBRx = 109, UCBRFx = 0, UCBRSx = 1, UCOS16 = 0
    USCI_A_UART_initParam param = {0};
    param.selectClockSource = USCI_A_UART_CLOCKSOURCE_SMCLK;
    param.clockPrescalar = 416;
    param.firstModReg = 0;
    param.secondModReg = 6;
    param.parity = USCI_A_UART_NO_PARITY;
    param.msborLsbFirst = USCI_A_UART_LSB_FIRST;
    param.numberofStopBits = USCI_A_UART_ONE_STOP_BIT;
    param.uartMode = USCI_A_UART_MODE;
    param.overSampling = USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;
    USCI_A_UART_init(USCI_A0_BASE, &param);


    //Enable UART module for operation
    USCI_A_UART_enable(USCI_A0_BASE);
    //Enable Receive Interrupt
    USCI_A_UART_clearInterrupt(USCI_A0_BASE,USCI_A_UART_RECEIVE_INTERRUPT);
    USCI_A_UART_enableInterrupt(USCI_A0_BASE,USCI_A_UART_RECEIVE_INTERRUPT);
    __enable_interrupt();

    while (1);
}
