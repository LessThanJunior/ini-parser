#ifndef INI_EXCEPTION_H
#define INI_EXCEPTION_H
#include <stdexcept>
#include <string>

class EmptyFileException : public std::runtime_error{
public:
    EmptyFileException(std::string filepath) : std::runtime_error("This file \"" + filepath + "\" is empty"){}
};

class TypeException : public std::runtime_error{
public:
    TypeException(std::string message) : std::runtime_error(message){}
};

class NotFoundFileException : public std::runtime_error{
public:
    NotFoundFileException(std::string message) : std::runtime_error(message){}
};

#endif