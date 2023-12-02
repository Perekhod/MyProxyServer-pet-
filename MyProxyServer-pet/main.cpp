#include <iostream>
#include <boost/asio.hpp>
#include "SocketManager.h"

int main() 
{
    // Создаем io_service для управления асинхронными операциями
    boost::asio::io_service ioService;

    // Создаем экземпляр SocketManager для управления сокетами
    SocketManager socketManager(ioService, 8080);

    // Начинаем прослушивание входящих соединений
    socketManager.startListening();

    // Запускаем io_service
    ioService.run();

    return 0;
}
