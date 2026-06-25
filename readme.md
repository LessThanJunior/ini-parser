# Ini Parser

This project is an educational self-made INI parser aimed at improving skills in:

- Testing  
- Working with strings  
- Error handling  

---

## Usage

```cpp
#include "parser.hpp"

IniParser parser("config.ini");
uint16_t value = parser.get<uint16_t>("section", "key");
parser.set("section", "key", value + 1);
```

---

## Install

### build from sourse
```sh
git clone https://github.com/LessThanJunior/ini-parser
cd ini-parser

cmake -B build
cmake --build build
```

### prebuilt
Download latest release from:
https://github.com/LessThanJunior/ini-parser/releases

---

## Features

- [x] Check if section exists  
- [x] Check if key exists  
- [x] Load file into memory  
- [x] Read and write INI file  
- [x] Strongly typed `get<T>()`  
- [x] Edge-case tests  
- [ ] Unit test coverage (in progress)  

---

## Documentation

```cpp
IniParser parser(const std::string& filepath)
```

Loads and parses an INI file into memory.

#### Throws:
- `NotFoundFileException` (if the file cannot be opened)

---

```cpp
parser.get<T>(const std::string& section, const std::string& key)
```

Retrieves a value as type `T`.

#### Supported types:
- integral types
- floating point types
- `bool`
- `std::string`

#### Throws:
- `TypeException` (invalid type conversion)
- `std::out_of_range` (missing section or key)

---

```cpp
parser.set<T>(const std::string& section, const std::string& key, const T& value)
```

Updates a value in memory and persists changes to the INI file.

#### Supported types:
- integral types
- floating point types
- `bool`
- `std::string`

#### Throws:
- `std::out_of_range` (missing section or key)

---

```cpp
parser.hasSection(const std::string& section)
```

Returns `true` if the section exists.

```cpp
parser.hasKey(const std::string& section, const std::string& key)
```

Returns `true` if the key exists in the specified section.

---

## Limitations

- No multiline values  
- No section inheritance  
- No escaping support  