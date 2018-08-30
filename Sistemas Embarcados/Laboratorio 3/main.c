#include "driverlib.h"

#define UCS_XT1_CRYSTAL_FREQUENCY ( 32768 )
#define UCS_XT2_CRYSTAL_FREQUENCY ( 4000000 )

#define UCS_XT1_TIMEOUT ( 50000 )
#define UCS_XT2_TIMEOUT ( 50000 )

#define MCLK_FREQ_KHZ     ( 8388 )
#define XT1CLK_KHZ        ( 32 )
#define MCLK_FLLREF_RATIO ( 256 ) //MCLK_FREQ_KHZ/XT1CLK_KHZ = 256
int a; a=0;

#pragma vector=PORT2_VECTOR
__interrupt void Port_2 (void)
{
    if(a){
        __delay_cycles(800);
        while(GPIO_INPUT_PIN_LOW == GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN1));
        a=0;
        UCS_initClockSignal( UCS_MCLK,
                             UCS_XT2CLK_SELECT,
                             UCS_CLOCK_DIVIDER_1
                             );
    }
    else{
        __delay_cycles(1677);
        while(GPIO_INPUT_PIN_LOW == GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN1));
        a=1;
        UCS_initClockSignal( UCS_MCLK,
                             UCS_DCOCLKDIV_SELECT,
                             UCS_CLOCK_DIVIDER_1
                             );
    }
    GPIO_clearInterrupt(GPIO_PORT_P2, GPIO_PIN1);
}

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


void main (void)

{

        WDT_A_hold(WDT_A_BASE); //Stop watchdog timer
        myInitClock();
        GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0); //Set P1.0 to output
        //Enable P2.1 internal resistance as pull-Up resistance
        GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN1);
        //P2.1 interrupt enabled
        GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN1);
        //P2.1 Hi/Lo edge
        GPIO_selectInterruptEdge(GPIO_PORT_P2, GPIO_PIN1,
        GPIO_HIGH_TO_LOW_TRANSITION);
        //P2.1 IFG cleared
        GPIO_clearInterrupt(GPIO_PORT_P2, GPIO_PIN1);
        __bis_SR_register(GIE); //Enable global interrupt

while(1){
    __delay_cycles(2000000);
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

}




