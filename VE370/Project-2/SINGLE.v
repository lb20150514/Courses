`ifndef SINGLE
`define SINGLE
`timescale 1ns / 1ps

`include "ALU.v"
`include "ALUctl.v"
`include "CTL.v"
`include "Data_Mem.v"
`include "Instruct_Mem.v"
`include "PC.v"
`include "Reg.v"
`include "SIGN_EX.v"

module SINGLE(CLK);
input wire CLK;

wire PCHold;
wire [31:0] PCin, PCout, PCadd4;

wire RegDst, Jump, Beq, Bne, MemRead, MemtoReg, ALUOp, MemWrite, ALUSrc, RegWrite, J;
wire [4:0] WR;
wire [31:0] Instruct, RD1, RD2, Jaddress, SEout, WD;

wire [1:0] ALUControl;
wire [31:0] shift32out, prebranch, ALUin2, address, zero;

wire [31:0] branch, RD;

assign PCadd4 = PCout + 4;

assign Jaddress = {PCadd4[31:28], {Instruct[25:0] << 2}};
assign WR = (RegDst) ? Instruct[20:16] : Instruct[15:11];

assign shift32out = SEout << 2;
assign prebranch = PCadd4 + shift32out;
assign ALUin2 = (ALUSrc) ? RD2 : SEout;

assign branch = ((Beq & zero) | (Bne & ~zero)) ? PCadd4 : prebranch;
assign PCin = (J) ? branch : Jaddress;
assign WD = (MemtoReg) ? address : RD;

pc PC(CLK, PCHold, PCin, PCout);
instruct_mem Instruct_Mem(PCout, Instruct);

control CTL(Instruct[31:26], RegDst, RegWrite, Beq, Bne, MemRead, MemtoReg, MemWrite, ALUOp, ALUSrc, J);
register Reg(CLK, RegWrite, Instruct[25:21], Instruct[20:16], WR, WD, RD1, RD2);
sign_extend SIGN_EX(SEout);

ALUcontrol ALUctl(ALUOp, Instruct[5:0], ALUControl);
ALUnit ALU(RD1, ALUin2, ALUControl, address, zero);

data_mem Data_Mem(CLK, MemWrite, MemRead, address, RD2, RD);


endmodule
`endif