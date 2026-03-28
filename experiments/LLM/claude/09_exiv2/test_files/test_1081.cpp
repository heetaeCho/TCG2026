#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/types.hpp>
#include <memory>
#include <sstream>

// A concrete subclass of Image for testing, since Image has pure virtual methods
class TestImage : public Exiv2::Image {
public:
    TestImage(Exiv2::ImageType type, uint16_t supportedMetadata, std::unique_ptr<Exiv2::BasicIo> io)
        : Exiv2::Image(type, supportedMetadata, std::move(io)) {}

    void readMetadata() override {}
    void writeMetadata() override {}
    std::string mimeType() const override { return "application/octet-stream"; }
};

class ImageTest_1081 : public ::testing::Test {
protected:
    std::unique_ptr<TestImage> createTestImage(uint16_t supportedMetadata = 0xFFFF) {
        auto io = std::make_unique<Exiv2::MemIo>();
        return std::make_unique<TestImage>(Exiv2::ImageType::none, supportedMetadata, std::move(io));
    }
};

// ==================== writeXmpFromPacket tests ====================

TEST_F(ImageTest_1081, WriteXmpFromPacketDefaultIsFalse_1081) {
    auto img = createTestImage();
    EXPECT_FALSE(img->writeXmpFromPacket());
}

TEST_F(ImageTest_1081, WriteXmpFromPacketSetTrue_1081) {
    auto img = createTestImage();
    img->writeXmpFromPacket(true);
    EXPECT_TRUE(img->writeXmpFromPacket());
}

TEST_F(ImageTest_1081, WriteXmpFromPacketSetFalse_1081) {
    auto img = createTestImage();
    img->writeXmpFromPacket(true);
    img->writeXmpFromPacket(false);
    EXPECT_FALSE(img->writeXmpFromPacket());
}

TEST_F(ImageTest_1081, WriteXmpFromPacketToggleMultipleTimes_1081) {
    auto img = createTestImage();
    img->writeXmpFromPacket(true);
    EXPECT_TRUE(img->writeXmpFromPacket());
    img->writeXmpFromPacket(false);
    EXPECT_FALSE(img->writeXmpFromPacket());
    img->writeXmpFromPacket(true);
    EXPECT_TRUE(img->writeXmpFromPacket());
}

// ==================== byteOrder tests ====================

