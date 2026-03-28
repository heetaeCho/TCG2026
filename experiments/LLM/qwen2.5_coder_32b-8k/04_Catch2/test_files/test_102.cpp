#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_reusable_string_stream.hpp"

#include "./TestProjects/Catch2/src/catch2/catch_tostring.hpp"



using namespace Catch;

using ::testing::Return;



TEST(StringMakerTests_102, ConvertDurationMinutes_102) {

    std::chrono::duration<int64_t, std::ratio<60>> duration(5);

    EXPECT_EQ(StringMaker<decltype(duration)>::convert(duration), "5 m");

}



TEST(StringMakerTests_102, ConvertBoolTrue_102) {

    bool b = true;

    EXPECT_EQ(StringMaker<bool>::convert(b), "true");

}



TEST(StringMakerTests_102, ConvertBoolFalse_102) {

    bool b = false;

    EXPECT_EQ(StringMaker<bool>::convert(b), "false");

}



TEST(StringMakerTests_102, ConvertNullptr_102) {

    std::nullptr_t nptr = nullptr;

    EXPECT_EQ(StringMaker<std::nullptr_t>::convert(nptr), "nullptr");

}



TEST(StringMakerTests_102, ConvertCharPointer_102) {

    char const* str = "test";

    EXPECT_EQ(StringMaker<char const*>::convert(str), "test");

}



TEST(StringMakerTests_102, ConvertString_102) {

    std::string str = "example";

    EXPECT_EQ(StringMaker<std::string>::convert(str), "example");

}



TEST(StringMakerTests_102, ConvertInt_102) {

    int value = 42;

    EXPECT_EQ(StringMaker<int>::convert(value), "42");

}



TEST(StringMakerTests_102, ConvertDouble_102) {

    double value = 3.14159;

    EXPECT_EQ(StringMaker<double>::convert(value), "3.14159");

}
