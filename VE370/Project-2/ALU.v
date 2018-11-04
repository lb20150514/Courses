`ifndef ALU
`define ALU
`timescale 1ns / 1ps

module ALU(IN1, IN2, CONTROL, OUT, ZERO);
input wire [31:0] IN1, IN2;
input wire [3:0] CONTROL;
output reg [31:0] OUT;
output wire ZERO;

always @(*) begin
case (CONTROL)
    (4'b0010): OUT = IN1 + IN2;     // add
    (4'b0110): OUT = IN1 - IN2;     // sub
    (4'b0000): OUT = IN1 & IN2;     // add
    (4'b0011): OUT = IN1 | IN2;     // or
    (4'b0100): OUT = IN1 < IN2;   // slt
    default: OUT = 0;
endcase
end

assign ZERO = (OUT == 0);
endmodule
`endif