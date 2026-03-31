#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstring>

#include "exiv2/image.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/types.hpp"

// We need a concrete Image subclass since Image has pure virtual methods
// or at least we need to instantiate it. We'll use a minimal approach.
// Since Image requires a BasicIo, we'll use MemIo.

namespace {

// Helper to create an Image instance for testing.
// We use a concrete subclass or rely on a factory. Since Image itself
// can be constructed with the right parameters, but it has virtual methods
// like readMetadata/writeMetadata that might be pure virtual or have
// default implementations. Let's create a test subclass.

class TestImage : public Exiv2::Image {
public:
    TestImage()
        : Exiv2::Image(Exiv2::ImageType::none, 0xFFFF, std::make_unique<Exiv2::MemIo>()) {}

    void readMetadata() override {}
    void writeMetadata() override {}
};

class ImageTest_1085 : public ::testing::Test {
protected:
    void SetUp() override {
        image_ = std::make_unique<TestImage>();
    }

    std::unique_ptr<TestImage> image_;
};

// Test that a newly created image has no ICC profile defined
TEST_F(ImageTest_1085, InitialIccProfileIsEmpty_1085) {
    EXPECT_FALSE(image_->iccProfileDefined());
    EXPECT_TRUE(image_->iccProfile().empty());
    EXPECT_EQ(image_->iccProfile().size(), 0u);
}

// Test appending ICC profile data with bTestValid = false
TEST_F(ImageTest_1085, AppendIccProfileAddsData_1085) {
    const uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
    image_->appendIccProfile(data, sizeof(data), false);

    EXPECT_TRUE(image_->iccProfileDefined());
    EXPECT_EQ(image_->iccProfile().size(), 4u);
    EXPECT_EQ(std::memcmp(image_->iccProfile().c_data(0), data, sizeof(data)), 0);
}

// Test appending ICC profile data multiple times accumulates
TEST_F(ImageTest_1085, AppendIccProfileMultipleTimes_1085) {
    const uint8_t data1[] = {0x01, 0x02};
    const uint8_t data2[] = {0x03, 0x04, 0x05};

    image_->appendIccProfile(data1, sizeof(data1), false);
    image_->appendIccProfile(data2, sizeof(data2), false);

    EXPECT_EQ(image_->iccProfile().size(), 5u);
    EXPECT_EQ(image_->iccProfile().read_uint8(0), 0x01);
    EXPECT_EQ(image_->iccProfile().read_uint8(1), 0x02);
    EXPECT_EQ(image_->iccProfile().read_uint8(2), 0x03);
    EXPECT_EQ(image_->iccProfile().read_uint8(3), 0x04);
    EXPECT_EQ(image_->iccProfile().read_uint8(4), 0x05);
}

// Test appending zero-size data
TEST_F(ImageTest_1085, AppendIccProfileZeroSize_1085) {
    const uint8_t data[] = {0x01};
    image_->appendIccProfile(data, 0, false);

    // Should remain empty or at least size 0 appended
    EXPECT_EQ(image_->iccProfile().size(), 0u);
}

// Test clearIccProfile clears the profile
TEST_F(ImageTest_1085, ClearIccProfile_1085) {
    const uint8_t data[] = {0x01, 0x02, 0x03};
    image_->appendIccProfile(data, sizeof(data), false);
    EXPECT_TRUE(image_->iccProfileDefined());

    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
    EXPECT_EQ(image_->iccProfile().size(), 0u);
}

// Test setIccProfile with valid DataBuf
TEST_F(ImageTest_1085, SetIccProfile_1085) {
    Exiv2::DataBuf buf(10);
    for (size_t i = 0; i < 10; i++) {
        buf.write_uint8(i, static_cast<uint8_t>(i));
    }

    image_->setIccProfile(std::move(buf), false);
    EXPECT_TRUE(image_->iccProfileDefined());
    EXPECT_EQ(image_->iccProfile().size(), 10u);
    EXPECT_EQ(image_->iccProfile().read_uint8(0), 0);
    EXPECT_EQ(image_->iccProfile().read_uint8(9), 9);
}

// Test setIccProfile followed by append
TEST_F(ImageTest_1085, SetThenAppendIccProfile_1085) {
    Exiv2::DataBuf buf(3);
    buf.write_uint8(0, 0xAA);
    buf.write_uint8(1, 0xBB);
    buf.write_uint8(2, 0xCC);

    image_->setIccProfile(std::move(buf), false);
    EXPECT_EQ(image_->iccProfile().size(), 3u);

    const uint8_t extra[] = {0xDD, 0xEE};
    image_->appendIccProfile(extra, sizeof(extra), false);
    EXPECT_EQ(image_->iccProfile().size(), 5u);
    EXPECT_EQ(image_->iccProfile().read_uint8(3), 0xDD);
    EXPECT_EQ(image_->iccProfile().read_uint8(4), 0xEE);
}

// Test initial pixel dimensions
TEST_F(ImageTest_1085, InitialPixelDimensions_1085) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// Test byteOrder default
TEST_F(ImageTest_1085, DefaultByteOrder_1085) {
    EXPECT_EQ(image_->byteOrder(), Exiv2::invalidByteOrder);
}

// Test setByteOrder
TEST_F(ImageTest_1085, SetByteOrder_1085) {
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);

    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::littleEndian);
}

