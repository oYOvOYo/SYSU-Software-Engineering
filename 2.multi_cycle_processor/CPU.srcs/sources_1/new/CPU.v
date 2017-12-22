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
    input clk, RST,
    output wire [2:0] ALUOp, state_out,  
    output wire [5:0] opcode,  
    output wire [4:0] rs, rt, rd,  
    output wire [31:0] ins, read_data1, read_data2, pc, result
    );           
    assign opcode = ins[31:26];  
    assign rs = ins[25:21];
    assign rt = ins[20:16];  
    assign rd = ins[15:11];

    //命名上变量尽量用小写和下划线的组合，实例化的模块名保证首字母大写，不和模块定义的名字相同
    //数据通路
    wire [31:0] i_pc, pc4, pc1, pcj,
    write_reg, write_reg_data, out1, out2, alu_srca, alu_srcb,
    result1, o_IR, extendData, LateOut1, LateOut2, data_out;
    wire zero;

    //控制信号
    wire [1:0] ExtSel, RegOut, PCSrc, RegDst;
    wire PCWre, IRWre, InsMemRW, WrRegDSrc, RegWre, ALUSrcA, ALUSrcB, _WR, _RD, DBDataSrc;  

    PC Pc(clk, PCWre, RST, i_pc, pc);
    InsMem InsMem(pc, InsMemRW, ins);
    Reg IR(ins, clk, IRWre, o_IR);
    PC4 Pc4(pc, pc4);
    PC1 Pc1(pc4, extendData, pc1);
    PCj Pcj(ins[25:0], pc4[31:28], pcj);
    Data_Selector4 NextPc(pc4, pc1, read_data1, pcj, PCSrc, i_pc);
    Data_Selector3 WriteReg(5'b11111, rt, rd, RegDst, write_reg);
    Data_Selector2 WriteData(pc4, LateOut2, WrRegDSrc, write_reg_data);
    RegFile Regfile(clk, RegWre, rs, rt, write_reg, write_reg_data, read_data1, read_data2);
    Reg ADR(read_data1, clk, 1, out1);
    Reg BDR(read_data2, clk, 1, out2);
    Data_Selector2 AluSrcA(out1, {27'b000000000000000000000000000, ins[10:6]}, ALUSrcA, alu_srca);
    Data_Selector2 AluSrcB(out2, extendData, ALUSrcB, alu_srcb);
    ALU Alu(alu_srca, alu_srcb, ALUOp, zero, result);
    Extend EXtend(ins[15:0], ExtSel, extendData);
    Reg AluOutDR(result, clk, 1, result1);
    RAM Ram(_WR, _RD, result1, out2, data_out);
    Data_Selector2 Dbdatasrc(result, data_out, DBDataSrc, LateOut1);
    Reg DBDR(LateOut1, clk, 1, LateOut2);
    CU Cu(opcode, zero, clk, RST, ALUSrcB, ALUSrcA, ALUOp, IRWre, InsMemRW, _RD, _WR, DBDataSrc, ExtSel, RegDst, WrRegDSrc, RegWre, PCWre, PCSrc, state_out);

endmodule
