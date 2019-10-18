/* 
 * "Small Hello World" example. 
 * 
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example 
 * designs. It requires a STDOUT  device in your system's hardware. 
 *
 * The purpose of this example is to demonstrate the smallest possible Hello 
 * World application, using the Nios II HAL library.  The memory footprint
 * of this hosted application is ~332 bytes by default using the standard 
 * reference design.  For a more fully featured Hello World application
 * example, see the example titled "Hello World".
 *
 * The memory footprint of this example has been reduced by making the
 * following changes to the normal "Hello World" example.
 * Check in the Nios II Software Developers Manual for a more complete 
 * description.
 * 
 * In the SW Application project (small_hello_world):
 *
 *  - In the C/C++ Build page
 * 
 *    - Set the Optimization Level to -Os
 * 
 * In System Library project (small_hello_world_syslib):
 *  - In the C/C++ Build page
 * 
 *    - Set the Optimization Level to -Os
 * 
 *    - Define the preprocessor option ALT_NO_INSTRUCTION_EMULATION 
 *      This removes software exception handling, which means that you cannot 
 *      run code compiled for Nios II cpu with a hardware multiplier on a core 
 *      without a the multiply unit. Check the Nios II Software Developers 
 *      Manual for more details.
 *
 *  - In the System Library page:
 *    - Set Periodic system timer and Timestamp timer to none
 *      This prevents the automatic inclusion of the timer driver.
 *
 *    - Set Max file descriptors to 4
 *      This reduces the size of the file handle pool.
 *
 *    - Check Main function does not exit
 *    - Uncheck Clean exit (flush buffers)
 *      This removes the unneeded call to exit when main returns, since it
 *      won't.
 *
 *    - Check Don't use C++
 *      This builds without the C++ support code.
 *
 *    - Check Small C library
 *      This uses a reduced functionality C library, which lacks  
 *      support for buffering, file IO, floating point and getch(), etc. 
 *      Check the Nios II Software Developers Manual for a complete list.
 *
 *    - Check Reduced device drivers
 *      This uses reduced functionality drivers if they're available. For the
 *      standard design this means you get polled UART and JTAG UART drivers,
 *      no support for the LCD driver and you lose the ability to program 
 *      CFI compliant flash devices.
 *
 *    - Check Access device drivers directly
 *      This bypasses the device file system to access device drivers directly.
 *      This eliminates the space required for the device file system services.
 *      It also provides a HAL version of libc services that access the drivers
 *      directly, further reducing space. Only a limited number of libc
 *      functions are available in this configuration.
 *
 *    - Use ALT versions of stdio routines:
 *
 *           Function                  Description
 *        ===============  =====================================
 *        alt_printf       Only supports %s, %x, and %c ( < 1 Kbyte)
 *        alt_putstr       Smaller overhead than puts with direct drivers
 *                         Note this function doesn't add a newline.
 *        alt_putchar      Smaller overhead than putchar with direct drivers
 *        alt_getchar      Smaller overhead than getchar with direct drivers
 *
 */

#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"
#include <priv/alt_legacy_irq.h>
#include <system.h>
#include "altera_avalon_jtag_uart_regs.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"

#define MINUTO 3
#define DECENAS_MINUTO 2
#define HORA 1
#define DECENAS_HORA 0

#define ALARM_MAX_TIME 20
#define ALARM_FIRST_BLINK 32000
#define ALARM_SECOND_BLINK 64000

#define AM_S7 0x8
#define PM_S7 0xC
#define ZERO_S7 0x40
#define ONE_S7 0x79
#define TWO_S7 0x24
#define THREE_S7 0xB0
#define FOUR_S7 0x99
#define FIVE_S7 0x12
#define SIX_S7 0x82
#define SEVEN_S7 0xF8
#define EIGHT_S7 0x80
#define NINE_S7 0x10

#define FIRST_LED 0x80
#define SECOND_LED 0x40
#define THIRD_LED 0x20
#define FOURTH_LED 0x10
#define FIFTH_LED 0x8

volatile unsigned int* TIMER_PTR;
volatile unsigned char* LED_PTR;
volatile unsigned char* SW_PTR;
volatile unsigned char* UART_PTR;
volatile unsigned int* BTN_UP_PTR;
volatile unsigned int* BTN_SET_PTR;
volatile unsigned int* BTN_CHANGE_SEG_PTR;
volatile unsigned char* S7_0_PTR;
volatile unsigned char* S7_1_PTR;
volatile unsigned char* S7_2_PTR;
volatile unsigned char* S7_3_PTR;
volatile unsigned char* S7_4_PTR;

volatile int Hour[5];
volatile int Alarm[5];

volatile int flagSet = 0;
volatile int segmentSelected = 0;
volatile int fpgaEnable = 0;
volatile int alarmaActive = 0;
volatile int alarmaTime = 0;

