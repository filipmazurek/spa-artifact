/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_cc.py:297
 */

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include <type_traits>

#include "base/compiler.hh"
#include "params/X86ACPIMadt.hh"
#include "sim/init.hh"
#include "sim/sim_object.hh"

#include "arch/x86/bios/acpi.hh"

#include "base/types.hh"
#include "base/types.hh"
#include <vector>
#include "arch/x86/bios/acpi.hh"
namespace py = pybind11;

namespace gem5
{

static void
module_init(py::module_ &m_internal)
{
py::module_ m = m_internal.def_submodule("param_X86ACPIMadt");
    py::class_<X86ACPIMadtParams, X86ACPISysDescTableParams, std::unique_ptr<X86ACPIMadtParams, py::nodelete>>(m, "X86ACPIMadtParams")
        .def(py::init<>())
        .def("create", &X86ACPIMadtParams::create)
        .def_readwrite("flags", &X86ACPIMadtParams::flags)
        .def_readwrite("local_apic_address", &X86ACPIMadtParams::local_apic_address)
        .def_readwrite("records", &X86ACPIMadtParams::records)
        ;

    py::class_<gem5::X86ISA::ACPI::MADT::MADT, gem5::X86ISA::ACPI::SysDescTable, std::unique_ptr<gem5::X86ISA::ACPI::MADT::MADT, py::nodelete>>(m, "gem5_COLONS_X86ISA_COLONS_ACPI_COLONS_MADT_COLONS_MADT")
        ;

}

static EmbeddedPyBind embed_obj("X86ACPIMadt", module_init, "X86ACPISysDescTable");

} // namespace gem5
namespace gem5
{

namespace
{

/*
 * If we can't define a default create() method for this params
 * struct because the SimObject doesn't have the right
 * constructor, use template magic to make it so we're actually
 * defining a create method for this class instead.
 */
class DummyX86ACPIMadtParamsClass
{
  public:
    gem5::X86ISA::ACPI::MADT::MADT *create() const;
};

template <class CxxClass, class Enable=void>
class DummyX86ACPIMadtShunt;

/*
 * This version directs to the real Params struct and the
 * default behavior of create if there's an appropriate
 * constructor.
 */
template <class CxxClass>
class DummyX86ACPIMadtShunt<CxxClass, std::enable_if_t<
    std::is_constructible_v<CxxClass, const X86ACPIMadtParams &>>>
{
  public:
    using Params = X86ACPIMadtParams;
    static gem5::X86ISA::ACPI::MADT::MADT *
    create(const Params &p)
    {
        return new CxxClass(p);
    }
};

/*
 * This version diverts to the DummyParamsClass and a dummy
 * implementation of create if the appropriate constructor does
 * not exist.
 */
template <class CxxClass>
class DummyX86ACPIMadtShunt<CxxClass, std::enable_if_t<
    !std::is_constructible_v<CxxClass, const X86ACPIMadtParams &>>>
{
  public:
    using Params = DummyX86ACPIMadtParamsClass;
    static gem5::X86ISA::ACPI::MADT::MADT *
    create(const Params &p)
    {
        return nullptr;
    }
};

} // anonymous namespace

/*
 * An implementation of either the real Params struct's create
 * method, or the Dummy one. Either an implementation is
 * mandantory since this was shunted off to the dummy class, or
 * one is optional which will override this weak version.
 */
[[maybe_unused]] gem5::X86ISA::ACPI::MADT::MADT *
DummyX86ACPIMadtShunt<gem5::X86ISA::ACPI::MADT::MADT>::Params::create() const
{
    return DummyX86ACPIMadtShunt<gem5::X86ISA::ACPI::MADT::MADT>::create(*this);
}

} // namespace gem5