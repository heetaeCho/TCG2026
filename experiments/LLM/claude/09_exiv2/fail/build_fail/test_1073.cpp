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

// A concrete subclass of Image for testing purposes, since Image itself
// has pure virtual methods (readMetadata, writeMetadata).
namespace {

class TestImage : public Exiv2::Image {
public:
    TestImage(std::unique_ptr<Exiv2::BasicIo> io)
        : Exiv2::Image(Exiv2::ImageType::none, Exiv2::MetadataId::mdNone, std::move(io)) {
    }

    TestImage(Exiv2::ImageType type, uint16_t supportedMetadata, std::unique_ptr<Exiv2::BasicIo> io)
        : Exiv2::Image(type, supportedMetadata, std::move(io)) {
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

std::unique_ptr<TestImage> createTestImageWithMetadata(uint16_t supportedMetadata) {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<TestImage>(Exiv2::ImageType::none, supportedMetadata, std::move(io));
}

} // anonymous namespace

class ImageTest_1073 : public ::testing::Test {
protected:
    void SetUp() override {
        image_ = createTestImage();
    }

    std::unique_ptr<TestImage> image_;
};

// ==================== clearExifData Tests ====================

TEST_F(ImageTest_1073, ClearExifData_EmptyData_1073) {
    // Clearing already empty exif data should result in empty exif data
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_EQ(image_->exifData().count(), 0u);
}

TEST_F(ImageTest_1073, ClearExifData_AfterAddingData_1073) {
    // Add some exif data, then clear it
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    EXPECT_FALSE(image_->exifData().empty());

    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_EQ(image_->exifData().count(), 0u);
}

TEST_F(ImageTest_1073, ClearExifData_MultipleTimes_1073) {
    // Clearing multiple times should be safe
    image_->clearExifData();
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

// ==================== setExifData / exifData Tests ====================

TEST_F(ImageTest_1073, SetExifData_Basic_1073) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "Canon";
    image_->setExifData(exifData);
    EXPECT_FALSE(image_->exifData().empty());
}

TEST_F(ImageTest_1073, ExifData_ReturnsMutableReference_1073) {
    Exiv2::ExifData& ref = image_->exifData();
    ref["Exif.Image.Model"] = "TestModel";
    EXPECT_FALSE(image_->exifData().empty());
}

// ==================== clearIptcData Tests ====================

TEST_F(ImageTest_1073, ClearIptcData_EmptyData_1073) {
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageTest_1073, ClearIptcData_AfterSetting_1073) {
    Exiv2::IptcData iptcData;
    image_->setIptcData(iptcData);
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

// ==================== clearXmpData Tests ====================

TEST_F(ImageTest_1073, ClearXmpData_EmptyData_1073) {
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// ==================== clearXmpPacket Tests ====================

TEST_F(ImageTest_1073, ClearXmpPacket_EmptyPacket_1073) {
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageTest_1073, SetXmpPacket_ThenClear_1073) {
    image_->setXmpPacket("<xmp>test</xmp>");
    EXPECT_FALSE(image_->xmpPacket().empty());
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// ==================== setComment / clearComment Tests ====================

TEST_F(ImageTest_1073, SetComment_Basic_1073) {
    image_->setComment("Hello World");
    EXPECT_EQ(image_->comment(), "Hello World");
}

TEST_F(ImageTest_1073, ClearComment_AfterSetting_1073) {
    image_->setComment("Test Comment");
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1073, ClearComment_EmptyComment_1073) {
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1073, SetComment_EmptyString_1073) {
    image_->setComment("");
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1073, SetComment_LongString_1073) {
    std::string longComment(10000, 'x');
    image_->setComment(longComment);
    EXPECT_EQ(image_->comment(), longComment);
}

// ==================== clearMetadata Tests ====================

TEST_F(ImageTest_1073, ClearMetadata_ClearsAll_1073) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "Test";
    image_->setExifData(exifData);
    image_->setComment("A comment");
    image_->setXmpPacket("<xmp/>");

    image_->clearMetadata();

    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_TRUE(image_->xmpPacket().empty());
    EXPECT_TRUE(image_->comment().empty());
}

// ==================== pixelWidth / pixelHeight Tests ====================

TEST_F(ImageTest_1073, PixelWidth_DefaultIsZero_1073) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(ImageTest_1073, PixelHeight_DefaultIsZero_1073) {
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// ==================== byteOrder Tests ====================

TEST_F(ImageTest_1073, ByteOrder_DefaultIsInvalid_1073) {
    EXPECT_EQ(image_->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageTest_1073, SetByteOrder_LittleEndian_1073) {
    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::littleEndian);
}

TEST_F(ImageTest_1073, SetByteOrder_BigEndian_1073) {
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);
}

// ==================== writeXmpFromPacket Tests ====================

TEST_F(ImageTest_1073, WriteXmpFromPacket_DefaultFalse_1073) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1073, WriteXmpFromPacket_SetTrue_1073) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1073, WriteXmpFromPacket_SetFalse_1073) {
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// ==================== good Tests ====================

TEST_F(ImageTest_1073, Good_WithMemIo_1073) {
    // MemIo should be in a good state
    EXPECT_TRUE(image_->good());
}

// ==================== io Tests ====================

TEST_F(ImageTest_1073, Io_ReturnsReference_1073) {
    const Exiv2::BasicIo& io = image_->io();
    // Just verify we can access the io reference without crashing
    (void)io;
}

// ==================== nativePreviews Tests ====================

TEST_F(ImageTest_1073, NativePreviews_DefaultEmpty_1073) {
    const Exiv2::NativePreviewList& previews = image_->nativePreviews();
    EXPECT_TRUE(previews.empty());
}

// ==================== Static method tests ====================

TEST_F(ImageTest_1073, IsBigEndianPlatform_OrIsLittleEndianPlatform_1073) {
    // One of them must be true, and they should be mutually exclusive
    bool big = Exiv2::Image::isBigEndianPlatform();
    bool little = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_TRUE(big || little);
    EXPECT_NE(big, little);
}

// ==================== byteSwap Tests ====================

TEST_F(ImageTest_1073, ByteSwap16_NoSwap_1073) {
    uint16_t val = 0x1234;
    uint16_t result = Exiv2::Image::byteSwap(val, false);
    EXPECT_EQ(result, val);
}

TEST_F(ImageTest_1073, ByteSwap16_Swap_1073) {
    uint16_t val = 0x1234;
    uint16_t result = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(result, 0x3412);
}

TEST_F(ImageTest_1073, ByteSwap32_NoSwap_1073) {
    uint32_t val = 0x12345678;
    uint32_t result = Exiv2::Image::byteSwap(val, false);
    EXPECT_EQ(result, val);
}

TEST_F(ImageTest_1073, ByteSwap32_Swap_1073) {
    uint32_t val = 0x12345678;
    uint32_t result = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(result, 0x78563412u);
}

TEST_F(ImageTest_1073, ByteSwap64_NoSwap_1073) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t result = Exiv2::Image::byteSwap(val, false);
    EXPECT_EQ(result, val);
}

TEST_F(ImageTest_1073, ByteSwap64_Swap_1073) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t result = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(result, 0x0807060504030201ULL);
}

TEST_F(ImageTest_1073, ByteSwap16_Zero_1073) {
    uint16_t val = 0x0000;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x0000);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x0000);
}

