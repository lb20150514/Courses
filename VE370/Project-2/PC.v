`ifndef PC
`define PC
`timescale 1ns / 1ps

module PC(CLK, PCHold, IN, OUT);
input wire CLK, PCHold;
input wire [31:0] IN;
output reg [31:0] OUT;

initial begin
    OUT = 32'b0;
end

always @(posedge CLK) begin
    if (PCHold)
        OUT = IN;
end
endmodule
`endif
