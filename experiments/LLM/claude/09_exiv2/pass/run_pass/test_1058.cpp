#include <gtest/gtest.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <cstdint>
#include <sstream>
#include <memory>

using namespace Exiv2;

// Helper to create an Image instance for testing.
// Since Image is abstract (has pure virtual methods like readMetadata/writeMetadata),
// we need a concrete subclass or use a real image type. We'll use a minimal approach
// by creating a MemIo-based approach and using ImageFactory if available,
// or we can test static methods directly.

// For static method testing, we don't need an instance.
// For instance method testing, we need a concrete Image subclass.

class ImageByteSwapTest_1058 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// ============================================================
// Tests for byteSwap(uint32_t, bool)
// ============================================================

TEST_F(ImageByteSwapTest_1058, ByteSwap32_NoSwap_1058) {
    uint32_t value = 0x12345678;
    uint32_t result = Image::byteSwap(value, false);
    EXPECT_EQ(result, 0x12345678U);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap32_Swap_1058) {
    uint32_t value = 0x12345678;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x78563412U);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap32_Zero_NoSwap_1058) {
    uint32_t result = Image::byteSwap(static_cast<uint32_t>(0), false);
    EXPECT_EQ(result, 0U);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap32_Zero_Swap_1058) {
    uint32_t result = Image::byteSwap(static_cast<uint32_t>(0), true);
    EXPECT_EQ(result, 0U);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap32_MaxValue_Swap_1058) {
    uint32_t value = 0xFFFFFFFF;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0xFFFFFFFFU);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap32_MaxValue_NoSwap_1058) {
    uint32_t value = 0xFFFFFFFF;
    uint32_t result = Image::byteSwap(value, false);
    EXPECT_EQ(result, 0xFFFFFFFFU);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap32_OneByte_Swap_1058) {
    uint32_t value = 0x000000FF;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0xFF000000U);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap32_HighByte_Swap_1058) {
    uint32_t value = 0xFF000000;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x000000FFU);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap32_DoubleSwapIsIdentity_1058) {
    uint32_t value = 0xDEADBEEF;
    uint32_t swapped = Image::byteSwap(value, true);
    uint32_t doubleSwapped = Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, value);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap32_MiddleBytes_Swap_1058) {
    uint32_t value = 0x00FFFF00;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x00FFFF00U);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap32_Asymmetric_Swap_1058) {
    uint32_t value = 0xAABBCCDD;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0xDDCCBBAAU);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap32_One_Swap_1058) {
    uint32_t value = 0x00000001;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x01000000U);
}

// ============================================================
// Tests for byteSwap(uint16_t, bool)
// ============================================================

TEST_F(ImageByteSwapTest_1058, ByteSwap16_NoSwap_1058) {
    uint16_t value = 0x1234;
    uint16_t result = Image::byteSwap(value, false);
    EXPECT_EQ(result, 0x1234U);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap16_Swap_1058) {
    uint16_t value = 0x1234;
    uint16_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x3412U);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap16_Zero_Swap_1058) {
    uint16_t result = Image::byteSwap(static_cast<uint16_t>(0), true);
    EXPECT_EQ(result, 0U);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap16_MaxValue_Swap_1058) {
    uint16_t value = 0xFFFF;
    uint16_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0xFFFFU);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap16_DoubleSwapIsIdentity_1058) {
    uint16_t value = 0xABCD;
    uint16_t swapped = Image::byteSwap(value, true);
    uint16_t doubleSwapped = Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, value);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap16_LowByte_Swap_1058) {
    uint16_t value = 0x00FF;
    uint16_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0xFF00U);
}

// ============================================================
// Tests for byteSwap(uint64_t, bool)
// ============================================================

