#include <gtest/gtest.h>
#include <exiv2/image.hpp>
#include <exiv2/types.hpp>
#include <cstring>

using namespace Exiv2;

class ImageByteSwap4Test_1061 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test byteSwap4 with bSwap = false (no swap) - should return bytes as-is in memory order
TEST_F(ImageByteSwap4Test_1061, NoSwapReturnsOriginalOrder_1061) {
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    
    uint32_t result = Image::byteSwap4(buf, 0, false);
    
    // When bSwap is false, no byte swapping occurs
    // The bytes are placed into a uint32_t in order: p[0]=0x01, p[1]=0x02, p[2]=0x03, p[3]=0x04
    uint32_t expected = 0;
    auto p = reinterpret_cast<char*>(&expected);
    p[0] = 0x01;
    p[1] = 0x02;
    p[2] = 0x03;
    p[3] = 0x04;
    
    EXPECT_EQ(result, expected);
}

// Test byteSwap4 with bSwap = true (swap) - should return byte-swapped value
TEST_F(ImageByteSwap4Test_1061, SwapReversesByteOrder_1061) {
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    
    uint32_t noSwap = Image::byteSwap4(buf, 0, false);
    uint32_t swapped = Image::byteSwap4(buf, 0, true);
    
    // Swapping twice should give back original
    uint32_t doubleSwapped = Image::byteSwap(swapped, true);
    EXPECT_EQ(noSwap, doubleSwapped);
}

// Test byteSwap4 with offset
TEST_F(ImageByteSwap4Test_1061, OffsetReadsCorrectBytes_1061) {
    uint8_t data[] = {0xFF, 0xFE, 0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    
    uint32_t result = Image::byteSwap4(buf, 2, false);
    
    uint32_t expected = 0;
    auto p = reinterpret_cast<char*>(&expected);
    p[0] = 0x01;
    p[1] = 0x02;
    p[2] = 0x03;
    p[3] = 0x04;
    
    EXPECT_EQ(result, expected);
}

// Test byteSwap4 with all zeros
TEST_F(ImageByteSwap4Test_1061, AllZerosNoSwap_1061) {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00};
    DataBuf buf(data, sizeof(data));
    
    uint32_t result = Image::byteSwap4(buf, 0, false);
    EXPECT_EQ(result, 0u);
}

// Test byteSwap4 with all zeros and swap
TEST_F(ImageByteSwap4Test_1061, AllZerosWithSwap_1061) {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00};
    DataBuf buf(data, sizeof(data));
    
    uint32_t result = Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(result, 0u);
}

// Test byteSwap4 with all 0xFF bytes
TEST_F(ImageByteSwap4Test_1061, AllOnesNoSwap_1061) {
    uint8_t data[] = {0xFF, 0xFF, 0xFF, 0xFF};
    DataBuf buf(data, sizeof(data));
    
    uint32_t result = Image::byteSwap4(buf, 0, false);
    EXPECT_EQ(result, 0xFFFFFFFFu);
}

// Test byteSwap4 with all 0xFF and swap - swapping 0xFFFFFFFF should still be 0xFFFFFFFF
TEST_F(ImageByteSwap4Test_1061, AllOnesWithSwap_1061) {
    uint8_t data[] = {0xFF, 0xFF, 0xFF, 0xFF};
    DataBuf buf(data, sizeof(data));
    
    uint32_t result = Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(result, 0xFFFFFFFFu);
}

// Test byteSwap (uint32_t) with bSwap false returns same value
TEST_F(ImageByteSwap4Test_1061, ByteSwapUint32NoSwap_1061) {
    uint32_t value = 0x12345678;
    uint32_t result = Image::byteSwap(value, false);
    EXPECT_EQ(result, value);
}

// Test byteSwap (uint32_t) with bSwap true reverses bytes
TEST_F(ImageByteSwap4Test_1061, ByteSwapUint32WithSwap_1061) {
    uint32_t value = 0x12345678;
    uint32_t result = Image::byteSwap(value, true);
    // Byte swap of 0x12345678 should be 0x78563412
    EXPECT_EQ(result, 0x78563412u);
}

// Test double byteSwap returns original
TEST_F(ImageByteSwap4Test_1061, DoubleByteSwapReturnsOriginal_1061) {
    uint32_t value = 0xDEADBEEF;
    uint32_t swapped = Image::byteSwap(value, true);
    uint32_t restored = Image::byteSwap(swapped, true);
    EXPECT_EQ(restored, value);
}

