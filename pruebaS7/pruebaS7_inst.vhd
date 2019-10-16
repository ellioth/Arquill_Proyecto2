	component pruebaS7 is
		port (
			btn_pin_export     : in  std_logic_vector(1 downto 0) := (others => 'X'); -- export
			clk_clk            : in  std_logic                    := 'X';             -- clk
			led_pin_export     : out std_logic_vector(7 downto 0);                    -- export
			reset_reset_n      : in  std_logic                    := 'X';             -- reset_n
			seg_7_0_pin_export : out std_logic_vector(6 downto 0);                    -- export
			seg_7_1_pin_export : out std_logic_vector(6 downto 0);                    -- export
			sw_pin_export      : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
			seg_7_2_pin_export : out std_logic_vector(6 downto 0);                    -- export
			seg_7_3_pin_export : out std_logic_vector(6 downto 0);                    -- export
			seg_7_4_pin_export : out std_logic_vector(6 downto 0)                     -- export
		);
	end component pruebaS7;

	u0 : component pruebaS7
		port map (
			btn_pin_export     => CONNECTED_TO_btn_pin_export,     --     btn_pin.export
			clk_clk            => CONNECTED_TO_clk_clk,            --         clk.clk
			led_pin_export     => CONNECTED_TO_led_pin_export,     --     led_pin.export
			reset_reset_n      => CONNECTED_TO_reset_reset_n,      --       reset.reset_n
			seg_7_0_pin_export => CONNECTED_TO_seg_7_0_pin_export, -- seg_7_0_pin.export
			seg_7_1_pin_export => CONNECTED_TO_seg_7_1_pin_export, -- seg_7_1_pin.export
			sw_pin_export      => CONNECTED_TO_sw_pin_export,      --      sw_pin.export
			seg_7_2_pin_export => CONNECTED_TO_seg_7_2_pin_export, -- seg_7_2_pin.export
			seg_7_3_pin_export => CONNECTED_TO_seg_7_3_pin_export, -- seg_7_3_pin.export
			seg_7_4_pin_export => CONNECTED_TO_seg_7_4_pin_export  -- seg_7_4_pin.export
		);

