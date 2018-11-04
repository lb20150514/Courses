`ifndef SIGN_EX
`define SIGN_EX
`timescale 1ns / 1ps

module SIGN_EX(IN, OUT);
input wire [15:0] IN;
output wire [31:0] OUT;
assign OUT = $signed(IN);
endmodule
`endif