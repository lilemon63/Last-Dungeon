#ifndef IRCEXTERNHANDLE_H
#define IRCEXTERNHANDLE_H

#include "../Vue/ircclient.h"

namespace IRC
{
    /** @brief Abstract class which is used for process data */
    class IRCExternHandle
    {
    public :
        //virtual bool handle(IRCClient::LineList & list){ return false; }
        virtual bool handle(const std::string & string, IRCClient * chat) = 0;

    };

}

#endif // IRCEXTERNHANDLE_H
