#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <sstream>
#include <memory>

// Since Image is abstract (readMetadata/writeMetadata are pure virtual in practice),
// we need a concrete subclass for testing. We'll use ImageFactory to create real images,
// or we can create a minimal concrete subclass.

// A minimal concrete Image subclass for testing purposes
class TestImage : public Exiv2::Image {
public:
    TestImage(std::unique_ptr<Exiv2::BasicIo> io)
        : Exiv2::Image(Exiv2::ImageType::none, 
                        static_cast<uint16_t>(Exiv2::MetadataId::mdExif) |
                        static_cast<uint16_t>(Exiv2::MetadataId::mdIptc) |
                        static_cast<uint16_t>(Exiv2::MetadataId::mdXmp) |
                        static_cast<uint16_t>(Exiv2::MetadataId::mdComment),
                        std::move(io)) {}

    TestImage(Exiv2::ImageType type, uint16_t supportedMetadata, std::unique_ptr<Exiv2::BasicIo> io)
        : Exiv2::Image(type, supportedMetadata, std::move(io)) {}

    void readMetadata() override {}
    void writeMetadata() override {}
    std::string mimeType() const override { return "application/octet-stream"; }
};

class ImageTest_57 : public ::testing::Test {
protected:
    std::unique_ptr<TestImage> createTestImage() {
        auto io = std::make_unique<Exiv2::MemIo>();
        return std::make_unique<TestImage>(std::move(io));
    }

    std::unique_ptr<TestImage> createTestImageWithType(Exiv2::ImageType type, uint16_t supportedMetadata) {
        auto io = std::make_unique<Exiv2::MemIo>();
        return std::make_unique<TestImage>(type, supportedMetadata, std::move(io));
    }
};

// =============================================================================
// imageType() tests
// =============================================================================

TEST_F(ImageTest_57, ImageTypeReturnsCorrectType_57) {
    auto img = createTestImageWithType(Exiv2::ImageType::jpeg, 0xFFFF);
    EXPECT_EQ(img->imageType(), Exiv2::ImageType::jpeg);
}

TEST_F(ImageTest_57, ImageTypeNone_57) {
    auto img = createTestImage();
    EXPECT_EQ(img->imageType(), Exiv2::ImageType::none);
}

// =============================================================================
// byteOrder() tests
// =============================================================================

