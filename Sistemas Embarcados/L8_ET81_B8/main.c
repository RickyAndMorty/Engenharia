#include "driverlib.h"

#define UCS_XT1_CRYSTAL_FREQUENCY ( 32768 )
#define UCS_XT2_CRYSTAL_FREQUENCY ( 4000000 )

#define UCS_XT1_TIMEOUT ( 50000 )
#define UCS_XT2_TIMEOUT ( 50000 )

#define MCLK_FREQ_KHZ     ( 8388 )
#define XT1CLK_KHZ        ( 32 )
#define MCLK_FLLREF_RATIO ( 256 ) //MCLK_FREQ_KHZ/XT1CLK_KHZ = 256
 Timer_A_initCompareModeParam initCompParam={0};

 int a=3000;
 void changePWM(void);

#pragma vector=PORT1_VECTOR

__interrupt void Port_1(void)
{
    if(a<3800)
    {
        __delay_cycles(800);
        while(GPIO_INPUT_PIN_LOW == GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1));
        a=a+200;
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

        changePWM();
    }
    else{
        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
    }
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN1);
}

#pragma vector=PORT2_VECTOR

__interrupt void Port_2(void)
{

    if(a>2000){
        __delay_cycles(800);
        while(GPIO_INPUT_PIN_LOW == GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN1));
        a=a-200;
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

        changePWM();
    }
    else{
        GPIO_setOutputHighOnPin (GPIO_PORT_P1, GPIO_PIN0);
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






int main(void) {

    WDT_A_hold(WDT_A_BASE);
    myInitClock();

 GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN1);
 GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
 GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0); // Colocando o LED na saída do P1.0
 GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN0);// Sinal do PWM
 GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);//habilitando interrupção no pino P1.1
 GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN1);//habilitando interrupção no pino P2.1
 GPIO_selectInterruptEdge(GPIO_PORT_P1, GPIO_PIN1, GPIO_HIGH_TO_LOW_TRANSITION);
 GPIO_selectInterruptEdge(GPIO_PORT_P2, GPIO_PIN1,GPIO_HIGH_TO_LOW_TRANSITION);
 GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN1);
 GPIO_clearInterrupt(GPIO_PORT_P2, GPIO_PIN1);

 __bis_SR_register(GIE); //Enable global interrupt
    Timer_A_initUpModeParam initUpParam = {0};

    initUpParam.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    initUpParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_2;
    initUpParam.timerPeriod = 39999; //Define período do sinal PWM
    initUpParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    initUpParam.captureCompareInterruptEnable_CCR0_CCIE= TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE;
    initUpParam.timerClear = TIMER_A_DO_CLEAR;
    initUpParam.startTimer= false;
    Timer_A_initUpMode(TIMER_A1_BASE, &initUpParam);
    Timer_A_startCounter(TIMER_A1_BASE,TIMER_A_UP_MODE);

    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN0);
    initCompParam.compareValue = 3000;
    initCompParam.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    initCompParam.compareInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE;
    initCompParam.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
    Timer_A_initCompareMode(TIMER_A1_BASE, &initCompParam);



    while(1){




    }
}
void changePWM(void){
    initCompParam.compareValue = a;
    Timer_A_initCompareMode(TIMER_A1_BASE, &initCompParam);
}



