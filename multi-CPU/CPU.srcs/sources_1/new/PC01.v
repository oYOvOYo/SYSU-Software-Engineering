`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/22 10:47:19
// Design Name: 
// Module Name: PC01
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


module PC1(
    input [31:0] PC4,
    input [31:0] immediate,
    output reg [31:0] o_pc
    );
    always @(immediate or PC4) o_pc = PC4 + immediate * 4;
endmodule
