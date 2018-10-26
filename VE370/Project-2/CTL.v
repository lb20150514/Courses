`timescale 1ns / 1ps

module CTL(op, RegDst, Branch, MemRead, MemtoRead, ALUOp, MemWrite, ALUSrc, RegWrite, J);
input wire [5:0] op;
output reg RegDst, Branch, MemRead, MemtoRead, MemWrite, ALUSrc, RegWrite, J;
output reg [1:0] ALUOp;

always @(*) begin
case (op)
    (6'b000000):
    begin
        RegDst = 1'b1;
        Branch = 1'b0;
        MemRead = 1'b0;
        MemtoRead = 1'b0;
        MemWrite = 1'b0;
        ALUSrc = 1'b0;
        RegWrite = 1'b1;
        J = 1'b0;
        ALUOp = 2'b10;
    end
endcase
end
endmodule
