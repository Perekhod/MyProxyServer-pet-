#pragma once

#include <string>

class TrafficFilter 
{
public:
    TrafficFilter() = default;
    ~TrafficFilter() = default;

    bool isUrlBlocked(const std::string& url) const;
};