TEST_F(ImageTest_57, DefaultByteOrderIsInvalid_57) {
    auto img = createTestImage();
    EXPECT_EQ(img->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageTest_57, SetByteOrderBigEndian_57) {
    auto img = createTestImage();
    img->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(img->byteOrder(), Exiv2::bigEndian);
}

TEST_F(ImageTest_57, SetByteOrderLittleEndian_57) {
    auto img = createTestImage();
    img->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(img->byteOrder(), Exiv2::littleEndian);
}

// =============================================================================
// pixelWidth() / pixelHeight() tests
// =============================================================================

TEST_F(ImageTest_57, DefaultPixelWidthIsZero_57) {
    auto img = createTestImage();
    EXPECT_EQ(img->pixelWidth(), 0u);
}

TEST_F(ImageTest_57, DefaultPixelHeightIsZero_57) {
    auto img = createTestImage();
    EXPECT_EQ(img->pixelHeight(), 0u);
}

// =============================================================================
// comment() tests
// =============================================================================

TEST_F(ImageTest_57, DefaultCommentIsEmpty_57) {
    auto img = createTestImage();
    EXPECT_TRUE(img->comment().empty());
}

TEST_F(ImageTest_57, SetCommentAndRetrieve_57) {
    auto img = createTestImage();
    img->setComment("Test comment");
    EXPECT_EQ(img->comment(), "Test comment");
}

TEST_F(ImageTest_57, ClearComment_57) {
    auto img = createTestImage();
    img->setComment("Some comment");
    img->clearComment();
    EXPECT_TRUE(img->comment().empty());
}

TEST_F(ImageTest_57, SetEmptyComment_57) {
    auto img = createTestImage();
    img->setComment("");
    EXPECT_TRUE(img->comment().empty());
}

// =============================================================================
// ExifData tests
// =============================================================================

TEST_F(ImageTest_57, ExifDataInitiallyEmpty_57) {
    auto img = createTestImage();
    EXPECT_TRUE(img->exifData().empty());
}

TEST_F(ImageTest_57, SetExifDataAndRetrieve_57) {
    auto img = createTestImage();
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    img->setExifData(exifData);
    EXPECT_FALSE(img->exifData().empty());
}

TEST_F(ImageTest_57, ClearExifData_57) {
    auto img = createTestImage();
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    img->setExifData(exifData);
    img->clearExifData();
    EXPECT_TRUE(img->exifData().empty());
}

// =============================================================================
// IptcData tests
// =============================================================================

TEST_F(ImageTest_57, IptcDataInitiallyEmpty_57) {
    auto img = createTestImage();
    EXPECT_TRUE(img->iptcData().empty());
}

TEST_F(ImageTest_57, SetIptcDataAndRetrieve_57) {
    auto img = createTestImage();
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test caption";
    img->setIptcData(iptcData);
    EXPECT_FALSE(img->iptcData().empty());
}

TEST_F(ImageTest_57, ClearIptcData_57) {
    auto img = createTestImage();
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test caption";
    img->setIptcData(iptcData);
    img->clearIptcData();
    EXPECT_TRUE(img->iptcData().empty());
}

// =============================================================================
// XmpData tests
// =============================================================================

TEST_F(ImageTest_57, XmpDataInitiallyEmpty_57) {
    auto img = createTestImage();
    EXPECT_TRUE(img->xmpData().empty());
}

TEST_F(ImageTest_57, SetXmpDataAndRetrieve_57) {
    auto img = createTestImage();
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test title";
    img->setXmpData(xmpData);
    EXPECT_FALSE(img->xmpData().empty());
}

TEST_F(ImageTest_57, ClearXmpData_57) {
    auto img = createTestImage();
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test title";
    img->setXmpData(xmpData);
    img->clearXmpData();
    EXPECT_TRUE(img->xmpData().empty());
}

// =============================================================================
// XmpPacket tests
// =============================================================================

TEST_F(ImageTest_57, XmpPacketInitiallyEmpty_57) {
    auto img = createTestImage();
    EXPECT_TRUE(img->xmpPacket().empty());
}

TEST_F(ImageTest_57, SetXmpPacketAndRetrieve_57) {
    auto img = createTestImage();
    img->setXmpPacket("<xmp>test</xmp>");
    EXPECT_EQ(img->xmpPacket(), "<xmp>test</xmp>");
}

TEST_F(ImageTest_57, ClearXmpPacket_57) {
    auto img = createTestImage();
    img->setXmpPacket("<xmp>test</xmp>");
    img->clearXmpPacket();
    EXPECT_TRUE(img->xmpPacket().empty());
}

// =============================================================================
// writeXmpFromPacket() tests
// =============================================================================

TEST_F(ImageTest_57, WriteXmpFromPacketDefaultFalse_57) {
    auto img = createTestImage();
    EXPECT_FALSE(img->writeXmpFromPacket());
}

TEST_F(ImageTest_57, SetWriteXmpFromPacketTrue_57) {
    auto img = createTestImage();
    img->writeXmpFromPacket(true);
    EXPECT_TRUE(img->writeXmpFromPacket());
}

TEST_F(ImageTest_57, SetWriteXmpFromPacketFalse_57) {
    auto img = createTestImage();
    img->writeXmpFromPacket(true);
    img->writeXmpFromPacket(false);
    EXPECT_FALSE(img->writeXmpFromPacket());
}

// =============================================================================
// ICC Profile tests
// =============================================================================

TEST_F(ImageTest_57, IccProfileNotDefinedByDefault_57) {
    auto img = createTestImage();
    EXPECT_FALSE(img->iccProfileDefined());
}

TEST_F(ImageTest_57, ClearIccProfile_57) {
    auto img = createTestImage();
    img->clearIccProfile();
    EXPECT_FALSE(img->iccProfileDefined());
}

// =============================================================================
// clearMetadata() tests
// =============================================================================

TEST_F(ImageTest_57, ClearMetadataClearsAll_57) {
    auto img = createTestImage();
    
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    img->setExifData(exifData);
    
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test";
    img->setIptcData(iptcData);
    
    img->setComment("Test comment");
    
    img->clearMetadata();
    
    EXPECT_TRUE(img->exifData().empty());
    EXPECT_TRUE(img->iptcData().empty());
    EXPECT_TRUE(img->comment().empty());
}

// =============================================================================
// setMetadata() tests
// =============================================================================

TEST_F(ImageTest_57, SetMetadataFromAnotherImage_57) {
    auto src = createTestImage();
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "SourceMake";
    src->setExifData(exifData);
    src->setComment("Source comment");
    
    auto dst = createTestImage();
    dst->setMetadata(*src);
    
    EXPECT_FALSE(dst->exifData().empty());
    EXPECT_EQ(dst->comment(), "Source comment");
}

// =============================================================================
// good() tests
// =============================================================================

TEST_F(ImageTest_57, GoodReturnsTrueForValidIo_57) {
    auto img = createTestImage();
    // MemIo should be in a good state
    EXPECT_TRUE(img->good());
}

// =============================================================================
// io() tests
// =============================================================================

TEST_F(ImageTest_57, IoReturnsReference_57) {
    auto img = createTestImage();
    const Exiv2::BasicIo& io = img->io();
    // Just verify we can access it without crashing
    SUCCEED();
}

// =============================================================================
// nativePreviews() tests
// =============================================================================

TEST_F(ImageTest_57, NativePreviewsInitiallyEmpty_57) {
    auto img = createTestImage();
    EXPECT_TRUE(img->nativePreviews().empty());
}

// =============================================================================
// Static method tests: byteSwap
// =============================================================================

TEST_F(ImageTest_57, ByteSwap16NoSwap_57) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x1234u);
}

