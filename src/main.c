#include "pwm.h"
#include "stm32f103xb.h"
#include "adc.h"
int poten = 0; 
int conv = 0; 
int valor = 1;
int led = 3;


int main(){
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    adc_init();

    pwm_init(1,1000);

    
    while(1){
        conv = adc_read(poten);
        valor = (conv*100)/4095;
        pwm(1,valor);
        
    }
}