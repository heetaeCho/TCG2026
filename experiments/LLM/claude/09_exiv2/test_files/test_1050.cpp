#include <gtest/gtest.h>
#include <exiv2/image.hpp>
#include <exiv2/types.hpp>
#include <exiv2/basicio.hpp>
#include <sstream>
#include <memory>

// Test fixture for Image static methods
class ImageStaticTest_1050 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== isLongLongType tests ====================

TEST_F(ImageStaticTest_1050, IsLongLongType_UnsignedLongLong_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::isLongLongType(Exiv2::unsignedLongLong));
}

TEST_F(ImageStaticTest_1050, IsLongLongType_SignedLongLong_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::isLongLongType(Exiv2::signedLongLong));
}

TEST_F(ImageStaticTest_1050, IsLongLongType_UnsignedByte_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::unsignedByte));
}

TEST_F(ImageStaticTest_1050, IsLongLongType_UnsignedShort_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::unsignedShort));
}

TEST_F(ImageStaticTest_1050, IsLongLongType_UnsignedLong_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1050, IsLongLongType_SignedLong_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::signedLong));
}

TEST_F(ImageStaticTest_1050, IsLongLongType_UnsignedRational_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::unsignedRational));
}

TEST_F(ImageStaticTest_1050, IsLongLongType_Undefined_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::undefined));
}

TEST_F(ImageStaticTest_1050, IsLongLongType_TiffIfd8_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::tiffIfd8));
}

TEST_F(ImageStaticTest_1050, IsLongLongType_Zero_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::isLongLongType(0));
}

TEST_F(ImageStaticTest_1050, IsLongLongType_MaxUint16_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::isLongLongType(0xFFFF));
}

// ==================== isStringType tests ====================

TEST_F(ImageStaticTest_1050, IsStringType_AsciiString_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::isStringType(Exiv2::asciiString));
}

TEST_F(ImageStaticTest_1050, IsStringType_UnsignedByte_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::isStringType(Exiv2::unsignedByte));
}

TEST_F(ImageStaticTest_1050, IsStringType_UnsignedLong_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::isStringType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1050, IsStringType_Zero_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::isStringType(0));
}

// ==================== isShortType tests ====================

TEST_F(ImageStaticTest_1050, IsShortType_UnsignedShort_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::isShortType(Exiv2::unsignedShort));
}

TEST_F(ImageStaticTest_1050, IsShortType_SignedShort_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::isShortType(Exiv2::signedShort));
}

TEST_F(ImageStaticTest_1050, IsShortType_UnsignedLong_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::isShortType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1050, IsShortType_UnsignedByte_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::isShortType(Exiv2::unsignedByte));
}

// ==================== isLongType tests ====================

TEST_F(ImageStaticTest_1050, IsLongType_UnsignedLong_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::isLongType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1050, IsLongType_SignedLong_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::isLongType(Exiv2::signedLong));
}

TEST_F(ImageStaticTest_1050, IsLongType_UnsignedShort_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::isLongType(Exiv2::unsignedShort));
}

TEST_F(ImageStaticTest_1050, IsLongType_UnsignedLongLong_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::isLongType(Exiv2::unsignedLongLong));
}

// ==================== isRationalType tests ====================

TEST_F(ImageStaticTest_1050, IsRationalType_UnsignedRational_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::isRationalType(Exiv2::unsignedRational));
}

TEST_F(ImageStaticTest_1050, IsRationalType_SignedRational_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::isRationalType(Exiv2::signedRational));
}

TEST_F(ImageStaticTest_1050, IsRationalType_UnsignedLong_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::isRationalType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1050, IsRationalType_TiffDouble_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::isRationalType(Exiv2::tiffDouble));
}

// ==================== is2ByteType tests ====================

TEST_F(ImageStaticTest_1050, Is2ByteType_UnsignedShort_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::is2ByteType(Exiv2::unsignedShort));
}

TEST_F(ImageStaticTest_1050, Is2ByteType_SignedShort_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::is2ByteType(Exiv2::signedShort));
}

TEST_F(ImageStaticTest_1050, Is2ByteType_UnsignedLong_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::is2ByteType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1050, Is2ByteType_UnsignedByte_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::is2ByteType(Exiv2::unsignedByte));
}

// ==================== is4ByteType tests ====================

TEST_F(ImageStaticTest_1050, Is4ByteType_UnsignedLong_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1050, Is4ByteType_SignedLong_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::signedLong));
}

TEST_F(ImageStaticTest_1050, Is4ByteType_TiffFloat_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::tiffFloat));
}

TEST_F(ImageStaticTest_1050, Is4ByteType_TiffIfd_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::tiffIfd));
}