TEST_F(ImageTest_57, ByteSwap16WithSwap_57) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x3412u);
}

TEST_F(ImageTest_57, ByteSwap32NoSwap_57) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x12345678u);
}

TEST_F(ImageTest_57, ByteSwap32WithSwap_57) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x78563412u);
}

TEST_F(ImageTest_57, ByteSwap64NoSwap_57) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x0102030405060708ULL);
}

TEST_F(ImageTest_57, ByteSwap64WithSwap_57) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x0807060504030201ULL);
}

// =============================================================================
// Static method tests: platform endianness
// =============================================================================

TEST_F(ImageTest_57, PlatformEndianness_57) {
    // One of these must be true, and they should be mutually exclusive
    bool big = Exiv2::Image::isBigEndianPlatform();
    bool little = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_TRUE(big || little);
    EXPECT_NE(big, little);
}

// =============================================================================
// Static method tests: type classification
// =============================================================================

TEST_F(ImageTest_57, IsStringType_57) {
    // TIFF ASCII type is 2
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
    // TIFF LONG type is 4, should not be string
    EXPECT_FALSE(Exiv2::Image::isStringType(4));
}

TEST_F(ImageTest_57, IsShortType_57) {
    // TIFF SHORT type is 3
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
    EXPECT_FALSE(Exiv2::Image::isShortType(4));
}

TEST_F(ImageTest_57, IsLongType_57) {
    // TIFF LONG type is 4
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
    EXPECT_FALSE(Exiv2::Image::isLongType(3));
}

TEST_F(ImageTest_57, IsRationalType_57) {
    // TIFF RATIONAL type is 5
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
    EXPECT_FALSE(Exiv2::Image::isRationalType(3));
}

TEST_F(ImageTest_57, Is2ByteType_57) {
    // SHORT (3) is 2 bytes
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

TEST_F(ImageTest_57, Is4ByteType_57) {
    // LONG (4) is 4 bytes
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
}

TEST_F(ImageTest_57, Is8ByteType_57) {
    // RATIONAL (5) is 8 bytes
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
    EXPECT_FALSE(Exiv2::Image::is8ByteType(3));
}

// =============================================================================
// Static method tests: byteSwap with DataBuf
// =============================================================================

TEST_F(ImageTest_57, ByteSwap2WithDataBuf_57) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    
    uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 0, false);
    EXPECT_EQ(noSwap, 0x1234u);
    
    uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
    EXPECT_EQ(swapped, 0x3412u);
}

TEST_F(ImageTest_57, ByteSwap4WithDataBuf_57) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    buf.data()[2] = 0x56;
    buf.data()[3] = 0x78;
    
    uint32_t noSwap = Exiv2::Image::byteSwap4(buf, 0, false);
    EXPECT_EQ(noSwap, 0x12345678u);
    
    uint32_t swapped = Exiv2::Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(swapped, 0x78563412u);
}

TEST_F(ImageTest_57, ByteSwap8WithDataBuf_57) {
    Exiv2::DataBuf buf(16);
    buf.data()[0] = 0x01;
    buf.data()[1] = 0x02;
    buf.data()[2] = 0x03;
    buf.data()[3] = 0x04;
    buf.data()[4] = 0x05;
    buf.data()[5] = 0x06;
    buf.data()[6] = 0x07;
    buf.data()[7] = 0x08;
    
    uint64_t noSwap = Exiv2::Image::byteSwap8(buf, 0, false);
    EXPECT_EQ(noSwap, 0x0102030405060708ULL);
    
    uint64_t swapped = Exiv2::Image::byteSwap8(buf, 0, true);
    EXPECT_EQ(swapped, 0x0807060504030201ULL);
}

