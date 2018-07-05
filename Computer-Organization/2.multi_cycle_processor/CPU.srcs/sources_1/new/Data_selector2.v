`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/22 11:14:25
// Design Name: 
// Module Name: Data_selector2
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

module Data_Selector2(
    input [31:0] A, B,  
    input Sign,
    output reg [31:0] Y
    );
    always@(A or B or Sign) begin
        Y = Sign ? B : A; //选择信号为1则选A（前面的参数）
    end
endmodule 
