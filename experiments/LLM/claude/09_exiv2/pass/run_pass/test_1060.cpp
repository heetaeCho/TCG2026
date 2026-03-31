#include <gtest/gtest.h>
#include <exiv2/image.hpp>
#include <exiv2/types.hpp>
#include <exiv2/basicio.hpp>
#include <cstring>

using namespace Exiv2;

class ImageStaticTest_1060 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== byteSwap (uint16_t) tests ====================

TEST_F(ImageStaticTest_1060, ByteSwap16_NoSwap_1060) {
    uint16_t value = 0x0102;
    uint16_t result = Image::byteSwap(value, false);
    EXPECT_EQ(result, value);
}

TEST_F(ImageStaticTest_1060, ByteSwap16_Swap_1060) {
    uint16_t value = 0x0102;
    uint16_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x0201);
}

TEST_F(ImageStaticTest_1060, ByteSwap16_Zero_NoSwap_1060) {
    uint16_t result = Image::byteSwap(static_cast<uint16_t>(0), false);
    EXPECT_EQ(result, 0);
}

TEST_F(ImageStaticTest_1060, ByteSwap16_Zero_Swap_1060) {
    uint16_t result = Image::byteSwap(static_cast<uint16_t>(0), true);
    EXPECT_EQ(result, 0);
}

TEST_F(ImageStaticTest_1060, ByteSwap16_MaxValue_Swap_1060) {
    uint16_t value = 0xFFFF;
    uint16_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0xFFFF);
}

TEST_F(ImageStaticTest_1060, ByteSwap16_DoubleSwapReturnsOriginal_1060) {
    uint16_t value = 0xABCD;
    uint16_t swapped = Image::byteSwap(value, true);
    uint16_t result = Image::byteSwap(swapped, true);
    EXPECT_EQ(result, value);
}

// ==================== byteSwap (uint32_t) tests ====================

TEST_F(ImageStaticTest_1060, ByteSwap32_NoSwap_1060) {
    uint32_t value = 0x01020304;
    uint32_t result = Image::byteSwap(value, false);
    EXPECT_EQ(result, value);
}

TEST_F(ImageStaticTest_1060, ByteSwap32_Swap_1060) {
    uint32_t value = 0x01020304;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x04030201u);
}

TEST_F(ImageStaticTest_1060, ByteSwap32_Zero_Swap_1060) {
    uint32_t result = Image::byteSwap(static_cast<uint32_t>(0), true);
    EXPECT_EQ(result, 0u);
}

TEST_F(ImageStaticTest_1060, ByteSwap32_MaxValue_Swap_1060) {
    uint32_t value = 0xFFFFFFFF;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0xFFFFFFFFu);
}

TEST_F(ImageStaticTest_1060, ByteSwap32_DoubleSwapReturnsOriginal_1060) {
    uint32_t value = 0xDEADBEEF;
    uint32_t swapped = Image::byteSwap(value, true);
    uint32_t result = Image::byteSwap(swapped, true);
    EXPECT_EQ(result, value);
}

// ==================== byteSwap (uint64_t) tests ====================

TEST_F(ImageStaticTest_1060, ByteSwap64_NoSwap_1060) {
    uint64_t value = 0x0102030405060708ULL;
    uint64_t result = Image::byteSwap(value, false);
    EXPECT_EQ(result, value);
}

TEST_F(ImageStaticTest_1060, ByteSwap64_Swap_1060) {
    uint64_t value = 0x0102030405060708ULL;
    uint64_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x0807060504030201ULL);
}

TEST_F(ImageStaticTest_1060, ByteSwap64_Zero_Swap_1060) {
    uint64_t result = Image::byteSwap(static_cast<uint64_t>(0), true);
    EXPECT_EQ(result, 0ULL);
}

TEST_F(ImageStaticTest_1060, ByteSwap64_DoubleSwapReturnsOriginal_1060) {
    uint64_t value = 0xDEADBEEFCAFEBABEULL;
    uint64_t swapped = Image::byteSwap(value, true);
    uint64_t result = Image::byteSwap(swapped, true);
    EXPECT_EQ(result, value);
}

// ==================== byteSwap2 tests ====================

TEST_F(ImageStaticTest_1060, ByteSwap2_NoSwap_1060) {
    byte data[] = {0x01, 0x02};
    DataBuf buf(data, 2);
    uint16_t result = Image::byteSwap2(buf, 0, false);
    // Without swap, bytes are read as-is into a uint16_t
    uint16_t expected = 0;
    auto p = reinterpret_cast<char*>(&expected);
    p[0] = 0x01;
    p[1] = 0x02;
    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticTest_1060, ByteSwap2_Swap_1060) {
    byte data[] = {0x01, 0x02};
    DataBuf buf(data, 2);
    uint16_t noSwap = Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Image::byteSwap2(buf, 0, true);
    EXPECT_EQ(swapped, Image::byteSwap(noSwap, true));
}

