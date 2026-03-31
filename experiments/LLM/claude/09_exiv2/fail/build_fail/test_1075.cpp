#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/xmp_exiv2.hpp>

#include <memory>
#include <sstream>

namespace {

// A concrete subclass of Image for testing, since Image has pure virtual methods
// We use a known image type creator or a minimal concrete subclass.
// Since Image requires a BasicIo, we use MemIo for in-memory testing.

class TestImage : public Exiv2::Image {
public:
    TestImage(std::unique_ptr<Exiv2::BasicIo> io)
        : Exiv2::Image(Exiv2::ImageType::none, 
                        static_cast<uint16_t>(Exiv2::MetadataId::mdExif) |
                        static_cast<uint16_t>(Exiv2::MetadataId::mdIptc) |
                        static_cast<uint16_t>(Exiv2::MetadataId::mdXmp) |
                        static_cast<uint16_t>(Exiv2::MetadataId::mdComment),
                        std::move(io)) {
    }

    void readMetadata() override {
        // No-op for testing
    }

    void writeMetadata() override {
        // No-op for testing
    }
};

std::unique_ptr<TestImage> createTestImage() {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<TestImage>(std::move(io));
}

class ImageClearIptcDataTest_1075 : public ::testing::Test {
protected:
    std::unique_ptr<TestImage> image;