TEST_F(ImageTest_1081, ByteOrderDefaultIsInvalid_1081) {
    auto img = createTestImage();
    EXPECT_EQ(img->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageTest_1081, SetByteOrderLittleEndian_1081) {
    auto img = createTestImage();
    img->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(img->byteOrder(), Exiv2::littleEndian);
}

TEST_F(ImageTest_1081, SetByteOrderBigEndian_1081) {
    auto img = createTestImage();
    img->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(img->byteOrder(), Exiv2::bigEndian);
}

// ==================== pixelWidth / pixelHeight tests ====================

TEST_F(ImageTest_1081, PixelWidthDefaultIsZero_1081) {
    auto img = createTestImage();
    EXPECT_EQ(img->pixelWidth(), 0u);
}

TEST_F(ImageTest_1081, PixelHeightDefaultIsZero_1081) {
    auto img = createTestImage();
    EXPECT_EQ(img->pixelHeight(), 0u);
}

// ==================== comment tests ====================

TEST_F(ImageTest_1081, CommentDefaultIsEmpty_1081) {
    auto img = createTestImage();
    EXPECT_TRUE(img->comment().empty());
}

TEST_F(ImageTest_1081, SetComment_1081) {
    auto img = createTestImage();
    img->setComment("Hello World");
    EXPECT_EQ(img->comment(), "Hello World");
}

TEST_F(ImageTest_1081, ClearComment_1081) {
    auto img = createTestImage();
    img->setComment("Test comment");
    img->clearComment();
    EXPECT_TRUE(img->comment().empty());
}

TEST_F(ImageTest_1081, SetCommentEmpty_1081) {
    auto img = createTestImage();
    img->setComment("");
    EXPECT_TRUE(img->comment().empty());
}

TEST_F(ImageTest_1081, SetCommentOverwrite_1081) {
    auto img = createTestImage();
    img->setComment("First");
    img->setComment("Second");
    EXPECT_EQ(img->comment(), "Second");
}

// ==================== ExifData tests ====================

TEST_F(ImageTest_1081, ExifDataDefaultIsEmpty_1081) {
    auto img = createTestImage();
    EXPECT_TRUE(img->exifData().empty());
}

TEST_F(ImageTest_1081, SetExifData_1081) {
    auto img = createTestImage();
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    img->setExifData(exifData);
    EXPECT_FALSE(img->exifData().empty());
}

TEST_F(ImageTest_1081, ClearExifData_1081) {
    auto img = createTestImage();
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    img->setExifData(exifData);
    img->clearExifData();
    EXPECT_TRUE(img->exifData().empty());
}

// ==================== IptcData tests ====================

TEST_F(ImageTest_1081, IptcDataDefaultIsEmpty_1081) {
    auto img = createTestImage();
    EXPECT_TRUE(img->iptcData().empty());
}

TEST_F(ImageTest_1081, SetIptcData_1081) {
    auto img = createTestImage();
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test caption";
    img->setIptcData(iptcData);
    EXPECT_FALSE(img->iptcData().empty());
}

TEST_F(ImageTest_1081, ClearIptcData_1081) {
    auto img = createTestImage();
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test caption";
    img->setIptcData(iptcData);
    img->clearIptcData();
    EXPECT_TRUE(img->iptcData().empty());
}

// ==================== XmpData tests ====================

TEST_F(ImageTest_1081, XmpDataDefaultIsEmpty_1081) {
    auto img = createTestImage();
    EXPECT_TRUE(img->xmpData().empty());
}

TEST_F(ImageTest_1081, ClearXmpData_1081) {
    auto img = createTestImage();
    img->clearXmpData();
    EXPECT_TRUE(img->xmpData().empty());
}

// ==================== XmpPacket tests ====================

TEST_F(ImageTest_1081, XmpPacketDefaultIsEmpty_1081) {
    auto img = createTestImage();
    EXPECT_TRUE(img->xmpPacket().empty());
}

TEST_F(ImageTest_1081, SetXmpPacket_1081) {
    auto img = createTestImage();
    std::string xmpPacket = "<?xml version=\"1.0\"?><x:xmpmeta></x:xmpmeta>";
    img->setXmpPacket(xmpPacket);
    EXPECT_EQ(img->xmpPacket(), xmpPacket);
}

TEST_F(ImageTest_1081, ClearXmpPacket_1081) {
    auto img = createTestImage();
    img->setXmpPacket("some packet");
    img->clearXmpPacket();
    EXPECT_TRUE(img->xmpPacket().empty());
}

// ==================== clearMetadata tests ====================

TEST_F(ImageTest_1081, ClearMetadataClearsAll_1081) {
    auto img = createTestImage();
    img->setComment("A comment");
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    img->setExifData(exifData);
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test";
    img->setIptcData(iptcData);

    img->clearMetadata();

    EXPECT_TRUE(img->comment().empty());
    EXPECT_TRUE(img->exifData().empty());
    EXPECT_TRUE(img->iptcData().empty());
    EXPECT_TRUE(img->xmpData().empty());
    EXPECT_TRUE(img->xmpPacket().empty());
}

// ==================== setMetadata tests ====================

TEST_F(ImageTest_1081, SetMetadataFromAnotherImage_1081) {
    auto img1 = createTestImage();
    auto img2 = createTestImage();

    img1->setComment("Source comment");
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "SourceMake";
    img1->setExifData(exifData);

    img2->setMetadata(*img1);

    EXPECT_EQ(img2->comment(), "Source comment");
    EXPECT_FALSE(img2->exifData().empty());
}

// ==================== ICC Profile tests ====================

TEST_F(ImageTest_1081, IccProfileDefaultNotDefined_1081) {
    auto img = createTestImage();
    EXPECT_FALSE(img->iccProfileDefined());
}

TEST_F(ImageTest_1081, ClearIccProfile_1081) {
    auto img = createTestImage();
    img->clearIccProfile();
    EXPECT_FALSE(img->iccProfileDefined());
}

// ==================== good() tests ====================

TEST_F(ImageTest_1081, GoodWithMemIo_1081) {
    auto img = createTestImage();
    // MemIo should report good state
    EXPECT_TRUE(img->good());
}

// ==================== io() tests ====================

TEST_F(ImageTest_1081, IoReturnsReference_1081) {
    auto img = createTestImage();
    const Exiv2::BasicIo& io = img->io();
    // Just verify we can access it without crashing
    EXPECT_NO_THROW(io.size());
}

// ==================== mimeType tests ====================

TEST_F(ImageTest_1081, MimeType_1081) {
    auto img = createTestImage();
    EXPECT_EQ(img->mimeType(), "application/octet-stream");
}

// ==================== imageType tests ====================

TEST_F(ImageTest_1081, ImageType_1081) {
    auto img = createTestImage();
    EXPECT_EQ(img->imageType(), Exiv2::ImageType::none);
}

// ==================== nativePreviews tests ====================

TEST_F(ImageTest_1081, NativePreviewsDefaultIsEmpty_1081) {
    auto img = createTestImage();
    EXPECT_TRUE(img->nativePreviews().empty());
}

// ==================== Static utility function tests ====================

TEST_F(ImageTest_1081, IsBigEndianOrLittleEndian_1081) {
    // On any platform, exactly one should be true
    bool big = Exiv2::Image::isBigEndianPlatform();
    bool little = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_NE(big, little);
}

TEST_F(ImageTest_1081, ByteSwap16NoSwap_1081) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x1234);
}

