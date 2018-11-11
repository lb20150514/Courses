module Comparator(inData1 ,inData2 ,equalFlag);

input [31:0]  in1;
input [31:0]  in2;
output equal;

assign equal = (in1 == in2) ? 1'b1 : 1'b0;

endmodule
