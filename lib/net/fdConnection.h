
/* Copyright (c) 2005-2007, Stefan Eilemann <eile@equalizergraphics.com> 
   All rights reserved. */

#ifndef EQNET_FD_CONNECTION_H
#define EQNET_FD_CONNECTION_H

#include <eq/net/connection.h>

namespace eqNet
{

    /**
     * A generic file descriptor-based connection, to be subclassed.
     */
    class EQ_EXPORT FDConnection : public Connection
    {
    public:
        virtual int64_t read( void* buffer, const uint64_t bytes );
        virtual int64_t write( const void* buffer, const uint64_t bytes ) const;

#ifndef WIN32
        virtual ReadNotifier getReadNotifier() const { return _readFD; }
#endif

    protected:
        FDConnection();
        FDConnection( const FDConnection& conn );

        int   _readFD;     //!< The read file descriptor.
        int   _writeFD;    //!< The write file descriptor.

        friend inline std::ostream& operator << ( std::ostream& os, 
                                               const FDConnection* connection );
    };

    inline std::ostream& operator << ( std::ostream& os, 
                                       const FDConnection* connection )
    {
        os << (Connection*)connection << " readFD " << connection->_readFD
           << " writeFD " << connection->_writeFD;
        return os;
    }
}

#endif //EQNET_FD_CONNECTION_H
