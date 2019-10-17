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
unsigned c;
int flagSetHour = 0;
int flagSetAlarm = 0;
int segmentSelected=0;
int fpgaEnable = 0;

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
	int number;
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

void checkAlarmValues(){
	if(segmentSelected==1 && Alarm[0]==1){
		*LED_PTR = 0x85;
		Alarm[0]=0;
	}
	else if(segmentSelected==1){
		*LED_PTR = 0x85;
		Alarm[0]=1;
	}
	else if(segmentSelected==2 && Alarm[1]==2 && Alarm[0]==1){
		*LED_PTR = 0x45;
		Alarm[1]=0;
	}
	else if(segmentSelected==2 && Alarm[1]==9 && Alarm[0]==0){
		*LED_PTR = 0x45;
		Alarm[1]=0;
	}
	else if(segmentSelected==2){
		*LED_PTR = 0x45;
		Alarm[1]+=1;
	}
	else if(segmentSelected==3 && Alarm[2]==5){
		*LED_PTR = 0x25;
		Alarm[2]=0;
	}
	else if(segmentSelected==3){
		*LED_PTR = 0x25;
		Alarm[2]+=1;
	}
	else if(segmentSelected==4 && Alarm[3]==9){
		*LED_PTR = 0x15;
		Alarm[3]=0;
	}
	else if(segmentSelected==4){
		*LED_PTR = 0x15;
		Alarm[3]+=1;
	}
	else if(segmentSelected==5 && Alarm[4]==1){
		*LED_PTR = 0xD;
		Alarm[4]=0;
	}
	else if(segmentSelected==5){
		*LED_PTR = 0xD;
		Alarm[4]=1;
	}
}

void checkHourValues(){
	if(segmentSelected==1 && Alarm[0]==1){
		*LED_PTR = 0x87;
		Hour[0]=0;
	}
	else if(segmentSelected==1){
		*LED_PTR = 0x87;
		Hour[0]=1;
	}
	else if(segmentSelected==2 && Hour[1]==2 && Hour[0]==1){
		*LED_PTR = 0x47;
		Hour[1]=0;
	}
	else if(segmentSelected==2 && Hour[1]==9 && Hour[0]==0){
		*LED_PTR = 0x47;
		Hour[1]=0;
	}
	else if(segmentSelected==2){
		*LED_PTR = 0x47;
		Hour[1]+=1;
	}
	else if(segmentSelected==3 && Hour[2]==5){
		*LED_PTR = 0x27;
		Hour[2]=0;
	}
	else if(segmentSelected==3){
		*LED_PTR = 0x27;
		Hour[2]+=1;
	}
	else if(segmentSelected==4 && Hour[3]==9){
		*LED_PTR = 0x17;
		Hour[3]=0;
	}
	else if(segmentSelected==4){
		*LED_PTR = 0x17;
		Hour[3]+=1;
	}
	else if(segmentSelected==5 && Hour[4]==1){
		*LED_PTR = 0xF;
		Hour[4]=0;
	}
	else if(segmentSelected==5){
		*LED_PTR = 0xF;
		Hour[4]=1;
	}
}

void btn_up_handler(){
	if(flagSet==1){
		checkAlarmValues();
	}
	else if(flagSet==0){
		checkHourValues();
	}
}

void btn_set_handler(){
	if(segmentSelected==1){
		segmentSelected=0;
	}
	else{
		segmentSelected=1;
	}
	flagSet=*SW_PTR;
	if(flagSet==1){
		checkAlarmValues();
	}
	else if(flagSet==0){
		checkHourValues();
	}
}


int main()
{ 
  alt_putstr("Hello from Nios II!\n");

  LED_PTR= (unsigned char*)0x3070;
  SW_PTR= (unsigned char*)0x3060;
  UART_PTR=(unsigned char*)0x3080;
  BTN_PTR= (unsigned char*)0x3050;
  S7_0_PTR= (unsigned char*)0x3040;
  S7_1_PTR= (unsigned char*)0x3030;
  S7_2_PTR= (unsigned char*)0x3020;
  S7_3_PTR= (unsigned char*)0x3010;
  S7_4_PTR= (unsigned char*)0x3000;
  /* Event loop never exits. */




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
    	  else{
    		  flagSetHour=1;
    	  }

    	  flagSetAlarm=0;
    	  break;
      case 'W':
    	  //habilitar y setear alarma desde el teclado
    	  if(flagSetAlarm){
    		  *LED_PTR = 0x5;
    		  flagSetAlarm=0;
    		  segmentSelected=1;
    	  }
    	  else{
    		  flagSetAlarm=1;
    	  }
    	  flagSetHour=0;
    	  break;
      }
      if(flagSetAlarm || flagSetHour){
    	  //seleccionar 7 segmento
    	  segmentSelected = setSegmentSelected(segmentSelected,input);

    	  //verficar cual 7 segmento cambiar
    	  if(*BTN_PTR == 0x1){
    		  //DELAY
    		  int delay = 0;
    		  while(delay < 1000000)
    		  {
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
        		  Alarm[4]=*SW_PTR & 0x0F;
        	  }
        	  else if(flagSetHour==1){
				  *LED_PTR = 0xF;
				  Hour[4]=*SW_PTR & 0x0F;
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
				  Alarm[3]=*SW_PTR & 0x0F;
			  }
			  else if(flagSetHour==1){
				  *LED_PTR = 0x17;
				  Hour[3]=*SW_PTR & 0x0F;
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
				  Alarm[2]=*SW_PTR & 0x0F;
			  }
			  else if(flagSetHour==1){
				  *LED_PTR = 0x27;
				  Hour[2]=*SW_PTR & 0x0F;
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
				  Alarm[1]=*SW_PTR & 0x0F;
			  }
			  else if(flagSetHour==1){
				  *LED_PTR = 0x47;
				  Hour[1]=*SW_PTR & 0x0F;
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
				  Alarm[0]=*SW_PTR & 0x0F;
			  }
			  else if(flagSetHour==1){
				  *LED_PTR = 0x87;
				  Hour[0]=*SW_PTR & 0x0F;
			  }
        	  setNum(S7_0_PTR,input);
        	  if(fpgaEnable){
        		  printNum(S7_0_PTR, *SW_PTR & 0x0F);
        	  }
        	  break;
          }
      }
    }

    alt_putstr("Program complete\n");
    *LED_PTR = 0x0; // all off
  /*
  while (1){
	  printNum(S7_0_PTR, *SW_PTR);
	  printNum(S7_1_PTR, *SW_PTR);
  }*/

  return 0;
}
