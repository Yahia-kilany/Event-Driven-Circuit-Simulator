
module full_adder_1bit (
    input a,    
    input b,    
    input cin,  
    output sum, 
    output cout);

    assign {cout, sum} = a + b + cin; 
endmodule

module full_adder_4bit (
    input [3:0] a,    // 4-bit input a
    input [3:0] b,    // 4-bit input b
    input cin,        // Carry in
    output [3:0] sum, // 4-bit sum output
    output cout       // Carry out
);
    wire c1, c2, c3; 

    // Instantiate 1-bit full adders for each bit
    full_adder_1bit fa0 (.a(a[0]), .b(b[0]), .cin(cin), .sum(sum[0]), .cout(c1));
    full_adder_1bit fa1 (.a(a[1]), .b(b[1]), .cin(c1), .sum(sum[1]), .cout(c2));
    full_adder_1bit fa2 (.a(a[2]), .b(b[2]), .cin(c2), .sum(sum[2]), .cout(c3));
    full_adder_1bit fa3 (.a(a[3]), .b(b[3]), .cin(c3), .sum(sum[3]), .cout(cout));

endmodule
