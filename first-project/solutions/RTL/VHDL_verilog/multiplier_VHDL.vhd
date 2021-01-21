package multiplier_pack_VHDL is    
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
    constant S13 : integer := 13;
    constant S14 : integer := 14;
    constant S15 : integer := 15;
    constant S16 : integer := 16;
    constant S17 : integer := 17;
    constant S18 : integer := 18;
    constant S19 : integer := 19;
    constant S20 : integer := 20;
    constant S21 : integer := 21;
    constant S22 : integer := 22;
    constant S23 : integer := 23;
    constant S24 : integer := 24;
    constant S25 : integer := 25;
    constant S26 : integer := 26;
    constant S27 : integer := 27;
    constant S28 : integer := 28;
    constant S29 : integer := 29;
    constant S30 : integer := 30;
    constant S31 : integer := 31;
    constant S32 : integer := 32;
    constant S33 : integer := 33;
    constant S_Reset : integer := 34;
    constant DOUBLE_MANTISSA : integer := 48;
    constant MANTISSA : integer := 23;
    constant ESPONENTE : integer := 8;
end multiplier_pack_VHDL;

LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE WORK.multiplier_pack_VHDL.ALL;
USE IEEE.NUMERIC_BIT.ALL;

entity multiplier_VHDL is
    port (
        clk : in bit;
        rst : in bit;
        ready : in bit;
        op : in unsigned (31 downto 0);
        done : out bit;
        eccezione_out : out unsigned (2 downto 0);
        result : out unsigned (31 downto 0)
    );
end multiplier_VHDL;

architecture multiplier_architecture of multiplier_VHDL is
    subtype STATE is integer range 0 to 34;

    signal mantissa_op1, mantissa_op2 : unsigned (MANTISSA downto 0);
    signal segno_op1, segno_op2 : bit;
    signal esponente_op1, esponente_op2 : unsigned (ESPONENTE - 1 downto 0);
    signal temp_mantissa : unsigned (DOUBLE_MANTISSA - 1 downto 0);
    signal mantissa : unsigned (MANTISSA + 1 downto 0);   
    signal t7, esponente : unsigned (ESPONENTE downto 0) ;
    signal t1, t2, t3, t4, t5, t6 : boolean;
    signal current_state, next_state : STATE;
    signal eccezione : unsigned ( 2 downto 0);
    signal moltiplicando : unsigned (DOUBLE_MANTISSA - 1 downto 0);
    signal counter : integer;

