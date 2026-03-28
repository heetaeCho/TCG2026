#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/image.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>

#include <memory>
#include <sstream>

// We need a concrete Image subclass since Image has pure virtual methods (readMetadata, writeMetadata)
// We'll create a minimal test subclass
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

class ImageSetXmpDataTest_1080 : public ::testing::Test {
protected:
    std::unique_ptr<TestImage> image_;

    void SetUp() override {
        image_ = createTestImage();
    }
};

// Test that setXmpData assigns the XMP data to the image
TEST_F(ImageSetXmpDataTest_1080, SetXmpDataAssignsData_1080) {
    Exiv2::XmpData xmpData;
    // Add some data to xmpData
    xmpData["Xmp.dc.title"] = "Test Title";
    
    EXPECT_TRUE(image_->xmpData().empty());
    
    image_->setXmpData(xmpData);
    
    EXPECT_FALSE(image_->xmpData().empty());
    EXPECT_EQ(image_->xmpData().count(), xmpData.count());
}

// Test that setXmpData sets writeXmpFromPacket to false
TEST_F(ImageSetXmpDataTest_1080, SetXmpDataSetsWriteXmpFromPacketFalse_1080) {
    // First set writeXmpFromPacket to true
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
    
    Exiv2::XmpData xmpData;
    image_->setXmpData(xmpData);
    
    // After setXmpData, writeXmpFromPacket should be false
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// Test setting empty XmpData
TEST_F(ImageSetXmpDataTest_1080, SetEmptyXmpData_1080) {
    Exiv2::XmpData emptyXmpData;
    
    image_->setXmpData(emptyXmpData);
    
    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_EQ(image_->xmpData().count(), 0);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// Test overwriting existing XMP data
TEST_F(ImageSetXmpDataTest_1080, SetXmpDataOverwritesExistingData_1080) {
    Exiv2::XmpData xmpData1;
    xmpData1["Xmp.dc.title"] = "First Title";
    image_->setXmpData(xmpData1);
    
    EXPECT_EQ(image_->xmpData().count(), 1);
    
    Exiv2::XmpData xmpData2;
    xmpData2["Xmp.dc.creator"] = "Author";
    xmpData2["Xmp.dc.description"] = "Description";
    image_->setXmpData(xmpData2);
    
    EXPECT_EQ(image_->xmpData().count(), 2);
}

// Test that setXmpData with data after clearing
TEST_F(ImageSetXmpDataTest_1080, SetXmpDataAfterClear_1080) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Title";
    image_->setXmpData(xmpData);
    
    EXPECT_FALSE(image_->xmpData().empty());
    
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
    
    Exiv2::XmpData xmpData2;
    xmpData2["Xmp.dc.subject"] = "Subject";
    image_->setXmpData(xmpData2);
    
    EXPECT_FALSE(image_->xmpData().empty());
    EXPECT_EQ(image_->xmpData().count(), 1);
}

// Test that setXmpData always resets writeXmpFromPacket even when called multiple times
TEST_F(ImageSetXmpDataTest_1080, SetXmpDataAlwaysResetsWriteXmpFromPacket_1080) {
    Exiv2::XmpData xmpData;
    
    // Call setXmpData multiple times, checking writeXmpFromPacket each time
    for (int i = 0; i < 3; ++i) {
        image_->writeXmpFromPacket(true);
        EXPECT_TRUE(image_->writeXmpFromPacket());
        
        image_->setXmpData(xmpData);
        EXPECT_FALSE(image_->writeXmpFromPacket());
    }
}

// Test replacing non-empty XmpData with empty XmpData
TEST_F(ImageSetXmpDataTest_1080, ReplaceNonEmptyWithEmpty_1080) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Title";
    xmpData["Xmp.dc.creator"] = "Creator";
    image_->setXmpData(xmpData);
    
    EXPECT_EQ(image_->xmpData().count(), 2);
    
    Exiv2::XmpData emptyXmpData;
    image_->setXmpData(emptyXmpData);
    
    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_EQ(image_->xmpData().count(), 0);
}

// Test that writeXmpFromPacket is false when it was already false before setXmpData
TEST_F(ImageSetXmpDataTest_1080, WriteXmpFromPacketStaysFalse_1080) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
    
    Exiv2::XmpData xmpData;
    image_->setXmpData(xmpData);
    
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// Test setXmpData with multiple properties
TEST_F(ImageSetXmpDataTest_1080, SetXmpDataWithMultipleProperties_1080) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Title";
    xmpData["Xmp.dc.creator"] = "Creator";
    xmpData["Xmp.dc.description"] = "Description";
    xmpData["Xmp.dc.subject"] = "Subject";
    
    image_->setXmpData(xmpData);
    
    EXPECT_EQ(image_->xmpData().count(), xmpData.count());
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// Additional Image interface tests

class ImageGeneralTest_1080 : public ::testing::Test {
protected:
    std::unique_ptr<TestImage> image_;

    void SetUp() override {
        image_ = createTestImage();
    }
};

