`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:02:34 03/19/2016 
// Design Name: 
// Module Name:    ControlUnit 
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
module CU(
    input [5:0] opcode,
    input zero, clk, RST,
    output reg ALUSrcB,
    output reg ALUSrcA,
    output reg [2:0] ALUOp,
    output reg IRWre,
    output reg InsMemRW,
    output reg _RD,
    output reg _WR,
    output reg DBdataSrc,
    output reg ExtSel,
    output reg [1:0] RegDst,
    output reg WrRegDSrc,
    output reg RegWre,
    output reg PCWre,
    output reg [1:0] PCSrc,
    output reg [2:0] state_out //多添加一个输出，并在顶层模块输出波形，便于分析实验结果和调试
    );
    //定义状态参数,增加代码可读性
	parameter [2:0] IF = 3'b000,
                      ID = 3'b001,
                    EXE1 = 3'b110,
                    EXE2 = 3'b101,
                    EXE3 = 3'b010,
                     MEM = 3'b011,  
                     WB1 = 3'b111,
                     WB2 = 3'b100;                            
    parameter [5:0] add = 6'b000000,
                      addi = 6'b000010,
                       sub = 6'b000001,
                        Or = 6'b010000,
                       ori = 6'b010010,
                       And = 6'b010001,
                       slt = 6'b100110,
                      slti = 6'b100111,  
                       sll = 6'b011000,
                        sw = 6'b110000,  
                        lw = 6'b110001,  
                       beq = 6'b110100,  
                         j = 6'b111000,  
                        jr = 6'b111001,  
                       jal = 6'b111010,
                      halt = 6'b111111;         
    reg [2:0] state, next_state;
    
    //相当于内含的D触发器，时钟下降沿到时切换状态
    always @(posedge clk) begin  
        if (RST) state <= IF;  
        else state <= next_state;
        state_out <= state;
    end
       
    //下一状态块   
    always @(state or opcode) begin  
        case(state)  
            IF: next_state = ID;  
            ID: begin  
                case (opcode[5:3]) //根据操作码前三位区分下一状态
                    3'b111: next_state = IF; //j, jal, jr, halt指令  
                    3'b110: begin
                        if (opcode == beq) next_state = EXE2; //beq指令  
                        else next_state = EXE3; //sw, lw指令  
                    end  
                    default: next_state = EXE1; //其他指令  
                endcase  
            end
            EXE1: next_state = WB1;  
            EXE2: next_state = IF;  
            EXE3: next_state = MEM;  
            MEM: begin  
                if (opcode == 6'b110001) next_state = WB2; //lw指令  
                else next_state = IF; //sw指令  
            end  
            WB1: next_state = IF;  
            WB2: next_state = IF;  
            default: next_state = IF;  
        endcase  
    end  
            
    //输出信号块，还是一个逻辑电路，只是在state变量发生改变的时候去更新这些信号的值           
    always @(state) begin 
        if (state == IF) begin
            if(opcode == halt) PCWre = 0;
            else PCWre = 1; //只有在取址阶段且非停机指令时PC才会改变
        end
        else PCWre = 0;
                  
        InsMemRW = 0; //不需要这个信号
           
        if (opcode == sll) ALUSrcA = 1; //只有位移指令SrcA需要从sa拿数据
        else ALUSrcA = 0;
                        
        if (opcode == addi || opcode == ori || opcode == slti || opcode == sw || opcode == lw) ALUSrcB = 1; //这些指令中SrcB取扩展后的立即数
        else ALUSrcB = 0;
           
        if (opcode == lw) DBdataSrc = 1; //lw指令下该信号表示取从MEM中取出的数据
        else DBdataSrc = 0;
                 
        if (state == WB1 || state == WB2 || opcode == jal) RegWre = 1; //在写回阶段或者jal指令时需要让寄存器接收写指令
        else RegWre = 0;
       
        if (opcode == jal) WrRegDSrc = 0; //只有jal指令时写回寄存器的数据取的是PC + 4
        else WrRegDSrc = 1;
       
        if (state == MEM && opcode == sw) _WR = 0; //sw和lw相关的读写信号，输出低电平表示有效
        else _WR = 1;  
        if (state == MEM && opcode == lw) _RD = 0;  
        else _RD = 1; 
       
        if (state == IF) IRWre = 1; //IR寄存器在IF阶段接到这个指令之后，等时钟上升沿的到来就从IRMRM中读出相关指令
        else IRWre = 0;
       
        if (opcode == ori) ExtSel = 0; //只有ori指令下做无符号扩展 
        else ExtSel = 1;
        
        if (opcode == jal) RegDst = 2'b00; //jal指令下寄存器写回的地址为$31内容
        else if (opcode == addi || opcode == ori || opcode == slti || opcode == lw) RegDst = 2'b01;  
        else RegDst = 2'b10;
              
        case(opcode) //如控制信号表中所示的四种情况
            j: PCSrc = 2'b11;  
            jal: PCSrc = 2'b11;  
            jr: PCSrc = 2'b10;  
            beq: begin  
                if (zero) PCSrc = 2'b01;  
                else PCSrc = 2'b00;  
            end  
            default: PCSrc = 2'b00;  
        endcase  
              
        case(opcode) //取决于不同指令对应的逻辑运算操作
            sub: ALUOp = 3'b001;  
            Or: ALUOp = 3'b101; 
            ori: ALUOp = 3'b101; 
            And: ALUOp = 3'b110;
            slt: ALUOp = 3'b010;  
            slti: ALUOp = 3'b010;
            sll: ALUOp = 3'b100;  
            beq: ALUOp = 3'b001;  
            default: ALUOp = 3'b000;
        endcase
        
        if (state == IF) begin // 防止在IF阶段写数据  
            RegWre = 0;
            _WR = 1;  
        end  
    end
    
endmodule
