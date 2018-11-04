`ifndef REG
`define REG
`timescale 1ns / 1ps

module Reg(CLK, RegWrite, ReadReg1, ReadReg2, WriteReg, WriteData, ReadData1, ReadData2);
input wire CLK, RegWrite;
input wire [4:0] ReadReg1, ReadReg2, WriteReg;
output [31:0] ReadData1, ReadData2, WriteData;

reg [31:0] regs [0:31];
integer i;

initial begin
    for (i = 0; i < 32; i = i + 1)
        regs[i] = 32'b0;
end

assign ReadData1 = regs[ReadReg1];
assign ReadData2 = regs[ReadReg2];

always @ (posedge CLK)
begin
    if (RegWrite)
        regs[WriteReg] = WriteData;
end
endmodule
`endif