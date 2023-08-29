/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_cc.py:297
 */

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include <type_traits>

#include "base/compiler.hh"
#include "params/L1Cache_Controller.hh"
#include "sim/init.hh"
#include "sim/sim_object.hh"

#include "mem/ruby/protocol/L1Cache_Controller.hh"

#include "mem/ruby/structures/CacheMemory.hh"
#include "mem/ruby/structures/CacheMemory.hh"
#include "mem/ruby/structures/CacheMemory.hh"
#include "base/types.hh"
#include "mem/ruby/network/MessageBuffer.hh"
#include "base/types.hh"
#include "base/types.hh"
#include "mem/ruby/network/MessageBuffer.hh"
#include "mem/ruby/network/MessageBuffer.hh"
#include "mem/ruby/network/MessageBuffer.hh"
#include "mem/ruby/network/MessageBuffer.hh"
#include "mem/ruby/system/Sequencer.hh"
#include "mem/ruby/network/MessageBuffer.hh"
#include "mem/ruby/network/MessageBuffer.hh"
namespace py = pybind11;

namespace gem5
{

static void
module_init(py::module_ &m_internal)
{
py::module_ m = m_internal.def_submodule("param_L1Cache_Controller");
    py::class_<L1Cache_ControllerParams, RubyControllerParams, std::unique_ptr<L1Cache_ControllerParams, py::nodelete>>(m, "L1Cache_ControllerParams")
        .def(py::init<>())
        .def("create", &L1Cache_ControllerParams::create)
        .def_readwrite("L1Dcache", &L1Cache_ControllerParams::L1Dcache)
        .def_readwrite("L1Icache", &L1Cache_ControllerParams::L1Icache)
        .def_readwrite("L2cache", &L1Cache_ControllerParams::L2cache)
        .def_readwrite("cache_response_latency", &L1Cache_ControllerParams::cache_response_latency)
        .def_readwrite("forwardToCache", &L1Cache_ControllerParams::forwardToCache)
        .def_readwrite("issue_latency", &L1Cache_ControllerParams::issue_latency)
        .def_readwrite("l2_cache_hit_latency", &L1Cache_ControllerParams::l2_cache_hit_latency)
        .def_readwrite("mandatoryQueue", &L1Cache_ControllerParams::mandatoryQueue)
        .def_readwrite("no_mig_atomic", &L1Cache_ControllerParams::no_mig_atomic)
        .def_readwrite("requestFromCache", &L1Cache_ControllerParams::requestFromCache)
        .def_readwrite("responseFromCache", &L1Cache_ControllerParams::responseFromCache)
        .def_readwrite("responseToCache", &L1Cache_ControllerParams::responseToCache)
        .def_readwrite("send_evictions", &L1Cache_ControllerParams::send_evictions)
        .def_readwrite("sequencer", &L1Cache_ControllerParams::sequencer)
        .def_readwrite("triggerQueue", &L1Cache_ControllerParams::triggerQueue)
        .def_readwrite("unblockFromCache", &L1Cache_ControllerParams::unblockFromCache)
        ;

    py::class_<gem5::ruby::L1Cache_Controller, gem5::ruby::AbstractController, std::unique_ptr<gem5::ruby::L1Cache_Controller, py::nodelete>>(m, "gem5_COLONS_ruby_COLONS_L1Cache_Controller")
        ;

}

static EmbeddedPyBind embed_obj("L1Cache_Controller", module_init, "RubyController");

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
class DummyL1Cache_ControllerParamsClass
{
  public:
    gem5::ruby::L1Cache_Controller *create() const;
};

template <class CxxClass, class Enable=void>
class DummyL1Cache_ControllerShunt;

/*
 * This version directs to the real Params struct and the
 * default behavior of create if there's an appropriate
 * constructor.
 */
template <class CxxClass>
class DummyL1Cache_ControllerShunt<CxxClass, std::enable_if_t<
    std::is_constructible_v<CxxClass, const L1Cache_ControllerParams &>>>
{
  public:
    using Params = L1Cache_ControllerParams;
    static gem5::ruby::L1Cache_Controller *
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
class DummyL1Cache_ControllerShunt<CxxClass, std::enable_if_t<
    !std::is_constructible_v<CxxClass, const L1Cache_ControllerParams &>>>
{
  public:
    using Params = DummyL1Cache_ControllerParamsClass;
    static gem5::ruby::L1Cache_Controller *
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
[[maybe_unused]] gem5::ruby::L1Cache_Controller *
DummyL1Cache_ControllerShunt<gem5::ruby::L1Cache_Controller>::Params::create() const
{
    return DummyL1Cache_ControllerShunt<gem5::ruby::L1Cache_Controller>::create(*this);
}

} // namespace gem5