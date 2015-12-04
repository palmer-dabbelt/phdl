#include <libphdl/verilog.h++>
#include <libputil/filesystem.h++>
#include <string>
#include <cstring>
#include <iostream>

int main(int argc, char **argv)
{
    auto input = [&]() -> std::string
        {
            for (int i = 1; i < argc; ++i)
                if (strcmp(argv[i], "-i") == 0)
                    return argv[i+1];
            std::cerr << "Unable to find -i argument" << std::endl;
            abort();
        }();

    auto output = [&]() -> std::string
        {
            for (int i = 1; i < argc; ++i)
                if (strcmp(argv[i], "-o") == 0)
                    return argv[i+1];
            std::cerr << "Unable to find -o argument" << std::endl;
            abort();
        }();

    auto circuit = phdl::verilog::parse(input);
    auto verilog_string = phdl::verilog::serialize(circuit);
    {
        auto file = putil::filesystem::textfile(output);
        file.write({verilog_string});
    }
}
