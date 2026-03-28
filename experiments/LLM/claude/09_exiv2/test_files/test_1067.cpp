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

// We need a concrete subclass of Image since Image is abstract (has pure virtual methods)
// We'll use a minimal test image class that implements the required virtual methods
class TestImage : public Exiv2::Image {
public:
    TestImage(std::unique_ptr<Exiv2::BasicIo> io)
        : Exiv2::Image(Exiv2::ImageType::none, 0xFFFF, std::move(io)) {}

    void readMetadata() override {}
    void writeMetadata() override {}
    std::string mimeType() const override { return "application/octet-stream"; }
};

class ImageTest_1067 : public ::testing::Test {
protected:
    void SetUp() override {
        auto io = std::make_unique<Exiv2::MemIo>();
        image_ = std::make_unique<TestImage>(std::move(io));
    }

    std::unique_ptr<TestImage> image_;
};

// ==================== clearMetadata Tests ====================

TEST_F(ImageTest_1067, ClearMetadataClearsExifData_1067) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    ASSERT_FALSE(image_->exifData().empty());

    image_->clearMetadata();
    EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(ImageTest_1067, ClearMetadataClearsIptcData_1067) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "TestCaption";
    image_->setIptcData(iptcData);
    ASSERT_FALSE(image_->iptcData().empty());

    image_->clearMetadata();
    EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageTest_1067, ClearMetadataClearsXmpData_1067) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "TestTitle";
    image_->setXmpData(xmpData);
    ASSERT_FALSE(image_->xmpData().empty());

    image_->clearMetadata();
    EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageTest_1067, ClearMetadataClearsXmpPacket_1067) {
    image_->setXmpPacket("<xmp>test</xmp>");
    ASSERT_FALSE(image_->xmpPacket().empty());

    image_->clearMetadata();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageTest_1067, ClearMetadataClearsComment_1067) {
    image_->setComment("Test Comment");
    ASSERT_EQ(image_->comment(), "Test Comment");

    image_->clearMetadata();
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1067, ClearMetadataClearsIccProfile_1067) {
    // Create a minimal ICC profile-like data
    const uint8_t iccData[] = {
        0x00, 0x00, 0x00, 0x18, // Profile size (24 bytes minimum for test)
        'a', 'c', 's', 'p',     // Signature at offset 36... simplified
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
    };
    Exiv2::DataBuf buf(iccData, sizeof(iccData));
    image_->setIccProfile(std::move(buf), false);

    image_->clearMetadata();
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1067, ClearMetadataOnAlreadyClearedImage_1067) {
    // Should not crash when called on an image with no metadata
    EXPECT_NO_THROW(image_->clearMetadata());
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_TRUE(image_->xmpPacket().empty());
    EXPECT_TRUE(image_->comment().empty());
}

// ==================== Individual Clear Methods Tests ====================

TEST_F(ImageTest_1067, ClearExifDataOnly_1067) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    image_->setComment("Keep this");

    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_EQ(image_->comment(), "Keep this");
}

TEST_F(ImageTest_1067, ClearIptcDataOnly_1067) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "TestCaption";
    image_->setIptcData(iptcData);
    image_->setComment("Keep this");

    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_EQ(image_->comment(), "Keep this");
}

TEST_F(ImageTest_1067, ClearXmpDataOnly_1067) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "TestTitle";
    image_->setXmpData(xmpData);
    image_->setComment("Keep this");

    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_EQ(image_->comment(), "Keep this");
}

TEST_F(ImageTest_1067, ClearXmpPacketOnly_1067) {
    image_->setXmpPacket("some xmp");
    image_->setComment("Keep this");

    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
    EXPECT_EQ(image_->comment(), "Keep this");
}

TEST_F(ImageTest_1067, ClearCommentOnly_1067) {
    image_->setComment("Test Comment");
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);

    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
    EXPECT_FALSE(image_->exifData().empty());
}

TEST_F(ImageTest_1067, ClearIccProfileOnly_1067) {
    Exiv2::DataBuf buf(24);
    image_->setIccProfile(std::move(buf), false);
    image_->setComment("Keep this");

    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
    EXPECT_EQ(image_->comment(), "Keep this");
}

// ==================== Set/Get Methods Tests ====================

TEST_F(ImageTest_1067, SetAndGetExifData_1067) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "Canon";
    image_->setExifData(exifData);

    EXPECT_FALSE(image_->exifData().empty());
}

TEST_F(ImageTest_1067, SetAndGetIptcData_1067) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "My Caption";
    image_->setIptcData(iptcData);

    EXPECT_FALSE(image_->iptcData().empty());
}

TEST_F(ImageTest_1067, SetAndGetXmpData_1067) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "My Title";
    image_->setXmpData(xmpData);

    EXPECT_FALSE(image_->xmpData().empty());
}

TEST_F(ImageTest_1067, SetAndGetXmpPacket_1067) {
    std::string packet = "<xmp>test packet</xmp>";
    image_->setXmpPacket(packet);

    EXPECT_EQ(image_->xmpPacket(), packet);
}

