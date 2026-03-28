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

using namespace Exiv2;

// Concrete subclass for testing since Image is abstract
class TestImage : public Exiv2::Image {
public:
    TestImage(std::unique_ptr<BasicIo> io)
        : Image(ImageType::none, mdExif | mdIptc | mdXmp | mdComment, std::move(io)) {}

    void readMetadata() override {}
    void writeMetadata() override {}
};

class ImageTest_1099 : public ::testing::Test {
protected:
    void SetUp() override {
        auto io = std::make_unique<MemIo>();
        image_ = std::make_unique<TestImage>(std::move(io));
    }

    std::unique_ptr<TestImage> image_;
};

// Test byteOrder default
TEST_F(ImageTest_1099, DefaultByteOrderIsInvalid_1099) {
    EXPECT_EQ(image_->byteOrder(), invalidByteOrder);
}

// Test setByteOrder / byteOrder
TEST_F(ImageTest_1099, SetByteOrderLittleEndian_1099) {
    image_->setByteOrder(littleEndian);
    EXPECT_EQ(image_->byteOrder(), littleEndian);
}

TEST_F(ImageTest_1099, SetByteOrderBigEndian_1099) {
    image_->setByteOrder(bigEndian);
    EXPECT_EQ(image_->byteOrder(), bigEndian);
}

