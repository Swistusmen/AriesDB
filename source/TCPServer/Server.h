#pragma once
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <thread>
#include <optional>
#include <array>
#include <condition_variable>

//for one thread only, no objects program version

class Server;

using boost::asio::ip::tcp;

class tcpConnection: public boost::enable_shared_from_this<tcpConnection>
{
public:
    typedef boost::shared_ptr<tcpConnection> pointer;

    static pointer createTCPConnection(boost::asio::io_context&io, Server& _server)
    {
        return pointer(new tcpConnection(io, _server));
    }

    tcp::socket& getSocket(){return socket;};

    void start();

private:
    tcpConnection(boost::asio::io_context& io, Server& _server);

    void handle_write(const boost::system::error_code& /*error*/,
      size_t /*bytes_transferred*/){}

      void handle_read(const boost::system::error_code& /*error*/,
      size_t /*bytes_transferred*/){}

private:
    tcp::socket socket;
    Server& server;
};

class tcpServer{
public:
    tcpServer(boost::asio::io_context& _context, const int _port, Server& _server);

private:
    void accept_connections();

    void handle_accept(tcpConnection::pointer connection);

private:
    boost::asio::io_context& context;
    tcp::acceptor acceptor;
    const int port;
    Server& server;
};

class Server{
    public:
        Server(const int _port);
        ~Server();

        void run();
        void setResponse(const std::string& );
        std::optional<std::string> waitForRequest();

        void aquisitRequest(std::string request);
        std::string waitUntilRequestProcessed();

        void refresh();
    private:
        boost::asio::io_context io_context;
        std::unique_ptr<tcpServer> server;
        const int port;
        std::thread communicationThread;
        std::array<std::string,2> requestResponse {"",""};

    private:
        void communication();
};