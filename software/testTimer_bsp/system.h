/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'NIOS_CPU' in SOPC Builder design 'pruebaS7'
 * SOPC Builder design path: ../../pruebaS7.sopcinfo
 *
 * Generated: Wed Oct 16 00:32:42 CST 2019
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * BTN configuration
 *
 */

#define ALT_MODULE_CLASS_BTN altera_avalon_pio
#define BTN_BASE 0x11070
#define BTN_BIT_CLEARING_EDGE_REGISTER 0
#define BTN_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BTN_CAPTURE 0
#define BTN_DATA_WIDTH 2
#define BTN_DO_TEST_BENCH_WIRING 0
#define BTN_DRIVEN_SIM_VALUE 0
#define BTN_EDGE_TYPE "NONE"
#define BTN_FREQ 50000000
#define BTN_HAS_IN 1
#define BTN_HAS_OUT 0
#define BTN_HAS_TRI 0
#define BTN_IRQ -1
#define BTN_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BTN_IRQ_TYPE "NONE"
#define BTN_NAME "/dev/BTN"
#define BTN_RESET_VALUE 0
#define BTN_SPAN 16
#define BTN_TYPE "altera_avalon_pio"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x00010820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x11
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x00008020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x11
#define ALT_CPU_NAME "NIOS_CPU"
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00008000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x00010820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x11
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x00008020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x11
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00008000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_GEN2


/*
 * LED configuration
 *
 */

#define ALT_MODULE_CLASS_LED altera_avalon_pio
#define LED_BASE 0x11090
#define LED_BIT_CLEARING_EDGE_REGISTER 0
#define LED_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LED_CAPTURE 0
#define LED_DATA_WIDTH 8
#define LED_DO_TEST_BENCH_WIRING 0
#define LED_DRIVEN_SIM_VALUE 0
#define LED_EDGE_TYPE "NONE"
#define LED_FREQ 50000000
#define LED_HAS_IN 0
#define LED_HAS_OUT 1
#define LED_HAS_TRI 0
#define LED_IRQ -1
#define LED_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LED_IRQ_TYPE "NONE"
#define LED_NAME "/dev/LED"
#define LED_RESET_VALUE 0
#define LED_SPAN 16
#define LED_TYPE "altera_avalon_pio"


/*
 * RAM configuration
 *
 */

#define ALT_MODULE_CLASS_RAM altera_avalon_onchip_memory2
#define RAM_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define RAM_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define RAM_BASE 0x8000
#define RAM_CONTENTS_INFO ""
#define RAM_DUAL_PORT 0
#define RAM_GUI_RAM_BLOCK_TYPE "AUTO"
#define RAM_INIT_CONTENTS_FILE "pruebaS7_RAM"
#define RAM_INIT_MEM_CONTENT 1
#define RAM_INSTANCE_ID "NONE"
#define RAM_IRQ -1
#define RAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define RAM_NAME "/dev/RAM"
#define RAM_NON_DEFAULT_INIT_FILE_ENABLED 0
#define RAM_RAM_BLOCK_TYPE "AUTO"
#define RAM_READ_DURING_WRITE_MODE "DONT_CARE"
#define RAM_SINGLE_CLOCK_OP 0
#define RAM_SIZE_MULTIPLE 1
#define RAM_SIZE_VALUE 32768
#define RAM_SPAN 32768
#define RAM_TYPE "altera_avalon_onchip_memory2"
#define RAM_WRITABLE 1


/*
 * SEG_7_0 configuration
 *
 */

