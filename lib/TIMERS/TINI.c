#include "TINI.h"
void delay_init(){
    RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;
    TIM2->CR1&~(TIM_CR1_CEN);
    TIM2->CNT=0;
    TIM2->PSC=7;
    TIM2->ARR=0XFFFF;   
    TIM2->DIER|=TIM_DIER_UIE;
    TIM2->EGR|=TIM_EGR_UG;
    TIM2->SR&=~TIM_SR_UIF;
}

void delay_us(uint32_t us){          
  TIM2->CR1|=TIM_CR1_CEN;
  int time=0;
  while(TIM2->CNT<us){
    delay_us(1);
    time++;
}
}
void delay_ms(uint32_t ms){          
    TIM2->CR1|=TIM_CR1_CEN;
    int time=0;
    while(time<ms){
        delay_us(1000);
        time++;
    }
    }
void timer_init(){
    RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN; 
    TIM2->CR1&~(TIM_CR1_CEN); 
    TIM2->PSC=7; 
    TIM2->ARR=0XFFFF;
    TIM2->CNT=0; 
    TIM2->DIER|=TIM_DIER_UIE;
    TIM2->EGR|=TIM_EGR_UG; 
    TIM2->SR|=TIM_SR_UIF; 
    NVIC_EnableIRQ(TIM2_IRQn); 
    TIM2->CR1|=TIM_CR1_CEN;
    }

volatile int flow;
void TIM2_IrqHandler(){
    if(TIM2->SR&TIM_SR_UIF){//lo lee
         TIM2->SR&=~TIM_SR_UIF;//limpia flag
         flow+=65356;
        }
}
uint32_t timer_millis(){
    TIM2->CR1|=TIM_CR1_CEN;  //empieza a contar
    int t_actual=TIM2->CNT;  //lee el valor actual del contador
    int tiempo=(t_actual+flow)/1000;//formula
    }
