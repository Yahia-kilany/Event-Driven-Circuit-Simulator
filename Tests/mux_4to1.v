module mux_4to1(i0, i1, i2, i3, s1, s0, out);
input i0;
input i1;
input i2;
input i3;
input s1;
input s0;
output out;

wire not_s1;
wire not_s0;
wire and0;
wire and1;
wire and2;
wire and3;

not #(2) u1(not_s1, s1);
not #(2) u2(not_s0, s0);

and #(3) u3(and0, i0, not_s1, not_s0);
and #(3) u4(and1, i1, not_s1, s0);     
and #(3) u5(and2, i2, s1, not_s0);      
and #(3) u6(and3, i3, s1, s0);         

// OR gate with delay
or #4 u7(out, and0, and1, and2, and3);
endmodule