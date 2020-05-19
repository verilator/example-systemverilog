// DESCRIPTION: Verilator: Verilog example module
//
// This file ONLY is placed under the Creative Commons Public Domain, for
// any use, without warranty, 2003 by Wilson Snyder.
// SPDX-License-Identifier: CC0-1.0
// ======================================================================

module top
  (input logic clk,
   input logic reset);

   // Create 100 cycles of example stimulus
   reg [31:0] count_c;
   always_ff @ (posedge clk) begin
      //$display("[%0t] clk=%b reset=%b", $time, clk, reset);
      if (reset) begin
	 count_c <= 0;
      end
      else begin
	 count_c <= count_c + 1;
	 if (count_c >= 99) begin
            $write("*-* All Finished *-*\n");
            $finish;
	 end
      end
   end

   // Example coverage analysis
   cover property (@(posedge clk) count_c == 30);  // Hit
   cover property (@(posedge clk) count_c == 300);  // Not covered

   // Example toggle analysis
   wire count_hit_50;  // Hit
   wire count_hit_500;  // Not covered

   assign count_hit_50 = (count_c == 50);
   assign count_hit_500 = (count_c == 500);

   // Example line and block coverage
   always_comb begin
      if (count_hit_50) begin  // Hit	
         $write("[%0t] got 50\n", $time);  // Hit
      end
      if (count_hit_500) begin  // Not covered
         $write("[%0t] got 600\n", $time);  // Not covered
      end
   end

endmodule
