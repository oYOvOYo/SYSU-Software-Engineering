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

/*module RAM(
     input clk,
	 input [31:0] address,
	 input [31:0] writeData, // [31:24], [23:16], [15:8], [7:0]
	 input _WR,
	 input _RD,
	 input DBdataSrc,
	 output [31:0] Dataout
     );
	 reg [7:0] RAM [0:60];
	 
	 //读数的时候需要有Dataout，写的时候这个输出无所谓
     if(DBdataSrc && ~_RD) begin
        assign Dataout[7:0]   = RAM[address + 3];
        assign Dataout[15:8]  = RAM[address + 2];
        assign Dataout[23:16] = RAM[address + 1];
        assign Dataout[31:24] = RAM[address];
    end
    else assign Dataout = address;

	always@( negedge clk ) begin  
		if(!_WR) begin	
		    RAM[address]   <= writeData[31:24]; //大端规则，高位在前
		    RAM[address+1] <= writeData[23:16];
			RAM[address+2] <= writeData[15:8];
			RAM[address+3] <= writeData[7:0];
		end
	 end
endmodule*/

module RAM(
    input clock,
    input [31:0] result,
    input [31:0] readData2,
    input _WR,
    input _RD,
    input DBdataSrc,
    output [31:0] write_data
    );

	reg [7:0] DataMem [0:60];
	reg [31:0] DataOut;
	
	initial begin
	   //Mem[8:11]初始化为5
	   DataMem[8]  = 8'b00000000;
	   DataMem[9]  = 8'b00000000;
	   DataMem[10] = 8'b00000000;
	   DataMem[11] = 8'b00000101;
	end
	
	always@ ( _RD or result) begin
	    if(!_RD) begin
            DataOut[7:0]   = DataMem[result + 3];
            DataOut[15:8]  = DataMem[result + 2];
            DataOut[23:16] = DataMem[result + 1];
            DataOut[31:24] = DataMem[result];
        end
    end
	
	always@ ( negedge clock ) begin
		if(!_WR) begin	
            DataMem[result]   <= readData2[31:24]; //大端规则，高位在前
            DataMem[result+1] <= readData2[23:16];
            DataMem[result+2] <= readData2[15:8];
            DataMem[result+3] <= readData2[7:0];
        end
	end
   
    assign write_data = ( DBdataSrc == 0 )? result : DataOut;

endmodule