    void SetUp() override {
        image = createTestImage();
    }
};

// Test that clearIptcData empties the IPTC data
TEST_F(ImageClearIptcDataTest_1075, ClearIptcDataEmptiesData_1075) {
    // First, set some IPTC data
    Exiv2::IptcData iptcData;
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("Test caption");
    iptcData.add(key, value.get());
    
    image->setIptcData(iptcData);
    
    // Verify data is not empty before clearing
    ASSERT_FALSE(image->iptcData().empty());
    
    // Clear the IPTC data
    image->clearIptcData();
    
    // Verify data is now empty
    EXPECT_TRUE(image->iptcData().empty());
    EXPECT_EQ(image->iptcData().size(), 0u);
}

// Test that clearIptcData on already empty data works fine
TEST_F(ImageClearIptcDataTest_1075, ClearIptcDataOnEmptyData_1075) {
    // IPTC data should be empty by default
    ASSERT_TRUE(image->iptcData().empty());
    
    // Clearing empty data should not cause any error
    image->clearIptcData();
    
    EXPECT_TRUE(image->iptcData().empty());
    EXPECT_EQ(image->iptcData().size(), 0u);
}

// Test that clearIptcData can be called multiple times
TEST_F(ImageClearIptcDataTest_1075, ClearIptcDataMultipleTimes_1075) {
    Exiv2::IptcData iptcData;
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("Some text");
    iptcData.add(key, value.get());
    
    image->setIptcData(iptcData);
    ASSERT_FALSE(image->iptcData().empty());
    
    image->clearIptcData();
    EXPECT_TRUE(image->iptcData().empty());
    
    // Clear again - should be safe
    image->clearIptcData();
    EXPECT_TRUE(image->iptcData().empty());
}

// Test that clearIptcData does not affect ExifData
TEST_F(ImageClearIptcDataTest_1075, ClearIptcDataDoesNotAffectExifData_1075) {
    // Set some exif data
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image->setExifData(exifData);
    
    // Set some IPTC data
    Exiv2::IptcData iptcData;
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("Test");
    iptcData.add(key, value.get());
    image->setIptcData(iptcData);
    
    ASSERT_FALSE(image->exifData().empty());
    ASSERT_FALSE(image->iptcData().empty());
    
    // Clear only IPTC data
    image->clearIptcData();
    
    EXPECT_TRUE(image->iptcData().empty());
    EXPECT_FALSE(image->exifData().empty());
}

// Test that clearIptcData does not affect XmpData
TEST_F(ImageClearIptcDataTest_1075, ClearIptcDataDoesNotAffectXmpData_1075) {
    // Set some XMP data
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test Title";
    image->setXmpData(xmpData);
    
    // Set some IPTC data
    Exiv2::IptcData iptcData;
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("Test");
    iptcData.add(key, value.get());
    image->setIptcData(iptcData);
    
    ASSERT_FALSE(image->xmpData().empty());
    ASSERT_FALSE(image->iptcData().empty());
    
    image->clearIptcData();
    
    EXPECT_TRUE(image->iptcData().empty());
    EXPECT_FALSE(image->xmpData().empty());
}

// Test that clearIptcData does not affect comment
TEST_F(ImageClearIptcDataTest_1075, ClearIptcDataDoesNotAffectComment_1075) {
    image->setComment("Hello World");
    
    Exiv2::IptcData iptcData;
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("Test");
    iptcData.add(key, value.get());
    image->setIptcData(iptcData);
    
    image->clearIptcData();
    
    EXPECT_TRUE(image->iptcData().empty());
    EXPECT_EQ(image->comment(), "Hello World");
}

// Test that after clearing, new IPTC data can be set
TEST_F(ImageClearIptcDataTest_1075, SetIptcDataAfterClear_1075) {
    // Set initial data
    Exiv2::IptcData iptcData1;
    Exiv2::IptcKey key1("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value1 = Exiv2::Value::create(Exiv2::string);
    value1->read("First");
    iptcData1.add(key1, value1.get());
    image->setIptcData(iptcData1);
    
    ASSERT_EQ(image->iptcData().size(), 1u);
    
    // Clear
    image->clearIptcData();
    ASSERT_TRUE(image->iptcData().empty());
    
    // Set new data
    Exiv2::IptcData iptcData2;
    Exiv2::IptcKey key2("Iptc.Application2.Keywords");
    Exiv2::Value::UniquePtr value2 = Exiv2::Value::create(Exiv2::string);
    value2->read("keyword1");
    iptcData2.add(key2, value2.get());
    
    Exiv2::IptcKey key3("Iptc.Application2.Keywords");
    Exiv2::Value::UniquePtr value3 = Exiv2::Value::create(Exiv2::string);
    value3->read("keyword2");
    iptcData2.add(key3, value3.get());
    
    image->setIptcData(iptcData2);
    
    EXPECT_EQ(image->iptcData().size(), 2u);
    EXPECT_FALSE(image->iptcData().empty());
}

// Test clearIptcData with multiple IPTC entries
TEST_F(ImageClearIptcDataTest_1075, ClearIptcDataWithMultipleEntries_1075) {
    Exiv2::IptcData iptcData;
    
    Exiv2::IptcKey key1("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value1 = Exiv2::Value::create(Exiv2::string);
    value1->read("Caption text");
    iptcData.add(key1, value1.get());
    
    Exiv2::IptcKey key2("Iptc.Application2.Keywords");
    Exiv2::Value::UniquePtr value2 = Exiv2::Value::create(Exiv2::string);
    value2->read("keyword");
    iptcData.add(key2, value2.get());
    
    Exiv2::IptcKey key3("Iptc.Application2.City");
    Exiv2::Value::UniquePtr value3 = Exiv2::Value::create(Exiv2::string);
    value3->read("TestCity");
    iptcData.add(key3, value3.get());
    
    image->setIptcData(iptcData);
    ASSERT_EQ(image->iptcData().size(), 3u);
    
    image->clearIptcData();
    
    EXPECT_TRUE(image->iptcData().empty());
    EXPECT_EQ(image->iptcData().size(), 0u);
    EXPECT_EQ(image->iptcData().begin(), image->iptcData().end());
}

// Test that iterators are valid after clear (begin == end)
TEST_F(ImageClearIptcDataTest_1075, IteratorsAfterClear_1075) {
    Exiv2::IptcData iptcData;
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("Test");
    iptcData.add(key, value.get());
    image->setIptcData(iptcData);
    
    ASSERT_NE(image->iptcData().begin(), image->iptcData().end());
    
    image->clearIptcData();
    
    EXPECT_EQ(image->iptcData().begin(), image->iptcData().end());
}

// Additional tests for related Image methods to ensure comprehensive coverage

class ImageGeneralTest_1075 : public ::testing::Test {
protected:
    std::unique_ptr<TestImage> image;

    void SetUp() override {
        image = createTestImage();
    }
};

// Test clearMetadata clears everything
TEST_F(ImageGeneralTest_1075, ClearMetadataClearsIptc_1075) {
    Exiv2::IptcData iptcData;
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("Test");
    iptcData.add(key, value.get());
    image->setIptcData(iptcData);
    
    image->clearMetadata();
    
    EXPECT_TRUE(image->iptcData().empty());
}

// Test setIptcData replaces existing data
TEST_F(ImageGeneralTest_1075, SetIptcDataReplacesExisting_1075) {
    Exiv2::IptcData iptcData1;
    Exiv2::IptcKey key1("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value1 = Exiv2::Value::create(Exiv2::string);
    value1->read("First");
    iptcData1.add(key1, value1.get());
    image->setIptcData(iptcData1);
    
    ASSERT_EQ(image->iptcData().size(), 1u);
    
    Exiv2::IptcData iptcData2;
    Exiv2::IptcKey key2("Iptc.Application2.Keywords");
    Exiv2::Value::UniquePtr value2 = Exiv2::Value::create(Exiv2::string);
    value2->read("kw1");
    iptcData2.add(key2, value2.get());
    
    Exiv2::IptcKey key3("Iptc.Application2.City");
    Exiv2::Value::UniquePtr value3 = Exiv2::Value::create(Exiv2::string);
    value3->read("City");
    iptcData2.add(key3, value3.get());
    
    image->setIptcData(iptcData2);
    
    EXPECT_EQ(image->iptcData().size(), 2u);
}

// Test static utility methods
TEST_F(ImageGeneralTest_1075, EndianPlatformCheck_1075) {
    bool isBig = Exiv2::Image::isBigEndianPlatform();
    bool isLittle = Exiv2::Image::isLittleEndianPlatform();
    
    // One must be true and the other false (on typical platforms)
    EXPECT_NE(isBig, isLittle);
}

// Test byteSwap for uint16_t
TEST_F(ImageGeneralTest_1075, ByteSwap16NoSwap_1075) {
    uint16_t val = 0x0102;
    uint16_t result = Exiv2::Image::byteSwap(val, false);
    EXPECT_EQ(result, val);
}

TEST_F(ImageGeneralTest_1075, ByteSwap16WithSwap_1075) {
    uint16_t val = 0x0102;
    uint16_t result = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(result, 0x0201);
}

// Test byteSwap for uint32_t
TEST_F(ImageGeneralTest_1075, ByteSwap32NoSwap_1075) {
    uint32_t val = 0x01020304;
    uint32_t result = Exiv2::Image::byteSwap(val, false);
    EXPECT_EQ(result, val);
}

TEST_F(ImageGeneralTest_1075, ByteSwap32WithSwap_1075) {
    uint32_t val = 0x01020304;
    uint32_t result = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(result, 0x04030201u);
}

// Test byteSwap for uint64_t
TEST_F(ImageGeneralTest_1075, ByteSwap64NoSwap_1075) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t result = Exiv2::Image::byteSwap(val, false);
    EXPECT_EQ(result, val);
}

TEST_F(ImageGeneralTest_1075, ByteSwap64WithSwap_1075) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t result = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(result, 0x0807060504030201ULL);
}

// Test default byte order
TEST_F(ImageGeneralTest_1075, DefaultByteOrder_1075) {
    EXPECT_EQ(image->byteOrder(), Exiv2::invalidByteOrder);
}

// Test setByteOrder
TEST_F(ImageGeneralTest_1075, SetByteOrder_1075) {
    image->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(image->byteOrder(), Exiv2::bigEndian);
    
    image->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(image->byteOrder(), Exiv2::littleEndian);
}

// Test default pixel dimensions
TEST_F(ImageGeneralTest_1075, DefaultPixelDimensions_1075) {
    EXPECT_EQ(image->pixelWidth(), 0u);
    EXPECT_EQ(image->pixelHeight(), 0u);
}

// Test comment operations
TEST_F(ImageGeneralTest_1075, SetAndClearComment_1075) {
    image->setComment("Test comment");
    EXPECT_EQ(image->comment(), "Test comment");
    
    image->clearComment();
    EXPECT_TRUE(image->comment().empty());
}

// Test writeXmpFromPacket
TEST_F(ImageGeneralTest_1075, WriteXmpFromPacketFlag_1075) {
    EXPECT_FALSE(image->writeXmpFromPacket());
    
    image->writeXmpFromPacket(true);
    EXPECT_TRUE(image->writeXmpFromPacket());
    
    image->writeXmpFromPacket(false);
    EXPECT_FALSE(image->writeXmpFromPacket());
}

// Test clearExifData
TEST_F(ImageGeneralTest_1075, ClearExifData_1075) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image->setExifData(exifData);
    ASSERT_FALSE(image->exifData().empty());
    
    image->clearExifData();
    EXPECT_TRUE(image->exifData().empty());
}

// Test clearXmpData
TEST_F(ImageGeneralTest_1075, ClearXmpData_1075) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Title";
    image->setXmpData(xmpData);
    ASSERT_FALSE(image->xmpData().empty());
    
