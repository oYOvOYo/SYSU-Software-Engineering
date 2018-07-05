`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:47:46 03/19/2016 
// Design Name: 
// Module Name:    InstructionSave 
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
module InsMem(
    input [31:0] PC,
    input InsMemRW,
    output [31:0] instruction
    );
    reg [7:0] InsMEM [127:0];
    
    initial begin
        $readmemb("D:/Ins.txt", InsMEM);
    end
	assign instruction = { InsMEM[PC], InsMEM[PC + 1], InsMEM[PC + 2], InsMEM[PC+ 3] };
	
endmodule
