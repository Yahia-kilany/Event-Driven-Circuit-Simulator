module parity_checker(output parity, input a, b, c, d);
    wire xor1, xor2, xor3;

    
    xor u1( xor1, a, b);    
    xor u2( xor2, xor1, c); 
    xor u3( parity, xor2, d); 

    //This Func chechs if the number of 1s in a binary seq. is even or odd. Output is 1 if even, 0 if odd.
    
endmodule