    image->clearXmpData();
    EXPECT_TRUE(image->xmpData().empty());
}

// Test clearXmpPacket
TEST_F(ImageGeneralTest_1075, SetAndClearXmpPacket_1075) {
    std::string packet = "<x:xmpmeta></x:xmpmeta>";
    image->setXmpPacket(packet);
    EXPECT_EQ(image->xmpPacket(), packet);
    
    image->clearXmpPacket();
    EXPECT_TRUE(image->xmpPacket().empty());
}

// Test ICC profile operations
TEST_F(ImageGeneralTest_1075, IccProfileDefaultNotDefined_1075) {
    EXPECT_FALSE(image->iccProfileDefined());
}

TEST_F(ImageGeneralTest_1075, ClearIccProfile_1075) {
    image->clearIccProfile();
    EXPECT_FALSE(image->iccProfileDefined());
}

// Test isStringType
TEST_F(ImageGeneralTest_1075, IsStringType_1075) {
    // Type 2 is ASCII in TIFF
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
    // Type 1 (BYTE) is not a string type
    EXPECT_FALSE(Exiv2::Image::isStringType(1));
}

// Test isShortType
TEST_F(ImageGeneralTest_1075, IsShortType_1075) {
    // Type 3 is SHORT in TIFF
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
    EXPECT_FALSE(Exiv2::Image::isShortType(2));
}

// Test isLongType
TEST_F(ImageGeneralTest_1075, IsLongType_1075) {
    // Type 4 is LONG in TIFF
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
    EXPECT_FALSE(Exiv2::Image::isLongType(3));
}

// Test isRationalType
TEST_F(ImageGeneralTest_1075, IsRationalType_1075) {
    // Type 5 is RATIONAL in TIFF
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
    EXPECT_FALSE(Exiv2::Image::isRationalType(4));
}

// Test is2ByteType
TEST_F(ImageGeneralTest_1075, Is2ByteType_1075) {
    // SHORT (3) is 2-byte type
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

// Test is4ByteType
TEST_F(ImageGeneralTest_1075, Is4ByteType_1075) {
    // LONG (4) is 4-byte type
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
}

}  // namespace
