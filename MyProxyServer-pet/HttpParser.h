#pragma once

#include <string>
#include <boost/beast/http.hpp>

class HttpParser
{
public:
    // ����� ��� ������� HTTP-�������
    static void parserHttpRequest(const std::string& httpRequestString);
};