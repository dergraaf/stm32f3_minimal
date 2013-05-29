
#include <stdint.h>
#include <stdbool.h>

#include <stm32f30x.h>

extern void delay_us(uint32_t us);

/**
 * Stub required by newlibc.
 * 
 * E.g. for malloc()
 */
void
_sbrk(void)
{
}

/**
 * Stub required by newlibc.
 *
 * Used for static constructors in C++
 */
void
_init(void)
{
}

/**
 * Initialize the system clock.
 * 
 * Uses the external 8 MHz clock from the ST-Link to generate the
 * 72 MHz system clock.
 */
void
init_clock()
{
	// use external 8MHz clock from ST-LINK
	RCC->CR |= RCC_CR_HSEBYP | RCC_CR_HSEON;
	
	// wait until the external clock is stable
	uint32_t t = 1500;
	while (!(RCC->CR & RCC_CR_HSERDY) && --t) {
	}
	
	if (!(RCC->CR & RCC_CR_HSERDY)) {
		// no external clock found => abort
		return;
	}
	
	uint32_t tmp = 0;
	// Read reserved and read-only values and clear all other values
	tmp |= RCC->CFGR & ((1 << 31) | (1 << 30) | (1 << 29) | (1 << 28) | (1 << 27) |
	                    (1 << 15) | (1 << 14) |
	                    (1 << 3) | (1 << 2));

	// PLLSRC source for PLL
	tmp |= RCC_CFGR_PLLSRC_PREDIV1;
	
	// PLLMUL = factor is user defined
	tmp |= RCC_CFGR_PLLMULL9;
	
	RCC->CFGR = tmp;
	
	// enable PLL
	RCC->CR |= RCC_CR_PLLON;	

	// Wait until the PLL is stable
	while (!(RCC->CR & RCC_CR_PLLRDY)) {
		if (!(--t)) {
			return false;
		}
	}
	
	// Switch to the PLL
	// AHB = 72 / 1 = 72 MHz
	RCC->CFGR = ( RCC->CFGR & 0xffff0000) |
	            ((RCC_CFGR_PPRE1_DIV2 | // APB1 = 72 / 2 = 36 MHz
	              RCC_CFGR_PPRE2_DIV1 | // APB2 = 72 / 1 = 72 MHz
	              RCC_CFGR_HPRE_DIV1 |  // SYSCLK = 72 / 1 = 72 MHz
	              RCC_CFGR_SW_PLL) &    // select PLL as source
	              0x0000ffff);

	// Wait till the main PLL is used as system clock source
	while ((RCC->CFGR & (uint32_t) RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
	{
	}
}

int
main (void)
{
	init_clock();
	
	// Struct of PIO Port E
	GPIO_TypeDef *PE = GPIOE;
	
	// Red LED (North) is PE9
	// Red LED (South) is PE13
	// Set mode to 01 -> Output
	PE->MODER = (1 << (9*2)) | (1 << (13*2));

	// Switch LED on (is connected between IO and GND => active high)
	PE->ODR = (1 << 9) | (1 << 13);
	
	uint32_t count_led1 = 0;
	uint32_t count_led2 = 0;
	while(1)
	{
		count_led1++;
		if (count_led1 >= 500) {
			count_led1 = 0;

			if (PE->ODR & (1 << 9)) {
				PE->BRR = (1 << 9);
			}
			else {
				PE->BSRR = (1 << 9);
			}
		}
		
		count_led2++;
		if (count_led2 >= 300) {
			count_led2 = 0;

			if (PE->ODR & (1 << 13)) {
				PE->BRR = (1 << 13);
			}
			else {
				PE->BSRR = (1 << 13);
			}
		}
			
		delay_us(1000);
	}
}



