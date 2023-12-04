#include "SocketManager.h"

// Конструктор, инициализирующий acceptor и socket
SocketManager::SocketManager(boost::asio::io_service& ioService, short port)
    :   acceptor_       (ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
        socket_         (ioService),
        targetSocket_   (ioService),
        strand_         (ioService) {}

// Метод для начала прослушивания входящих соединений
void SocketManager::startListening() 
{
    std::cout << "I'm listening!\n";
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
    if (!error) 
    {
        // Обработка полученных данных (ваша логика обработки)

        // Отправляем данные обратно клиенту (просто для примера)
        boost::asio::async_write(targetSocket_, boost::asio::buffer(clientBuffer_, bytes_transferred),
            strand_.wrap([this](const boost::system::error_code& error, std::size_t /*bytes_transferred*/) 
                {
                if (error) 
                {
                    // Обработка ошибок при асинхронной записи
                    handleWriteError(error);
                }
                })
        );

        // Продолжаем асинхронный прием данных от клиента
        socket_.async_read_some(boost::asio::buffer(clientBuffer_),
            strand_.wrap([this](const boost::system::error_code& error, std::size_t bytes_transferred) {
                if (error) 
                {
                    // Обработка ошибок при асинхронном чтении
                    handleReadError(error);
                }
                else 
                {
                    handleData(error, bytes_transferred);
                }
                })
        );
    }
    else 
    {
        // Обработка ошибок при асинхронном чтении
        handleReadError(error);
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
        handleReadError(error);
    }
}

void SocketManager::handleReadError(const boost::system::error_code& error) 
{
    // Обработка ошибок при асинхронном чтении
    std::cerr << "Error during async_read_some: " << error.message() << std::endl;

    // Закрываем соединения с клиентом и целевым сервером
    strand_.post([this]() 
        {
        socket_.close();
        targetSocket_.close();
        });
}

void SocketManager::handleWriteError(const boost::system::error_code& error) 
{
    // Обработка ошибок при асинхронной записи
    std::cerr << "Error during async_write: " << error.message() << std::endl;

    // Закрываем соединения с клиентом и целевым сервером
    strand_.post([this]() 
        {
        socket_.close();
        targetSocket_.close();
        });
}