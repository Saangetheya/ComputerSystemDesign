`timescale 1ns/1ps

// Written by CS20B053, CS20B051, CS20B054

module IF_ID_Buffer (
    input             clk,
    input             rst,
    input             StallD,
    input             FlushD,
    input      [31:0] instruction, // Current Instruction
    input      [31:0] PCF,         // Current Instruction Address
    input      [31:0] PCPlus4F,
    output reg [31:0] instrD, 
    output reg [31:0] PCD,
    output reg [31:0] PCPlus4D
);
    always @(posedge clk) begin
        if (rst) begin
           instrD    <= 32'd0;
            PCD      <= 32'd0;
            PCPlus4D <= 32'd0;
        end
        else if (StallD) begin
            instrD   <= instrD;
            PCD      <= PCD;
            PCPlus4D <= PCPlus4D;
        end
        else if (FlushD) begin
            instrD   <= 32'd0;
            PCD      <= 32'd0;
            PCPlus4D <= 32'd0;
        end
        else begin
            instrD   <= instruction;
            PCD      <= PCF;
            PCPlus4D <= PCPlus4F;
        end
        
    end
    
endmodule