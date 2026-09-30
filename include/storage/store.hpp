#pragma once

#include <optional>
#include <string>
#include <unordered_map>

class Store {
public:
    void set(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key);
    void del(const std::string& key);

private:
    std::unordered_map<std::string, std::string> data;
};