// Test byteSwap (uint16_t) with bSwap false
TEST_F(ImageByteSwap4Test_1061, ByteSwapUint16NoSwap_1061) {
    uint16_t value = 0x1234;
    uint16_t result = Image::byteSwap(value, false);
    EXPECT_EQ(result, value);
}

// Test byteSwap (uint16_t) with bSwap true
TEST_F(ImageByteSwap4Test_1061, ByteSwapUint16WithSwap_1061) {
    uint16_t value = 0x1234;
    uint16_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x3412);
}

// Test byteSwap (uint64_t) with bSwap false
TEST_F(ImageByteSwap4Test_1061, ByteSwapUint64NoSwap_1061) {
    uint64_t value = 0x0102030405060708ULL;
    uint64_t result = Image::byteSwap(value, false);
    EXPECT_EQ(result, value);
}

// Test byteSwap (uint64_t) with bSwap true
TEST_F(ImageByteSwap4Test_1061, ByteSwapUint64WithSwap_1061) {
    uint64_t value = 0x0102030405060708ULL;
    uint64_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x0807060504030201ULL);
}

// Test byteSwap2 static method
TEST_F(ImageByteSwap4Test_1061, ByteSwap2NoSwap_1061) {
    uint8_t data[] = {0xAB, 0xCD};
    DataBuf buf(data, sizeof(data));
    
    uint16_t result = Image::byteSwap2(buf, 0, false);
    
    uint16_t expected = 0;
    auto p = reinterpret_cast<char*>(&expected);
    p[0] = static_cast<char>(0xAB);
    p[1] = static_cast<char>(0xCD);
    
    EXPECT_EQ(result, expected);
}

// Test byteSwap2 with swap
TEST_F(ImageByteSwap4Test_1061, ByteSwap2WithSwap_1061) {
    uint8_t data[] = {0xAB, 0xCD};
    DataBuf buf(data, sizeof(data));
    
    uint16_t noSwap = Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Image::byteSwap2(buf, 0, true);
    
    EXPECT_EQ(Image::byteSwap(noSwap, true), swapped);
}

// Test byteSwap8 static method
TEST_F(ImageByteSwap4Test_1061, ByteSwap8NoSwap_1061) {
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    DataBuf buf(data, sizeof(data));
    
    uint64_t result = Image::byteSwap8(buf, 0, false);
    
    uint64_t expected = 0;
    auto p = reinterpret_cast<char*>(&expected);
    for (int i = 0; i < 8; i++)
        p[i] = static_cast<char>(data[i]);
    
    EXPECT_EQ(result, expected);
}

// Test byteSwap8 with swap
TEST_F(ImageByteSwap4Test_1061, ByteSwap8WithSwap_1061) {
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    DataBuf buf(data, sizeof(data));
    
    uint64_t noSwap = Image::byteSwap8(buf, 0, false);
    uint64_t swapped = Image::byteSwap8(buf, 0, true);
    
    EXPECT_EQ(Image::byteSwap(noSwap, true), swapped);
}

// Test isBigEndianPlatform and isLittleEndianPlatform are mutually exclusive
TEST_F(ImageByteSwap4Test_1061, EndianPlatformMutuallyExclusive_1061) {
    bool big = Image::isBigEndianPlatform();
    bool little = Image::isLittleEndianPlatform();
    EXPECT_NE(big, little);
}

// Test isStringType
TEST_F(ImageByteSwap4Test_1061, IsStringType_1061) {
    // Type 2 is ASCII string in TIFF
    EXPECT_TRUE(Image::isStringType(2));
    // Type 3 is SHORT, not string
    EXPECT_FALSE(Image::isStringType(3));
}

// Test isShortType
TEST_F(ImageByteSwap4Test_1061, IsShortType_1061) {
    // Type 3 is SHORT
    EXPECT_TRUE(Image::isShortType(3));
    // Type 8 is SSHORT
    EXPECT_TRUE(Image::isShortType(8));
    // Type 1 is BYTE, not short
    EXPECT_FALSE(Image::isShortType(1));
}

// Test isLongType
TEST_F(ImageByteSwap4Test_1061, IsLongType_1061) {
    // Type 4 is LONG
    EXPECT_TRUE(Image::isLongType(4));
    // Type 9 is SLONG
    EXPECT_TRUE(Image::isLongType(9));
    EXPECT_FALSE(Image::isLongType(3));
}

