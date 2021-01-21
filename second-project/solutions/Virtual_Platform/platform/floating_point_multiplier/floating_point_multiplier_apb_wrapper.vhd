package pack is    
    constant S0 : integer := 0;
    constant S1 : integer := 1;
    constant S2 : integer := 2;
    constant S3 : integer := 3;
    constant S4 : integer := 4;
	constant S5 : integer := 5;
	constant S6 : integer := 6;
	constant S7 : integer := 7;
	constant S8 : integer := 8;
	constant S9 : integer := 9;
	constant S10 : integer := 10;
	constant S11 : integer := 11;
	constant S12 : integer := 12;
end pack;

library ieee;
use ieee.std_logic_1164.all;
use IEEE.NUMERIC_STD.ALL;
use work.pack.all;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

ENTITY floating_point_multiplier_apb_wrapper IS
	PORT (
		pclk	: in std_logic;
		presetn : in std_logic;
		paddr 	: in std_logic_vector(31 downto 0);
		psel 	: in std_logic;
		penable : in std_logic;
		pwrite 	: in std_logic;
		pwdata 	: in std_logic_vector(31 downto 0);
		pready 	: out std_logic;
		prdata 	: out std_logic_vector(31 downto 0)
	);
END floating_point_multiplier_apb_wrapper;

ARCHITECTURE floating_point_multiplier_apb_wrapper OF floating_point_multiplier_apb_wrapper IS
	COMPONENT floating_point_multiplier
		PORT (
			clk 				: in std_logic;
			rst 				: in std_logic;
			ready 				: in bit;

			VHDL_in 			: in unsigned (31 downto 0);
			verilog_in			: in unsigned (31 downto 0);

			result 				: out unsigned (31 downto 0);
			done 				: out bit;
			eccezione_out 		: out unsigned (2 downto 0)
		);
	END COMPONENT floating_point_multiplier;
	subtype STATE is integer range 0 to 12;

	SIGNAL current_state, next_state : STATE;
	SIGNAL clk					: std_logic;
	SIGNAL rst					: std_logic;
	SIGNAL ready				: bit;
	SIGNAL VHDL_in				: unsigned(31 downto 0);
	SIGNAL verilog_in			: unsigned(31 downto 0);
	SIGNAL eccezione_out		: unsigned(2 downto 0);
	SIGNAL result				: unsigned(31 downto 0);
	SIGNAL done 				: bit;
	SIGNAL temp					: unsigned (31 downto 0);
	SIGNAL temp1				: unsigned (31 downto 0);
	SIGNAL temp2				: unsigned (31 downto 0);
BEGIN

	process (penable, done, current_state)
	begin
		case current_state is
			when S0 =>
				if penable = '1' then
					next_state <= S1;
				else
					next_state <= S0;
				end if;
			when S1 =>
				if penable = '1' then
					next_state <= S1;
				else
					next_state <= S2;
				end if;
			when S2 =>
				if penable = '1' then
					next_state <= S3;
				else
					next_state <= S2;
				end if;
			when S3 =>
				if penable = '1' then
					next_state <= S3;
				else
					next_state <= S4;
				end if;
			when S4 =>
				if penable = '1' then
					next_state <= S5;
				else
					next_state <= S4;
				end if;
			when S5 =>
			     if penable = '1' then
			        next_state <= S5;
                 else
				    next_state <= S6;
				end if;
			when S6 =>
				if penable = '1' then
					next_state <= S7;
				else
					next_state <= S6;
				end if;
			when S7 =>
				next_state <= S8;
			when S8 =>
				if done = '1' then
					next_state <= S9;
				else 
					next_state <= S8;
				end if;
			when S9 =>
				next_state <= S10;
			when S10 =>
				next_state <= S11;
			when S11 =>
				if penable = '1' then
					next_state <= S12;
				else 
					next_state <= S11;
				end if;
			when S12 =>
				if penable = '1' then
					next_state <= S12;
				else 
					next_state <= S0;
				end if;
			when others =>
				next_state <= current_state;
		end case;
	end process;
	
	process (pclk, presetn)
	begin
		if pclk'event and pclk = '1' then
			current_state <= next_state;
			case next_state is
				when S0 =>
					pready <= '0';
					prdata <= (others => '0');
				when S1 =>
					temp <= unsigned(pwdata);
				when S2 =>
					-- empty
				when S3 =>
					temp1 <= unsigned(pwdata);
				when S4 =>
					-- empty
				when S5 =>
					temp2 <= unsigned(pwdata);
				when S6 =>
					-- empty
				when S7 =>
					ready <= '1';
					VHDL_in <= temp;
					verilog_in <= temp1;
					temp <= unsigned(pwdata);
				when S8 =>
					VHDL_in <= temp2;
					verilog_in <= temp;
					ready <= '0';
				when S9 =>
					temp <= result;
				when S10 =>
					temp1 <= result;
				when S11 =>
					pready <= '1';
					prdata <= std_logic_vector(temp);
				when S12 =>
					prdata <= std_logic_vector(temp1);
			end case;
		end if;
	end process;


	floating_point_multiplier_0 : floating_point_multiplier
	PORT MAP(
		clk 				=> pclk,
		ready 				=> ready,
		VHDL_in 			=> VHDL_in,
		verilog_in 			=> verilog_in,
		eccezione_out 		=> eccezione_out,
		done 				=> done,
		result 				=> result,
		rst					=> presetn
	);
END floating_point_multiplier_apb_wrapper;