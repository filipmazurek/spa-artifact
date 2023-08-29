/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_cc.py:297
 */

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include <type_traits>

#include "base/compiler.hh"
#include "params/X86IntelMPProcessor.hh"
#include "sim/init.hh"
#include "sim/sim_object.hh"

#include "arch/x86/bios/intelmp.hh"

#include "base/types.hh"
#include "base/types.hh"
#include "base/types.hh"
#include "base/types.hh"
#include "base/types.hh"
#include "base/types.hh"
namespace py = pybind11;

namespace gem5
{

static void
module_init(py::module_ &m_internal)
{
py::module_ m = m_internal.def_submodule("param_X86IntelMPProcessor");
    py::class_<X86IntelMPProcessorParams, X86IntelMPBaseConfigEntryParams, std::unique_ptr<X86IntelMPProcessorParams, py::nodelete>>(m, "X86IntelMPProcessorParams")
        .def(py::init<>())
        .def("create", &X86IntelMPProcessorParams::create)
        .def_readwrite("bootstrap", &X86IntelMPProcessorParams::bootstrap)
        .def_readwrite("enable", &X86IntelMPProcessorParams::enable)
        .def_readwrite("family", &X86IntelMPProcessorParams::family)
        .def_readwrite("feature_flags", &X86IntelMPProcessorParams::feature_flags)
        .def_readwrite("local_apic_id", &X86IntelMPProcessorParams::local_apic_id)
        .def_readwrite("local_apic_version", &X86IntelMPProcessorParams::local_apic_version)
        .def_readwrite("model", &X86IntelMPProcessorParams::model)
        .def_readwrite("stepping", &X86IntelMPProcessorParams::stepping)
        ;

    py::class_<gem5::X86ISA::intelmp::Processor, gem5::X86ISA::intelmp::BaseConfigEntry, std::unique_ptr<gem5::X86ISA::intelmp::Processor, py::nodelete>>(m, "gem5_COLONS_X86ISA_COLONS_intelmp_COLONS_Processor")
        ;

}

static EmbeddedPyBind embed_obj("X86IntelMPProcessor", module_init, "X86IntelMPBaseConfigEntry");

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
class DummyX86IntelMPProcessorParamsClass
{
  public:
    gem5::X86ISA::intelmp::Processor *create() const;
};

template <class CxxClass, class Enable=void>
class DummyX86IntelMPProcessorShunt;

/*
 * This version directs to the real Params struct and the
 * default behavior of create if there's an appropriate
 * constructor.
 */
template <class CxxClass>
class DummyX86IntelMPProcessorShunt<CxxClass, std::enable_if_t<
    std::is_constructible_v<CxxClass, const X86IntelMPProcessorParams &>>>
{
  public:
    using Params = X86IntelMPProcessorParams;
    static gem5::X86ISA::intelmp::Processor *
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
class DummyX86IntelMPProcessorShunt<CxxClass, std::enable_if_t<
    !std::is_constructible_v<CxxClass, const X86IntelMPProcessorParams &>>>
{
  public:
    using Params = DummyX86IntelMPProcessorParamsClass;
    static gem5::X86ISA::intelmp::Processor *
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
[[maybe_unused]] gem5::X86ISA::intelmp::Processor *
DummyX86IntelMPProcessorShunt<gem5::X86ISA::intelmp::Processor>::Params::create() const
{
    return DummyX86IntelMPProcessorShunt<gem5::X86ISA::intelmp::Processor>::create(*this);
}

} // namespace gem5