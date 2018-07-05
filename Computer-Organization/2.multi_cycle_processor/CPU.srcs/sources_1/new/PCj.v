`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/22 10:50:15
// Design Name: 
// Module Name: PCj
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

module PCj(
    input [25:0] immediate,
    input [3:0] PC4,
    output reg [31:0] pcj
    );
    always @(immediate or PC4) pcj = {PC4, immediate, 2'b00};
endmodule
