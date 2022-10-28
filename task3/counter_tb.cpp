#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"



int main(int argc, char **argv, char**env) {
    int i;
    int clk;

    Verilated::commandArgs(argc,argv);
    //innit top verilog instance
    Vcounter* top = new Vcounter;
    //init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top -> trace (tfp, 99);
    tfp -> open ("counter.vcd");

    //init vbuddy
    if (vbdOpen()!=1) return (-1);
    vbdHeader("Lab 1: Counter");

    //initialise simulation inputs
    top->clk = 1;
    top->rst = 0;
    top->en = 0;
    //initialise "triggerVal" to 0 else will immidiately jump to encoder value
    top->triggerVal = 0;
    //initialise val to 0 (start on zero)
    top->val = 0b00000000;


    //run simulation for many clock cycles
    for (i = 0; i < 600; i++) {

        //dump variables into VCD file and toggle clock
        for (clk=0; clk<2; clk++) {
            tfp->dump (2*i+clk); //units will be in picoseconds 
            top->clk = !top->clk;
            top->eval ();
        }

        //plot the current count
        vbdPlot(int(top->count), 0, 110);
        vbdCycle(i+1);



        // ---- end of Vbuddy output selection

        //enable button on vbuddy
        top->en = vbdFlag();

        //input is now set to "shot fire" mode
        // when pressed, the flag is set to 1, but once read it is immidiately set to 0
        vbdSetMode(1);

        //behaviour: when the button is pressed, set the count to the value on the rotary encoder.
        //(the counter will still increase in value, but will set itsself to a value when button is pressed.)
        
        //here is the value for the rotary encoder, we must now pass it in to the val parameter
        //(we can pass it in every clock cycle, it wont change unless theres a pulse.)
        int value = vbdValue();
        
        //if the flag is pressed
        if (vbdFlag()) {

            //a small debugging step
            //this has the function "every time you click add 1"
            
            //top->en = 1;

            
            top->triggerVal = 1;
            top->val = vbdValue();
            
        }


        if(Verilated::gotFinish()) exit(0);

    }

    vbdClose();
    tfp->close();
    exit(0);

}