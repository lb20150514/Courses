`ifndef DATA_MEM
`define DATA_MEM
`timescale 1ns / 1ps

module Data_Mem(CLK, MemWrite, MemRead, Address, WriteData, ReadData);
input wire CLK, MemWrite, MemRead;
input wire [31:0] Address, WriteData;
output [31:0] ReadData;

reg [31:0] data [0:127];
integer i;

initial begin
    for (i = 0; i < 128; i = i + 1)
        data[i] = 32'b0; 
end

assign ReadData = (MemRead) ? data[Address] : 32'b0;

always @(posedge CLK)
begin
    if (MemWrite)
        data[Address] = WriteData;
end
endmodule
`endif