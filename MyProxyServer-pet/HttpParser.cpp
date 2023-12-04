#include "HttpParser.h"
#include <iostream>
#include <boost/beast/http.hpp>

void HttpParser::parserHttpRequest(const std::string& httpRequestString)
{
    // Ищем позиции начала и конца строки URL
    auto urlStart   = httpRequestString.find(' ') + 1;
    auto urlEnd     = httpRequestString.find(' ', urlStart);

    // Выводим Method и URL
    std::cout << "Method: " << httpRequestString.substr(0, urlStart - 1)             << std::endl;
    std::cout << "URL: "    << httpRequestString.substr(urlStart, urlEnd - urlStart) << std::endl;
}
