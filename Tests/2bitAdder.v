module TwoBitAdder(
    input a1, a0, //first 2-bit binary number
    input b1, b0, //second 2-bit binary number
    output sum1, sum0, // 2-bit sum output
    output carry_out // Carry out signal
);
    wire carry0, carry1, sum_bit0, sum_bit1, sum_carry;

    // First bit addition (LSB)
    xor (sum0, a0, b0);       // Calculate the sum of the LSBs
    and (carry0, a0, b0);     // Generate carry from the LSB addition

    // Second bit addition (MSB)
    xor (sum_bit1, a1, b1);   // Calculate the sum of the MSBs without the carry-in
    and (carry1, a1, b1);     // Calculate carry from the MSBs without carry-in
    xor (sum1, sum_bit1, carry0); // Calculate the sum of the MSBs including the carry-in from the LSB
    and (sum_carry, sum_bit1, carry0); // Calculate carry from MSBs considering the carry-in
    or  (carry_out, carry1, sum_carry); // Calculate the final carry-out signal

endmodule