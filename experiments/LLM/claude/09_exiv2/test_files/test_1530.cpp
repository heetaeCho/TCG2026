#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <memory>

// Include necessary headers from exiv2
#include "makernote_int.hpp"
#include "tiffimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewSonyMnTest_1530 : public ::testing::Test {
protected:
    static constexpr uint16_t testTag = 0x927c;
    static constexpr IfdId testGroup = IfdId::exifId;
    static constexpr IfdId testMnGroup = IfdId::ifd0Id;
    static constexpr ByteOrder testByteOrder = littleEndian;
};

// Test: Data too small (less than 12 bytes, and less than 18 bytes) should return nullptr
TEST_F(NewSonyMnTest_1530, NullptrWhenSizeTooSmall_1530) {
    const byte data[10] = {0};
    auto result = newSonyMn(testTag, testGroup, testMnGroup, data, 10, testByteOrder);
    EXPECT_EQ(result, nullptr);
}

// Test: Size is 0 should return nullptr
TEST_F(NewSonyMnTest_1530, NullptrWhenSizeIsZero_1530) {
    const byte data[1] = {0};
    auto result = newSonyMn(testTag, testGroup, testMnGroup, data, 0, testByteOrder);
    EXPECT_EQ(result, nullptr);
}

// Test: Non-Sony signature with exactly 18 bytes should return a Sony2 makernote
TEST_F(NewSonyMnTest_1530, NonSonySignatureWithSize18ReturnsSony2_1530) {
    byte data[18] = {};
    memset(data, 'X', 18);
    auto result = newSonyMn(testTag, testGroup, testMnGroup, data, 18, testByteOrder);
    EXPECT_NE(result, nullptr);
}

// Test: Non-Sony signature with exactly 17 bytes (< 18) should return nullptr
TEST_F(NewSonyMnTest_1530, NonSonySignatureWithSize17ReturnsNullptr_1530) {
    byte data[17] = {};
    memset(data, 'X', 17);
    auto result = newSonyMn(testTag, testGroup, testMnGroup, data, 17, testByteOrder);
    EXPECT_EQ(result, nullptr);
}

// Test: Non-Sony signature with size 12 but less than 18 returns nullptr
TEST_F(NewSonyMnTest_1530, NonSonySignatureSize12LessThan18ReturnsNullptr_1530) {
    byte data[12] = {'N', 'O', 'T', ' ', 'S', 'O', 'N', 'Y', ' ', ' ', ' ', ' '};
    auto result = newSonyMn(testTag, testGroup, testMnGroup, data, 12, testByteOrder);
    EXPECT_EQ(result, nullptr);
}

// Test: Valid Sony DSC signature with sufficient size returns Sony1 makernote
TEST_F(NewSonyMnTest_1530, ValidSonyDscSignatureReturnsSony1_1530) {
    // "SONY DSC \0\0\0" is 12 bytes
    // SonyMnHeader::sizeOfSignature() + 14 bytes needed
    // We'll provide a generous buffer
    const size_t bufSize = 256;
    byte data[bufSize] = {};
    const char sig[] = "SONY DSC \0\0\0";
    memcpy(data, sig, 12);
    auto result = newSonyMn(testTag, testGroup, testMnGroup, data, bufSize, testByteOrder);
    EXPECT_NE(result, nullptr);
}

// Test: Valid Sony DSC signature but insufficient total size returns nullptr
TEST_F(NewSonyMnTest_1530, ValidSonyDscSignatureInsufficientSizeReturnsNullptr_1530) {
    // The signature is 12 bytes; we need sizeOfSignature() + 14 bytes total
    // With only 12 bytes, it should likely be insufficient
    byte data[12] = {};
    const char sig[] = "SONY DSC \0\0\0";
    memcpy(data, sig, 12);
    auto result = newSonyMn(testTag, testGroup, testMnGroup, data, 12, testByteOrder);
    // 12 bytes is very likely less than sizeOfSignature() + 14
    EXPECT_EQ(result, nullptr);
}

// Test: Non-Sony signature with large size returns Sony2 makernote
TEST_F(NewSonyMnTest_1530, NonSonySignatureLargeSizeReturnsSony2_1530) {
    const size_t bufSize = 1024;
    byte data[bufSize] = {};
    memset(data, 0xFF, bufSize);
    auto result = newSonyMn(testTag, testGroup, testMnGroup, data, bufSize, testByteOrder);
    EXPECT_NE(result, nullptr);
}

// Test: Partial Sony signature should not match and go to Sony2 path
TEST_F(NewSonyMnTest_1530, PartialSonySignatureGoesToSony2Path_1530) {
    const size_t bufSize = 64;
    byte data[bufSize] = {};
    // "SONY DSC" but without the trailing nulls - partial match
    memcpy(data, "SONY DSC \0\0X", 12); // last byte is 'X' not '\0'
    auto result = newSonyMn(testTag, testGroup, testMnGroup, data, bufSize, testByteOrder);
    // This doesn't match the 12-byte Sony signature, so it goes to Sony2 path
    EXPECT_NE(result, nullptr);
}

// Test: Size exactly 11 (less than 12 and less than 18) returns nullptr
TEST_F(NewSonyMnTest_1530, Size11ReturnsNullptr_1530) {
    byte data[11] = {};
    auto result = newSonyMn(testTag, testGroup, testMnGroup, data, 11, testByteOrder);
    EXPECT_EQ(result, nullptr);
}

// Test: Size exactly 1 returns nullptr
TEST_F(NewSonyMnTest_1530, Size1ReturnsNullptr_1530) {
    byte data[1] = {0};
    auto result = newSonyMn(testTag, testGroup, testMnGroup, data, 1, testByteOrder);
    EXPECT_EQ(result, nullptr);
}

// Test: With big endian byte order, valid Sony DSC with sufficient size
TEST_F(NewSonyMnTest_1530, ValidSonyDscBigEndianReturnsSony1_1530) {
    const size_t bufSize = 256;
    byte data[bufSize] = {};
    const char sig[] = "SONY DSC \0\0\0";
    memcpy(data, sig, 12);
    auto result = newSonyMn(testTag, testGroup, testMnGroup, data, bufSize, bigEndian);
    EXPECT_NE(result, nullptr);
}

// Test: Non-Sony with exactly 19 bytes (just above 18) returns Sony2
TEST_F(NewSonyMnTest_1530, NonSonySignatureSize19ReturnsSony2_1530) {
    byte data[19] = {};
    memset(data, 'A', 19);
    auto result = newSonyMn(testTag, testGroup, testMnGroup, data, 19, testByteOrder);
    EXPECT_NE(result, nullptr);
}

// Test: Sony DSC signature with size 13 (likely less than sizeOfSignature() + 14)
TEST_F(NewSonyMnTest_1530, SonyDscSignatureSize13ReturnsNullptr_1530) {
    byte data[13] = {};
    const char sig[] = "SONY DSC \0\0\0";
    memcpy(data, sig, 12);
    data[12] = 0;
    auto result = newSonyMn(testTag, testGroup, testMnGroup, data, 13, testByteOrder);
    EXPECT_EQ(result, nullptr);
}
