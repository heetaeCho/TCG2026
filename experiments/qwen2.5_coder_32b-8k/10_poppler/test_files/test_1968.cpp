#include <gtest/gtest.h>

#include <cctype>



// Assuming parseNumericName is part of a namespace or class, we'll define it here for testing purposes.

namespace GfxFont {

    static bool parseNumericName(const char *s, bool hex, unsigned int *u);

}



using ::testing::Test;



class ParseNumericNameTest_1968 : public Test {

protected:

    unsigned int result;

};



TEST_F(ParseNumericNameTest_1968, ValidHexInput_1968) {

    const char* input = "1A";

    bool success = GfxFont::parseNumericName(input, true, &result);

    EXPECT_TRUE(success);

    EXPECT_EQ(result, 26U);

}



TEST_F(ParseNumericNameTest_1968, ValidHexInputWithAlphaPrefix_1968) {

    const char* input = "A1A";

    bool success = GfxFont::parseNumericName(input, true, &result);

    EXPECT_TRUE(success);

    EXPECT_EQ(result, 257U);

}



TEST_F(ParseNumericNameTest_1968, InvalidHexInputTooShort_1968) {

    const char* input = "A";

    bool success = GfxFont::parseNumericName(input, true, &result);

    EXPECT_FALSE(success);

}



TEST_F(ParseNumericNameTest_1968, InvalidHexInputTooLong_1968) {

    const char* input = "123";

    bool success = GfxFont::parseNumericName(input, true, &result);

    EXPECT_FALSE(success);

}



TEST_F(ParseNumericNameTest_1968, ValidAlphaPrefixOnly_1968) {

    const char* input = "A";

    bool success = GfxFont::parseNumericName(input, true, &result);

    EXPECT_FALSE(success);

}



TEST_F(ParseNumericNameTest_1968, ValidDecimalInput_1968) {

    const char* input = "257";

    bool success = GfxFont::parseNumericName(input, false, &result);

    EXPECT_TRUE(success);

    EXPECT_EQ(result, 257U);

}



TEST_F(ParseNumericNameTest_1968, InvalidDecimalInputWithNonNumericSuffix_1968) {

    const char* input = "257abc";

    bool success = GfxFont::parseNumericName(input, false, &result);

    EXPECT_TRUE(success);

    EXPECT_EQ(result, 257U);

}



TEST_F(ParseNumericNameTest_1968, ValidAlphabeticPrefixDecimalInput_1968) {

    const char* input = "Abc123";

    bool success = GfxFont::parseNumericName(input, false, &result);

    EXPECT_TRUE(success);

    EXPECT_EQ(result, 0U); // The function skips alphabetic characters at the start in decimal mode

}



TEST_F(ParseNumericNameTest_1968, InvalidInputEmptyString_1968) {

    const char* input = "";

    bool success = GfxFont::parseNumericName(input, false, &result);

    EXPECT_FALSE(success);

}



TEST_F(ParseNumericNameTest_1968, InvalidInputNonNumeric_1968) {

    const char* input = "abc";

    bool success = GfxFont::parseNumericName(input, false, &result);

    EXPECT_FALSE(success);

}
