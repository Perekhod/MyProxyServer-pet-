#include <iostream>
#include <boost/asio.hpp>

int main()
{
    // Создаем экземпляр класса io_service
    boost::asio::io_service ioService;

    // Создаем объект acceptor для прослушивания входящих соединений
    boost::asio::ip::tcp::acceptor acceptor(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080));

    // Бесконечный цикл ожидания входящих соединений
    while (true)
    {
        // Создаем сокет для установки соединения с клиентом
        boost::asio::ip::tcp::socket socket(ioService);

        // Принимаем входящее соединение и связываем его с созданным сокетом
        acceptor.accept(socket);

        // Далее следует код для обработки соединений...
    }

    return 0;
}