TEST_F(ImageByteSwapTest_1058, ByteSwap64_NoSwap_1058) {
    uint64_t value = 0x0102030405060708ULL;
    uint64_t result = Image::byteSwap(value, false);
    EXPECT_EQ(result, 0x0102030405060708ULL);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap64_Swap_1058) {
    uint64_t value = 0x0102030405060708ULL;
    uint64_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x0807060504030201ULL);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap64_Zero_Swap_1058) {
    uint64_t result = Image::byteSwap(static_cast<uint64_t>(0), true);
    EXPECT_EQ(result, 0ULL);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap64_MaxValue_Swap_1058) {
    uint64_t value = 0xFFFFFFFFFFFFFFFFULL;
    uint64_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0xFFFFFFFFFFFFFFFFULL);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap64_DoubleSwapIsIdentity_1058) {
    uint64_t value = 0xDEADBEEFCAFEBABEULL;
    uint64_t swapped = Image::byteSwap(value, true);
    uint64_t doubleSwapped = Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, value);
}

// ============================================================
// Tests for platform endianness checks
// ============================================================

TEST_F(ImageByteSwapTest_1058, EndiannessMutuallyExclusive_1058) {
    bool big = Image::isBigEndianPlatform();
    bool little = Image::isLittleEndianPlatform();
    // Platform must be one or the other
    EXPECT_NE(big, little);
}

TEST_F(ImageByteSwapTest_1058, IsBigEndianPlatformConsistent_1058) {
    // Calling multiple times should return same result
    EXPECT_EQ(Image::isBigEndianPlatform(), Image::isBigEndianPlatform());
}

TEST_F(ImageByteSwapTest_1058, IsLittleEndianPlatformConsistent_1058) {
    EXPECT_EQ(Image::isLittleEndianPlatform(), Image::isLittleEndianPlatform());
}

// ============================================================
// Tests for isStringType, isShortType, isLongType, etc.
// ============================================================

TEST_F(ImageByteSwapTest_1058, IsStringType_AsciiType_1058) {
    // Type 2 is ASCII in TIFF
    EXPECT_TRUE(Image::isStringType(2));
}

TEST_F(ImageByteSwapTest_1058, IsStringType_NonStringType_1058) {
    // Type 3 is SHORT in TIFF, not string
    EXPECT_FALSE(Image::isStringType(3));
}

TEST_F(ImageByteSwapTest_1058, IsShortType_ShortType_1058) {
    // Type 3 is SHORT in TIFF
    EXPECT_TRUE(Image::isShortType(3));
}

TEST_F(ImageByteSwapTest_1058, IsShortType_NonShortType_1058) {
    EXPECT_FALSE(Image::isShortType(2));
}

TEST_F(ImageByteSwapTest_1058, IsLongType_LongType_1058) {
    // Type 4 is LONG in TIFF
    EXPECT_TRUE(Image::isLongType(4));
}

TEST_F(ImageByteSwapTest_1058, IsLongType_NonLongType_1058) {
    EXPECT_FALSE(Image::isLongType(2));
}

TEST_F(ImageByteSwapTest_1058, IsRationalType_RationalType_1058) {
    // Type 5 is RATIONAL in TIFF
    EXPECT_TRUE(Image::isRationalType(5));
}

TEST_F(ImageByteSwapTest_1058, IsRationalType_NonRationalType_1058) {
    EXPECT_FALSE(Image::isRationalType(3));
}

TEST_F(ImageByteSwapTest_1058, Is2ByteType_ShortType_1058) {
    // SHORT (3) and SSHORT (8) are 2-byte types
    EXPECT_TRUE(Image::is2ByteType(3));
}

TEST_F(ImageByteSwapTest_1058, Is2ByteType_NonTwoByteType_1058) {
    EXPECT_FALSE(Image::is2ByteType(4));
}

TEST_F(ImageByteSwapTest_1058, Is4ByteType_LongType_1058) {
    // LONG (4) is a 4-byte type
    EXPECT_TRUE(Image::is4ByteType(4));
}

TEST_F(ImageByteSwapTest_1058, Is4ByteType_NonFourByteType_1058) {
    EXPECT_FALSE(Image::is4ByteType(3));
}

