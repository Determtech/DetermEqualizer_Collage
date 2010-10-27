
/* Copyright (c) 2007-2010, Stefan Eilemann <eile@equalizergraphics.com> 
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 2.1 as published
 * by the Free Software Foundation.
 *  
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef EQNET_NULLCM_H
#define EQNET_NULLCM_H

#include <eq/net/objectCM.h> // base class
#include <eq/net/version.h>  // used enum
#include <eq/base/idPool.h>  // for EQ_ID_INVALID

namespace eq
{
namespace net
{
    class Node;

    /** 
     * The NOP object change manager for unmapped objects.
     * @internal
     */
    class NullCM : public ObjectCM
    {
    public:
        NullCM() {}
        virtual ~NullCM() {}

        virtual void init() {}

        /**
         * @name Versioning
         */
        //@{
        virtual uint32_t commitNB() { EQDONTCALL; return EQ_ID_INVALID; }
        virtual uint32_t commitSync( const uint32_t )
            { EQDONTCALL; return VERSION_NONE; }

        virtual void setAutoObsolete( const uint32_t ) { EQDONTCALL; }
        virtual uint32_t getAutoObsolete() const { EQDONTCALL; return 0; }

        virtual uint32_t sync( const uint32_t )
            { EQDONTCALL; return VERSION_NONE; }

        virtual uint32_t getHeadVersion() const   { return VERSION_NONE; }
        virtual uint32_t getVersion() const       { return VERSION_NONE; }
        virtual uint32_t getOldestVersion() const { return VERSION_NONE; }
        //@}

        virtual bool isMaster() const { return false; }
        virtual uint32_t getMasterInstanceID() const
            { EQDONTCALL; return EQ_ID_INVALID; }

        virtual uint32_t addSlave( Command& )
            { EQDONTCALL; return VERSION_INVALID; }
        virtual void removeSlave( NodePtr ) { EQDONTCALL; }

        virtual void applyMapData( const uint32_t version ) { EQDONTCALL; }

    private:
    };
}
}

#endif // EQNET_NULLCM_H
