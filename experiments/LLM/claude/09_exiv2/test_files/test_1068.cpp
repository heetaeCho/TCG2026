#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <sstream>
#include <memory>

// Since Image is abstract (readMetadata/writeMetadata are pure virtual in many subclasses),
// we need a concrete subclass for testing. We'll create a minimal test image class.
class TestImage : public Exiv2::Image {
public:
    TestImage(std::unique_ptr<Exiv2::BasicIo> io)
        : Exiv2::Image(Exiv2::ImageType::none, 0xFFFF, std::move(io)) {}

    void readMetadata() override {}
    void writeMetadata() override {}
    std::string mimeType() const override { return "application/test"; }
};

class ImageTest_1068 : public ::testing::Test {
protected:
    void SetUp() override {
        auto io = std::make_unique<Exiv2::MemIo>();
        image_ = std::make_unique<TestImage>(std::move(io));
    }

    std::unique_ptr<TestImage> image_;
};

// Test that exifData() returns a reference that can be used
TEST_F(ImageTest_1068, ExifDataReturnsReference_1068) {
    Exiv2::ExifData& exif = image_->exifData();
    EXPECT_TRUE(exif.empty());
}

// Test that iptcData() returns a reference
TEST_F(ImageTest_1068, IptcDataReturnsReference_1068) {
    Exiv2::IptcData& iptc = image_->iptcData();
    EXPECT_TRUE(iptc.empty());
}

// Test that xmpData() returns a reference
TEST_F(ImageTest_1068, XmpDataReturnsReference_1068) {
    Exiv2::XmpData& xmp = image_->xmpData();
    EXPECT_TRUE(xmp.empty());
}

// Test that xmpPacket() returns a reference to an initially empty string
TEST_F(ImageTest_1068, XmpPacketReturnsEmptyString_1068) {
    std::string& xmpPacket = image_->xmpPacket();
    EXPECT_TRUE(xmpPacket.empty());
}

// Test setExifData and clearExifData
TEST_F(ImageTest_1068, SetAndClearExifData_1068) {
    Exiv2::ExifData exifData;
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("TestMake");
    exifData.add(key, value.get());

    image_->setExifData(exifData);
    EXPECT_FALSE(image_->exifData().empty());

    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

// Test setIptcData and clearIptcData
TEST_F(ImageTest_1068, SetAndClearIptcData_1068) {
    Exiv2::IptcData iptcData;
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("TestCaption");
    iptcData.add(key, value.get());

    image_->setIptcData(iptcData);
    EXPECT_FALSE(image_->iptcData().empty());

    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

// Test setXmpData and clearXmpData
TEST_F(ImageTest_1068, SetAndClearXmpData_1068) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "TestTitle";

    image_->setXmpData(xmpData);
    EXPECT_FALSE(image_->xmpData().empty());

    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// Test setXmpPacket and clearXmpPacket
TEST_F(ImageTest_1068, SetAndClearXmpPacket_1068) {
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    image_->setXmpPacket(packet);
    EXPECT_EQ(image_->xmpPacket(), packet);

    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// Test setComment and clearComment
TEST_F(ImageTest_1068, SetAndClearComment_1068) {
    std::string comment = "Test comment";
    image_->setComment(comment);
    EXPECT_EQ(image_->comment(), comment);

    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

// Test comment is initially empty
TEST_F(ImageTest_1068, CommentInitiallyEmpty_1068) {
    EXPECT_TRUE(image_->comment().empty());
}

// Test pixelWidth and pixelHeight are initially zero
TEST_F(ImageTest_1068, PixelDimensionsInitiallyZero_1068) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// Test byteOrder initial value
TEST_F(ImageTest_1068, ByteOrderInitiallyInvalid_1068) {
    EXPECT_EQ(image_->byteOrder(), Exiv2::invalidByteOrder);
}

// Test setByteOrder
TEST_F(ImageTest_1068, SetByteOrder_1068) {
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);

    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::littleEndian);
}

// Test writeXmpFromPacket flag
TEST_F(ImageTest_1068, WriteXmpFromPacketFlag_1068) {
    EXPECT_FALSE(image_->writeXmpFromPacket());

    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());

    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// Test good() with valid MemIo
TEST_F(ImageTest_1068, GoodWithValidIo_1068) {
    // MemIo should be good by default
    EXPECT_TRUE(image_->good());
}

// Test mimeType
TEST_F(ImageTest_1068, MimeType_1068) {
    EXPECT_EQ(image_->mimeType(), "application/test");
}

// Test io() returns a reference
TEST_F(ImageTest_1068, IoReturnsReference_1068) {
    const Exiv2::BasicIo& io = image_->io();
    // Just verify we can access it without crashing
    (void)io;
}

// Test nativePreviews returns empty list initially
TEST_F(ImageTest_1068, NativePreviewsInitiallyEmpty_1068) {
    const Exiv2::NativePreviewList& previews = image_->nativePreviews();
    EXPECT_TRUE(previews.empty());
}

// Test clearMetadata clears all metadata
TEST_F(ImageTest_1068, ClearMetadataClearsAll_1068) {
    // Set some data
    Exiv2::ExifData exifData;
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("TestMake");
    exifData.add(key, value.get());
    image_->setExifData(exifData);

    image_->setComment("test comment");
    image_->setXmpPacket("<test/>");

    // Clear everything
    image_->clearMetadata();

    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_TRUE(image_->comment().empty());
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// Test setMetadata copies from another image
TEST_F(ImageTest_1068, SetMetadataFromAnotherImage_1068) {
    auto io2 = std::make_unique<Exiv2::MemIo>();
    TestImage source(std::move(io2));

    source.setComment("source comment");
    Exiv2::ExifData exifData;
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("SourceMake");
    exifData.add(key, value.get());
    source.setExifData(exifData);

    image_->setMetadata(source);

    EXPECT_EQ(image_->comment(), "source comment");
    EXPECT_FALSE(image_->exifData().empty());
}

// Test iccProfile initially undefined
TEST_F(ImageTest_1068, IccProfileInitiallyUndefined_1068) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

// Test setIccProfile and clearIccProfile
TEST_F(ImageTest_1068, SetAndClearIccProfile_1068) {
    // Create a minimal valid ICC profile header (at least 132 bytes with proper signature)
    // ICC profile signature at offset 36: 'acsp'
    std::vector<uint8_t> iccData(132, 0);
    // Set profile size
    iccData[0] = 0;
    iccData[1] = 0;
    iccData[2] = 0;
    iccData[3] = 132;
    // Set 'acsp' at offset 36
    iccData[36] = 'a';
    iccData[37] = 'c';
    iccData[38] = 's';
    iccData[39] = 'p';

    Exiv2::DataBuf buf(iccData.data(), iccData.size());
    image_->setIccProfile(std::move(buf), true);

    EXPECT_TRUE(image_->iccProfileDefined());

    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

// Test static byteSwap for uint16_t
TEST_F(ImageTest_1068, ByteSwap16_1068) {
    uint16_t val = 0x0102;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0201);

    uint16_t notSwapped = Exiv2::Image::byteSwap(val, false);
    EXPECT_EQ(notSwapped, val);
}

// Test static byteSwap for uint32_t
TEST_F(ImageTest_1068, ByteSwap32_1068) {
    uint32_t val = 0x01020304;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x04030201u);

    uint32_t notSwapped = Exiv2::Image::byteSwap(val, false);
    EXPECT_EQ(notSwapped, val);
}

// Test static byteSwap for uint64_t
TEST_F(ImageTest_1068, ByteSwap64_1068) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0807060504030201ULL);

    uint64_t notSwapped = Exiv2::Image::byteSwap(val, false);
    EXPECT_EQ(notSwapped, val);
}

