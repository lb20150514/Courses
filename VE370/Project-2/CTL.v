`timescale 1ns / 1ps

module CTL(op, RegDst, RegWrite, BranchEq, BranchNe, 
    MemRead, MemtoReg, MemWrite, ALUOp, ALUSrc, J);
input wire [5:0] op;
output reg RegDst, BranchEq, BranchNe, MemRead, MemtoReg, MemWrite, ALUSrc, RegWrite, J;
output reg [1:0] ALUOp;

initial begin
    RegDst = 1'b0;
    BranchEq = 1'b0;
    BranchNe = 1'b0;
    MemRead = 1'b0;
    MemtoReg = 1'b0;
    MemWrite = 1'b0;
    ALUSrc = 1'b0;
    RegWrite = 1'b0;
    J = 1'b0;
    ALUOp = 2'b00;
end

always @(op) begin
case (op)
    (6'b000000):            // R-type: add, sub, and, or, slt
    begin
        RegDst = 1'b1;
        BranchEq = 1'b0;
        BranchNe = 1'b0;
        MemRead = 1'b0;
        MemtoReg = 1'b0;
        MemWrite = 1'b0;
        ALUSrc = 1'b0;
        RegWrite = 1'b1;
        J = 1'b0;
        ALUOp = 2'b10;
    end
    (6'b001000):            // I-type: addi
    begin
        RegDst = 1'b0;
        BranchEq = 1'b0;
        BranchNe = 1'b0;
        MemRead = 1'b0;
        MemtoReg = 1'b0;
        MemWrite = 1'b0;
        ALUSrc = 1'b1;
        RegWrite = 1'b1;
        J = 1'b0;
        ALUOp = 2'b00;
    end
    (6'b001100):            // I-type: andi
    begin
        RegDst = 1'b0;
        BranchEq = 1'b0;
        MemRead = 1'b0;
        MemtoReg = 1'b0;
        MemWrite = 1'b0;
        ALUSrc = 1'b1;
        RegWrite = 1'b1;
        J = 1'b0;
        ALUOp = 2'b00;
    end
    (6'b100011):            // I-type: lw
    begin
        RegDst = 1'b0;
        BranchEq = 1'b0;
        BranchNe = 1'b0;
        MemRead = 1'b1;
        MemtoReg = 1'b0;
        MemWrite = 1'b0;
        ALUSrc = 1'b1;
        RegWrite = 1'b1;
        J = 1'b0;
        ALUOp = 2'b11;
    end
    (6'b101011):            // I-type: sw
    begin
        RegDst = 1'b0;
        BranchEq = 1'b0;
        BranchNe = 1'b0;
        MemRead = 1'b0;
        MemtoReg = 1'b0;
        MemWrite = 1'b1;
        ALUSrc = 1'b1;
        RegWrite = 1'b0;
        J = 1'b0;
        ALUOp = 2'b11;
    end
    (6'b000100):            // I-type: beq
    begin
        RegDst = 1'b1;
        BranchEq = 1'b1;
        BranchNe = 1'b0;
        MemRead = 1'b0;
        MemtoReg = 1'b0;
        MemWrite = 1'b0;
        ALUSrc = 1'b0;
        RegWrite = 1'b0;
        J = 1'b0;
        ALUOp = 2'b01;
    end
    (6'b000101):            // I-type: bne
    begin
        RegDst = 1'b1;
        BranchEq = 1'b0;
        BranchNe = 1'b1;
        MemRead = 1'b0;
        MemtoReg = 1'b0;
        MemWrite = 1'b0;
        ALUSrc = 1'b0;
        RegWrite = 1'b0;
        J = 1'b0;
        ALUOp = 2'b01;
    end
    (6'b000010):            // J-type: j
    begin
        RegDst = 1'b0;
        BranchEq = 1'b0;
        BranchNe = 1'b0;
        MemRead = 1'b0;
        MemtoReg = 1'b0;
        MemWrite = 1'b0;
        ALUSrc = 1'b0;
        RegWrite = 1'b0;
        J = 1'b1;
        ALUOp = 2'b00;
    end
    default:
    begin
        RegDst = 1'b0;
        BranchEq = 1'b0;
        BranchNe = 1'b0;
        MemRead = 1'b0;
        MemtoReg = 1'b0;
        MemWrite = 1'b0;
        ALUSrc = 1'b0;
        RegWrite = 1'b0;
        J = 1'b0;
        ALUOp = 2'b00;
    end
endcase
end
endmodule
