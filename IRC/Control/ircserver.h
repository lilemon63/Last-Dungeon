#ifndef IRCSERVER_H
#define IRCSERVER_H

const int TAILLE_MAX = 200; //TODO taille max ligne envoyée

#include "../../ifstream.h"
#include "../../Network/server.h"
#include <string>
#include <boost/asio.hpp>

namespace IRC
{
    class IRCServer;
    class IRCControlor;
    Ifstream & operator>>(Ifstream & in, IRCServer & t);

    class IRCServer
    {
    public:
        IRCServer( IRCControlor * server, Network::Server & _server);
        void openConnexion(void);
        void openConnexion(const std::string & name, const std::string & hote, const std::string & port);
        void sendMessage(const std::string &);
        void closeConnexion(void);
        void start(void);
    private :
        Network::Server & server;
        IRCControlor * m_control;
        friend Ifstream & operator>>(Ifstream & in, IRCServer & t);
        std::string name;
        std::string hostname;
        std::string port;
        std::string nick;
        std::string message;
        char data[TAILLE_MAX];
        boost::asio::ip::tcp::socket * socket;
        void receive(const boost::system::error_code &, size_t);
        void handleRead(const boost::system::error_code& error, size_t bytesT);
    };
}



#endif // IRCSERVER_H
