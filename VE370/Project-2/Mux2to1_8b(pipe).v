module Mux2x1_8Bits(out, in1, in2, sel);

input [7:0] in1, in2; 
input sel;
output [7:0] out; 

assign out = 	(sel == 1'b0) ? in1 :
		(sel == 1'b1) ? in2 : 8'bx;

endmodule
