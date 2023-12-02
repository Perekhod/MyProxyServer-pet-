#include "SocketManager.h"

// Конструктор, инициализирующий acceptor и socket
SocketManager::SocketManager(boost::asio::io_service& ioService, short port)
    : acceptor_(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    socket_(ioService),
    targetSocket_(ioService) {  // Инициализируем targetSocket_ с использованием ioService
}

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
        // Соединение установлено успешно, начинаем прием данных от клиента
        socket_.async_read_some(boost::asio::buffer(clientBuffer_),
            [this](const boost::system::error_code& error, std::size_t bytes_transferred) 
            {
                forwardData(error, bytes_transferred);
            }
        );
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
        // Обработка ошибок при приеме данных от клиента
        handleError(error);
    }
}

void SocketManager::forwardData(const boost::system::error_code& error, std::size_t bytes_transferred) {
    if (!error) 
    {
        // Отправляем данные на целевой сервер (просто для примера)
        boost::asio::async_write(targetSocket_, boost::asio::buffer(clientBuffer_, bytes_transferred),
            [this](const boost::system::error_code& error, std::size_t /*bytes_transferred*/) 
            {
                if (error) 
                {
                    // Обработка ошибок при отправке данных на целевой сервер
                    std::cerr << "Error during async_write to target server: " << error.message() << std::endl;
                }
            }
        );

        // Продолжаем асинхронный прием данных от клиента
        socket_.async_read_some(boost::asio::buffer(clientBuffer_),
            [this](const boost::system::error_code& error, std::size_t bytes_transferred) 
            {
                forwardData(error, bytes_transferred);
            }
        );
    }
    else 
    {
        // Обработка ошибок при приеме данных от клиента
        handleError(error);
    }
}

void SocketManager::handleError(const boost::system::error_code& error) 
{
    std::cerr << "Error: " << error.message() << std::endl;
    // Закрываем соединения с клиентом и целевым сервером
    socket_.close();
    targetSocket_.close();
}