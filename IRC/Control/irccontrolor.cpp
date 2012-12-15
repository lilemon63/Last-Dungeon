#include "irccontrolor.h"
#include "ircserver.h"
#include "../../ifstream.h"
#include "../Vue/ircclient.h"
#include "IRCExternHandle.h"

#include <stdio.h>

namespace IRC
{
    IRCControlor::IRCControlor(const std::string & configFile, Network::Server & _server, IRCClient *vue)
        : m_server(_server), m_vue(vue), m_externHandle(NULL)
    {
        Ifstream file(configFile);
        //informations générales

        //file >> realName;
        //file >> userHost;

        IRCServer * tmp;
        while( file  )
        {
            tmp = new IRCServer(this, m_server);
            file >> *tmp;
            server.push_back(tmp);

            tmp->openConnexion();
        }

        //start server


        file.close();
    }


    void IRCControlor::handle(std::string mess)
    {
        if(mess[0] == '!')
        {
            mess.erase(0,1);
            if( ! ( m_externHandle && m_externHandle->handle(mess, m_vue) ) )
                m_vue->printMessage( IRCClient::widen("Unknow command " + mess) );
        }

        // if mess[0] == '/'
        std::stringstream is(mess);
        std::string command;
        is >> command;
        if(command == "/server" || command == "/SERVER")
        {
            std::string name, hote, port;
            if( is >> name >> hote >> port )
            {
                IRCServer * tmp = new IRCServer(this, m_server);
                server.push_back( tmp );
                std::cerr << hote << ":" << port << std::endl;
                tmp->openConnexion(name, hote, port);
            }
            else
                ;//error
        }
        else
        {
            mess += "\r\n";
            std::cerr << "sending mess" << mess << std::endl;
            (*server.begin())->sendMessage(mess); // !!! choix du channel
        }
    }

    void IRCControlor::handleRead(std::string & data, const boost::system::error_code&, size_t, IRCServer * s)
    {
        std::cerr << "total paquet : " << data.size() << "\n" << data << std::endl << std::endl;
        std::stringstream in(data);
        IRCClient::LineList l;
        std::string line;
        while( std::getline(in, line ,'\n')   && line[line.size()-1] == '\r')
        {
            std::cerr << "receive data : " << line << std::endl;
            std::string command;
            std::stringstream is(line);
            is >> command;
            if(command == "PING")
            {
                std::string retour;
                is >> retour;
                s->sendMessage("PONG " + retour + "\r\n");
            }
            else
            {
                line.erase(line.end()- 1, line.end() );
                std::cerr << (int)line[line.size() - 1] << std::endl;
                std::cerr << (int)line[line.size() - 2] << std::endl;
                std::cerr << (int)line[line.size() - 3] << std::endl;
                char * c = "é";
                std::cerr << (int)L'à' << std::endl;
                l.push_back(line);
            }
        }
        if( line[line.size()-1] != '\r' )
        {
            data = line;
//            data.sputn(line.c_str(), line.size() );
        }
        std::cerr << "receive data line : " << line << std::endl;
        m_vue->print(l);
    }

    void IRCControlor::setHandle(IRCExternHandle * handle)
    {
        m_externHandle = handle;
    }
}
