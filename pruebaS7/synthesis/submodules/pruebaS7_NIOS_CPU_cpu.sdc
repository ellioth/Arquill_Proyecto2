# Legal Notice: (C)2019 Altera Corporation. All rights reserved.  Your
# use of Altera Corporation's design tools, logic functions and other
# software and tools, and its AMPP partner logic functions, and any
# output files any of the foregoing (including device programming or
# simulation files), and any associated documentation or information are
# expressly subject to the terms and conditions of the Altera Program
# License Subscription Agreement or other applicable license agreement,
# including, without limitation, that your use is for the sole purpose
# of programming logic devices manufactured by Altera and sold by Altera
# or its authorized distributors.  Please refer to the applicable
# agreement for further details.

#**************************************************************
# Timequest JTAG clock definition
#   Uncommenting the following lines will define the JTAG
#   clock in TimeQuest Timing Analyzer
#**************************************************************

#create_clock -period 10MHz {altera_reserved_tck}
#set_clock_groups -asynchronous -group {altera_reserved_tck}

#**************************************************************
# Set TCL Path Variables 
#**************************************************************

set 	pruebaS7_NIOS_CPU_cpu 	pruebaS7_NIOS_CPU_cpu:*
set 	pruebaS7_NIOS_CPU_cpu_oci 	pruebaS7_NIOS_CPU_cpu_nios2_oci:the_pruebaS7_NIOS_CPU_cpu_nios2_oci
set 	pruebaS7_NIOS_CPU_cpu_oci_break 	pruebaS7_NIOS_CPU_cpu_nios2_oci_break:the_pruebaS7_NIOS_CPU_cpu_nios2_oci_break
set 	pruebaS7_NIOS_CPU_cpu_ocimem 	pruebaS7_NIOS_CPU_cpu_nios2_ocimem:the_pruebaS7_NIOS_CPU_cpu_nios2_ocimem
set 	pruebaS7_NIOS_CPU_cpu_oci_debug 	pruebaS7_NIOS_CPU_cpu_nios2_oci_debug:the_pruebaS7_NIOS_CPU_cpu_nios2_oci_debug
set 	pruebaS7_NIOS_CPU_cpu_wrapper 	pruebaS7_NIOS_CPU_cpu_debug_slave_wrapper:the_pruebaS7_NIOS_CPU_cpu_debug_slave_wrapper
set 	pruebaS7_NIOS_CPU_cpu_jtag_tck 	pruebaS7_NIOS_CPU_cpu_debug_slave_tck:the_pruebaS7_NIOS_CPU_cpu_debug_slave_tck
set 	pruebaS7_NIOS_CPU_cpu_jtag_sysclk 	pruebaS7_NIOS_CPU_cpu_debug_slave_sysclk:the_pruebaS7_NIOS_CPU_cpu_debug_slave_sysclk
set 	pruebaS7_NIOS_CPU_cpu_oci_path 	 [format "%s|%s" $pruebaS7_NIOS_CPU_cpu $pruebaS7_NIOS_CPU_cpu_oci]
set 	pruebaS7_NIOS_CPU_cpu_oci_break_path 	 [format "%s|%s" $pruebaS7_NIOS_CPU_cpu_oci_path $pruebaS7_NIOS_CPU_cpu_oci_break]
set 	pruebaS7_NIOS_CPU_cpu_ocimem_path 	 [format "%s|%s" $pruebaS7_NIOS_CPU_cpu_oci_path $pruebaS7_NIOS_CPU_cpu_ocimem]
set 	pruebaS7_NIOS_CPU_cpu_oci_debug_path 	 [format "%s|%s" $pruebaS7_NIOS_CPU_cpu_oci_path $pruebaS7_NIOS_CPU_cpu_oci_debug]
set 	pruebaS7_NIOS_CPU_cpu_jtag_tck_path 	 [format "%s|%s|%s" $pruebaS7_NIOS_CPU_cpu_oci_path $pruebaS7_NIOS_CPU_cpu_wrapper $pruebaS7_NIOS_CPU_cpu_jtag_tck]
set 	pruebaS7_NIOS_CPU_cpu_jtag_sysclk_path 	 [format "%s|%s|%s" $pruebaS7_NIOS_CPU_cpu_oci_path $pruebaS7_NIOS_CPU_cpu_wrapper $pruebaS7_NIOS_CPU_cpu_jtag_sysclk]
set 	pruebaS7_NIOS_CPU_cpu_jtag_sr 	 [format "%s|*sr" $pruebaS7_NIOS_CPU_cpu_jtag_tck_path]

#**************************************************************
# Set False Paths
#**************************************************************

set_false_path -from [get_keepers *$pruebaS7_NIOS_CPU_cpu_oci_break_path|break_readreg*] -to [get_keepers *$pruebaS7_NIOS_CPU_cpu_jtag_sr*]
set_false_path -from [get_keepers *$pruebaS7_NIOS_CPU_cpu_oci_debug_path|*resetlatch]     -to [get_keepers *$pruebaS7_NIOS_CPU_cpu_jtag_sr[33]]
set_false_path -from [get_keepers *$pruebaS7_NIOS_CPU_cpu_oci_debug_path|monitor_ready]  -to [get_keepers *$pruebaS7_NIOS_CPU_cpu_jtag_sr[0]]
set_false_path -from [get_keepers *$pruebaS7_NIOS_CPU_cpu_oci_debug_path|monitor_error]  -to [get_keepers *$pruebaS7_NIOS_CPU_cpu_jtag_sr[34]]
set_false_path -from [get_keepers *$pruebaS7_NIOS_CPU_cpu_ocimem_path|*MonDReg*] -to [get_keepers *$pruebaS7_NIOS_CPU_cpu_jtag_sr*]
set_false_path -from *$pruebaS7_NIOS_CPU_cpu_jtag_sr*    -to *$pruebaS7_NIOS_CPU_cpu_jtag_sysclk_path|*jdo*
set_false_path -from sld_hub:*|irf_reg* -to *$pruebaS7_NIOS_CPU_cpu_jtag_sysclk_path|ir*
set_false_path -from sld_hub:*|sld_shadow_jsm:shadow_jsm|state[1] -to *$pruebaS7_NIOS_CPU_cpu_oci_debug_path|monitor_go
