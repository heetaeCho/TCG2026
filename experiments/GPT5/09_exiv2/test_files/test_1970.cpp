#include <gtest/gtest.h>
#include "XMPMeta-Parse.cpp"
#include "XMP_Const.h"

class DetermineInputEncodingTest : public ::testing::Test {
protected:
    // SetUp and TearDown can be used if any setup or cleanup is required
};

TEST_F(DetermineInputEncodingTest, TestEncodingUTF8_1970) {
    // Test case where the encoding is determined to be UTF8
    const XMP_Uns8 buffer[] = { 0x61, 0x00 }; // Represents 'a'
    size_t length = 2;

    XMP_OptionBits encoding = DetermineInputEncoding(buffer, length);
    
    // Verify that the encoding is UTF8
    EXPECT_EQ(encoding, kXMP_EncodeUTF8);
}

TEST_F(DetermineInputEncodingTest, TestEncodingUTF16Big_1971) {
    // Test case where the encoding is determined to be UTF16Big
    const XMP_Uns8 buffer[] = { 0x00, 0x61 }; // Represents 'a' in UTF16Big
    size_t length = 2;

    XMP_OptionBits encoding = DetermineInputEncoding(buffer, length);
    
    // Verify that the encoding is UTF16Big
    EXPECT_EQ(encoding, kXMP_EncodeUTF16Big);
}

TEST_F(DetermineInputEncodingTest, TestEncodingUTF32Big_1972) {
    // Test case where the encoding is determined to be UTF32Big
    const XMP_Uns8 buffer[] = { 0x00, 0x00, 0x00, 0x61 }; // Represents 'a' in UTF32Big
    size_t length = 4;

    XMP_OptionBits encoding = DetermineInputEncoding(buffer, length);
    
    // Verify that the encoding is UTF32Big
    EXPECT_EQ(encoding, kXMP_EncodeUTF32Big);
}

TEST_F(DetermineInputEncodingTest, TestEncodingUTF16Little_1973) {
    // Test case where the encoding is determined to be UTF16Little
    const XMP_Uns8 buffer[] = { 0x61, 0x00 }; // Represents 'a' in UTF16Little
    size_t length = 2;

    XMP_OptionBits encoding = DetermineInputEncoding(buffer, length);
    
    // Verify that the encoding is UTF16Little
    EXPECT_EQ(encoding, kXMP_EncodeUTF16Little);
}

TEST_F(DetermineInputEncodingTest, TestEncodingUTF32Little_1974) {
    // Test case where the encoding is determined to be UTF32Little
    const XMP_Uns8 buffer[] = { 0x61, 0x00, 0x00, 0x00 }; // Represents 'a' in UTF32Little
    size_t length = 4;

    XMP_OptionBits encoding = DetermineInputEncoding(buffer, length);
    
    // Verify that the encoding is UTF32Little
    EXPECT_EQ(encoding, kXMP_EncodeUTF32Little);
}

TEST_F(DetermineInputEncodingTest, TestEncodingInvalidLength_1975) {
    // Test case where the length is too short to determine the encoding
    const XMP_Uns8 buffer[] = { 0x61 }; // Just 'a', not enough length
    size_t length = 1;

    XMP_OptionBits encoding = DetermineInputEncoding(buffer, length);
    
    // Verify that the encoding is UTF8 (fallback default)
    EXPECT_EQ(encoding, kXMP_EncodeUTF8);
}

TEST_F(DetermineInputEncodingTest, TestEncodingEFByte_1976) {
    // Test case where the encoding is determined to be UTF8 due to the 0xEF byte
    const XMP_Uns8 buffer[] = { 0xEF, 0xBB, 0xBF }; // BOM for UTF-8
    size_t length = 3;

    XMP_OptionBits encoding = DetermineInputEncoding(buffer, length);
    
    // Verify that the encoding is UTF8
    EXPECT_EQ(encoding, kXMP_EncodeUTF8);
}

TEST_F(DetermineInputEncodingTest, TestEncodingFEByte_1977) {
    // Test case where the encoding is determined to be UTF16Big due to the 0xFE byte
    const XMP_Uns8 buffer[] = { 0xFE, 0xFF }; // BOM for UTF-16 Big Endian
    size_t length = 2;

    XMP_OptionBits encoding = DetermineInputEncoding(buffer, length);
    
    // Verify that the encoding is UTF16Big
    EXPECT_EQ(encoding, kXMP_EncodeUTF16Big);
}

TEST_F(DetermineInputEncodingTest, TestEncodingInvalidByte_1978) {
    // Test case where the encoding cannot be determined due to invalid byte pattern
    const XMP_Uns8 buffer[] = { 0xFF, 0xFF, 0xFF }; // Invalid sequence
    size_t length = 3;

    XMP_OptionBits encoding = DetermineInputEncoding(buffer, length);
    
    // Verify that the encoding is UTF8 (fallback default)
    EXPECT_EQ(encoding, kXMP_EncodeUTF8);
}