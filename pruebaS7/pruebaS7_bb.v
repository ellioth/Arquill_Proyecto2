
module pruebaS7 (
	btn_pin_export,
	clk_clk,
	led_pin_export,
	reset_reset_n,
	seg_7_0_pin_export,
	seg_7_1_pin_export,
	seg_7_2_pin_export,
	seg_7_3_pin_export,
	seg_7_4_pin_export,
	sw_pin_export);	

	input	[1:0]	btn_pin_export;
	input		clk_clk;
	output	[7:0]	led_pin_export;
	input		reset_reset_n;
	output	[6:0]	seg_7_0_pin_export;
	output	[6:0]	seg_7_1_pin_export;
	output	[6:0]	seg_7_2_pin_export;
	output	[6:0]	seg_7_3_pin_export;
	output	[6:0]	seg_7_4_pin_export;
	input	[7:0]	sw_pin_export;
endmodule
