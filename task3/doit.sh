#!/bin/sh

#cleanup
rm -rf obj_dir
rm -f counter.vcd


#run Verilator to translate Verilog into C++, including the C++ testbench
verilator -Wall --cc --trace counter.sv --exe counter_tb.cpp

#build C++ project via make automatically generated by verilator
make -j -C obj_dir/ -f Vcounter.mk Vcounter

#clears up all the compile time junk
#if youre having problems and need to see the errors comment the clear
#clear

#run executable simulation file
obj_dir/Vcounter


#to run:
#source ./doit.sh