# AUTOSAR C++14 CHECKER

## Description 

This project tries to create a code checker for the [AUTOSAR C++14 coding guidelines](https://www.autosar.org/fileadmin/user_upload/standards/adaptive/18-10/AUTOSAR_RS_CPP14Guidelines.pdf) using the LLVM/Clang tooling infrastructure.

## Requirements

- Git
- CMake >= 3.16.3
- Ninja
- GCC >= 5.1
- Python >= 3.6 
- Build LLVM, Clang and Clang-tidy from source. (simply run `./build.sh`) 
- All files are created, compiled and tested on Ubuntu 20.04 LTS.

## Usage

Enable the rules `autosar-*` when invoking clang-tidy.

## To Dos

- There are still many rules that are not yet covered. So covering as many rules as possible is a clear next step in this project.

## Authors

- **Mohamed khalil El-Bechir** - [medkhalilelb@gmail.com](medkhalilelb@gmail.com) | [GitHub/iamkhalil](https://github.com/iamkhalil)
- **Khouloud Mansour** - [khouloud.mansour@ensi-uma.tn](khouloud.mansour@ensi-uma.tn) 	

## Licence

MIT Licence
