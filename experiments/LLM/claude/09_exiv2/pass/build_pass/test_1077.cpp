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

using namespace Exiv2;

// Since Image is abstract (has pure virtual methods like readMetadata/writeMetadata),
// we need a concrete subclass for testing.
class TestImage : public Image {
public:
    TestImage(std::unique_ptr<BasicIo> io)
        : Image(ImageType::none, mdExif | mdIptc | mdXmp | mdComment, std::move(io)) {}

    void readMetadata() override {}
    void writeMetadata() override {}
    std::string mimeType() const override { return "application/octet-stream"; }
};

class ImageTest_1077 : public ::testing::Test {
protected:
    void SetUp() override {
        auto io = std::make_unique<MemIo>();
        image_ = std::make_unique<TestImage>(std::move(io));
    }

    std::unique_ptr<TestImage> image_;
};

// ==================== clearXmpPacket tests ====================

TEST_F(ImageTest_1077, ClearXmpPacketClearsPacket_1077) {
    image_->setXmpPacket("<xmp>test</xmp>");
    EXPECT_FALSE(image_->xmpPacket().empty());
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageTest_1077, ClearXmpPacketSetsWriteXmpFromPacketTrue_1077) {
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1077, ClearXmpPacketOnEmptyPacket_1077) {
    // Clearing an already empty packet should still work
    EXPECT_TRUE(image_->xmpPacket().empty());
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

// ==================== setXmpPacket / xmpPacket tests ====================

TEST_F(ImageTest_1077, SetXmpPacketStoresPacket_1077) {
    std::string packet = "<xmp>some xmp data</xmp>";
    image_->setXmpPacket(packet);
    EXPECT_EQ(image_->xmpPacket(), packet);
}

TEST_F(ImageTest_1077, SetXmpPacketEmptyString_1077) {
    image_->setXmpPacket("");
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// ==================== writeXmpFromPacket tests ====================

TEST_F(ImageTest_1077, WriteXmpFromPacketDefaultFalse_1077) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1077, WriteXmpFromPacketSetTrue_1077) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1077, WriteXmpFromPacketSetFalse_1077) {
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// ==================== ExifData tests ====================

TEST_F(ImageTest_1077, ExifDataInitiallyEmpty_1077) {
    EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(ImageTest_1077, SetExifDataAndRetrieve_1077) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "TestCamera";
    image_->setExifData(exifData);
    EXPECT_FALSE(image_->exifData().empty());
}

TEST_F(ImageTest_1077, ClearExifData_1077) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "TestCamera";
    image_->setExifData(exifData);
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

// ==================== IptcData tests ====================

TEST_F(ImageTest_1077, IptcDataInitiallyEmpty_1077) {
    EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageTest_1077, SetIptcDataAndRetrieve_1077) {
    IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test Caption";
    image_->setIptcData(iptcData);
    EXPECT_FALSE(image_->iptcData().empty());
}

TEST_F(ImageTest_1077, ClearIptcData_1077) {
    IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test Caption";
    image_->setIptcData(iptcData);
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

// ==================== XmpData tests ====================

TEST_F(ImageTest_1077, XmpDataInitiallyEmpty_1077) {
    EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageTest_1077, ClearXmpData_1077) {
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// ==================== Comment tests ====================

TEST_F(ImageTest_1077, CommentInitiallyEmpty_1077) {
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1077, SetComment_1077) {
    image_->setComment("Hello World");
    EXPECT_EQ(image_->comment(), "Hello World");
}

TEST_F(ImageTest_1077, ClearComment_1077) {
    image_->setComment("Hello World");
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1077, SetCommentEmptyString_1077) {
    image_->setComment("");
    EXPECT_TRUE(image_->comment().empty());
}

// ==================== clearMetadata tests ====================

TEST_F(ImageTest_1077, ClearMetadataClearsAll_1077) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "TestCamera";
    image_->setExifData(exifData);
    image_->setComment("Test comment");
    image_->setXmpPacket("<xmp>test</xmp>");

    image_->clearMetadata();

    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_TRUE(image_->xmpPacket().empty());
    EXPECT_TRUE(image_->comment().empty());
}

// ==================== ByteOrder tests ====================

TEST_F(ImageTest_1077, ByteOrderDefaultInvalid_1077) {
    EXPECT_EQ(image_->byteOrder(), invalidByteOrder);
}

TEST_F(ImageTest_1077, SetByteOrderBigEndian_1077) {
    image_->setByteOrder(bigEndian);
    EXPECT_EQ(image_->byteOrder(), bigEndian);
}

TEST_F(ImageTest_1077, SetByteOrderLittleEndian_1077) {
    image_->setByteOrder(littleEndian);
    EXPECT_EQ(image_->byteOrder(), littleEndian);
}

// ==================== pixelWidth / pixelHeight tests ====================

TEST_F(ImageTest_1077, PixelWidthInitiallyZero_1077) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(ImageTest_1077, PixelHeightInitiallyZero_1077) {
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// ==================== good() tests ====================

TEST_F(ImageTest_1077, GoodReturnsTrueForValidIo_1077) {
    // MemIo should be "good" by default
    EXPECT_TRUE(image_->good());
}

// ==================== io() tests ====================

TEST_F(ImageTest_1077, IoReturnsReference_1077) {
    const BasicIo& io = image_->io();
    // Just verify it doesn't crash and is accessible
    (void)io;
}

// ==================== mimeType tests ====================

TEST_F(ImageTest_1077, MimeType_1077) {
    EXPECT_EQ(image_->mimeType(), "application/octet-stream");
}

// ==================== nativePreviews tests ====================

TEST_F(ImageTest_1077, NativePreviewsInitiallyEmpty_1077) {
    EXPECT_TRUE(image_->nativePreviews().empty());
}

// ==================== ICC Profile tests ====================

TEST_F(ImageTest_1077, IccProfileNotDefinedInitially_1077) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1077, ClearIccProfile_1077) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

// ==================== Static method tests ====================

TEST_F(ImageTest_1077, IsBigOrLittleEndianPlatform_1077) {
    // One of them must be true
    bool big = Image::isBigEndianPlatform();
    bool little = Image::isLittleEndianPlatform();
    EXPECT_NE(big, little);
}

TEST_F(ImageTest_1077, IsStringType_1077) {
    // ASCII type is 2 in TIFF
    EXPECT_TRUE(Image::isStringType(2));
    EXPECT_FALSE(Image::isStringType(3)); // SHORT type
}

TEST_F(ImageTest_1077, IsShortType_1077) {
    // SHORT is 3, SSHORT is 8
    EXPECT_TRUE(Image::isShortType(3));
    EXPECT_TRUE(Image::isShortType(8));
    EXPECT_FALSE(Image::isShortType(2));
}

TEST_F(ImageTest_1077, IsLongType_1077) {
    // LONG is 4, SLONG is 9
    EXPECT_TRUE(Image::isLongType(4));
    EXPECT_TRUE(Image::isLongType(9));
    EXPECT_FALSE(Image::isLongType(3));
}

TEST_F(ImageTest_1077, IsRationalType_1077) {
    // RATIONAL is 5, SRATIONAL is 10
    EXPECT_TRUE(Image::isRationalType(5));
    EXPECT_TRUE(Image::isRationalType(10));
    EXPECT_FALSE(Image::isRationalType(4));
}

TEST_F(ImageTest_1077, Is2ByteType_1077) {
    // SHORT=3, SSHORT=8
    EXPECT_TRUE(Image::is2ByteType(3));
    EXPECT_TRUE(Image::is2ByteType(8));
    EXPECT_FALSE(Image::is2ByteType(4));
}

TEST_F(ImageTest_1077, Is4ByteType_1077) {
    // LONG=4, SLONG=9, FLOAT=11
    EXPECT_TRUE(Image::is4ByteType(4));
    EXPECT_TRUE(Image::is4ByteType(9));
    EXPECT_FALSE(Image::is4ByteType(3));
}

TEST_F(ImageTest_1077, Is8ByteType_1077) {
    // RATIONAL=5, SRATIONAL=10, DOUBLE=12
    EXPECT_TRUE(Image::is8ByteType(5));
    EXPECT_TRUE(Image::is8ByteType(10));
    EXPECT_FALSE(Image::is8ByteType(3));
}

// ==================== byteSwap tests ====================

TEST_F(ImageTest_1077, ByteSwap16NoSwap_1077) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1077, ByteSwap16WithSwap_1077) {
    uint16_t val = 0x1234;
    uint16_t swapped = Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x3412);
}

