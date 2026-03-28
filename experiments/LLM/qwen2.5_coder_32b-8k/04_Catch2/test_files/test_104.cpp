#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <chrono>

#include "catch2/catch_tostring.hpp"



using namespace ::testing;

using namespace Catch;



TEST(CatchToStringTest_104, ConvertTimePointSinceEpoch_104) {

    auto now = std::chrono::system_clock::now();

    std::string result = convert(now);

    EXPECT_THAT(result, EndsWith(" since epoch"));

}



TEST(CatchToStringTest_104, ConvertDurationSeconds_104) {

    std::chrono::seconds duration(5);

    std::string result = convert(duration);

    EXPECT_EQ(result, "5 s");

}



TEST(CatchToStringTest_104, ConvertDurationMinutes_104) {

    std::chrono::minutes duration(2);

    std::string result = convert(duration);

    EXPECT_EQ(result, "2 min");

}



TEST(CatchToStringTest_104, ConvertDurationHours_104) {

    std::chrono::hours duration(3);

    std::string result = convert(duration);

    EXPECT_EQ(result, "3 h");

}



TEST(CatchToStringTest_104, ConvertBoolTrue_104) {

    bool value = true;

    std::string result = StringMaker<bool>::convert(value);

    EXPECT_EQ(result, "true");

}



TEST(CatchToStringTest_104, ConvertBoolFalse_104) {

    bool value = false;

    std::string result = StringMaker<bool>::convert(value);

    EXPECT_EQ(result, "false");

}



TEST(CatchToStringTest_104, ConvertNullptr_104) {

    std::nullptr_t value = nullptr;

    std::string result = StringMaker<std::nullptr_t>::convert(value);

    EXPECT_EQ(result, "nullptr");

}



TEST(CatchToStringTest_104, ConvertStringLiteral_104) {

    const char* str = "Hello";

    std::string result = convert(str);

    EXPECT_EQ(result, "Hello");

}



TEST(CatchToStringTest_104, ConvertStdString_104) {

    std::string str = "World";

    std::string result = StringMaker<std::string>::convert(str);

    EXPECT_EQ(result, "World");

}



TEST(CatchToStringTest_104, ConvertWStringLiteral_104) {

    const wchar_t* wstr = L"Hello";

    std::string result = convert(wstr);

    EXPECT_EQ(result, u8"Hello");

}



TEST(CatchToStringTest_104, ConvertWStdString_104) {

    std::wstring wstr = L"World";

    std::string result = StringMaker<std::wstring>::convert(wstr);

    EXPECT_EQ(result, u8"World");

}



TEST(CatchToStringTest_104, ConvertByte_104) {

    std::byte value = std::byte{42};

    std::string result = StringMaker<std::byte>::convert(value);

    EXPECT_EQ(result, "std::byte{42}");

}



TEST(CatchToStringTest_104, ConvertInt_104) {

    int value = 42;

    std::string result = StringMaker<int>::convert(value);

    EXPECT_EQ(result, "42");

}



TEST(CatchToStringTest_104, ConvertLong_104) {

    long value = 42L;

    std::string result = StringMaker<long>::convert(value);

    EXPECT_EQ(result, "42");

}



TEST(CatchToStringTest_104, ConvertLongLong_104) {

    long long value = 42LL;

    std::string result = StringMaker<long long>::convert(value);

    EXPECT_EQ(result, "42");

}



TEST(CatchToStringTest_104, ConvertUnsignedInt_104) {

    unsigned int value = 42U;

    std::string result = StringMaker<unsigned int>::convert(value);

    EXPECT_EQ(result, "42");

}



TEST(CatchToStringTest_104, ConvertUnsignedLong_104) {

    unsigned long value = 42UL;

    std::string result = StringMaker<unsigned long>::convert(value);

    EXPECT_EQ(result, "42");

}



TEST(CatchToStringTest_104, ConvertUnsignedLongLong_104) {

    unsigned long long value = 42ULL;

    std::string result = StringMaker<unsigned long long>::convert(value);

    EXPECT_EQ(result, "42");

}



TEST(CatchToStringTest_104, ConvertSignedChar_104) {

    signed char value = 'A';

    std::string result = StringMaker<signed char>::convert(value);

    EXPECT_EQ(result, "'A'");

}



TEST(CatchToStringTest_104, ConvertChar_104) {

    char value = 'B';

    std::string result = StringMaker<char>::convert(value);

    EXPECT_EQ(result, "'B'");

}



TEST(CatchToStringTest_104, ConvertUnsignedChar_104) {

    unsigned char value = 'C';

    std::string result = StringMaker<unsigned char>::convert(value);

    EXPECT_EQ(result, "'C'");

}



TEST(CatchToStringTest_104, ConvertFloat_104) {

    float value = 3.14f;

    std::string result = StringMaker<float>::convert(value);

    EXPECT_EQ(result, "3.14");

}



TEST(CatchToStringTest_104, ConvertDouble_104) {

    double value = 2.718;

    std::string result = StringMaker<double>::convert(value);

    EXPECT_EQ(result, "2.718");

}
