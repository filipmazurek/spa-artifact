/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   /shared/gem5/src/mem/slicc/symbols/Type.py:501
 */

#include <iostream>
#include <memory>

#include "mem/ruby/protocol/ResponseMsg.hh"
#include "mem/ruby/system/RubySystem.hh"

namespace gem5
{

namespace ruby
{

/** \brief Print the state of this object */
void
ResponseMsg::print(std::ostream& out) const
{
    out << "[ResponseMsg: ";
    out << "addr = " << printAddress(m_addr) << " ";
    out << "Type = " << m_Type << " ";
    out << "Sender = " << m_Sender << " ";
    out << "CurOwner = " << m_CurOwner << " ";
    out << "Destination = " << m_Destination << " ";
    out << "DataBlk = " << m_DataBlk << " ";
    out << "Dirty = " << m_Dirty << " ";
    out << "Acks = " << m_Acks << " ";
    out << "MessageSize = " << m_MessageSize << " ";
    out << "InitialRequestTime = " << m_InitialRequestTime << " ";
    out << "ForwardRequestTime = " << m_ForwardRequestTime << " ";
    out << "SilentAcks = " << m_SilentAcks << " ";
    out << "]";
}
bool
ResponseMsg::functionalRead(Packet* param_pkt)
{
    if ((((((m_Type == CoherenceResponseType_DATA) || (m_Type == CoherenceResponseType_DATA_SHARED)) || (m_Type == CoherenceResponseType_DATA_EXCLUSIVE)) || (m_Type == CoherenceResponseType_WB_DIRTY)) || (m_Type == CoherenceResponseType_WB_EXCLUSIVE_DIRTY))) {
        return (testAndRead(m_addr, m_DataBlk, param_pkt));
    }
    return (false);

}
bool
ResponseMsg::functionalWrite(Packet* param_pkt)
{
return (testAndWrite(m_addr, m_DataBlk, param_pkt));

}
} // namespace ruby
} // namespace gem5
