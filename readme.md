# Ini Parser

This project is educational self-made for level up in such areas:

- Testing
- Working with strings
- Error handling

## Features

- [x] Check if section exists
- [x] Check if key exists
- [x] Load file into RAM
- [x] Read/write INI file 
- [x] Strongly-type for `get<T>()`
- [x] Edge-case tests
- [ ] Unit tests coverage (in progress)

## Documentation

### `IniParser parser(string filepath)` 
Load and parse INI file into memory

#### Throws:
- NotFoundFileException (can't open file)

### `parser.get<T>(string section, string key)` 
Get value as T type

#### Supported types:
- integral, floating point, bool, std::string

#### Throws:
- TypeException (invalid casting)
- std::out_of_range (missing key/section)

### `parser.set(string section, string key, T value)` 
Set value into RAM and INI file

#### Supported types
- integral, floating point, bool, std::string

#### Throws:
- std::out_of_range (missing key/section)

### `parser.hasSection(string section)` 
Return true if section exists

### `parser.hasKey(string section, string key)` 
Return true if key exists

## Limitations
- No multiline values
- No section inheritance
- No escaping support