#include <gtest/gtest.h>
#include <string>

// We need to include the Catch2 header that declares StringMaker<signed char>
// Since we're testing the Catch2 library's StringMaker, we include the relevant headers.
#include "catch2/catch_tostring.hpp"

class StringMakerSignedCharTest_275 : public ::testing::Test {
protected:
    // Helper to call the function under test
    std::string convert(signed char value) {
        return Catch::StringMaker<signed char>::convert(value);
    }
};

// Test carriage return character
TEST_F(StringMakerSignedCharTest_275, CarriageReturn_275) {
    EXPECT_EQ(convert('\r'), "'\\r'");
}

// Test form feed character
TEST_F(StringMakerSignedCharTest_275, FormFeed_275) {
    EXPECT_EQ(convert('\f'), "'\\f'");
}

// Test newline character
TEST_F(StringMakerSignedCharTest_275, Newline_275) {
    EXPECT_EQ(convert('\n'), "'\\n'");
}

// Test tab character
TEST_F(StringMakerSignedCharTest_275, Tab_275) {
    EXPECT_EQ(convert('\t'), "'\\t'");
}

// Test null character (control character, value 0)
TEST_F(StringMakerSignedCharTest_275, NullCharacter_275) {
    signed char val = '\0';
    std::string result = convert(val);
    // '\0' is >= '\0' and < ' ', so it should stringify as unsigned int (0)
    EXPECT_EQ(result, Catch::StringMaker<unsigned int>::convert(static_cast<unsigned int>(0)));
}

// Test control character 1 (SOH)
TEST_F(StringMakerSignedCharTest_275, ControlChar1_275) {
    signed char val = 1;
    std::string result = convert(val);
    EXPECT_EQ(result, Catch::StringMaker<unsigned int>::convert(1u));
}

// Test control character just before space (value 31, US)
TEST_F(StringMakerSignedCharTest_275, ControlChar31_275) {
    signed char val = 31;
    std::string result = convert(val);
    EXPECT_EQ(result, Catch::StringMaker<unsigned int>::convert(31u));
}

// Test space character (value 32, which is ' ')
// Space is NOT < ' ', so it should go to the else branch and be printed as a quoted char
TEST_F(StringMakerSignedCharTest_275, SpaceCharacter_275) {
    signed char val = ' ';
    std::string result = convert(val);
    EXPECT_EQ(result, "' '");
}

// Test printable character 'A'
TEST_F(StringMakerSignedCharTest_275, PrintableCharA_275) {
    signed char val = 'A';
    std::string result = convert(val);
    EXPECT_EQ(result, "'A'");
}

// Test printable character 'z'
TEST_F(StringMakerSignedCharTest_275, PrintableCharZ_275) {
    signed char val = 'z';
    std::string result = convert(val);
    EXPECT_EQ(result, "'z'");
}

// Test printable character '0' (digit)
TEST_F(StringMakerSignedCharTest_275, PrintableDigit0_275) {
    signed char val = '0';
    std::string result = convert(val);
    EXPECT_EQ(result, "'0'");
}

// Test printable character '~' (tilde, value 126)
TEST_F(StringMakerSignedCharTest_275, PrintableTilde_275) {
    signed char val = '~';
    std::string result = convert(val);
    EXPECT_EQ(result, "'~'");
}

// Test negative value (-1)
// Negative values are < '\0', so they go to the else branch
TEST_F(StringMakerSignedCharTest_275, NegativeValue_275) {
    signed char val = -1;
    std::string result = convert(val);
    // -1 as signed char: not \r, \f, \n, \t, and not in [0, 32), so else branch
    // The else branch puts the char value into chstr[1]
    // The resulting string will be a 3-char string: quote, the byte, quote
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], '\'');
    EXPECT_EQ(result[1], static_cast<char>(-1));
    EXPECT_EQ(result[2], '\'');
}

// Test minimum signed char value (-128)
TEST_F(StringMakerSignedCharTest_275, MinSignedChar_275) {
    signed char val = -128;
    std::string result = convert(val);
    // Negative, so goes to else branch
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], '\'');
    EXPECT_EQ(result[1], static_cast<char>(-128));
    EXPECT_EQ(result[2], '\'');
}

// Test maximum signed char value (127)
TEST_F(StringMakerSignedCharTest_275, MaxSignedChar_275) {
    signed char val = 127;
    std::string result = convert(val);
    // 127 (DEL) is >= '\0' but not < ' ' (127 >= 32), so else branch
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], '\'');
    EXPECT_EQ(result[1], static_cast<char>(127));
    EXPECT_EQ(result[2], '\'');
}

// Test control character 2 (STX)
TEST_F(StringMakerSignedCharTest_275, ControlChar2_275) {
    signed char val = 2;
    std::string result = convert(val);
    EXPECT_EQ(result, Catch::StringMaker<unsigned int>::convert(2u));
}

// Test control character BEL (7)
TEST_F(StringMakerSignedCharTest_275, ControlCharBEL_275) {
    signed char val = 7;
    std::string result = convert(val);
    EXPECT_EQ(result, Catch::StringMaker<unsigned int>::convert(7u));
}

// Test character '!' (value 33, first printable after space)
TEST_F(StringMakerSignedCharTest_275, ExclamationMark_275) {
    signed char val = '!';
    std::string result = convert(val);
    EXPECT_EQ(result, "'!'");
}

// Test that \r is specifically handled (not as generic control char)
TEST_F(StringMakerSignedCharTest_275, CarriageReturnIsSpecial_275) {
    signed char val = '\r'; // value 13
    std::string result = convert(val);
    // It should be the escaped form, not the numeric form
    EXPECT_EQ(result, "'\\r'");
    EXPECT_NE(result, Catch::StringMaker<unsigned int>::convert(13u));
}

// Test that \n is specifically handled (not as generic control char)
TEST_F(StringMakerSignedCharTest_275, NewlineIsSpecial_275) {
    signed char val = '\n'; // value 10
    std::string result = convert(val);
    EXPECT_EQ(result, "'\\n'");
    EXPECT_NE(result, Catch::StringMaker<unsigned int>::convert(10u));
}

// Test that \t is specifically handled
TEST_F(StringMakerSignedCharTest_275, TabIsSpecial_275) {
    signed char val = '\t'; // value 9
    std::string result = convert(val);
    EXPECT_EQ(result, "'\\t'");
    EXPECT_NE(result, Catch::StringMaker<unsigned int>::convert(9u));
}

// Test that \f is specifically handled
TEST_F(StringMakerSignedCharTest_275, FormFeedIsSpecial_275) {
    signed char val = '\f'; // value 12
    std::string result = convert(val);
    EXPECT_EQ(result, "'\\f'");
    EXPECT_NE(result, Catch::StringMaker<unsigned int>::convert(12u));
}

// Test control character ESC (27)
TEST_F(StringMakerSignedCharTest_275, ControlCharESC_275) {
    signed char val = 27;
    std::string result = convert(val);
    EXPECT_EQ(result, Catch::StringMaker<unsigned int>::convert(27u));
}
