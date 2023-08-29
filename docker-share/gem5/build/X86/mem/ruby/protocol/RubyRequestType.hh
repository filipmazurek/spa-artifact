/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   /shared/gem5/src/mem/slicc/symbols/Type.py:643
 */

#ifndef __RubyRequestType_HH__
#define __RubyRequestType_HH__

#include <iostream>
#include <string>

namespace gem5
{

namespace ruby
{


// Class definition
/** \enum RubyRequestType
 *  \brief ...
 */
enum RubyRequestType {
    RubyRequestType_FIRST,
    RubyRequestType_LD = RubyRequestType_FIRST, /**< Load */
    RubyRequestType_ST, /**< Store */
    RubyRequestType_ATOMIC, /**< Atomic Load/Store -- depricated. use ATOMIC_RETURN or ATOMIC_NO_RETURN */
    RubyRequestType_ATOMIC_RETURN, /**< Atomic Load/Store, return data */
    RubyRequestType_ATOMIC_NO_RETURN, /**< Atomic Load/Store, do not return data */
    RubyRequestType_IFETCH, /**< Instruction fetch */
    RubyRequestType_IO, /**< I/O */
    RubyRequestType_REPLACEMENT, /**< Replacement */
    RubyRequestType_Load_Linked, /**<  */
    RubyRequestType_Store_Conditional, /**<  */
    RubyRequestType_RMW_Read, /**<  */
    RubyRequestType_RMW_Write, /**<  */
    RubyRequestType_Locked_RMW_Read, /**<  */
    RubyRequestType_Locked_RMW_Write, /**<  */
    RubyRequestType_COMMIT, /**< Commit version */
    RubyRequestType_NULL, /**< Invalid request type */
    RubyRequestType_FLUSH, /**< Flush request type */
    RubyRequestType_Release, /**< Release operation */
    RubyRequestType_Acquire, /**< Acquire opertion */
    RubyRequestType_AcquireRelease, /**< Acquire and Release opertion */
    RubyRequestType_HTM_Start, /**< hardware memory transaction: begin */
    RubyRequestType_HTM_Commit, /**< hardware memory transaction: commit */
    RubyRequestType_HTM_Cancel, /**< hardware memory transaction: cancel */
    RubyRequestType_HTM_Abort, /**< hardware memory transaction: abort */
    RubyRequestType_TLBI, /**< TLB Invalidation - Initiation */
    RubyRequestType_TLBI_SYNC, /**< TLB Invalidation Sync operation - Potential initiation */
    RubyRequestType_TLBI_EXT_SYNC, /**< TLB Invalidation Sync operation - External Sync has been requested */
    RubyRequestType_TLBI_EXT_SYNC_COMP, /**< TLB Invalidation Sync operation - External Sync has been completed */
    RubyRequestType_NUM
};

// Code to convert from a string to the enumeration
RubyRequestType string_to_RubyRequestType(const ::std::string& str);

// Code to convert state to a string
::std::string RubyRequestType_to_string(const RubyRequestType& obj);

// Code to increment an enumeration type
RubyRequestType &operator++(RubyRequestType &e);

::std::ostream&
operator<<(::std::ostream& out, const RubyRequestType& obj);

} // namespace ruby
} // namespace gem5
#endif // __RubyRequestType_HH__