`ifndef INSTRUCT_MEM
`define INSTRCT_MEM
`timescale 1ns / 1ps

module Instruct_Mem(IN, OUT);
input wire [31:0] IN;
output wire [31:0] OUT;

reg [31:0] mem [31:0];
integer i;

initial begin
for (i = 0; i < 32; i = i + 1)
    mem[i] = 32'b0;
end

assign OUT = mem[IN >> 2];
endmodule
`endif