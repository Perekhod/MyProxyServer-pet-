#pragma once

#include <boost/asio.hpp>

class SocketManager 
{
public:
    // �����������, ���������������� acceptor � socket
    SocketManager(boost::asio::io_service& ioService, short port);

    // ����� ��� ������ ������������� �������� ����������
    void startListening();

    // ���������� ���������� �������� async_accept
    void handleAccept(const boost::system::error_code& error);

private:
    // Acceptor ��� ������������� �������� ����������
    boost::asio::ip::tcp::acceptor acceptor_;   

    // ����� ��� ��������� ����������
    boost::asio::ip::tcp::socket socket_;
};
