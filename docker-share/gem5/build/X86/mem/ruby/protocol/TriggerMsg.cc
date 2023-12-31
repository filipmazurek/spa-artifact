/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   /shared/gem5/src/mem/slicc/symbols/Type.py:501
 */

#include <iostream>
#include <memory>

#include "mem/ruby/protocol/TriggerMsg.hh"
#include "mem/ruby/system/RubySystem.hh"

namespace gem5
{

namespace ruby
{

/** \brief Print the state of this object */
void
TriggerMsg::print(std::ostream& out) const
{
    out << "[TriggerMsg: ";
    out << "addr = " << printAddress(m_addr) << " ";
    out << "Type = " << m_Type << " ";
    out << "]";
}
bool
TriggerMsg::functionalRead(Packet* param_pkt)
{
return (false);

}
bool
TriggerMsg::functionalWrite(Packet* param_pkt)
{
return (false);

}
} // namespace ruby
} // namespace gem5
