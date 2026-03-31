#include <gtest/gtest.h>
#include <exiv2/image.hpp>
#include <exiv2/types.hpp>
#include <exiv2/basicio.hpp>
#include <sstream>
#include <memory>

// Test fixture for static methods that don't require an Image instance
class ImageStaticTest_1053 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Tests for is4ByteType
// ============================================================

TEST_F(ImageStaticTest_1053, Is4ByteType_UnsignedLong_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1053, Is4ByteType_SignedLong_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::signedLong));
}

TEST_F(ImageStaticTest_1053, Is4ByteType_TiffFloat_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::tiffFloat));
}

TEST_F(ImageStaticTest_1053, Is4ByteType_TiffIfd_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::tiffIfd));
}

TEST_F(ImageStaticTest_1053, Is4ByteType_UnsignedShort_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::unsignedShort));
}

TEST_F(ImageStaticTest_1053, Is4ByteType_UnsignedByte_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::unsignedByte));
}

TEST_F(ImageStaticTest_1053, Is4ByteType_AsciiString_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::asciiString));
}

TEST_F(ImageStaticTest_1053, Is4ByteType_UnsignedRational_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::unsignedRational));
}

TEST_F(ImageStaticTest_1053, Is4ByteType_SignedRational_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::signedRational));
}

TEST_F(ImageStaticTest_1053, Is4ByteType_TiffDouble_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::tiffDouble));
}

TEST_F(ImageStaticTest_1053, Is4ByteType_Undefined_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::undefined));
}

TEST_F(ImageStaticTest_1053, Is4ByteType_SignedByte_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::signedByte));
}

TEST_F(ImageStaticTest_1053, Is4ByteType_SignedShort_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::signedShort));
}

TEST_F(ImageStaticTest_1053, Is4ByteType_UnsignedLongLong_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::unsignedLongLong));
}

TEST_F(ImageStaticTest_1053, Is4ByteType_SignedLongLong_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::signedLongLong));
}

TEST_F(ImageStaticTest_1053, Is4ByteType_TiffIfd8_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::tiffIfd8));
}

TEST_F(ImageStaticTest_1053, Is4ByteType_Zero_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(0));
}

TEST_F(ImageStaticTest_1053, Is4ByteType_InvalidTypeId_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::invalidTypeId));
}

// ============================================================
// Tests for isLongType
// ============================================================

TEST_F(ImageStaticTest_1053, IsLongType_UnsignedLong_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::isLongType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1053, IsLongType_SignedLong_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::isLongType(Exiv2::signedLong));
}

TEST_F(ImageStaticTest_1053, IsLongType_UnsignedShort_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::isLongType(Exiv2::unsignedShort));
}

TEST_F(ImageStaticTest_1053, IsLongType_TiffFloat_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::isLongType(Exiv2::tiffFloat));
}

TEST_F(ImageStaticTest_1053, IsLongType_TiffIfd_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::isLongType(Exiv2::tiffIfd));
}

// ============================================================
// Tests for isShortType
// ============================================================

TEST_F(ImageStaticTest_1053, IsShortType_UnsignedShort_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::isShortType(Exiv2::unsignedShort));
}

TEST_F(ImageStaticTest_1053, IsShortType_SignedShort_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::isShortType(Exiv2::signedShort));
}

TEST_F(ImageStaticTest_1053, IsShortType_UnsignedLong_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::isShortType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1053, IsShortType_UnsignedByte_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::isShortType(Exiv2::unsignedByte));
}

// ============================================================
// Tests for isStringType
// ============================================================

TEST_F(ImageStaticTest_1053, IsStringType_AsciiString_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::isStringType(Exiv2::asciiString));
}

TEST_F(ImageStaticTest_1053, IsStringType_UnsignedLong_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::isStringType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1053, IsStringType_UnsignedByte_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::isStringType(Exiv2::unsignedByte));
}

// ============================================================
// Tests for isLongLongType
// ============================================================

TEST_F(ImageStaticTest_1053, IsLongLongType_UnsignedLongLong_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::isLongLongType(Exiv2::unsignedLongLong));
}

TEST_F(ImageStaticTest_1053, IsLongLongType_SignedLongLong_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::isLongLongType(Exiv2::signedLongLong));
}

TEST_F(ImageStaticTest_1053, IsLongLongType_UnsignedLong_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::unsignedLong));
}

// ============================================================
// Tests for isRationalType
// ============================================================

TEST_F(ImageStaticTest_1053, IsRationalType_UnsignedRational_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::isRationalType(Exiv2::unsignedRational));
}

TEST_F(ImageStaticTest_1053, IsRationalType_SignedRational_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::isRationalType(Exiv2::signedRational));
}

TEST_F(ImageStaticTest_1053, IsRationalType_UnsignedLong_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::isRationalType(Exiv2::unsignedLong));
}

