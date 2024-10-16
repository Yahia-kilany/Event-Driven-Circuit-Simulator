module mux_4to1(output out, input i0, i1, i2, i3, input s1, s0);
    wire not_s1, not_s0;
    wire and0, and1, and2, and3;

    // Inverting select lines
    not u1(not_s1, s1);
    not u2(not_s0, s0);

    
    and u3(and0, i0, not_s1, not_s0);  // i0 is selected when s1 = 0 and s0 = 0
    and u4(and1, i1, not_s1, s0);      // i1 is selected when s1 = 0 and s0 = 1
    and u5(and2, i2, s1, not_s0);      // i2 is selected when s1 = 1 and s0 = 0
    and u6(and3, i3, s1, s0);          // i3 is selected when s1 = 1 and s0 = 1

    
    or u7(out, and0, and1, and2, and3);
endmodule
