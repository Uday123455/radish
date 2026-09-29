#include <iostream>
#include <unordered_map>
#include <string>
#include <optional>

class Database {
public:
    void set(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key);
    void del(const std::string& key);

private:
    std::unordered_map<std::string, std::string> data;
};

void Database::set(const std::string& key, const std::string& value) {
    data[key] = value;
}

std::optional<std::string> Database::get(const std::string& key) {
    auto it = data.find(key);
    if (it == data.end()) {
        return std::nullopt;
    }
    return it->second;
}

void Database::del(const std::string& key) {
    data.erase(key);
}

int main(){
    Database db;

    //store
    db.set("name", "Hitesh");
    db.set("course", "cse");

    //find something
    auto it = db.get("name");
    if (it) {
        std::cout << *it << "\n";
    } else {
        std::cout<< "(nil)\n";
    }

    it = db.get("age");
    if (it) {
        std::cout << *it << "\n";
    } else {
        std::cout<< "(nil)\n";
    }
    return 0;
}