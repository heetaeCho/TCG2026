#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/catch_tostring.hpp"



TEST(StringMaker_CharPtr_Convert_263, NormalOperationNonNullString_263) {

    char str[] = "Hello, World!";

    EXPECT_EQ(Catch::StringMaker<char*>::convert(str), "Hello, World!");

}



TEST(StringMaker_CharPtr_Convert_263, BoundaryConditionEmptyString_263) {

    char str[] = "";

    EXPECT_EQ(Catch::StringMaker<char*>::convert(str), "");

}



TEST(StringMaker_CharPtr_Convert_263, ExceptionalCaseNullPointer_263) {

    char* str = nullptr;

    EXPECT_EQ(Catch::StringMaker<char*>::convert(str), "{null string}");

}
