/* Copyright 2015 Palmer Dabbelt <palmer.dabbelt@eecs.berkeley.edu> */

#ifndef LIBPHDL__MODULE_HXX
#define LIBPHDL__MODULE_HXX

#include <memory>
#include <vector>

namespace phdl {
    /* Holds a single Verilog-style module. */
    class module {
    public:
        typedef std::shared_ptr<module> ptr;

    private:
        const std::vector<std::string> _lines;

    public:
        /* FIXME: parse_verilog() should do something more than this. */
        module(const std::vector<std::string>& lines);

    public:
        /* Formats this module as a string. */
        std::string serialize_verilog(void) const __attribute__((pure));

    public:
        static ptr parse_verilog(const std::vector<std::string>& contents);
    };
}

#endif
