/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_cc.py:297
 */

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include <type_traits>

#include "base/compiler.hh"
#include "params/TAGEBase.hh"
#include "sim/init.hh"
#include "sim/sim_object.hh"

#include "cpu/pred/tage_base.hh"

#include "base/types.hh"
#include "base/types.hh"
#include "base/types.hh"
#include "base/types.hh"
#include <vector>
#include "base/types.hh"
#include "base/types.hh"
#include "base/types.hh"
#include "base/types.hh"
#include "base/types.hh"
#include "base/types.hh"
#include <vector>
#include "base/types.hh"
#include "base/types.hh"
#include "base/types.hh"
#include "base/types.hh"
#include <vector>
#include "base/types.hh"
#include "base/types.hh"
#include "base/types.hh"
namespace py = pybind11;

namespace gem5
{

static void
module_init(py::module_ &m_internal)
{
py::module_ m = m_internal.def_submodule("param_TAGEBase");
    py::class_<TAGEBaseParams, SimObjectParams, std::unique_ptr<TAGEBaseParams, py::nodelete>>(m, "TAGEBaseParams")
        .def(py::init<>())
        .def("create", &TAGEBaseParams::create)
        .def_readwrite("histBufferSize", &TAGEBaseParams::histBufferSize)
        .def_readwrite("initialTCounterValue", &TAGEBaseParams::initialTCounterValue)
        .def_readwrite("instShiftAmt", &TAGEBaseParams::instShiftAmt)
        .def_readwrite("logRatioBiModalHystEntries", &TAGEBaseParams::logRatioBiModalHystEntries)
        .def_readwrite("logTagTableSizes", &TAGEBaseParams::logTagTableSizes)
        .def_readwrite("logUResetPeriod", &TAGEBaseParams::logUResetPeriod)
        .def_readwrite("maxHist", &TAGEBaseParams::maxHist)
        .def_readwrite("maxNumAlloc", &TAGEBaseParams::maxNumAlloc)
        .def_readwrite("minHist", &TAGEBaseParams::minHist)
        .def_readwrite("nHistoryTables", &TAGEBaseParams::nHistoryTables)
        .def_readwrite("noSkip", &TAGEBaseParams::noSkip)
        .def_readwrite("numThreads", &TAGEBaseParams::numThreads)
        .def_readwrite("numUseAltOnNa", &TAGEBaseParams::numUseAltOnNa)
        .def_readwrite("pathHistBits", &TAGEBaseParams::pathHistBits)
        .def_readwrite("speculativeHistUpdate", &TAGEBaseParams::speculativeHistUpdate)
        .def_readwrite("tagTableCounterBits", &TAGEBaseParams::tagTableCounterBits)
        .def_readwrite("tagTableTagWidths", &TAGEBaseParams::tagTableTagWidths)
        .def_readwrite("tagTableUBits", &TAGEBaseParams::tagTableUBits)
        .def_readwrite("useAltOnNaBits", &TAGEBaseParams::useAltOnNaBits)
        ;

    py::class_<gem5::branch_prediction::TAGEBase, gem5::SimObject, std::unique_ptr<gem5::branch_prediction::TAGEBase, py::nodelete>>(m, "gem5_COLONS_branch_prediction_COLONS_TAGEBase")
        ;

}

static EmbeddedPyBind embed_obj("TAGEBase", module_init, "SimObject");

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
class DummyTAGEBaseParamsClass
{
  public:
    gem5::branch_prediction::TAGEBase *create() const;
};

template <class CxxClass, class Enable=void>
class DummyTAGEBaseShunt;

/*
 * This version directs to the real Params struct and the
 * default behavior of create if there's an appropriate
 * constructor.
 */
template <class CxxClass>
class DummyTAGEBaseShunt<CxxClass, std::enable_if_t<
    std::is_constructible_v<CxxClass, const TAGEBaseParams &>>>
{
  public:
    using Params = TAGEBaseParams;
    static gem5::branch_prediction::TAGEBase *
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
class DummyTAGEBaseShunt<CxxClass, std::enable_if_t<
    !std::is_constructible_v<CxxClass, const TAGEBaseParams &>>>
{
  public:
    using Params = DummyTAGEBaseParamsClass;
    static gem5::branch_prediction::TAGEBase *
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
[[maybe_unused]] gem5::branch_prediction::TAGEBase *
DummyTAGEBaseShunt<gem5::branch_prediction::TAGEBase>::Params::create() const
{
    return DummyTAGEBaseShunt<gem5::branch_prediction::TAGEBase>::create(*this);
}

} // namespace gem5