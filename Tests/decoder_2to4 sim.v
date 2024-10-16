module test_decoder_2to4;

    reg a0, a1;         // 2-bit input as two separate bits
    wire y0, y1, y2, y3; // 4 outputs

    // Instantiate the 2-to-4 decoder
    decoder_2to4 uut (
        .a0(a0),
        .a1(a1),
        .y0(y0),
        .y1(y1),
        .y2(y2),
        .y3(y3)
    );

    initial begin
        // Apply test cases
        a0 = 0; a1 = 0; #10; // Expected y0 = 1, y1 = 0, y2 = 0, y3 = 0
        a0 = 1; a1 = 0; #10; // Expected y0 = 0, y1 = 1, y2 = 0, y3 = 0
        a0 = 0; a1 = 1; #10; // Expected y0 = 0, y1 = 0, y2 = 1, y3 = 0
        a0 = 1; a1 = 1; #10; // Expected y0 = 0, y1 = 0, y2 = 0, y3 = 1

        $finish;
    end

endmodule