#define ALT_MODULE_CLASS_SEG_7_0 altera_avalon_pio
#define SEG_7_0_BASE 0x11060
#define SEG_7_0_BIT_CLEARING_EDGE_REGISTER 0
#define SEG_7_0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SEG_7_0_CAPTURE 0
#define SEG_7_0_DATA_WIDTH 7
#define SEG_7_0_DO_TEST_BENCH_WIRING 0
#define SEG_7_0_DRIVEN_SIM_VALUE 0
#define SEG_7_0_EDGE_TYPE "NONE"
#define SEG_7_0_FREQ 50000000
#define SEG_7_0_HAS_IN 0
#define SEG_7_0_HAS_OUT 1
#define SEG_7_0_HAS_TRI 0
#define SEG_7_0_IRQ -1
#define SEG_7_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEG_7_0_IRQ_TYPE "NONE"
#define SEG_7_0_NAME "/dev/SEG_7_0"
#define SEG_7_0_RESET_VALUE 0
#define SEG_7_0_SPAN 16
#define SEG_7_0_TYPE "altera_avalon_pio"


/*
 * SEG_7_1 configuration
 *
 */

#define ALT_MODULE_CLASS_SEG_7_1 altera_avalon_pio
#define SEG_7_1_BASE 0x11050
#define SEG_7_1_BIT_CLEARING_EDGE_REGISTER 0
#define SEG_7_1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SEG_7_1_CAPTURE 0
#define SEG_7_1_DATA_WIDTH 7
#define SEG_7_1_DO_TEST_BENCH_WIRING 0
#define SEG_7_1_DRIVEN_SIM_VALUE 0
#define SEG_7_1_EDGE_TYPE "NONE"
#define SEG_7_1_FREQ 50000000
#define SEG_7_1_HAS_IN 0
#define SEG_7_1_HAS_OUT 1
#define SEG_7_1_HAS_TRI 0
#define SEG_7_1_IRQ -1
#define SEG_7_1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEG_7_1_IRQ_TYPE "NONE"
#define SEG_7_1_NAME "/dev/SEG_7_1"
#define SEG_7_1_RESET_VALUE 0
#define SEG_7_1_SPAN 16
#define SEG_7_1_TYPE "altera_avalon_pio"


/*
 * SEG_7_2 configuration
 *
 */

#define ALT_MODULE_CLASS_SEG_7_2 altera_avalon_pio
#define SEG_7_2_BASE 0x11040
#define SEG_7_2_BIT_CLEARING_EDGE_REGISTER 0
#define SEG_7_2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SEG_7_2_CAPTURE 0
#define SEG_7_2_DATA_WIDTH 7
#define SEG_7_2_DO_TEST_BENCH_WIRING 0
#define SEG_7_2_DRIVEN_SIM_VALUE 0
#define SEG_7_2_EDGE_TYPE "NONE"
#define SEG_7_2_FREQ 50000000
#define SEG_7_2_HAS_IN 0
#define SEG_7_2_HAS_OUT 1
#define SEG_7_2_HAS_TRI 0
#define SEG_7_2_IRQ -1
#define SEG_7_2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEG_7_2_IRQ_TYPE "NONE"
#define SEG_7_2_NAME "/dev/SEG_7_2"
#define SEG_7_2_RESET_VALUE 0
#define SEG_7_2_SPAN 16
#define SEG_7_2_TYPE "altera_avalon_pio"


/*
 * SEG_7_3 configuration
 *
 */

#define ALT_MODULE_CLASS_SEG_7_3 altera_avalon_pio
#define SEG_7_3_BASE 0x11030
#define SEG_7_3_BIT_CLEARING_EDGE_REGISTER 0
#define SEG_7_3_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SEG_7_3_CAPTURE 0
#define SEG_7_3_DATA_WIDTH 7
#define SEG_7_3_DO_TEST_BENCH_WIRING 0
#define SEG_7_3_DRIVEN_SIM_VALUE 0
#define SEG_7_3_EDGE_TYPE "NONE"
#define SEG_7_3_FREQ 50000000
#define SEG_7_3_HAS_IN 0
#define SEG_7_3_HAS_OUT 1
#define SEG_7_3_HAS_TRI 0
#define SEG_7_3_IRQ -1
#define SEG_7_3_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEG_7_3_IRQ_TYPE "NONE"
#define SEG_7_3_NAME "/dev/SEG_7_3"
#define SEG_7_3_RESET_VALUE 0
#define SEG_7_3_SPAN 16
#define SEG_7_3_TYPE "altera_avalon_pio"


