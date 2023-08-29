/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   /shared/gem5/src/mem/slicc/symbols/Type.py:643
 */

#ifndef __CoherenceResponseType_HH__
#define __CoherenceResponseType_HH__

#include <iostream>
#include <string>

namespace gem5
{

namespace ruby
{


// Class definition
/** \enum CoherenceResponseType
 *  \brief ...
 */
enum CoherenceResponseType {
    CoherenceResponseType_FIRST,
    CoherenceResponseType_ACK = CoherenceResponseType_FIRST, /**< ACKnowledgment, responder does not have a copy */
    CoherenceResponseType_ACK_SHARED, /**< ACKnowledgment, responder has a shared copy */
    CoherenceResponseType_DATA, /**< Data, responder does not have a copy */
    CoherenceResponseType_DATA_SHARED, /**< Data, responder has a shared copy */
    CoherenceResponseType_DATA_EXCLUSIVE, /**< Data, responder was exclusive, gave us a copy, and they went to invalid */
    CoherenceResponseType_WB_CLEAN, /**< Clean writeback */
    CoherenceResponseType_WB_DIRTY, /**< Dirty writeback */
    CoherenceResponseType_WB_EXCLUSIVE_CLEAN, /**< Clean writeback of exclusive data */
    CoherenceResponseType_WB_EXCLUSIVE_DIRTY, /**< Dirty writeback of exclusive data */
    CoherenceResponseType_UNBLOCK, /**< Unblock for writeback */
    CoherenceResponseType_UNBLOCKS, /**< Unblock now in S */
    CoherenceResponseType_UNBLOCKM, /**< Unblock now in M/O/E */
    CoherenceResponseType_NULL, /**< Null value */
    CoherenceResponseType_NUM
};

// Code to convert from a string to the enumeration
CoherenceResponseType string_to_CoherenceResponseType(const ::std::string& str);

// Code to convert state to a string
::std::string CoherenceResponseType_to_string(const CoherenceResponseType& obj);

// Code to increment an enumeration type
CoherenceResponseType &operator++(CoherenceResponseType &e);

::std::ostream&
operator<<(::std::ostream& out, const CoherenceResponseType& obj);

} // namespace ruby
} // namespace gem5
#endif // __CoherenceResponseType_HH__