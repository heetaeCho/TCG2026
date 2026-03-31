#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <sstream>
#include <cstdint>
#include <memory>

namespace {

// Helper to create an Image instance for testing.
// Since Image is abstract (readMetadata/writeMetadata are pure virtual in some subclasses),
// we need a concrete subclass or use a type that can be instantiated.
// We'll use a MemIo-based approach with a minimal concrete image if possible.
// However, since the static methods can be called directly, we test those first.

class ImageByteSwapTest_1057 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// ==================== byteSwap(uint64_t, bool) tests ====================

TEST_F(ImageByteSwapTest_1057, ByteSwap64_NoSwap_1057) {
    uint64_t value = 0x0102030405060708ULL;
    uint64_t result = Exiv2::Image::byteSwap(value, false);
    EXPECT_EQ(result, value);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap64_Swap_1057) {
    uint64_t value = 0x0102030405060708ULL;
    uint64_t result = Exiv2::Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x0807060504030201ULL);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap64_SwapZero_1057) {
    uint64_t value = 0x0000000000000000ULL;
    uint64_t result = Exiv2::Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x0000000000000000ULL);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap64_SwapMax_1057) {
    uint64_t value = 0xFFFFFFFFFFFFFFFFULL;
    uint64_t result = Exiv2::Image::byteSwap(value, true);
    EXPECT_EQ(result, 0xFFFFFFFFFFFFFFFFULL);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap64_SwapOne_1057) {
    uint64_t value = 0x0000000000000001ULL;
    uint64_t result = Exiv2::Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x0100000000000000ULL);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap64_DoubleSwapIsIdentity_1057) {
    uint64_t value = 0xDEADBEEFCAFEBABEULL;
    uint64_t swapped = Exiv2::Image::byteSwap(value, true);
    uint64_t result = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(result, value);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap64_NoSwapMax_1057) {
    uint64_t value = 0xFFFFFFFFFFFFFFFFULL;
    uint64_t result = Exiv2::Image::byteSwap(value, false);
    EXPECT_EQ(result, value);
}

// ==================== byteSwap(uint32_t, bool) tests ====================

TEST_F(ImageByteSwapTest_1057, ByteSwap32_NoSwap_1057) {
    uint32_t value = 0x01020304;
    uint32_t result = Exiv2::Image::byteSwap(value, false);
    EXPECT_EQ(result, value);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap32_Swap_1057) {
    uint32_t value = 0x01020304;
    uint32_t result = Exiv2::Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x04030201u);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap32_SwapZero_1057) {
    uint32_t result = Exiv2::Image::byteSwap(static_cast<uint32_t>(0), true);
    EXPECT_EQ(result, 0u);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap32_SwapMax_1057) {
    uint32_t result = Exiv2::Image::byteSwap(static_cast<uint32_t>(0xFFFFFFFF), true);
    EXPECT_EQ(result, 0xFFFFFFFFu);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap32_DoubleSwapIsIdentity_1057) {
    uint32_t value = 0xDEADBEEF;
    uint32_t swapped = Exiv2::Image::byteSwap(value, true);
    uint32_t result = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(result, value);
}

// ==================== byteSwap(uint16_t, bool) tests ====================

TEST_F(ImageByteSwapTest_1057, ByteSwap16_NoSwap_1057) {
    uint16_t value = 0x0102;
    uint16_t result = Exiv2::Image::byteSwap(value, false);
    EXPECT_EQ(result, value);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap16_Swap_1057) {
    uint16_t value = 0x0102;
    uint16_t result = Exiv2::Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x0201);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap16_SwapZero_1057) {
    uint16_t result = Exiv2::Image::byteSwap(static_cast<uint16_t>(0), true);
    EXPECT_EQ(result, 0);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap16_SwapMax_1057) {
    uint16_t result = Exiv2::Image::byteSwap(static_cast<uint16_t>(0xFFFF), true);
    EXPECT_EQ(result, 0xFFFF);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap16_DoubleSwapIsIdentity_1057) {
    uint16_t value = 0xABCD;
    uint16_t swapped = Exiv2::Image::byteSwap(value, true);
    uint16_t result = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(result, value);
}

// ==================== Platform endianness tests ====================

TEST_F(ImageByteSwapTest_1057, PlatformEndianness_MutuallyExclusive_1057) {
    bool big = Exiv2::Image::isBigEndianPlatform();
    bool little = Exiv2::Image::isLittleEndianPlatform();
    // Platform should be one or the other
    EXPECT_NE(big, little);
}

TEST_F(ImageByteSwapTest_1057, IsBigEndianPlatform_Consistent_1057) {
    bool result1 = Exiv2::Image::isBigEndianPlatform();
    bool result2 = Exiv2::Image::isBigEndianPlatform();
    EXPECT_EQ(result1, result2);
}

