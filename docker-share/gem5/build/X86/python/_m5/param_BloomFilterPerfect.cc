/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_cc.py:297
 */

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include <type_traits>

#include "base/compiler.hh"
#include "params/BloomFilterPerfect.hh"
#include "sim/init.hh"
#include "sim/sim_object.hh"

#include "base/filters/perfect_bloom_filter.hh"

namespace py = pybind11;

namespace gem5
{

static void
module_init(py::module_ &m_internal)
{
py::module_ m = m_internal.def_submodule("param_BloomFilterPerfect");
    py::class_<BloomFilterPerfectParams, BloomFilterBaseParams, std::unique_ptr<BloomFilterPerfectParams, py::nodelete>>(m, "BloomFilterPerfectParams")
        .def(py::init<>())
        .def("create", &BloomFilterPerfectParams::create)
        ;

    py::class_<gem5::bloom_filter::Perfect, gem5::bloom_filter::Base, std::unique_ptr<gem5::bloom_filter::Perfect, py::nodelete>>(m, "gem5_COLONS_bloom_filter_COLONS_Perfect")
        ;

}

static EmbeddedPyBind embed_obj("BloomFilterPerfect", module_init, "BloomFilterBase");

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
class DummyBloomFilterPerfectParamsClass
{
  public:
    gem5::bloom_filter::Perfect *create() const;
};

template <class CxxClass, class Enable=void>
class DummyBloomFilterPerfectShunt;

/*
 * This version directs to the real Params struct and the
 * default behavior of create if there's an appropriate
 * constructor.
 */
template <class CxxClass>
class DummyBloomFilterPerfectShunt<CxxClass, std::enable_if_t<
    std::is_constructible_v<CxxClass, const BloomFilterPerfectParams &>>>
{
  public:
    using Params = BloomFilterPerfectParams;
    static gem5::bloom_filter::Perfect *
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
class DummyBloomFilterPerfectShunt<CxxClass, std::enable_if_t<
    !std::is_constructible_v<CxxClass, const BloomFilterPerfectParams &>>>
{
  public:
    using Params = DummyBloomFilterPerfectParamsClass;
    static gem5::bloom_filter::Perfect *
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
[[maybe_unused]] gem5::bloom_filter::Perfect *
DummyBloomFilterPerfectShunt<gem5::bloom_filter::Perfect>::Params::create() const
{
    return DummyBloomFilterPerfectShunt<gem5::bloom_filter::Perfect>::create(*this);
}

} // namespace gem5
