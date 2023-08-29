/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_cc.py:297
 */

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include <type_traits>

#include "base/compiler.hh"
#include "params/BiModeBP.hh"
#include "sim/init.hh"
#include "sim/sim_object.hh"

#include "cpu/pred/bi_mode.hh"

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
py::module_ m = m_internal.def_submodule("param_BiModeBP");
    py::class_<BiModeBPParams, BranchPredictorParams, std::unique_ptr<BiModeBPParams, py::nodelete>>(m, "BiModeBPParams")
        .def(py::init<>())
        .def("create", &BiModeBPParams::create)
        .def_readwrite("choiceCtrBits", &BiModeBPParams::choiceCtrBits)
        .def_readwrite("choicePredictorSize", &BiModeBPParams::choicePredictorSize)
        .def_readwrite("globalCtrBits", &BiModeBPParams::globalCtrBits)
        .def_readwrite("globalPredictorSize", &BiModeBPParams::globalPredictorSize)
        ;

    py::class_<gem5::branch_prediction::BiModeBP, gem5::branch_prediction::BPredUnit, std::unique_ptr<gem5::branch_prediction::BiModeBP, py::nodelete>>(m, "gem5_COLONS_branch_prediction_COLONS_BiModeBP")
        ;

}

static EmbeddedPyBind embed_obj("BiModeBP", module_init, "BranchPredictor");

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
class DummyBiModeBPParamsClass
{
  public:
    gem5::branch_prediction::BiModeBP *create() const;
};

template <class CxxClass, class Enable=void>
class DummyBiModeBPShunt;

/*
 * This version directs to the real Params struct and the
 * default behavior of create if there's an appropriate
 * constructor.
 */
template <class CxxClass>
class DummyBiModeBPShunt<CxxClass, std::enable_if_t<
    std::is_constructible_v<CxxClass, const BiModeBPParams &>>>
{
  public:
    using Params = BiModeBPParams;
    static gem5::branch_prediction::BiModeBP *
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
class DummyBiModeBPShunt<CxxClass, std::enable_if_t<
    !std::is_constructible_v<CxxClass, const BiModeBPParams &>>>
{
  public:
    using Params = DummyBiModeBPParamsClass;
    static gem5::branch_prediction::BiModeBP *
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
[[maybe_unused]] gem5::branch_prediction::BiModeBP *
DummyBiModeBPShunt<gem5::branch_prediction::BiModeBP>::Params::create() const
{
    return DummyBiModeBPShunt<gem5::branch_prediction::BiModeBP>::create(*this);
}

} // namespace gem5