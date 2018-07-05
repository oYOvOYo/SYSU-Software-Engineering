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
module PC(
    input clk, PCWre, RST,
    input [31:0] i_pc,
    output reg [31:0] o_pc
    );
    always @(negedge clk) begin //当pcWre改变的时候或者RST改变的时候再检测
        if(RST) o_pc <= 0;
        else if(PCWre) o_pc <= i_pc;
    end
endmodule