`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   16:22:59 03/19/2016
// Design Name:   Cpu
// Module Name:   F:/xilinx/SimpleCPU/CPU_tf.v
// Project Name:  SimpleCPU
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: Cpu
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module CPU_sim();

	// Inputs
	reg clock;
	reg reset;

	// Outputs
	wire ALUSrcB;
	wire ALUSrcA;
	wire RegWre;
	wire InsMemRW;
	wire _RD;
    wire _WR;
	wire ExtSel;
	wire PCSrc;
	wire RegDst;
	wire PCWre;
	wire zero;
	wire DBdataSrc;
	wire [2:0] ALUop;
	wire [4:0] rs;
	wire [4:0] rt;
	wire [4:0] rd;
	wire [4:0] sa;
	wire [31:0] PC_out;
	wire [31:0] PC;
	wire [31:0] instruction;
	wire [31:0] readData1;
	wire [31:0] readData2;
	wire [31:0] write_data;
	wire [31:0] result;
	wire [31:0] next;

	// Instantiate the Unit Under Test (UUT)
	CPU uut (
		.clock(clock), 
		.ALUSrcB(ALUSrcB),
		.ALUSrcA(ALUSrcA),
		.RegWre(RegWre),
		.InsMemRW(InsMemRW),
		._RD(_RD),
		._WR(_WR),
		.ExtSel(ExtSel), 
		.PCSrc(PCSrc), 
		.RegDst(RegDst), 
		.PCWre(PCWre), 
		.zero(zero), 
		.DBdataSrc(DBdataSrc),
		.ALUop(ALUop), 
		.rs(rs), 
		.rt(rt), 
		.rd(rd), 
		.sa(sa),
		.PC_out(PC_out), 
		.PC(PC), 
		.instruction(instruction), 
		.readData1(readData1), 
		.readData2(readData2), 
		.write_data(write_data),
		.result(result),
		.next(next)
	);

	initial begin
		// Initialize Inputs
		clock = 0;
		reset = 1;
		// Wait 100 ns for global reset to finish
		#10;
        forever #10 clock = ~clock;
		// Add stimulus here

	end
      
endmodule