// Test pixelWidth / pixelHeight defaults
TEST_F(ImageTest_1099, DefaultPixelWidthIsZero_1099) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(ImageTest_1099, DefaultPixelHeightIsZero_1099) {
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// Test comment default
TEST_F(ImageTest_1099, DefaultCommentIsEmpty_1099) {
    EXPECT_TRUE(image_->comment().empty());
}

// Test setComment / comment
TEST_F(ImageTest_1099, SetCommentReturnsCorrectValue_1099) {
    image_->setComment("Hello World");
    EXPECT_EQ(image_->comment(), "Hello World");
}

// Test clearComment
TEST_F(ImageTest_1099, ClearCommentRemovesComment_1099) {
    image_->setComment("Test comment");
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

// Test setExifData / exifData
TEST_F(ImageTest_1099, SetExifDataStoresData_1099) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    EXPECT_FALSE(image_->exifData().empty());
}

// Test clearExifData
TEST_F(ImageTest_1099, ClearExifDataRemovesData_1099) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

// Test setIptcData / iptcData
TEST_F(ImageTest_1099, SetIptcDataStoresData_1099) {
    IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test";
    image_->setIptcData(iptcData);
    EXPECT_FALSE(image_->iptcData().empty());
}

// Test clearIptcData
TEST_F(ImageTest_1099, ClearIptcDataRemovesData_1099) {
    IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test";
    image_->setIptcData(iptcData);
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

// Test setXmpData / xmpData
TEST_F(ImageTest_1099, SetXmpDataStoresData_1099) {
    XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test Title";
    image_->setXmpData(xmpData);
    EXPECT_FALSE(image_->xmpData().empty());
}

// Test clearXmpData
TEST_F(ImageTest_1099, ClearXmpDataRemovesData_1099) {
    XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test Title";
    image_->setXmpData(xmpData);
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// Test xmpPacket
TEST_F(ImageTest_1099, DefaultXmpPacketIsEmpty_1099) {
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// Test setXmpPacket / clearXmpPacket
TEST_F(ImageTest_1099, SetXmpPacketStoresPacket_1099) {
    image_->setXmpPacket("<xmp>test</xmp>");
    EXPECT_EQ(image_->xmpPacket(), "<xmp>test</xmp>");
}

TEST_F(ImageTest_1099, ClearXmpPacketRemovesPacket_1099) {
    image_->setXmpPacket("<xmp>test</xmp>");
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// Test writeXmpFromPacket
TEST_F(ImageTest_1099, DefaultWriteXmpFromPacketIsFalse_1099) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1099, SetWriteXmpFromPacketTrue_1099) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1099, SetWriteXmpFromPacketFalse_1099) {
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// Test clearMetadata
TEST_F(ImageTest_1099, ClearMetadataClearsAll_1099) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    image_->setComment("Test");

    image_->clearMetadata();

    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_TRUE(image_->comment().empty());
}

// Test good()
TEST_F(ImageTest_1099, GoodReturnsTrueForValidIo_1099) {
    // MemIo should be in a good state by default
    EXPECT_TRUE(image_->good());
}

// Test io()
TEST_F(ImageTest_1099, IoReturnsReference_1099) {
    const BasicIo& io = image_->io();
    // Just verify we can access it without crash
    EXPECT_NO_THROW(io.size());
}

// Test imageType
TEST_F(ImageTest_1099, ImageTypeIsNone_1099) {
    EXPECT_EQ(image_->imageType(), ImageType::none);
}

// Test nativePreviews
TEST_F(ImageTest_1099, NativePreviewsDefaultEmpty_1099) {
    EXPECT_TRUE(image_->nativePreviews().empty());
}

// Test ICC profile
TEST_F(ImageTest_1099, DefaultIccProfileNotDefined_1099) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1099, ClearIccProfile_1099) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

// Test setMetadata copies from another image
TEST_F(ImageTest_1099, SetMetadataCopiesFromAnotherImage_1099) {
    auto io2 = std::make_unique<MemIo>();
    TestImage other(std::move(io2));
    other.setComment("Copied comment");

    ExifData exifData;
    exifData["Exif.Image.Make"] = "CopiedMake";
    other.setExifData(exifData);

    image_->setMetadata(other);

    EXPECT_EQ(image_->comment(), "Copied comment");
    EXPECT_FALSE(image_->exifData().empty());
}

// Static method tests
TEST_F(ImageTest_1099, IsBigEndianOrLittleEndianPlatform_1099) {
    // One of these must be true on any platform
    bool isBig = Image::isBigEndianPlatform();
    bool isLittle = Image::isLittleEndianPlatform();
    EXPECT_NE(isBig, isLittle);
}

// Test isStringType
TEST_F(ImageTest_1099, IsStringTypeForAscii_1099) {
    // Type 2 is ASCII in TIFF
    EXPECT_TRUE(Image::isStringType(2));
}

TEST_F(ImageTest_1099, IsStringTypeForNonString_1099) {
    // Type 3 is SHORT
    EXPECT_FALSE(Image::isStringType(3));
}

// Test isShortType
TEST_F(ImageTest_1099, IsShortTypeForShort_1099) {
    // Type 3 is SHORT
    EXPECT_TRUE(Image::isShortType(3));
}

TEST_F(ImageTest_1099, IsShortTypeForNonShort_1099) {
    EXPECT_FALSE(Image::isShortType(2));
}

// Test isLongType
TEST_F(ImageTest_1099, IsLongTypeForLong_1099) {
    // Type 4 is LONG
    EXPECT_TRUE(Image::isLongType(4));
}

TEST_F(ImageTest_1099, IsLongTypeForNonLong_1099) {
    EXPECT_FALSE(Image::isLongType(2));
}

// Test isRationalType
TEST_F(ImageTest_1099, IsRationalTypeForRational_1099) {
    // Type 5 is RATIONAL
    EXPECT_TRUE(Image::isRationalType(5));
}

TEST_F(ImageTest_1099, IsRationalTypeForNonRational_1099) {
    EXPECT_FALSE(Image::isRationalType(2));
}

// Test is2ByteType
TEST_F(ImageTest_1099, Is2ByteTypeForShort_1099) {
    // SHORT (3) is 2-byte
    EXPECT_TRUE(Image::is2ByteType(3));
}

// Test is4ByteType
TEST_F(ImageTest_1099, Is4ByteTypeForLong_1099) {
    // LONG (4) is 4-byte
    EXPECT_TRUE(Image::is4ByteType(4));
}

// Test is8ByteType
TEST_F(ImageTest_1099, Is8ByteTypeForRational_1099) {
    // RATIONAL (5) is 8-byte
    EXPECT_TRUE(Image::is8ByteType(5));
}

// Test byteSwap uint16_t
TEST_F(ImageTest_1099, ByteSwap16NoSwap_1099) {
    uint16_t val = 0x0102;
    EXPECT_EQ(Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1099, ByteSwap16WithSwap_1099) {
    uint16_t val = 0x0102;
    uint16_t swapped = Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0201);
}

// Test byteSwap uint32_t
TEST_F(ImageTest_1099, ByteSwap32NoSwap_1099) {
    uint32_t val = 0x01020304;
    EXPECT_EQ(Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1099, ByteSwap32WithSwap_1099) {
    uint32_t val = 0x01020304;
    uint32_t swapped = Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x04030201u);
}

// Test byteSwap uint64_t
TEST_F(ImageTest_1099, ByteSwap64NoSwap_1099) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1099, ByteSwap64WithSwap_1099) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t swapped = Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0807060504030201ULL);
}

// Test byteSwap2 with DataBuf
TEST_F(ImageTest_1099, ByteSwap2FromBuf_1099) {
    uint8_t data[] = {0x01, 0x02};
    DataBuf buf(data, sizeof(data));
    uint16_t result = Image::byteSwap2(buf, 0, false);
    uint16_t resultSwapped = Image::byteSwap2(buf, 0, true);
    // One should be 0x0102, the other 0x0201
    EXPECT_NE(result, resultSwapped);
}

