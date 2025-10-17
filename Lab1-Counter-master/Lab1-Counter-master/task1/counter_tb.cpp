#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv) {

    int i;//i counts the number of clock cycles to simulate
    int clk;//clk is the module clk signal

    Verilated::commandArgs(argc, argv);//read cmd line args
    //init top verilog instance
    Vcounter* top = new Vcounter;

    //init trace dump
    Verilated::traceEverOn(true);//turn on signal tracing
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);//trace 99 levels of hierarchy
    tfp->open("counter.vcd");// open the dump file

    //initialize simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    //run simulation for 300 clock cycles
    for(i=0; i<300; i++){//i counts the number of cycles
        //dumbing the variables into VCD file and toggle clock
        for(clk=0; clk<2; clk++){
            tfp->dump(10*i+5*clk);//unit in ps
            top->clk = !top->clk;//toggle clock
            top->eval();//evaluate model
        }
        top->rst = (i<1);//assert reset for 2 cycles
        top->en = !((i>9) & (i<13));//enable counting between 5 and 14
        if (Verilated::gotFinish()) exit(0);
    }
    tfp->close();
    exit(0);
}
