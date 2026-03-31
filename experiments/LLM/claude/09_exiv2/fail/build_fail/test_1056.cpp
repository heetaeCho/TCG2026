#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <sstream>
#include <memory>

// Test fixture for Image static methods and isPrintICC
class ImageTest_1056 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// ==================== isPrintICC Tests ====================

TEST_F(ImageTest_1056, IsPrintICC_CorrectTypeAndOption_ReturnsTrue_1056) {
    // type 0x8773 is the ICC profile tag, kpsIccProfile is the matching option
    EXPECT_TRUE(Exiv2::Image::isPrintICC(0x8773, Exiv2::kpsIccProfile));
}

TEST_F(ImageTest_1056, IsPrintICC_CorrectTypeWrongOption_ReturnsFalse_1056) {
    EXPECT_FALSE(Exiv2::Image::isPrintICC(0x8773, Exiv2::kpsNone));
    EXPECT_FALSE(Exiv2::Image::isPrintICC(0x8773, Exiv2::kpsBasic));
    EXPECT_FALSE(Exiv2::Image::isPrintICC(0x8773, Exiv2::kpsXMP));
    EXPECT_FALSE(Exiv2::Image::isPrintICC(0x8773, Exiv2::kpsRecursive));
    EXPECT_FALSE(Exiv2::Image::isPrintICC(0x8773, Exiv2::kpsIptcErase));
}

TEST_F(ImageTest_1056, IsPrintICC_WrongTypeCorrectOption_ReturnsFalse_1056) {
    EXPECT_FALSE(Exiv2::Image::isPrintICC(0x0000, Exiv2::kpsIccProfile));
    EXPECT_FALSE(Exiv2::Image::isPrintICC(0x8772, Exiv2::kpsIccProfile));
    EXPECT_FALSE(Exiv2::Image::isPrintICC(0x8774, Exiv2::kpsIccProfile));
    EXPECT_FALSE(Exiv2::Image::isPrintICC(0xFFFF, Exiv2::kpsIccProfile));
    EXPECT_FALSE(Exiv2::Image::isPrintICC(0x0001, Exiv2::kpsIccProfile));
}

TEST_F(ImageTest_1056, IsPrintICC_WrongTypeWrongOption_ReturnsFalse_1056) {
    EXPECT_FALSE(Exiv2::Image::isPrintICC(0x0000, Exiv2::kpsNone));
    EXPECT_FALSE(Exiv2::Image::isPrintICC(0xFFFF, Exiv2::kpsBasic));
    EXPECT_FALSE(Exiv2::Image::isPrintICC(0x1234, Exiv2::kpsXMP));
}

// ==================== isPrintXMP Tests ====================

TEST_F(ImageTest_1056, IsPrintXMP_CorrectTypeAndOption_ReturnsTrue_1056) {
    // type 700 (0x02BC) is XMP tag
    EXPECT_TRUE(Exiv2::Image::isPrintXMP(700, Exiv2::kpsXMP));
}

TEST_F(ImageTest_1056, IsPrintXMP_WrongType_ReturnsFalse_1056) {
    EXPECT_FALSE(Exiv2::Image::isPrintXMP(0, Exiv2::kpsXMP));
    EXPECT_FALSE(Exiv2::Image::isPrintXMP(701, Exiv2::kpsXMP));
}

TEST_F(ImageTest_1056, IsPrintXMP_WrongOption_ReturnsFalse_1056) {
    EXPECT_FALSE(Exiv2::Image::isPrintXMP(700, Exiv2::kpsNone));
    EXPECT_FALSE(Exiv2::Image::isPrintXMP(700, Exiv2::kpsIccProfile));
}

// ==================== isStringType Tests ====================

TEST_F(ImageTest_1056, IsStringType_AsciiType_ReturnsTrue_1056) {
    // TIFF type 2 = ASCII
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
}