TEST_F(ImageTest_1081, ByteSwap16WithSwap_1081) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x3412);
}

TEST_F(ImageTest_1081, ByteSwap32NoSwap_1081) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x12345678u);
}

TEST_F(ImageTest_1081, ByteSwap32WithSwap_1081) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x78563412u);
}

TEST_F(ImageTest_1081, ByteSwap64NoSwap_1081) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x0102030405060708ULL);
}

TEST_F(ImageTest_1081, ByteSwap64WithSwap_1081) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x0807060504030201ULL);
}

TEST_F(ImageTest_1081, ByteSwap16Zero_1081) {
    uint16_t val = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0);
}

TEST_F(ImageTest_1081, ByteSwap32Zero_1081) {
    uint32_t val = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0u);
}

TEST_F(ImageTest_1081, ByteSwap64Zero_1081) {
    uint64_t val = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0ULL);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0ULL);
}

// ==================== isStringType tests ====================

TEST_F(ImageTest_1081, IsStringTypeForAscii_1081) {
    // Type 2 is typically ASCII in TIFF
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
}

TEST_F(ImageTest_1081, IsStringTypeForNonString_1081) {
    // Type 3 is SHORT in TIFF
    EXPECT_FALSE(Exiv2::Image::isStringType(3));
}

// ==================== isShortType tests ====================

TEST_F(ImageTest_1081, IsShortTypeForShort_1081) {
    // Type 3 is SHORT
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
}

TEST_F(ImageTest_1081, IsShortTypeForNonShort_1081) {
    EXPECT_FALSE(Exiv2::Image::isShortType(2));
}

// ==================== isLongType tests ====================

TEST_F(ImageTest_1081, IsLongTypeForLong_1081) {
    // Type 4 is LONG
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
}

TEST_F(ImageTest_1081, IsLongTypeForNonLong_1081) {
    EXPECT_FALSE(Exiv2::Image::isLongType(2));
}

// ==================== isRationalType tests ====================

TEST_F(ImageTest_1081, IsRationalTypeForRational_1081) {
    // Type 5 is RATIONAL
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
}

