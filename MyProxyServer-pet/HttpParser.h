#pragma once

#include <string>
#include <boost/beast/http.hpp>

class HttpParser
{
public:
    // Метод для разбора HTTP-запроса
    static void parserHttpRequest(const std::string& httpRequestString);
};