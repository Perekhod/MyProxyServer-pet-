#include "SocketManager.h"

// Конструктор, инициализирующий acceptor и socket
SocketManager::SocketManager(boost::asio::io_service& ioService, short port)
    : acceptor_(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    socket_(ioService) {}

// Метод для начала прослушивания входящих соединений
void SocketManager::startListening() 
{
    acceptor_.async_accept(socket_,
        [this](const boost::system::error_code& error) 
        {
            handleAccept(error);
        }
    );
}

// Обработчик завершения операции async_accept
void SocketManager::handleAccept(const boost::system::error_code& error) 
{
    if (!error) 
    {
        // Здесь можно добавить код для обработки нового соединения
    }

    // Продолжаем прослушивание для новых соединений
    startListening();
}
