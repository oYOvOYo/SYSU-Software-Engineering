`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:52:05 03/19/2016 
// Design Name: 
// Module Name:    Cpu 
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
module CPU(
    input clock,
    output ALUSrcB,
    output ALUSrcA,
    output RegWre,
    output InsMemRW,
    output _RD,
    output _WR,
    output ExtSel,
    output PCSrc,
    output RegDst,
    output PCWre,
    output zero,
    output DBdataSrc,
    output [2:0] ALUop,
    output [4:0] rs,
    output [4:0] rt,
    output [4:0] rd,
    output [4:0] sa,
    output reg[31:0] PC_out,  //对应nextPC，在PC模块对应输入
    output [31:0] PC,         //对应curPC,在PC模块做输出
    output [31:0] instruction,
    output [31:0] readData1,
    output [31:0] readData2,
    output [31:0] write_data,
    output [31:0] result,
    output [31:0] DataOut,
    output [31:0] next
    );

	reg reset;
	 
	wire [5:0] operationCode;
	wire [15:0] immediate_16;
	wire [31:0] immediate_32;
	
	initial begin
		PC_out = 32'h00000000;
		reset = 0;
		#40 reset = 1;
	end
	PC pc(clock, reset, PCWre, PC_out, PC);
	InsMem insmem(PC, InsMemRW, instruction);
	//从指令中切分出rs、rd等参数
	assign operationCode = instruction[31:26];
	assign rs = instruction[25:21];
	assign rt = instruction[20:16];
	assign rd = instruction[15:11];
	assign sa = instruction[10:6];
	assign immediate_16 = instruction[15:0];
	CU cu(operationCode, zero, ALUSrcB, ALUSrcA, RegWre, InsMemRW, _RD, _WR, ExtSel, PCSrc, RegDst, PCWre, DBdataSrc, ALUop);
	Regfile regfile(clock, RegWre, RegDst, rs, rt, rd, write_data, readData1, readData2);
	Extend extend(immediate_16, ExtSel, immediate_32);
	ALU alu(readData1, readData2, immediate_32, sa, ALUSrcB, ALUSrcA, ALUop, zero, result);
	RAM ram(clock, result, readData2, _WR, _RD, DBdataSrc, write_data);
	NextPC nextpc(PC, immediate_32, PCSrc, next);
	always@(*) begin
		PC_out = next;
	end

endmodule
