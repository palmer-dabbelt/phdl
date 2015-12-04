/* Copyright 2015 Palmer Dabbelt <palmer.dabbelt@eecs.berkeley.edu> */

#include "module.h++"
#include <sstream>
using namespace phdl;

module::module(const std::vector<std::string>& lines)
    : _lines(lines)
{
}

std::string module::serialize_verilog(void) const
{
    std::stringstream s;

    for (const auto& line: _lines)
        s << line << "\n";

    return s.str();
}

module::ptr module::parse_verilog(const std::vector<std::string>& lines)
{
    return std::make_shared<module>(lines);
}
