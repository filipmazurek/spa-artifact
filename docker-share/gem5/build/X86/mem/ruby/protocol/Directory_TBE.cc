/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   /shared/gem5/src/mem/slicc/symbols/Type.py:501
 */

#include <iostream>
#include <memory>

#include "mem/ruby/protocol/Directory_TBE.hh"
#include "mem/ruby/system/RubySystem.hh"

namespace gem5
{

namespace ruby
{

/** \brief Print the state of this object */
void
Directory_TBE::print(std::ostream& out) const
{
    out << "[Directory_TBE: ";
    out << "PhysicalAddress = " << printAddress(m_PhysicalAddress) << " ";
    out << "TBEState = " << m_TBEState << " ";
    out << "ResponseType = " << m_ResponseType << " ";
    out << "Acks = " << m_Acks << " ";
    out << "SilentAcks = " << m_SilentAcks << " ";
    out << "DmaDataBlk = " << m_DmaDataBlk << " ";
    out << "DataBlk = " << m_DataBlk << " ";
    out << "Len = " << m_Len << " ";
    out << "DmaRequestor = " << m_DmaRequestor << " ";
    out << "GetSRequestors = " << m_GetSRequestors << " ";
    out << "NumPendingMsgs = " << m_NumPendingMsgs << " ";
    out << "CacheDirty = " << m_CacheDirty << " ";
    out << "Sharers = " << m_Sharers << " ";
    out << "Owned = " << m_Owned << " ";
    out << "]";
}
} // namespace ruby
} // namespace gem5
