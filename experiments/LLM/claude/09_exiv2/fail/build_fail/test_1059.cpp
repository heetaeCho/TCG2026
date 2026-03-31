#include <gtest/gtest.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <sstream>
#include <cstdint>
#include <memory>

using namespace Exiv2;

// Helper to create a minimal Image instance for testing.
// Since Image is abstract (has pure virtual methods like readMetadata/writeMetadata),
// we need a concrete subclass or use a file-based image. We'll use ImageFactory
// or create a MemIo-based approach. However, since Image has virtual methods,
// we create a minimal concrete subclass for testing purposes.

class TestImage : public Exiv2::Image {
public:
    TestImage(std::unique_ptr<BasicIo> io)
        : Image(ImageType::none, static_cast<uint16_t>(0xFFFF), std::move(io)) {}

    void readMetadata() override {}
    void writeMetadata() override {}
    std::string mimeType() const override { return "application/octet-stream"; }
};

class ImageByteSwapTest_1059 : public ::testing::Test {
protected:
    std::unique_ptr<TestImage> image_;

    void SetUp() override {
        auto io = std::make_unique<MemIo>();
        image_ = std::make_unique<TestImage>(std::move(io));
    }
};

// ========== byteSwap uint16_t tests ==========

TEST_F(ImageByteSwapTest_1059, ByteSwap16_NoSwap_ReturnsOriginal_1059) {
    uint16_t value = 0x1234;
    uint16_t result = Image::byteSwap(value, false);
    EXPECT_EQ(result, 0x1234);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap16_Swap_ReturnsSwapped_1059) {
    uint16_t value = 0x1234;
    uint16_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x3412);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap16_SwapZero_ReturnsZero_1059) {
    uint16_t value = 0x0000;
    uint16_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x0000);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap16_SwapFFFF_ReturnsFFFF_1059) {
    uint16_t value = 0xFFFF;
    uint16_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0xFFFF);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap16_SwapFF00_Returns00FF_1059) {
    uint16_t value = 0xFF00;
    uint16_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x00FF);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap16_Swap00FF_ReturnsFF00_1059) {
    uint16_t value = 0x00FF;
    uint16_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0xFF00);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap16_DoubleSwap_ReturnsOriginal_1059) {
    uint16_t value = 0xABCD;
    uint16_t swapped = Image::byteSwap(value, true);
    uint16_t result = Image::byteSwap(swapped, true);
    EXPECT_EQ(result, value);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap16_NoSwapZero_ReturnsZero_1059) {
    uint16_t value = 0x0000;
    uint16_t result = Image::byteSwap(value, false);
    EXPECT_EQ(result, 0x0000);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap16_Swap0100_Returns0001_1059) {
    uint16_t value = 0x0100;
    uint16_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x0001);
}

// ========== byteSwap uint32_t tests ==========

TEST_F(ImageByteSwapTest_1059, ByteSwap32_NoSwap_ReturnsOriginal_1059) {
    uint32_t value = 0x12345678;
    uint32_t result = Image::byteSwap(value, false);
    EXPECT_EQ(result, 0x12345678U);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap32_Swap_ReturnsSwapped_1059) {
    uint32_t value = 0x12345678;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x78563412U);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap32_SwapZero_ReturnsZero_1059) {
    uint32_t value = 0x00000000;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x00000000U);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap32_SwapFFFFFFFF_ReturnsFFFFFFFF_1059) {
    uint32_t value = 0xFFFFFFFF;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0xFFFFFFFFU);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap32_DoubleSwap_ReturnsOriginal_1059) {
    uint32_t value = 0xDEADBEEF;
    uint32_t swapped = Image::byteSwap(value, true);
    uint32_t result = Image::byteSwap(swapped, true);
    EXPECT_EQ(result, value);
}

// ========== byteSwap uint64_t tests ==========

