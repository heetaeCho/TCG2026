#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Test fixture class if needed (empty in this case for simple tests)
class XMPMetaParseTest : public ::testing::Test {
protected:
    // Setup and teardown methods if needed
    void SetUp() override {}
    void TearDown() override {}
};

// TEST_ID: 1971 - Test normal UTF-8 byte sequences
TEST_F(XMPMetaParseTest, CountUTF8_ValidUtf8Test_1971) {
    XMP_Uns8 validUtf8[] = {0xC0, 0x80}; // valid 2-byte UTF-8 sequence
    XMP_Uns8* bufEnd = validUtf8 + sizeof(validUtf8);

    int byteCount = CountUTF8(validUtf8, bufEnd);

    // Test that the byte count for valid UTF-8 sequence is as expected
    EXPECT_EQ(byteCount, 2);
}

// TEST_ID: 1972 - Test invalid UTF-8 sequence (not enough bytes for a valid sequence)
TEST_F(XMPMetaParseTest, CountUTF8_InvalidUtf8Test_1972) {
    XMP_Uns8 invalidUtf8[] = {0xC0}; // Only one byte, but it's not a valid start
    XMP_Uns8* bufEnd = invalidUtf8 + sizeof(invalidUtf8);

    int byteCount = CountUTF8(invalidUtf8, bufEnd);

    // Test that an invalid UTF-8 sequence returns 0
    EXPECT_EQ(byteCount, 0);
}

// TEST_ID: 1973 - Test sequence where charStart >= bufEnd (error case)
TEST_F(XMPMetaParseTest, CountUTF8_CharStartGreaterThanBufEnd_1973) {
    XMP_Uns8 validUtf8[] = {0xC0, 0x80}; // valid 2-byte UTF-8 sequence
    XMP_Uns8* charStart = validUtf8 + 2; // Start beyond the end of the buffer
    XMP_Uns8* bufEnd = validUtf8 + 2;

    int byteCount = CountUTF8(charStart, bufEnd);

    // Test that when charStart >= bufEnd, the function returns 0
    EXPECT_EQ(byteCount, 0);
}

// TEST_ID: 1974 - Test sequence where first byte is not a valid UTF-8 start byte
TEST_F(XMPMetaParseTest, CountUTF8_InvalidFirstByte_1974) {
    XMP_Uns8 invalidUtf8[] = {0x80, 0x80}; // Invalid start byte (0x80 is not valid)
    XMP_Uns8* bufEnd = invalidUtf8 + sizeof(invalidUtf8);

    int byteCount = CountUTF8(invalidUtf8, bufEnd);

    // Test that the function returns 0 for invalid start byte
    EXPECT_EQ(byteCount, 0);
}

// TEST_ID: 1975 - Test boundary where buffer is too small to complete UTF-8 sequence
TEST_F(XMPMetaParseTest, CountUTF8_BufferTooSmall_1975) {
    XMP_Uns8 validUtf8[] = {0xC0, 0x80}; // valid 2-byte UTF-8 sequence
    XMP_Uns8* bufEnd = validUtf8 + 1; // Only one byte available

    int byteCount = CountUTF8(validUtf8, bufEnd);

    // Test that when the buffer is too small, the function returns a negative value
    EXPECT_EQ(byteCount, -2);
}

// TEST_ID: 1976 - Test empty buffer
TEST_F(XMPMetaParseTest, CountUTF8_EmptyBuffer_1976) {
    XMP_Uns8 empty[] = {};
    XMP_Uns8* bufEnd = empty + 0;

    int byteCount = CountUTF8(empty, bufEnd);

    // Test that an empty buffer returns 0
    EXPECT_EQ(byteCount, 0);
}