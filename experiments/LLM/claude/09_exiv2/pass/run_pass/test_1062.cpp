#include <gtest/gtest.h>
#include <exiv2/image.hpp>
#include <exiv2/types.hpp>
#include <exiv2/basicio.hpp>
#include <cstring>
#include <sstream>

using namespace Exiv2;

// Test fixture for Image static methods
class ImageStaticTest_1062 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== byteSwap8 tests ====================

TEST_F(ImageStaticTest_1062, ByteSwap8_NoSwap_ReturnsOriginalBytes_1062) {
    // Create a DataBuf with 8 known bytes
    byte data[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    DataBuf buf(data, 8);

    uint64_t result = Image::byteSwap8(buf, 0, false);

    // When bSwap is false, the bytes should be read as-is into uint64_t
    uint64_t expected = 0;
    auto p = reinterpret_cast<byte*>(&expected);
    for (int i = 0; i < 8; i++)
        p[i] = data[i];

    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticTest_1062, ByteSwap8_WithSwap_ReturnsByteSwappedValue_1062) {
    byte data[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    DataBuf buf(data, 8);

    uint64_t noSwap = Image::byteSwap8(buf, 0, false);
    uint64_t swapped = Image::byteSwap8(buf, 0, true);

    // byteSwap8 with bSwap=true should return the byte-swapped version
    uint64_t expectedSwapped = Image::byteSwap(noSwap, true);
    EXPECT_EQ(swapped, expectedSwapped);
}

TEST_F(ImageStaticTest_1062, ByteSwap8_WithOffset_ReadsFromCorrectPosition_1062) {
    byte data[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04,
                     0x05, 0x06, 0x07, 0x08, 0xFF, 0xFF, 0xFF, 0xFF};
    DataBuf buf(data, 16);

    uint64_t result = Image::byteSwap8(buf, 4, false);

    uint64_t expected = 0;
    auto p = reinterpret_cast<byte*>(&expected);
    for (int i = 0; i < 8; i++)
        p[i] = data[4 + i];

    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticTest_1062, ByteSwap8_AllZeros_ReturnsZero_1062) {
    byte data[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    DataBuf buf(data, 8);

    EXPECT_EQ(Image::byteSwap8(buf, 0, false), 0u);
    EXPECT_EQ(Image::byteSwap8(buf, 0, true), 0u);
}

TEST_F(ImageStaticTest_1062, ByteSwap8_AllOnes_ReturnsMaxValue_1062) {
    byte data[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    DataBuf buf(data, 8);

    uint64_t result = Image::byteSwap8(buf, 0, false);
    EXPECT_EQ(result, UINT64_MAX);

    // Swapping all 0xFF bytes should still give all 0xFF
    uint64_t swapped = Image::byteSwap8(buf, 0, true);
    EXPECT_EQ(swapped, UINT64_MAX);
}

// ==================== byteSwap (uint64_t) tests ====================

TEST_F(ImageStaticTest_1062, ByteSwapUint64_NoSwap_ReturnsSameValue_1062) {
    uint64_t value = 0x0102030405060708ULL;
    EXPECT_EQ(Image::byteSwap(value, false), value);
}

TEST_F(ImageStaticTest_1062, ByteSwapUint64_WithSwap_ReversesBytes_1062) {
    uint64_t value = 0x0102030405060708ULL;
    uint64_t swapped = Image::byteSwap(value, true);
    EXPECT_EQ(swapped, 0x0807060504030201ULL);
}

TEST_F(ImageStaticTest_1062, ByteSwapUint64_DoubleSwap_ReturnsOriginal_1062) {
    uint64_t value = 0xDEADBEEFCAFEBABEULL;
    uint64_t doubleSwapped = Image::byteSwap(Image::byteSwap(value, true), true);
    EXPECT_EQ(doubleSwapped, value);
}

TEST_F(ImageStaticTest_1062, ByteSwapUint64_Zero_1062) {
    EXPECT_EQ(Image::byteSwap(static_cast<uint64_t>(0), true), 0u);
    EXPECT_EQ(Image::byteSwap(static_cast<uint64_t>(0), false), 0u);
}

// ==================== byteSwap (uint32_t) tests ====================

TEST_F(ImageStaticTest_1062, ByteSwapUint32_NoSwap_ReturnsSameValue_1062) {
    uint32_t value = 0x01020304;
    EXPECT_EQ(Image::byteSwap(value, false), value);
}

TEST_F(ImageStaticTest_1062, ByteSwapUint32_WithSwap_ReversesBytes_1062) {
    uint32_t value = 0x01020304;
    uint32_t swapped = Image::byteSwap(value, true);
    EXPECT_EQ(swapped, 0x04030201u);
}

TEST_F(ImageStaticTest_1062, ByteSwapUint32_DoubleSwap_ReturnsOriginal_1062) {
    uint32_t value = 0xDEADBEEF;
    uint32_t doubleSwapped = Image::byteSwap(Image::byteSwap(value, true), true);
    EXPECT_EQ(doubleSwapped, value);
}

// ==================== byteSwap (uint16_t) tests ====================

TEST_F(ImageStaticTest_1062, ByteSwapUint16_NoSwap_ReturnsSameValue_1062) {
    uint16_t value = 0x0102;
    EXPECT_EQ(Image::byteSwap(value, false), value);
}

TEST_F(ImageStaticTest_1062, ByteSwapUint16_WithSwap_ReversesBytes_1062) {
    uint16_t value = 0x0102;
    uint16_t swapped = Image::byteSwap(value, true);
    EXPECT_EQ(swapped, static_cast<uint16_t>(0x0201));
}

TEST_F(ImageStaticTest_1062, ByteSwapUint16_DoubleSwap_ReturnsOriginal_1062) {
    uint16_t value = 0xBEEF;
    uint16_t doubleSwapped = Image::byteSwap(Image::byteSwap(value, true), true);
    EXPECT_EQ(doubleSwapped, value);
}

// ==================== byteSwap2 tests ====================

TEST_F(ImageStaticTest_1062, ByteSwap2_NoSwap_1062) {
    byte data[2] = {0x01, 0x02};
    DataBuf buf(data, 2);

    uint16_t result = Image::byteSwap2(buf, 0, false);

    uint16_t expected = 0;
    auto p = reinterpret_cast<byte*>(&expected);
    p[0] = 0x01;
    p[1] = 0x02;

    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticTest_1062, ByteSwap2_WithSwap_1062) {
    byte data[2] = {0x01, 0x02};
    DataBuf buf(data, 2);

    uint16_t noSwap = Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Image::byteSwap2(buf, 0, true);

    EXPECT_EQ(swapped, Image::byteSwap(noSwap, true));
}

// ==================== byteSwap4 tests ====================

TEST_F(ImageStaticTest_1062, ByteSwap4_NoSwap_1062) {
    byte data[4] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);

    uint32_t result = Image::byteSwap4(buf, 0, false);

    uint32_t expected = 0;
    auto p = reinterpret_cast<byte*>(&expected);
    for (int i = 0; i < 4; i++)
        p[i] = data[i];

    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticTest_1062, ByteSwap4_WithSwap_1062) {
    byte data[4] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);

    uint32_t noSwap = Image::byteSwap4(buf, 0, false);
    uint32_t swapped = Image::byteSwap4(buf, 0, true);

    EXPECT_EQ(swapped, Image::byteSwap(noSwap, true));
}

// ==================== Platform endianness tests ====================

TEST_F(ImageStaticTest_1062, PlatformEndianness_MutuallyExclusive_1062) {
    bool big = Image::isBigEndianPlatform();
    bool little = Image::isLittleEndianPlatform();

    // Exactly one should be true
    EXPECT_NE(big, little);
}

// ==================== Type classification tests ====================

TEST_F(ImageStaticTest_1062, IsStringType_AsciiType_1062) {
    // TIFF type 2 is ASCII
    EXPECT_TRUE(Image::isStringType(2));
}

TEST_F(ImageStaticTest_1062, IsStringType_NonStringType_1062) {
    // TIFF type 3 is SHORT
    EXPECT_FALSE(Image::isStringType(3));
}

TEST_F(ImageStaticTest_1062, IsShortType_ShortType_1062) {
    // TIFF type 3 is SHORT
    EXPECT_TRUE(Image::isShortType(3));
}

TEST_F(ImageStaticTest_1062, IsShortType_NonShortType_1062) {
    EXPECT_FALSE(Image::isShortType(2));
}

TEST_F(ImageStaticTest_1062, IsLongType_LongType_1062) {
    // TIFF type 4 is LONG
    EXPECT_TRUE(Image::isLongType(4));
}

TEST_F(ImageStaticTest_1062, IsLongType_NonLongType_1062) {
    EXPECT_FALSE(Image::isLongType(3));
}

TEST_F(ImageStaticTest_1062, IsRationalType_RationalType_1062) {
    // TIFF type 5 is RATIONAL
    EXPECT_TRUE(Image::isRationalType(5));
}

TEST_F(ImageStaticTest_1062, IsRationalType_NonRationalType_1062) {
    EXPECT_FALSE(Image::isRationalType(3));
}

TEST_F(ImageStaticTest_1062, Is2ByteType_ShortType_1062) {
    // SHORT (3) is 2 bytes
    EXPECT_TRUE(Image::is2ByteType(3));
}

TEST_F(ImageStaticTest_1062, Is2ByteType_Non2ByteType_1062) {
    // LONG (4) is not 2 bytes
    EXPECT_FALSE(Image::is2ByteType(4));
}

TEST_F(ImageStaticTest_1062, Is4ByteType_LongType_1062) {
    // LONG (4) is 4 bytes
    EXPECT_TRUE(Image::is4ByteType(4));
}

TEST_F(ImageStaticTest_1062, Is4ByteType_Non4ByteType_1062) {
    EXPECT_FALSE(Image::is4ByteType(3));
}

TEST_F(ImageStaticTest_1062, Is8ByteType_RationalType_1062) {
    // RATIONAL (5) is 8 bytes
    EXPECT_TRUE(Image::is8ByteType(5));
}

TEST_F(ImageStaticTest_1062, Is8ByteType_Non8ByteType_1062) {
    EXPECT_FALSE(Image::is8ByteType(3));
}

TEST_F(ImageStaticTest_1062, IsLongLongType_1062) {
    // Type 16 is typically LONG8 in BigTIFF
    // We just test that it returns consistent results
    bool result = Image::isLongLongType(16);
    // Can't assert specific value without knowing implementation, but test it doesn't crash
    (void)result;
}

// ==================== byteSwap8 with specific patterns ====================

TEST_F(ImageStaticTest_1062, ByteSwap8_SingleByte_NonZero_1062) {
    byte data[8] = {0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    DataBuf buf(data, 8);

    uint64_t noSwap = Image::byteSwap8(buf, 0, false);
    uint64_t swapped = Image::byteSwap8(buf, 0, true);

    // The no-swap value should have 0x42 at byte position 0
    auto p = reinterpret_cast<byte*>(&noSwap);
    EXPECT_EQ(p[0], 0x42);

    // The swapped value should have 0x42 at byte position 7
    auto ps = reinterpret_cast<byte*>(&swapped);
    EXPECT_EQ(ps[7], 0x42);
}

TEST_F(ImageStaticTest_1062, ByteSwap8_SymmetricPattern_1062) {
    // A palindromic byte pattern should be unchanged by swap
    byte data[8] = {0x01, 0x02, 0x03, 0x04, 0x04, 0x03, 0x02, 0x01};
    DataBuf buf(data, 8);

    uint64_t noSwap = Image::byteSwap8(buf, 0, false);
    uint64_t swapped = Image::byteSwap8(buf, 0, true);

    EXPECT_EQ(noSwap, swapped);
}

TEST_F(ImageStaticTest_1062, ByteSwap8_DoubleSwap_ReturnsOriginal_1062) {
    byte data[8] = {0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE, 0xBA, 0xBE};
    DataBuf buf(data, 8);

    uint64_t original = Image::byteSwap8(buf, 0, false);
    uint64_t swappedOnce = Image::byteSwap8(buf, 0, true);
    uint64_t swappedTwice = Image::byteSwap(swappedOnce, true);

    EXPECT_EQ(swappedTwice, original);
}

// ==================== Boundary: offset at end of buffer ====================

TEST_F(ImageStaticTest_1062, ByteSwap8_OffsetAtEnd_ReadsCorrectly_1062) {
    byte data[16] = {0};
    data[8] = 0xAA;
    data[9] = 0xBB;
    data[10] = 0xCC;
    data[11] = 0xDD;
    data[12] = 0xEE;
    data[13] = 0xFF;
    data[14] = 0x11;
    data[15] = 0x22;
    DataBuf buf(data, 16);

    uint64_t result = Image::byteSwap8(buf, 8, false);

    uint64_t expected = 0;
    auto p = reinterpret_cast<byte*>(&expected);
    for (int i = 0; i < 8; i++)
        p[i] = data[8 + i];

    EXPECT_EQ(result, expected);
}

// ==================== byteSwap consistency between methods ====================

TEST_F(ImageStaticTest_1062, ByteSwap2_ConsistentWithByteSwapUint16_1062) {
    byte data[2] = {0xAB, 0xCD};
    DataBuf buf(data, 2);

    uint16_t fromBuf = Image::byteSwap2(buf, 0, true);

    // Manually construct the value and swap it
    uint16_t manual = 0;
    auto p = reinterpret_cast<byte*>(&manual);
    p[0] = 0xAB;
    p[1] = 0xCD;
    uint16_t expected = Image::byteSwap(manual, true);

    EXPECT_EQ(fromBuf, expected);
}

TEST_F(ImageStaticTest_1062, ByteSwap4_ConsistentWithByteSwapUint32_1062) {
    byte data[4] = {0x12, 0x34, 0x56, 0x78};
    DataBuf buf(data, 4);

    uint32_t fromBuf = Image::byteSwap4(buf, 0, true);

    uint32_t manual = 0;
    auto p = reinterpret_cast<byte*>(&manual);
    for (int i = 0; i < 4; i++)
        p[i] = data[i];
    uint32_t expected = Image::byteSwap(manual, true);

    EXPECT_EQ(fromBuf, expected);
}
