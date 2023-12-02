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

void SocketManager::handleData(const boost::system::error_code& error, std::size_t bytes_transferred) {
    if (!error) {
        // Обработка полученных данных (ваша логика обработки)

        // Отправляем данные обратно клиенту (просто для примера)
        boost::asio::async_write(socket_, boost::asio::buffer(buffer_, bytes_transferred),
            [this](const boost::system::error_code& error, std::size_t /*bytes_transferred*/) 
            {
                if (error) 
                {
                    // Обработка ошибок при отправке данных
                    std::cerr << "Error during async_write: " << error.message() << std::endl;
                }
            }
        );

        // Продолжаем асинхронный прием данных
        socket_.async_read_some(boost::asio::buffer(buffer_),
            [this](const boost::system::error_code& error, std::size_t bytes_transferred) 
            {
                handleData(error, bytes_transferred);
            }
        );
    }
    else 
    {
        // Обработка ошибок при приеме данных
        std::cerr << "Error during async_read_some: " << error.message() << std::endl;

        // Добавим простую логику: закрываем сокет и перезапускаем прослушивание для новых соединений
        socket_.close ();
        startListening();
    }
}