TEST_F(ImageTest_1073, ByteSwap16_MaxValue_1073) {
    uint16_t val = 0xFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFF);
}

TEST_F(ImageTest_1073, ByteSwap32_Zero_1073) {
    uint32_t val = 0x00000000;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x00000000u);
}

// ==================== isStringType Tests ====================

TEST_F(ImageTest_1073, IsStringType_AsciiType_1073) {
    // Type 2 is typically ASCII in TIFF
    bool result = Exiv2::Image::isStringType(2);
    EXPECT_TRUE(result);
}

TEST_F(ImageTest_1073, IsStringType_NonStringType_1073) {
    // Type 3 is SHORT, not string
    bool result = Exiv2::Image::isStringType(3);
    EXPECT_FALSE(result);
}

// ==================== isShortType Tests ====================

TEST_F(ImageTest_1073, IsShortType_ShortType_1073) {
    // Type 3 is SHORT in TIFF
    bool result = Exiv2::Image::isShortType(3);
    EXPECT_TRUE(result);
}

TEST_F(ImageTest_1073, IsShortType_NonShortType_1073) {
    bool result = Exiv2::Image::isShortType(2);
    EXPECT_FALSE(result);
}

// ==================== isLongType Tests ====================

TEST_F(ImageTest_1073, IsLongType_LongType_1073) {
    // Type 4 is LONG in TIFF
    bool result = Exiv2::Image::isLongType(4);
    EXPECT_TRUE(result);
}

TEST_F(ImageTest_1073, IsLongType_NonLongType_1073) {
    bool result = Exiv2::Image::isLongType(2);
    EXPECT_FALSE(result);
}

// ==================== isRationalType Tests ====================

