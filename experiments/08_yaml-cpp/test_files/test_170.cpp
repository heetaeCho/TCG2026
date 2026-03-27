#include <gtest/gtest.h>

#include "stream.cpp"  // Assuming this is how to include the file containing the function



namespace YAML {



class Utf8AdjustTest_170 : public ::testing::Test {

protected:

    // Setup and teardown can be done here if needed

};



TEST_F(Utf8AdjustTest_170, NormalOperationSingleByte_170) {

    unsigned long ch = 0x7F;  // Single byte character

    unsigned char lead_bits = 7;

    unsigned char rshift = 0;

    EXPECT_EQ(Utf8Adjust(ch, lead_bits, rshift), '\x7F');

}



TEST_F(Utf8AdjustTest_170, NormalOperationTwoBytes_170) {

    unsigned long ch = 0xFF;  // Two byte character

    unsigned char lead_bits = 5;

    unsigned char rshift = 6;

    EXPECT_EQ(Utf8Adjust(ch, lead_bits, rshift), '\xC3');  // First byte of the two-byte sequence for U+00FF

}



TEST_F(Utf8AdjustTest_170, NormalOperationThreeBytes_170) {

    unsigned long ch = 0x7FF;  // Three byte character

    unsigned char lead_bits = 4;

    unsigned char rshift = 12;

    EXPECT_EQ(Utf8Adjust(ch, lead_bits, rshift), '\xE7');  // First byte of the three-byte sequence for U+07FF

}



TEST_F(Utf8AdjustTest_170, NormalOperationFourBytes_170) {

    unsigned long ch = 0xFFFF;  // Four byte character

    unsigned char lead_bits = 3;

    unsigned char rshift = 18;

    EXPECT_EQ(Utf8Adjust(ch, lead_bits, rshift), '\xF4');  // First byte of the four-byte sequence for U+FFFF

}



TEST_F(Utf8AdjustTest_170, BoundaryConditionMaxSingleByte_170) {

    unsigned long ch = 0x7F;  // Max single byte character

    unsigned char lead_bits = 7;

    unsigned char rshift = 0;

    EXPECT_EQ(Utf8Adjust(ch, lead_bits, rshift), '\x7F');

}



TEST_F(Utf8AdjustTest_170, BoundaryConditionMinTwoBytes_170) {

    unsigned long ch = 0x80;  // Min two byte character

    unsigned char lead_bits = 5;

    unsigned char rshift = 6;

    EXPECT_EQ(Utf8Adjust(ch, lead_bits, rshift), '\xC2');  // First byte of the two-byte sequence for U+0080

}



TEST_F(Utf8AdjustTest_170, BoundaryConditionMaxTwoBytes_170) {

    unsigned long ch = 0x7FF;  // Max two byte character

    unsigned char lead_bits = 5;

    unsigned char rshift = 6;

    EXPECT_EQ(Utf8Adjust(ch, lead_bits, rshift), '\xDF');  // First byte of the two-byte sequence for U+07FF

}



TEST_F(Utf8AdjustTest_170, BoundaryConditionMinThreeBytes_170) {

    unsigned long ch = 0x800;  // Min three byte character

    unsigned char lead_bits = 4;

    unsigned char rshift = 12;

    EXPECT_EQ(Utf8Adjust(ch, lead_bits, rshift), '\xE0');  // First byte of the three-byte sequence for U+0800

}



TEST_F(Utf8AdjustTest_170, BoundaryConditionMaxThreeBytes_170) {

    unsigned long ch = 0xFFFF;  // Max three byte character

    unsigned char lead_bits = 4;

    unsigned char rshift = 12;

    EXPECT_EQ(Utf8Adjust(ch, lead_bits, rshift), '\xEF');  // First byte of the three-byte sequence for U+FFFF

}



TEST_F(Utf8AdjustTest_170, BoundaryConditionMinFourBytes_170) {

    unsigned long ch = 0x10000;  // Min four byte character

    unsigned char lead_bits = 3;

    unsigned char rshift = 18;

    EXPECT_EQ(Utf8Adjust(ch, lead_bits, rshift), '\xF0');  // First byte of the four-byte sequence for U+10000

}



TEST_F(Utf8AdjustTest_170, BoundaryConditionMaxFourBytes_170) {

    unsigned long ch = 0x10FFFF;  // Max four byte character in UTF-8

    unsigned char lead_bits = 3;

    unsigned char rshift = 18;

    EXPECT_EQ(Utf8Adjust(ch, lead_bits, rshift), '\xF4');  // First byte of the four-byte sequence for U+10FFFF

}



TEST_F(Utf8AdjustTest_170, InvalidCharacterTooLarge_170) {

    unsigned long ch = 0x110000;  // Beyond the max valid Unicode character

    unsigned char lead_bits = 3;

    unsigned char rshift = 18;

    EXPECT_NE(Utf8Adjust(ch, lead_bits, rshift), '\xF5');  // This should not produce a valid UTF-8 first byte

}



TEST_F(Utf8AdjustTest_170, InvalidLeadBitsTooLarge_170) {

    unsigned long ch = 0x1;  // Any character

    unsigned char lead_bits = 9;  // Lead bits too large for UTF-8 encoding

    unsigned char rshift = 0;

    EXPECT_NE(Utf8Adjust(ch, lead_bits, rshift), static_cast<char>(static_cast<unsigned char>(((1 << lead_bits) - 1) << (8 - lead_bits))));  // This should not produce a valid header

}



TEST_F(Utf8AdjustTest_170, InvalidRShiftTooLarge_170) {

    unsigned long ch = 0x1;  // Any character

    unsigned char lead_bits = 3;

    unsigned char rshift = 25;  // RShift too large for meaningful operation

    EXPECT_NE(Utf8Adjust(ch, lead_bits, rshift), static_cast<char>(static_cast<unsigned char>(((1 << lead_bits) - 1) << (8 - lead_bits))));  // This should not produce a valid header

}



}  // namespace YAML
