
/* Copyright (c) 2005-2006, Stefan Eilemann <eile@equalizergraphics.com> 
   All rights reserved. */

#ifndef EQNET_CONNECTION_H
#define EQNET_CONNECTION_H

#include "packets.h"

#include <eq/base/base.h>
#include <eq/base/referenced.h>
#include <eq/base/refPtr.h>

#include <poll.h>
#include <stdexcept>
#include <vector>

namespace eqNet
{
    class ConnectionDescription;

#   define DEFAULT_PORT 4242

    /**
     * A base class to provide communication to other hosts.
     */
    class Connection : public eqBase::Referenced
    {
    public:

        /** The supported network protocols. */
        enum Type
        {
            TYPE_TCPIP,   //!< TCP/IP networking.
            TYPE_PIPE,    //!< pipe() based bi-directional connection
            TYPE_UNI_PIPE //!< pipe() based uni-directional connection
        };

        enum State {
            STATE_CLOSED,
            STATE_CONNECTING,
            STATE_CONNECTED,
            STATE_LISTENING
        };

        /** 
         * Creates a new connection.
         *
         * This factory method creates a new concrete connection for the
         * requested type. The concrete connection may not support all
         * functionality of the Connection interface.
         * 
         * @param type the connection type.
         * @return the connection.
         */
        static eqBase::RefPtr<Connection> create( const Type type );
        
        /** @name Connection Management */
        //@{
        /** 
         * Connect the connection.
         *
         * @return <code>true</code> if the connection was successfully
         *         connected, <code>false</code> if not.
         */
        virtual bool connect()
            { return false; }
        
        /** 
         * Put the connection into the listening state for a new incoming
         * connection.
         *
         * @return <code>true</code> if the connection is listening for new
         *         incoming connections, <code>false</code> if not.
         */
        virtual bool listen()
            { return false; }

        /** 
         * Accepts the next incoming connection.
         * 
         * @return the accepted connection, or <code>NULL</code> if no
         *         connection was accepted.
         */
        virtual eqBase::RefPtr<Connection> accept(){ return NULL; }

        /** 
         * Accepts the next incoming connection with a timeout.
         * 
         * @param timeout the amount of time to wait in milliseconds, if set
         *                to <code>-1</code> the method blocks indefinitely.
         * @return the accepted connection, or <code>NULL</code> if no
         *         connection was accepted.
         */
        virtual eqBase::RefPtr<Connection> accept( const int timeout );
        
        virtual void close(){};
        //@}

        /** @name Messaging API */
        //@{
        /** 
         * Reads a message from the connection.
         * 
         * @param buffer the buffer for saving the message.
         * @param bytes the number of bytes to read.
         * @return the number of bytes received.
         */
        virtual uint64_t recv( const void* buffer, const uint64_t bytes )
            {return 0;}

        /** 
         * Sends a message using the connection.
         * 
         * @param buffer the buffer containing the message.
         * @param bytes the number of bytes to send.
         * @return the number of bytes send.
         */
        virtual uint64_t send( const void* buffer, const uint64_t bytes) const
            {return 0;}

        /** 
         * Sends a packaged message using the connection.
         * 
         * @param packet the message packet.
         * @return the number of bytes send.
         */
        uint64_t send( const Packet &packet ) const
            {return send( &packet, packet.size); }

        /** 
         * Sends a packaged message including a string using the connection.
         * 
         * @param packet the message packet.
         * @param string the string.
         * @return the number of bytes send.
         * @sa Node::send
         */
        uint64_t send( Packet &packet, const std::string& string ) const
            { return send( packet, string.c_str(), string.size()+1 ); }

        /** 
         * Sends a packaged message including the data.
         * 
         * @param packet the message packet.
         * @param data the vector containing the data.
         * @return the number of bytes send.
         * @sa Node::send
         */
        template< class T >
        uint64_t send( Packet &packet, const std::vector<T>& data ) const;

        /** 
         * Sends a packaged message including additional data using the
         * connection.
         * 
         * @param packet the message packet.
         * @param data the data.
         * @param size the data size in bytes.
         * @return the number of bytes send.
         * @sa Node::send
         */
        uint64_t send( Packet& packet, const void* data, const uint64_t size )
            const;
        //@}

        /** 
         * Returns the state of this connection.
         * 
         * @return the state of this connection.
         */
        State getState() const { return _state; }

        /** 
         * Set the connection's description.
         * 
         * @param description the connection parameters.
         */
        void setDescription( eqBase::RefPtr<ConnectionDescription> description);

        /** @return the description for this connection. */
        eqBase::RefPtr<ConnectionDescription> getDescription();

        virtual int getReadFD() const { return -1; }

    protected:
        Connection();
        Connection(const Connection& conn);
        virtual ~Connection();

        State                                 _state; //!< The connection state
        eqBase::RefPtr<ConnectionDescription> _description;
    };

    inline std::ostream& operator << ( std::ostream& os, 
                                       const Connection* connection )
    {
        if( !connection )
        {
            os << "NULL connection";
            return os;
        }

        Connection::State state = connection->getState();
        
        os << "Connection " << (void*)connection << " type "
           << typeid(*connection).name() << " state "
           << ( state == Connection::STATE_CLOSED     ? "closed" :
                state == Connection::STATE_CONNECTING ? "connecting" :
                state == Connection::STATE_CONNECTED  ? "connected" :
                state == Connection::STATE_LISTENING  ? "listening" :
                "unknown state");
        return os;
    }

#   include "connection.ipp" // template implementation
}
#endif //EQNET_CONNECTION_H