// Test isBigEndianPlatform and isLittleEndianPlatform are complementary
TEST_F(ImageTest_1068, EndianPlatformConsistency_1068) {
    bool big = Exiv2::Image::isBigEndianPlatform();
    bool little = Exiv2::Image::isLittleEndianPlatform();
    // They should be mutually exclusive
    EXPECT_NE(big, little);
}

// Test isStringType
TEST_F(ImageTest_1068, IsStringType_1068) {
    // ASCII type = 2
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
    // LONG type = 4
    EXPECT_FALSE(Exiv2::Image::isStringType(4));
}

// Test isShortType
TEST_F(ImageTest_1068, IsShortType_1068) {
    // SHORT = 3
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
    // LONG = 4
    EXPECT_FALSE(Exiv2::Image::isShortType(4));
}

// Test isLongType
TEST_F(ImageTest_1068, IsLongType_1068) {
    // LONG = 4
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
    // SHORT = 3
    EXPECT_FALSE(Exiv2::Image::isLongType(3));
}

// Test isRationalType
TEST_F(ImageTest_1068, IsRationalType_1068) {
    // RATIONAL = 5
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
    // LONG = 4
    EXPECT_FALSE(Exiv2::Image::isRationalType(4));
}

// Test is2ByteType
TEST_F(ImageTest_1068, Is2ByteType_1068) {
    // SHORT = 3 is 2 bytes
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
    // LONG = 4 is not 2 bytes
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

// Test is4ByteType
TEST_F(ImageTest_1068, Is4ByteType_1068) {
    // LONG = 4 is 4 bytes
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
    // SHORT = 3 is not 4 bytes
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
}

// Test is8ByteType
TEST_F(ImageTest_1068, Is8ByteType_1068) {
    // RATIONAL = 5 is 8 bytes
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
    // SHORT = 3 is not 8 bytes
    EXPECT_FALSE(Exiv2::Image::is8ByteType(3));
}

// Test byteSwap2 with DataBuf
TEST_F(ImageTest_1068, ByteSwap2WithDataBuf_1068) {
    std::vector<uint8_t> data = {0x01, 0x02, 0x03, 0x04};
    Exiv2::DataBuf buf(data.data(), data.size());

    uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
    uint16_t notSwapped = Exiv2::Image::byteSwap2(buf, 0, false);

    // When not swapping, should read as-is in memory order
    // When swapping, bytes should be reversed
    EXPECT_NE(swapped, notSwapped);
}

// Test byteSwap4 with DataBuf
TEST_F(ImageTest_1068, ByteSwap4WithDataBuf_1068) {
    std::vector<uint8_t> data = {0x01, 0x02, 0x03, 0x04};
    Exiv2::DataBuf buf(data.data(), data.size());

    uint32_t swapped = Exiv2::Image::byteSwap4(buf, 0, true);
    uint32_t notSwapped = Exiv2::Image::byteSwap4(buf, 0, false);

    EXPECT_NE(swapped, notSwapped);
}

// Test byteSwap8 with DataBuf
TEST_F(ImageTest_1068, ByteSwap8WithDataBuf_1068) {
    std::vector<uint8_t> data = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    Exiv2::DataBuf buf(data.data(), data.size());

    uint64_t swapped = Exiv2::Image::byteSwap8(buf, 0, true);
    uint64_t notSwapped = Exiv2::Image::byteSwap8(buf, 0, false);

    EXPECT_NE(swapped, notSwapped);
}

// Test imageType
TEST_F(ImageTest_1068, ImageTypeReturnsCorrectType_1068) {
    EXPECT_EQ(image_->imageType(), Exiv2::ImageType::none);
}

// Test setTypeSupported
TEST_F(ImageTest_1068, SetTypeSupported_1068) {
    image_->setTypeSupported(Exiv2::ImageType::jpeg, 0x0001);
    EXPECT_EQ(image_->imageType(), Exiv2::ImageType::jpeg);
}

// Test exifData modification through reference
TEST_F(ImageTest_1068, ExifDataModifiableThroughReference_1068) {
    Exiv2::ExifData& exif = image_->exifData();
    EXPECT_TRUE(exif.empty());

    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("Canon");
    exif.add(key, value.get());

    EXPECT_FALSE(image_->exifData().empty());
}

// Test setComment with empty string
TEST_F(ImageTest_1068, SetEmptyComment_1068) {
    image_->setComment("");
    EXPECT_EQ(image_->comment(), "");
}

// Test setComment with long string
TEST_F(ImageTest_1068, SetLongComment_1068) {
    std::string longComment(10000, 'x');
    image_->setComment(longComment);
    EXPECT_EQ(image_->comment(), longComment);
}

// Test byteSwap with zero
TEST_F(ImageTest_1068, ByteSwapZero_1068) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint32_t>(0), true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint64_t>(0), true), 0u);
}

