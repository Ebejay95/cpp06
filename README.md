# C++ Module 06

**C++ Casts**

This module focuses on mastering type conversions and understanding the use of casts in C++.

## Structure

### ex00/ - Conversion of Scalar Types
- **ScalarConverter.{hpp,cpp}**: Implements a static method `convert` to handle conversions of string representations of scalar types (`char`, `int`, `float`, `double`).
- **main.cpp**: Tests type detection, conversions, and error handling for invalid or overflow scenarios.

### ex01/ - Serialization
- **Serializer.{hpp,cpp}**: Contains two static methods:
  - `serialize(Data* ptr)`: Converts a pointer to `uintptr_t`.
  - `deserialize(uintptr_t raw)`: Converts a `uintptr_t` back to a pointer to `Data`.
- **Data.{hpp,cpp}**: Defines the non-empty `Data` structure.
- **main.cpp**: Validates the serialization and deserialization process.

### ex02/ - Identify Real Type
- **Base.{hpp,cpp}**: Abstract base class with a virtual destructor.
- **A.{hpp,cpp}, B.{hpp,cpp}, C.{hpp,cpp}**: Classes inheriting from `Base`.
- Functions:
  - `Base* generate()`: Randomly instantiates `A`, `B`, or `C` and returns a `Base*`.
  - `void identify(Base* p)`: Identifies the type of object pointed to by `p`.
  - `void identify(Base& p)`: Identifies the type of object referred to by `p`.
- **main.cpp**: Tests type identification.

## Features

- **Static Methods**: Key operations are encapsulated in static methods for modular design.
- **Type Casting**: Demonstrates `reinterpret_cast`, `dynamic_cast`, and manual type management.
- **Randomized Behavior**: Tests inheritance-based type identification with randomized object creation.
- **Serialization**: Explores memory address manipulation for object persistence.