/*
 * method to print a char on a seven segments
 * by now only prints A o F, depending if it is
 * AM o PM.
 */
void printChar(volatile unsigned char * pS7_ptr, int num) {
	if (num == 0) {
		*pS7_ptr = AM_S7;
	} else if (num == 1) {
		*pS7_ptr = PM_S7;
	}
}

/*
 * method to print a number on a seven segments
 * by now only prints numbers betwen 0 and 9.
 */
void printNum(volatile unsigned char * pS7_ptr, int num) {
	if (num == 0) {
		*pS7_ptr = ZERO_S7;
	} else if (num == 1) {
		*pS7_ptr = ONE_S7;
	} else if (num == 2) {
		*pS7_ptr = TWO_S7;
	} else if (num == 3) {
		*pS7_ptr = THREE_S7;
	} else if (num == 4) {
		*pS7_ptr = FOUR_S7;
	} else if (num == 5) {
		*pS7_ptr = FIVE_S7;
	} else if (num == 6) {
		*pS7_ptr = SIX_S7;
	} else if (num == 7) {
		*pS7_ptr = SEVEN_S7;
	} else if (num == 8) {
		*pS7_ptr = EIGHT_S7;
	} else if (num == 9) {
		*pS7_ptr = NINE_S7;
	}
}

/**
 * method to check and increment the values of the alarm.
 * it is triggerd by the push of the button.
 */
void sum_Hour_Alarm_Values(volatile int * pointer) {
	switch (segmentSelected) {
	case 1:
		if (pointer[DECENAS_HORA] == 1)
			pointer[DECENAS_HORA] = 0;
		else
			pointer[DECENAS_HORA] = 1;
		break;
	case 2:
		if (pointer[HORA] == 2 && pointer[DECENAS_HORA] == 1)
			pointer[HORA] = 0;
		else if (pointer[HORA] == 9 && pointer[DECENAS_HORA] == 0)
			pointer[HORA] = 0;
		else
			pointer[HORA]++;
		break;
	case 3:
		if (pointer[DECENAS_MINUTO] == 5)
			pointer[DECENAS_MINUTO] = 0;
		else
			pointer[DECENAS_MINUTO] += 1;
		break;
	case 4:
		if (pointer[MINUTO] == 9)
			pointer[MINUTO] = 0;
		else
			pointer[MINUTO] += 1;
		break;
	case 5:
		if (pointer[4] == 1)
			pointer[4] = 0;
		else
			pointer[4] += 1;
		break;
	}
}

void segmentSelectedLed() {
	switch (segmentSelected) {
	case 1:
		*LED_PTR = FIRST_LED;
		break;
	case 2:
		*LED_PTR = SECOND_LED;
		break;
	case 3:
		*LED_PTR = THIRD_LED;
		break;
	case 4:
		*LED_PTR = FOURTH_LED;
		break;
	case 5:
		*LED_PTR = FIFTH_LED;
		break;
	}
	return;
}

/*
 * method to catch the interrup when someone try to push
 * the 2 on the system.
 */
static void btn_change_seg_handler(void* context) {
	//Aumenta el contador del selector de 7 segmento
	*(BTN_CHANGE_SEG_PTR + 2) = 0xf;
	*(BTN_CHANGE_SEG_PTR + 3) = 0;
	if(segmentSelected==0){
		return;
	}
	segmentSelected = segmentSelected + 1;
	if (segmentSelected > 5) {
		segmentSelected = 1;
	}
	segmentSelectedLed();
	return;
}

/**
 * method to catch the interruption
 * when the last button is press.
 */
static void btn_up_handler(void* context) {
	if (flagSet == 1) {
		sum_Hour_Alarm_Values(Alarm);
	} else if (flagSet == 0) {
		sum_Hour_Alarm_Values(Hour);
	}
	*(BTN_UP_PTR + 2) = 0xf;
	*(BTN_UP_PTR + 3) = 0;
}

/**
 * method to catch the interruption
 * when the thrid button on the system
 * is triggerd.
 */
static void btn_set_handler(void* context) {
	if (segmentSelected == 0) {
		segmentSelected = 1;
		*LED_PTR = FIRST_LED;
	} else {
		segmentSelected = 0;
		*LED_PTR = 0x0;
	}
	*(BTN_SET_PTR + 2) = 0xf;
	*(BTN_SET_PTR + 3) = 0;
}

