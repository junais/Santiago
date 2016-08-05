#ifndef SANTIAGO_AUTHENTICATION_TCPCONNECTION_H
#define SANTIAGO_AUTHENTICATION_TCPCONNECTION_H

#include <memory>
#include <string>
#include <cstdlib>

#include <boost/asio/strand.hpp>
#include <boost/asio.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/streambuf.hpp>

#include <boost/bind.hpp>
#include <boost/function.hpp>

#include "Message.h"

namespace Santiago{ namespace Authentication
{
    class TCPConnection:public std::enable_shared_from_this<TCPConnection>
    {
    public:

        static const unsigned BUFFER_INCREMENT_SIZE = 4096;
        typedef boost::shared_ptr<boost::asio::strand> StrandPtr;
        typedef std::shared_ptr<TCPConnection> Ptr;
        typedef boost::asio::ip::tcp::socket MySocket;
        typedef std::shared_ptr<MySocket> MySocketPtr;

        typedef std::function<void()> OnDisconnectCallbackFn;
        typedef std::function<void(const ConnectionMessage&)> OnMessageCallbackFn;

        TCPConnection(const MySocketPtr& socketPtr_,
                      const OnDisconnectCallbackFn& onDisconnectCallbackFn_,
                      const OnMessageCallbackFn& onMessageCallbackFn_);

        void sendMessage(const ConnectionMessage& message_);
        void start();
        void close();

    private:

        void handleRead(const boost::system::error_code& error_,size_t bytesTransferred_);
        void sendMessageImpl(const ConnectionMessage& message_);

        MySocketPtr                             _socketPtr;
        boost::asio::io_service                &_ioService;
        StrandPtr                               _strandPtr;
        OnDisconnectCallbackFn                  _onDisconnectCallbackFn;
        OnMessageCallbackFn                     _onMessageCallbackFn;

        boost::asio::streambuf                  _inputBuffer;
    };



}} //closing namespace Santiango::Authentication

#endif

