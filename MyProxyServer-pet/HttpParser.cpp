#include "HttpParser.h"
#include <iostream>
#include <boost/beast/http.hpp>

void HttpParser::parserHttpRequest(const std::string& httpRequestString)
{
    // ���� ������� ������ � ����� ������ URL
    auto urlStart   = httpRequestString.find(' ') + 1;
    auto urlEnd     = httpRequestString.find(' ', urlStart);

    // ������� Method � URL
    std::cout << "Method: " << httpRequestString.substr(0, urlStart - 1)             << std::endl;
    std::cout << "URL: "    << httpRequestString.substr(urlStart, urlEnd - urlStart) << std::endl;
}