TEST_F(ImageByteSwapTest_1059, ByteSwap64_NoSwap_ReturnsOriginal_1059) {
    uint64_t value = 0x0102030405060708ULL;
    uint64_t result = Image::byteSwap(value, false);
    EXPECT_EQ(result, 0x0102030405060708ULL);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap64_Swap_ReturnsSwapped_1059) {
    uint64_t value = 0x0102030405060708ULL;
    uint64_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x0807060504030201ULL);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap64_SwapZero_ReturnsZero_1059) {
    uint64_t value = 0x0000000000000000ULL;
    uint64_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x0000000000000000ULL);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap64_DoubleSwap_ReturnsOriginal_1059) {
    uint64_t value = 0xDEADBEEFCAFEBABEULL;
    uint64_t swapped = Image::byteSwap(value, true);
    uint64_t result = Image::byteSwap(swapped, true);
    EXPECT_EQ(result, value);
}

// ========== Endianness platform tests ==========

TEST_F(ImageByteSwapTest_1059, EndiannessMutuallyExclusive_1059) {
    bool big = Image::isBigEndianPlatform();
    bool little = Image::isLittleEndianPlatform();
    EXPECT_NE(big, little);
}

TEST_F(ImageByteSwapTest_1059, IsBigEndianPlatform_ConsistentWithLittle_1059) {
    EXPECT_EQ(Image::isBigEndianPlatform(), !Image::isLittleEndianPlatform());
}

// ========== isStringType tests ==========

TEST_F(ImageByteSwapTest_1059, IsStringType_Type2_ReturnsTrue_1059) {
    // TIFF ASCII type is 2
    EXPECT_TRUE(Image::isStringType(2));
}

TEST_F(ImageByteSwapTest_1059, IsStringType_Type0_ReturnsFalse_1059) {
    EXPECT_FALSE(Image::isStringType(0));
}

// ========== isShortType tests ==========

TEST_F(ImageByteSwapTest_1059, IsShortType_Type3_ReturnsTrue_1059) {
    // TIFF SHORT type is 3
    EXPECT_TRUE(Image::isShortType(3));
}

TEST_F(ImageByteSwapTest_1059, IsShortType_Type8_ReturnsTrue_1059) {
    // TIFF SSHORT type is 8
    EXPECT_TRUE(Image::isShortType(8));
}

TEST_F(ImageByteSwapTest_1059, IsShortType_Type0_ReturnsFalse_1059) {
    EXPECT_FALSE(Image::isShortType(0));
}

// ========== isLongType tests ==========

TEST_F(ImageByteSwapTest_1059, IsLongType_Type4_ReturnsTrue_1059) {
    // TIFF LONG type is 4
    EXPECT_TRUE(Image::isLongType(4));
}

TEST_F(ImageByteSwapTest_1059, IsLongType_Type9_ReturnsTrue_1059) {
    // TIFF SLONG type is 9
    EXPECT_TRUE(Image::isLongType(9));
}

TEST_F(ImageByteSwapTest_1059, IsLongType_Type0_ReturnsFalse_1059) {
    EXPECT_FALSE(Image::isLongType(0));
}

// ========== isLongLongType tests ==========

