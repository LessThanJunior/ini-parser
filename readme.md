# Ini Parser

This project is an educational self-made INI parser aimed at improving skills in:

- Testing  
- Working with strings  
- Error handling  

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

### `IniParser parser(const std::string& filepath)`

Loads and parses an INI file into memory.

#### Throws:
- `NotFoundFileException` (if the file cannot be opened)

---

### `parser.get<T>(const std::string& section, const std::string& key)`

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

### `parser.set<T>(const std::string& section, const std::string& key, const T& value)`

Updates a value in memory and persists changes to the INI file.

#### Supported types:
- integral types
- floating point types
- `bool`
- `std::string`

#### Throws:
- `std::out_of_range` (missing section or key)

---

### `parser.hasSection(const std::string& section)`

Returns `true` if the section exists.

---

### `parser.hasKey(const std::string& section, const std::string& key)`

Returns `true` if the key exists in the specified section.

---

## Limitations

- No multiline values  
- No section inheritance  
- No escaping support  