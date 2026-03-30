// File: tests/stringmaker_char_convert_276_test.cpp

#include <gtest/gtest.h>
#include <string>

// Include the provided interfaces
#include "Catch2/src/catch2/catch_tostring.hpp"

// We test only public/observable behavior from the interface.
// No assumptions about internal stringify formatting are made.

class StringMakerCharTest_276 : public ::testing::Test {};

// Normal case: printable ASCII ('A' == 65)
TEST_F(StringMakerCharTest_276, MatchesSignedCharConversionForPrintable_276) {
    const char c = 'A'; // 65
    const signed char sc = static_cast<signed char>(c);

    const std::string from_char =
        Catch::StringMaker<char>::convert(c);
    const std::string from_signed_char =
        Catch::StringMaker<signed char>::convert(sc);

    EXPECT_EQ(from_char, from_signed_char);
}

// Boundary: NUL (0)
TEST_F(StringMakerCharTest_276, MatchesSignedCharConversionForNullChar_276) {
    const char c = static_cast<char>(0);
    const signed char sc = static_cast<signed char>(0);

    const std::string from_char =
        Catch::StringMaker<char>::convert(c);
    const std::string from_signed_char =
        Catch::StringMaker<signed char>::convert(sc);

    EXPECT_EQ(from_char, from_signed_char);
}

// Boundary: DEL (127). Safe across signed/unsigned char platforms.
TEST_F(StringMakerCharTest_276, MatchesSignedCharConversionForDEL_276) {
    const char c = static_cast<char>(127);
    const signed char sc = static_cast<signed char>(127);

    const std::string from_char =
        Catch::StringMaker<char>::convert(c);
    const std::string from_signed_char =
        Catch::StringMaker<signed char>::convert(sc);

    EXPECT_EQ(from_char, from_signed_char);
}

// Broader coverage within portable range [0,127]:
// Verifies the relation holds for several representative values.
TEST_F(StringMakerCharTest_276, MatchesSignedCharConversionForSampledAscii_276) {
    const int samples[] = {0, 1, 7, 9, 10, 32, 48, 57, 65, 90, 97, 122, 126, 127};
    for (int v : samples) {
        const char c  = static_cast<char>(v);
        const signed char sc = static_cast<signed char>(v);

        const std::string from_char =
            Catch::StringMaker<char>::convert(c);
        const std::string from_signed_char =
            Catch::StringMaker<signed char>::convert(sc);

        EXPECT_EQ(from_char, from_signed_char) << "Mismatch at value " << v;
    }
}
