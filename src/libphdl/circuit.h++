/* Copyright 2015 Palmer Dabbelt <palmer.dabbelt@eecs.berkeley.edu> */

#ifndef LIBPHDL__CIRCUIT_HXX
#define LIBPHDL__CIRCUIT_HXX

#include <memory>
#include "module.h++"

namespace phdl {
    /* Holds an entire circuit, in a form that can be both manipulated and
     * written back to a string. */
    class circuit {
    public:
        typedef std::shared_ptr<circuit> ptr;

    private:
        std::vector<module::ptr> _modules;

    public:
        /* Creates a circuit given every module in that circuit. */
        circuit(const std::vector<module::ptr>& modules);

    public:
        /* Lists the modules in this circuit. */
        const std::vector<module::ptr>& modules(void) __attribute__((pure))
        { return _modules; }
    };
}

#endif
