# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests


add_executable(Google_Tests_run
        ../PolynomialTree/PolynomialPrimitives/Node/Node.h
        ../PolynomialTree/PolynomialPrimitives/Operands/Variable.cpp
        ../PolynomialTree/PolynomialPrimitives/Operands/Variable.h
        ../PolynomialTree/PolynomialPrimitives/Operands/Constant.cpp
        ../PolynomialTree/PolynomialPrimitives/Operands/Constant.h
        ../PolynomialTree/PolynomialPrimitives/Operations/AbstractOperations/AbstractUnaryOperation.cpp
        ../PolynomialTree/PolynomialPrimitives/Operations/AbstractOperations/AbstractUnaryOperation.h
        ../PolynomialTree/PolynomialPrimitives/Operations/AbstractOperations/AbstractBinaryOperation.cpp
        ../PolynomialTree/PolynomialPrimitives/Operations/AbstractOperations/AbstractBinaryOperation.h
        ../PolynomialTree/PolynomialPrimitives/Operations/Operations/Sum.cpp
        ../PolynomialTree/PolynomialPrimitives/Operations/Operations/Sum.h
        ../PolynomialTree/PolynomialPrimitives/Operations/Operations/UnaryMinus.cpp
        ../PolynomialTree/PolynomialPrimitives/Operations/Operations/UnaryMinus.h
        ../PolynomialTree/PolynomialPrimitives/Operations/Operations/BinaryMinus.cpp
        ../PolynomialTree/PolynomialPrimitives/Operations/Operations/BinaryMinus.h
        ../PolynomialTree/PolynomialPrimitives/Operations/Operations/Divide.cpp
        ../PolynomialTree/PolynomialPrimitives/Operations/Operations/Divide.h
        ../PolynomialTree/PolynomialPrimitives/Operations/Operations/Multiplication.cpp
        ../PolynomialTree/PolynomialPrimitives/Operations/Operations/Multiplication.h
        ../PolynomialTree/PolynomialPrimitives/Operations/Operations/Exponentiation.cpp
        ../PolynomialTree/PolynomialPrimitives/Operations/Operations/Exponentiation.h
        ../Parser/Parser.cpp
        ../Parser/Parser.h
        ../PolynomialTree/PolynomialPrimitives/Associativity.h
        ../Exceptions/ParserExceptions/ParseException.cpp
        ../Exceptions/ParserExceptions/ParseException.h
        ../Exceptions/ParserExceptions/DivisionByZero.cpp
        ../Exceptions/ParserExceptions/DivisionByZero.h
        ../Exceptions/ParserExceptions/LostOperand.cpp
        ../Exceptions/ParserExceptions/LostOperand.h
        ../Exceptions/ParserExceptions/WrongToken.cpp
        ../Exceptions/ParserExceptions/WrongToken.h
        ../Exceptions/ParserExceptions/UnsupportedOperation.cpp
        ../Exceptions/ParserExceptions/UnsupportedOperation.h
        ../Exceptions/ParserExceptions/InvalidArgument.cpp
        ../Exceptions/ParserExceptions/InvalidArgument.h
        ParserTest.cpp TreeOperationTest.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main)