// ============================================================
// Tests for is2ByteType
// ============================================================

TEST_F(ImageStaticTest_1053, Is2ByteType_UnsignedShort_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::is2ByteType(Exiv2::unsignedShort));
}

TEST_F(ImageStaticTest_1053, Is2ByteType_SignedShort_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::is2ByteType(Exiv2::signedShort));
}

TEST_F(ImageStaticTest_1053, Is2ByteType_UnsignedLong_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is2ByteType(Exiv2::unsignedLong));
}

// ============================================================
// Tests for is8ByteType
// ============================================================

TEST_F(ImageStaticTest_1053, Is8ByteType_UnsignedRational_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::unsignedRational));
}

TEST_F(ImageStaticTest_1053, Is8ByteType_SignedRational_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::signedRational));
}

TEST_F(ImageStaticTest_1053, Is8ByteType_TiffDouble_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::tiffDouble));
}

TEST_F(ImageStaticTest_1053, Is8ByteType_UnsignedLongLong_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::unsignedLongLong));
}

TEST_F(ImageStaticTest_1053, Is8ByteType_SignedLongLong_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::signedLongLong));
}

TEST_F(ImageStaticTest_1053, Is8ByteType_TiffIfd8_ReturnsTrue_1053) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::tiffIfd8));
}

TEST_F(ImageStaticTest_1053, Is8ByteType_UnsignedLong_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1053, Is8ByteType_UnsignedShort_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::unsignedShort));
}

// ============================================================
// Tests for platform endianness
// ============================================================

TEST_F(ImageStaticTest_1053, EndiannessMutuallyExclusive_1053) {
    bool isBig = Exiv2::Image::isBigEndianPlatform();
    bool isLittle = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_NE(isBig, isLittle);
}

// ============================================================
// Tests for byteSwap
// ============================================================

TEST_F(ImageStaticTest_1053, ByteSwap16_NoSwap_ReturnsSameValue_1053) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageStaticTest_1053, ByteSwap16_Swap_ReturnsSwappedValue_1053) {
    uint16_t val = 0x1234;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, static_cast<uint16_t>(0x3412));
}

TEST_F(ImageStaticTest_1053, ByteSwap32_NoSwap_ReturnsSameValue_1053) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageStaticTest_1053, ByteSwap32_Swap_ReturnsSwappedValue_1053) {
    uint32_t val = 0x12345678;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, static_cast<uint32_t>(0x78563412));
}

TEST_F(ImageStaticTest_1053, ByteSwap64_NoSwap_ReturnsSameValue_1053) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageStaticTest_1053, ByteSwap64_Swap_ReturnsSwappedValue_1053) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, static_cast<uint64_t>(0x0807060504030201ULL));
}

TEST_F(ImageStaticTest_1053, ByteSwap16_Zero_1053) {
    uint16_t val = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), static_cast<uint16_t>(0));
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), static_cast<uint16_t>(0));
}

TEST_F(ImageStaticTest_1053, ByteSwap32_Zero_1053) {
    uint32_t val = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), static_cast<uint32_t>(0));
}

TEST_F(ImageStaticTest_1053, ByteSwap64_Zero_1053) {
    uint64_t val = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), static_cast<uint64_t>(0));
}

TEST_F(ImageStaticTest_1053, ByteSwap16_MaxValue_1053) {
    uint16_t val = 0xFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), static_cast<uint16_t>(0xFFFF));
}

TEST_F(ImageStaticTest_1053, ByteSwap32_MaxValue_1053) {
    uint32_t val = 0xFFFFFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), static_cast<uint32_t>(0xFFFFFFFF));
}

// ============================================================
// Tests for byteSwap2, byteSwap4, byteSwap8 with DataBuf
// ============================================================

TEST_F(ImageStaticTest_1053, ByteSwap2_NoSwap_1053) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    uint16_t result = Exiv2::Image::byteSwap2(buf, 0, false);
    // Without swap, should read as-is in memory order
    uint16_t expected;
    std::memcpy(&expected, buf.c_data(), 2);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticTest_1053, ByteSwap2_Swap_1053) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
    EXPECT_EQ(swapped, Exiv2::Image::byteSwap(noSwap, true));
}

TEST_F(ImageStaticTest_1053, ByteSwap4_NoSwap_1053) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    buf.data()[2] = 0x56;
    buf.data()[3] = 0x78;
    uint32_t result = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t expected;
    std::memcpy(&expected, buf.c_data(), 4);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticTest_1053, ByteSwap4_WithOffset_1053) {
    Exiv2::DataBuf buf(8);
    buf.data()[2] = 0xAB;
    buf.data()[3] = 0xCD;
    buf.data()[4] = 0xEF;
    buf.data()[5] = 0x01;
    uint32_t result = Exiv2::Image::byteSwap4(buf, 2, false);
    uint32_t expected;
    std::memcpy(&expected, buf.c_data() + 2, 4);
    EXPECT_EQ(result, expected);
}

