/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   /shared/gem5/src/mem/slicc/symbols/Type.py:935
 */

#include <cassert>
#include <iostream>
#include <string>

#include "base/logging.hh"
#include "mem/ruby/protocol/RubyRequestType.hh"

namespace gem5
{

namespace ruby
{

// Code for output operator
::std::ostream&
operator<<(::std::ostream& out, const RubyRequestType& obj)
{
    out << RubyRequestType_to_string(obj);
    out << ::std::flush;
    return out;
}

// Code to convert state to a string
std::string
RubyRequestType_to_string(const RubyRequestType& obj)
{
    switch(obj) {
      case RubyRequestType_LD:
        return "LD";
      case RubyRequestType_ST:
        return "ST";
      case RubyRequestType_ATOMIC:
        return "ATOMIC";
      case RubyRequestType_ATOMIC_RETURN:
        return "ATOMIC_RETURN";
      case RubyRequestType_ATOMIC_NO_RETURN:
        return "ATOMIC_NO_RETURN";
      case RubyRequestType_IFETCH:
        return "IFETCH";
      case RubyRequestType_IO:
        return "IO";
      case RubyRequestType_REPLACEMENT:
        return "REPLACEMENT";
      case RubyRequestType_Load_Linked:
        return "Load_Linked";
      case RubyRequestType_Store_Conditional:
        return "Store_Conditional";
      case RubyRequestType_RMW_Read:
        return "RMW_Read";
      case RubyRequestType_RMW_Write:
        return "RMW_Write";
      case RubyRequestType_Locked_RMW_Read:
        return "Locked_RMW_Read";
      case RubyRequestType_Locked_RMW_Write:
        return "Locked_RMW_Write";
      case RubyRequestType_COMMIT:
        return "COMMIT";
      case RubyRequestType_NULL:
        return "NULL";
      case RubyRequestType_FLUSH:
        return "FLUSH";
      case RubyRequestType_Release:
        return "Release";
      case RubyRequestType_Acquire:
        return "Acquire";
      case RubyRequestType_AcquireRelease:
        return "AcquireRelease";
      case RubyRequestType_HTM_Start:
        return "HTM_Start";
      case RubyRequestType_HTM_Commit:
        return "HTM_Commit";
      case RubyRequestType_HTM_Cancel:
        return "HTM_Cancel";
      case RubyRequestType_HTM_Abort:
        return "HTM_Abort";
      case RubyRequestType_TLBI:
        return "TLBI";
      case RubyRequestType_TLBI_SYNC:
        return "TLBI_SYNC";
      case RubyRequestType_TLBI_EXT_SYNC:
        return "TLBI_EXT_SYNC";
      case RubyRequestType_TLBI_EXT_SYNC_COMP:
        return "TLBI_EXT_SYNC_COMP";
      default:
        panic("Invalid range for type RubyRequestType");
    }
    // Appease the compiler since this function has a return value
    return "";
}

// Code to convert from a string to the enumeration
RubyRequestType
string_to_RubyRequestType(const std::string& str)
{
    if (str == "LD") {
        return RubyRequestType_LD;
    } else if (str == "ST") {
        return RubyRequestType_ST;
    } else if (str == "ATOMIC") {
        return RubyRequestType_ATOMIC;
    } else if (str == "ATOMIC_RETURN") {
        return RubyRequestType_ATOMIC_RETURN;
    } else if (str == "ATOMIC_NO_RETURN") {
        return RubyRequestType_ATOMIC_NO_RETURN;
    } else if (str == "IFETCH") {
        return RubyRequestType_IFETCH;
    } else if (str == "IO") {
        return RubyRequestType_IO;
    } else if (str == "REPLACEMENT") {
        return RubyRequestType_REPLACEMENT;
    } else if (str == "Load_Linked") {
        return RubyRequestType_Load_Linked;
    } else if (str == "Store_Conditional") {
        return RubyRequestType_Store_Conditional;
    } else if (str == "RMW_Read") {
        return RubyRequestType_RMW_Read;
    } else if (str == "RMW_Write") {
        return RubyRequestType_RMW_Write;
    } else if (str == "Locked_RMW_Read") {
        return RubyRequestType_Locked_RMW_Read;
    } else if (str == "Locked_RMW_Write") {
        return RubyRequestType_Locked_RMW_Write;
    } else if (str == "COMMIT") {
        return RubyRequestType_COMMIT;
    } else if (str == "NULL") {
        return RubyRequestType_NULL;
    } else if (str == "FLUSH") {
        return RubyRequestType_FLUSH;
    } else if (str == "Release") {
        return RubyRequestType_Release;
    } else if (str == "Acquire") {
        return RubyRequestType_Acquire;
    } else if (str == "AcquireRelease") {
        return RubyRequestType_AcquireRelease;
    } else if (str == "HTM_Start") {
        return RubyRequestType_HTM_Start;
    } else if (str == "HTM_Commit") {
        return RubyRequestType_HTM_Commit;
    } else if (str == "HTM_Cancel") {
        return RubyRequestType_HTM_Cancel;
    } else if (str == "HTM_Abort") {
        return RubyRequestType_HTM_Abort;
    } else if (str == "TLBI") {
        return RubyRequestType_TLBI;
    } else if (str == "TLBI_SYNC") {
        return RubyRequestType_TLBI_SYNC;
    } else if (str == "TLBI_EXT_SYNC") {
        return RubyRequestType_TLBI_EXT_SYNC;
    } else if (str == "TLBI_EXT_SYNC_COMP") {
        return RubyRequestType_TLBI_EXT_SYNC_COMP;
    } else {
        panic("Invalid string conversion for %s, type RubyRequestType", str);
    }
}

// Code to increment an enumeration type
RubyRequestType&
operator++(RubyRequestType& e)
{
    assert(e < RubyRequestType_NUM);
    return e = RubyRequestType(e+1);
}
} // namespace ruby
} // namespace gem5