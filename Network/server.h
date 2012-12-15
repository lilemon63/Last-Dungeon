#ifndef SERVER_H
#define SERVER_H

#include<boost/asio.hpp>
#include <boost/bind.hpp>

#include <boost/thread.hpp>

namespace Network
{
    class Server
    {
    public:
        Server(unsigned int port);

        ~Server(void);

        boost::asio::ip::tcp::endpoint getEndPoint(const std::string host, const std::string port);

        boost::asio::ip::tcp::socket * getNewSocket(void);

       void m_run(unsigned int port);

    private :

        inline void start(void);

        /** @brief The unique io_service of the programm */
        boost::asio::io_service io_service;

        /** @brief accept connection */
        boost::asio::ip::tcp::acceptor accept;

        /** @brief Server thread */
        boost::thread * m_thread;

        /** @brief handle intrance connection */
        void handleAccept(boost::asio::ip::tcp::socket * socket, const boost::system::error_code & error);
    };


    void Server::start(void)
    {
        boost::asio::ip::tcp::socket * socket = new boost::asio::ip::tcp::socket(io_service);
        accept.async_accept( *socket , boost::bind(&Server::handleAccept, this, socket, boost::asio::placeholders::error) );
    }
}

#endif // SERVER_H
