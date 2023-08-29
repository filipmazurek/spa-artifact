/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   /shared/gem5/src/mem/slicc/symbols/Type.py:443
 */

#ifndef __RequestMsg_HH__
#define __RequestMsg_HH__

#include <iostream>

#include "mem/ruby/slicc_interface/RubySlicc_Util.hh"

#include "mem/ruby/protocol/CoherenceRequestType.hh"
#include "mem/ruby/protocol/MachineID.hh"
#include "mem/ruby/protocol/NetDest.hh"
#include "mem/ruby/protocol/NetDest.hh"
#include "mem/ruby/protocol/MessageSizeType.hh"
#include "mem/ruby/protocol/Message.hh"
namespace gem5
{

namespace ruby
{

class RequestMsg :  public Message
{
  public:
    RequestMsg
(Tick curTime) : Message(curTime) {
        // m_addr has no default
        m_Type = CoherenceRequestType_NUM;
         // default value of CoherenceRequestType
        // m_Requestor has no default
        // m_MergedRequestors has no default
        // m_Destination has no default
        m_MessageSize = MessageSizeType_NUM;
         // default value of MessageSizeType
        m_DirectedProbe = false; // default for this field
        m_InitialRequestTime = Cycles(0); // default for this field
        m_ForwardRequestTime = Cycles(0); // default for this field
        m_SilentAcks = 0; // default for this field
    }
    RequestMsg(const RequestMsg&) = default;
    RequestMsg
    &operator=(const RequestMsg&) = default;
    RequestMsg(const Tick curTime, const Addr& local_addr, const CoherenceRequestType& local_Type, const MachineID& local_Requestor, const NetDest& local_MergedRequestors, const NetDest& local_Destination, const MessageSizeType& local_MessageSize, const bool& local_DirectedProbe, const Cycles& local_InitialRequestTime, const Cycles& local_ForwardRequestTime, const int& local_SilentAcks)
        : Message(curTime)
    {
        m_addr = local_addr;
        m_Type = local_Type;
        m_Requestor = local_Requestor;
        m_MergedRequestors = local_MergedRequestors;
        m_Destination = local_Destination;
        m_MessageSize = local_MessageSize;
        m_DirectedProbe = local_DirectedProbe;
        m_InitialRequestTime = local_InitialRequestTime;
        m_ForwardRequestTime = local_ForwardRequestTime;
        m_SilentAcks = local_SilentAcks;
    }
    MsgPtr
    clone() const
    {
         return std::shared_ptr<Message>(new RequestMsg(*this));
    }
    // Const accessors methods for each field
    /** \brief Const accessor method for addr field.
     *  \return addr field
     */
    const Addr&
    getaddr() const
    {
        return m_addr;
    }
    /** \brief Const accessor method for Type field.
     *  \return Type field
     */
    const CoherenceRequestType&
    getType() const
    {
        return m_Type;
    }
    /** \brief Const accessor method for Requestor field.
     *  \return Requestor field
     */
    const MachineID&
    getRequestor() const
    {
        return m_Requestor;
    }
    /** \brief Const accessor method for MergedRequestors field.
     *  \return MergedRequestors field
     */
    const NetDest&
    getMergedRequestors() const
    {
        return m_MergedRequestors;
    }
    /** \brief Const accessor method for Destination field.
     *  \return Destination field
     */
    const NetDest&
    getDestination() const
    {
        return m_Destination;
    }
    /** \brief Const accessor method for MessageSize field.
     *  \return MessageSize field
     */
    const MessageSizeType&
    getMessageSize() const
    {
        return m_MessageSize;
    }
    /** \brief Const accessor method for DirectedProbe field.
     *  \return DirectedProbe field
     */
    const bool&
    getDirectedProbe() const
    {
        return m_DirectedProbe;
    }
    /** \brief Const accessor method for InitialRequestTime field.
     *  \return InitialRequestTime field
     */
    const Cycles&
    getInitialRequestTime() const
    {
        return m_InitialRequestTime;
    }
    /** \brief Const accessor method for ForwardRequestTime field.
     *  \return ForwardRequestTime field
     */
    const Cycles&
    getForwardRequestTime() const
    {
        return m_ForwardRequestTime;
    }
    /** \brief Const accessor method for SilentAcks field.
     *  \return SilentAcks field
     */
    const int&
    getSilentAcks() const
    {
        return m_SilentAcks;
    }
    // Non const Accessors methods for each field
    /** \brief Non-const accessor method for addr field.
     *  \return addr field
     */
    Addr&
    getaddr()
    {
        return m_addr;
    }
    /** \brief Non-const accessor method for Type field.
     *  \return Type field
     */
    CoherenceRequestType&
    getType()
    {
        return m_Type;
    }
    /** \brief Non-const accessor method for Requestor field.
     *  \return Requestor field
     */
    MachineID&
    getRequestor()
    {
        return m_Requestor;
    }
    /** \brief Non-const accessor method for MergedRequestors field.
     *  \return MergedRequestors field
     */
    NetDest&
    getMergedRequestors()
    {
        return m_MergedRequestors;
    }
    /** \brief Non-const accessor method for Destination field.
     *  \return Destination field
     */
    NetDest&
    getDestination()
    {
        return m_Destination;
    }
    /** \brief Non-const accessor method for MessageSize field.
     *  \return MessageSize field
     */
    MessageSizeType&
    getMessageSize()
    {
        return m_MessageSize;
    }
    /** \brief Non-const accessor method for DirectedProbe field.
     *  \return DirectedProbe field
     */
    bool&
    getDirectedProbe()
    {
        return m_DirectedProbe;
    }
    /** \brief Non-const accessor method for InitialRequestTime field.
     *  \return InitialRequestTime field
     */
    Cycles&
    getInitialRequestTime()
    {
        return m_InitialRequestTime;
    }
    /** \brief Non-const accessor method for ForwardRequestTime field.
     *  \return ForwardRequestTime field
     */
    Cycles&
    getForwardRequestTime()
    {
        return m_ForwardRequestTime;
    }
    /** \brief Non-const accessor method for SilentAcks field.
     *  \return SilentAcks field
     */
    int&
    getSilentAcks()
    {
        return m_SilentAcks;
    }
    // Mutator methods for each field
    /** \brief Mutator method for addr field */
    void
    setaddr(const Addr& local_addr)
    {
        m_addr = local_addr;
    }
    /** \brief Mutator method for Type field */
    void
    setType(const CoherenceRequestType& local_Type)
    {
        m_Type = local_Type;
    }
    /** \brief Mutator method for Requestor field */
    void
    setRequestor(const MachineID& local_Requestor)
    {
        m_Requestor = local_Requestor;
    }
    /** \brief Mutator method for MergedRequestors field */
    void
    setMergedRequestors(const NetDest& local_MergedRequestors)
    {
        m_MergedRequestors = local_MergedRequestors;
    }
    /** \brief Mutator method for Destination field */
    void
    setDestination(const NetDest& local_Destination)
    {
        m_Destination = local_Destination;
    }
    /** \brief Mutator method for MessageSize field */
    void
    setMessageSize(const MessageSizeType& local_MessageSize)
    {
        m_MessageSize = local_MessageSize;
    }
    /** \brief Mutator method for DirectedProbe field */
    void
    setDirectedProbe(const bool& local_DirectedProbe)
    {
        m_DirectedProbe = local_DirectedProbe;
    }
    /** \brief Mutator method for InitialRequestTime field */
    void
    setInitialRequestTime(const Cycles& local_InitialRequestTime)
    {
        m_InitialRequestTime = local_InitialRequestTime;
    }
    /** \brief Mutator method for ForwardRequestTime field */
    void
    setForwardRequestTime(const Cycles& local_ForwardRequestTime)
    {
        m_ForwardRequestTime = local_ForwardRequestTime;
    }
    /** \brief Mutator method for SilentAcks field */
    void
    setSilentAcks(const int& local_SilentAcks)
    {
        m_SilentAcks = local_SilentAcks;
    }
    void print(std::ostream& out) const;
  //private:
    /** Physical address for this request */
    Addr m_addr;
    /** Type of request (GetS, GetX, PutX, etc) */
    CoherenceRequestType m_Type;
    /** Node who initiated the request */
    MachineID m_Requestor;
    /** Merge set of read requestors */
    NetDest m_MergedRequestors;
    /** Multicast destination mask */
    NetDest m_Destination;
    /** size category of the message */
    MessageSizeType m_MessageSize;
    /** probe filter directed probe */
    bool m_DirectedProbe;
    /** time the initial requests was sent from the L1Cache */
    Cycles m_InitialRequestTime;
    /** time the dir forwarded the request */
    Cycles m_ForwardRequestTime;
    /** silent acks from the full-bit directory */
    int m_SilentAcks;
    bool functionalRead(Packet* param_pkt);
    bool functionalWrite(Packet* param_pkt);
};
inline ::std::ostream&
operator<<(::std::ostream& out, const RequestMsg& obj)
{
    obj.print(out);
    out << ::std::flush;
    return out;
}

} // namespace ruby
} // namespace gem5

#endif // __RequestMsg_HH__