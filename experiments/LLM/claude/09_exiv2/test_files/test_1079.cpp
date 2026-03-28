#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>

#include <memory>
#include <sstream>

// We need a concrete Image subclass for testing since Image has pure virtual methods
// (readMetadata, writeMetadata). We'll create a minimal test subclass.
namespace {

class TestImage : public Exiv2::Image {
public:
    TestImage(std::unique_ptr<Exiv2::BasicIo> io)
        : Exiv2::Image(Exiv2::ImageType::none, 
                        static_cast<uint16_t>(Exiv2::MetadataId::mdExif) |
                        static_cast<uint16_t>(Exiv2::MetadataId::mdIptc) |
                        static_cast<uint16_t>(Exiv2::MetadataId::mdXmp) |
                        static_cast<uint16_t>(Exiv2::MetadataId::mdComment),
                        std::move(io)) {}

    void readMetadata() override {}
    void writeMetadata() override {}
};

std::unique_ptr<TestImage> createTestImage() {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<TestImage>(std::move(io));
}

} // anonymous namespace

class ImageTest_1079 : public ::testing::Test {
protected:
    void SetUp() override {
        image_ = createTestImage();
    }

    std::unique_ptr<TestImage> image_;
};

// ============================================================
// clearXmpData tests
// ============================================================

TEST_F(ImageTest_1079, ClearXmpDataMakesXmpDataEmpty_1079) {
    // Add some XMP data first, then clear
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test Title";
    image_->setXmpData(xmpData);
    ASSERT_FALSE(image_->xmpData().empty());

    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageTest_1079, ClearXmpDataSetsWriteXmpFromPacketFalse_1079) {
    // Set writeXmpFromPacket to true, then clearXmpData should set it to false
    image_->writeXmpFromPacket(true);
    ASSERT_TRUE(image_->writeXmpFromPacket());

    image_->clearXmpData();
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1079, ClearXmpDataOnAlreadyEmptyData_1079) {
    // Clearing already empty XMP data should not cause issues
    EXPECT_TRUE(image_->xmpData().empty());
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1079, ClearXmpDataCountBecomesZero_1079) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Title1";
    xmpData["Xmp.dc.creator"] = "Creator1";
    image_->setXmpData(xmpData);
    ASSERT_GT(image_->xmpData().count(), 0);

    image_->clearXmpData();
    EXPECT_EQ(image_->xmpData().count(), 0);
}

// ============================================================
// setXmpData / xmpData tests
// ============================================================

TEST_F(ImageTest_1079, SetXmpDataAndRetrieve_1079) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "My Title";
    image_->setXmpData(xmpData);
    EXPECT_FALSE(image_->xmpData().empty());
}

TEST_F(ImageTest_1079, XmpDataInitiallyEmpty_1079) {
    EXPECT_TRUE(image_->xmpData().empty());
}

// ============================================================
// writeXmpFromPacket tests
// ============================================================

TEST_F(ImageTest_1079, WriteXmpFromPacketDefaultFalse_1079) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1079, WriteXmpFromPacketSetTrue_1079) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1079, WriteXmpFromPacketSetFalse_1079) {
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// ============================================================
// clearExifData tests
// ============================================================

TEST_F(ImageTest_1079, ClearExifDataMakesExifEmpty_1079) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    ASSERT_FALSE(image_->exifData().empty());

    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

// ============================================================
// clearIptcData tests
// ============================================================

TEST_F(ImageTest_1079, ClearIptcDataMakesIptcEmpty_1079) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Headline"] = "Test Headline";
    image_->setIptcData(iptcData);
    ASSERT_FALSE(image_->iptcData().empty());

    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

// ============================================================
// clearComment tests
// ============================================================

TEST_F(ImageTest_1079, ClearCommentMakesCommentEmpty_1079) {
    image_->setComment("Test Comment");
    ASSERT_EQ(image_->comment(), "Test Comment");

    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1079, SetCommentAndRetrieve_1079) {
    image_->setComment("Hello World");
    EXPECT_EQ(image_->comment(), "Hello World");
}

// ============================================================
// clearMetadata tests
// ============================================================

TEST_F(ImageTest_1079, ClearMetadataClearsAll_1079) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);

    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Headline"] = "Headline";
    image_->setIptcData(iptcData);

    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Title";
    image_->setXmpData(xmpData);

    image_->setComment("A comment");

    image_->clearMetadata();

    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_TRUE(image_->comment().empty());
}

// ============================================================
// setXmpPacket / clearXmpPacket tests
// ============================================================

TEST_F(ImageTest_1079, SetXmpPacketAndRetrieve_1079) {
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    image_->setXmpPacket(packet);
    EXPECT_EQ(image_->xmpPacket(), packet);
}

TEST_F(ImageTest_1079, ClearXmpPacketMakesPacketEmpty_1079) {
    image_->setXmpPacket("<x:xmpmeta>test</x:xmpmeta>");
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// ============================================================
// byteOrder tests
// ============================================================

TEST_F(ImageTest_1079, ByteOrderDefaultInvalid_1079) {
    EXPECT_EQ(image_->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageTest_1079, SetByteOrderBigEndian_1079) {
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);
}

TEST_F(ImageTest_1079, SetByteOrderLittleEndian_1079) {
    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::littleEndian);
}

