module majority_logic(output out, input a, b, c);
    wire ab, bc, ca;

    and u1(ab, a, b);   
    and u2(bc, b, c);   
    and u3(ca, c, a);   
    or u4(out, ab, bc, ca); 

    //This module outputs a 1 iff at least 2 of the inputs are 1s
endmodule
