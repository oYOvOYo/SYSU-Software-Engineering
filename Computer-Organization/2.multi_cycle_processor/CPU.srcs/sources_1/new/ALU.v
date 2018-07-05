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
    input [31:0] ALUSrcA,
    input [31:0] ALUSrcB,
    input [2:0] ALUop,
    output zero,
    output reg[31:0] result
    );
	 
    always@( ALUop or ALUSrcA or ALUSrcB) begin
		case( ALUop )
			3'b000: result = ALUSrcA + ALUSrcB;
			3'b001: result = ALUSrcA - ALUSrcB;
			3'b100: result = ALUSrcB << ALUSrcA;
			3'b101: result = ALUSrcA | ALUSrcB;
			3'b110: result = ALUSrcA & ALUSrcB;
			3'b111: result = ALUSrcA ^ ALUSrcB; //异或
			3'b011: result = (ALUSrcA < ALUSrcB) ? 1 : 0;
            3'b010: begin //有符号地比较A是否小于B
                if (ALUSrcA < ALUSrcB &&((ALUSrcA[31] == 0 && ALUSrcB[31]==0) || (ALUSrcA[31] == 1 && ALUSrcB[31]==1))) result = 1;
                else if (ALUSrcA[31] == 0 && ALUSrcB[31]==1)  result = 0;
                else if (ALUSrcA[31] == 1 && ALUSrcB[31]==0)  result = 1;
                else result = 0;
		    end
		endcase 
	end
	assign zero = (result == 0) ? 1 : 0;
endmodule
