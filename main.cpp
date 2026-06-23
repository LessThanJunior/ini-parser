#include "parser.hpp"
#include <cstdint>
#include <iostream>

int main(){
    IniParser config("examples/config.ini");
    std::cout << config.get<uint16_t>("Window", "Width") << "\n";
    config.set("Network", "Port", 12345);
    config.set("Database", "Type", "SQLite12345");
    config.set("Database", "Paths", "data/database12345.db");
    config.set("General","Debug", true);
    config.set("Window", "Width", 1280);
    std::cout << config.get<bool>("General","Debug") << "\n";
}