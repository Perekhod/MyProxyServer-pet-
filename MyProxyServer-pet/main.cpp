#include <iostream>
#include <boost/asio.hpp>

#include "SocketManager.h"
#include "HttpParser.h"

int main() 
{
    // Создаем io_service для управления асинхронными операциями
    boost::asio::io_service ioService;

    // Создаем экземпляр SocketManager для управления сокетами
    SocketManager socketManager(ioService, 8080);

    // Начинаем прослушивание входящих соединений
    socketManager.startListening();

    // Пример HTTP-запроса на главную страницу Google
    std::string httpRequestString = "GET / HTTP/1.1\r\n"
        "Host: www.google.com\r\n"
        "Connection: close\r\n\r\n";

    // Вызов метода для разбора HTTP-запроса
    HttpParser::parserHttpRequest(httpRequestString);

    // Запускаем io_service
    ioService.run();

    return 0;
}