TEST_F(ImageTest_1056, IsStringType_NonStringType_ReturnsFalse_1056) {
    EXPECT_FALSE(Exiv2::Image::isStringType(0));
    EXPECT_FALSE(Exiv2::Image::isStringType(1)); // BYTE
    EXPECT_FALSE(Exiv2::Image::isStringType(3)); // SHORT
    EXPECT_FALSE(Exiv2::Image::isStringType(4)); // LONG
}

// ==================== isShortType Tests ====================

TEST_F(ImageTest_1056, IsShortType_ShortType_ReturnsTrue_1056) {
    // TIFF type 3 = SHORT, type 8 = SSHORT
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
    EXPECT_TRUE(Exiv2::Image::isShortType(8));
}

TEST_F(ImageTest_1056, IsShortType_NonShortType_ReturnsFalse_1056) {
    EXPECT_FALSE(Exiv2::Image::isShortType(0));
    EXPECT_FALSE(Exiv2::Image::isShortType(1));
    EXPECT_FALSE(Exiv2::Image::isShortType(2));
    EXPECT_FALSE(Exiv2::Image::isShortType(4));
}

// ==================== isLongType Tests ====================

TEST_F(ImageTest_1056, IsLongType_LongType_ReturnsTrue_1056) {
    // TIFF type 4 = LONG, type 9 = SLONG
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
    EXPECT_TRUE(Exiv2::Image::isLongType(9));
}

TEST_F(ImageTest_1056, IsLongType_NonLongType_ReturnsFalse_1056) {
    EXPECT_FALSE(Exiv2::Image::isLongType(0));
    EXPECT_FALSE(Exiv2::Image::isLongType(3));
    EXPECT_FALSE(Exiv2::Image::isLongType(5));
}

// ==================== isLongLongType Tests ====================

TEST_F(ImageTest_1056, IsLongLongType_LongLongType_ReturnsTrue_1056) {
    // TIFF type 16 = LONG8, type 17 = SLONG8
    EXPECT_TRUE(Exiv2::Image::isLongLongType(16));
    EXPECT_TRUE(Exiv2::Image::isLongLongType(17));
}

TEST_F(ImageTest_1056, IsLongLongType_NonLongLongType_ReturnsFalse_1056) {
    EXPECT_FALSE(Exiv2::Image::isLongLongType(0));
    EXPECT_FALSE(Exiv2::Image::isLongLongType(4));
    EXPECT_FALSE(Exiv2::Image::isLongLongType(15));
}

// ==================== isRationalType Tests ====================

TEST_F(ImageTest_1056, IsRationalType_RationalType_ReturnsTrue_1056) {
    // TIFF type 5 = RATIONAL, type 10 = SRATIONAL
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
    EXPECT_TRUE(Exiv2::Image::isRationalType(10));
}

TEST_F(ImageTest_1056, IsRationalType_NonRationalType_ReturnsFalse_1056) {
    EXPECT_FALSE(Exiv2::Image::isRationalType(0));
    EXPECT_FALSE(Exiv2::Image::isRationalType(4));
    EXPECT_FALSE(Exiv2::Image::isRationalType(6));
}

// ==================== is2ByteType Tests ====================

TEST_F(ImageTest_1056, Is2ByteType_ShortTypes_ReturnsTrue_1056) {
    // SHORT (3) and SSHORT (8) are 2-byte types
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
    EXPECT_TRUE(Exiv2::Image::is2ByteType(8));
}

TEST_F(ImageTest_1056, Is2ByteType_NonTwoByte_ReturnsFalse_1056) {
    EXPECT_FALSE(Exiv2::Image::is2ByteType(0));
    EXPECT_FALSE(Exiv2::Image::is2ByteType(1));
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

// ==================== is4ByteType Tests ====================

TEST_F(ImageTest_1056, Is4ByteType_LongTypes_ReturnsTrue_1056) {
    // LONG (4) and SLONG (9) are 4-byte types
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
    EXPECT_TRUE(Exiv2::Image::is4ByteType(9));
}

TEST_F(ImageTest_1056, Is4ByteType_NonFourByte_ReturnsFalse_1056) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(0));
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
    EXPECT_FALSE(Exiv2::Image::is4ByteType(5));
}