// Test clearXmpData
TEST_F(ImageGeneralTest_1080, ClearXmpData_1080) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Title";
    image_->setXmpData(xmpData);
    
    EXPECT_FALSE(image_->xmpData().empty());
    
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// Test writeXmpFromPacket getter/setter
TEST_F(ImageGeneralTest_1080, WriteXmpFromPacketFlag_1080) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
    
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
    
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// Test setComment and comment
TEST_F(ImageGeneralTest_1080, SetAndGetComment_1080) {
    image_->setComment("Test comment");
    EXPECT_EQ(image_->comment(), "Test comment");
}

// Test clearComment
TEST_F(ImageGeneralTest_1080, ClearComment_1080) {
    image_->setComment("Test comment");
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

// Test setByteOrder and byteOrder
TEST_F(ImageGeneralTest_1080, SetAndGetByteOrder_1080) {
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);
    
    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::littleEndian);
}

// Test initial pixel dimensions
TEST_F(ImageGeneralTest_1080, InitialPixelDimensions_1080) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// Test clearMetadata
TEST_F(ImageGeneralTest_1080, ClearMetadata_1080) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Title";
    image_->setXmpData(xmpData);
    image_->setComment("Comment");
    
    image_->clearMetadata();
    
    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_TRUE(image_->comment().empty());
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
}

// Test static byteSwap methods
TEST_F(ImageGeneralTest_1080, ByteSwap16NoSwap_1080) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x1234u);
}

TEST_F(ImageGeneralTest_1080, ByteSwap16WithSwap_1080) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x3412u);
}

TEST_F(ImageGeneralTest_1080, ByteSwap32NoSwap_1080) {
    uint32_t val = 0x12345678u;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x12345678u);
}

TEST_F(ImageGeneralTest_1080, ByteSwap32WithSwap_1080) {
    uint32_t val = 0x12345678u;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x78563412u);
}

TEST_F(ImageGeneralTest_1080, ByteSwap64NoSwap_1080) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x0102030405060708ULL);
}

TEST_F(ImageGeneralTest_1080, ByteSwap64WithSwap_1080) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x0807060504030201ULL);
}

// Test endianness detection (at least one must be true)
TEST_F(ImageGeneralTest_1080, EndiannessPlatformCheck_1080) {
    bool big = Exiv2::Image::isBigEndianPlatform();
    bool little = Exiv2::Image::isLittleEndianPlatform();
    
    // Platform must be either big or little endian
    EXPECT_TRUE(big || little);
    // Cannot be both
    EXPECT_NE(big, little);
}

// Test isStringType
TEST_F(ImageGeneralTest_1080, IsStringType_1080) {
    // ASCII type (2) should be string type
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
    // SHORT type (3) should not be string type
    EXPECT_FALSE(Exiv2::Image::isStringType(3));
}

// Test isShortType
TEST_F(ImageGeneralTest_1080, IsShortType_1080) {
    // SHORT (3) and SSHORT (8) should be short types
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
    EXPECT_TRUE(Exiv2::Image::isShortType(8));
    // LONG (4) should not be short type
    EXPECT_FALSE(Exiv2::Image::isShortType(4));
}

// Test isLongType
TEST_F(ImageGeneralTest_1080, IsLongType_1080) {
    // LONG (4) and SLONG (9) should be long types
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
    EXPECT_TRUE(Exiv2::Image::isLongType(9));
    // SHORT (3) should not be long type
    EXPECT_FALSE(Exiv2::Image::isLongType(3));
}

// Test isRationalType
TEST_F(ImageGeneralTest_1080, IsRationalType_1080) {
    // RATIONAL (5) and SRATIONAL (10) should be rational types
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
    EXPECT_TRUE(Exiv2::Image::isRationalType(10));
    // SHORT (3) should not be rational type
    EXPECT_FALSE(Exiv2::Image::isRationalType(3));
}

// Test is2ByteType
TEST_F(ImageGeneralTest_1080, Is2ByteType_1080) {
    // SHORT (3) is 2-byte
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
    // LONG (4) is not 2-byte
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

// Test is4ByteType
TEST_F(ImageGeneralTest_1080, Is4ByteType_1080) {
    // LONG (4) is 4-byte
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
    // SHORT (3) is not 4-byte
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
}

// Test is8ByteType
TEST_F(ImageGeneralTest_1080, Is8ByteType_1080) {
    // RATIONAL (5) is 8-byte
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
    // SHORT (3) is not 8-byte
    EXPECT_FALSE(Exiv2::Image::is8ByteType(3));
}

// Test setXmpPacket and xmpPacket
TEST_F(ImageGeneralTest_1080, SetXmpPacket_1080) {
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    image_->setXmpPacket(packet);
    EXPECT_EQ(image_->xmpPacket(), packet);
}

// Test clearXmpPacket
TEST_F(ImageGeneralTest_1080, ClearXmpPacket_1080) {
    image_->setXmpPacket("<x:xmpmeta>test</x:xmpmeta>");
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// Test nativePreviews returns a reference
TEST_F(ImageGeneralTest_1080, NativePreviewsEmpty_1080) {
    const auto& previews = image_->nativePreviews();
    EXPECT_TRUE(previews.empty());
}

// Test clearIccProfile
TEST_F(ImageGeneralTest_1080, ClearIccProfile_1080) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

// Test good() with MemIo
TEST_F(ImageGeneralTest_1080, GoodWithMemIo_1080) {
    // MemIo should report good
    EXPECT_TRUE(image_->good());
}
