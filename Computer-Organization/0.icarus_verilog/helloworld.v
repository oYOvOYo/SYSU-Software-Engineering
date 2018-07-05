// this is a helloworld
// use fellow commands to run it
//    iverilog helloworld.v -o helloworld.out 
//    vvp helloworld.out

module main;
  initial
    begin
      $display("Hello World!");
      $finish;
    end
endmodule