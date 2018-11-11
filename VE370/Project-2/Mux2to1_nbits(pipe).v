module Mux2x1_nBits(out, in1, in2, sel);

input [n-1:0] in1, in2; 
input sel;
output [n-1:0] out; 

assign out = 	(sel == 1'b0) ? in1 :
	        (sel == 1'b1) ? in2 : n'bx;

endmodule
