#include <gtest/gtest.h>

#include "catch2/catch_tostring.hpp"

#include <chrono>



using namespace std::chrono;



TEST(StringMakerTest_100, ConvertDurationSeconds_100) {

    duration<int> dur(42);

    EXPECT_EQ(Catch::StringMaker<duration<int>>::convert(dur), "42 s");

}



TEST(StringMakerTest_100, ConvertDurationMilliseconds_100) {

    duration<int, std::milli> dur(42);

    EXPECT_EQ(Catch::StringMaker<duration<int, std::milli>>::convert(dur), "42 ms");

}



TEST(StringMakerTest_100, ConvertDurationMicroseconds_100) {

    duration<int, std::micro> dur(42);

    EXPECT_EQ(Catch::StringMaker<duration<int, std::micro>>::convert(dur), "42 us");

}



TEST(StringMakerTest_100, ConvertDurationNanoseconds_100) {

    duration<int, std::nano> dur(42);

    EXPECT_EQ(Catch::StringMaker<duration<int, std::nano>>::convert(dur), "42 ns");

}



TEST(StringMakerTest_100, ConvertDurationMinutes_100) {

    minutes dur(42);

    EXPECT_EQ(Catch::StringMaker<minutes>::convert(dur), "42 m");

}



TEST(StringMakerTest_100, ConvertDurationHours_100) {

    hours dur(42);

    EXPECT_EQ(Catch::StringMaker<hours>::convert(dur), "42 h");

}



TEST(StringMakerTest_100, ConvertBoolTrue_100) {

    bool b = true;

    EXPECT_EQ(Catch::StringMaker<bool>::convert(b), "true");

}



TEST(StringMakerTest_100, ConvertBoolFalse_100) {

    bool b = false;

    EXPECT_EQ(Catch::StringMaker<bool>::convert(b), "false");

}



TEST(StringMakerTest_100, ConvertNullptr_100) {

    std::nullptr_t nptr = nullptr;

    EXPECT_EQ(Catch::StringMaker<std::nullptr_t>::convert(nptr), "nullptr");

}



TEST(StringMakerTest_100, ConvertCharPointer_100) {

    const char* str = "Hello";

    EXPECT_EQ(Catch::StringMaker<char const*>::convert(str), "Hello");

}



TEST(StringMakerTest_100, ConvertStdString_100) {

    std::string str = "World";

    EXPECT_EQ(Catch::StringMaker<std::string>::convert(str), "World");

}



TEST(StringMakerTest_100, ConvertChar_100) {

    char c = 'A';

    EXPECT_EQ(Catch::StringMaker<char>::convert(c), "A");

}



TEST(StringMakerTest_100, ConvertInt_100) {

    int value = 42;

    EXPECT_EQ(Catch::StringMaker<int>::convert(value), "42");

}



TEST(StringMakerTest_100, ConvertUnsignedInt_100) {

    unsigned int value = 42u;

    EXPECT_EQ(Catch::StringMaker<unsigned int>::convert(value), "42");

}



TEST(StringMakerTest_100, ConvertFloat_100) {

    float value = 3.14f;

    EXPECT_EQ(Catch::StringMaker<float>::convert(value), "3.14");

}



TEST(StringMakerTest_100, ConvertDouble_100) {

    double value = 2.718;

    EXPECT_EQ(Catch::StringMaker<double>::convert(value), "2.718");

}
