/* Copyright 2015 Palmer Dabbelt <palmer.dabbelt@eecs.berkeley.edu> */

#ifndef LIBPHDL__VERILOG_HXX
#define LIBPHDL__VERILOG_HXX

#include "circuit.h++"

namespace phdl {
    namespace verilog {
        /* Parses a Verilog file, producing a circuit. */
        circuit::ptr parse(const std::string& filename);
        circuit::ptr parse(FILE* file);

        /* Converts a circuit to a string. */
        std::string serialize(const circuit::ptr& circuit);
    }
}

#endif
