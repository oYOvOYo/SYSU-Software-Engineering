`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:16:46 03/19/2016 
// Design Name: 
// Module Name:    NextPc 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module NextPC(
    input [31:0] PC,
    input [31:0] immediate_32,
    input PCSrc,
    output [31:0] next
    );

   assign next = (PCSrc == 0) ? PC + 4 : PC + 4 + immediate_32 * 4 ;
endmodule
