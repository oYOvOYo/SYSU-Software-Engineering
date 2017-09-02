`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/04/10 12:14:17
// Design Name: 
// Module Name: Regfile
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

module Regfile(
    input clock,
    input RegWre,
    input RegDst,
    input [4:0] rs,
    input [4:0] rt,
    input [4:0] rd,
    input [31:0] write_data,
    output [31:0] readData1,
    output [31:0] readData2
    );
	reg [31:0] register [0:31];
    wire [4:0] rin;
    initial begin
        register[0] = 0; //0号寄存器的值始终为0并且不允许改变
    end
    
    assign rin = ( RegDst == 0 )? rt : rd;

	assign readData1 = (rs== 0)? 0 : register[rs];
	assign readData2 = (rt== 0)? 0 : register[rt];

	always @(posedge clock) begin
		if ( (rin != 0) & (RegWre == 1) )
            register[rin] <= write_data;
    end

endmodule
