// This is module to implement a 2x1 Mux, later will be used to implement 8x1 Mux. 
module mux_2x1 (
    input a,      
    input b,       
    input sel,    //the selector 
    output y;      
);
    assign y = (sel) ? b : a;  
endmodule

// 8x1 Mux using the 2x1 Mux modules
module mux_8x1 (
    input [7:0] in,   // 8 inputs array
    input [2:0] sel,  // 3 select inputs array
    output y;         
);
    wire mux1_out, mux2_out, mux3_out, mux4_out, mux5_out, mux6_out; // wires because they will be used as inputs in other functions

    
    mux_2x1 mux1 (.a(in[0]), .b(in[1]), .sel(sel[0]), .y(mux1_out)); //selects between in[0] and in[1]
    mux_2x1 mux2 (.a(in[2]), .b(in[3]), .sel(sel[0]), .y(mux2_out)); //selects between in[2] and in[3]
    mux_2x1 mux3 (.a(in[4]), .b(in[5]), .sel(sel[0]), .y(mux3_out)); //selects between in[4] and in[5]
    mux_2x1 mux4 (.a(in[6]), .b(in[7]), .sel(sel[0]), .y(mux4_out)); //selects between in[6] and in[7]

    
    mux_2x1 mux5 (.a(mux1_out), .b(mux2_out), .sel(sel[1]), .y(mux5_out)); 
    mux_2x1 mux6 (.a(mux3_out), .b(mux4_out), .sel(sel[1]), .y(mux6_out)); 

    
    mux_2x1 mux7 (.a(mux5_out), .b(mux6_out), .sel(sel[2]), .y(y)); 

endmodule
