/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   /shared/gem5/src/mem/slicc/symbols/Type.py:643
 */

#ifndef __L1Cache_State_HH__
#define __L1Cache_State_HH__

#include <iostream>
#include <string>

#include "mem/ruby/protocol/AccessPermission.hh"
namespace gem5
{

namespace ruby
{


// Class definition
/** \enum L1Cache_State
 *  \brief Cache states
 */
enum L1Cache_State {
    L1Cache_State_FIRST,
    L1Cache_State_I = L1Cache_State_FIRST, /**< Idle */
    L1Cache_State_S, /**< Shared */
    L1Cache_State_O, /**< Owned */
    L1Cache_State_M, /**< Modified (dirty) */
    L1Cache_State_MM, /**< Modified (dirty and locally modified) */
    L1Cache_State_IR, /**< Idle */
    L1Cache_State_SR, /**< Shared */
    L1Cache_State_OR, /**< Owned */
    L1Cache_State_MR, /**< Modified (dirty) */
    L1Cache_State_MMR, /**< Modified (dirty and locally modified) */
    L1Cache_State_IM, /**< Issued GetX */
    L1Cache_State_SM, /**< Issued GetX, we still have a valid copy of the line */
    L1Cache_State_OM, /**< Issued GetX, received data */
    L1Cache_State_ISM, /**< Issued GetX, received valid data, waiting for all acks */
    L1Cache_State_M_W, /**< Issued GetS, received exclusive data */
    L1Cache_State_MM_W, /**< Issued GetX, received exclusive data */
    L1Cache_State_IS, /**< Issued GetS */
    L1Cache_State_SS, /**< Issued GetS, received data, waiting for all acks */
    L1Cache_State_OI, /**< Issued PutO, waiting for ack */
    L1Cache_State_MI, /**< Issued PutX, waiting for ack */
    L1Cache_State_II, /**< Issued PutX/O, saw Other_GETS or Other_GETX, waiting for ack */
    L1Cache_State_ST, /**< S block transferring to L1 */
    L1Cache_State_OT, /**< O block transferring to L1 */
    L1Cache_State_MT, /**< M block transferring to L1 */
    L1Cache_State_MMT, /**< MM block transferring to L0 */
    L1Cache_State_MI_F, /**< Issued PutX due to a Flush, waiting for ack */
    L1Cache_State_MM_F, /**< Issued GETF due to a Flush, waiting for ack */
    L1Cache_State_IM_F, /**< Issued GetX due to a Flush */
    L1Cache_State_ISM_F, /**< Issued GetX, received data, waiting for all acks */
    L1Cache_State_SM_F, /**< Issued GetX, we still have an old copy of the line */
    L1Cache_State_OM_F, /**< Issued GetX, received data */
    L1Cache_State_MM_WF, /**< Issued GetX, received exclusive data */
    L1Cache_State_NUM
};

// Code to convert from a string to the enumeration
L1Cache_State string_to_L1Cache_State(const ::std::string& str);

// Code to convert state to a string
::std::string L1Cache_State_to_string(const L1Cache_State& obj);

// Code to increment an enumeration type
L1Cache_State &operator++(L1Cache_State &e);

// Code to convert the current state to an access permission
AccessPermission L1Cache_State_to_permission(const L1Cache_State& obj);


::std::ostream&
operator<<(::std::ostream& out, const L1Cache_State& obj);

} // namespace ruby
} // namespace gem5
#endif // __L1Cache_State_HH__