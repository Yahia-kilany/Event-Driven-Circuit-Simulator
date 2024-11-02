module XnorNandNor(A, B, C, D);
input A;
input B;
input C;
output D;

wire w0;
wire w1;
wire w2;
wire w3;

xnor #(30) u1(w0, A, B);     
buf  #(10) u2(w1, w0);        
nand #(20) u3(w2, C, w1);     
not  #(10) u4(w3, w2);        
nor  #(30) u5(D, w1, w3);     

endmodule