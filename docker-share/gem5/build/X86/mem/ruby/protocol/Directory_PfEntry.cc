/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   /shared/gem5/src/mem/slicc/symbols/Type.py:501
 */

#include <iostream>
#include <memory>

#include "mem/ruby/protocol/Directory_PfEntry.hh"
#include "mem/ruby/system/RubySystem.hh"

namespace gem5
{

namespace ruby
{

/** \brief Print the state of this object */
void
Directory_PfEntry::print(std::ostream& out) const
{
    out << "[Directory_PfEntry: ";
    out << "PfState = " << m_PfState << " ";
    out << "Owner = " << m_Owner << " ";
    out << "Sharers = " << m_Sharers << " ";
    out << "]";
}
} // namespace ruby
} // namespace gem5