static void sum_hour(void* context) {
	volatile int *interval_timer_ptr = (int *) TIMER_PTR;

	*(interval_timer_ptr) = 0;           // clear the interrupt

	//add +1 minute to current time
	if (Hour[MINUTO] == 9) {
		Hour[MINUTO] = 0;

		if (Hour[DECENAS_MINUTO] == 5) {
			Hour[DECENAS_MINUTO] = 0;
			if (Hour[HORA] == 9 && Hour[DECENAS_HORA] == 0) {
				Hour[HORA] = 0;
				Hour[DECENAS_HORA] = 1;

			}
			if (Hour[HORA] == 2 && Hour[DECENAS_HORA] == 1) {
				Hour[HORA] = 0;
				Hour[DECENAS_HORA] = 0;

			} else
				++Hour[HORA];

		} else
			++Hour[DECENAS_MINUTO];
	} else
		++Hour[MINUTO];

	if (Hour[DECENAS_HORA] == Alarm[DECENAS_HORA] && Hour[HORA] == Alarm[HORA] && Hour[DECENAS_MINUTO] == Alarm[DECENAS_MINUTO]
			&& Hour[MINUTO] == Alarm[MINUTO] && Hour[4] == Alarm[4]) {
		alarmaActive = 1;
	}
}

void showDataSevenSegments(volatile int * pointer) {
	printNum(S7_0_PTR, pointer[0]);
	printNum(S7_1_PTR, pointer[1]);
	printNum(S7_2_PTR, pointer[2]);
	printNum(S7_3_PTR, pointer[3]);
	printChar(S7_4_PTR, pointer[4]);
}

int main() {
	alt_putstr("Hello from Nios II!\n");
	int tt = 0;
	TIMER_PTR = (unsigned int*) TIMER_0_BASE;
	LED_PTR = (unsigned char*) LED_BASE;
	SW_PTR = (unsigned char*) SW_BASE;
	UART_PTR = (unsigned char*) UART_BASE;
	BTN_UP_PTR = (unsigned int*) BTN_UP_BASE;
	BTN_SET_PTR = (unsigned int*) BTN_SET_BASE;
	BTN_CHANGE_SEG_PTR = (unsigned int*) BTN_CHANGE_SEG_BASE;
	S7_0_PTR = (unsigned char*) SEG_7_0_BASE;
	S7_1_PTR = (unsigned char*) SEG_7_1_BASE;
	S7_2_PTR = (unsigned char*) SEG_7_2_BASE;
	S7_3_PTR = (unsigned char*) SEG_7_3_BASE;
	S7_4_PTR = (unsigned char*) SEG_7_4_BASE;

	for (int i = 0; i < 5; i++) {
		Hour[i] = 0;
		Alarm[i] = 0;
	}
	alt_irq_register(BTN_SET_IRQ, (void*) &tt, btn_set_handler);
	*(BTN_SET_PTR + 2) = 0xf;
	//*(BTN_SET_PTR+3)=0;

	alt_irq_register(BTN_UP_IRQ, (void*) &tt, btn_up_handler);
	*(BTN_UP_PTR + 2) = 0xf;
	//*(BTN_UP_PTR+3)=0;

	alt_irq_register(BTN_CHANGE_SEG_IRQ, (void*) &tt, btn_change_seg_handler);
	*(BTN_CHANGE_SEG_PTR + 2) = 0xf;
	//*(BTN_CHANGE_SEG_PTR+3)=0;

	alt_irq_register(TIMER_0_IRQ, (void*) &tt, sum_hour);

	int timePass = 0;
	alarmaTime = 0;
	*(TIMER_PTR + 1) = 0x7; // STOP = 0, START = 1, CONT = 1, ITO = 1

	while (1) {

		//habilitar el seteo de la alarma
		if (*SW_PTR == 0x1) {
			flagSet = 1;
		}
		//habilitar el seteo de la hora
		else if (*SW_PTR == 0x0) {
			flagSet = 0;
		}

		//para cuando se va a imprimir el seteo de la hora
		if (segmentSelected != 0 && flagSet == 0) {
			showDataSevenSegments(Hour);
			*LED_PTR = 0x2 | *LED_PTR;
		}
		//para cuando se va a imprimir el seteo de la alarma
		else if (segmentSelected != 0 && flagSet == 1) {
			showDataSevenSegments(Alarm);
			*LED_PTR = 0xFD & *LED_PTR;
		}
		//para imprimir la hora
		else if (segmentSelected == 0) {
			showDataSevenSegments(Hour);
			if (alarmaActive == 0)
				*LED_PTR = 0x0; // all off
		}

		if (alarmaActive == 1) {
			switch (timePass) {
			case ALARM_FIRST_BLINK:
				*LED_PTR = 0xAA;
				timePass++;
				break;
			case ALARM_SECOND_BLINK:
				*LED_PTR = 0x55;
				timePass = 0;
				alarmaTime++;
				timePass++;
				break;
			default:
				timePass++;
			}
			if (alarmaTime == ALARM_MAX_TIME) {
				alarmaTime = 0;
				alarmaActive = 0;
				*LED_PTR = 0x0;
			}
		}
	}

	alt_putstr("Program complete\n");
	*LED_PTR = 0x0; // all off
	return 0;
}
