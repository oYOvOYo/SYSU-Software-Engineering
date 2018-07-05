`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:40:41 03/19/2016 
// Design Name: 
// Module Name:    PC 
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
module PC( clk, reset, PCWre, nextPC, curPC);
    input clk, reset, PCWre;    // clk为时钟信号；reset为重置信号；PCWre为PC使能信号
    input [31:0] nextPC;        // nextPC为下个PC值
    output reg [31:0] curPC;   // 当前PC值

	// 上升沿触发
    always@(posedge clk) begin
        if( reset == 0)
            curPC <= 0;  // PC初值为0, 从0地址开始
        else if (PCWre)
			curPC = nextPC;  // 下条指令的地址
    end
endmodule