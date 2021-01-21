library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.NUMERIC_BIT.all;
use ieee.math_real.all;

entity tb is 
end tb;

architecture bh of tb is 
    signal clk : bit;
    signal rst : bit;
    signal ready : bit;

    signal match_segno : bit;
    signal match_esponente : bit;
    signal match_mantissa : bit;
    signal match_eccezione : bit;

    signal VHDL_out : unsigned (31 downto 0);
    signal verilog_out : unsigned (31 downto 0);

    signal done : bit;
    signal result : unsigned (31 downto 0);
    signal eccezione_in : unsigned (2 downto 0);

    signal segno_in_VHDL : bit;
    signal esponente_in_VHDL : unsigned (7 downto 0);
    signal mantissa_in_VHDL : unsigned (22 downto 0);
    signal eccezione_in_VHDL : unsigned (2 downto 0);

    signal segno_in_verilog : bit;
    signal esponente_in_verilog : unsigned (7 downto 0);
    signal mantissa_in_verilog : unsigned (22 downto 0);
    signal eccezione_in_verilog : unsigned (2 downto 0);

    constant ClockPeriod    : time    := 8 ns;

    component tl is
        port (        
            clk : in bit;
            rst : in bit;
            ready : in bit;

            VHDL_in : in unsigned (31 downto 0);
            verilog_in: in unsigned (31 downto 0);

            result: out unsigned(31 downto 0);

            done : out bit;
            eccezione_out : out unsigned (2 downto 0)
            );
    end component tl;

begin

    multiplier_toplevel : tl port map (
        clk => clk,
        rst => rst,
        ready => ready,

        VHDL_in => VHDL_out,
        verilog_in => verilog_out,

        result => result,

        done => done,
        eccezione_out => eccezione_in
    );

    clk <= not clk after ClockPeriod/2;

    process
        variable i: integer :=1;
        variable seed1 : positive;
        variable seed2 : positive;
        variable x : real;
    begin

        seed1 := 1;
        seed2 := 1;
        rst <= '1';
        
        wait for ClockPeriod;        
        
        while i <20 loop     
        
            rst <= '0';  
            
            wait for ClockPeriod;                        
                     
            ready <= '1';

            uniform(seed1, seed2, x);
            VHDL_out <= (to_unsigned(integer(floor(x * 2.0)), 1)(0) & to_unsigned(integer(floor(x * 256.0)), 8) & to_unsigned(integer(floor(x * 8388608.0)), 23));
            uniform(seed1, seed2, x);
            verilog_out <= (to_unsigned(integer(floor(x * 2.0)), 1)(0) & to_unsigned(integer(floor(x * 256.0)), 8) & to_unsigned(integer(floor(x * 8388608.0)), 23));

            wait for ClockPeriod;
            
            uniform(seed1, seed2, x);
            VHDL_out <= (to_unsigned(integer(floor(x * 2.0)), 1)(0) & to_unsigned(integer(floor(x * 256.0)), 8) & to_unsigned(integer(floor(x * 8388608.0)), 23));
            uniform(seed1, seed2, x);             
            verilog_out <= (to_unsigned(integer(floor(x * 2.0)), 1)(0) & to_unsigned(integer(floor(x * 256.0)), 8) & to_unsigned(integer(floor(x * 8388608.0)), 23));
            
            wait for ClockPeriod;
            
            ready <= '0';

            while done /= '1' loop
                wait for ClockPeriod;
            end loop;
            
            segno_in_VHDL <= result(31);
            esponente_in_VHDL <= result(30 downto 23);
            mantissa_in_VHDL <= result(22 downto 0);
            eccezione_in_VHDL <= eccezione_in;
    
            wait for ClockPeriod;
    
            segno_in_verilog <= result(31);
            esponente_in_verilog <= result(30 downto 23);
            mantissa_in_verilog <= result(22 downto 0);
            eccezione_in_verilog <= eccezione_in;
            
            wait for ClockPeriod;

            rst <= '1';            
            VHDL_out <= (others => '0');
            verilog_out <= (others => '0');

            i := i + 1;
            wait for ClockPeriod;
                        
        end loop;

        rst <= '0';

        wait for ClockPeriod;
        
        ready <= '1';

        uniform(seed1, seed2, x);
        VHDL_out <= (to_unsigned(integer(floor(x * 2.0)), 1)(0) & to_unsigned(integer(floor(x * 256.0)), 8) & to_unsigned(integer(floor(x * 8388608.0)), 23));
        verilog_out <= (to_unsigned(integer(floor(x * 2.0)), 1)(0) & to_unsigned(integer(floor(x * 256.0)), 8) & to_unsigned(integer(floor(x * 8388608.0)), 23));
        
        wait for ClockPeriod;
        
        uniform(seed1, seed2, x);
        VHDL_out <= (to_unsigned(integer(floor(x * 2.0)), 1)(0) & to_unsigned(integer(floor(x * 256.0)), 8) & to_unsigned(integer(floor(x * 8388608.0)), 23));
        verilog_out <= (to_unsigned(integer(floor(x * 2.0)), 1)(0) & to_unsigned(integer(floor(x * 256.0)), 8) & to_unsigned(integer(floor(x * 8388608.0)), 23));
        
        wait for ClockPeriod;

        ready <= '0';

        while done /= '1' loop
            wait for ClockPeriod;
        end loop;

        segno_in_VHDL <= result(31);
        esponente_in_VHDL <= result(30 downto 23);
        mantissa_in_VHDL <= result(22 downto 0);
        eccezione_in_VHDL <= eccezione_in;

        wait for ClockPeriod;

        segno_in_verilog <= result(31);
        esponente_in_verilog <= result(30 downto 23);
        mantissa_in_verilog <= result(22 downto 0);
        eccezione_in_verilog <= eccezione_in;
        
        wait for ClockPeriod;

        if segno_in_VHDL = segno_in_verilog then
            match_segno <= '1';
        else
            match_segno <= '0';
        end if;
        if esponente_in_VHDL = esponente_in_verilog then
            match_esponente <= '1';
        else
            match_esponente <= '0';
        end if;
        if mantissa_in_VHDL = mantissa_in_verilog then
            match_mantissa <= '1';
        else
            match_mantissa <= '0';
        end if;
        if eccezione_in_VHDL = eccezione_in_verilog then
            match_eccezione <= '1';
        else
            match_eccezione <= '0';
        end if;

        rst <= '1';
        ready <= '0';
        VHDL_out <= (others => '0');
        verilog_out <= (others => '0');
        wait for ClockPeriod;
    end process;   
end architecture;