// ============================================================
// Tests for isPrintXMP and isPrintICC
// ============================================================

TEST_F(ImageStaticTest_1053, IsPrintXMP_WithStringTypeAndPrintXMP_1053) {
    // asciiString (type 2) with kpsXMP option
    bool result = Exiv2::Image::isPrintXMP(Exiv2::asciiString, Exiv2::kpsXMP);
    // We just verify it returns a bool without crashing
    (void)result;
}

TEST_F(ImageStaticTest_1053, IsPrintICC_WithUndefinedTypeAndPrintICC_1053) {
    bool result = Exiv2::Image::isPrintICC(Exiv2::undefined, Exiv2::kpsIccProfile);
    (void)result;
}

// ============================================================
// Tests for boundary/edge cases on type classification
// ============================================================

TEST_F(ImageStaticTest_1053, Is4ByteType_AllNon4ByteTypes_ReturnsFalse_1053) {
    // Test a selection of types that should NOT be 4-byte
    std::vector<uint16_t> non4ByteTypes = {
        Exiv2::unsignedByte,
        Exiv2::asciiString,
        Exiv2::unsignedShort,
        Exiv2::unsignedRational,
        Exiv2::signedByte,
        Exiv2::undefined,
        Exiv2::signedShort,
        Exiv2::signedRational,
        Exiv2::tiffDouble,
        Exiv2::unsignedLongLong,
        Exiv2::signedLongLong,
        Exiv2::tiffIfd8
    };
    for (auto type : non4ByteTypes) {
        EXPECT_FALSE(Exiv2::Image::is4ByteType(type)) << "Type " << type << " should not be 4-byte";
    }
}

TEST_F(ImageStaticTest_1053, Is4ByteType_All4ByteTypes_ReturnsTrue_1053) {
    std::vector<uint16_t> fourByteTypes = {
        Exiv2::unsignedLong,
        Exiv2::signedLong,
        Exiv2::tiffFloat,
        Exiv2::tiffIfd
    };
    for (auto type : fourByteTypes) {
        EXPECT_TRUE(Exiv2::Image::is4ByteType(type)) << "Type " << type << " should be 4-byte";
    }
}

// ============================================================
// Tests for byteSwap double-swap identity
// ============================================================

TEST_F(ImageStaticTest_1053, ByteSwap16_DoubleSwapIsIdentity_1053) {
    uint16_t val = 0xABCD;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    uint16_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, val);
}

TEST_F(ImageStaticTest_1053, ByteSwap32_DoubleSwapIsIdentity_1053) {
    uint32_t val = 0xDEADBEEF;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    uint32_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, val);
}

TEST_F(ImageStaticTest_1053, ByteSwap64_DoubleSwapIsIdentity_1053) {
    uint64_t val = 0xDEADBEEFCAFEBABEULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    uint64_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, val);
}

// ============================================================
// Tests with MemIo-backed Image instance
// ============================================================

class ImageInstanceTest_1053 : public ::testing::Test {
protected:
    // We'll use a MemIo-based approach. Since Image is abstract (has pure virtual methods),
    // we need a concrete subclass. We'll test only the non-virtual methods through a minimal approach.
    // Actually, Image's constructor is protected/public but Image itself has pure virtual readMetadata/writeMetadata.
    // We can still test static methods without an instance.
};

// Additional edge case for type 0
TEST_F(ImageStaticTest_1053, IsStringType_Zero_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::isStringType(0));
}

TEST_F(ImageStaticTest_1053, IsShortType_Zero_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::isShortType(0));
}

TEST_F(ImageStaticTest_1053, IsLongType_Zero_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::isLongType(0));
}

TEST_F(ImageStaticTest_1053, IsLongLongType_Zero_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::isLongLongType(0));
}

TEST_F(ImageStaticTest_1053, IsRationalType_Zero_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::isRationalType(0));
}

TEST_F(ImageStaticTest_1053, Is2ByteType_Zero_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is2ByteType(0));
}

TEST_F(ImageStaticTest_1053, Is4ByteType_ZeroBoundary_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(0));
}

TEST_F(ImageStaticTest_1053, Is8ByteType_Zero_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(0));
}

// ============================================================
// Tests for large/invalid type values
// ============================================================

TEST_F(ImageStaticTest_1053, Is4ByteType_LargeInvalidValue_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(65535));
}

TEST_F(ImageStaticTest_1053, IsLongType_LargeInvalidValue_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::isLongType(65535));
}

TEST_F(ImageStaticTest_1053, Is8ByteType_LargeInvalidValue_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(65535));
}

TEST_F(ImageStaticTest_1053, Is2ByteType_LargeInvalidValue_ReturnsFalse_1053) {
    EXPECT_FALSE(Exiv2::Image::is2ByteType(65535));
}
