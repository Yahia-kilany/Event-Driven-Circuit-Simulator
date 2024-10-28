module TwoBitAdder(a1, a0, b1, b0, sum1, sum0, carry_out);
input a1;
input a0;
input b1;
input b0;
output sum1, sum0;
output carry_out;

wire carry0;
wire carry1;
wire sum_bit1;
wire sum_carry;

xor #(2) xor1(sum0, a0, b0);     
and #(3) and1(carry0, a0, b0);   

xor #(2) xor2(sum_bit1, a1, b1); 
and #(3) and2(carry1, a1, b1);   
xor #(2) xor3(sum1, sum_bit1, carry0); 
and #(3) and3(sum_carry, sum_bit1, carry0); 
or  #(4) or1(carry_out, carry1, sum_carry); 

endmodule