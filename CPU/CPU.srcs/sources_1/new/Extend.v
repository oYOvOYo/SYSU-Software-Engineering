`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:07:30 03/19/2016 
// Design Name: 
// Module Name:    Extend 
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
module Extend(
    input [15:0] immediate_16,
    input ExtSel,
    output reg[31:0] immediate_32
    );

   always@( immediate_16 or ExtSel ) begin
	if ( ExtSel == 0 )
		immediate_32 = { 16'h0000, immediate_16 };
	else if (immediate_16[15] == 1 )
		immediate_32 = { 16'hffff, immediate_16 };
	else
		immediate_32 = { 16'h0000, immediate_16 };
	end
endmodule
