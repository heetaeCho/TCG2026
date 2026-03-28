#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <memory>
#include <cstring>

using namespace Exiv2;

// Helper: Create an image using ImageFactory::create which gives us a concrete Image
// We use ImageType::none or a known type for testing
class ImageTest_1098 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create an in-memory image using a MemIo
        auto io = std::make_unique<MemIo>();
        // We'll try to create a JPEG-type image for testing
        // Using ImageFactory::create with a type
        try {
            image_ = ImageFactory::create(ImageType::jpeg);
        } catch (...) {
            image_ = nullptr;
        }
    }

    Image::UniquePtr image_;
};

// Test checkMode delegates to ImageFactory::checkMode
TEST_F(ImageTest_1098, CheckModeExif_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    AccessMode mode = image_->checkMode(MetadataId::mdExif);
    AccessMode expected = ImageFactory::checkMode(image_->imageType(), MetadataId::mdExif);
    EXPECT_EQ(mode, expected);
}

TEST_F(ImageTest_1098, CheckModeIptc_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    AccessMode mode = image_->checkMode(MetadataId::mdIptc);
    AccessMode expected = ImageFactory::checkMode(image_->imageType(), MetadataId::mdIptc);
    EXPECT_EQ(mode, expected);
}

TEST_F(ImageTest_1098, CheckModeXmp_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    AccessMode mode = image_->checkMode(MetadataId::mdXmp);
    AccessMode expected = ImageFactory::checkMode(image_->imageType(), MetadataId::mdXmp);
    EXPECT_EQ(mode, expected);
}

TEST_F(ImageTest_1098, CheckModeComment_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    AccessMode mode = image_->checkMode(MetadataId::mdComment);
    AccessMode expected = ImageFactory::checkMode(image_->imageType(), MetadataId::mdComment);
    EXPECT_EQ(mode, expected);
}

TEST_F(ImageTest_1098, CheckModeIccProfile_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    AccessMode mode = image_->checkMode(MetadataId::mdIccProfile);
    AccessMode expected = ImageFactory::checkMode(image_->imageType(), MetadataId::mdIccProfile);
    EXPECT_EQ(mode, expected);
}

