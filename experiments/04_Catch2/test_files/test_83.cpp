#include <gtest/gtest.h>

#include <catch2/catch_tostring.hpp>



namespace Catch {

    static std::string convert(unsigned char const* str) {

        auto reinterpreted = reinterpret_cast<char const*>(str);

        return Detail::convertIntoString(StringRef(reinterpreted, Detail::catch_strnlen(reinterpreted, SZ)));

    }

}



TEST(CatchToStringTest_83, ConvertUnsignedCharPointer_NormalOperation_83) {

    unsigned char const* input = reinterpret_cast<unsigned char const*>("test");

    std::string expectedOutput = "test";

    EXPECT_EQ(Catch::convert(input), expectedOutput);

}



TEST(CatchToStringTest_83, ConvertUnsignedCharPointer_EmptyString_83) {

    unsigned char const* input = reinterpret_cast<unsigned char const*>("");

    std::string expectedOutput = "";

    EXPECT_EQ(Catch::convert(input), expectedOutput);

}



TEST(CatchToStringTest_83, ConvertUnsignedCharPointer_SpecialCharacters_83) {

    unsigned char const* input = reinterpret_cast<unsigned char const*>("t\0est");

    std::string expectedOutput = "t";

    EXPECT_EQ(Catch::convert(input), expectedOutput);

}



// Assuming SZ is defined and known to be large enough for this test

TEST(CatchToStringTest_83, ConvertUnsignedCharPointer_LargeString_83) {

    unsigned char const* input = reinterpret_cast<unsigned char const*>("ThisIsAVeryLongStringThatShouldNotBeTruncated");

    std::string expectedOutput = "ThisIsAVeryLongStringThatShouldNotBeTruncated";

    EXPECT_EQ(Catch::convert(input), expectedOutput);

}



// Assuming SZ is defined and known to be smaller than this test

TEST(CatchToStringTest_83, ConvertUnsignedCharPointer_StringLargerThanSZ_83) {

    unsigned char const* input = reinterpret_cast<unsigned char const*>("ThisIsAVeryLongStringThatShouldBeTruncated");

    std::string expectedOutput = "ThisIsAVeryLon"; // Assuming SZ is 16 for this test

    EXPECT_EQ(Catch::convert(input), expectedOutput);

}
