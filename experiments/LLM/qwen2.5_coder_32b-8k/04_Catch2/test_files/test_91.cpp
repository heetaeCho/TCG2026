#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/catch_tostring.hpp"



using namespace Catch;

using namespace std::chrono_literals;



TEST(CatchToStringTest_91, ConvertBoolTrue_91) {

    EXPECT_EQ(StringMaker<bool>::convert(true), "true");

}



TEST(CatchToStringTest_91, ConvertBoolFalse_91) {

    EXPECT_EQ(StringMaker<bool>::convert(false), "false");

}



TEST(CatchToStringTest_91, ConvertNullptr_91) {

    EXPECT_EQ(StringMaker<std::nullptr_t>::convert(nullptr), "nullptr");

}



TEST(CatchToStringTest_91, ConvertCharPointer_91) {

    const char* str = "Hello";

    EXPECT_EQ(StringMaker<char const*>::convert(str), "Hello");

}



TEST(CatchToStringTest_91, ConvertCharArray_91) {

    const char arr[] = "World";

    EXPECT_EQ(StringMaker<char>::convert(arr), "World");

}



TEST(CatchToStringTest_91, ConvertStdString_91) {

    std::string str = "Catch2";

    EXPECT_EQ(StringMaker<std::string>::convert(str), "Catch2");

}



TEST(CatchToStringTest_91, ConvertStringView_91) {

    std::string_view sv = "StringView";

    EXPECT_EQ(StringMaker<std::string_view>::convert(sv), "StringView");

}



TEST(CatchToStringTest_91, ConvertInt_91) {

    int value = 42;

    EXPECT_EQ(StringMaker<int>::convert(value), "42");

}



TEST(CatchToStringTest_91, ConvertLong_91) {

    long value = 123456789L;

    EXPECT_EQ(StringMaker<long>::convert(value), "123456789");

}



TEST(CatchToStringTest_91, ConvertLongLong_91) {

    long long value = 9876543210LL;

    EXPECT_EQ(StringMaker<long long>::convert(value), "9876543210");

}



TEST(CatchToStringTest_91, ConvertUnsignedInt_91) {

    unsigned int value = 42u;

    EXPECT_EQ(StringMaker<unsigned int>::convert(value), "42");

}



TEST(CatchToStringTest_91, ConvertUnsignedLong_91) {

    unsigned long value = 123456789UL;

    EXPECT_EQ(StringMaker<unsigned long>::convert(value), "123456789");

}



TEST(CatchToStringTest_91, ConvertUnsignedLongLong_91) {

    unsigned long long value = 9876543210ULL;

    EXPECT_EQ(StringMaker<unsigned long long>::convert(value), "9876543210");

}



TEST(CatchToStringTest_91, ConvertSignedChar_91) {

    signed char value = 'A';

    EXPECT_EQ(StringMaker<signed char>::convert(value), "A");

}



TEST(CatchToStringTest_91, ConvertUnsignedChar_91) {

    unsigned char value = 'B';

    EXPECT_EQ(StringMaker<unsigned char>::convert(value), "B");

}



TEST(CatchToStringTest_91, ConvertFloat_91) {

    float value = 3.14f;

    std::string result = StringMaker<float>::convert(value);

    EXPECT_TRUE(result.find("3.14") != std::string::npos); // Float comparison can be tricky

}



TEST(CatchToStringTest_91, ConvertDouble_91) {

    double value = 2.718;

    std::string result = StringMaker<double>::convert(value);

    EXPECT_TRUE(result.find("2.718") != std::string::npos); // Double comparison can be tricky

}



TEST(CatchToStringTest_91, ConvertChronoDurationSeconds_91) {

    auto duration = 5s;

    EXPECT_EQ(StringMaker<std::chrono::duration<int>>::convert(duration), "5s");

}



TEST(CatchToStringTest_91, ConvertChronoDurationMinutes_91) {

    auto duration = 3min;

    EXPECT_EQ(StringMaker<std::chrono::duration<int, std::ratio<60>>>::convert(duration), "3m");

}



TEST(CatchToStringTest_91, ConvertChronoDurationHours_91) {

    auto duration = 2h;

    EXPECT_EQ(StringMaker<std::chrono::duration<int, std::ratio<3600>>>::convert(duration), "2h");

}



TEST(CatchToStringTest_91, ConvertChronoTimePoint_91) {

    auto time_point = system_clock::now();

    std::string result = StringMaker<std::chrono::system_clock::time_point>::convert(time_point);

    EXPECT_FALSE(result.empty()); // The exact format is not specified, but it should not be empty

}



TEST(CatchToStringTest_91, ConvertChronoTimePointCustomClock_91) {

    using custom_clock = std::chrono::steady_clock;

    auto time_point = custom_clock::now();

    std::string result = StringMaker<custom_clock::time_point>::convert(time_point);

    EXPECT_FALSE(result.empty()); // The exact format is not specified, but it should not be empty

}
