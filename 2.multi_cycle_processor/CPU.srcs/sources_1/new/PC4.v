`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/22 10:35:48
// Design Name: 
// Module Name: PC4
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module PC4(
    input [31:0] i_pc,
    output reg [31:0] o_pc
    );
    always @(i_pc) o_pc = i_pc + 4;
endmodule