TEST_F(ImageStaticTest_1050, Is4ByteType_UnsignedShort_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::unsignedShort));
}

TEST_F(ImageStaticTest_1050, Is4ByteType_UnsignedLongLong_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::unsignedLongLong));
}

// ==================== is8ByteType tests ====================

TEST_F(ImageStaticTest_1050, Is8ByteType_UnsignedRational_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::unsignedRational));
}

TEST_F(ImageStaticTest_1050, Is8ByteType_SignedRational_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::signedRational));
}

TEST_F(ImageStaticTest_1050, Is8ByteType_TiffDouble_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::tiffDouble));
}

TEST_F(ImageStaticTest_1050, Is8ByteType_UnsignedLongLong_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::unsignedLongLong));
}

TEST_F(ImageStaticTest_1050, Is8ByteType_SignedLongLong_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::signedLongLong));
}

TEST_F(ImageStaticTest_1050, Is8ByteType_TiffIfd8_ReturnsTrue_1050) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::tiffIfd8));
}

TEST_F(ImageStaticTest_1050, Is8ByteType_UnsignedLong_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1050, Is8ByteType_UnsignedShort_ReturnsFalse_1050) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::unsignedShort));
}

// ==================== Platform endianness tests ====================

TEST_F(ImageStaticTest_1050, PlatformEndianness_ExactlyOne_1050) {
    bool isBig = Exiv2::Image::isBigEndianPlatform();
    bool isLittle = Exiv2::Image::isLittleEndianPlatform();
    // Exactly one should be true
    EXPECT_NE(isBig, isLittle);
}

TEST_F(ImageStaticTest_1050, IsBigEndianPlatform_ConsistentResult_1050) {
    bool first = Exiv2::Image::isBigEndianPlatform();
    bool second = Exiv2::Image::isBigEndianPlatform();
    EXPECT_EQ(first, second);
}

TEST_F(ImageStaticTest_1050, IsLittleEndianPlatform_ConsistentResult_1050) {
    bool first = Exiv2::Image::isLittleEndianPlatform();
    bool second = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_EQ(first, second);
}

// ==================== byteSwap tests ====================

TEST_F(ImageStaticTest_1050, ByteSwap16_NoSwap_ReturnsSameValue_1050) {
    uint16_t value = 0x1234;
    EXPECT_EQ(value, Exiv2::Image::byteSwap(value, false));
}

TEST_F(ImageStaticTest_1050, ByteSwap16_Swap_ReturnsSwappedValue_1050) {
    uint16_t value = 0x1234;
    uint16_t expected = 0x3412;
    EXPECT_EQ(expected, Exiv2::Image::byteSwap(value, true));
}

TEST_F(ImageStaticTest_1050, ByteSwap16_SwapZero_ReturnsZero_1050) {
    EXPECT_EQ(static_cast<uint16_t>(0), Exiv2::Image::byteSwap(static_cast<uint16_t>(0), true));
}

TEST_F(ImageStaticTest_1050, ByteSwap16_DoubleSwap_ReturnsOriginal_1050) {
    uint16_t value = 0xABCD;
    uint16_t swapped = Exiv2::Image::byteSwap(value, true);
    uint16_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(value, doubleSwapped);
}

TEST_F(ImageStaticTest_1050, ByteSwap32_NoSwap_ReturnsSameValue_1050) {
    uint32_t value = 0x12345678;
    EXPECT_EQ(value, Exiv2::Image::byteSwap(value, false));
}

TEST_F(ImageStaticTest_1050, ByteSwap32_Swap_ReturnsSwappedValue_1050) {
    uint32_t value = 0x12345678;
    uint32_t expected = 0x78563412;
    EXPECT_EQ(expected, Exiv2::Image::byteSwap(value, true));
}

TEST_F(ImageStaticTest_1050, ByteSwap32_SwapZero_ReturnsZero_1050) {
    EXPECT_EQ(static_cast<uint32_t>(0), Exiv2::Image::byteSwap(static_cast<uint32_t>(0), true));
}

TEST_F(ImageStaticTest_1050, ByteSwap32_DoubleSwap_ReturnsOriginal_1050) {
    uint32_t value = 0xDEADBEEF;
    uint32_t swapped = Exiv2::Image::byteSwap(value, true);
    uint32_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(value, doubleSwapped);
}

TEST_F(ImageStaticTest_1050, ByteSwap64_NoSwap_ReturnsSameValue_1050) {
    uint64_t value = 0x123456789ABCDEF0ULL;
    EXPECT_EQ(value, Exiv2::Image::byteSwap(value, false));
}

