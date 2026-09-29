#include "storage/store.hpp"

void Store::set(const std::string& key, const std::string& value)
{
    data[key] = value;
}

std::string Store::get(const std::string& key)
{
    auto it = data.find(key);

    if (it == data.end()) {
        return "(nil)";
    }

    return it->second;
}
void Store::del(const std::string& key){

    
    auto it=data.find(key);
    data.erase(key);
    

}