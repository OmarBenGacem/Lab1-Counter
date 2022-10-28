
/*things to note: 
    - the file name must always be the same
    - the number of bits stored in the counter is determined by WIDTH, which is 8 buts
    always_ff defines the clocked circuit behaviour.
    - <= is a non blocking assignment, and should always be used for the clocked circuits
    - {WIDTH{1’b0}} in line 12 uses the concatenation operator { } to form WIDTH bits of ‘0’.
        - so line 24 is concatinating 7 zeros with enable (if enable is 1 we add 1 else add 0)
*/


module counter#(
    parameter WIDTH = 8
)(
    //interface signals
    input logic [WIDTH-1:0] val, //a value to set the counter to
    input logic             triggerVal, //set count = val
    input logic             clk,    //clock
    input logic             rst,    //reset
    input logic             en,     //enable
    output logic [WIDTH-1:0] count   //current counted to value
);

always_ff @ (posedge clk) //the clock circuit behaviour

        if (rst) count <= {WIDTH{1'b0}}; //if reset, set count equal to zero


        /*

        //if you want to stop counting, up, delete this line (no longer countng down becaue flag is set to "one shot")
        else if (en) count <= count + {{WIDTH-1{1'b0}}, en};

        //new: if triggerVal = 1, we need to set count to val, which is the value on the rotary encoder
        else if (triggerVal) count <= val;
        

        */

        //only exdcute logic if the module is enabled
        if (en) begin

            if (triggerVal) count <= val;
            else count <= count + {{WIDTH-1{1'b0}}, en};

        end


endmodule