// Test isRationalType
TEST_F(ImageByteSwap4Test_1061, IsRationalType_1061) {
    // Type 5 is RATIONAL
    EXPECT_TRUE(Image::isRationalType(5));
    // Type 10 is SRATIONAL
    EXPECT_TRUE(Image::isRationalType(10));
    EXPECT_FALSE(Image::isRationalType(4));
}

// Test is2ByteType
TEST_F(ImageByteSwap4Test_1061, Is2ByteType_1061) {
    // SHORT (3) and SSHORT (8) are 2-byte types
    EXPECT_TRUE(Image::is2ByteType(3));
    EXPECT_TRUE(Image::is2ByteType(8));
    EXPECT_FALSE(Image::is2ByteType(4));
}

// Test is4ByteType
TEST_F(ImageByteSwap4Test_1061, Is4ByteType_1061) {
    // LONG (4) and SLONG (9) are 4-byte types; also FLOAT (11)
    EXPECT_TRUE(Image::is4ByteType(4));
    EXPECT_TRUE(Image::is4ByteType(9));
    EXPECT_FALSE(Image::is4ByteType(3));
}

// Test is8ByteType
TEST_F(ImageByteSwap4Test_1061, Is8ByteType_1061) {
    // RATIONAL (5), SRATIONAL (10), DOUBLE (12) are 8-byte types
    EXPECT_TRUE(Image::is8ByteType(5));
    EXPECT_TRUE(Image::is8ByteType(10));
    EXPECT_FALSE(Image::is8ByteType(4));
}

// Test byteSwap4 with specific known value on the platform
TEST_F(ImageByteSwap4Test_1061, ByteSwap4SpecificValue_1061) {
    // Build a DataBuf that represents a known uint32_t
    uint32_t original = 0xAABBCCDD;
    uint8_t data[4];
    std::memcpy(data, &original, 4);
    DataBuf buf(data, sizeof(data));
    
    // With no swap, we should get back the original
    uint32_t result = Image::byteSwap4(buf, 0, false);
    EXPECT_EQ(result, original);
    
    // With swap, we should get the byte-reversed value
    uint32_t swappedResult = Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(swappedResult, Image::byteSwap(original, true));
}

// Test byteSwap4 at non-zero offset within larger buffer
TEST_F(ImageByteSwap4Test_1061, ByteSwap4LargerBufferOffset_1061) {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0xDE, 0xAD, 0xBE, 0xEF, 0x00, 0x00};
    DataBuf buf(data, sizeof(data));
    
    uint32_t result = Image::byteSwap4(buf, 4, false);
    
    uint32_t expected = 0;
    auto p = reinterpret_cast<char*>(&expected);
    p[0] = static_cast<char>(0xDE);
    p[1] = static_cast<char>(0xAD);
    p[2] = static_cast<char>(0xBE);
    p[3] = static_cast<char>(0xEF);
    
    EXPECT_EQ(result, expected);
}

// Test byteSwap4 consistency: swap(noswap) == swap result
TEST_F(ImageByteSwap4Test_1061, ByteSwap4ConsistencyCheck_1061) {
    uint8_t data[] = {0x11, 0x22, 0x33, 0x44};
    DataBuf buf(data, sizeof(data));
    
    uint32_t noSwapResult = Image::byteSwap4(buf, 0, false);
    uint32_t swapResult = Image::byteSwap4(buf, 0, true);
    
    // byteSwap4 with swap should equal byteSwap applied to byteSwap4 without swap
    EXPECT_EQ(swapResult, Image::byteSwap(noSwapResult, true));
}

// Test byteSwap with zero value
TEST_F(ImageByteSwap4Test_1061, ByteSwapZeroValue_1061) {
    EXPECT_EQ(Image::byteSwap(static_cast<uint32_t>(0), true), 0u);
    EXPECT_EQ(Image::byteSwap(static_cast<uint32_t>(0), false), 0u);
    EXPECT_EQ(Image::byteSwap(static_cast<uint16_t>(0), true), 0u);
    EXPECT_EQ(Image::byteSwap(static_cast<uint64_t>(0), true), 0u);
}

// Test isLongLongType
TEST_F(ImageByteSwap4Test_1061, IsLongLongType_1061) {
    // Type 16 is LONG8, Type 17 is SLONG8 in BigTIFF
    EXPECT_FALSE(Image::isLongLongType(4));
    // We don't know exactly which types are long long, but we know standard ones are not
    EXPECT_FALSE(Image::isLongLongType(3));
}
