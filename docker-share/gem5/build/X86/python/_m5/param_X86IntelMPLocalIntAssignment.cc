/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_cc.py:297
 */

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include <type_traits>

#include "base/compiler.hh"
#include "params/X86IntelMPLocalIntAssignment.hh"
#include "sim/init.hh"
#include "sim/sim_object.hh"

#include "arch/x86/bios/intelmp.hh"

#include "base/types.hh"
#include "base/types.hh"
#include "enums/X86IntelMPInterruptType.hh"
#include "enums/X86IntelMPPolarity.hh"
#include "base/types.hh"
#include "base/types.hh"
#include "enums/X86IntelMPTriggerMode.hh"
namespace py = pybind11;

namespace gem5
{

static void
module_init(py::module_ &m_internal)
{
py::module_ m = m_internal.def_submodule("param_X86IntelMPLocalIntAssignment");
    py::class_<X86IntelMPLocalIntAssignmentParams, X86IntelMPBaseConfigEntryParams, std::unique_ptr<X86IntelMPLocalIntAssignmentParams, py::nodelete>>(m, "X86IntelMPLocalIntAssignmentParams")
        .def(py::init<>())
        .def("create", &X86IntelMPLocalIntAssignmentParams::create)
        .def_readwrite("dest_local_apic_id", &X86IntelMPLocalIntAssignmentParams::dest_local_apic_id)
        .def_readwrite("dest_local_apic_intin", &X86IntelMPLocalIntAssignmentParams::dest_local_apic_intin)
        .def_readwrite("interrupt_type", &X86IntelMPLocalIntAssignmentParams::interrupt_type)
        .def_readwrite("polarity", &X86IntelMPLocalIntAssignmentParams::polarity)
        .def_readwrite("source_bus_id", &X86IntelMPLocalIntAssignmentParams::source_bus_id)
        .def_readwrite("source_bus_irq", &X86IntelMPLocalIntAssignmentParams::source_bus_irq)
        .def_readwrite("trigger", &X86IntelMPLocalIntAssignmentParams::trigger)
        ;

    py::class_<gem5::X86ISA::intelmp::LocalIntAssignment, gem5::X86ISA::intelmp::BaseConfigEntry, std::unique_ptr<gem5::X86ISA::intelmp::LocalIntAssignment, py::nodelete>>(m, "gem5_COLONS_X86ISA_COLONS_intelmp_COLONS_LocalIntAssignment")
        ;

}

static EmbeddedPyBind embed_obj("X86IntelMPLocalIntAssignment", module_init, "X86IntelMPBaseConfigEntry");

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
class DummyX86IntelMPLocalIntAssignmentParamsClass
{
  public:
    gem5::X86ISA::intelmp::LocalIntAssignment *create() const;
};

template <class CxxClass, class Enable=void>
class DummyX86IntelMPLocalIntAssignmentShunt;

/*
 * This version directs to the real Params struct and the
 * default behavior of create if there's an appropriate
 * constructor.
 */
template <class CxxClass>
class DummyX86IntelMPLocalIntAssignmentShunt<CxxClass, std::enable_if_t<
    std::is_constructible_v<CxxClass, const X86IntelMPLocalIntAssignmentParams &>>>
{
  public:
    using Params = X86IntelMPLocalIntAssignmentParams;
    static gem5::X86ISA::intelmp::LocalIntAssignment *
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
class DummyX86IntelMPLocalIntAssignmentShunt<CxxClass, std::enable_if_t<
    !std::is_constructible_v<CxxClass, const X86IntelMPLocalIntAssignmentParams &>>>
{
  public:
    using Params = DummyX86IntelMPLocalIntAssignmentParamsClass;
    static gem5::X86ISA::intelmp::LocalIntAssignment *
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
[[maybe_unused]] gem5::X86ISA::intelmp::LocalIntAssignment *
DummyX86IntelMPLocalIntAssignmentShunt<gem5::X86ISA::intelmp::LocalIntAssignment>::Params::create() const
{
    return DummyX86IntelMPLocalIntAssignmentShunt<gem5::X86ISA::intelmp::LocalIntAssignment>::create(*this);
}

} // namespace gem5
