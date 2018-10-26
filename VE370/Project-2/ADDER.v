`timescale 1ns / 1ps

module ADDER(IN1, IN2, OUT);
input wire [31:0] IN1, IN2;
output wire OUT;

assign OUT = IN1 + IN2;
endmodule
