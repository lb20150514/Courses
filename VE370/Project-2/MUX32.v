`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/10/20 18:02:49
// Design Name: 
// Module Name: MUX32
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module MUX32(IN1, IN2, CONTROL, OUT);
input wire [31:0] IN1, IN2;
input wire CONTROL;
output wire [31:0] OUT;
    
assign OUT = CONTROL ? IN1 : IN2;
endmodule
