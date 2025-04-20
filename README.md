# MLP Neural Network Implementation

This project implements a Multi-Layer Perceptron (MLP) Neural Network designed for digit recognition using C++.

## Overview

The project consists of several modular components:

- **Matrix Class (`Matrix.h`, `Matrix.cpp`)**: Handles matrix operations, including arithmetic, transformations, and I/O.
- **Dense Layer (`Dense.h`, `Dense.cpp`)**: Implements fully connected neural network layers using customizable activation functions.
- **Activation Functions (`Activation.h`, `Activation.cpp`)**: Implements ReLU and Softmax activation functions.
- **MLP Network (`MlpNetwork.h`, `MlpNetwork.cpp`)**: Defines the neural network architecture comprising multiple Dense layers for digit recognition tasks.

## Features

- Modular and clean implementation
- Supports ReLU and Softmax activation functions
- Exception handling for dimension mismatches and invalid inputs

## Usage

Instantiate `MlpNetwork` with predefined weights and biases, and use the overloaded `()` operator to perform digit recognition on input data.

## Requirements

- C++ Compiler supporting C++11 or later

## Compilation

Use a standard C++ compiler command, such as:

```bash
g++ -std=c++11 *.cpp -o mlp_network
```

## Run

```bash
./mlp_network
```

## Author

Dana Siton

## License

[MIT License](LICENSE)

