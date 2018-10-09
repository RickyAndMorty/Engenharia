#include "driverlib.h"

#define UCS_XT1_CRYSTAL_FREQUENCY ( 32768 )
#define UCS_XT2_CRYSTAL_FREQUENCY ( 4000000 )

#define UCS_XT1_TIMEOUT ( 50000 )
#define UCS_XT2_TIMEOUT ( 50000 )

#define MCLK_FREQ_KHZ     ( 8388 )
#define XT1CLK_KHZ        ( 32 )
#define MCLK_FLLREF_RATIO ( 256 ) //MCLK_FREQ_KHZ/XT1CLK_KHZ = 256


void myInitClock(void);         //Inicializa as fontes de clock.
void myGPIO();
void myADC();

unsigned int result;

#pragma vector=ADC12_VECTOR
__interrupt void ADC12_A_ISR (void)
    {
    switch (__even_in_range(ADC12IV,34)){
        case 0: break; //Vector 0: No interrupt
        case 2: break; //Vector 2: ADC overflow
        case 4: break; //Vector 4: ADC timing overflow
        case 6: //Vector 6: ADC12IFG0
        result = ADC12_A_getResults(ADC12_A_BASE, ADC12_A_MEMORY_0);
        if(result<2500){        //no preto -> result=220
            GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN0);
        }
        else{                   //No branco -> result=3300
            GPIO_setOutputHighOnPin(GPIO_PORT_P1,GPIO_PIN0);
        }
        __no_operation();
        case 8: break; //Vector 8: ADC12IFG1
        case 10: break; //Vector 10: ADC12IFG2
        case 12: break; //Vector 12: ADC12IFG3
        case 14: break; //Vector 14: ADC12IFG4
        case 16: break; //Vector 16: ADC12IFG5
        case 32: break; //Vector 32: ADC12IFG13
        case 34: break; //Vector 34: ADC12IFG14
        default: break;

    }


    ADC12_A_clearInterrupt(ADC12_A_BASE, ADC12IFG0);
    ADC12_A_startConversion(ADC12_A_BASE, ADC12_A_MEMORY_0, ADC12_A_SINGLECHANNEL);
}

int main(void) {

    WDT_A_hold(WDT_A_BASE);
    myInitClock();
    myGPIO();

    myADC();

    while(1){
    }

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

void myGPIO(){

    GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN0);

    GPIO_setAsOutputPin(GPIO_PORT_P1,GPIO_PIN0);
}

void myADC(){

    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN0);

    ADC12_A_init(ADC12_A_BASE, ADC12_A_SAMPLEHOLDSOURCE_SC,
    ADC12_A_CLOCKSOURCE_ADC12OSC, ADC12_A_CLOCKDIVIDER_1);
    ADC12_A_enable(ADC12_A_BASE);

    ADC12_A_setupSamplingTimer(ADC12_A_BASE, ADC12_A_CYCLEHOLD_64_CYCLES,
       ADC12_A_CYCLEHOLD_4_CYCLES, ADC12_A_MULTIPLESAMPLESDISABLE);

    ADC12_A_configureMemoryParam param = {0};
    param.memoryBufferControlIndex = ADC12_A_MEMORY_0;
    param.inputSourceSelect = ADC12_A_INPUT_A0;
    param.positiveRefVoltageSourceSelect = ADC12_A_VREFPOS_AVCC;
    param.negativeRefVoltageSourceSelect = ADC12_A_VREFNEG_AVSS;
    param.endOfSequence = ADC12_A_NOTENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE ,&param);
    //Enable memory buffer 0 interrupt
    ADC12_A_clearInterrupt(ADC12_A_BASE, ADC12IFG0);
    ADC12_A_enableInterrupt(ADC12_A_BASE, ADC12IE0);

    ADC12_A_startConversion(ADC12_A_BASE, ADC12_A_MEMORY_0, ADC12_A_SINGLECHANNEL);
    __bis_SR_register(GIE);

}
