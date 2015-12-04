/* Copyright 2015 Palmer Dabbelt <palmer.dabbelt@eecs.berkeley.edu> */

#include "verilog.h++"
#include "module.h++"
#include <cstring>
#include <sstream>
#include <vector>
using namespace phdl;

#ifndef LINE_MAX
#define LINE_MAX 1024
#endif

circuit::ptr verilog::parse(const std::string& filename)
{
    auto f = fopen(filename.c_str(), "r");
    auto out = parse(f);
    fclose(f);
    return out;
}

circuit::ptr verilog::parse(FILE* file)
{
    enum class parse_state {
        NONE,
        MODULE,
    } state = parse_state::NONE;

    auto str_start = [](std::string str, std::string needle) -> bool
        {
            return strncmp(str.c_str(), needle.c_str(), needle.size()) == 0;
        };

    char line[LINE_MAX];

    std::vector<std::string> module;
    std::vector<module::ptr> modules;

    while (fgets(line, LINE_MAX, file)) {
        while (isspace(line[strlen(line)-1]))
            line[strlen(line)-1] = '\0';
        fprintf(stderr, "line: '%s'\n", line);

        switch (state) {
        case parse_state::NONE:
            if (str_start(line, "module ")) {
                state = parse_state::MODULE;
                module = {line};
                goto successful_line_parse;
            }
            break;

        case parse_state::MODULE:
            module.push_back(line);
            if (str_start(line, "endmodule")) {
                state = parse_state::NONE;
                modules.push_back(module::parse_verilog(module));
                module = {};
            }
            goto successful_line_parse;
            break;
        }

        fprintf(stderr, "Unable to parse line '%s'\n", line);
        abort();

    successful_line_parse:
        continue;
    }

    return std::make_shared<circuit>(modules);
}

std::string verilog::serialize(const circuit::ptr& circuit __attribute__((unused)))
{
    std::stringstream s;

    for (const auto& module: circuit->modules()) {
        s << module->serialize_verilog() << "\n";
    }

    auto str = s.str();
    return std::string(str, 0, str.size()-1);
}