TEST_F(ImageTest_1073, IsRationalType_RationalType_1073) {
    // Type 5 is RATIONAL in TIFF
    bool result = Exiv2::Image::isRationalType(5);
    EXPECT_TRUE(result);
}

TEST_F(ImageTest_1073, IsRationalType_NonRationalType_1073) {
    bool result = Exiv2::Image::isRationalType(2);
    EXPECT_FALSE(result);
}

// ==================== is2ByteType Tests ====================

TEST_F(ImageTest_1073, Is2ByteType_ShortType_1073) {
    // SHORT (3) is 2 bytes
    bool result = Exiv2::Image::is2ByteType(3);
    EXPECT_TRUE(result);
}

// ==================== is4ByteType Tests ====================

TEST_F(ImageTest_1073, Is4ByteType_LongType_1073) {
    // LONG (4) is 4 bytes
    bool result = Exiv2::Image::is4ByteType(4);
    EXPECT_TRUE(result);
}

// ==================== is8ByteType Tests ====================

TEST_F(ImageTest_1073, Is8ByteType_RationalType_1073) {
    // RATIONAL (5) is 8 bytes
    bool result = Exiv2::Image::is8ByteType(5);
    EXPECT_TRUE(result);
}

// ==================== ICC Profile Tests ====================

TEST_F(ImageTest_1073, IccProfileDefined_DefaultFalse_1073) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1073, ClearIccProfile_WhenNoneSet_1073) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

// ==================== setMetadata Tests ====================

TEST_F(ImageTest_1073, SetMetadata_CopiesFromOtherImage_1073) {
    auto other = createTestImage();
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "CopiedMake";
    other->setExifData(exifData);
    other->setComment("Copied Comment");

    image_->setMetadata(*other);

    EXPECT_FALSE(image_->exifData().empty());
    EXPECT_EQ(image_->comment(), "Copied Comment");
}

// ==================== imageType Tests ====================

TEST_F(ImageTest_1073, ImageType_ReturnsCorrectType_1073) {
    EXPECT_EQ(image_->imageType(), Exiv2::ImageType::none);
}

// ==================== xmpData Tests ====================

TEST_F(ImageTest_1073, XmpData_ReturnsMutableReference_1073) {
    Exiv2::XmpData& xmpData = image_->xmpData();
    EXPECT_TRUE(xmpData.empty());
}

// ==================== iptcData Tests ====================

TEST_F(ImageTest_1073, IptcData_ReturnsMutableReference_1073) {
    Exiv2::IptcData& iptcData = image_->iptcData();
    EXPECT_TRUE(iptcData.empty());
}

// ==================== xmpPacket Tests ====================

TEST_F(ImageTest_1073, XmpPacket_DefaultEmpty_1073) {
    EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageTest_1073, SetXmpPacket_Basic_1073) {
    std::string packet = "<xmp>data</xmp>";
    image_->setXmpPacket(packet);
    EXPECT_EQ(image_->xmpPacket(), packet);
}

// ==================== Double swap is identity ====================

TEST_F(ImageTest_1073, ByteSwap16_DoubleSwapIsIdentity_1073) {
    uint16_t val = 0xABCD;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    uint16_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, val);
}

TEST_F(ImageTest_1073, ByteSwap32_DoubleSwapIsIdentity_1073) {
    uint32_t val = 0xDEADBEEF;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    uint32_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, val);
}

TEST_F(ImageTest_1073, ByteSwap64_DoubleSwapIsIdentity_1073) {
    uint64_t val = 0xDEADBEEFCAFEBABEULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    uint64_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, val);
}

// ==================== setExifData then clearExifData round-trip ====================

TEST_F(ImageTest_1073, SetExifData_ClearExifData_RoundTrip_1073) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "Nikon";
    exifData["Exif.Image.Model"] = "D850";
    image_->setExifData(exifData);
    EXPECT_GE(image_->exifData().count(), 2u);

    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_EQ(image_->exifData().count(), 0u);
}

// ==================== setComment special characters ====================

TEST_F(ImageTest_1073, SetComment_SpecialCharacters_1073) {
    std::string specialComment = "Test\n\t\r\"'\\<>&";
    image_->setComment(specialComment);
    EXPECT_EQ(image_->comment(), specialComment);
}

// ==================== mimeType Tests ====================

TEST_F(ImageTest_1073, MimeType_DefaultForNoneType_1073) {
    // For ImageType::none, the mime type should be some default
    std::string mime = image_->mimeType();
    // Just verify it doesn't crash and returns something
    (void)mime;
}
