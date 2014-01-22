#if defined (__USE_CMSIS)
#include "stm32f0xx.h"
#endif


//*****************************************************************************
//
// Allocated stack space
//
//*****************************************************************************
#define STACKSIZE 64

static unsigned int StackMem[STACKSIZE];
#define _pStackTop ((void *)((unsigned int)StackMem + sizeof(StackMem)))

//*****************************************************************************

#define WEAK __attribute__ ((weak))
#define ALIAS(f) __attribute__ ((weak, alias (#f)))

//*****************************************************************************
//
// Forward declaration of the default handlers. These are aliased.
// When the application defines a handler (with the same name), this will
// automatically take precedence over these weak definitions
//
//*****************************************************************************

WEAK void ResetISR(void);
WEAK void NMI_Handler(void);
WEAK void HardFault_Handler(void);
WEAK void SVC_Handler(void);
WEAK void PendSV_Handler(void);
WEAK void SysTick_Handler(void);
WEAK void IntDefaultHandler(void);

//*****************************************************************************
//
// Forward declaration of the specific IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the application
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//
//*****************************************************************************

void WWDG_IRQHandler(void) ALIAS(IntDefaultHandler);
void PVD_IRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_IRQHandler(void) ALIAS(IntDefaultHandler);
void FLASH_IRQHandler(void) ALIAS(IntDefaultHandler);
void RCC_IRQHandler(void) ALIAS(IntDefaultHandler);
void EXTI0_1_IRQHandler(void) ALIAS(IntDefaultHandler);
void EXTI2_3_IRQHandler(void) ALIAS(IntDefaultHandler);
void EXTI4_15_IRQHandler(void) ALIAS(IntDefaultHandler);
void TS_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_Channel1_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_Channel2_3_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_Channel4_5_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1_COMP_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM1_BRK_UP_TRG_COM_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM1_CC_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM2_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM3_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM6_DAC_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM14_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM15_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM16_IRQHandler(void) ALIAS(IntDefaultHandler);
void TIM17_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C1_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C2_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI1_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI2_IRQHandler(void) ALIAS(IntDefaultHandler);
void USART1_IRQHandler(void) ALIAS(IntDefaultHandler);
void USART2_IRQHandler(void) ALIAS(IntDefaultHandler);
void CEC_IRQHandler(void) ALIAS(IntDefaultHandler);
#define BootRAM ((void *)0xF108F85F)

//*****************************************************************************
//
// The vector table.
// This relies on the linker script to place at correct location in memory.
//
//*****************************************************************************
extern void (* const g_pfnVectors[])(void);
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
	// Core Level - CM0plus
    _pStackTop, //&_vStackTop,		// The initial stack pointer
    ResetISR,				// The reset handler
    NMI_Handler,			// The NMI handler
    HardFault_Handler,			// The hard fault handler
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    SVC_Handler,			// SVCall handler
    0,					// Reserved
    0,					// Reserved
    PendSV_Handler,			// The PendSV handler
    SysTick_Handler,			// The SysTick handler

    // Chip Level - STM32F051
    WWDG_IRQHandler,
    PVD_IRQHandler,
    RTC_IRQHandler,
    FLASH_IRQHandler,
    RCC_IRQHandler,
    EXTI0_1_IRQHandler,
    EXTI2_3_IRQHandler,
    EXTI4_15_IRQHandler,
    TS_IRQHandler,
    DMA1_Channel1_IRQHandler,
    DMA1_Channel2_3_IRQHandler,
    DMA1_Channel4_5_IRQHandler,
    ADC1_COMP_IRQHandler,
    TIM1_BRK_UP_TRG_COM_IRQHandler,
    TIM1_CC_IRQHandler,
    TIM2_IRQHandler,
    TIM3_IRQHandler,
    TIM6_DAC_IRQHandler,
    0,
    TIM14_IRQHandler,
    TIM15_IRQHandler,
    TIM16_IRQHandler,
    TIM17_IRQHandler,
    I2C1_IRQHandler,
    I2C2_IRQHandler,
    SPI1_IRQHandler,
    SPI2_IRQHandler,
    USART1_IRQHandler,
    USART2_IRQHandler,
    0,
    CEC_IRQHandler,
    0,
    BootRAM
}; /* End of g_pfnVectors */


//*****************************************************************************
// Reset entry point for your code.
// Sets up a simple C runtime environment.
//*****************************************************************************

extern unsigned int _etext;
extern unsigned int _data;
extern unsigned int _edata;
extern unsigned int _bss;
extern unsigned int _ebss;

// Simple gcc-compatible C runtime init
static inline void
crt0(void)
{
    unsigned char *src, *dest, *dend;
    // copy the data section
    src  = (unsigned char *)(&_etext);
    dest = (unsigned char *)(&_data);
    dend = (unsigned char *)(&_edata);
    while (dest < dend)
	*(dest++) = *(src++);
    // blank the bss section
    dest = (unsigned char *)(&_bss);
    dend = (unsigned char *)(&_ebss);
    while (dest < dend)
	*(dest++) = 0;
}

void SystemInit(void);
void main(void);

__attribute__ ((section(".after_vectors")))
void
ResetISR(void)
{
    SystemInit();
    crt0();
    main();
    while (1) ;	// hang if main returns
}

//*****************************************************************************
// Default exception handlers. Override the ones here by defining your own
// handler routines in your application code.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void NMI_Handler(void)
{
    while(1)
    {
    }
}
__attribute__ ((section(".after_vectors")))
void HardFault_Handler(void)
{
    while(1)
    {
    }
}
__attribute__ ((section(".after_vectors")))
void SVCall_Handler(void)
{
    while(1)
    {
    }
}
__attribute__ ((section(".after_vectors")))
void PendSV_Handler(void)
{
    while(1)
    {
    }
}
__attribute__ ((section(".after_vectors")))
void SysTick_Handler(void)
{
    while(1)
    {
    }
}

//*****************************************************************************
//
// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.
//
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void IntDefaultHandler(void)
{
    while(1)
    {
    }
}

