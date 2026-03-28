#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/catch_tostring.hpp"



namespace Catch {

    template<typename T, typename>

    struct StringMaker;



    static std::string convert(char const* str) { return std::string(str); }

    static std::string convert(std::nullptr_t) { return "nullptr"; }

}



TEST(CatchToStringTest_92, ConvertCharArray_ReturnsCorrectString_92) {

    const char arr[] = "Hello, World!";

    EXPECT_EQ(Catch::convert(arr), "Hello, World!");

}



TEST(CatchToStringTest_92, ConvertNullptr_ReturnsCorrectString_92) {

    EXPECT_EQ(Catch::convert(nullptr), "nullptr");

}



TEST(CatchToStringTest_92, ConvertBoolTrue_ReturnsCorrectString_92) {

    EXPECT_EQ(Catch::StringMaker<bool>::convert(true), "true");

}



TEST(CatchToStringTest_92, ConvertBoolFalse_ReturnsCorrectString_92) {

    EXPECT_EQ(Catch::StringMaker<bool>::convert(false), "false");

}



TEST(CatchToStringTest_92, ConvertInt_ReturnsCorrectString_92) {

    EXPECT_EQ(Catch::StringMaker<int>::convert(42), "42");

}



TEST(CatchToStringTest_92, ConvertLong_ReturnsCorrectString_92) {

    EXPECT_EQ(Catch::StringMaker<long>::convert(123456789L), "123456789");

}



TEST(CatchToStringTest_92, ConvertLongLong_ReturnsCorrectString_92) {

    EXPECT_EQ(Catch::StringMaker<long long>::convert(9876543210LL), "9876543210");

}



TEST(CatchToStringTest_92, ConvertUnsignedInt_ReturnsCorrectString_92) {

    EXPECT_EQ(Catch::StringMaker<unsigned int>::convert(42u), "42");

}



TEST(CatchToStringTest_92, ConvertUnsignedLong_ReturnsCorrectString_92) {

    EXPECT_EQ(Catch::StringMaker<unsigned long>::convert(123456789UL), "123456789");

}



TEST(CatchToStringTest_92, ConvertUnsignedLongLong_ReturnsCorrectString_92) {

    EXPECT_EQ(Catch::StringMaker<unsigned long long>::convert(9876543210ULL), "9876543210");

}



TEST(CatchToStringTest_92, ConvertSignedChar_ReturnsCorrectString_92) {

    signed char sc = 'A';

    EXPECT_EQ(Catch::StringMaker<signed char>::convert(sc), "A");

}



TEST(CatchToStringTest_92, ConvertChar_ReturnsCorrectString_92) {

    EXPECT_EQ(Catch::StringMaker<char>::convert('B'), "B");

}



TEST(CatchToStringTest_92, ConvertUnsignedChar_ReturnsCorrectString_92) {

    unsigned char uc = 'C';

    EXPECT_EQ(Catch::StringMaker<unsigned char>::convert(uc), "C");

}



TEST(CatchToStringTest_92, ConvertFloat_ReturnsCorrectString_92) {

    EXPECT_FLOAT_EQ(std::stof(Catch::StringMaker<float>::convert(3.14f)), 3.14f);

}



TEST(CatchToStringTest_92, ConvertDouble_ReturnsCorrectString_92) {

    EXPECT_DOUBLE_EQ(std::stod(Catch::StringMaker<double>::convert(3.14159)), 3.14159);

}



// Note: Catch::Approx is not provided in the partial code, so this test is omitted.

// TEST(CatchToStringTest_92, ConvertCatchApprox_ReturnsCorrectString_92) {

//     Catch::Approx approx = Catch::Approx(3.14).epsilon(0.01);

//     EXPECT_EQ(Catch::StringMaker<Catch::Approx>::convert(approx), "Approx( 3.14 )");

// }



TEST(CatchToStringTest_92, ConvertCharPointer_ReturnsCorrectString_92) {

    const char* str = "Hello";

    EXPECT_EQ(Catch::StringMaker<char const*>::convert(str), "Hello");

}



TEST(CatchToStringTest_92, ConvertNullCharPointer_ReturnsCorrectString_92) {

    const char* nullStr = nullptr;

    EXPECT_EQ(Catch::StringMaker<char const*>::convert(nullStr), "nullptr");

}
