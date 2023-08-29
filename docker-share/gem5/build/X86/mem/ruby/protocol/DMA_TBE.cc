/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   /shared/gem5/src/mem/slicc/symbols/Type.py:501
 */

#include <iostream>
#include <memory>

#include "mem/ruby/protocol/DMA_TBE.hh"
#include "mem/ruby/system/RubySystem.hh"

namespace gem5
{

namespace ruby
{

/** \brief Print the state of this object */
void
DMA_TBE::print(std::ostream& out) const
{
    out << "[DMA_TBE: ";
    out << "TBEState = " << m_TBEState << " ";
    out << "DataBlk = " << m_DataBlk << " ";
    out << "]";
}
} // namespace ruby
} // namespace gem5