// ============================================================
// pixelWidth / pixelHeight tests
// ============================================================

TEST_F(ImageTest_1079, PixelWidthDefaultZero_1079) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(ImageTest_1079, PixelHeightDefaultZero_1079) {
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// ============================================================
// good() tests
// ============================================================

TEST_F(ImageTest_1079, GoodReturnsTrueForValidIo_1079) {
    // MemIo should be good
    EXPECT_TRUE(image_->good());
}

// ============================================================
// Static helper function tests
// ============================================================

TEST_F(ImageTest_1079, IsBigOrLittleEndianPlatform_1079) {
    // One of these must be true
    bool big = Exiv2::Image::isBigEndianPlatform();
    bool little = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_TRUE(big || little);
    EXPECT_NE(big, little);
}

TEST_F(ImageTest_1079, ByteSwap16NoSwap_1079) {
    uint16_t val = 0x0102;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1079, ByteSwap16WithSwap_1079) {
    uint16_t val = 0x0102;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0201);
}

TEST_F(ImageTest_1079, ByteSwap32NoSwap_1079) {
    uint32_t val = 0x01020304;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1079, ByteSwap32WithSwap_1079) {
    uint32_t val = 0x01020304;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x04030201u);
}

TEST_F(ImageTest_1079, ByteSwap64NoSwap_1079) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1079, ByteSwap64WithSwap_1079) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0807060504030201ULL);
}

// ============================================================
// isStringType / isShortType / isLongType etc. static tests
// ============================================================

TEST_F(ImageTest_1079, IsStringTypeForAscii_1079) {
    // TIFF ASCII type = 2
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
}

TEST_F(ImageTest_1079, IsShortTypeForShort_1079) {
    // TIFF SHORT type = 3
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
}

TEST_F(ImageTest_1079, IsLongTypeForLong_1079) {
    // TIFF LONG type = 4
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
}

TEST_F(ImageTest_1079, IsRationalTypeForRational_1079) {
    // TIFF RATIONAL type = 5
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
}

TEST_F(ImageTest_1079, Is2ByteTypeForShort_1079) {
    // SHORT = 3 is 2 bytes
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
}

TEST_F(ImageTest_1079, Is4ByteTypeForLong_1079) {
    // LONG = 4 is 4 bytes
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
}

TEST_F(ImageTest_1079, Is8ByteTypeForRational_1079) {
    // RATIONAL = 5 is 8 bytes
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
}

// ============================================================
// ICC Profile tests
// ============================================================

TEST_F(ImageTest_1079, IccProfileNotDefinedByDefault_1079) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1079, ClearIccProfile_1079) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

// ============================================================
// nativePreviews tests
// ============================================================

TEST_F(ImageTest_1079, NativePreviewsInitiallyEmpty_1079) {
    EXPECT_TRUE(image_->nativePreviews().empty());
}

// ============================================================
// setMetadata tests
// ============================================================

TEST_F(ImageTest_1079, SetMetadataFromAnotherImage_1079) {
    auto sourceImage = createTestImage();
    sourceImage->setComment("Source Comment");

    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "SourceMake";
    sourceImage->setExifData(exifData);

    image_->setMetadata(*sourceImage);

    EXPECT_EQ(image_->comment(), "Source Comment");
    EXPECT_FALSE(image_->exifData().empty());
}

// ============================================================
// ClearXmpData combined behavior test
// ============================================================

TEST_F(ImageTest_1079, ClearXmpDataAfterSettingPacketFlagAndData_1079) {
    // Set writeXmpFromPacket to true and add XMP data
    image_->writeXmpFromPacket(true);
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.subject"] = "Subject";
    xmpData["Xmp.dc.description"] = "Description";
    image_->setXmpData(xmpData);

    ASSERT_TRUE(image_->writeXmpFromPacket());
    ASSERT_FALSE(image_->xmpData().empty());
    ASSERT_GE(image_->xmpData().count(), 2);

    // Now clear - both data and flag should be reset
    image_->clearXmpData();

    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_EQ(image_->xmpData().count(), 0);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1079, ClearXmpDataMultipleTimes_1079) {
    // Clearing multiple times should be safe
    image_->clearXmpData();
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1079, ClearXmpDataDoesNotAffectExifData_1079) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);

    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Title";
    image_->setXmpData(xmpData);

    image_->clearXmpData();

    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_FALSE(image_->exifData().empty());
}

TEST_F(ImageTest_1079, ClearXmpDataDoesNotAffectIptcData_1079) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Headline"] = "Headline";
    image_->setIptcData(iptcData);

    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Title";
    image_->setXmpData(xmpData);

    image_->clearXmpData();

    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_FALSE(image_->iptcData().empty());
}

TEST_F(ImageTest_1079, ClearXmpDataDoesNotAffectComment_1079) {
    image_->setComment("My Comment");

    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Title";
    image_->setXmpData(xmpData);

    image_->clearXmpData();

    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_EQ(image_->comment(), "My Comment");
}
