#include "pwm.h"
#include "stm32f103xb.h"

void pwm_init(uint8_t canal, uint32_t frec) {

    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    TIM3->PSC = 7; 
    TIM3->ARR = (1000000 / frec) - 1;

    switch (canal) {
        case 1: 
            RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
            GPIOA->CRL &= ~(0xF << (canal * 4));
            GPIOA->CRL |=  (0xB << (canal * 4)); 
            TIM3->CCMR1 &= ~(0x7F << 0);
            TIM3->CCMR1 |=  (0b110 << 4);    
            TIM3->CCMR1 |=  TIM_CCMR1_OC1PE; // Habilitar Preload
            TIM3->CCER  |=  TIM_CCER_CC1E;  
            break;

        case 2:
            RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
            GPIOA->CRL &= ~(0xF << (canal * 4));
            GPIOA->CRL |=  (0xB << (canal * 4)); 
            TIM3->CCMR1 &= ~(0x7F << 8);
            TIM3->CCMR1 |=  (0b110 << 12);   
            TIM3->CCMR1 |=  TIM_CCMR1_OC2PE; // Habilitar Preload
            TIM3->CCER  |=  TIM_CCER_CC2E;  // Habilitar salida CH2 
            break;

        case 3: 
            RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
            GPIOB->CRL &= ~(0xF << (canal * 4));
            GPIOB->CRL |=  (0xB << (canal * 4)); 
            TIM3->CCMR2 &= ~(0x7F << 0);     
            TIM3->CCMR2 |=  (0b110 << 4);    
            TIM3->CCMR2 |=  TIM_CCMR2_OC3PE; // Habilitar Preload
            TIM3->CCER  |=  TIM_CCER_CC3E;  // Habilitar salida CH3 
        break;
        case 4: 
            RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
            GPIOB->CRL &= ~(0xF << (canal * 4));
            GPIOB->CRL |=  (0xB << (canal * 4)); 
            TIM3->CCMR2 &= ~(0x7F << 8);    
            TIM3->CCMR2 |=  (0b110 << 12);   
            TIM3->CCMR2 |=  TIM_CCMR2_OC4PE; // Habilitar Preload
            TIM3->CCER  |=  TIM_CCER_CC4E;  // Habilitar salida CH4 
            break;

        default:
            return;
    }


    TIM3->EGR |= TIM_EGR_UG;
    TIM3->CR1 |= TIM_CR1_ARPE;
    TIM3->CR1 |= TIM_CR1_CEN;

}

void pwm(uint8_t canal, uint8_t duty) {
    if (duty > 100) duty = 100;

    uint32_t ccr_duty = ((uint32_t)(TIM3->ARR + 1) * duty) / 100; // Cálculo de duty 

    if (canal == 1)      TIM3->CCR1 = ccr_duty; 
    else if (canal == 2) TIM3->CCR2 = ccr_duty;
    else if (canal == 3) TIM3->CCR3 = ccr_duty;
    else if (canal == 4) TIM3->CCR4 = ccr_duty;
}