TEST_F(ImageByteSwapTest_1057, IsLittleEndianPlatform_Consistent_1057) {
    bool result1 = Exiv2::Image::isLittleEndianPlatform();
    bool result2 = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_EQ(result1, result2);
}

// ==================== isStringType tests ====================

TEST_F(ImageByteSwapTest_1057, IsStringType_AsciiType_1057) {
    // Type 2 is typically ASCII string in TIFF/EXIF
    bool result = Exiv2::Image::isStringType(2);
    EXPECT_TRUE(result);
}

TEST_F(ImageByteSwapTest_1057, IsStringType_NonString_1057) {
    // Type 3 is SHORT, not a string
    bool result = Exiv2::Image::isStringType(3);
    EXPECT_FALSE(result);
}

TEST_F(ImageByteSwapTest_1057, IsStringType_Zero_1057) {
    bool result = Exiv2::Image::isStringType(0);
    EXPECT_FALSE(result);
}

// ==================== isShortType tests ====================

TEST_F(ImageByteSwapTest_1057, IsShortType_ShortType_1057) {
    // Type 3 is SHORT in TIFF
    bool result = Exiv2::Image::isShortType(3);
    EXPECT_TRUE(result);
}

TEST_F(ImageByteSwapTest_1057, IsShortType_NonShortType_1057) {
    bool result = Exiv2::Image::isShortType(2);
    EXPECT_FALSE(result);
}

// ==================== isLongType tests ====================

TEST_F(ImageByteSwapTest_1057, IsLongType_LongType_1057) {
    // Type 4 is LONG in TIFF
    bool result = Exiv2::Image::isLongType(4);
    EXPECT_TRUE(result);
}

TEST_F(ImageByteSwapTest_1057, IsLongType_NonLongType_1057) {
    bool result = Exiv2::Image::isLongType(3);
    EXPECT_FALSE(result);
}

// ==================== isRationalType tests ====================

TEST_F(ImageByteSwapTest_1057, IsRationalType_RationalType_1057) {
    // Type 5 is RATIONAL in TIFF
    bool result = Exiv2::Image::isRationalType(5);
    EXPECT_TRUE(result);
}

TEST_F(ImageByteSwapTest_1057, IsRationalType_NonRationalType_1057) {
    bool result = Exiv2::Image::isRationalType(4);
    EXPECT_FALSE(result);
}

// ==================== is2ByteType tests ====================

TEST_F(ImageByteSwapTest_1057, Is2ByteType_ShortType_1057) {
    // SHORT (3) is 2 bytes
    bool result = Exiv2::Image::is2ByteType(3);
    EXPECT_TRUE(result);
}

TEST_F(ImageByteSwapTest_1057, Is2ByteType_LongType_1057) {
    // LONG (4) is not 2 bytes
    bool result = Exiv2::Image::is2ByteType(4);
    EXPECT_FALSE(result);
}

// ==================== is4ByteType tests ====================

TEST_F(ImageByteSwapTest_1057, Is4ByteType_LongType_1057) {
    // LONG (4) is 4 bytes
    bool result = Exiv2::Image::is4ByteType(4);
    EXPECT_TRUE(result);
}

TEST_F(ImageByteSwapTest_1057, Is4ByteType_ShortType_1057) {
    bool result = Exiv2::Image::is4ByteType(3);
    EXPECT_FALSE(result);
}

// ==================== is8ByteType tests ====================

TEST_F(ImageByteSwapTest_1057, Is8ByteType_RationalType_1057) {
    // RATIONAL (5) is 8 bytes (two LONGs)
    bool result = Exiv2::Image::is8ByteType(5);
    EXPECT_TRUE(result);
}

TEST_F(ImageByteSwapTest_1057, Is8ByteType_ShortType_1057) {
    bool result = Exiv2::Image::is8ByteType(3);
    EXPECT_FALSE(result);
}

// ==================== byteSwap2, byteSwap4, byteSwap8 with DataBuf ====================

TEST_F(ImageByteSwapTest_1057, ByteSwap2_FromBuf_NoSwap_1057) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x01;
    buf.data()[1] = 0x02;
    uint16_t result = Exiv2::Image::byteSwap2(buf, 0, false);
    // Should read bytes as-is in native byte order without swapping
    uint16_t expected;
    std::memcpy(&expected, buf.data(), 2);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap2_FromBuf_Swap_1057) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x01;
    buf.data()[1] = 0x02;
    uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
    // Swapped should be the byte-swapped version of noSwap
    EXPECT_EQ(swapped, Exiv2::Image::byteSwap(noSwap, true));
}