TEST_F(ImageStaticTest_1060, ByteSwap2_WithOffset_1060) {
    byte data[] = {0xFF, 0xAB, 0xCD};
    DataBuf buf(data, 3);
    uint16_t result = Image::byteSwap2(buf, 1, false);
    uint16_t expected = 0;
    auto p = reinterpret_cast<char*>(&expected);
    p[0] = static_cast<char>(0xAB);
    p[1] = static_cast<char>(0xCD);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticTest_1060, ByteSwap2_ZeroBytes_1060) {
    byte data[] = {0x00, 0x00};
    DataBuf buf(data, 2);
    uint16_t result = Image::byteSwap2(buf, 0, false);
    EXPECT_EQ(result, 0);
    result = Image::byteSwap2(buf, 0, true);
    EXPECT_EQ(result, 0);
}

// ==================== byteSwap4 tests ====================

TEST_F(ImageStaticTest_1060, ByteSwap4_NoSwap_1060) {
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    uint32_t result = Image::byteSwap4(buf, 0, false);
    uint32_t expected = 0;
    auto p = reinterpret_cast<char*>(&expected);
    p[0] = 0x01; p[1] = 0x02; p[2] = 0x03; p[3] = 0x04;
    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticTest_1060, ByteSwap4_Swap_1060) {
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 4);
    uint32_t noSwap = Image::byteSwap4(buf, 0, false);
    uint32_t swapped = Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(swapped, Image::byteSwap(noSwap, true));
}

// ==================== byteSwap8 tests ====================

TEST_F(ImageStaticTest_1060, ByteSwap8_NoSwap_1060) {
    byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    DataBuf buf(data, 8);
    uint64_t result = Image::byteSwap8(buf, 0, false);
    uint64_t expected = 0;
    auto p = reinterpret_cast<char*>(&expected);
    for (int i = 0; i < 8; i++) p[i] = static_cast<char>(i + 1);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticTest_1060, ByteSwap8_Swap_1060) {
    byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    DataBuf buf(data, 8);
    uint64_t noSwap = Image::byteSwap8(buf, 0, false);
    uint64_t swapped = Image::byteSwap8(buf, 0, true);
    EXPECT_EQ(swapped, Image::byteSwap(noSwap, true));
}

// ==================== Platform endianness tests ====================

TEST_F(ImageStaticTest_1060, PlatformEndianness_MutuallyExclusive_1060) {
    bool big = Image::isBigEndianPlatform();
    bool little = Image::isLittleEndianPlatform();
    EXPECT_NE(big, little);
}

TEST_F(ImageStaticTest_1060, PlatformEndianness_OneIsTrue_1060) {
    EXPECT_TRUE(Image::isBigEndianPlatform() || Image::isLittleEndianPlatform());
}

// ==================== Type classification tests ====================

TEST_F(ImageStaticTest_1060, IsStringType_1060) {
    // Type 2 is ASCII string in TIFF/Exif
    EXPECT_TRUE(Image::isStringType(2));
    EXPECT_FALSE(Image::isStringType(3)); // SHORT
}

TEST_F(ImageStaticTest_1060, IsShortType_1060) {
    // Type 3 is SHORT, type 8 is SSHORT
    EXPECT_TRUE(Image::isShortType(3));
    EXPECT_TRUE(Image::isShortType(8));
    EXPECT_FALSE(Image::isShortType(4)); // LONG
}

TEST_F(ImageStaticTest_1060, IsLongType_1060) {
    // Type 4 is LONG, type 9 is SLONG
    EXPECT_TRUE(Image::isLongType(4));
    EXPECT_TRUE(Image::isLongType(9));
    EXPECT_FALSE(Image::isLongType(3)); // SHORT
}

TEST_F(ImageStaticTest_1060, IsRationalType_1060) {
    // Type 5 is RATIONAL, type 10 is SRATIONAL
    EXPECT_TRUE(Image::isRationalType(5));
    EXPECT_TRUE(Image::isRationalType(10));
    EXPECT_FALSE(Image::isRationalType(4)); // LONG
}

TEST_F(ImageStaticTest_1060, Is2ByteType_1060) {
    // SHORT (3) and SSHORT (8) are 2-byte
    EXPECT_TRUE(Image::is2ByteType(3));
    EXPECT_TRUE(Image::is2ByteType(8));
    EXPECT_FALSE(Image::is2ByteType(4));
}

TEST_F(ImageStaticTest_1060, Is4ByteType_1060) {
    // LONG (4) and SLONG (9) are 4-byte
    EXPECT_TRUE(Image::is4ByteType(4));
    EXPECT_TRUE(Image::is4ByteType(9));
    EXPECT_FALSE(Image::is4ByteType(3));
}

TEST_F(ImageStaticTest_1060, Is8ByteType_1060) {
    // RATIONAL (5), SRATIONAL (10) are 8-byte
    EXPECT_TRUE(Image::is8ByteType(5));
    EXPECT_TRUE(Image::is8ByteType(10));
    EXPECT_FALSE(Image::is8ByteType(4));
}