/*
 * SEG_7_4 configuration
 *
 */

#define ALT_MODULE_CLASS_SEG_7_4 altera_avalon_pio
#define SEG_7_4_BASE 0x11020
#define SEG_7_4_BIT_CLEARING_EDGE_REGISTER 0
#define SEG_7_4_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SEG_7_4_CAPTURE 0
#define SEG_7_4_DATA_WIDTH 7
#define SEG_7_4_DO_TEST_BENCH_WIRING 0
#define SEG_7_4_DRIVEN_SIM_VALUE 0
#define SEG_7_4_EDGE_TYPE "NONE"
#define SEG_7_4_FREQ 50000000
#define SEG_7_4_HAS_IN 0
#define SEG_7_4_HAS_OUT 1
#define SEG_7_4_HAS_TRI 0
#define SEG_7_4_IRQ -1
#define SEG_7_4_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEG_7_4_IRQ_TYPE "NONE"
#define SEG_7_4_NAME "/dev/SEG_7_4"
#define SEG_7_4_RESET_VALUE 0
#define SEG_7_4_SPAN 16
#define SEG_7_4_TYPE "altera_avalon_pio"


/*
 * SW configuration
 *
 */

#define ALT_MODULE_CLASS_SW altera_avalon_pio
#define SW_BASE 0x11080
#define SW_BIT_CLEARING_EDGE_REGISTER 0
#define SW_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SW_CAPTURE 0
#define SW_DATA_WIDTH 8
#define SW_DO_TEST_BENCH_WIRING 0
#define SW_DRIVEN_SIM_VALUE 0
#define SW_EDGE_TYPE "NONE"
#define SW_FREQ 50000000
#define SW_HAS_IN 1
#define SW_HAS_OUT 0
#define SW_HAS_TRI 0
#define SW_IRQ -1
#define SW_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SW_IRQ_TYPE "NONE"
#define SW_NAME "/dev/SW"
#define SW_RESET_VALUE 0
#define SW_SPAN 16
#define SW_TYPE "altera_avalon_pio"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone V"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/UART"
#define ALT_STDERR_BASE 0x110a0
#define ALT_STDERR_DEV UART
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/UART"
#define ALT_STDIN_BASE 0x110a0
#define ALT_STDIN_DEV UART
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/UART"
#define ALT_STDOUT_BASE 0x110a0
#define ALT_STDOUT_DEV UART
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "pruebaS7"


/*
 * UART configuration
 *
 */

#define ALT_MODULE_CLASS_UART altera_avalon_jtag_uart
#define UART_BASE 0x110a0
#define UART_IRQ 0
#define UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define UART_NAME "/dev/UART"
#define UART_READ_DEPTH 64
#define UART_READ_THRESHOLD 8
#define UART_SPAN 8
#define UART_TYPE "altera_avalon_jtag_uart"
#define UART_WRITE_DEPTH 64
#define UART_WRITE_THRESHOLD 8


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 4
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none


/*
 * timer_0 configuration
 *
 */

#define ALT_MODULE_CLASS_timer_0 altera_avalon_timer
#define TIMER_0_ALWAYS_RUN 1
#define TIMER_0_BASE 0x11000
#define TIMER_0_COUNTER_SIZE 32
#define TIMER_0_FIXED_PERIOD 1
#define TIMER_0_FREQ 50000000
#define TIMER_0_IRQ 1
#define TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_0_LOAD_VALUE 49999999
#define TIMER_0_MULT 1.0
#define TIMER_0_NAME "/dev/timer_0"
#define TIMER_0_PERIOD 1
#define TIMER_0_PERIOD_UNITS "s"
#define TIMER_0_RESET_OUTPUT 0
#define TIMER_0_SNAPSHOT 0
#define TIMER_0_SPAN 32
#define TIMER_0_TICKS_PER_SEC 1
#define TIMER_0_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_0_TYPE "altera_avalon_timer"

#endif /* __SYSTEM_H_ */