// Test comment
TEST_F(ImageTest_1085, SetAndClearComment_1085) {
    EXPECT_EQ(image_->comment(), "");

    image_->setComment("Hello World");
    EXPECT_EQ(image_->comment(), "Hello World");

    image_->clearComment();
    EXPECT_EQ(image_->comment(), "");
}

// Test writeXmpFromPacket flag
TEST_F(ImageTest_1085, WriteXmpFromPacketFlag_1085) {
    EXPECT_FALSE(image_->writeXmpFromPacket());

    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());

    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// Test clearMetadata clears everything
TEST_F(ImageTest_1085, ClearMetadata_1085) {
    image_->setComment("test comment");
    const uint8_t data[] = {0x01};
    image_->appendIccProfile(data, sizeof(data), false);

    image_->clearMetadata();

    EXPECT_EQ(image_->comment(), "");
    EXPECT_FALSE(image_->iccProfileDefined());
}

// Test good() depends on io state
TEST_F(ImageTest_1085, GoodReflectsIoState_1085) {
    // A MemIo with no data should still be "good" in some sense
    // This tests the observable behavior
    EXPECT_TRUE(image_->good());
}

// Test static helper: isBigEndianPlatform and isLittleEndianPlatform
TEST_F(ImageTest_1085, EndianPlatformConsistency_1085) {
    // Exactly one should be true
    bool big = Exiv2::Image::isBigEndianPlatform();
    bool little = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_NE(big, little);
}

// Test static byteSwap for uint16_t
TEST_F(ImageTest_1085, ByteSwap16_1085) {
    uint16_t val = 0x0102;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0201);

    uint16_t notSwapped = Exiv2::Image::byteSwap(val, false);
    EXPECT_EQ(notSwapped, val);
}

// Test static byteSwap for uint32_t
TEST_F(ImageTest_1085, ByteSwap32_1085) {
    uint32_t val = 0x01020304;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x04030201u);

    uint32_t notSwapped = Exiv2::Image::byteSwap(val, false);
    EXPECT_EQ(notSwapped, val);
}

// Test static byteSwap for uint64_t
TEST_F(ImageTest_1085, ByteSwap64_1085) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0807060504030201ULL);

    uint64_t notSwapped = Exiv2::Image::byteSwap(val, false);
    EXPECT_EQ(notSwapped, val);
}

// Test isStringType
TEST_F(ImageTest_1085, IsStringType_1085) {
    // TIFF ASCII type is 2
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
    // TIFF LONG type is 4, not a string
    EXPECT_FALSE(Exiv2::Image::isStringType(4));
}