TEST_F(ImageTest_1077, ByteSwap32NoSwap_1077) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1077, ByteSwap32WithSwap_1077) {
    uint32_t val = 0x12345678;
    uint32_t swapped = Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x78563412u);
}

TEST_F(ImageTest_1077, ByteSwap64NoSwap_1077) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1077, ByteSwap64WithSwap_1077) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t swapped = Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0807060504030201ULL);
}

// ==================== byteSwap2/4/8 from DataBuf tests ====================

TEST_F(ImageTest_1077, ByteSwap2FromBuf_1077) {
    DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    uint16_t result = Image::byteSwap2(buf, 0, false);
    EXPECT_EQ(result, 0x1234);
    uint16_t swapped = Image::byteSwap2(buf, 0, true);
    EXPECT_EQ(swapped, 0x3412);
}

TEST_F(ImageTest_1077, ByteSwap4FromBuf_1077) {
    DataBuf buf(8);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    buf.data()[2] = 0x56;
    buf.data()[3] = 0x78;
    uint32_t result = Image::byteSwap4(buf, 0, false);
    EXPECT_EQ(result, 0x12345678u);
    uint32_t swapped = Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(swapped, 0x78563412u);
}

TEST_F(ImageTest_1077, ByteSwap8FromBuf_1077) {
    DataBuf buf(16);
    buf.data()[0] = 0x01;
    buf.data()[1] = 0x02;
    buf.data()[2] = 0x03;
    buf.data()[3] = 0x04;
    buf.data()[4] = 0x05;
    buf.data()[5] = 0x06;
    buf.data()[6] = 0x07;
    buf.data()[7] = 0x08;
    uint64_t result = Image::byteSwap8(buf, 0, false);
    EXPECT_EQ(result, 0x0102030405060708ULL);
    uint64_t swapped = Image::byteSwap8(buf, 0, true);
    EXPECT_EQ(swapped, 0x0807060504030201ULL);
}

