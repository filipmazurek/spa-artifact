/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/enum_cc.py:170
 */

#include "base/compiler.hh"
#include "enums/Characteristic.hh"

namespace gem5
{

GEM5_DEPRECATED_NAMESPACE(Enums, enums);
namespace enums
{
    const char *CharacteristicStrings[Num_Characteristic] =
    {
        "APM",
        "CDBoot",
        "CGA_Mono",
        "EDD",
        "EISA",
        "ESCD",
        "Flash",
        "Floppy_3_5_2_88MB",
        "Floppy_3_5_720KB",
        "Floppy_5_25_1_2MB",
        "Floppy_5_25_360KB",
        "ISA",
        "Keyboard8024",
        "MCA",
        "NEC9800",
        "NEC_PC_98",
        "PCI",
        "PCMCIA",
        "PCMCIABoot",
        "PnP",
        "PrintScreen",
        "Printer",
        "SelectBoot",
        "Serial",
        "Shadow",
        "Socketed",
        "Toshiba",
        "Unknown",
        "Unsupported",
        "VL_Vesa",
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
    py::module_ m = m_internal.def_submodule("enum_Characteristic");

py::enum_<enums::Characteristic>(m, "enum_Characteristic")
        .value("APM", enums::APM)
        .value("CDBoot", enums::CDBoot)
        .value("CGA_Mono", enums::CGA_Mono)
        .value("EDD", enums::EDD)
        .value("EISA", enums::EISA)
        .value("ESCD", enums::ESCD)
        .value("Flash", enums::Flash)
        .value("Floppy_3_5_2_88MB", enums::Floppy_3_5_2_88MB)
        .value("Floppy_3_5_720KB", enums::Floppy_3_5_720KB)
        .value("Floppy_5_25_1_2MB", enums::Floppy_5_25_1_2MB)
        .value("Floppy_5_25_360KB", enums::Floppy_5_25_360KB)
        .value("ISA", enums::ISA)
        .value("Keyboard8024", enums::Keyboard8024)
        .value("MCA", enums::MCA)
        .value("NEC9800", enums::NEC9800)
        .value("NEC_PC_98", enums::NEC_PC_98)
        .value("PCI", enums::PCI)
        .value("PCMCIA", enums::PCMCIA)
        .value("PCMCIABoot", enums::PCMCIABoot)
        .value("PnP", enums::PnP)
        .value("PrintScreen", enums::PrintScreen)
        .value("Printer", enums::Printer)
        .value("SelectBoot", enums::SelectBoot)
        .value("Serial", enums::Serial)
        .value("Shadow", enums::Shadow)
        .value("Socketed", enums::Socketed)
        .value("Toshiba", enums::Toshiba)
        .value("Unknown", enums::Unknown)
        .value("Unsupported", enums::Unsupported)
        .value("VL_Vesa", enums::VL_Vesa)
        .value("Num_Characteristic", enums::Num_Characteristic)
        .export_values()
        ;
    }
static EmbeddedPyBind embed_enum("enum_Characteristic", module_init);

} // namespace gem5
    