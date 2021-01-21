package multiplier_pack_toplevel is
    constant S0 : integer := 0;
    constant S1 : integer := 1;
    constant S2 : integer := 2;
    constant S3 : integer := 3;
    constant S4 : integer := 4;
    constant S5 : integer := 5;
    constant S6 : integer := 6;
    constant S7 : integer := 7;
    constant S8 : integer := 8;
    constant MANTISSA : integer := 23;
    constant ESPONENTE : integer := 8;
end multiplier_pack_toplevel;

library ieee;
use ieee.std_logic_1164.all;
USE WORK.multiplier_pack_toplevel.ALL;
use IEEE.NUMERIC_STD.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity floating_point_multiplier is 
    port(
        clk : in std_logic;
        rst : in std_logic;
        ready : in bit;

        VHDL_in : in unsigned (31 downto 0);
        verilog_in  : in unsigned (31 downto 0);

        result: out unsigned (31 downto 0);
        done : out bit;
        eccezione_out : out unsigned (2 downto 0)
    );
end floating_point_multiplier;

architecture floating_point_multiplier of floating_point_multiplier is 
        subtype STATE is integer range 0 to 8;

        signal current_state, next_state : STATE;

        signal VHDL_out : unsigned (31 downto 0);
        signal verilog_out : unsigned (31 downto 0);

        signal done_VHDL : bit;
        signal eccezione_out_VHDL : unsigned (2 downto 0);
        signal done_verilog : bit;
        signal eccezione_out_verilog : unsigned (2 downto 0);

        component multiplier_VHDL is
            port (
                clk : in std_logic;
                rst : in std_logic;
                ready : in bit;
                op : in unsigned (31 downto 0);
                done : out bit;
                eccezione_out : out unsigned (2 downto 0);
                result : out unsigned (31 downto 0)
                );
        end component multiplier_VHDL;

        component multiplier_verilog is
            port(
                clk : in std_logic;
                rst : in std_logic;
                ready : in bit;
                op : in unsigned (31 downto 0);
                done : out bit;
                eccezione_out : out unsigned (2 downto 0);
                result : out unsigned (31 downto 0)
            );
        end component multiplier_verilog;
begin

    multiplier_VHDL_1 : multiplier_VHDL port map (
        clk => clk,
        rst => rst,
        ready => ready,
        op => VHDL_in,
        done => done_VHDL,
        eccezione_out => eccezione_out_VHDL,
        result => VHDL_out
    );

    multiplier_verilog_1 : multiplier_verilog port map (
        clk => clk,
        rst => rst,
        ready => ready,
        op => verilog_in,
        done => done_verilog,
        eccezione_out => eccezione_out_verilog,
        result => verilog_out
    );

    process (current_state, ready, done_VHDL, done_verilog)
    -- FSM
    begin
        case current_state is
            when S0 =>
                if ready = '0' then
                    next_state <= S0;
                else
                    next_state <= S1;
                end if;
            when S1 =>
                if done_VHDL = '0' and done_verilog = '0' then
                    next_state <= S1;
                elsif done_VHDL = '1' and done_verilog = '1' then
                    next_state <= S2;
                elsif done_VHDL = '1' and done_verilog = '0' then
                    next_state <= S3;
                else
                    next_state <= S4;
                end if;
            when S2 =>
                next_state <= S5;
            when S3 =>
                if done_verilog = '0' then
                    next_state <= S6;
                else 
                    next_state <= S5;
                end if;
            when S4 =>
                if done_VHDL = '0' then
                    next_state <= S7;
                else
                    next_state <= S5;
                end if;
            when S5 =>
                next_state <= S8;
            when S6 =>
                if done_verilog = '0' then
                    next_state <= S6;
                else
                    next_state <= S5;
                end if;
            when S7 =>
                if done_VHDL = '0' then
                    next_state <= S7;
                else
                    next_state <= S5;
                end if;
            when S8 =>
                next_state <= S0;
        end case;
    end process;
  
    process (rst, clk)
    -- DATAPATH
    begin
        if rst = '1' then
            current_state <= S0;
        elsif clk'event and clk = '1' then
            current_state <= next_state;
            case next_state is
                when S0 =>
                    result <= (others => '0');
                    eccezione_out <= (others => '0');
                    done <= '0';
                when S1 =>
                    -- empty
                when S2 =>
                    -- empty
                when S3 =>
                    -- empty
                when S4 =>
                    -- empty
                when S5 =>
                    result <= VHDL_out;
                    eccezione_out <= eccezione_out_VHDL;
                    done <= '1';
                when S6 =>
                    -- empty
                when S7 =>
                    -- empty
                when S8 =>
                    result <= verilog_out;
                    eccezione_out <= eccezione_out_verilog;
            end case;
        end if;
    end process;
  
end architecture;