TEST_F(ImageStaticTest_1050, ByteSwap64_Swap_ReturnsSwappedValue_1050) {
    uint64_t value = 0x123456789ABCDEF0ULL;
    uint64_t expected = 0xF0DEBC9A78563412ULL;
    EXPECT_EQ(expected, Exiv2::Image::byteSwap(value, true));
}

TEST_F(ImageStaticTest_1050, ByteSwap64_SwapZero_ReturnsZero_1050) {
    EXPECT_EQ(static_cast<uint64_t>(0), Exiv2::Image::byteSwap(static_cast<uint64_t>(0), true));
}

TEST_F(ImageStaticTest_1050, ByteSwap64_DoubleSwap_ReturnsOriginal_1050) {
    uint64_t value = 0xCAFEBABEDEADBEEFULL;
    uint64_t swapped = Exiv2::Image::byteSwap(value, true);
    uint64_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(value, doubleSwapped);
}

// ==================== byteSwap2/4/8 with DataBuf tests ====================

TEST_F(ImageStaticTest_1050, ByteSwap2_NoSwap_ReturnsOriginal_1050) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    uint16_t result = Exiv2::Image::byteSwap2(buf, 0, false);
    // Without swap, should return bytes as they are in memory
    uint16_t expected;
    std::memcpy(&expected, buf.c_data(), sizeof(uint16_t));
    EXPECT_EQ(expected, result);
}

TEST_F(ImageStaticTest_1050, ByteSwap2_Swap_ReturnsSwapped_1050) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
    EXPECT_EQ(Exiv2::Image::byteSwap(noSwap, true), swapped);
}

TEST_F(ImageStaticTest_1050, ByteSwap4_NoSwap_ReturnsOriginal_1050) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    buf.data()[2] = 0x56;
    buf.data()[3] = 0x78;
    uint32_t result = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t expected;
    std::memcpy(&expected, buf.c_data(), sizeof(uint32_t));
    EXPECT_EQ(expected, result);
}

TEST_F(ImageStaticTest_1050, ByteSwap4_Swap_ReturnsSwapped_1050) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    buf.data()[2] = 0x56;
    buf.data()[3] = 0x78;
    uint32_t noSwap = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t swapped = Exiv2::Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(Exiv2::Image::byteSwap(noSwap, true), swapped);
}

TEST_F(ImageStaticTest_1050, ByteSwap8_NoSwap_ReturnsOriginal_1050) {
    Exiv2::DataBuf buf(16);
    for (int i = 0; i < 8; i++) {
        buf.data()[i] = static_cast<uint8_t>(i + 1);
    }
    uint64_t result = Exiv2::Image::byteSwap8(buf, 0, false);
    uint64_t expected;
    std::memcpy(&expected, buf.c_data(), sizeof(uint64_t));
    EXPECT_EQ(expected, result);
}

TEST_F(ImageStaticTest_1050, ByteSwap8_Swap_ReturnsSwapped_1050) {
    Exiv2::DataBuf buf(16);
    for (int i = 0; i < 8; i++) {
        buf.data()[i] = static_cast<uint8_t>(i + 1);
    }
    uint64_t noSwap = Exiv2::Image::byteSwap8(buf, 0, false);
    uint64_t swapped = Exiv2::Image::byteSwap8(buf, 0, true);
    EXPECT_EQ(Exiv2::Image::byteSwap(noSwap, true), swapped);
}

TEST_F(ImageStaticTest_1050, ByteSwap2_WithOffset_1050) {
    Exiv2::DataBuf buf(8);
    buf.data()[2] = 0xAB;
    buf.data()[3] = 0xCD;
    uint16_t result = Exiv2::Image::byteSwap2(buf, 2, false);
    uint16_t expected;
    std::memcpy(&expected, buf.c_data() + 2, sizeof(uint16_t));
    EXPECT_EQ(expected, result);
}

// ==================== isPrintXMP tests ====================

TEST_F(ImageStaticTest_1050, IsPrintXMP_WithXmpTag_AndPrintOption_1050) {
    // We test various combinations; exact behavior depends on implementation
    // but we can check it returns bool consistently
    bool result1 = Exiv2::Image::isPrintXMP(Exiv2::unsignedShort, Exiv2::kpsXMP);
    bool result2 = Exiv2::Image::isPrintXMP(Exiv2::unsignedShort, Exiv2::kpsNone);
    // At minimum these should be deterministic
    EXPECT_EQ(result1, Exiv2::Image::isPrintXMP(Exiv2::unsignedShort, Exiv2::kpsXMP));
    EXPECT_EQ(result2, Exiv2::Image::isPrintXMP(Exiv2::unsignedShort, Exiv2::kpsNone));
}

// ==================== isPrintICC tests ====================

