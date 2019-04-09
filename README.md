# Steganography with C++ and .PPM files

Steganography is a set of techniques for hiding secret data within ordinary data. This software hides messages into .ppm images files.
It's written in Standard C++, no dependencies.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

GNU GCC Compiler OR Microsoft Visual C++ Compiler

### Cloning, compiling and running

Instructions to compile

If you are on Windows Microsoft Visual C++ Compiler

```
git clone https://github.com/ArthoPacini/Steganography
cd Steganography/
path/to/cl.exe /EHsc main.cpp
./main
```

On GNU GCC Compiler

```
git clone https://github.com/ArthoPacini/Steganography
cd Steganography/
make
./main
```

## Running

Right now the input and output paths to images are hard coded on main.cpp, line 12 and 17. This will be changed.

## Example

This is a sample image, found on "samples" folder.
![beach original image](https://i.imgur.com/hXQY9jp.jpg)

This is the output image, found on "output_images" folder.
![beach output image](https://i.imgur.com/7J2NFiD.jpg)
it contains "This is a hidden message inside the file! " inside it.

## Goals

- [X] Hide a message inside a .ppm image file
- [ ] Add symmetric-key cryptography
- [ ] Add asymmetric-key cryptography
- [ ] Hide a file inside a .ppm image file
- [ ] Add support for reading .jpeg, .png and .gif files
- [ ] Add support for writing .jpeg, .png and .gif files
- [ ] Make an electron app and add this code as an node.js addon

## Contributing

Just pull a request, that's it.

## Authors

* **Artho Pacini** - *First implementation* - [Twitter](https://twitter.com/arthopacini)

## License

This project is public domain, you may use it whenever you like, distributed and change it at your own taste.