// ==================== is8ByteType Tests ====================

TEST_F(ImageTest_1056, Is8ByteType_RationalAndLongLong_ReturnsTrue_1056) {
    // RATIONAL (5), SRATIONAL (10), LONG8 (16), SLONG8 (17) are 8-byte types
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
    EXPECT_TRUE(Exiv2::Image::is8ByteType(10));
    EXPECT_TRUE(Exiv2::Image::is8ByteType(16));
    EXPECT_TRUE(Exiv2::Image::is8ByteType(17));
}

TEST_F(ImageTest_1056, Is8ByteType_NonEightByte_ReturnsFalse_1056) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(0));
    EXPECT_FALSE(Exiv2::Image::is8ByteType(3));
    EXPECT_FALSE(Exiv2::Image::is8ByteType(4));
}

// ==================== Platform Endian Tests ====================

TEST_F(ImageTest_1056, EndianPlatform_MutuallyExclusive_1056) {
    bool isBig = Exiv2::Image::isBigEndianPlatform();
    bool isLittle = Exiv2::Image::isLittleEndianPlatform();
    // Platform must be one or the other
    EXPECT_TRUE(isBig != isLittle);
}

TEST_F(ImageTest_1056, IsBigEndianPlatform_ConsistentResult_1056) {
    bool first = Exiv2::Image::isBigEndianPlatform();
    bool second = Exiv2::Image::isBigEndianPlatform();
    EXPECT_EQ(first, second);
}

TEST_F(ImageTest_1056, IsLittleEndianPlatform_ConsistentResult_1056) {
    bool first = Exiv2::Image::isLittleEndianPlatform();
    bool second = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_EQ(first, second);
}

// ==================== byteSwap Tests ====================

TEST_F(ImageTest_1056, ByteSwap16_NoSwap_ReturnsSameValue_1056) {
    uint16_t val = 0x1234;
    EXPECT_EQ(val, Exiv2::Image::byteSwap(val, false));
}

TEST_F(ImageTest_1056, ByteSwap16_Swap_ReturnsSwappedValue_1056) {
    uint16_t val = 0x1234;
    uint16_t expected = 0x3412;
    EXPECT_EQ(expected, Exiv2::Image::byteSwap(val, true));
}

TEST_F(ImageTest_1056, ByteSwap16_Zero_1056) {
    EXPECT_EQ(static_cast<uint16_t>(0), Exiv2::Image::byteSwap(static_cast<uint16_t>(0), true));
    EXPECT_EQ(static_cast<uint16_t>(0), Exiv2::Image::byteSwap(static_cast<uint16_t>(0), false));
}

TEST_F(ImageTest_1056, ByteSwap16_DoubleSwap_ReturnsOriginal_1056) {
    uint16_t val = 0xABCD;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    uint16_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(val, doubleSwapped);
}

TEST_F(ImageTest_1056, ByteSwap32_NoSwap_ReturnsSameValue_1056) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(val, Exiv2::Image::byteSwap(val, false));
}

TEST_F(ImageTest_1056, ByteSwap32_Swap_ReturnsSwappedValue_1056) {
    uint32_t val = 0x12345678;
    uint32_t expected = 0x78563412;
    EXPECT_EQ(expected, Exiv2::Image::byteSwap(val, true));
}

TEST_F(ImageTest_1056, ByteSwap32_DoubleSwap_ReturnsOriginal_1056) {
    uint32_t val = 0xDEADBEEF;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    uint32_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(val, doubleSwapped);
}

TEST_F(ImageTest_1056, ByteSwap64_NoSwap_ReturnsSameValue_1056) {
    uint64_t val = 0x123456789ABCDEF0ULL;
    EXPECT_EQ(val, Exiv2::Image::byteSwap(val, false));
}

TEST_F(ImageTest_1056, ByteSwap64_Swap_ReturnsSwappedValue_1056) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t expected = 0x0807060504030201ULL;
    EXPECT_EQ(expected, Exiv2::Image::byteSwap(val, true));
}

