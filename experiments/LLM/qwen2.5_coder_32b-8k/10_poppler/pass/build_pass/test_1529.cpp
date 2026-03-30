#include <gtest/gtest.h>

#include "UTF.cc"



namespace {



TEST(utf16CountUtf8BytesTest_1529, EmptyString_1529) {

    const uint16_t utf16[] = {0};

    EXPECT_EQ(utf16CountUtf8Bytes(utf16), 0);

}



TEST(utf16CountUtf8BytesTest_1529, SingleAsciiCharacter_1529) {

    const uint16_t utf16[] = {'A', 0};

    EXPECT_EQ(utf16CountUtf8Bytes(utf16), 1);

}



TEST(utf16CountUtf8BytesTest_1529, SingleTwoByteCharacter_1529) {

    const uint16_t utf16[] = {0x00A9, 0}; // Copyright sign

    EXPECT_EQ(utf16CountUtf8Bytes(utf16), 2);

}



TEST(utf16CountUtf8BytesTest_1529, SingleThreeByteCharacter_1529) {

    const uint16_t utf16[] = {0x4E2D, 0}; // CJK UNIFIED IDEOGRAPH-MIDDLE

    EXPECT_EQ(utf16CountUtf8Bytes(utf16), 3);

}



TEST(utf16CountUtf8BytesTest_1529, SingleFourByteCharacter_1529) {

    const uint16_t utf16[] = {0xD834, 0xDD1E}; // MUSICAL SYMBOL G CLEF

    EXPECT_EQ(utf16CountUtf8Bytes(utf16), 4);

}



TEST(utf16CountUtf8BytesTest_1529, MultipleCharactersMixedLengths_1529) {

    const uint16_t utf16[] = {'A', 0x00A9, 0x4E2D, 0xD834, 0xDD1E, 0};

    EXPECT_EQ(utf16CountUtf8Bytes(utf16), 1 + 2 + 3 + 4);

}



TEST(utf16CountUtf8BytesTest_1529, InvalidSurrogatePair_ReplacementChar_1529) {

    const uint16_t utf16[] = {0xD834, 'A', 0}; // Invalid surrogate pair

    EXPECT_EQ(utf16CountUtf8Bytes(utf16), 3 + 1);

}



TEST(utf16CountUtf8BytesTest_1529, BoundaryConditionMaxUcs4_1529) {

    const uint16_t utf16[] = {0xDBFF, 0xDFFF}; // Last valid Unicode character

    EXPECT_EQ(utf16CountUtf8Bytes(utf16), 4);

}



TEST(utf16CountUtf8BytesTest_1529, BoundaryConditionOverMaxUcs4_ReplacementChar_1529) {

    const uint16_t utf16[] = {0xDC00, 0xDFFF}; // Over max UCS4

    EXPECT_EQ(utf16CountUtf8Bytes(utf16), 3);

}



TEST(utf16CountUtf8BytesTest_1529, BoundaryConditionHighSurrogateOnly_ReplacementChar_1529) {

    const uint16_t utf16[] = {0xD834}; // High surrogate only

    EXPECT_EQ(utf16CountUtf8Bytes(utf16), 3);

}



TEST(utf16CountUtf8BytesTest_1529, BoundaryConditionLowSurrogateOnly_ReplacementChar_1529) {

    const uint16_t utf16[] = {0xDD1E}; // Low surrogate only

    EXPECT_EQ(utf16CountUtf8Bytes(utf16), 3);

}



TEST(utf16CountUtf8BytesTest_1529, BoundaryConditionRejectState_ReplacementChar_1529) {

    const uint16_t utf16[] = {0xFFFE}; // Invalid UTF-16 code point

    EXPECT_EQ(utf16CountUtf8Bytes(utf16), 3);

}



} // namespace
