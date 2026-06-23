#include "parser.hpp"
#include <fstream>
#include <ios>
#include <string>

void IniParser::fillData(){
    std::string row;
    
    data.clear();
    file.clear();
    file.seekg(0);
    
    if(file.is_open()){
        std::string last_section = "";
        while(std::getline(file, row)){
            if(isSection(row)){
                // Remove "[]" from section name
                last_section = row.substr(1, row.size()-2);
            }

            if(isKeyOrValue(row) && !last_section.empty()){
                auto keyValue = getKeyValue(row);
                data[last_section][keyValue.first] = keyValue.second;
            }
        }
    }
}

IniParser::IniParser(const std::string& fileName){
    file.open(fileName, std::ios::in | std::ios::out);
    if(!file.is_open())
        std::cerr << "Can't open file\n";
    this->fileName = fileName;
    fillData();
}

IniParser::~IniParser(){
    if(file.is_open())
        file.close();
}