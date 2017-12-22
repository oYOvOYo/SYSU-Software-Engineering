`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/23 10:39:02
// Design Name: 
// Module Name: Data_Selector3
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

module Data_Selector3(
    input [4:0] A, B, C,
    input [1:0] Sign,
    output reg [4:0] Y
    );
    always@(A or B or C or Sign) begin
        if(Sign == 2'b00) Y = A;
        else if(Sign == 2'b01) Y = B;
        else Y = C;    
    end
endmodule
