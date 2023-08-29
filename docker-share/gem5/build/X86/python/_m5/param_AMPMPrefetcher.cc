/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_cc.py:297
 */

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include <type_traits>

#include "base/compiler.hh"
#include "params/AMPMPrefetcher.hh"
#include "sim/init.hh"
#include "sim/sim_object.hh"

#include "mem/cache/prefetch/access_map_pattern_matching.hh"

#include "mem/cache/prefetch/access_map_pattern_matching.hh"
namespace py = pybind11;

namespace gem5
{

static void
module_init(py::module_ &m_internal)
{
py::module_ m = m_internal.def_submodule("param_AMPMPrefetcher");
    py::class_<AMPMPrefetcherParams, QueuedPrefetcherParams, std::unique_ptr<AMPMPrefetcherParams, py::nodelete>>(m, "AMPMPrefetcherParams")
        .def(py::init<>())
        .def("create", &AMPMPrefetcherParams::create)
        .def_readwrite("ampm", &AMPMPrefetcherParams::ampm)
        ;

    py::class_<gem5::prefetch::AMPM, gem5::prefetch::Queued, std::unique_ptr<gem5::prefetch::AMPM, py::nodelete>>(m, "gem5_COLONS_prefetch_COLONS_AMPM")
        ;

}

static EmbeddedPyBind embed_obj("AMPMPrefetcher", module_init, "QueuedPrefetcher");

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
class DummyAMPMPrefetcherParamsClass
{
  public:
    gem5::prefetch::AMPM *create() const;
};

template <class CxxClass, class Enable=void>
class DummyAMPMPrefetcherShunt;

/*
 * This version directs to the real Params struct and the
 * default behavior of create if there's an appropriate
 * constructor.
 */
template <class CxxClass>
class DummyAMPMPrefetcherShunt<CxxClass, std::enable_if_t<
    std::is_constructible_v<CxxClass, const AMPMPrefetcherParams &>>>
{
  public:
    using Params = AMPMPrefetcherParams;
    static gem5::prefetch::AMPM *
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
class DummyAMPMPrefetcherShunt<CxxClass, std::enable_if_t<
    !std::is_constructible_v<CxxClass, const AMPMPrefetcherParams &>>>
{
  public:
    using Params = DummyAMPMPrefetcherParamsClass;
    static gem5::prefetch::AMPM *
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
[[maybe_unused]] gem5::prefetch::AMPM *
DummyAMPMPrefetcherShunt<gem5::prefetch::AMPM>::Params::create() const
{
    return DummyAMPMPrefetcherShunt<gem5::prefetch::AMPM>::create(*this);
}

} // namespace gem5