TEST_F(ImageTest_1056, ByteSwap64_DoubleSwap_ReturnsOriginal_1056) {
    uint64_t val = 0xDEADBEEFCAFEBABEULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    uint64_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(val, doubleSwapped);
}

// ==================== byteSwap2/4/8 with DataBuf Tests ====================

TEST_F(ImageTest_1056, ByteSwap2_FromDataBuf_NoSwap_1056) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    uint16_t result = Exiv2::Image::byteSwap2(buf, 0, false);
    // Without swap, it should read as-is (native byte order representation)
    uint16_t expected;
    std::memcpy(&expected, buf.c_data(), 2);
    EXPECT_EQ(expected, result);
}

TEST_F(ImageTest_1056, ByteSwap2_FromDataBuf_Swap_1056) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
    EXPECT_EQ(Exiv2::Image::byteSwap(noSwap, true), swapped);
}

TEST_F(ImageTest_1056, ByteSwap4_FromDataBuf_NoSwap_1056) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    buf.data()[2] = 0x56;
    buf.data()[3] = 0x78;
    uint32_t result = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t expected;
    std::memcpy(&expected, buf.c_data(), 4);
    EXPECT_EQ(expected, result);
}

TEST_F(ImageTest_1056, ByteSwap8_FromDataBuf_NoSwap_1056) {
    Exiv2::DataBuf buf(16);
    for (int i = 0; i < 8; i++) {
        buf.data()[i] = static_cast<uint8_t>(i + 1);
    }
    uint64_t result = Exiv2::Image::byteSwap8(buf, 0, false);
    uint64_t expected;
    std::memcpy(&expected, buf.c_data(), 8);
    EXPECT_EQ(expected, result);
}

// ==================== Image instance tests using MemIo ====================

class ImageInstanceTest_1056 : public ::testing::Test {
protected:
    // We'll use a concrete subclass through ImageFactory or just test statics
    // Since Image is abstract, we test the static methods primarily
};

// Test that byteSwap with boundary values works
TEST_F(ImageTest_1056, ByteSwap16_MaxValue_1056) {
    uint16_t val = 0xFFFF;
    EXPECT_EQ(val, Exiv2::Image::byteSwap(val, true));
    EXPECT_EQ(val, Exiv2::Image::byteSwap(val, false));
}

TEST_F(ImageTest_1056, ByteSwap32_MaxValue_1056) {
    uint32_t val = 0xFFFFFFFF;
    EXPECT_EQ(val, Exiv2::Image::byteSwap(val, true));
    EXPECT_EQ(val, Exiv2::Image::byteSwap(val, false));
}

TEST_F(ImageTest_1056, ByteSwap64_MaxValue_1056) {
    uint64_t val = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_EQ(val, Exiv2::Image::byteSwap(val, true));
    EXPECT_EQ(val, Exiv2::Image::byteSwap(val, false));
}

TEST_F(ImageTest_1056, ByteSwap16_SingleByte_1056) {
    uint16_t val = 0x00FF;
    uint16_t expected = 0xFF00;
    EXPECT_EQ(expected, Exiv2::Image::byteSwap(val, true));
}

TEST_F(ImageTest_1056, ByteSwap32_Zero_1056) {
    uint32_t val = 0;
    EXPECT_EQ(static_cast<uint32_t>(0), Exiv2::Image::byteSwap(val, true));
}

TEST_F(ImageTest_1056, ByteSwap64_Zero_1056) {
    uint64_t val = 0;
    EXPECT_EQ(static_cast<uint64_t>(0), Exiv2::Image::byteSwap(val, true));
}

// ==================== Type classification boundary tests ====================

TEST_F(ImageTest_1056, IsStringType_BoundaryValues_1056) {
    EXPECT_FALSE(Exiv2::Image::isStringType(0));
    EXPECT_FALSE(Exiv2::Image::isStringType(0xFFFF));
}

