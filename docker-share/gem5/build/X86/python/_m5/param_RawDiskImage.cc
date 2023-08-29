/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_cc.py:297
 */

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include <type_traits>

#include "base/compiler.hh"
#include "params/RawDiskImage.hh"
#include "sim/init.hh"
#include "sim/sim_object.hh"

#include "dev/storage/disk_image.hh"

namespace py = pybind11;

namespace gem5
{

static void
module_init(py::module_ &m_internal)
{
py::module_ m = m_internal.def_submodule("param_RawDiskImage");
    py::class_<RawDiskImageParams, DiskImageParams, std::unique_ptr<RawDiskImageParams, py::nodelete>>(m, "RawDiskImageParams")
        .def(py::init<>())
        .def("create", &RawDiskImageParams::create)
        ;

    py::class_<gem5::RawDiskImage, gem5::DiskImage, std::unique_ptr<gem5::RawDiskImage, py::nodelete>>(m, "gem5_COLONS_RawDiskImage")
        ;

}

static EmbeddedPyBind embed_obj("RawDiskImage", module_init, "DiskImage");

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
class DummyRawDiskImageParamsClass
{
  public:
    gem5::RawDiskImage *create() const;
};

template <class CxxClass, class Enable=void>
class DummyRawDiskImageShunt;

/*
 * This version directs to the real Params struct and the
 * default behavior of create if there's an appropriate
 * constructor.
 */
template <class CxxClass>
class DummyRawDiskImageShunt<CxxClass, std::enable_if_t<
    std::is_constructible_v<CxxClass, const RawDiskImageParams &>>>
{
  public:
    using Params = RawDiskImageParams;
    static gem5::RawDiskImage *
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
class DummyRawDiskImageShunt<CxxClass, std::enable_if_t<
    !std::is_constructible_v<CxxClass, const RawDiskImageParams &>>>
{
  public:
    using Params = DummyRawDiskImageParamsClass;
    static gem5::RawDiskImage *
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
[[maybe_unused]] gem5::RawDiskImage *
DummyRawDiskImageShunt<gem5::RawDiskImage>::Params::create() const
{
    return DummyRawDiskImageShunt<gem5::RawDiskImage>::create(*this);
}

} // namespace gem5
