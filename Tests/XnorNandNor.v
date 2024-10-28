module XnorNandNor(A, B, C, D);
input A;
input B;
input C;
output D;

wire w0;
wire w1;
wire w2;
wire w3;

xnor #(3) u1(w0, A, B);     
buf  #(1) u2(w1, w0);        
nand #(2) u3(w2, C, w1);     
not  #(1) u4(w3, w2);        
nor  #(3) u5(D, w1, w3);     

endmodule