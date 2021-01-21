`timescale 1ns / 1ps

module multiplier_verilog(
        input clk,
        input rst,
        input ready,
        input op,
        output done,
        output eccezione_out,
        output result
    );

    wire clk, rst, ready, done;
    wire [2:0] eccezione_out;
    wire [31:0] op, result;
    
    reg done_reg;
    reg [2:0] eccezione_out_reg;
    reg [31:0] result_reg;

    reg segno_op1, segno_op2, t1, t2, t3, t4, t5, t6;
    reg [2:0] eccezione;
    reg [4:0] counter;
    reg [5:0] current_state, next_state;
    reg [7:0] esponente_op1, esponente_op2;
    reg [8:0] t7, esponente;
    reg [23:0] mantissa_op1, mantissa_op2;
    reg [24:0] mantissa;
    reg [47:0] moltiplicando;
    reg [47:0] temp_mantissa;

    parameter S0=0, S1=1, S2=2, S3=3, S4=4, S5=5, S6=6, S7=7, S8=8, S9=9, S10=10, S11=11, S12=12, S13=13, S14=14, S15=15, S16=16, S17=17, S18=18, S19=19, S20=20, S21=21, S22=22, S23=23, S24=24, S25=25, S26=26, S27=27, S28=28, S29=29, S30=30, S31=31, S32=32, S33=33, S_Reset=34;

    assign done = done_reg;
    assign result = result_reg;
    assign eccezione_out = eccezione_out_reg;

    always @(ready, t1, t2, t3, t4, t5, t6, counter, mantissa_op2, temp_mantissa, esponente, mantissa, current_state)
    begin 
    // FSM
        case (current_state)
            S0: begin
                if (ready == 1'b0) 
                    next_state <= S0;
                else    
                    next_state <= S1;
            end
            S1: begin
               next_state <= S2; 
            end
            S2: begin
                next_state <= S3;
            end
            S3: begin
                if (t1 && t3)
                    next_state <= S4;
                else if (t2 && t4)
                    next_state <= S5;
                else if ((t1 && t4) || (t2 && t3))
                    next_state <= S6;
                else if ((t1 && !t3) || (t3 && !t1))
                    next_state <= S7;
                else if ((t2 && !t4) || (!t2 && t4))
                    next_state <= S8;
                else
                    next_state <= S9;
            end 
            S4: begin
                if (t5 && t6)
                    next_state <= S19;
                else    
                    next_state <= S10;
            end
            S5: begin
                if (t5 && t6)
                    next_state <= S19;
                else    
                    next_state <= S11;                    
            end
            S6: begin
                if (t5 && t6) 
                    next_state <= S12; 
                else if (!(t5 && t6))
                    next_state <= S13;
                else if ((! t5 && t1) || (!t6 && t3))
                    next_state <= S14;
                else
                    next_state <= S15;
            end
            S7: begin
                if (t5 && t6)
                    next_state <= S19;
                else
                    next_state <= S16;
            end
            S8: begin
               if (t5 && t6) 
                    next_state <= S19;
                else
                    next_state <= S17;
            end
            S9: begin
                next_state <= S20;
            end
            S10: begin
                next_state <= S18;
            end
            S11: begin
                next_state <= S18;
            end
            S12: begin
                next_state <= S18;
            end
            S13: begin
                next_state <= S18;
            end
            S14: begin
                next_state <= S18;
            end
            S15: begin
                next_state <= S18;
            end
            S16:begin
                next_state <= S18;
            end
            S17: begin
                next_state <= S18;
            end
            S18: begin
                next_state <= S0;
            end
            S19: begin
                next_state <= S0;
            end
            S20: begin
                if (counter < 24) 
                    next_state <= S21;
                else
                    next_state <= S24;
            end
            S21: begin
                if (mantissa_op2[counter] == 1'b1)
                    next_state <= S22;
                else
                    next_state <= S23;
            end
            S22: begin
                next_state <= S23;
            end
            S23: begin
                next_state <= S20;
            end
            S24: begin
                if (temp_mantissa[47] == 1'b1)
                    next_state <= S25;
                else
                    next_state <= S26;
            end
            S25: begin
                next_state <= S26;
            end
            S26: begin
                if (esponente[8] == 1'b1)
                    next_state <= S27;
                else
                    next_state <= S30;
            end
            S27: begin
                if (esponente[7] == 1'b0)
                    next_state <= S28;
                else
                    next_state <= S29;
            end
            S28: begin
                next_state <= S18;
            end
            S29: begin
                next_state <= S18;
            end
            S30: begin
                next_state <= S31;
            end
            S31: begin
                if (t4 || t5)
                    next_state <= S32;
                else
                    next_state <= S33;
            end
            S32: begin
                next_state <= S33;
            end
            S33: begin
                if (mantissa[24] == 1'b1)
                    next_state <= S25;
                else
                    next_state <= S19;
            end
            S_Reset: begin
                next_state <= S0;
            end
            default: begin
                next_state <= current_state;
            end
        endcase
    end

    always @(posedge clk, posedge rst)
    begin
        if (rst == 1'b1) 
            current_state <= S_Reset;
        else 
        begin
            current_state <= next_state;
            case (next_state)
                S0: begin
                    done_reg <= 1'b0;
                    mantissa <= 25'b0; 
                    moltiplicando <= 48'b0; 
                    temp_mantissa <= 48'b0;                 
                    counter <= 0;
                    mantissa_op1[23] <= 1'b1;
                    mantissa_op2[23] <= 1'b1;                    
                end
                S1: begin
                    segno_op1 <= op[31];
                    esponente_op1 <= op[30:23];
                    mantissa_op1[22:0] <= op[22:0];
                end
                S2: begin
                    segno_op2 <= op[31];
                    esponente_op2 <= op[30:23];
                    mantissa_op2[22:0] <= op[22:0];
                end
                S3: begin
                    t1 <= esponente_op1 == 8'h00;
                    t2 <= esponente_op1 == 8'hff;
                    t3 <= esponente_op2 == 8'h00;
                    t4 <= esponente_op2 == 8'hff;
                    t5 <= mantissa_op1[22:0] == 23'h0000;
                    t6 <= mantissa_op2[22:0] == 23'h0000;
                    t7 <= {1'b0, esponente_op1} + {1'b0, esponente_op2};
                end
                S4: begin
                    esponente <= 8'b0;
                end
                S5: begin
                    esponente <= 8'b1;
                end
                S6: begin
                    // empty
                end
                S7: begin
                    esponente <= 8'b0;
                end
                S8: begin
                    esponente <= 8'b1;
                end
                S9: begin
                    esponente <= t7 - 127;
                    moltiplicando[23:0] <= mantissa_op1;
                end
                S10: begin
                    eccezione <= 3'b010;
                end
                S11: begin
                    eccezione <= 3'b001;
                end
                S12: begin             
                    eccezione <= 3'b001;       
                end
                S13: begin             
                    eccezione <= 3'b011;       
                end
                S14: begin
                    eccezione <= 3'b010;
                end
                S15: begin             
                    eccezione <= 3'b001;       
                end
                S16: begin             
                    eccezione <= 3'b010;       
                end
                S17: begin             
                    eccezione <= 3'b001;       
                end
                S18: begin             
                    result_reg <= 32'b0;
                    done_reg <= 1'b1;
                    eccezione_out_reg <= eccezione;
                end
                S19: begin
                    result_reg <= {segno_op1 ^ segno_op2, esponente[7:0], mantissa[22:0]};
                    done_reg <= 1'b1;
                    eccezione_out_reg <= 3'b000;
                end
                S20: begin                
                    // empty    
                end
                S21: begin
                    // empty
                end
                S22: begin
                    temp_mantissa <= temp_mantissa + moltiplicando;
                end
                S23: begin
                    moltiplicando <= moltiplicando << 1;
                    counter <= counter + 1;
                end
                S24: begin
                    // empty
                end
                S25: begin
                    esponente <= esponente + 1;
                    temp_mantissa <= temp_mantissa >> 1;
                end
                S26: begin
                    mantissa <= temp_mantissa[47:23];
                end
                S27: begin
                    // empty
                end
                S28: begin
                    eccezione <= 3'b100;
                end
                S29: begin
                    eccezione <= 3'b101;
                end
                S30: begin
                    t1 <= temp_mantissa[23] == 1'b1;
                    t2 <= temp_mantissa[22] == 1'b1;
                    t3 <= temp_mantissa[21:0] == 23'h0000;
                end
                S31: begin
                    t4 <= t1 && t2 && t3;
                    t5 <= t2 && !t3;
                    temp_mantissa <= 48'b0;
                end
                S32: begin
                    mantissa <= mantissa + 1;
                end
                S33: begin
                    temp_mantissa[47:23] <= mantissa;
                end
                S_Reset: begin
                    result_reg <= 32'b0;
                    eccezione_out_reg <= 3'b0;
                end
            endcase
        end
    end
endmodule