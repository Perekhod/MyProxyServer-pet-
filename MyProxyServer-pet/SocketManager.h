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

    // Метод для обработки данных и перенаправления
    void forwardData(const boost::system::error_code& error, std::size_t bytes_transferred);

    // Метод для обработки ошибок и закрытия соединений
    void handleError(const boost::system::error_code& error);

private:
    // Acceptor для прослушивания входящих соединений
    boost::asio::ip::tcp::acceptor acceptor_;   

    // Сокет для обработки соединений
    boost::asio::ip::tcp::socket socket_;

    // Буфер для приема/отправки данных
    std::array<char, 8192> buffer_;

    // Новые члены для хранения данных о целевом сервере
    std::string targetHost_;
    short targetPort_;
    boost::asio::ip::tcp::socket targetSocket_;

    // Новый буфер для хранения данных от клиента и для отправки на целевой сервер
    std::array<char, 8192> clientBuffer_;
};
