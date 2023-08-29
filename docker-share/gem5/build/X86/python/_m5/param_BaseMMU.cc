/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_cc.py:297
 */

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include <type_traits>

#include "base/compiler.hh"
#include "params/BaseMMU.hh"
#include "sim/init.hh"
#include "sim/sim_object.hh"

#include "arch/generic/mmu.hh"

#include "arch/generic/tlb.hh"
#include "arch/generic/tlb.hh"
namespace py = pybind11;

namespace gem5
{

static void
module_init(py::module_ &m_internal)
{
py::module_ m = m_internal.def_submodule("param_BaseMMU");
    py::class_<BaseMMUParams, SimObjectParams, std::unique_ptr<BaseMMUParams, py::nodelete>>(m, "BaseMMUParams")
        .def_readwrite("dtb", &BaseMMUParams::dtb)
        .def_readwrite("itb", &BaseMMUParams::itb)
        ;

    py::class_<gem5::BaseMMU, gem5::SimObject, std::unique_ptr<gem5::BaseMMU, py::nodelete>>(m, "gem5_COLONS_BaseMMU")
        ;

}

static EmbeddedPyBind embed_obj("BaseMMU", module_init, "SimObject");

} // namespace gem5