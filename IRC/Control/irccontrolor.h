#ifndef IRCCONTROLOR_H
#define IRCCONTROLOR_H

#include<string>
#include <list>
#include "../../Network/server.h"

namespace IRC
{
    class IRCServer;
    class IRCClient;
    class IRCExternHandle;

    /** @brief TODO : auto-complétation */

    class IRCControlor
    {
    public:
        IRCControlor(const std::string & configFile, Network::Server & server, IRCClient * vue);
        void handle(std::string);
        void handleRead(std::string & data, const boost::system::error_code& error, size_t bytesT, IRCServer * s);
        void setHandle(IRCExternHandle *);
    private :
        std::list<IRCServer *> server;
        std::string realName;
        std::string userHost;
        Network::Server & m_server;
        IRCClient * m_vue;
        IRCExternHandle * m_externHandle;

    };
}

#endif // IRCCONTROLOR_H