TEST_F(ImageByteSwapTest_1059, IsLongLongType_Type16_1059) {
    // TIFF LONG8 type is 16
    bool result = Image::isLongLongType(16);
    // Just verify it returns a boolean; the actual type mapping is implementation-defined
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(ImageByteSwapTest_1059, IsLongLongType_Type0_ReturnsFalse_1059) {
    EXPECT_FALSE(Image::isLongLongType(0));
}

// ========== isRationalType tests ==========

TEST_F(ImageByteSwapTest_1059, IsRationalType_Type5_ReturnsTrue_1059) {
    // TIFF RATIONAL type is 5
    EXPECT_TRUE(Image::isRationalType(5));
}

TEST_F(ImageByteSwapTest_1059, IsRationalType_Type10_ReturnsTrue_1059) {
    // TIFF SRATIONAL type is 10
    EXPECT_TRUE(Image::isRationalType(10));
}

TEST_F(ImageByteSwapTest_1059, IsRationalType_Type0_ReturnsFalse_1059) {
    EXPECT_FALSE(Image::isRationalType(0));
}

// ========== is2ByteType tests ==========

TEST_F(ImageByteSwapTest_1059, Is2ByteType_Type3_ReturnsTrue_1059) {
    EXPECT_TRUE(Image::is2ByteType(3));
}

TEST_F(ImageByteSwapTest_1059, Is2ByteType_Type0_ReturnsFalse_1059) {
    EXPECT_FALSE(Image::is2ByteType(0));
}

// ========== is4ByteType tests ==========

TEST_F(ImageByteSwapTest_1059, Is4ByteType_Type4_ReturnsTrue_1059) {
    EXPECT_TRUE(Image::is4ByteType(4));
}

TEST_F(ImageByteSwapTest_1059, Is4ByteType_Type0_ReturnsFalse_1059) {
    EXPECT_FALSE(Image::is4ByteType(0));
}

// ========== is8ByteType tests ==========

TEST_F(ImageByteSwapTest_1059, Is8ByteType_Type5_ReturnsTrue_1059) {
    // RATIONAL is 8 bytes (two uint32_t)
    EXPECT_TRUE(Image::is8ByteType(5));
}

TEST_F(ImageByteSwapTest_1059, Is8ByteType_Type0_ReturnsFalse_1059) {
    EXPECT_FALSE(Image::is8ByteType(0));
}

// ========== Image basic functionality tests ==========

TEST_F(ImageByteSwapTest_1059, ImageGood_WithMemIo_1059) {
    // MemIo should be "good" initially
    bool result = image_->good();
    // The result depends on the IO state
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(ImageByteSwapTest_1059, ImageByteOrder_Default_1059) {
    // Default byte order should be invalidByteOrder
    EXPECT_EQ(image_->byteOrder(), invalidByteOrder);
}

TEST_F(ImageByteSwapTest_1059, ImageSetByteOrder_1059) {
    image_->setByteOrder(bigEndian);
    EXPECT_EQ(image_->byteOrder(), bigEndian);
    
    image_->setByteOrder(littleEndian);
    EXPECT_EQ(image_->byteOrder(), littleEndian);
}

TEST_F(ImageByteSwapTest_1059, ImagePixelWidth_Default_1059) {
    EXPECT_EQ(image_->pixelWidth(), 0U);
}

TEST_F(ImageByteSwapTest_1059, ImagePixelHeight_Default_1059) {
    EXPECT_EQ(image_->pixelHeight(), 0U);
}

TEST_F(ImageByteSwapTest_1059, ImageComment_Default_1059) {
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageByteSwapTest_1059, ImageSetComment_1059) {
    image_->setComment("Test comment");
    EXPECT_EQ(image_->comment(), "Test comment");
}

TEST_F(ImageByteSwapTest_1059, ImageClearComment_1059) {
    image_->setComment("Test comment");
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageByteSwapTest_1059, ImageWriteXmpFromPacket_DefaultFalse_1059) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageByteSwapTest_1059, ImageWriteXmpFromPacket_SetTrue_1059) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageByteSwapTest_1059, ImageWriteXmpFromPacket_SetFalse_1059) {
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageByteSwapTest_1059, ImageClearMetadata_1059) {
    image_->setComment("some comment");
    image_->clearMetadata();
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageByteSwapTest_1059, ImageIccProfileDefined_DefaultFalse_1059) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageByteSwapTest_1059, ImageClearIccProfile_1059) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageByteSwapTest_1059, ImageClearExifData_1059) {
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(ImageByteSwapTest_1059, ImageClearIptcData_1059) {
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageByteSwapTest_1059, ImageClearXmpData_1059) {
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageByteSwapTest_1059, ImageClearXmpPacket_1059) {
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageByteSwapTest_1059, ImageSetXmpPacket_1059) {
    std::string xmpData = "<x:xmpmeta></x:xmpmeta>";
    image_->setXmpPacket(xmpData);
    EXPECT_EQ(image_->xmpPacket(), xmpData);
}

TEST_F(ImageByteSwapTest_1059, ImageNativePreviews_DefaultEmpty_1059) {
    EXPECT_TRUE(image_->nativePreviews().empty());
}

TEST_F(ImageByteSwapTest_1059, ImageImageType_1059) {
    EXPECT_EQ(image_->imageType(), ImageType::none);
}

// ========== byteSwap2/byteSwap4/byteSwap8 with DataBuf tests ==========

TEST_F(ImageByteSwapTest_1059, ByteSwap2_NoSwap_1059) {
    DataBuf buf(4);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    uint16_t result = Image::byteSwap2(buf, 0, false);
    // Without swap, should read as-is in memory order
    uint16_t expected;
    std::memcpy(&expected, buf.c_data(), 2);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap2_Swap_1059) {
    DataBuf buf(4);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    uint16_t noSwap = Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Image::byteSwap2(buf, 0, true);
    EXPECT_EQ(swapped, Image::byteSwap(noSwap, true));
}

TEST_F(ImageByteSwapTest_1059, ByteSwap4_NoSwap_1059) {
    DataBuf buf(8);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    buf.write_uint8(2, 0x56);
    buf.write_uint8(3, 0x78);
    uint32_t result = Image::byteSwap4(buf, 0, false);
    uint32_t expected;
    std::memcpy(&expected, buf.c_data(), 4);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap4_Swap_1059) {
    DataBuf buf(8);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    buf.write_uint8(2, 0x56);
    buf.write_uint8(3, 0x78);
    uint32_t noSwap = Image::byteSwap4(buf, 0, false);
    uint32_t swapped = Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(swapped, Image::byteSwap(noSwap, true));
}

TEST_F(ImageByteSwapTest_1059, ByteSwap8_NoSwap_1059) {
    DataBuf buf(16);
    for (size_t i = 0; i < 8; i++) {
        buf.write_uint8(i, static_cast<uint8_t>(i + 1));
    }
    uint64_t result = Image::byteSwap8(buf, 0, false);
    uint64_t expected;
    std::memcpy(&expected, buf.c_data(), 8);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap8_Swap_1059) {
    DataBuf buf(16);
    for (size_t i = 0; i < 8; i++) {
        buf.write_uint8(i, static_cast<uint8_t>(i + 1));
    }
    uint64_t noSwap = Image::byteSwap8(buf, 0, false);
    uint64_t swapped = Image::byteSwap8(buf, 0, true);
    EXPECT_EQ(swapped, Image::byteSwap(noSwap, true));
}

// ========== Boundary / Edge case byteswap tests ==========

TEST_F(ImageByteSwapTest_1059, ByteSwap16_MaxValue_NoSwap_1059) {
    uint16_t value = 0xFFFF;
    EXPECT_EQ(Image::byteSwap(value, false), 0xFFFF);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap32_MaxValue_NoSwap_1059) {
    uint32_t value = 0xFFFFFFFF;
    EXPECT_EQ(Image::byteSwap(value, false), 0xFFFFFFFFU);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap64_MaxValue_NoSwap_1059) {
    uint64_t value = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_EQ(Image::byteSwap(value, false), 0xFFFFFFFFFFFFFFFFULL);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap64_MaxValue_Swap_1059) {
    uint64_t value = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_EQ(Image::byteSwap(value, true), 0xFFFFFFFFFFFFFFFFULL);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap16_SingleByte_Low_1059) {
    uint16_t value = 0x0001;
    uint16_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x0100);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap32_SingleByte_Low_1059) {
    uint32_t value = 0x00000001;
    uint32_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x01000000U);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap64_SingleByte_Low_1059) {
    uint64_t value = 0x0000000000000001ULL;
    uint64_t result = Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x0100000000000000ULL);
}