// =============================================================================
// Boundary: byteSwap with zero values
// =============================================================================

TEST_F(ImageTest_57, ByteSwap16Zero_57) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), false), 0u);
}

TEST_F(ImageTest_57, ByteSwap32Zero_57) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint32_t>(0), true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint32_t>(0), false), 0u);
}

TEST_F(ImageTest_57, ByteSwap64Zero_57) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint64_t>(0), true), 0ULL);
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint64_t>(0), false), 0ULL);
}

// =============================================================================
// Boundary: byteSwap with max values
// =============================================================================

TEST_F(ImageTest_57, ByteSwap16Max_57) {
    uint16_t maxVal = 0xFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(maxVal, true), 0xFFFFu);
    EXPECT_EQ(Exiv2::Image::byteSwap(maxVal, false), 0xFFFFu);
}

TEST_F(ImageTest_57, ByteSwap32Max_57) {
    uint32_t maxVal = 0xFFFFFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(maxVal, true), 0xFFFFFFFFu);
    EXPECT_EQ(Exiv2::Image::byteSwap(maxVal, false), 0xFFFFFFFFu);
}

// =============================================================================
// setTypeSupported tests
// =============================================================================

TEST_F(ImageTest_57, SetTypeSupportedChangesImageType_57) {
    auto img = createTestImage();
    EXPECT_EQ(img->imageType(), Exiv2::ImageType::none);
    img->setTypeSupported(Exiv2::ImageType::jpeg, 0xFFFF);
    EXPECT_EQ(img->imageType(), Exiv2::ImageType::jpeg);
}

// =============================================================================
// mimeType() test
// =============================================================================

TEST_F(ImageTest_57, MimeTypeReturnsExpectedValue_57) {
    auto img = createTestImage();
    EXPECT_EQ(img->mimeType(), "application/octet-stream");
}

// =============================================================================
// ByteSwap2 with offset in DataBuf
// =============================================================================

TEST_F(ImageTest_57, ByteSwap2WithOffset_57) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x00;
    buf.data()[1] = 0x00;
    buf.data()[2] = 0xAB;
    buf.data()[3] = 0xCD;
    
    uint16_t val = Exiv2::Image::byteSwap2(buf, 2, false);
    EXPECT_EQ(val, 0xABCDu);
    
    uint16_t swapped = Exiv2::Image::byteSwap2(buf, 2, true);
    EXPECT_EQ(swapped, 0xCDABu);
}

// =============================================================================
// Multiple set/clear cycles
// =============================================================================

TEST_F(ImageTest_57, MultipleSetClearCycles_57) {
    auto img = createTestImage();
    
    img->setComment("First");
    EXPECT_EQ(img->comment(), "First");
    
    img->clearComment();
    EXPECT_TRUE(img->comment().empty());
    
    img->setComment("Second");
    EXPECT_EQ(img->comment(), "Second");
    
    img->setComment("Third");
    EXPECT_EQ(img->comment(), "Third");
}

// =============================================================================
// isLongLongType tests
// =============================================================================

TEST_F(ImageTest_57, IsLongLongType_57) {
    // Type 16 is TIFF_LONG8
    EXPECT_TRUE(Exiv2::Image::isLongLongType(16));
    EXPECT_FALSE(Exiv2::Image::isLongLongType(4));
}

// =============================================================================
// Copy constructor and assignment are deleted
// =============================================================================
// These are compile-time checks; we verify that the class is non-copyable
// by not writing code that copies it (it wouldn't compile).

// =============================================================================
// isPrintXMP / isPrintICC tests
// =============================================================================

TEST_F(ImageTest_57, IsPrintXMPWithStringType_57) {
    // type 2 is string, with option kpsXMP
    bool result = Exiv2::Image::isPrintXMP(2, Exiv2::kpsXMP);
    // Behavior depends on implementation; just ensure no crash
    SUCCEED();
}

TEST_F(ImageTest_57, IsPrintICCWithStringType_57) {
    bool result = Exiv2::Image::isPrintICC(2, Exiv2::kpsIccProfile);
    SUCCEED();
}
