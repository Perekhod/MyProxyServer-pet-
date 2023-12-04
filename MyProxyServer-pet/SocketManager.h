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

    // Метод обработки завершения операции async_accept
    void handleAccept(const boost::system::error_code& error);

    // Метод обработки данных
    void handleData(const boost::system::error_code& error, std::size_t bytes_transferred);

    // Метод для обработки данных и перенаправления
    void forwardData(const boost::system::error_code& error, std::size_t bytes_transferred);

    // Метод для обработки ошибок при асинхронном чтении
    void handleReadError(const boost::system::error_code& error);

    // Метод для обработки ошибок при асинхронной записи
    void handleWriteError(const boost::system::error_code& error);

private:
    // Acceptor для прослушивания входящих соединений
    boost::asio::ip::tcp::acceptor acceptor_;   

    // Сокет для обработки соединений
    boost::asio::ip::tcp::socket socket_;

    // Буфер для приема/отправки данных
    std::array<char, 8192> buffer_;

    // Члены для хранения данных о целевом сервере
    std::string targetHost_;
    short targetPort_;
    boost::asio::ip::tcp::socket targetSocket_;

    // Буфер для хранения данных от клиента и для отправки на целевой сервер
    std::array<char, 8192> clientBuffer_;

    // Объект strand для безопасности многопоточности
    boost::asio::io_service::strand strand_;
};