begin
    process (ready, t1, t2, t3, t4, t5, t6, counter, mantissa_op2, temp_mantissa, esponente, mantissa, current_state)
        --FSM
    begin
        case current_state is
            when S0 =>
                if ready = '0' then
                    next_state <= S0;
                else 
                    next_state <= S1;
                end if;
            when S1 =>
                next_state <= S2;
            when S2 =>
                next_state <= S3;
            when S3 =>
                if t1 and t3 then    
                    next_state <= S4;
                elsif t2 and t4 then
                    next_state <= S5;
                elsif (t1 and t4) or (t2 and t3) then
                    next_state <= S6;
                elsif (t1 and not t3) or (t3 and not t1) then
                    next_state <= S7;
                elsif (t2 and not t4) or (not t2 and t4) then
                    next_state <= S8;
                else 
                    next_state <= S9;
                end if;
            when S4 =>
                if t5 and t6 then
                    next_state <= S19;
                else 
                    next_state <= S10;
                end if;
            when S5 =>
                if t5 and t6 then
                    next_state <= S19;
                else 
                    next_state <= S11;
                end if;
            when S6 =>
                if t5 and t6 then
                    next_state <= S12;
                elsif t5 nand t6 then
                    next_state <= S13;
                elsif (not t5 and t1) or (not t6 and t3) then
                    next_state <= S14;
                else
                    next_state <= S15;
                end if;
            when S7 =>
                if t5 and t6 then
                    next_state <= S19;
                else 
                    next_state <= S16;
                end if;
            when S8 =>
                if t5 and t6 then
                    next_state <= S19;
                else 
                    next_state <= S17;
                end if;
            when S9 =>
                next_state <= S20;
            when S10 =>
                next_state <= S18;
            when S11 =>
                next_state <= S18;
            when S12 =>
                next_state <= S18;            
            when S13 =>
                next_state <= S18;
            when S14 =>
                next_state <= S18;
            when S15 =>
                next_state <= S18;
            when S16 =>
                next_state <= S18;
            when S17 =>
                next_state <= S18;
            when S18 =>
                next_state <= S0;
            when S19 =>
                next_state <= S0;
            when S20 =>
                if counter < 24 then
                    next_state <= S21;
                else
                    next_state <= S24;
                end if;
            when S21 =>
                if mantissa_op2(counter) = '1' then
                    next_state <= S22;
                else
                    next_state <= S23;
                end if;
            when S22 =>
                next_state <= S23;
            when S23 =>
                next_state <= S20;
            when S24 =>
                if temp_mantissa(47) = '1' then
                    next_state <= S25;
                else
                    next_state <= S26;
                end if;
            when S25 =>
                next_state <= S26;
            when S26 =>
                if esponente(8) = '1' then
                    next_state <= S27;
                else
                    next_state <= S30;
                end if;
            when S27 =>
                if esponente(7) = '0' then
                    next_state <= S28;
                else 
                    next_state <= S29;
                end if;
            when S28 =>
                next_state <= S18;
            when S29 =>
                next_state <= S18;
            when S30 =>
                next_state <= S31;
            when S31 =>
                if t4 or t5 then
                    next_state <= S32;
                else
                    next_state <= S33;
                end if;
            when S32 =>
                next_state <= S33;
            when S33 =>
                if mantissa(24) = '1' then
                    next_state <= S25;
                else
                    next_state <= S19;
                end if;
            when S_Reset =>
                next_state <= S0;
            when others =>
                next_state <= current_state;
        end case;
    end process;

    process (clk, rst)
    -- DATAPATH
    begin
        if rst = '1' then
            current_state <= S_Reset;
        elsif clk'event and clk = '1' then
            current_state <= next_state;
            case next_state is
                when S0 =>
                    done <= '0';
                    mantissa <= (others => '0');
                    moltiplicando <= (others => '0');
                    temp_mantissa <= (others => '0');
                    counter <= 0;
                    mantissa_op1(23) <= '1';
                    mantissa_op2(23) <= '1';
                when S1 =>
                    segno_op1 <= op(31);
                    esponente_op1 <= op(30 downto 23);
                    mantissa_op1(22 downto 0) <= op(22 downto 0);
                when S2 =>
                    segno_op2 <= op(31);
                    esponente_op2 <= op(30 downto 23);
                    mantissa_op2(22 downto 0) <= op(22 downto 0);
                when S3 =>
                    t1 <= esponente_op1 = 0;
                    t2 <= esponente_op1 = 255;
                    t3 <= esponente_op2 = 0;
                    t4 <= esponente_op2 = 255;
                    t5 <= mantissa_op1(22 downto 0) = 0;
                    t6 <= mantissa_op2(22 downto 0) = 0;
                    t7 <= ('0' & esponente_op1) + ('0' & esponente_op2);
                when S4 =>
                    esponente <= (others => '0');
                when S5 =>
                    esponente <= (others => '1');
                when S6 =>
                    -- empty
                when S7 =>
                    esponente <= (others => '0');
                when S8 =>
                    esponente <= (others => '1');
                when S9 =>
                    esponente <= t7 - 127;
                    moltiplicando(23 downto 0) <= mantissa_op1;
                when S10 =>
                    eccezione <= ('0','1','0');
                when S11 =>
                    eccezione <= ('0','0','1');
                when S12 =>
                    eccezione <= ('0','0','1');
                when S13 =>
                    eccezione <= ('0','1','1');
                when S14 =>
                    eccezione <= ('0','1','0');
                when S15 =>
                    eccezione <= ('0','0','1');
                when S16 =>
                    eccezione <= ('0','1','0');
                when S17 =>
                    eccezione <= ('0','0','1');
                when S18 =>
                    result <= (others => '0');
                    done <= '1';
                    eccezione_out <= eccezione;
                when S19 =>
                    result <= ((segno_op1 xor segno_op2) & (esponente(7 downto 0)) & (mantissa(22 downto 0)));
                    done <= '1';
                    eccezione_out <= ('0','0','0');
                when S20 =>
                    -- empty
                when S21 =>
                    -- empty
                when S22 =>
                    temp_mantissa <= temp_mantissa + moltiplicando;
                when S23 =>
                    moltiplicando <= moltiplicando sll 1;
                    counter <= counter + 1;
                when S24 =>
                    -- empty
                when S25 =>
                    esponente <= esponente + 1;
                    temp_mantissa <= temp_mantissa srl 1;
                when S26 =>
                    mantissa <= temp_mantissa(47 downto 23);
                when S27 =>
                    -- empty
                when S28 =>
                    eccezione <= ('1','0','0');
                when S29 =>
                    eccezione <= ('1','0','1');
                when S30 =>
                    t1 <= temp_mantissa(23) = '1';
                    t2 <= temp_mantissa(22) = '1';
                    t3 <= temp_mantissa(21 downto 0) = 0;
                when S31 =>
                    t4 <= t1 and t2 and t3;
                    t5 <= t2 and not t3;
                    temp_mantissa <= (others => '0');
                when S32 =>
                    mantissa <= mantissa + 1;
                when S33 =>
                    temp_mantissa(47 downto 23) <= mantissa;
                when S_Reset =>
                    result <= (others => '0');
                    eccezione_out <= (others => '0');
            end case;
        end if;
    end process;
end multiplier_architecture;