`timescale 1ns/1ps

module pipeline_tb ();
    reg clk;
    reg rst;
    wire [31:0] checkx2;
    wire [31:0] checkx1;
    wire [31:0] checkx3;
    wire [31:0] checkx4;
    wire [31:0] checkx5;
    wire [31:0] checkx6;
    wire [31:0] DM0;
    wire [31:0] instruction;
    
    initial clk=0;
    always #5 clk=~clk;

    initial begin
        rst = 1;
        #20
        rst = 0;
    end

    main i_riscv (
        .clk(clk),
        .rst(rst),
        .checkx1(checkx1),
        .checkx2(checkx2),
        .checkx3(checkx3),
        .checkx4(checkx4),
        .checkx5(checkx5),
        .checkx6(checkx6),
        .DM0(DM0),
        .instruction(instruction)
    );
 
endmodule