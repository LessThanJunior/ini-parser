#ifndef PARSER_HPP
#define PARSER_HPP
#include <fstream>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>
#include <string>
#include <iostream>

using section = std::string; 
using key = std::string;
using value = std::string;

class IniParser{
    std::fstream file;
    std::string fileName;

    std::unordered_map<section, std::unordered_map<key, value>> data;
    void fillData();

    bool isSection(const std::string& row){
        return !row.empty() && row[0] == '[' && row[row.size()-1] == ']';
    }

    bool isKeyOrValue(const std::string& row){
        return !isSection(row) && !row.empty();
    }

    std::pair<std::string, std::string> getKeyValue(const std::string& row){
        std::pair<std::string, std::string> keyValue;

        size_t delimiter = row.find("=");
        keyValue.first = row.substr(0, delimiter);
        keyValue.second = row.substr(delimiter + 1); 

        return keyValue;
    } 

    void saveFile(){
        file.clear();
        file.seekg(0);

        std::rename(fileName.c_str(), ("~" + fileName).c_str());
        std::fstream newFile;
        newFile.open(fileName, std::ios::out);
        for (const auto& section : data){
            newFile << "[" << section.first << "]\n";
            for (const auto& keyValue : section.second){
                newFile << keyValue.first << "=" << keyValue.second << "\n"; 
            }
            newFile << "\n";
        }
        newFile.close();
        if(file.is_open()){
            file.close();
        }
        file.open(fileName, std::ios::in | std::ios::out);
        std::remove(("~" + fileName).c_str());
    }

public:
    IniParser(const std::string& file);

    bool hasSection(std::string section){
        return data.find(section) != data.end();
    };

    bool hasKey(std::string section, std::string key){
        auto sectionIterator = data.find(section);
        if(sectionIterator == data.end())
            return false;

        return sectionIterator->second.find(key) != sectionIterator->second.end(); 
    }

    template <class Type>
    inline Type get(const std::string& section, const std::string& key){
        const auto& value = data.at(section).at(key);

        if constexpr (std::is_same_v<Type, bool>) {
            if(value != "true" && value != "false")
                throw std::runtime_error("Isn't a boolean");
            return value == "true" ? true : false;
        }

        else if constexpr (std::is_integral_v<Type>) {
            return std::stoull(value);
        }  

        else if constexpr (std::is_floating_point_v<Type>) {
            return std::stod(value);
        }
                
        return (Type)0;
    }
    
    template <class Type>
    inline void set(const std::string& section, const std::string& key, const Type& value){
        std::string newValue = "";
        bool boolean; 

        if constexpr (std::is_same_v<Type, bool>) {
            boolean = value;
            newValue = boolean == true ? "true" : "false";
        }

        else if constexpr (std::is_integral_v<Type>) {
            newValue = std::to_string(value);
        }

        else {
            newValue.assign(value);
        }
        
        data.at(section).at(key) = newValue;
        saveFile();
    }

    ~IniParser();
};

#endif