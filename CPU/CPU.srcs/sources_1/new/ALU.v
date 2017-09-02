`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:28:59 03/19/2016 
// Design Name: 
// Module Name:    ALU 
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
//readData1, readData2, immediate_32, sa, ALUSrcB, ALUSrcA, ALUop, zero, result
module ALU(
    input [31:0] readData1,
    input [31:0] readData2,
    input [31:0] immediate_32,
    input [4:0] sa,
    input ALUSrcB,
    input ALUSrcA,
    input [2:0] ALUop,
    output zero,
    output reg[31:0] result
    );
	 
    wire [31:0] alub;
    assign alub = ( ALUSrcB == 0 )? readData2 : immediate_32;
	 
    always@( sa or readData1 or alub or ALUop ) begin
	    //$display("flag: %d", ALUFlag);
		case( ALUop )
			3'b000: begin
				result = readData1 + alub;
				//$display("add");
			end
			3'b001: begin
				result = readData1 - alub;
				//$display("sub");
			end
			3'b100: begin
				result = readData1 | alub;
				//$display("or");
			end
			3'b101: begin
				result = readData1 & alub;
				//$display("and");
			end
			3'b011 : result = alub << sa;
            3'b010 : result = (readData1 == alub) ? 1 : 0; //相等zero会输出0 
		endcase 
	end
	assign zero = (result == 0) ? 1 : 0;
	 
endmodule