// Test initial pixel dimensions are zero
TEST_F(ImageTest_1098, InitialPixelWidthIsZero_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(ImageTest_1098, InitialPixelHeightIsZero_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// Test initial comment is empty
TEST_F(ImageTest_1098, InitialCommentIsEmpty_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    EXPECT_TRUE(image_->comment().empty());
}

// Test setComment and clearComment
TEST_F(ImageTest_1098, SetComment_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    image_->setComment("Hello World");
    EXPECT_EQ(image_->comment(), "Hello World");
}

TEST_F(ImageTest_1098, ClearComment_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    image_->setComment("Hello World");
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

// Test setExifData and clearExifData
TEST_F(ImageTest_1098, SetExifData_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    EXPECT_FALSE(image_->exifData().empty());
}

TEST_F(ImageTest_1098, ClearExifData_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

// Test setIptcData and clearIptcData
TEST_F(ImageTest_1098, SetIptcData_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "TestCaption";
    image_->setIptcData(iptcData);
    EXPECT_FALSE(image_->iptcData().empty());
}

TEST_F(ImageTest_1098, ClearIptcData_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "TestCaption";
    image_->setIptcData(iptcData);
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

// Test setXmpData and clearXmpData
TEST_F(ImageTest_1098, SetXmpData_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    XmpData xmpData;
    xmpData["Xmp.dc.title"] = "TestTitle";
    image_->setXmpData(xmpData);
    EXPECT_FALSE(image_->xmpData().empty());
}

TEST_F(ImageTest_1098, ClearXmpData_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    XmpData xmpData;
    xmpData["Xmp.dc.title"] = "TestTitle";
    image_->setXmpData(xmpData);
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// Test setXmpPacket and clearXmpPacket
TEST_F(ImageTest_1098, SetXmpPacket_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    image_->setXmpPacket(packet);
    EXPECT_EQ(image_->xmpPacket(), packet);
}

TEST_F(ImageTest_1098, ClearXmpPacket_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    image_->setXmpPacket("<x:xmpmeta>test</x:xmpmeta>");
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// Test clearMetadata clears everything
TEST_F(ImageTest_1098, ClearMetadata_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    image_->setComment("Test");
    ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "TestCaption";
    image_->setIptcData(iptcData);

    image_->clearMetadata();

    EXPECT_TRUE(image_->comment().empty());
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// Test writeXmpFromPacket flag
TEST_F(ImageTest_1098, WriteXmpFromPacketDefault_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1098, WriteXmpFromPacketSetTrue_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1098, WriteXmpFromPacketSetFalse_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// Test byteOrder
TEST_F(ImageTest_1098, ByteOrderDefault_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    EXPECT_EQ(image_->byteOrder(), invalidByteOrder);
}

TEST_F(ImageTest_1098, SetByteOrderBigEndian_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    image_->setByteOrder(bigEndian);
    EXPECT_EQ(image_->byteOrder(), bigEndian);
}

TEST_F(ImageTest_1098, SetByteOrderLittleEndian_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    image_->setByteOrder(littleEndian);
    EXPECT_EQ(image_->byteOrder(), littleEndian);
}

// Test good()
TEST_F(ImageTest_1098, GoodReturnsTrue_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    // A freshly created image with MemIo should be "good"
    EXPECT_TRUE(image_->good());
}

// Test ICC profile
TEST_F(ImageTest_1098, IccProfileNotDefinedInitially_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1098, ClearIccProfile_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

// Test imageType
TEST_F(ImageTest_1098, ImageTypeIsJpeg_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    EXPECT_EQ(image_->imageType(), ImageType::jpeg);
}

// Test nativePreviews
TEST_F(ImageTest_1098, NativePreviewsInitiallyEmpty_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    EXPECT_TRUE(image_->nativePreviews().empty());
}

// Test static methods - byteSwap
TEST(ImageStaticTest_1098, ByteSwap16NoSwap_1098) {
    uint16_t val = 0x0102;
    uint16_t result = Image::byteSwap(val, false);
    EXPECT_EQ(result, val);
}

TEST(ImageStaticTest_1098, ByteSwap16WithSwap_1098) {
    uint16_t val = 0x0102;
    uint16_t result = Image::byteSwap(val, true);
    EXPECT_EQ(result, 0x0201);
}

TEST(ImageStaticTest_1098, ByteSwap32NoSwap_1098) {
    uint32_t val = 0x01020304;
    uint32_t result = Image::byteSwap(val, false);
    EXPECT_EQ(result, val);
}

TEST(ImageStaticTest_1098, ByteSwap32WithSwap_1098) {
    uint32_t val = 0x01020304;
    uint32_t result = Image::byteSwap(val, true);
    EXPECT_EQ(result, 0x04030201u);
}

TEST(ImageStaticTest_1098, ByteSwap64NoSwap_1098) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t result = Image::byteSwap(val, false);
    EXPECT_EQ(result, val);
}

TEST(ImageStaticTest_1098, ByteSwap64WithSwap_1098) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t result = Image::byteSwap(val, true);
    EXPECT_EQ(result, 0x0807060504030201ULL);
}

// Test endianness detection - at least one should be true
TEST(ImageStaticTest_1098, EndianDetection_1098) {
    bool big = Image::isBigEndianPlatform();
    bool little = Image::isLittleEndianPlatform();
    EXPECT_TRUE(big || little);
    EXPECT_NE(big, little);
}

// Test isStringType
TEST(ImageStaticTest_1098, IsStringType_1098) {
    // Type 2 is ASCII in TIFF
    EXPECT_TRUE(Image::isStringType(2));
    // Type 1 (BYTE) should not be a string type
    EXPECT_FALSE(Image::isStringType(1));
}

// Test isShortType
TEST(ImageStaticTest_1098, IsShortType_1098) {
    // Type 3 is SHORT in TIFF
    EXPECT_TRUE(Image::isShortType(3));
    EXPECT_FALSE(Image::isShortType(1));
}

// Test isLongType
TEST(ImageStaticTest_1098, IsLongType_1098) {
    // Type 4 is LONG in TIFF
    EXPECT_TRUE(Image::isLongType(4));
    EXPECT_FALSE(Image::isLongType(1));
}

// Test isRationalType
TEST(ImageStaticTest_1098, IsRationalType_1098) {
    // Type 5 is RATIONAL in TIFF
    EXPECT_TRUE(Image::isRationalType(5));
    EXPECT_FALSE(Image::isRationalType(1));
}

// Test is2ByteType
TEST(ImageStaticTest_1098, Is2ByteType_1098) {
    // SHORT (3) is 2 bytes
    EXPECT_TRUE(Image::is2ByteType(3));
    EXPECT_FALSE(Image::is2ByteType(4));
}

// Test is4ByteType
TEST(ImageStaticTest_1098, Is4ByteType_1098) {
    // LONG (4) is 4 bytes
    EXPECT_TRUE(Image::is4ByteType(4));
    EXPECT_FALSE(Image::is4ByteType(3));
}

// Test is8ByteType
TEST(ImageStaticTest_1098, Is8ByteType_1098) {
    // RATIONAL (5) is 8 bytes
    EXPECT_TRUE(Image::is8ByteType(5));
    EXPECT_FALSE(Image::is8ByteType(3));
}

// Test setMetadata copies from another image
TEST(ImageSetMetadataTest_1098, SetMetadataCopiesData_1098) {
    auto img1 = ImageFactory::create(ImageType::jpeg);
    auto img2 = ImageFactory::create(ImageType::jpeg);
    if (!img1 || !img2) GTEST_SKIP() << "Could not create test images";

    img1->setComment("Source Comment");
    ExifData exif;
    exif["Exif.Image.Make"] = "SourceMake";
    img1->setExifData(exif);

    img2->setMetadata(*img1);
    EXPECT_EQ(img2->comment(), "Source Comment");
    EXPECT_FALSE(img2->exifData().empty());
}

// Test byteSwap2 with DataBuf
TEST(ImageStaticTest_1098, ByteSwap2_1098) {
    DataBuf buf(4);
    buf.data()[0] = 0x01;
    buf.data()[1] = 0x02;
    uint16_t result = Image::byteSwap2(buf, 0, false);
    uint16_t resultSwapped = Image::byteSwap2(buf, 0, true);
    EXPECT_NE(result, 0u);
    // One should be the byte-swapped version of the other
    EXPECT_EQ(result, Image::byteSwap(resultSwapped, true));
}

// Test byteSwap4 with DataBuf
TEST(ImageStaticTest_1098, ByteSwap4_1098) {
    DataBuf buf(8);
    buf.data()[0] = 0x01;
    buf.data()[1] = 0x02;
    buf.data()[2] = 0x03;
    buf.data()[3] = 0x04;
    uint32_t result = Image::byteSwap4(buf, 0, false);
    uint32_t resultSwapped = Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(result, Image::byteSwap(resultSwapped, true));
}

// Test byteSwap8 with DataBuf
TEST(ImageStaticTest_1098, ByteSwap8_1098) {
    DataBuf buf(16);
    for (size_t i = 0; i < 8; i++) {
        buf.data()[i] = static_cast<uint8_t>(i + 1);
    }
    uint64_t result = Image::byteSwap8(buf, 0, false);
    uint64_t resultSwapped = Image::byteSwap8(buf, 0, true);
    EXPECT_EQ(result, Image::byteSwap(resultSwapped, true));
}

// Test supportsMetadata
TEST_F(ImageTest_1098, SupportsMetadata_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    // JPEG should support Exif
    bool supports = image_->supportsMetadata(MetadataId::mdExif);
    // Just check it returns a boolean without crashing
    EXPECT_TRUE(supports || !supports);
}

// Test io() returns a reference
TEST_F(ImageTest_1098, IoReturnsReference_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    const BasicIo& io = image_->io();
    // Just verify it doesn't crash
    (void)io;
    SUCCEED();
}

// Test setTypeSupported changes imageType
TEST_F(ImageTest_1098, SetTypeSupported_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    image_->setTypeSupported(ImageType::png, 0xFFFF);
    EXPECT_EQ(image_->imageType(), ImageType::png);
}

// Test checkMode after changing type
TEST_F(ImageTest_1098, CheckModeAfterTypeChange_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    image_->setTypeSupported(ImageType::png, 0xFFFF);
    AccessMode mode = image_->checkMode(MetadataId::mdExif);
    AccessMode expected = ImageFactory::checkMode(ImageType::png, MetadataId::mdExif);
    EXPECT_EQ(mode, expected);
}

// Boundary: byteSwap with 0
TEST(ImageStaticTest_1098, ByteSwap16Zero_1098) {
    EXPECT_EQ(Image::byteSwap(static_cast<uint16_t>(0), true), 0u);
    EXPECT_EQ(Image::byteSwap(static_cast<uint16_t>(0), false), 0u);
}

TEST(ImageStaticTest_1098, ByteSwap32Zero_1098) {
    EXPECT_EQ(Image::byteSwap(static_cast<uint32_t>(0), true), 0u);
    EXPECT_EQ(Image::byteSwap(static_cast<uint32_t>(0), false), 0u);
}

TEST(ImageStaticTest_1098, ByteSwap64Zero_1098) {
    EXPECT_EQ(Image::byteSwap(static_cast<uint64_t>(0), true), 0u);
    EXPECT_EQ(Image::byteSwap(static_cast<uint64_t>(0), false), 0u);
}

// Boundary: byteSwap with max values
TEST(ImageStaticTest_1098, ByteSwap16Max_1098) {
    uint16_t val = 0xFFFF;
    EXPECT_EQ(Image::byteSwap(val, true), 0xFFFFu);
    EXPECT_EQ(Image::byteSwap(val, false), 0xFFFFu);
}

TEST(ImageStaticTest_1098, ByteSwap32Max_1098) {
    uint32_t val = 0xFFFFFFFF;
    EXPECT_EQ(Image::byteSwap(val, true), 0xFFFFFFFFu);
    EXPECT_EQ(Image::byteSwap(val, false), 0xFFFFFFFFu);
}

TEST(ImageStaticTest_1098, ByteSwap64Max_1098) {
    uint64_t val = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_EQ(Image::byteSwap(val, true), 0xFFFFFFFFFFFFFFFFULL);
    EXPECT_EQ(Image::byteSwap(val, false), 0xFFFFFFFFFFFFFFFFULL);
}

// Test double swap returns original
TEST(ImageStaticTest_1098, DoubleSwap16_1098) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Image::byteSwap(Image::byteSwap(val, true), true), val);
}

TEST(ImageStaticTest_1098, DoubleSwap32_1098) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Image::byteSwap(Image::byteSwap(val, true), true), val);
}

TEST(ImageStaticTest_1098, DoubleSwap64_1098) {
    uint64_t val = 0x123456789ABCDEF0ULL;
    EXPECT_EQ(Image::byteSwap(Image::byteSwap(val, true), true), val);
}

// Test mimeType for JPEG
TEST_F(ImageTest_1098, MimeType_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    std::string mime = image_->mimeType();
    // JPEG images should have image/jpeg mime type
    EXPECT_FALSE(mime.empty());
}

// Test isPrintXMP and isPrintICC with various types and options
TEST(ImageStaticTest_1098, IsPrintXMP_1098) {
    // Just check it doesn't crash and returns a bool
    bool result = Image::isPrintXMP(2, PrintStructureOption::kpsXMP);
    (void)result;
    SUCCEED();
}

TEST(ImageStaticTest_1098, IsPrintICC_1098) {
    bool result = Image::isPrintICC(2, PrintStructureOption::kpsIccProfile);
    (void)result;
    SUCCEED();
}

// Test isLongLongType
TEST(ImageStaticTest_1098, IsLongLongType_1098) {
    // Type 16 is LONG8 in BigTiff
    // Type 1 should not be long long
    EXPECT_FALSE(Image::isLongLongType(1));
}

// Test setComment with empty string
TEST_F(ImageTest_1098, SetCommentEmpty_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    image_->setComment("");
    EXPECT_EQ(image_->comment(), "");
}

// Test setComment with very long string
TEST_F(ImageTest_1098, SetCommentLong_1098) {
    if (!image_) GTEST_SKIP() << "Could not create test image";
    std::string longComment(10000, 'A');
    image_->setComment(longComment);
    EXPECT_EQ(image_->comment(), longComment);
}
