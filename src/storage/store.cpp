#include "storage/store.hpp"
#include <optional>
#include <string>

void Store::set(const std::string& key, const std::string& value)
{
    data[key] = value;
}

std::optional<std::string> Store::get(const std::string& key)
{
    auto it = data.find(key);

    if (it == data.end()) {
        return std::nullopt;
    }

    return it->second;
}
void Store::del(const std::string& key){

    
    auto it=data.find(key);
    data.erase(key);
    

}