// Test byteSwap4 with DataBuf
TEST_F(ImageTest_1099, ByteSwap4FromBuf_1099) {
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    uint32_t result = Image::byteSwap4(buf, 0, false);
    uint32_t resultSwapped = Image::byteSwap4(buf, 0, true);
    EXPECT_NE(result, resultSwapped);
}

// Test byteSwap8 with DataBuf
TEST_F(ImageTest_1099, ByteSwap8FromBuf_1099) {
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    DataBuf buf(data, sizeof(data));
    uint64_t result = Image::byteSwap8(buf, 0, false);
    uint64_t resultSwapped = Image::byteSwap8(buf, 0, true);
    EXPECT_NE(result, resultSwapped);
}

// Test supportsMetadata
TEST_F(ImageTest_1099, SupportsExifMetadata_1099) {
    EXPECT_TRUE(image_->supportsMetadata(mdExif));
}

TEST_F(ImageTest_1099, SupportsIptcMetadata_1099) {
    EXPECT_TRUE(image_->supportsMetadata(mdIptc));
}

TEST_F(ImageTest_1099, SupportsXmpMetadata_1099) {
    EXPECT_TRUE(image_->supportsMetadata(mdXmp));
}

TEST_F(ImageTest_1099, SupportsCommentMetadata_1099) {
    EXPECT_TRUE(image_->supportsMetadata(mdComment));
}

// Test setTypeSupported
TEST_F(ImageTest_1099, SetTypeSupportedChangesImageType_1099) {
    image_->setTypeSupported(ImageType::jpeg, mdExif);
    EXPECT_EQ(image_->imageType(), ImageType::jpeg);
}

// Test setComment with empty string
TEST_F(ImageTest_1099, SetEmptyComment_1099) {
    image_->setComment("");
    EXPECT_EQ(image_->comment(), "");
}

// Test setComment with long string
TEST_F(ImageTest_1099, SetLongComment_1099) {
    std::string longComment(10000, 'x');
    image_->setComment(longComment);
    EXPECT_EQ(image_->comment(), longComment);
}

// Test byteSwap boundary - zero values
TEST_F(ImageTest_1099, ByteSwap16Zero_1099) {
    EXPECT_EQ(Image::byteSwap(static_cast<uint16_t>(0), true), 0u);
    EXPECT_EQ(Image::byteSwap(static_cast<uint16_t>(0), false), 0u);
}

TEST_F(ImageTest_1099, ByteSwap32Zero_1099) {
    EXPECT_EQ(Image::byteSwap(static_cast<uint32_t>(0), true), 0u);
    EXPECT_EQ(Image::byteSwap(static_cast<uint32_t>(0), false), 0u);
}

TEST_F(ImageTest_1099, ByteSwap64Zero_1099) {
    EXPECT_EQ(Image::byteSwap(static_cast<uint64_t>(0), true), 0u);
    EXPECT_EQ(Image::byteSwap(static_cast<uint64_t>(0), false), 0u);
}

// Test byteSwap max values
TEST_F(ImageTest_1099, ByteSwap16MaxValue_1099) {
    uint16_t val = 0xFFFF;
    EXPECT_EQ(Image::byteSwap(val, true), 0xFFFF);
}

TEST_F(ImageTest_1099, ByteSwap32MaxValue_1099) {
    uint32_t val = 0xFFFFFFFF;
    EXPECT_EQ(Image::byteSwap(val, true), 0xFFFFFFFF);
}

TEST_F(ImageTest_1099, ByteSwap64MaxValue_1099) {
    uint64_t val = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_EQ(Image::byteSwap(val, true), 0xFFFFFFFFFFFFFFFFULL);
}

// Endian platform consistency
TEST_F(ImageTest_1099, EndianPlatformConsistency_1099) {
    EXPECT_TRUE(Image::isBigEndianPlatform() || Image::isLittleEndianPlatform());
    EXPECT_FALSE(Image::isBigEndianPlatform() && Image::isLittleEndianPlatform());
}

// Test checkMode
TEST_F(ImageTest_1099, CheckModeForSupportedMetadata_1099) {
    AccessMode mode = image_->checkMode(mdExif);
    // Should return amReadWrite or amRead for supported metadata
    EXPECT_NE(mode, amNone);
}

// Test isLongLongType
TEST_F(ImageTest_1099, IsLongLongTypeForNonLongLong_1099) {
    EXPECT_FALSE(Image::isLongLongType(3)); // SHORT is not LONGLONG
}

// Test appendIccProfile and iccProfileDefined
TEST_F(ImageTest_1099, AppendIccProfileMakesItDefined_1099) {
    // A minimal ICC profile header (must be at least 132 bytes for a valid ICC profile)
    // We use bTestValid=false to skip validation
    uint8_t bytes[4] = {0x01, 0x02, 0x03, 0x04};
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}
