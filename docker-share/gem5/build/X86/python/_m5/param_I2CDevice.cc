/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_cc.py:297
 */

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include <type_traits>

#include "base/compiler.hh"
#include "params/I2CDevice.hh"
#include "sim/init.hh"
#include "sim/sim_object.hh"

#include "dev/i2c/device.hh"

#include "base/types.hh"
namespace py = pybind11;

namespace gem5
{

static void
module_init(py::module_ &m_internal)
{
py::module_ m = m_internal.def_submodule("param_I2CDevice");
    py::class_<I2CDeviceParams, SimObjectParams, std::unique_ptr<I2CDeviceParams, py::nodelete>>(m, "I2CDeviceParams")
        .def_readwrite("i2c_addr", &I2CDeviceParams::i2c_addr)
        ;

    py::class_<gem5::I2CDevice, gem5::SimObject, std::unique_ptr<gem5::I2CDevice, py::nodelete>>(m, "gem5_COLONS_I2CDevice")
        ;

}

static EmbeddedPyBind embed_obj("I2CDevice", module_init, "SimObject");

} // namespace gem5
