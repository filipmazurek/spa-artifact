/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_cc.py:297
 */

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include <type_traits>

#include "base/compiler.hh"
#include "params/ThermalCapacitor.hh"
#include "sim/init.hh"
#include "sim/sim_object.hh"

#include "sim/power/thermal_model.hh"

namespace py = pybind11;

namespace gem5
{

static void
module_init(py::module_ &m_internal)
{
py::module_ m = m_internal.def_submodule("param_ThermalCapacitor");
    py::class_<ThermalCapacitorParams, SimObjectParams, std::unique_ptr<ThermalCapacitorParams, py::nodelete>>(m, "ThermalCapacitorParams")
        .def(py::init<>())
        .def("create", &ThermalCapacitorParams::create)
        .def_readwrite("capacitance", &ThermalCapacitorParams::capacitance)
        ;

    py::class_<gem5::ThermalCapacitor, gem5::SimObject, std::unique_ptr<gem5::ThermalCapacitor, py::nodelete>>(m, "gem5_COLONS_ThermalCapacitor")
        .def("setNodes", &gem5::ThermalCapacitor::setNodes)
        ;

}

static EmbeddedPyBind embed_obj("ThermalCapacitor", module_init, "SimObject");

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
class DummyThermalCapacitorParamsClass
{
  public:
    gem5::ThermalCapacitor *create() const;
};

template <class CxxClass, class Enable=void>
class DummyThermalCapacitorShunt;

/*
 * This version directs to the real Params struct and the
 * default behavior of create if there's an appropriate
 * constructor.
 */
template <class CxxClass>
class DummyThermalCapacitorShunt<CxxClass, std::enable_if_t<
    std::is_constructible_v<CxxClass, const ThermalCapacitorParams &>>>
{
  public:
    using Params = ThermalCapacitorParams;
    static gem5::ThermalCapacitor *
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
class DummyThermalCapacitorShunt<CxxClass, std::enable_if_t<
    !std::is_constructible_v<CxxClass, const ThermalCapacitorParams &>>>
{
  public:
    using Params = DummyThermalCapacitorParamsClass;
    static gem5::ThermalCapacitor *
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
[[maybe_unused]] gem5::ThermalCapacitor *
DummyThermalCapacitorShunt<gem5::ThermalCapacitor>::Params::create() const
{
    return DummyThermalCapacitorShunt<gem5::ThermalCapacitor>::create(*this);
}

} // namespace gem5
