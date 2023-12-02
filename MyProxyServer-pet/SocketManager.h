#pragma once

#include <boost/asio.hpp>
#include <iostream>

class SocketManager 
{
public:
    // Конструктор, инициализирующий acceptor и socket
    SocketManager(boost::asio::io_service& ioService, short port);

    // Метод для начала прослушивания входящих соединений
    void startListening();

    // Обработчик завершения операции async_accept
    void handleAccept(const boost::system::error_code& error);

    // Обработчик данных
    void handleData(const boost::system::error_code& error, std::size_t bytes_transferred);

private:
    // Acceptor для прослушивания входящих соединений
    boost::asio::ip::tcp::acceptor acceptor_;   

    // Сокет для обработки соединений
    boost::asio::ip::tcp::socket socket_;

    // Буфер для приема/отправки данных
    std::array<char, 8192> buffer_;
};
