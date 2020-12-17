cmake_minimum_required(VERSION 3.15)
project(ComputerAlgebraTask)

set(CMAKE_SXX_STANDARD 20)

add_executable(ComputerAlgebraTask
        main.cpp
        PolynomialTree/PolynomialPrimitives/Node/Node.h
        PolynomialTree/PolynomialPrimitives/Operands/Variable.cpp
        PolynomialTree/PolynomialPrimitives/Operands/Variable.h
        PolynomialTree/PolynomialPrimitives/Operands/Constant.cpp
        PolynomialTree/PolynomialPrimitives/Operands/Constant.h
        PolynomialTree/PolynomialPrimitives/Operations/AbstractOperations/AbstractUnaryOperation.cpp
        PolynomialTree/PolynomialPrimitives/Operations/AbstractOperations/AbstractUnaryOperation.h
        PolynomialTree/PolynomialPrimitives/Operations/AbstractOperations/AbstractBinaryOperation.cpp
        PolynomialTree/PolynomialPrimitives/Operations/AbstractOperations/AbstractBinaryOperation.h
        PolynomialTree/PolynomialPrimitives/Operations/Operations/Sum.cpp
        PolynomialTree/PolynomialPrimitives/Operations/Operations/Sum.h
        PolynomialTree/PolynomialPrimitives/Operations/Operations/UnaryMinus.cpp
        PolynomialTree/PolynomialPrimitives/Operations/Operations/UnaryMinus.h
        PolynomialTree/PolynomialPrimitives/Operations/Operations/BinaryMinus.cpp
        PolynomialTree/PolynomialPrimitives/Operations/Operations/BinaryMinus.h
        PolynomialTree/PolynomialPrimitives/Operations/Operations/Divide.cpp
        PolynomialTree/PolynomialPrimitives/Operations/Operations/Divide.h
        PolynomialTree/PolynomialPrimitives/Operations/Operations/Multiplication.cpp
        PolynomialTree/PolynomialPrimitives/Operations/Operations/Multiplication.h
        PolynomialTree/PolynomialPrimitives/Operations/Operations/Exponentiation.cpp
        PolynomialTree/PolynomialPrimitives/Operations/Operations/Exponentiation.h
        Parser/Parser.cpp
        Parser/Parser.h
        RationalNumber/RationalNumber.cpp
        RationalNumber/RationalNumber.h)

add_subdirectory(Google_tests)