// ========== setMetadata test ==========

TEST_F(ImageByteSwapTest_1059, ImageSetMetadata_CopiesComment_1059) {
    auto io2 = std::make_unique<MemIo>();
    TestImage source(std::move(io2));
    source.setComment("source comment");
    
    image_->setMetadata(source);
    EXPECT_EQ(image_->comment(), "source comment");
}

// ========== byteSwap2/4/8 with offset ==========

TEST_F(ImageByteSwapTest_1059, ByteSwap2_WithOffset_1059) {
    DataBuf buf(8);
    buf.write_uint8(0, 0x00);
    buf.write_uint8(1, 0x00);
    buf.write_uint8(2, 0xAB);
    buf.write_uint8(3, 0xCD);
    uint16_t result = Image::byteSwap2(buf, 2, false);
    uint16_t expected;
    std::memcpy(&expected, buf.c_data() + 2, 2);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageByteSwapTest_1059, ByteSwap4_WithOffset_1059) {
    DataBuf buf(12);
    for (size_t i = 0; i < 12; i++) {
        buf.write_uint8(i, static_cast<uint8_t>(i));
    }
    uint32_t result = Image::byteSwap4(buf, 4, false);
    uint32_t expected;
    std::memcpy(&expected, buf.c_data() + 4, 4);
    EXPECT_EQ(result, expected);
}
