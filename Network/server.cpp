#include "server.h"


namespace Network
{
    Server::Server(unsigned int port)
        : accept(  io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)  )
    {
        m_thread = new boost::thread(boost::bind(&Server::m_run, this, port));


    }

    void Server::m_run(unsigned int port)
    {
        start();
        //io_service = new boost::asio::io_service;
        //accept = new boost::asio::ip::tcp::acceptor( *io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port) );
        //launch listenner
        io_service.run(); //.poll();
        std::cerr << "finu" << std::endl;
    }

    void  Server::handleAccept(boost::asio::ip::tcp::socket * socket, const boost::system::error_code & error)
    {
        if( ! error )
        {
            std::cerr << "No target for socket" << std::endl; //new Client(socket, false, m_list, m_nbTreatThread, io_service);
            delete socket;
        }
        else
            delete socket;
        start();
    }


    boost::asio::ip::tcp::endpoint Server::getEndPoint(const std::string host, const std::string port)
    {
        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::query query(host, port);
        boost::asio::ip::tcp::resolver::iterator it = resolver.resolve((query));
        boost::asio::ip::tcp::resolver::iterator end;
        if(it != end)
        {
            return *it;
        }
        throw std::runtime_error("host not found");
    }

    boost::asio::ip::tcp::socket * Server::getNewSocket(void)
    {
        return new boost::asio::ip::tcp::socket(io_service);
    }

    Server::~Server(void)
    {
        accept.close();
        io_service.stop();
        m_thread->join();
        delete m_thread;
    }
}
