#include <stm32f0xx.h>

static volatile uint32_t sysTick;
static int cur = 1;
static int led_gpio_pin = GPIO_Pin_8;

void SysTick_Handler(void)
{
  sysTick++;
  if (sysTick > 500 && sysTick <= 1000 && sysTick % 100 == 0) {
    cur = !cur;
    GPIO_WriteBit(GPIOC, led_gpio_pin, cur);
  }
  if (sysTick > 1000 && sysTick % 10 == 0) {
    cur = !cur;
    GPIO_WriteBit(GPIOC, led_gpio_pin, cur);
  }
}

int main(void)
{
  GPIO_InitTypeDef gpio_init;

  SystemCoreClockUpdate();
  SysTick_Config(SystemCoreClock / 100);

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  GPIO_StructInit(&gpio_init);
  gpio_init.GPIO_Pin = led_gpio_pin;
  gpio_init.GPIO_Mode = GPIO_Mode_OUT;
  gpio_init.GPIO_Speed = GPIO_Speed_Level_1;
  gpio_init.GPIO_OType = GPIO_OType_PP;
  gpio_init.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOC, &gpio_init);

  //GPIO_SetBits(GPIOC, led_gpio_pin);
  GPIO_WriteBit(GPIOC, led_gpio_pin, cur);

  while (1) {
    __WFI();
  }
  
  return 0;
}
