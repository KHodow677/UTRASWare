/**
 * File name: SoundExample.h
 * Devices: LM4F120; TM4C123
 * Description: Example program to demonstrate outputting sound waves from a
 * speaker.
 * Authors: Matthew Yu.
 * Last Modified: 03/10/21
 */

/** General imports. */
#include <stdio.h>

/** Device specific imports. */
#include <TM4C123Drivers/inc/PLL.h>
#include <TM4C123Drivers/lib/DAC/Sound.h>
#include <TM4C123Drivers/lib/Misc/Misc.h>


void EnableInterrupts(void);    // Defined in startup.s
void DisableInterrupts(void);   // Defined in startup.s
void WaitForInterrupt(void);    // Defined in startup.s

void flipPF1(void) {
    GPIOSetBitFast(PIN_F1, !GPIOGetBitFast(PIN_F1));
}

uint16_t Test[16] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	7, 7, 7, 7, 7, 7, 7, 7,
};

GPIOConfig_t PF1Config = {PIN_F1, PULL_DOWN, true, false, 0, false};
TimerConfig_t timer0AConfig = {TIMER_0A, 0, true, 4, flipPF1};

int main(void) {
    struct SoundConfig config = {
		R_DAC,
        {.pins={PIN_B6, PIN_A2, PIN_A3, PIN_COUNT, PIN_COUNT, PIN_COUNT}}
    };

    PLL_Init(Bus80MHz);
	DisableInterrupts();

	initializeSoundPlayer(config);
	EnableInterrupts();

    /* Connect up with a speaker using a R_2R or Binary Weighted DAC
     * in ascending order of pins defined in config. Peaks at 2300 Hz
	 * with some loss as frequency increases (75 Hz at 2300 Hz). */
	uint32_t freq = 446;
	playSound(0, freq, Test);
	while (1) {
    	playSound(0, freq, Test);
		delayMillisec(20);
        freq = (freq + 10) % 2300;
    }
}

int mainSPI(void) {
    struct SoundConfig config = {
		SPI_DAC,
        {.ssi={SSI2_PB, FREESCALE_SPI, true, 16}},
    };

    PLL_Init(Bus80MHz);
	DisableInterrupts();

    /* Flash PF1 once per second. */
    GPIOInit(PF1Config);
    timer0AConfig.period = freqToPeriod(2, MAX_FREQ);
	TimerInit(timer0AConfig);

	initializeSoundPlayer(config);
	EnableInterrupts();

    /* Connect up with a speaker using TLV5616 SPI DAC. Use SSI2 pins
     * defined in SSI.h.
     * Listen for increasing pitch wave from 1 - 10kHz frequency. */
	uint32_t freq = 1;
	playSound(0, freq, Test);
	while (1) {
        delayMillisec(100);
        freq = (freq + 1) % 10000;
    }
}