// ==================== imageType tests ====================

TEST_F(ImageTest_1077, ImageTypeReturnsCorrectType_1077) {
    EXPECT_EQ(image_->imageType(), ImageType::none);
}

// ==================== setMetadata tests ====================

TEST_F(ImageTest_1077, SetMetadataFromAnotherImage_1077) {
    auto io2 = std::make_unique<MemIo>();
    TestImage other(std::move(io2));
    other.setComment("Copied comment");

    ExifData exifData;
    exifData["Exif.Image.Make"] = "CopiedCamera";
    other.setExifData(exifData);

    image_->setMetadata(other);
    EXPECT_EQ(image_->comment(), "Copied comment");
    EXPECT_FALSE(image_->exifData().empty());
}

// ==================== Multiple clearXmpPacket calls ====================

TEST_F(ImageTest_1077, MultipleClearXmpPacketCalls_1077) {
    image_->setXmpPacket("<xmp>data</xmp>");
    image_->clearXmpPacket();
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

// ==================== Set then clear then set ====================

TEST_F(ImageTest_1077, SetClearSetXmpPacket_1077) {
    image_->setXmpPacket("<xmp>first</xmp>");
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());

    image_->setXmpPacket("<xmp>second</xmp>");
    EXPECT_EQ(image_->xmpPacket(), "<xmp>second</xmp>");
}

// ==================== isPrintXMP / isPrintICC tests ====================

TEST_F(ImageTest_1077, IsPrintXMPTest_1077) {
    // type 2 = ASCII, with kpsXMP option
    bool result = Image::isPrintXMP(2, kpsXMP);
    // We just verify it returns a bool without crashing
    (void)result;
}

TEST_F(ImageTest_1077, IsPrintICCTest_1077) {
    bool result = Image::isPrintICC(2, kpsIccProfile);
    (void)result;
}

// ==================== IsLongLongType tests ====================

TEST_F(ImageTest_1077, IsLongLongType_1077) {
    // LONG8 = 16, SLONG8 = 17 (if using BigTIFF)
    // Type 0 should not be long long
    EXPECT_FALSE(Image::isLongLongType(0));
    EXPECT_FALSE(Image::isLongLongType(4)); // LONG, not LONGLONG
}

// ==================== Edge case: byteSwap with zero ====================

TEST_F(ImageTest_1077, ByteSwap16Zero_1077) {
    EXPECT_EQ(Image::byteSwap(static_cast<uint16_t>(0), true), 0u);
    EXPECT_EQ(Image::byteSwap(static_cast<uint16_t>(0), false), 0u);
}

TEST_F(ImageTest_1077, ByteSwap32Zero_1077) {
    EXPECT_EQ(Image::byteSwap(static_cast<uint32_t>(0), true), 0u);
    EXPECT_EQ(Image::byteSwap(static_cast<uint32_t>(0), false), 0u);
}

TEST_F(ImageTest_1077, ByteSwap64Zero_1077) {
    EXPECT_EQ(Image::byteSwap(static_cast<uint64_t>(0), true), 0u);
    EXPECT_EQ(Image::byteSwap(static_cast<uint64_t>(0), false), 0u);
}

// ==================== Edge case: byteSwap with max values ====================

TEST_F(ImageTest_1077, ByteSwap16Max_1077) {
    uint16_t maxVal = 0xFFFF;
    EXPECT_EQ(Image::byteSwap(maxVal, true), 0xFFFF);
    EXPECT_EQ(Image::byteSwap(maxVal, false), 0xFFFF);
}

TEST_F(ImageTest_1077, ByteSwap32Max_1077) {
    uint32_t maxVal = 0xFFFFFFFF;
    EXPECT_EQ(Image::byteSwap(maxVal, true), 0xFFFFFFFFu);
    EXPECT_EQ(Image::byteSwap(maxVal, false), 0xFFFFFFFFu);
}
