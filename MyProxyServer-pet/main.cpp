#include <iostream>
#include <boost/asio.hpp>
#include "SocketManager.h"

int main() 
{
    // ������� io_service ��� ���������� ������������ ����������
    boost::asio::io_service ioService;

    // ������� ��������� SocketManager ��� ���������� ��������
    SocketManager socketManager(ioService, 8080);

    // �������� ������������� �������� ����������
    socketManager.startListening();

    // ��������� io_service
    ioService.run();

    return 0;
}