// Test byteSwap with max values
TEST_F(ImageTest_1068, ByteSwapMaxValues_1068) {
    uint16_t max16 = 0xFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(max16, true), 0xFFFF);

    uint32_t max32 = 0xFFFFFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(max32, true), 0xFFFFFFFF);

    uint64_t max64 = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(max64, true), 0xFFFFFFFFFFFFFFFFULL);
}

// Test double swap returns original value
TEST_F(ImageTest_1068, DoubleSwapReturnsOriginal16_1068) {
    uint16_t val = 0x1234;
    uint16_t result = Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true);
    EXPECT_EQ(result, val);
}

TEST_F(ImageTest_1068, DoubleSwapReturnsOriginal32_1068) {
    uint32_t val = 0x12345678;
    uint32_t result = Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true);
    EXPECT_EQ(result, val);
}

TEST_F(ImageTest_1068, DoubleSwapReturnsOriginal64_1068) {
    uint64_t val = 0x123456789ABCDEF0ULL;
    uint64_t result = Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true);
    EXPECT_EQ(result, val);
}

// Test setIccProfile with bTestValid=false (should not validate)
TEST_F(ImageTest_1068, SetIccProfileNoValidation_1068) {
    std::vector<uint8_t> data(10, 0);
    Exiv2::DataBuf buf(data.data(), data.size());
    image_->setIccProfile(std::move(buf), false);
    EXPECT_TRUE(image_->iccProfileDefined());
}

// Test printStructure doesn't crash
TEST_F(ImageTest_1068, PrintStructureDoesNotCrash_1068) {
    std::ostringstream oss;
    EXPECT_NO_THROW(image_->printStructure(oss, Exiv2::kpsNone, 0));
}

// Test isLongLongType
TEST_F(ImageTest_1068, IsLongLongType_1068) {
    // Type 16 is typically LONG8 in TIFF BigTIFF
    // Type 4 (LONG) should not be LongLong
    EXPECT_FALSE(Exiv2::Image::isLongLongType(4));
}
