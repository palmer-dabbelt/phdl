/* Copyright 2015 Palmer Dabbelt <palmer.dabbelt@eecs.berkeley.edu> */

#include "circuit.h++"
using namespace phdl;

circuit::circuit(const std::vector<module::ptr>& modules)
    : _modules(modules)
{
}