// Test isShortType
TEST_F(ImageTest_1085, IsShortType_1085) {
    // TIFF SHORT is type 3
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
    EXPECT_FALSE(Exiv2::Image::isShortType(4));
}

// Test isLongType
TEST_F(ImageTest_1085, IsLongType_1085) {
    // TIFF LONG is type 4
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
    EXPECT_FALSE(Exiv2::Image::isLongType(3));
}

// Test is2ByteType
TEST_F(ImageTest_1085, Is2ByteType_1085) {
    // SHORT (3) is 2 bytes
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

// Test is4ByteType
TEST_F(ImageTest_1085, Is4ByteType_1085) {
    // LONG (4) is 4 bytes
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
}

// Test imageType
TEST_F(ImageTest_1085, ImageTypeReturnsNone_1085) {
    EXPECT_EQ(image_->imageType(), Exiv2::ImageType::none);
}

// Test setExifData and clearExifData
TEST_F(ImageTest_1085, SetAndClearExifData_1085) {
    Exiv2::ExifData exifData;
    image_->setExifData(exifData);
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

// Test setIptcData and clearIptcData
TEST_F(ImageTest_1085, SetAndClearIptcData_1085) {
    Exiv2::IptcData iptcData;
    image_->setIptcData(iptcData);
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

// Test setXmpData and clearXmpData
TEST_F(ImageTest_1085, SetAndClearXmpData_1085) {
    Exiv2::XmpData xmpData;
    image_->setXmpData(xmpData);
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// Test setXmpPacket and clearXmpPacket
TEST_F(ImageTest_1085, SetAndClearXmpPacket_1085) {
    image_->setXmpPacket("<xmp>test</xmp>");
    EXPECT_EQ(image_->xmpPacket(), "<xmp>test</xmp>");

    image_->clearXmpPacket();
    EXPECT_EQ(image_->xmpPacket(), "");
}

// Test nativePreviews is initially empty
TEST_F(ImageTest_1085, NativePreviewsInitiallyEmpty_1085) {
    EXPECT_TRUE(image_->nativePreviews().empty());
}

// Test appending a single byte
TEST_F(ImageTest_1085, AppendSingleByte_1085) {
    const uint8_t byte = 0xFF;
    image_->appendIccProfile(&byte, 1, false);
    EXPECT_EQ(image_->iccProfile().size(), 1u);
    EXPECT_EQ(image_->iccProfile().read_uint8(0), 0xFF);
}

// Test appending large data
TEST_F(ImageTest_1085, AppendLargeIccProfile_1085) {
    std::vector<uint8_t> largeData(10000, 0x42);
    image_->appendIccProfile(largeData.data(), largeData.size(), false);
    EXPECT_EQ(image_->iccProfile().size(), 10000u);
    EXPECT_EQ(image_->iccProfile().read_uint8(0), 0x42);
    EXPECT_EQ(image_->iccProfile().read_uint8(9999), 0x42);
}

// Test clear then append
TEST_F(ImageTest_1085, ClearThenAppend_1085) {
    const uint8_t data1[] = {0x01, 0x02};
    image_->appendIccProfile(data1, sizeof(data1), false);
    EXPECT_EQ(image_->iccProfile().size(), 2u);

    image_->clearIccProfile();
    EXPECT_EQ(image_->iccProfile().size(), 0u);

    const uint8_t data2[] = {0x03};
    image_->appendIccProfile(data2, sizeof(data2), false);
    EXPECT_EQ(image_->iccProfile().size(), 1u);
    EXPECT_EQ(image_->iccProfile().read_uint8(0), 0x03);
}

// Test io() returns a reference
TEST_F(ImageTest_1085, IoReturnsValidReference_1085) {
    const Exiv2::BasicIo& io = image_->io();
    // Just verify we can access the io without crashing
    (void)io;
}

// Test mimeType returns some string (default for none type)
TEST_F(ImageTest_1085, MimeTypeReturnsString_1085) {
    std::string mime = image_->mimeType();
    // Should return some string, possibly empty for ImageType::none
    (void)mime;
}

}  // namespace
