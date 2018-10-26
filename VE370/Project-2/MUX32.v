`timescale 1ns / 1ps

module MUX32(IN1, IN2, CONTROL, OUT);
input wire [31:0] IN1, IN2;
input wire CONTROL;
output wire [31:0] OUT;
    
assign OUT = CONTROL ? IN1 : IN2;
endmodule