TEST_F(ImageTest_1081, IsRationalTypeForNonRational_1081) {
    EXPECT_FALSE(Exiv2::Image::isRationalType(2));
}

// ==================== is2ByteType tests ====================

TEST_F(ImageTest_1081, Is2ByteType_1081) {
    // SHORT (3) is 2 bytes
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
    // LONG (4) is not 2 bytes
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

// ==================== is4ByteType tests ====================

TEST_F(ImageTest_1081, Is4ByteType_1081) {
    // LONG (4) is 4 bytes
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
    // SHORT (3) is not 4 bytes
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
}

// ==================== is8ByteType tests ====================

TEST_F(ImageTest_1081, Is8ByteType_1081) {
    // RATIONAL (5) is 8 bytes
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
    // SHORT (3) is not 8 bytes
    EXPECT_FALSE(Exiv2::Image::is8ByteType(3));
}

// ==================== byteSwap2/4/8 with DataBuf ====================

TEST_F(ImageTest_1081, ByteSwap2WithDataBuf_1081) {
    Exiv2::DataBuf buf(4);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    uint16_t result = Exiv2::Image::byteSwap2(buf, 0, false);
    uint16_t resultSwapped = Exiv2::Image::byteSwap2(buf, 0, true);
    // One should be the byte-swapped version of the other
    EXPECT_EQ(result, Exiv2::Image::byteSwap(resultSwapped, true));
}

TEST_F(ImageTest_1081, ByteSwap4WithDataBuf_1081) {
    Exiv2::DataBuf buf(8);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    buf.write_uint8(2, 0x56);
    buf.write_uint8(3, 0x78);
    uint32_t result = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t resultSwapped = Exiv2::Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(result, Exiv2::Image::byteSwap(resultSwapped, true));
}

TEST_F(ImageTest_1081, ByteSwap8WithDataBuf_1081) {
    Exiv2::DataBuf buf(16);
    buf.write_uint8(0, 0x01);
    buf.write_uint8(1, 0x02);
    buf.write_uint8(2, 0x03);
    buf.write_uint8(3, 0x04);
    buf.write_uint8(4, 0x05);
    buf.write_uint8(5, 0x06);
    buf.write_uint8(6, 0x07);
    buf.write_uint8(7, 0x08);
    uint64_t result = Exiv2::Image::byteSwap8(buf, 0, false);
    uint64_t resultSwapped = Exiv2::Image::byteSwap8(buf, 0, true);
    EXPECT_EQ(result, Exiv2::Image::byteSwap(resultSwapped, true));
}

// ==================== Boundary: ByteSwap with max values ====================

TEST_F(ImageTest_1081, ByteSwap16MaxValue_1081) {
    uint16_t val = 0xFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFF);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0xFFFF);
}

TEST_F(ImageTest_1081, ByteSwap32MaxValue_1081) {
    uint32_t val = 0xFFFFFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFFFFFu);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0xFFFFFFFFu);
}

TEST_F(ImageTest_1081, ByteSwap64MaxValue_1081) {
    uint64_t val = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFFFFFFFFFFFFFULL);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0xFFFFFFFFFFFFFFFFULL);
}

// ==================== setTypeSupported tests ====================

TEST_F(ImageTest_1081, SetTypeSupported_1081) {
    auto img = createTestImage(0);
    img->setTypeSupported(Exiv2::ImageType::jpeg, 0xFFFF);
    EXPECT_EQ(img->imageType(), Exiv2::ImageType::jpeg);
}

// ==================== Double swap is identity ====================

TEST_F(ImageTest_1081, DoubleByteSwap16IsIdentity_1081) {
    uint16_t val = 0xABCD;
    EXPECT_EQ(Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true), val);
}

TEST_F(ImageTest_1081, DoubleByteSwap32IsIdentity_1081) {
    uint32_t val = 0xDEADBEEF;
    EXPECT_EQ(Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true), val);
}

TEST_F(ImageTest_1081, DoubleByteSwap64IsIdentity_1081) {
    uint64_t val = 0xDEADBEEFCAFEBABEULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true), val);
}
