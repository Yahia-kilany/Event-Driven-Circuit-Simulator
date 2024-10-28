module majority_logic(a, b, c, out);
input a;
input b;
input c;
output out;

wire ab;
wire bc;
wire ca;

and #(3) u1(ab, a, b);   
and #(3) u2(bc, b, c);   
and #(3) u3(ca, c, a);   
or #(4) u4(out, ab, bc, ca); 
endmodule