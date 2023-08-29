/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_cc.py:297
 */

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include <type_traits>

#include "base/compiler.hh"
#include "params/BIPRP.hh"
#include "sim/init.hh"
#include "sim/sim_object.hh"

#include "mem/cache/replacement_policies/bip_rp.hh"

#include "base/types.hh"
namespace py = pybind11;

namespace gem5
{

static void
module_init(py::module_ &m_internal)
{
py::module_ m = m_internal.def_submodule("param_BIPRP");
    py::class_<BIPRPParams, LRURPParams, std::unique_ptr<BIPRPParams, py::nodelete>>(m, "BIPRPParams")
        .def(py::init<>())
        .def("create", &BIPRPParams::create)
        .def_readwrite("btp", &BIPRPParams::btp)
        ;

    py::class_<gem5::replacement_policy::BIP, gem5::replacement_policy::LRU, std::unique_ptr<gem5::replacement_policy::BIP, py::nodelete>>(m, "gem5_COLONS_replacement_policy_COLONS_BIP")
        ;

}

static EmbeddedPyBind embed_obj("BIPRP", module_init, "LRURP");

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
class DummyBIPRPParamsClass
{
  public:
    gem5::replacement_policy::BIP *create() const;
};

template <class CxxClass, class Enable=void>
class DummyBIPRPShunt;

/*
 * This version directs to the real Params struct and the
 * default behavior of create if there's an appropriate
 * constructor.
 */
template <class CxxClass>
class DummyBIPRPShunt<CxxClass, std::enable_if_t<
    std::is_constructible_v<CxxClass, const BIPRPParams &>>>
{
  public:
    using Params = BIPRPParams;
    static gem5::replacement_policy::BIP *
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
class DummyBIPRPShunt<CxxClass, std::enable_if_t<
    !std::is_constructible_v<CxxClass, const BIPRPParams &>>>
{
  public:
    using Params = DummyBIPRPParamsClass;
    static gem5::replacement_policy::BIP *
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
[[maybe_unused]] gem5::replacement_policy::BIP *
DummyBIPRPShunt<gem5::replacement_policy::BIP>::Params::create() const
{
    return DummyBIPRPShunt<gem5::replacement_policy::BIP>::create(*this);
}

} // namespace gem5
