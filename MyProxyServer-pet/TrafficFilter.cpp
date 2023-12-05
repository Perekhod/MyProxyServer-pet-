#include "TrafficFilter.h"
#include <unordered_set>

namespace 
{
    // Здесь мы определяем список заблокированных URL-адресов
    const std::unordered_set<std::string> blockedUrls = 
    {
        "google.com",
        "yandex.ru"
        // Добавьте сюда другие URL-адреса, которые вы хотите заблокировать
    };
}

bool TrafficFilter::isUrlBlocked(const std::string& url) const 
{
    // Проверяем, находится ли URL в списке заблокированных
    return blockedUrls.find(url) != blockedUrls.end();
}
