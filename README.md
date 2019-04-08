# Steganography with C++ and .PPM files

Steganography is a set of techniques for hiding secret data within ordinary data. This software hides messages into .ppm images files.
It's written in Standard C++, no dependencies.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

A copy of this repository
GNU GCC Compiler or Visual C++ Compiler

```
Give examples
```

### Compiling

Instructions to compile

If you are on Windows Microsoft Visual C++ Compiler

```
cl.exe /EHsc main.cpp
main
```

On GNU GCC Compiler

```
g++ main.cpp -o main -std=c++17 -lstdc++fs
main
```

## Running

Right now the input and output paths to images are hard coded on main.cpp, line 12 and 17. This will be changed.

## Contributing

Just pull a request, that's it.

## Authors

* **Artho Pacini** - *First implementation* - [Twitter](https://twitter.com/arthopacini)

## License

This project is public domain, you may use it whenever you like, distributed and change it at your own taste.
