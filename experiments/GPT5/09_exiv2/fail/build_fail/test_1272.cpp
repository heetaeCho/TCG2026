#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <string_view>
#include <cctype>

namespace Exiv2 { namespace Internal { std::string lower(std::string_view a) { std::string b; b.reserve(a.size()); for (auto c : a) b.push_back(std::tolower(static_cast<unsigned char>(c))); return b; } } }

TEST_F(UtilsTest_1272, LowerCaseConversion_Normal_1272) {
    std::string_view input = "Hello World";
    std::string expected = "hello world";

    std::string result = Exiv2::Internal::lower(input);
    
    EXPECT_EQ(result, expected);
}

TEST_F(UtilsTest_1272, LowerCaseConversion_EmptyString_1272) {
    std::string_view input = "";
    std::string expected = "";

    std::string result = Exiv2::Internal::lower(input);
    
    EXPECT_EQ(result, expected);
}

TEST_F(UtilsTest_1272, LowerCaseConversion_SingleCharacter_1272) {
    std::string_view input = "A";
    std::string expected = "a";

    std::string result = Exiv2::Internal::lower(input);
    
    EXPECT_EQ(result, expected);
}

TEST_F(UtilsTest_1272, LowerCaseConversion_MixedCase_1272) {
    std::string_view input = "ExIv2";
    std::string expected = "exiv2";

    std::string result = Exiv2::Internal::lower(input);
    
    EXPECT_EQ(result, expected);
}

TEST_F(UtilsTest_1272, LowerCaseConversion_NonAlphaCharacters_1272) {
    std::string_view input = "123!@#";
    std::string expected = "123!@#";

    std::string result = Exiv2::Internal::lower(input);
    
    EXPECT_EQ(result, expected);
}