TEST_F(ImageByteSwapTest_1057, ByteSwap4_FromBuf_NoSwap_1057) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x01;
    buf.data()[1] = 0x02;
    buf.data()[2] = 0x03;
    buf.data()[3] = 0x04;
    uint32_t result = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t expected;
    std::memcpy(&expected, buf.data(), 4);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap4_FromBuf_Swap_1057) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x01;
    buf.data()[1] = 0x02;
    buf.data()[2] = 0x03;
    buf.data()[3] = 0x04;
    uint32_t noSwap = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t swapped = Exiv2::Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(swapped, Exiv2::Image::byteSwap(noSwap, true));
}

TEST_F(ImageByteSwapTest_1057, ByteSwap8_FromBuf_NoSwap_1057) {
    Exiv2::DataBuf buf(16);
    for (int i = 0; i < 8; i++) {
        buf.data()[i] = static_cast<uint8_t>(i + 1);
    }
    uint64_t result = Exiv2::Image::byteSwap8(buf, 0, false);
    uint64_t expected;
    std::memcpy(&expected, buf.data(), 8);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap8_FromBuf_Swap_1057) {
    Exiv2::DataBuf buf(16);
    for (int i = 0; i < 8; i++) {
        buf.data()[i] = static_cast<uint8_t>(i + 1);
    }
    uint64_t noSwap = Exiv2::Image::byteSwap8(buf, 0, false);
    uint64_t swapped = Exiv2::Image::byteSwap8(buf, 0, true);
    EXPECT_EQ(swapped, Exiv2::Image::byteSwap(noSwap, true));
}

TEST_F(ImageByteSwapTest_1057, ByteSwap2_WithOffset_1057) {
    Exiv2::DataBuf buf(8);
    buf.data()[2] = 0xAB;
    buf.data()[3] = 0xCD;
    uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 2, false);
    uint16_t expected;
    std::memcpy(&expected, buf.data() + 2, 2);
    EXPECT_EQ(noSwap, expected);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap4_WithOffset_1057) {
    Exiv2::DataBuf buf(12);
    buf.data()[4] = 0xDE;
    buf.data()[5] = 0xAD;
    buf.data()[6] = 0xBE;
    buf.data()[7] = 0xEF;
    uint32_t noSwap = Exiv2::Image::byteSwap4(buf, 4, false);
    uint32_t expected;
    std::memcpy(&expected, buf.data() + 4, 4);
    EXPECT_EQ(noSwap, expected);
}

// ==================== Boundary: byteSwap with specific patterns ====================

TEST_F(ImageByteSwapTest_1057, ByteSwap64_HighBytOnly_1057) {
    uint64_t value = 0xFF00000000000000ULL;
    uint64_t result = Exiv2::Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x00000000000000FFULL);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap32_HighByteOnly_1057) {
    uint32_t value = 0xFF000000u;
    uint32_t result = Exiv2::Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x000000FFu);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap16_HighByteOnly_1057) {
    uint16_t value = 0xFF00;
    uint16_t result = Exiv2::Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x00FF);
}

TEST_F(ImageByteSwapTest_1057, ByteSwap64_Palindrome_1057) {
    // A palindromic pattern should remain the same after swap
    uint64_t value = 0x0102030303020100ULL;
    // Actually this is not a palindrome at byte level. Let's check:
    // bytes: 00 01 02 03 03 02 01 00 (little endian representation)
    // A true byte palindrome: 0x0102030330201000 won't work either.
    // Let's just use a symmetric value
    uint64_t symmetric = 0x0A0B0C0D0D0C0B0AULL;
    uint64_t result = Exiv2::Image::byteSwap(symmetric, true);
    EXPECT_EQ(result, symmetric);
}

// ==================== isLongLongType tests ====================

TEST_F(ImageByteSwapTest_1057, IsLongLongType_Zero_1057) {
    bool result = Exiv2::Image::isLongLongType(0);
    EXPECT_FALSE(result);
}

TEST_F(ImageByteSwapTest_1057, IsLongLongType_Type16_1057) {
    // Type 16 is LONG8 in BigTIFF
    bool result = Exiv2::Image::isLongLongType(16);
    EXPECT_TRUE(result);
}

// ==================== Multiple overloads consistency ====================

TEST_F(ImageByteSwapTest_1057, ByteSwap_AllSizes_NoSwapReturnsOriginal_1057) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0x1234), false), static_cast<uint16_t>(0x1234));
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint32_t>(0x12345678), false), static_cast<uint32_t>(0x12345678));
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint64_t>(0x123456789ABCDEF0ULL), false), static_cast<uint64_t>(0x123456789ABCDEF0ULL));
}

}  // namespace
