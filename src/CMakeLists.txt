cmake_minimum_required(VERSION 3.15)
project(ComputerAlgebraTask)

set(CMAKE_SXX_STANDARD 20)
set(BOOST_ROOT "C:/Users/Nik Carlson/Documents/LIBS/boost_1_75_0")
set(LAPACK_ROOT "C:/Users/Nik Carlson/Documents/LIBS/Lapackpp1.1a")
find_package(Boost 1.75.0)
find_package(Lapack 1.1)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()
include_directories(${BOOST_ROOT})
include_directories(${LAPACK_ROOT})

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
        PolynomialTree/PolynomialPrimitives/Operations/Operations/Multiplication.cpp
        PolynomialTree/PolynomialPrimitives/Operations/Operations/Multiplication.h
        PolynomialTree/PolynomialPrimitives/Operations/Operations/Exponentiation.cpp
        PolynomialTree/PolynomialPrimitives/Operations/Operations/Exponentiation.h
        Parser/Parser.cpp
        Parser/Parser.h
        PolynomialTree/PolynomialPrimitives/Associativity.h
        Exceptions/ParserExceptions/ParseException.cpp
        Exceptions/ParserExceptions/ParseException.h
        Exceptions/ParserExceptions/DivisionByZero.cpp
        Exceptions/ParserExceptions/DivisionByZero.h
        Exceptions/ParserExceptions/LostOperand.cpp
        Exceptions/ParserExceptions/LostOperand.h
        Exceptions/ParserExceptions/WrongToken.cpp
        Exceptions/ParserExceptions/WrongToken.h
        Exceptions/ParserExceptions/UnsupportedOperation.cpp
        Exceptions/ParserExceptions/UnsupportedOperation.h
        Exceptions/ParserExceptions/InvalidArgument.cpp
        Exceptions/ParserExceptions/InvalidArgument.h
        PolynomialOperations/MonomialOrder/MonomialOrder.h
        PolynomialOperations/MonomialOrder/Orders/Lex.cpp
        PolynomialOperations/MonomialOrder/Orders/Lex.h
        Utils/Utils.h PolynomialOperations/Simplify/Simplify.h
        Exceptions/OrderExceptions/OrderException.cpp
        Exceptions/OrderExceptions/OrderException.h
        Exceptions/OrderExceptions/UnexpectedOperationException.cpp
        Exceptions/OrderExceptions/UnexpectedOperationException.h
        PolynomialOperations/MonomialOrder/Orders/Grlex.cpp
        PolynomialOperations/MonomialOrder/Orders/Grlex.h
        PolynomialOperations/MonomialOrder/Orders/Plex.cpp
        PolynomialOperations/MonomialOrder/Orders/Plex.h
        FGLM/FGLM.cpp
        FGLM/FGLM.h
        PolynomialOperations/MonomialOrder/MonomialOrder.cpp
        PolynomialOperations/Simplify/Equals.h
        PolynomialOperations/Simplify/Equals.cpp
        PolynomialOperations/Simplify/Simplify.cpp
        PolynomialOperations/ArithmeticOperations/ArithmeticOperations.h
        PolynomialOperations/ArithmeticOperations/ArithmeticOperations.cpp
        PolynomialOperations/MonomialslJoiner/Join.h
        PolynomialOperations/MonomialslJoiner/Join.cpp
        PolynomialTree/MonomialThings/MonomialThings.h
        PolynomialTree/MonomialThings/MonomialThings.cpp)

add_subdirectory(Google_tests)