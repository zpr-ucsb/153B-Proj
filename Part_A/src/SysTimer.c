/*
 * ECE 153B - Spring 2023
 *
 * Name(s):
 * Section:
 * Lab: 6C
 */

#include "SysTimer.h"
#include "motor.h"

static uint32_t volatile step;

void SysTick_Init(void) {
	// SysTick Control & Status Register
	SysTick->CTRL = 0; // Disable SysTick IRQ and SysTick Counter

	SysTick->LOAD = 79999;
	SysTick->VAL = 0;
	
	// Enables SysTick exception request
	// 1 = counting down to zero asserts the SysTick exception request
	// 0 = counting down to zero does not assert the SysTick exception request
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; 
	// Select clock source
	// If CLKSOURCE = 0, the external clock is used. The frequency of SysTick clock is the frequency of the AHB clock divided by 8.
	// If CLKSOURCE = 1, the processor clock is used.
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;		
	
	// Enable SysTick IRQ and SysTick Timer
	// Configure and Enable SysTick interrupt in NVIC
	NVIC_EnableIRQ(SysTick_IRQn);
	NVIC_SetPriority(SysTick_IRQn, 1); // Set Priority to 1
}

void SysTick_Handler(void) {
		++step;
}

void delay(uint32_t ms) {
		// Reset the counter
		step = 0;
	
		//Reset VAL to 0 for SysTick
    SysTick->VAL = 0;
    
    // Set LOAD to a desirable value for 1ms interrupt frequency
    SysTick->LOAD = 79999;
    
    // Enable SysTick
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    
    // Busy wait for counter to reach desired value
    while (step < ms) {}
    
    // Disable SysTick for future use
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}
