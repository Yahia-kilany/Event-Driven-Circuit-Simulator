
module test_full_adder_4bit;

    reg [3:0] a, b;  // 4-bit inputs
    reg cin;         // Carry in
    wire [3:0] sum;  // Sum output
    wire cout;       // Carry out

    // Instantiate the 4-bit full adder
    full_adder_4bit uut (
        .a(a),
        .b(b),
        .cin(cin),
        .sum(sum),
        .cout(cout)
    );

    initial begin
        // Apply test cases
        a = 4'b0001; b = 4'b0010; cin = 0; #10; // a = 1, b = 2 -> sum = 3
        a = 4'b1111; b = 4'b0001; cin = 0; #10; // a = 15, b = 1 -> sum = 16 (carry = 1)
        a = 4'b0101; b = 4'b1010; cin = 1; #10; // a = 5, b = 10, carry = 1 -> sum = 16

        $finish;
    end

endmodule