TEST_F(ImageByteSwapTest_1058, Is8ByteType_RationalType_1058) {
    // RATIONAL (5) is an 8-byte type
    EXPECT_TRUE(Image::is8ByteType(5));
}

TEST_F(ImageByteSwapTest_1058, Is8ByteType_NonEightByteType_1058) {
    EXPECT_FALSE(Image::is8ByteType(3));
}

TEST_F(ImageByteSwapTest_1058, IsLongLongType_ZeroIsNotLongLong_1058) {
    EXPECT_FALSE(Image::isLongLongType(0));
}

// ============================================================
// Tests for byteSwap2, byteSwap4, byteSwap8 with DataBuf
// ============================================================

TEST_F(ImageByteSwapTest_1058, ByteSwap2_NoSwap_1058) {
    DataBuf buf(4);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    uint16_t result = Image::byteSwap2(buf, 0, false);
    // No swap: should read as-is (platform-dependent byte order interpretation)
    // With bSwap=false, the raw bytes 0x12, 0x34 should be returned as the native uint16
    uint16_t expected = static_cast<uint16_t>(buf.read_uint8(0)) | 
                        (static_cast<uint16_t>(buf.read_uint8(1)) << 8);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap4_NoSwap_1058) {
    DataBuf buf(8);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    buf.write_uint8(2, 0x56);
    buf.write_uint8(3, 0x78);
    uint32_t result = Image::byteSwap4(buf, 0, false);
    uint32_t expected = static_cast<uint32_t>(buf.read_uint8(0)) |
                        (static_cast<uint32_t>(buf.read_uint8(1)) << 8) |
                        (static_cast<uint32_t>(buf.read_uint8(2)) << 16) |
                        (static_cast<uint32_t>(buf.read_uint8(3)) << 24);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap2_SwapAndNoSwapDiffer_1058) {
    DataBuf buf(4);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    uint16_t resultNoSwap = Image::byteSwap2(buf, 0, false);
    uint16_t resultSwap = Image::byteSwap2(buf, 0, true);
    // When bytes are different, swapping should produce a different result
    EXPECT_NE(resultNoSwap, resultSwap);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap4_SwapAndNoSwapDiffer_1058) {
    DataBuf buf(8);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    buf.write_uint8(2, 0x56);
    buf.write_uint8(3, 0x78);
    uint32_t resultNoSwap = Image::byteSwap4(buf, 0, false);
    uint32_t resultSwap = Image::byteSwap4(buf, 0, true);
    EXPECT_NE(resultNoSwap, resultSwap);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap4_WithOffset_1058) {
    DataBuf buf(8);
    buf.write_uint8(0, 0x00);
    buf.write_uint8(1, 0x00);
    buf.write_uint8(2, 0xAA);
    buf.write_uint8(3, 0xBB);
    buf.write_uint8(4, 0xCC);
    buf.write_uint8(5, 0xDD);
    uint32_t resultNoSwap = Image::byteSwap4(buf, 2, false);
    uint32_t expected = static_cast<uint32_t>(0xAA) |
                        (static_cast<uint32_t>(0xBB) << 8) |
                        (static_cast<uint32_t>(0xCC) << 16) |
                        (static_cast<uint32_t>(0xDD) << 24);
    EXPECT_EQ(resultNoSwap, expected);
}

// ============================================================
// Tests for byteSwap32 with palindromic value
// ============================================================

TEST_F(ImageByteSwapTest_1058, ByteSwap32_Palindrome_Swap_1058) {
    // A palindromic byte pattern should be unchanged after swap
    uint32_t value = 0xABBAABBA;
    uint32_t result = Image::byteSwap(value, true);
    // 0xAB BA AB BA -> reversed: BA AB BA AB = 0xBAABBAAB
    EXPECT_EQ(result, 0xBAABBAABU);
}

TEST_F(ImageByteSwapTest_1058, ByteSwap32_SymmetricValue_Swap_1058) {
    // 0x12211221 -> swap -> 0x21122112
    uint32_t value = 0x12211221;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x21122112U);
}
