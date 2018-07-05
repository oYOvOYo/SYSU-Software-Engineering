`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:02:34 03/19/2016 
// Design Name: 
// Module Name:    ControlUnit 
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
module CU(
    input [5:0] operationCode,
    input zero,
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
    output DBdataSrc,
    output [2:0] ALUop
    );
	wire [2:0] tempflag;
	wire addop, subop, oriop, andop, orop, moveop, swop, lwop, beop, haltop;
	// add is 000000
	assign addop  = ~operationCode[5] & ~operationCode[4] & ~operationCode[3] & ~operationCode[2] & ~operationCode[1] & ~operationCode[0];
	// addi is 000001
    assign addiop  = ~operationCode[5] & ~operationCode[4] & ~operationCode[3] & ~operationCode[2] & ~operationCode[1] & operationCode[0];
	//sub is 000010
	assign subop  =  ~operationCode[5] & ~operationCode[4] & ~operationCode[3] & ~operationCode[2] & operationCode[1] & ~operationCode[0];
	//ori is 010000
	assign oriop  =  ~operationCode[5] & operationCode[4] & ~operationCode[3] & ~operationCode[2] & ~operationCode[1] & ~operationCode[0];
	//and is 010001
	assign andop  =  ~operationCode[5] & operationCode[4] & ~operationCode[3] & ~operationCode[2] & ~operationCode[1] & operationCode[0];
	//or is 010010
	assign orop   =  ~operationCode[5] & operationCode[4] & ~operationCode[3] & ~operationCode[2] & operationCode[1] & ~operationCode[0];
	//sw is 100110
	assign swop   =   operationCode[5] & ~operationCode[4] & ~operationCode[3] & operationCode[2] & operationCode[1] & ~operationCode[0];
	//lw is 100111
	assign lwop   =   operationCode[5] & ~operationCode[4] & ~operationCode[3] & operationCode[2] & operationCode[1] & operationCode[0];
	//beq is 110000
	assign beqop  =   operationCode[5] & operationCode[4] & ~operationCode[3] & ~operationCode[2] & ~operationCode[1] & ~operationCode[0];
	//halt is 111111
	assign haltop =   operationCode[5] & operationCode[4] & operationCode[3] & operationCode[2] & operationCode[1] & operationCode[0];
	//sll is 011000
	assign sllop =   ~operationCode[5] & operationCode[4] & operationCode[3] & ~operationCode[2] & ~operationCode[1] & ~operationCode[0];
	
	//各输出信号的逻辑表达式
	assign ALUSrcB=addiop | oriop | swop | lwop;
	assign ALUSrcA=sllop;
	assign RegWre=addop | addiop | subop | andop | orop | oriop | sllop | lwop;
	assign InsMemRW=0;
	assign _RD=~lwop;
	assign _WR=~swop;
	assign ExtSel=addiop | lwop | swop | (beqop && ~zero);
	assign PCSrc=beqop && ~zero;
	assign RegDst= addop | subop | andop | orop | sllop;
	assign PCWre=~haltop;
	assign DBdataSrc=lwop;
	assign tempflag[2]=orop | andop | oriop | haltop; 
	assign tempflag[1]=sllop | beqop | haltop;
	assign tempflag[0]=subop | andop | sllop | haltop;
	assign ALUop=tempflag;
endmodule
