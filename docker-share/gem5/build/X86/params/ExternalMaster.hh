/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:235
 */

#ifndef __PARAMS__ExternalMaster__
#define __PARAMS__ExternalMaster__

namespace gem5 {
class ExternalMaster;
} // namespace gem5
#include <cstddef>
#include <string>
#include <cstddef>
#include <string>
#include <cstddef>
#include "params/System.hh"

#include "params/SimObject.hh"

namespace gem5
{
struct ExternalMasterParams
    : public SimObjectParams
{
    gem5::ExternalMaster * create() const;
    std::string port_data;
    std::string port_type;
    gem5::System * system;
    unsigned int port_port_connection_count;
};

} // namespace gem5

#endif // __PARAMS__ExternalMaster__