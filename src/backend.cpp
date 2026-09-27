#include <iostream>
#include <unordered_map>
#include <string>

int main(){
    std::unordered_map<std::string, std::string> store;

    //store
    store["name"] = "Hitesh";
    store["course"] = "cse";

    //find something
    auto it = store.find("name");
    if (it != store.end()) {
        std::cout << it->second << "\n";
    } else {
        std::cout<< "(nil)\n";
    }

    it = store.find("age");
    if (it != store.end()) {
        std::cout << it->second << "\n";
    } else {
        std::cout<< "(nil)\n";
    }
    return 0;
}