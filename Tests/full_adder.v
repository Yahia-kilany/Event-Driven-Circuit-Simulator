module full_adder(output sum, carry_out, input a, b, carry_in);
    wire xor1, and1, and2;

    // Full adder logic using XOR and AND gates
    xor u1(xor1, a, b);             
    xor u2(sum, xor1, carry_in);   
    and u3(and1, a, b);            
    and u4(and2, xor1, carry_in);  
    or  u5(carry_out, and1, and2);  
endmodule
