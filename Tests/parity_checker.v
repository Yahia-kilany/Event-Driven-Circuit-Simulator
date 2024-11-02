
module parity_checker(a,b ,c ,d ,parity);
input a;
input b;
input c;
input d;
output parity;

wire xor1;
wire xor2;

xor #(20) u1(xor1,a,b);    
xor #(20) u2(xor2, xor1, c); 
xor #(20) u3(parity, xor2, d); 

endmodule
