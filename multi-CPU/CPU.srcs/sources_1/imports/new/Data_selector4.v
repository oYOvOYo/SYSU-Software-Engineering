`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/22 11:19:40
// Design Name: 
// Module Name: Data_selector3
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

module Data_Selector4(
    input [31:0] A, B, C, D,
    input [1:0] Sign,
    output reg [31:0] Y
    );
    always@(A or B or C or D or Sign) begin
        if(Sign == 2'b00) Y = A;
        else if(Sign == 2'b01) Y = B;
        else if(Sign == 2'b10) Y = C;
        else Y = D;
    end
endmodule
