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
#include <system.h>
#include "altera_avalon_jtag_uart_regs.h"

volatile unsigned char* LED_PTR;
volatile unsigned char* SW_PTR;
volatile unsigned char* UART_PTR;
volatile unsigned char* BTN_PTR;
volatile unsigned char* S7_0_PTR;
volatile unsigned char* S7_1_PTR;
volatile unsigned char* S7_2_PTR;
volatile unsigned char* S7_3_PTR;
volatile unsigned char* S7_4_PTR;
int Hour[5];
int Alarm[5];

/**
 * method to print an A or P on the last seven
 * segments of the fpga.
 * recives the pointer of the seven segements
 * and the number that goes corresponding the
 * A or P,
 */
void printChar(volatile unsigned char * pS7_ptr, int num){
	if(num==0){
		*pS7_ptr=0x8;
	}
	else if(num==1){
		*pS7_ptr=0xC;
	}
}

void printNum(volatile unsigned char * pS7_ptr, int num){
	if(num==0){
		*pS7_ptr=0x40;
	}
	else if(num==1){
		*pS7_ptr=0x79;
	}
	else if(num==2){
		*pS7_ptr=0x24;
	}
	else if(num==3){
		*pS7_ptr=0xB0;
	}
	else if(num==4){
		*pS7_ptr=0x99;
	}
	else if(num==5){
		*pS7_ptr=0x12;
	}
	else if(num==6){
		*pS7_ptr=0x82;
	}
	else if(num==7){
		*pS7_ptr=0xF8;
	}
	else if(num==8){
		*pS7_ptr=0x80;
	}
	else if(num==9){
		*pS7_ptr=0x10;
	}
}

void setNum(volatile unsigned char * pS7_ptr,const char * input){
	switch(*input){
    case '0':
  	  printNum(pS7_ptr, 0);
  	  break;
    case '1':
  	  printNum(pS7_ptr, 1);
  	  break;
    case '2':
  	  printNum(pS7_ptr, 2);
  	  break;
    case '3':
  	  printNum(pS7_ptr, 3);
  	  break;
    case '4':
  	  printNum(pS7_ptr, 4);
  	  break;
    case '5':
  	  printNum(pS7_ptr, 5);
  	  break;
    case '6':
  	  printNum(pS7_ptr, 6);
  	  break;
    case '7':
  	  printNum(pS7_ptr, 7);
  	  break;
    case '8':
  	  printNum(pS7_ptr, 8);
  	  break;
    case '9':
  	  printNum(pS7_ptr, 9);
  	  break;
    case 'a':
	  printChar(pS7_ptr, 0);
	  break;
    case 'p':
	  printChar(pS7_ptr, 1);
	  break;
    }
}

int setSegmentSelected(int segmentSelected,const char * input){

    switch(*input){
    case 'Z':
  	  //7 segmento hora 1
  	  segmentSelected=5;
  	  break;
    case 'X':
  	  //7 segmento hora 2
  	  segmentSelected=4;
  	  break;
    case 'C':
  	  //7 segmento min 1
  	  segmentSelected=3;
  	  break;
    case 'V':
  	  //7 segmento min 2
  	  segmentSelected=2;
  	  break;
    case 'B':
  	  //7 segmento tiempo AM/PM
  	  segmentSelected=1;
  	  break;
    }

	return segmentSelected;


}

void checkClock(int tickLast, int tickActual){
	///Hour=[0,0,0,0];
	if((tickActual-tickLast)==1){
		if(Hour[3]==10){///Hour=[0,0,0,#9#];
			Hour[3]=0;
			Hour[2]+=1;///Hour=[0,0,+1,#0#];
		}
		if(Hour[2]==6){///Hour=[0,0,6,#*#];
			Hour[2]=0;
			Hour[1]+=1;///Hour=[0,+1,#0#,*];
		}
		if(Hour[1]==10){
			Hour[1]=0;
			Hour[0]+=1;///Hour=[0,#9#,*,*];
		}
		if(Hour[0]==1 && Hour[1]==3){
			Hour[0]=0;///Hour=[#0#,*,*,*];
			Hour[1]=1;
			Hour[2]=0;
			Hour[3]=0;
			if(Hour[4]==0){
				Hour[4]=1;
			}
			else{
				Hour[4]=0;
			}
		}
	}
}

