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
	reg clk;
	reg RST;
	// Outputs
	wire [2:0] ALUOp, state_out;
	wire [4:0] rs;
	wire [4:0] rt;
	wire [4:0] rd;
	wire [5:0] opcode;
	wire [31:0] pc;
	wire [31:0] ins;
	wire [31:0] read_data1;
	wire [31:0] read_data2;
	wire [31:0] result;

	// Instantiate the Unit Under Test (UUT)
	CPU uut (
		.clk(clk), 
		.RST(RST),
		.ALUOp(ALUOp),
		.state_out(state_out),
		.opcode(opcode),
		.rs(rs),
		.rt(rt), 
		.rd(rd),
		.ins(ins),
		.read_data1(read_data1), 
		.read_data2(read_data2),
		.pc(pc),
		.result(result)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		RST = 1;
		// Wait 100 ns for global reset to finish
		#10;
		RST = 0;
        forever #10 clk = ~clk;
		// Add stimulus here
	end
      
endmodule
