module XnorNandNor (input A, B, C, output D); 
    wire w0, w1, w2, w3, w4;

    xnor(w0, A, B);      // w0 = A XNOR B
    buf(w1, w0);         // w1 = w0 to align the time between w1 and w3
    nand(w2, C, w1);     // w2 = C NAND w1
    not(w3, w2);         // w3 = NOT w2
    nor(D, w1, w3);      // D = w1 NOR w3
endmodule