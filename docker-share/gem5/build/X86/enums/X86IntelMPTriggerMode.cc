/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/enum_cc.py:170
 */

#include "base/compiler.hh"
#include "enums/X86IntelMPTriggerMode.hh"

namespace gem5
{

GEM5_DEPRECATED_NAMESPACE(Enums, enums);
namespace enums
{
    const char *X86IntelMPTriggerModeStrings[Num_X86IntelMPTriggerMode] =
    {
        "ConformTrigger",
        "EdgeTrigger",
        "LevelTrigger",
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
    py::module_ m = m_internal.def_submodule("enum_X86IntelMPTriggerMode");

py::enum_<enums::X86IntelMPTriggerMode>(m, "enum_X86IntelMPTriggerMode")
        .value("ConformTrigger", enums::ConformTrigger)
        .value("EdgeTrigger", enums::EdgeTrigger)
        .value("LevelTrigger", enums::LevelTrigger)
        .value("Num_X86IntelMPTriggerMode", enums::Num_X86IntelMPTriggerMode)
        .export_values()
        ;
    }
static EmbeddedPyBind embed_enum("enum_X86IntelMPTriggerMode", module_init);

} // namespace gem5
    
