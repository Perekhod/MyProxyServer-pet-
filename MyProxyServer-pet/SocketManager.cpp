#include "SocketManager.h"

// �����������, ���������������� acceptor � socket
SocketManager::SocketManager(boost::asio::io_service& ioService, short port)
    : acceptor_(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    socket_(ioService) {}

// ����� ��� ������ ������������� �������� ����������
void SocketManager::startListening() 
{
    acceptor_.async_accept(socket_,
        [this](const boost::system::error_code& error) 
        {
            handleAccept(error);
        }
    );
}

// ���������� ���������� �������� async_accept
void SocketManager::handleAccept(const boost::system::error_code& error) 
{
    if (!error) 
    {
        // ����� ����� �������� ��� ��� ��������� ������ ����������
    }

    // ���������� ������������� ��� ����� ����������
    startListening();
}
