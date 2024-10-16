module decoder_2to4 (
    input wire a0,    // Input bit 0
    input wire a1,    // Input bit 1
    output wire y0,   // Output for a = 00
    output wire y1,   // Output for a = 01
    output wire y2,   // Output for a = 10
    output wire y3    // Output for a = 11
);

    wire not_a0, not_a1;

    // NOT gates for the inputs
    not (not_a0, a0);
    not (not_a1, a1);

    // AND gates for the outputs
    and (y0, not_a1, not_a0); // y0 is high when a1 = 0, a0 = 0 (00)
    and (y1, not_a1, a0);     // y1 is high when a1 = 0, a0 = 1 (01)
    and (y2, a1, not_a0);     // y2 is high when a1 = 1, a0 = 0 (10)
    and (y3, a1, a0);         // y3 is high when a1 = 1, a0 = 1 (11)

endmodule