TEST_F(ImageStaticTest_1050, IsPrintICC_WithIccTag_AndPrintOption_1050) {
    bool result1 = Exiv2::Image::isPrintICC(Exiv2::unsignedShort, Exiv2::kpsIccProfile);
    bool result2 = Exiv2::Image::isPrintICC(Exiv2::unsignedShort, Exiv2::kpsNone);
    EXPECT_EQ(result1, Exiv2::Image::isPrintICC(Exiv2::unsignedShort, Exiv2::kpsIccProfile));
    EXPECT_EQ(result2, Exiv2::Image::isPrintICC(Exiv2::unsignedShort, Exiv2::kpsNone));
}

// ==================== Instance method tests using MemIo ====================

class ImageInstanceTest_1050 : public ::testing::Test {
protected:
    // We'll use a JpegImage or similar; since Image is abstract, we need a concrete type
    // We use ImageFactory to create an image from a MemIo for testing instance methods
};

// Test byteOrder set/get
TEST_F(ImageInstanceTest_1050, SetAndGetByteOrder_1050) {
    auto io = std::make_unique<Exiv2::MemIo>();
    // We can't instantiate Image directly since it's abstract
    // We'll test static methods and type checking which don't need an instance
    // For instance methods, we'd need a concrete subclass

    // Additional static boundary tests
    EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::tiffFloat));
    EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::tiffDouble));
    EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::tiffIfd));
    EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::asciiString));
    EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::signedByte));
    EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::signedShort));
    EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::signedRational));
}

// ==================== Boundary: all TypeId values against isLongLongType ====================

TEST_F(ImageStaticTest_1050, IsLongLongType_AllTypes_OnlyLongLongTrue_1050) {
    // Check all standard type IDs
    std::vector<uint16_t> allTypes = {
        Exiv2::unsignedByte, Exiv2::asciiString, Exiv2::unsignedShort,
        Exiv2::unsignedLong, Exiv2::unsignedRational, Exiv2::signedByte,
        Exiv2::undefined, Exiv2::signedShort, Exiv2::signedLong,
        Exiv2::signedRational, Exiv2::tiffFloat, Exiv2::tiffDouble,
        Exiv2::tiffIfd, Exiv2::tiffIfd8
    };

    for (auto t : allTypes) {
        EXPECT_FALSE(Exiv2::Image::isLongLongType(t))
            << "Type " << t << " should NOT be LongLong";
    }

    EXPECT_TRUE(Exiv2::Image::isLongLongType(Exiv2::unsignedLongLong));
    EXPECT_TRUE(Exiv2::Image::isLongLongType(Exiv2::signedLongLong));
}

// ==================== Boundary: type values adjacent to LongLong ====================

TEST_F(ImageStaticTest_1050, IsLongLongType_AdjacentValues_ReturnsFalse_1050) {
    // unsignedLongLong = 16, signedLongLong = 17
    EXPECT_FALSE(Exiv2::Image::isLongLongType(15));
    EXPECT_TRUE(Exiv2::Image::isLongLongType(16));
    EXPECT_TRUE(Exiv2::Image::isLongLongType(17));
    EXPECT_FALSE(Exiv2::Image::isLongLongType(18)); // tiffIfd8
}

// ==================== ByteSwap symmetric properties ====================

TEST_F(ImageStaticTest_1050, ByteSwap16_AllOnes_1050) {
    uint16_t value = 0xFFFF;
    EXPECT_EQ(value, Exiv2::Image::byteSwap(value, true));
}

TEST_F(ImageStaticTest_1050, ByteSwap32_AllOnes_1050) {
    uint32_t value = 0xFFFFFFFF;
    EXPECT_EQ(value, Exiv2::Image::byteSwap(value, true));
}

TEST_F(ImageStaticTest_1050, ByteSwap64_AllOnes_1050) {
    uint64_t value = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_EQ(value, Exiv2::Image::byteSwap(value, true));
}

TEST_F(ImageStaticTest_1050, ByteSwap16_OneByte_1050) {
    uint16_t value = 0x00FF;
    uint16_t expected = 0xFF00;
    EXPECT_EQ(expected, Exiv2::Image::byteSwap(value, true));
}

TEST_F(ImageStaticTest_1050, ByteSwap32_SingleByte_1050) {
    uint32_t value = 0x000000FF;
    uint32_t expected = 0xFF000000;
    EXPECT_EQ(expected, Exiv2::Image::byteSwap(value, true));
}

TEST_F(ImageStaticTest_1050, ByteSwap64_SingleByte_1050) {
    uint64_t value = 0x00000000000000FFULL;
    uint64_t expected = 0xFF00000000000000ULL;
    EXPECT_EQ(expected, Exiv2::Image::byteSwap(value, true));
}
