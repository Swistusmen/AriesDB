#include "Server.h"

//tcpConnection

void tcpConnection::start(){
      boost::array<char, 1024> buf;
        boost::asio::async_read(socket,boost::asio::buffer(buf),
          boost::bind(&tcpConnection::handle_read,
          shared_from_this(),
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));

        server.aquisitRequest(buf.data());
        auto message=server.waitUntilRequestProcessed();
        server.refresh();

        boost::asio::async_write(socket,boost::asio::buffer(message),
            boost::bind(&tcpConnection::handle_write, 
            shared_from_this(), 
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

tcpConnection::tcpConnection(boost::asio::io_context& io, Server& _server):socket(io),server(_server){}

//tcpServer

tcpServer::tcpServer(boost::asio::io_context& _context, const int _port, Server & _server):server(_server),context(_context),port(_port),acceptor(context,tcp::endpoint(tcp::v4(),port))
{
    accept_connections();
}

void tcpServer::accept_connections(){
        tcpConnection::pointer connection=tcpConnection::createTCPConnection(context,server);
        acceptor.async_accept(connection->getSocket(),boost::bind(&tcpServer::handle_accept,this,connection));
}

void tcpServer::handle_accept(tcpConnection::pointer connection){
        connection->start();
        accept_connections();
}

//Server

Server::Server(const int _port):port(_port){}

Server::~Server()
{
    if(communicationThread.joinable())
    {
        communicationThread.join();
    }
}

void Server::run()
{
    std::thread t(&Server::communication,this);
    communicationThread=std::move(t);
}

void Server::communication()
{
    server=std::make_unique<tcpServer>(io_context,port,*this);
    boost::thread t(boost::bind(&boost::asio::io_context::run, &io_context));
    io_context.run();
}

void Server::aquisitRequest(std::string request)
{
    requestResponse[0]=request;
}

void Server::setResponse(const std::string& response)
{
    requestResponse[1]=response;
}

std::optional<std::string> Server::waitForRequest()
{
    if(requestResponse[0]==""){
        return {};
    }
    return requestResponse[0];
}

std::string Server::waitUntilRequestProcessed()
{
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        if(requestResponse[1]!=""){
            return requestResponse[1];
        }
    }
}

void Server::refresh()
{
    requestResponse[0]="";
    requestResponse[1]="";
}