int checkAlarm(){
	if(Hour[0]==Alarm[0] &&
			Hour[1]==Alarm[1] &&
			Hour[2]==Alarm[2] &&
			Hour[3]==Alarm[3] &&
			Hour[4]==Alarm[4]){
		return 0;
	}
	return 1;
}

int main(){

	alt_putstr("Hello from Nios II!\n");

	for(int i=0; i<5; i++){
		Hour[i]=0;
		Alarm[i]=0;
	}
	LED_PTR= (unsigned char*)0x3090;
	SW_PTR= (unsigned char*)0x3080;
	UART_PTR=(unsigned char*)0x30a0;
	BTN_PTR= (unsigned char*)0x3070;
	S7_0_PTR= (unsigned char*)0x3060;
	S7_1_PTR= (unsigned char*)0x3050;
	S7_2_PTR= (unsigned char*)0x3040;
	S7_3_PTR= (unsigned char*)0x3030;
	S7_4_PTR= (unsigned char*)0x3020;
	/* Event loop never exits. */

	unsigned c;
	int flagSetHour = 0;
	int flagSetAlarm = 0;
	int segmentSelected=1;
	int fpgaEnable = 0;

	int alarmDuration=10;
	int alarmFlag=0;

	int tickLast=0;
	int tickActual=0;

	while (1) {
		c = *UART_PTR;
		unsigned temp = c & ALTERA_AVALON_JTAG_UART_DATA_DATA_MSK;
		const char * input = (char *)&temp;

		//habilitar y setear hora desde el switch
		if((*SW_PTR & 0x80) == 0x80){
			fpgaEnable=1;
			flagSetHour=1;
			flagSetAlarm=0;
			*LED_PTR = 0x7; //para demostrar con los leds que esta estableciendo la hora
		}
		else if ((*SW_PTR & 0x80) == 0x0){
			if(flagSetHour==1){
				fpgaEnable=0;
				*LED_PTR = 0x0;
				flagSetHour=0;
				segmentSelected=1;
			}
		}

		//habilitar y setear hora desde la alarma
		if((*SW_PTR & 0x40)  == 0x40){
			fpgaEnable=1;
			flagSetHour=0;
			flagSetAlarm=1;
			*LED_PTR = 0x5; //para demostras con los leds que esta estableciendo la alarma
		}
		else if((*SW_PTR & 0x40)  == 0x0){
			if (flagSetAlarm==1){
				fpgaEnable=0;
				*LED_PTR = 0x0;
				flagSetAlarm=0;
				segmentSelected=1;
			}
		}

		switch(*input){
			case 'Q':
				//habilitar y setear hora desde el teclado
				if(flagSetHour){
					*LED_PTR = 0x7;
					flagSetHour=0;
					segmentSelected=1;
				}
				else
					flagSetHour=1;
				flagSetAlarm=0;
				break;
			case 'W':
				//habilitar y setear alarma desde el teclado
				if(flagSetAlarm){
					*LED_PTR = 0x5;
					flagSetAlarm=0;
					segmentSelected=1;
				}
				else
					flagSetAlarm=1;
				flagSetHour=0;
				break;
		}

		if(flagSetAlarm || flagSetHour){
			//7 segmento para AM/PM
			if(flagSetAlarm==1){
				for(int i=0; i<4; i++){
					printNum(S7_4_PTR, Alarm[i]);
				}
				printChar(S7_4_PTR, Alarm[4]);
			}
			else if(flagSetHour==1){
				for(int i=0; i<4; i++){
					printNum(S7_4_PTR, Hour[i]);
				}
				printChar(S7_4_PTR, Hour[4]);
			}
			//seleccionar 7 segmento
			segmentSelected = setSegmentSelected(segmentSelected,input);

			//verficar cual 7 segmento cambiar
			if(*BTN_PTR == 0x1){
				//DELAY
				int delay = 0;
				while(delay < 1000000){
					delay++;
				}
				//Aumenta el contador del selector de 7 segmento
				segmentSelected=segmentSelected+1;
				if(segmentSelected > 5){
					segmentSelected = 1;
				}
			}
			switch(segmentSelected){
				case 5:
					//7 segmento para AM/PM
					if(flagSetAlarm==1){
						*LED_PTR = 0xD;
						Alarm[4]=(*SW_PTR & 0x0F);
					}
					else if(flagSetHour==1){
						*LED_PTR = 0xF;
						Hour[4]=(*SW_PTR & 0x0F);
					}
					setNum(S7_4_PTR,input);
					if(fpgaEnable){
						printChar(S7_4_PTR, *SW_PTR & 0x0F);
					}
					break;
				case 4:
					//7 segmento minuto[2]
					if(flagSetAlarm==1){
						*LED_PTR = 0x15;
						Alarm[3]=(*SW_PTR & 0x0F);
					}
					else if(flagSetHour==1){
						*LED_PTR = 0x17;
						Hour[3]=(*SW_PTR & 0x0F);
					}
					setNum(S7_3_PTR,input);
					if(fpgaEnable){
						printNum(S7_3_PTR, *SW_PTR & 0x0F);
					}
					break;
				case 3:
					//7 segmento minuto[1]
					if(flagSetAlarm==1){
						*LED_PTR = 0x25;
						Alarm[2]=(*SW_PTR & 0x0F);
					}
					else if(flagSetHour==1){
						*LED_PTR = 0x27;
						Hour[2]=(*SW_PTR & 0x0F);
					}
					setNum(S7_2_PTR,input);
					if(fpgaEnable){
						printNum(S7_2_PTR, *SW_PTR & 0x0F);
					}
					break;
				case 2:
					//7 segmento hora[2]
					if(flagSetAlarm==1){
						*LED_PTR = 0x45;
						Alarm[1]=(*SW_PTR & 0x0F);
					}
					else if(flagSetHour==1){
						*LED_PTR = 0x47;
						Hour[1]=(*SW_PTR & 0x0F);
					}
					setNum(S7_1_PTR,input);
					if(fpgaEnable){
						printNum(S7_1_PTR, *SW_PTR & 0x0F);
					}
					break;
				case 1:
					//7 segmento hora[1]
					if(flagSetAlarm==1){
						*LED_PTR = 0x85;
						Alarm[0]=(*SW_PTR & 0x0F);
					}
					else if(flagSetHour==1){
						*LED_PTR = 0x87;
						Hour[0]=(*SW_PTR & 0x0F);
					}
					setNum(S7_0_PTR,input);
					if(fpgaEnable){
						printNum(S7_0_PTR, *SW_PTR & 0x0F);
					}
					break;
			}
		}
		/*
		else{
			for(int i=0; i<4; i++){
				printNum(S7_4_PTR, Hour[i]);
			}
			printChar(S7_4_PTR, Hour[4]);

			//suma de la hora, se tiene que operar sobre tickActual

			checkClock(tickActual, tickLast); //ask if the clock is not out bounds(am/pm format)

			if(checkAlarm()==0){
				alarmFlag=1;
				tickLast=tickActual;
			}

			if(alarmFlag==1 && alarmDuration!=0 && (alarmDuration%2)==0){
				*LED_PTR = 0xAA;
			}
			else if(alarmFlag==1 && alarmDuration!=0 && (alarmDuration%2)!=0){
				*LED_PTR = 0x55;
			}
			else if(alarmDuration==0){
				alarmFlag=0;
				alarmDuration=11;
			}
			if((tickActual-tickLast)==1){
				alarmDuration--;
				tickLast=tickActual;
			}
		}*/
	}
	alt_putstr("Program complete\n");
	*LED_PTR = 0x0; // all off
	return 0;
}
