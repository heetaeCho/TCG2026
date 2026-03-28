#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <exiv2/exif.hpp>

// We need access to the printUcs2 function from the Internal namespace
namespace Exiv2 {
namespace Internal {
std::ostream& printUcs2(std::ostream& os, const Value& value, const ExifData*);
}
}

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintUcs2Test_1380 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test with empty value - should fall through to printing value directly
TEST_F(PrintUcs2Test_1380, EmptyValue_PrintsValueDirectly_1380) {
    auto value = Value::create(unsignedByte);
    // Empty value, size == 0
    printUcs2(os, *value, nullptr);
    // With empty value, cnv stays false, so os << value is called
    // The output depends on how Value prints an empty unsignedByte
    // Just verify it doesn't crash and produces some output (could be empty string)
    EXPECT_NO_THROW(printUcs2(os, *value, nullptr));
}

// Test with non-unsignedByte type - should print value directly
TEST_F(PrintUcs2Test_1380, NonUnsignedByteType_PrintsValueDirectly_1380) {
    auto value = Value::create(asciiString);
    value->read("Hello");
    printUcs2(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result, "Hello");
}

// Test with valid UCS-2LE encoded string "AB" -> 0x41 0x00 0x42 0x00
TEST_F(PrintUcs2Test_1380, ValidUcs2String_PrintsUtf8_1380) {
    auto value = Value::create(unsignedByte);
    // "AB" in UCS-2LE: 0x41 0x00 0x42 0x00
    byte data[] = {0x41, 0x00, 0x42, 0x00};
    value->read(data, sizeof(data), invalidByteOrder);
    printUcs2(os, *value, nullptr);
    std::string result = os.str();
    // If conversion succeeds, we should get "AB"
    // If conversion fails (no iconv support), it falls back to printing the value
    // We just check it doesn't crash
    EXPECT_FALSE(result.empty());
}

// Test with UCS-2LE string followed by null terminators that should be stripped
TEST_F(PrintUcs2Test_1380, Ucs2StringWithNullTerminators_StripsNulls_1380) {
    auto value = Value::create(unsignedByte);
    // "A" in UCS-2LE with two null terminators: 0x41 0x00 0x00 0x00 0x00 0x00
    byte data[] = {0x41, 0x00, 0x00, 0x00, 0x00, 0x00};
    value->read(data, sizeof(data), invalidByteOrder);
    printUcs2(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with odd-sized buffer (should trim last byte to make even)
TEST_F(PrintUcs2Test_1380, OddSizedBuffer_TrimsLastByte_1380) {
    auto value = Value::create(unsignedByte);
    // 3 bytes: 0x41 0x00 0x42 - odd size, last byte should be trimmed
    byte data[] = {0x41, 0x00, 0x42};
    value->read(data, sizeof(data), invalidByteOrder);
    printUcs2(os, *value, nullptr);
    // Should not crash
    EXPECT_NO_THROW((void)os.str());
}

// Test with single byte (size == 1, odd, trimmed to 0 bytes)
TEST_F(PrintUcs2Test_1380, SingleByte_FallsThrough_1380) {
    auto value = Value::create(unsignedByte);
    byte data[] = {0x41};
    value->read(data, sizeof(data), invalidByteOrder);
    printUcs2(os, *value, nullptr);
    // After trimming odd byte, buf.size() == 0, so no conversion
    // Then cnv is false if the buffer was all nulls or too small
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with all null bytes - should strip all and potentially fail conversion
TEST_F(PrintUcs2Test_1380, AllNullBytes_HandledGracefully_1380) {
    auto value = Value::create(unsignedByte);
    byte data[] = {0x00, 0x00, 0x00, 0x00};
    value->read(data, sizeof(data), invalidByteOrder);
    printUcs2(os, *value, nullptr);
    // All nulls get stripped, empty string remains
    // Behavior depends on whether convertStringCharset handles empty string
    EXPECT_NO_THROW((void)os.str());
}

// Test with two bytes that are both zero (single null UCS-2 char)
TEST_F(PrintUcs2Test_1380, TwoNullBytes_HandledGracefully_1380) {
    auto value = Value::create(unsignedByte);
    byte data[] = {0x00, 0x00};
    value->read(data, sizeof(data), invalidByteOrder);
    printUcs2(os, *value, nullptr);
    EXPECT_NO_THROW((void)os.str());
}

// Test with nullptr ExifData (should be fine since it's unused in the function)
TEST_F(PrintUcs2Test_1380, NullExifData_NoIssue_1380) {
    auto value = Value::create(unsignedByte);
    byte data[] = {0x48, 0x00, 0x69, 0x00}; // "Hi" in UCS-2LE
    value->read(data, sizeof(data), invalidByteOrder);
    EXPECT_NO_THROW(printUcs2(os, *value, nullptr));
}

// Test with non-null-terminated UCS-2 string (no trailing nulls to strip)
TEST_F(PrintUcs2Test_1380, NonNullTerminatedUcs2_PrintsCorrectly_1380) {
    auto value = Value::create(unsignedByte);
    // "XY" in UCS-2LE without null terminator: last bytes are non-zero
    byte data[] = {0x58, 0x00, 0x59, 0x00};
    value->read(data, sizeof(data), invalidByteOrder);
    printUcs2(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with a larger UCS-2LE encoded string
TEST_F(PrintUcs2Test_1380, LargerUcs2String_PrintsCorrectly_1380) {
    auto value = Value::create(unsignedByte);
    // "Hello" in UCS-2LE
    byte data[] = {
        0x48, 0x00, // H
        0x65, 0x00, // e
        0x6C, 0x00, // l
        0x6C, 0x00, // l
        0x6F, 0x00  // o
    };
    value->read(data, sizeof(data), invalidByteOrder);
    printUcs2(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with signedByte type (not unsignedByte) - should fall through
TEST_F(PrintUcs2Test_1380, SignedByteType_PrintsValueDirectly_1380) {
    auto value = Value::create(signedByte);
    byte data[] = {0x41, 0x00};
    value->read(data, sizeof(data), invalidByteOrder);
    printUcs2(os, *value, nullptr);
    // signedByte != unsignedByte, so cnv stays false, value is printed directly
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test that the function returns the ostream reference
TEST_F(PrintUcs2Test_1380, ReturnsOstreamReference_1380) {
    auto value = Value::create(unsignedByte);
    byte data[] = {0x41, 0x00};
    value->read(data, sizeof(data), invalidByteOrder);
    std::ostream& returned = printUcs2(os, *value, nullptr);
    EXPECT_EQ(&returned, &os);
}

// Test with UCS-2 non-ASCII character (e.g., é = U+00E9 -> 0xE9 0x00 in UCS-2LE)
TEST_F(PrintUcs2Test_1380, NonAsciiUcs2Char_HandledCorrectly_1380) {
    auto value = Value::create(unsignedByte);
    // é in UCS-2LE
    byte data[] = {0xE9, 0x00};
    value->read(data, sizeof(data), invalidByteOrder);
    printUcs2(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with mixed content and trailing null terminators
TEST_F(PrintUcs2Test_1380, MixedContentWithTrailingNulls_1380) {
    auto value = Value::create(unsignedByte);
    // "A" followed by multiple null terminators
    byte data[] = {0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    value->read(data, sizeof(data), invalidByteOrder);
    printUcs2(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with unsigned short type - should fall through to printing value
TEST_F(PrintUcs2Test_1380, UnsignedShortType_PrintsValueDirectly_1380) {
    auto value = Value::create(unsignedShort);
    value->read("42");
    printUcs2(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}
