`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/04/14 09:35:12
// Design Name: 
// Module Name: RAM
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

module RAM(
    input _WR, _RD,
    input [31:0] DAddr,
    input [31:0] DataIn,
    output reg [31:0] DataOut
    );
	reg [7:0] DataMem [0:60];
	
	always@ (_RD or DAddr) begin //读
	    if(!_RD) begin
            DataOut[7:0]   = DataMem[DAddr + 3];
            DataOut[15:8]  = DataMem[DAddr + 2];
            DataOut[23:16] = DataMem[DAddr + 1];
            DataOut[31:24] = DataMem[DAddr];
        end
    end
	
	always@ (_WR or DAddr or DataIn) begin //写
		if(!_WR) begin	
            DataMem[DAddr]     = DataIn[31:24]; //大端规则，高位在前
            DataMem[DAddr + 1] = DataIn[23:16];
            DataMem[DAddr + 2] = DataIn[15:8];
            DataMem[DAddr + 3] = DataIn[7:0];
        end
	end

endmodule
