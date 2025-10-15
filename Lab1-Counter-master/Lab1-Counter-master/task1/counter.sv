module counter #(
    parameter width = 8
)(
    input logic clk,
    input logic rst,
    input logic en,
    output logic [width-1:0] count
);

alwayys_ff @(posedge clk) begin
    if(rst)begin
        count <= {width{1'b0}};
    end else if(en)begin
        count <= count +1'b1;
    end
end



endmodule