TEST_F(ImageTest_1056, IsShortType_BoundaryValues_1056) {
    EXPECT_FALSE(Exiv2::Image::isShortType(2));
    EXPECT_FALSE(Exiv2::Image::isShortType(4));
    EXPECT_FALSE(Exiv2::Image::isShortType(7));
    EXPECT_FALSE(Exiv2::Image::isShortType(9));
}

TEST_F(ImageTest_1056, IsLongType_BoundaryValues_1056) {
    EXPECT_FALSE(Exiv2::Image::isLongType(3));
    EXPECT_FALSE(Exiv2::Image::isLongType(5));
    EXPECT_FALSE(Exiv2::Image::isLongType(8));
    EXPECT_FALSE(Exiv2::Image::isLongType(10));
}

TEST_F(ImageTest_1056, IsRationalType_BoundaryValues_1056) {
    EXPECT_FALSE(Exiv2::Image::isRationalType(4));
    EXPECT_FALSE(Exiv2::Image::isRationalType(6));
    EXPECT_FALSE(Exiv2::Image::isRationalType(9));
    EXPECT_FALSE(Exiv2::Image::isRationalType(11));
}

// ==================== Consistency tests: type checks vs byte size checks ====================

TEST_F(ImageTest_1056, ShortTypeIs2Byte_1056) {
    // All short types should be 2-byte types
    for (uint16_t t = 0; t < 20; t++) {
        if (Exiv2::Image::isShortType(t)) {
            EXPECT_TRUE(Exiv2::Image::is2ByteType(t)) << "Type " << t << " is short but not 2-byte";
        }
    }
}

TEST_F(ImageTest_1056, LongTypeIs4Byte_1056) {
    for (uint16_t t = 0; t < 20; t++) {
        if (Exiv2::Image::isLongType(t)) {
            EXPECT_TRUE(Exiv2::Image::is4ByteType(t)) << "Type " << t << " is long but not 4-byte";
        }
    }
}

TEST_F(ImageTest_1056, RationalTypeIs8Byte_1056) {
    for (uint16_t t = 0; t < 20; t++) {
        if (Exiv2::Image::isRationalType(t)) {
            EXPECT_TRUE(Exiv2::Image::is8ByteType(t)) << "Type " << t << " is rational but not 8-byte";
        }
    }
}

TEST_F(ImageTest_1056, LongLongTypeIs8Byte_1056) {
    for (uint16_t t = 0; t < 20; t++) {
        if (Exiv2::Image::isLongLongType(t)) {
            EXPECT_TRUE(Exiv2::Image::is8ByteType(t)) << "Type " << t << " is longlong but not 8-byte";
        }
    }
}

// ==================== ByteSwap with offset in DataBuf ====================

TEST_F(ImageTest_1056, ByteSwap2_WithOffset_1056) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x00;
    buf.data()[1] = 0x00;
    buf.data()[2] = 0xAB;
    buf.data()[3] = 0xCD;
    uint16_t result = Exiv2::Image::byteSwap2(buf, 2, false);
    uint16_t expected;
    std::memcpy(&expected, buf.c_data() + 2, 2);
    EXPECT_EQ(expected, result);
}

TEST_F(ImageTest_1056, ByteSwap4_WithOffset_1056) {
    Exiv2::DataBuf buf(12);
    buf.data()[4] = 0xDE;
    buf.data()[5] = 0xAD;
    buf.data()[6] = 0xBE;
    buf.data()[7] = 0xEF;
    uint32_t result = Exiv2::Image::byteSwap4(buf, 4, false);
    uint32_t expected;
    std::memcpy(&expected, buf.c_data() + 4, 4);
    EXPECT_EQ(expected, result);
}

TEST_F(ImageTest_1056, ByteSwap8_WithOffset_1056) {
    Exiv2::DataBuf buf(24);
    for (int i = 0; i < 8; i++) {
        buf.data()[8 + i] = static_cast<uint8_t>(0x10 + i);
    }
    uint64_t result = Exiv2::Image::byteSwap8(buf, 8, false);
    uint64_t expected;
    std::memcpy(&expected, buf.c_data() + 8, 8);
    EXPECT_EQ(expected, result);
}
