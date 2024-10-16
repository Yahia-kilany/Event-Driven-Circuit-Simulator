module test_mux_8x1;

    reg [7:0] in;         // 8 inputs
    reg [2:0] sel;        // 3-bit select line
    wire y;               // Output

    // Instantiate the 8x1 MUX
    mux_8x1 uut (
        .in(in),
        .sel(sel),
        .y(y)
    );

    initial begin
        // Apply different test vectors
        in = 8'b10101010; // Test input pattern
        sel = 3'b000; #10; // Select in[0], expected y = in[0] = 1
        sel = 3'b001; #10; // Select in[1], expected y = in[1] = 0
        sel = 3'b010; #10; // Select in[2], expected y = in[2] = 1
        sel = 3'b011; #10; // Select in[3], expected y = in[3] = 0
        sel = 3'b100; #10; // Select in[4], expected y = in[4] = 1
        sel = 3'b101; #10; // Select in[5], expected y = in[5] = 0
        sel = 3'b110; #10; // Select in[6], expected y = in[6] = 1
        sel = 3'b111; #10; // Select in[7], expected y = in[7] = 0

        // Test with another input pattern
        in = 8'b11001100; // Change input pattern
        sel = 3'b000; #10; // Select in[0], expected y = in[0] = 0
        sel = 3'b001; #10; // Select in[1], expected y = in[1] = 0
        sel = 3'b010; #10; // Select in[2], expected y = in[2] = 1
        sel = 3'b011; #10; // Select in[3], expected y = in[3] = 1
        sel = 3'b100; #10; // Select in[4], expected y = in[4] = 0
        sel = 3'b101; #10; // Select in[5], expected y = in[5] = 0
        sel = 3'b110; #10; // Select in[6], expected y = in[6] = 1
        sel = 3'b111; #10; // Select in[7], expected y = in[7] = 1

        $finish;
    end

endmodule
