#include <iostream>
#include <boost/asio.hpp>

int main()
{
    // ������� ��������� ������ io_service
    boost::asio::io_service ioService;

    // ������� ������ acceptor ��� ������������� �������� ����������
    boost::asio::ip::tcp::acceptor acceptor(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080));

    // ����������� ���� �������� �������� ����������
    while (true)
    {
        // ������� ����� ��� ��������� ���������� � ��������
        boost::asio::ip::tcp::socket socket(ioService);

        // ��������� �������� ���������� � ��������� ��� � ��������� �������
        acceptor.accept(socket);

        // ����� ������� ��� ��� ��������� ����������...
    }

    return 0;
}
