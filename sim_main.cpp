// DESCRIPTION: Verilator: Verilog example module
//
// This file ONLY is placed under the Creative Commons Public Domain, for
// any use, without warranty, 2017 by Wilson Snyder.
// SPDX-License-Identifier: CC0-1.0
//======================================================================

#include <verilated.h>

#include "Vtop.h"

vluint64_t main_time = 0;
double sc_time_stamp() {
    return main_time;  // Note does conversion to real, to match SystemC
}

int main(int argc, char** argv, char** env) {
    // This example started with the Verilator example files.
    // Please see those examples for commented sources, here:
    // https://github.com/verilator/verilator/tree/master/examples

    if (0 && argc && argv && env) {}

    Verilated::debug(0);
    Verilated::randReset(2);
    Verilated::traceEverOn(true);
    Verilated::commandArgs(argc, argv);
    Verilated::mkdir("logs");

    Vtop* top = new Vtop;  // Or use a const unique_ptr, or the VL_UNIQUE_PTR wrapper

    top->clk = 0;
    while (!Verilated::gotFinish()) {
        ++main_time;
        top->clk = !top->clk;
        top->reset = (main_time < 10) ? 1 : 0;
        if (main_time < 5) {
            // Zero coverage if still early in reset, otherwise toggles there may
            // falsely indicate a signal is covered
            VerilatedCov::zero();
        }
        top->eval();
    }

    top->final();

    //  Coverage analysis (since test passed)
#if VM_COVERAGE
    Verilated::mkdir("logs");
    VerilatedCov::write("logs/coverage.dat");
#endif

    delete top;
    top = NULL;
    exit(0);
}