TEST_F(ImageStaticTest_1060, IsLongLongType_1060) {
    // Type 16 is LONG8, type 17 is SLONG8
    EXPECT_TRUE(Image::isLongLongType(16));
    EXPECT_TRUE(Image::isLongLongType(17));
    EXPECT_FALSE(Image::isLongLongType(4));
}

// ==================== Edge cases for type checks with zero ====================

TEST_F(ImageStaticTest_1060, IsStringType_Zero_1060) {
    EXPECT_FALSE(Image::isStringType(0));
}

TEST_F(ImageStaticTest_1060, IsShortType_Zero_1060) {
    EXPECT_FALSE(Image::isShortType(0));
}

TEST_F(ImageStaticTest_1060, IsLongType_Zero_1060) {
    EXPECT_FALSE(Image::isLongType(0));
}

TEST_F(ImageStaticTest_1060, IsRationalType_Zero_1060) {
    EXPECT_FALSE(Image::isRationalType(0));
}

// ==================== byteSwap2 with identical bytes ====================

TEST_F(ImageStaticTest_1060, ByteSwap2_IdenticalBytes_SwapEqualsNoSwap_1060) {
    byte data[] = {0xAA, 0xAA};
    DataBuf buf(data, 2);
    uint16_t noSwap = Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Image::byteSwap2(buf, 0, true);
    // When both bytes are same, swapping should still yield a swapped uint16
    EXPECT_EQ(swapped, Image::byteSwap(noSwap, true));
}

// ==================== byteSwap consistency between buffer and direct ====================

TEST_F(ImageStaticTest_1060, ByteSwap2_ConsistentWithDirectByteSwap_1060) {
    byte data[] = {0xDE, 0xAD};
    DataBuf buf(data, 2);
    uint16_t fromBuf_noswap = Image::byteSwap2(buf, 0, false);
    uint16_t fromBuf_swap = Image::byteSwap2(buf, 0, true);
    EXPECT_EQ(fromBuf_swap, Image::byteSwap(fromBuf_noswap, true));
}

TEST_F(ImageStaticTest_1060, ByteSwap4_ConsistentWithDirectByteSwap_1060) {
    byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    DataBuf buf(data, 4);
    uint32_t fromBuf_noswap = Image::byteSwap4(buf, 0, false);
    uint32_t fromBuf_swap = Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(fromBuf_swap, Image::byteSwap(fromBuf_noswap, true));
}

TEST_F(ImageStaticTest_1060, ByteSwap8_ConsistentWithDirectByteSwap_1060) {
    byte data[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE, 0xBA, 0xBE};
    DataBuf buf(data, 8);
    uint64_t fromBuf_noswap = Image::byteSwap8(buf, 0, false);
    uint64_t fromBuf_swap = Image::byteSwap8(buf, 0, true);
    EXPECT_EQ(fromBuf_swap, Image::byteSwap(fromBuf_noswap, true));
}

// ==================== byteSwap with specific known values ====================

TEST_F(ImageStaticTest_1060, ByteSwap16_0x00FF_Swap_1060) {
    uint16_t value = 0x00FF;
    uint16_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0xFF00);
}

TEST_F(ImageStaticTest_1060, ByteSwap32_0x000000FF_Swap_1060) {
    uint32_t value = 0x000000FF;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0xFF000000u);
}

TEST_F(ImageStaticTest_1060, ByteSwap64_0x00000000000000FF_Swap_1060) {
    uint64_t value = 0x00000000000000FFULL;
    uint64_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0xFF00000000000000ULL);
}

// ==================== byteSwap2 with various offsets ====================

TEST_F(ImageStaticTest_1060, ByteSwap2_MiddleOffset_1060) {
    byte data[] = {0x00, 0x00, 0xAB, 0xCD, 0x00};
    DataBuf buf(data, 5);
    uint16_t noSwap = Image::byteSwap2(buf, 2, false);
    uint16_t expected = 0;
    auto p = reinterpret_cast<char*>(&expected);
    p[0] = static_cast<char>(0xAB);
    p[1] = static_cast<char>(0xCD);
    EXPECT_EQ(noSwap, expected);
}

TEST_F(ImageStaticTest_1060, ByteSwap4_WithOffset_1060) {
    byte data[] = {0x00, 0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, 5);
    uint32_t noSwap = Image::byteSwap4(buf, 1, false);
    uint32_t expected = 0;
    auto p = reinterpret_cast<char*>(&expected);
    p[0] = 0x01; p[1] = 0x02; p[2] = 0x03; p[3] = 0x04;
    EXPECT_EQ(noSwap, expected);
}

TEST_F(ImageStaticTest_1060, ByteSwap8_WithOffset_1060) {
    byte data[] = {0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    DataBuf buf(data, 9);
    uint64_t noSwap = Image::byteSwap8(buf, 1, false);
    uint64_t expected = 0;
    auto p = reinterpret_cast<char*>(&expected);
    for (int i = 0; i < 8; i++) p[i] = static_cast<char>(i + 1);
    EXPECT_EQ(noSwap, expected);
}