TEST_F(ImageTest_1067, SetAndGetComment_1067) {
    std::string comment = "This is a test comment";
    image_->setComment(comment);

    EXPECT_EQ(image_->comment(), comment);
}

TEST_F(ImageTest_1067, SetEmptyComment_1067) {
    image_->setComment("");
    EXPECT_TRUE(image_->comment().empty());
}

// ==================== ByteOrder Tests ====================

TEST_F(ImageTest_1067, DefaultByteOrderIsInvalid_1067) {
    EXPECT_EQ(image_->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageTest_1067, SetByteOrderBigEndian_1067) {
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);
}

TEST_F(ImageTest_1067, SetByteOrderLittleEndian_1067) {
    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::littleEndian);
}

// ==================== WriteXmpFromPacket Tests ====================

TEST_F(ImageTest_1067, DefaultWriteXmpFromPacketIsFalse_1067) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1067, SetWriteXmpFromPacketTrue_1067) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1067, SetWriteXmpFromPacketFalse_1067) {
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// ==================== Pixel Dimensions Tests ====================

TEST_F(ImageTest_1067, DefaultPixelWidthIsZero_1067) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(ImageTest_1067, DefaultPixelHeightIsZero_1067) {
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// ==================== Static Method Tests ====================

TEST_F(ImageTest_1067, PlatformEndianness_1067) {
    // One of these must be true
    bool big = Exiv2::Image::isBigEndianPlatform();
    bool little = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_TRUE(big || little);
    EXPECT_NE(big, little);
}

TEST_F(ImageTest_1067, ByteSwap16NoSwap_1067) {
    uint16_t value = 0x0102;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, false), 0x0102);
}

TEST_F(ImageTest_1067, ByteSwap16WithSwap_1067) {
    uint16_t value = 0x0102;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0x0201);
}

TEST_F(ImageTest_1067, ByteSwap32NoSwap_1067) {
    uint32_t value = 0x01020304;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, false), 0x01020304u);
}

TEST_F(ImageTest_1067, ByteSwap32WithSwap_1067) {
    uint32_t value = 0x01020304;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0x04030201u);
}

TEST_F(ImageTest_1067, ByteSwap64NoSwap_1067) {
    uint64_t value = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, false), 0x0102030405060708ULL);
}

TEST_F(ImageTest_1067, ByteSwap64WithSwap_1067) {
    uint64_t value = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0x0807060504030201ULL);
}

TEST_F(ImageTest_1067, ByteSwap16Zero_1067) {
    uint16_t value = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0);
    EXPECT_EQ(Exiv2::Image::byteSwap(value, false), 0);
}

TEST_F(ImageTest_1067, ByteSwap32Zero_1067) {
    uint32_t value = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(value, false), 0u);
}

TEST_F(ImageTest_1067, ByteSwap64Zero_1067) {
    uint64_t value = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0ULL);
    EXPECT_EQ(Exiv2::Image::byteSwap(value, false), 0ULL);
}

// ==================== Type Check Static Methods ====================

TEST_F(ImageTest_1067, IsStringType_1067) {
    // TIFF ASCII type is 2
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
    EXPECT_FALSE(Exiv2::Image::isStringType(3)); // SHORT
}

TEST_F(ImageTest_1067, IsShortType_1067) {
    // TIFF SHORT type is 3
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
    EXPECT_FALSE(Exiv2::Image::isShortType(2));
}

TEST_F(ImageTest_1067, IsLongType_1067) {
    // TIFF LONG type is 4
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
    EXPECT_FALSE(Exiv2::Image::isLongType(3));
}

TEST_F(ImageTest_1067, IsRationalType_1067) {
    // TIFF RATIONAL type is 5
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
    EXPECT_FALSE(Exiv2::Image::isRationalType(4));
}

TEST_F(ImageTest_1067, Is2ByteType_1067) {
    // SHORT (3) and SSHORT (8) are 2-byte types
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
    EXPECT_TRUE(Exiv2::Image::is2ByteType(8));
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

TEST_F(ImageTest_1067, Is4ByteType_1067) {
    // LONG (4) and SLONG (9) are 4-byte types
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
    EXPECT_TRUE(Exiv2::Image::is4ByteType(9));
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
}

TEST_F(ImageTest_1067, Is8ByteType_1067) {
    // RATIONAL (5), SRATIONAL (10) are 8-byte types
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
    EXPECT_TRUE(Exiv2::Image::is8ByteType(10));
    EXPECT_FALSE(Exiv2::Image::is8ByteType(4));
}

// ==================== Good Method Test ====================

TEST_F(ImageTest_1067, GoodReturnsTrueForValidIo_1067) {
    EXPECT_TRUE(image_->good());
}

// ==================== MimeType Test ====================

TEST_F(ImageTest_1067, MimeTypeReturnsExpectedValue_1067) {
    EXPECT_EQ(image_->mimeType(), "application/octet-stream");
}

// ==================== ImageType Test ====================

TEST_F(ImageTest_1067, ImageTypeReturnsCorrectType_1067) {
    EXPECT_EQ(image_->imageType(), Exiv2::ImageType::none);
}

// ==================== setMetadata Test ====================

TEST_F(ImageTest_1067, SetMetadataCopiesFromOtherImage_1067) {
    auto io2 = std::make_unique<Exiv2::MemIo>();
    TestImage other(std::move(io2));

    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "Nikon";
    other.setExifData(exifData);
    other.setComment("Other comment");

    image_->setMetadata(other);
    EXPECT_FALSE(image_->exifData().empty());
    EXPECT_EQ(image_->comment(), "Other comment");
}

// ==================== IccProfile Tests ====================

TEST_F(ImageTest_1067, IccProfileNotDefinedByDefault_1067) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1067, SetIccProfileMakesItDefined_1067) {
    Exiv2::DataBuf buf(128);
    std::memset(buf.data(), 0, buf.size());
    image_->setIccProfile(std::move(buf), false);
    EXPECT_TRUE(image_->iccProfileDefined());
}

