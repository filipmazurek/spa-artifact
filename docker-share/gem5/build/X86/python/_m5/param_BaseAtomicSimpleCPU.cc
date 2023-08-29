/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_cc.py:297
 */

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include <type_traits>

#include "base/compiler.hh"
#include "params/BaseAtomicSimpleCPU.hh"
#include "sim/init.hh"
#include "sim/sim_object.hh"

#include "cpu/simple/atomic.hh"

#include "base/types.hh"
namespace py = pybind11;

namespace gem5
{

static void
module_init(py::module_ &m_internal)
{
py::module_ m = m_internal.def_submodule("param_BaseAtomicSimpleCPU");
    py::class_<BaseAtomicSimpleCPUParams, BaseSimpleCPUParams, std::unique_ptr<BaseAtomicSimpleCPUParams, py::nodelete>>(m, "BaseAtomicSimpleCPUParams")
        .def(py::init<>())
        .def("create", &BaseAtomicSimpleCPUParams::create)
        .def_readwrite("simulate_data_stalls", &BaseAtomicSimpleCPUParams::simulate_data_stalls)
        .def_readwrite("simulate_inst_stalls", &BaseAtomicSimpleCPUParams::simulate_inst_stalls)
        .def_readwrite("width", &BaseAtomicSimpleCPUParams::width)
        ;

    py::class_<gem5::AtomicSimpleCPU, gem5::BaseSimpleCPU, std::unique_ptr<gem5::AtomicSimpleCPU, py::nodelete>>(m, "gem5_COLONS_AtomicSimpleCPU")
        ;

}

static EmbeddedPyBind embed_obj("BaseAtomicSimpleCPU", module_init, "BaseSimpleCPU");

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
class DummyBaseAtomicSimpleCPUParamsClass
{
  public:
    gem5::AtomicSimpleCPU *create() const;
};

template <class CxxClass, class Enable=void>
class DummyBaseAtomicSimpleCPUShunt;

/*
 * This version directs to the real Params struct and the
 * default behavior of create if there's an appropriate
 * constructor.
 */
template <class CxxClass>
class DummyBaseAtomicSimpleCPUShunt<CxxClass, std::enable_if_t<
    std::is_constructible_v<CxxClass, const BaseAtomicSimpleCPUParams &>>>
{
  public:
    using Params = BaseAtomicSimpleCPUParams;
    static gem5::AtomicSimpleCPU *
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
class DummyBaseAtomicSimpleCPUShunt<CxxClass, std::enable_if_t<
    !std::is_constructible_v<CxxClass, const BaseAtomicSimpleCPUParams &>>>
{
  public:
    using Params = DummyBaseAtomicSimpleCPUParamsClass;
    static gem5::AtomicSimpleCPU *
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
[[maybe_unused]] gem5::AtomicSimpleCPU *
DummyBaseAtomicSimpleCPUShunt<gem5::AtomicSimpleCPU>::Params::create() const
{
    return DummyBaseAtomicSimpleCPUShunt<gem5::AtomicSimpleCPU>::create(*this);
}

} // namespace gem5
