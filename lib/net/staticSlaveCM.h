
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

#ifndef EQNET_STATICSLAVECM_H
#define EQNET_STATICSLAVECM_H

#include <eq/net/objectCM.h>     // base class
#include <eq/net/version.h>      // enum
#include <eq/base/idPool.h>      // for EQ_ID_INVALID

namespace eq
{
namespace net
{
    class Command;
    class Node;
    class ObjectDataIStream;

    /** 
     * An object change manager handling static object slave instances.
     * @internal
     */
    class StaticSlaveCM : public ObjectCM
    {
    public:
        StaticSlaveCM( Object* object );
        virtual ~StaticSlaveCM();

        virtual void init(){}

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

        virtual uint32_t getHeadVersion() const { return VERSION_NONE; }
        virtual uint32_t getVersion() const     { return VERSION_NONE; }
        virtual uint32_t getOldestVersion() const { return VERSION_NONE; }
        //@}

        virtual bool isMaster() const { return false; }
        virtual uint32_t getMasterInstanceID() const { return EQ_ID_INVALID; }

        virtual uint32_t addSlave( Command& )
            { EQDONTCALL; return VERSION_INVALID; }
        virtual void removeSlave( NodePtr ) { EQDONTCALL; }

        virtual void applyMapData( const uint32_t version );
        virtual void addInstanceDatas( const ObjectInstanceDataIStreamDeque&, 
                                       const uint32_t startVersion );
        virtual const Object* getObject( ) const { return _object; }
    protected:
        /** The managed object. */
        Object* _object;

        /** istream for receiving the current version */
        ObjectDataIStream* _currentIStream;

    private:
        /* The command handlers. */
        bool _cmdInstance( Command& command );
    };
}
}

#endif // EQNET_STATICSLAVECM_H
