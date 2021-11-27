#include "gd32e23x.h"

#define LEDPORT     GPIOA
#define LEDPIN      GPIO_PIN_7
#define LED_CLOCK   RCU_GPIOA


void systick_config(void);
void delay_1ms(uint32_t count);

int main(void)
{
    systick_config();

    rcu_periph_clock_enable(LED_CLOCK);

    /* set output as output */
    gpio_mode_set(LEDPORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LEDPIN);
    gpio_output_options_set(LEDPORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LEDPIN);

    while (1)
    {
        gpio_bit_set(LEDPORT, LEDPIN);
        delay_1ms(500);
        gpio_bit_reset(LEDPORT, LEDPIN);
        delay_1ms(500);
    }
}

volatile static uint32_t delay;

void systick_config(void)
{
    /* setup systick timer for 1000Hz interrupts */
    if (SysTick_Config(SystemCoreClock / 1000U))
    {
        /* capture error */
        while (1)
        {
        }
    }
    /* configure the systick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x00U);
}

void delay_1ms(uint32_t count)
{
    delay = count;

    while (0U != delay)
    {
    }
}

void delay_decrement(void)
{
    if (0U != delay)
    {
        delay--;
    }
}



void SysTick_Handler(void)
{
    delay_decrement();
}
