`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/22 11:27:38
// Design Name: 
// Module Name: Reg
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

module Reg(
    input [31:0] i_data,  
    input clk, Sign,
    output reg [31:0] o_data
    );  
    always @(posedge clk) begin
        if(Sign) o_data <= i_data;
    end
endmodule
