#include "ircserver.h"
#include "irccontrolor.h"

#include<boost/bind.hpp>
#include<boost/asio.hpp>
#include<stdio.h>
#include <iostream>
#include <stdio.h>

namespace IRC
{
    IRCServer::IRCServer(IRCControlor * server, Network::Server & _server) : server(_server), m_control(server), socket(NULL)
    {

    }


    Ifstream & operator>>(Ifstream & in, IRCServer & t)
    {
        std::cerr << "fin" << std::endl;
        in >> t.name;
        std::cerr << "tname" << t.name << std::endl;
        in >> t.hostname >> t.port >> t.nick;
        std::cerr << t.hostname << ":" << t.port << std::endl;

        return in;
    }

    void IRCServer::openConnexion(void)
    {
        //resolver
        socket = server.getNewSocket();
        boost::system::error_code er;

        socket->connect( server.getEndPoint(hostname, port) , er);
        if( er )
        {
            std::cerr << "-" <<  er.message() << "-" << std::endl;
            //what to do ?
        }
        else
            start();

        //start();
    }

    void IRCServer::closeConnexion(void)
    {
        //....
    }

    void IRCServer::sendMessage(const std::string & mess)
    {
        socket->async_write_some(boost::asio::buffer(mess), boost::bind(&IRCServer::receive, this,
                                                                   boost::asio::placeholders::error,
                                                                   boost::asio::placeholders::bytes_transferred) );
    }

    void IRCServer::receive(const boost::system::error_code & err, size_t)
    {
        fprintf(stderr, "ttt");
    }

    void IRCServer::start(void)
    {
        std::cerr << "fin" << std::endl;
        socket->async_receive(boost::asio::buffer(data, TAILLE_MAX), boost::bind(&IRCServer::handleRead,
                                                  this, boost::asio::placeholders::error,
                                                  boost::asio::placeholders::bytes_transferred) );
        /*
       async_read_until(*socket,
                         data,
                         '\n',
                         boost::bind(&IRCServer::handleRead,
                                     this, boost::asio::placeholders::error,
                                     boost::asio::placeholders::bytes_transferred));*/
    }

    void IRCServer::handleRead(const boost::system::error_code& error, size_t bytesT)
    {
        message.append(data, bytesT);
        std::cerr << "mess err :" << error.message() << std::endl;
        //std::istream is( &data );
        if( error )
            std::cerr << "Error when read data" << std::endl; //what to do ?
        else
        {
            m_control->handleRead( message , error, bytesT, this);
            start();
        }
    }

    void IRCServer::openConnexion(const std::string & name, const std::string & hote, const std::string & port)
    {
        hostname = hote;
        this->name = name;
        this->port = port;
        openConnexion();
    }
}
