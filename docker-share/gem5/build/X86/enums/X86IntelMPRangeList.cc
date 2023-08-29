/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/enum_cc.py:170
 */

#include "base/compiler.hh"
#include "enums/X86IntelMPRangeList.hh"

namespace gem5
{

GEM5_DEPRECATED_NAMESPACE(Enums, enums);
namespace enums
{
    const char *X86IntelMPRangeListStrings[Num_X86IntelMPRangeList] =
    {
        "ISACompatible",
        "VGACompatible",
    };
} // namespace enums
} // namespace gem5
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include <sim/init.hh>

namespace py = pybind11;

namespace gem5
{

static void
module_init(py::module_ &m_internal)
{
    py::module_ m = m_internal.def_submodule("enum_X86IntelMPRangeList");

py::enum_<enums::X86IntelMPRangeList>(m, "enum_X86IntelMPRangeList")
        .value("ISACompatible", enums::ISACompatible)
        .value("VGACompatible", enums::VGACompatible)
        .value("Num_X86IntelMPRangeList", enums::Num_X86IntelMPRangeList)
        .export_values()
        ;
    }
static EmbeddedPyBind embed_enum("enum_X86IntelMPRangeList", module_init);

} // namespace gem5
    
