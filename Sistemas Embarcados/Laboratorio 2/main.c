#include "driverlib.h"

void main(void) {

    WDT_A_hold(WDT_A_BASE);

    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin (GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin (GPIO_PORT_P4, GPIO_PIN7);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN1);

    while(1){
        if(GPIO_INPUT_PIN_LOW == GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN1))
        {
            GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
            __delay_cycles(50000);
            while(GPIO_INPUT_PIN_LOW == GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN1));
        }
        else{
            GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
        }
        if(GPIO_INPUT_PIN_LOW == GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1))
        {
            GPIO_toggleOutputOnPin(GPIO_PORT_P4, GPIO_PIN7);
            __delay_cycles(50000);

            while(GPIO_INPUT_PIN_LOW == GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1));

        }

     }
}