// ==================== ByteSwap2/4/8 with DataBuf Tests ====================

TEST_F(ImageTest_1067, ByteSwap2WithDataBuf_1067) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x01;
    buf.data()[1] = 0x02;

    uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);

    // One should be 0x0102 and the other 0x0201
    EXPECT_NE(noSwap, swapped);
}

TEST_F(ImageTest_1067, ByteSwap4WithDataBuf_1067) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x01;
    buf.data()[1] = 0x02;
    buf.data()[2] = 0x03;
    buf.data()[3] = 0x04;

    uint32_t noSwap = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t swapped = Exiv2::Image::byteSwap4(buf, 0, true);

    EXPECT_NE(noSwap, swapped);
}

TEST_F(ImageTest_1067, ByteSwap8WithDataBuf_1067) {
    Exiv2::DataBuf buf(16);
    for (size_t i = 0; i < 8; i++) {
        buf.data()[i] = static_cast<uint8_t>(i + 1);
    }

    uint64_t noSwap = Exiv2::Image::byteSwap8(buf, 0, false);
    uint64_t swapped = Exiv2::Image::byteSwap8(buf, 0, true);

    EXPECT_NE(noSwap, swapped);
}

// ==================== NativePreviews Test ====================

TEST_F(ImageTest_1067, NativePreviewsEmptyByDefault_1067) {
    EXPECT_TRUE(image_->nativePreviews().empty());
}

// ==================== Io Accessor Test ====================

TEST_F(ImageTest_1067, IoAccessorReturnsValidReference_1067) {
    EXPECT_NO_THROW(image_->io());
}

// ==================== Multiple Clear Calls Test ====================

TEST_F(ImageTest_1067, MultipleClearMetadataCalls_1067) {
    image_->setComment("Test");
    image_->clearMetadata();
    image_->clearMetadata(); // Second call should be safe
    EXPECT_TRUE(image_->comment().empty());
}

// ==================== Set After Clear Test ====================

TEST_F(ImageTest_1067, SetCommentAfterClearMetadata_1067) {
    image_->setComment("First");
    image_->clearMetadata();
    image_->setComment("Second");
    EXPECT_EQ(image_->comment(), "Second");
}

TEST_F(ImageTest_1067, SetExifDataAfterClearMetadata_1067) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "Canon";
    image_->setExifData(exifData);
    image_->clearMetadata();

    Exiv2::ExifData newExifData;
    newExifData["Exif.Image.Model"] = "EOS 5D";
    image_->setExifData(newExifData);
    EXPECT_FALSE(image_->exifData().empty());
}

// ==================== ByteSwap boundary tests ====================

TEST_F(ImageTest_1067, ByteSwap16MaxValue_1067) {
    uint16_t value = 0xFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0xFFFF);
    EXPECT_EQ(Exiv2::Image::byteSwap(value, false), 0xFFFF);
}

TEST_F(ImageTest_1067, ByteSwap32MaxValue_1067) {
    uint32_t value = 0xFFFFFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0xFFFFFFFFu);
    EXPECT_EQ(Exiv2::Image::byteSwap(value, false), 0xFFFFFFFFu);
}

TEST_F(ImageTest_1067, ByteSwap64MaxValue_1067) {
    uint64_t value = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0xFFFFFFFFFFFFFFFFULL);
    EXPECT_EQ(Exiv2::Image::byteSwap(value, false), 0xFFFFFFFFFFFFFFFFULL);
}

// ==================== Double swap equals identity ====================

TEST_F(ImageTest_1067, DoubleByteSwap16IsIdentity_1067) {
    uint16_t value = 0x1234;
    uint16_t swapped = Exiv2::Image::byteSwap(value, true);
    uint16_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, value);
}

TEST_F(ImageTest_1067, DoubleByteSwap32IsIdentity_1067) {
    uint32_t value = 0x12345678;
    uint32_t swapped = Exiv2::Image::byteSwap(value, true);
    uint32_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, value);
}

TEST_F(ImageTest_1067, DoubleByteSwap64IsIdentity_1067) {
    uint64_t value = 0x123456789ABCDEF0ULL;
    uint64_t swapped = Exiv2::Image::byteSwap(value, true);
    uint64_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, value);
}
