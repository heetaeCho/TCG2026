#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <memory>

// Since Image is abstract (has pure virtual methods like readMetadata/writeMetadata),
// we need a concrete subclass for testing. We'll use a minimal test image class.
namespace {

class TestImage : public Exiv2::Image {
public:
    TestImage(uint16_t supportedMetadata, std::unique_ptr<Exiv2::BasicIo> io)
        : Exiv2::Image(Exiv2::ImageType::none, supportedMetadata, std::move(io)) {}

    void readMetadata() override {}
    void writeMetadata() override {}
    std::string mimeType() const override { return "application/x-test"; }
};

std::unique_ptr<TestImage> createTestImage(uint16_t supportedMetadata = 0xFFFF) {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<TestImage>(supportedMetadata, std::move(io));
}

} // anonymous namespace

class ImageTest_1097 : public ::testing::Test {
protected:
    void SetUp() override {
        image_ = createTestImage();
    }

    std::unique_ptr<TestImage> image_;
};

// ==================== supportsMetadata tests ====================

TEST_F(ImageTest_1097, SupportsMetadataAll_1097) {
    auto img = createTestImage(0xFFFF);
    EXPECT_TRUE(img->supportsMetadata(Exiv2::mdExif));
    EXPECT_TRUE(img->supportsMetadata(Exiv2::mdIptc));
    EXPECT_TRUE(img->supportsMetadata(Exiv2::mdXmp));
    EXPECT_TRUE(img->supportsMetadata(Exiv2::mdComment));
    EXPECT_TRUE(img->supportsMetadata(Exiv2::mdIccProfile));
}

TEST_F(ImageTest_1097, SupportsMetadataNone_1097) {
    auto img = createTestImage(0);
    EXPECT_FALSE(img->supportsMetadata(Exiv2::mdExif));
    EXPECT_FALSE(img->supportsMetadata(Exiv2::mdIptc));
    EXPECT_FALSE(img->supportsMetadata(Exiv2::mdXmp));
    EXPECT_FALSE(img->supportsMetadata(Exiv2::mdComment));
    EXPECT_FALSE(img->supportsMetadata(Exiv2::mdIccProfile));
}

TEST_F(ImageTest_1097, SupportsMetadataOnlyExif_1097) {
    auto img = createTestImage(Exiv2::mdExif);
    EXPECT_TRUE(img->supportsMetadata(Exiv2::mdExif));
    EXPECT_FALSE(img->supportsMetadata(Exiv2::mdIptc));
    EXPECT_FALSE(img->supportsMetadata(Exiv2::mdXmp));
    EXPECT_FALSE(img->supportsMetadata(Exiv2::mdComment));
}

TEST_F(ImageTest_1097, SupportsMetadataOnlyIptc_1097) {
    auto img = createTestImage(Exiv2::mdIptc);
    EXPECT_FALSE(img->supportsMetadata(Exiv2::mdExif));
    EXPECT_TRUE(img->supportsMetadata(Exiv2::mdIptc));
    EXPECT_FALSE(img->supportsMetadata(Exiv2::mdXmp));
}

TEST_F(ImageTest_1097, SupportsMetadataOnlyXmp_1097) {
    auto img = createTestImage(Exiv2::mdXmp);
    EXPECT_FALSE(img->supportsMetadata(Exiv2::mdExif));
    EXPECT_FALSE(img->supportsMetadata(Exiv2::mdIptc));
    EXPECT_TRUE(img->supportsMetadata(Exiv2::mdXmp));
}

TEST_F(ImageTest_1097, SupportsMetadataExifAndIptc_1097) {
    auto img = createTestImage(Exiv2::mdExif | Exiv2::mdIptc);
    EXPECT_TRUE(img->supportsMetadata(Exiv2::mdExif));
    EXPECT_TRUE(img->supportsMetadata(Exiv2::mdIptc));
    EXPECT_FALSE(img->supportsMetadata(Exiv2::mdXmp));
}

// ==================== byteOrder tests ====================

TEST_F(ImageTest_1097, DefaultByteOrderIsInvalid_1097) {
    EXPECT_EQ(image_->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageTest_1097, SetByteOrderBigEndian_1097) {
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);
}

TEST_F(ImageTest_1097, SetByteOrderLittleEndian_1097) {
    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::littleEndian);
}

// ==================== comment tests ====================

TEST_F(ImageTest_1097, DefaultCommentIsEmpty_1097) {
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1097, SetComment_1097) {
    image_->setComment("Hello World");
    EXPECT_EQ(image_->comment(), "Hello World");
}

TEST_F(ImageTest_1097, ClearComment_1097) {
    image_->setComment("Test comment");
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1097, SetEmptyComment_1097) {
    image_->setComment("");
    EXPECT_TRUE(image_->comment().empty());
}

// ==================== writeXmpFromPacket tests ====================

TEST_F(ImageTest_1097, DefaultWriteXmpFromPacketIsFalse_1097) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1097, SetWriteXmpFromPacketTrue_1097) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1097, SetWriteXmpFromPacketFalse_1097) {
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// ==================== pixelWidth/Height tests ====================

TEST_F(ImageTest_1097, DefaultPixelWidthIsZero_1097) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(ImageTest_1097, DefaultPixelHeightIsZero_1097) {
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// ==================== ExifData tests ====================

TEST_F(ImageTest_1097, ExifDataDefaultEmpty_1097) {
    EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(ImageTest_1097, SetAndClearExifData_1097) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    EXPECT_FALSE(image_->exifData().empty());
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

// ==================== IptcData tests ====================

TEST_F(ImageTest_1097, IptcDataDefaultEmpty_1097) {
    EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageTest_1097, SetAndClearIptcData_1097) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test";
    image_->setIptcData(iptcData);
    EXPECT_FALSE(image_->iptcData().empty());
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

// ==================== XmpData tests ====================

TEST_F(ImageTest_1097, XmpDataDefaultEmpty_1097) {
    EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageTest_1097, SetAndClearXmpData_1097) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test";
    image_->setXmpData(xmpData);
    EXPECT_FALSE(image_->xmpData().empty());
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// ==================== XmpPacket tests ====================

TEST_F(ImageTest_1097, XmpPacketDefaultEmpty_1097) {
    EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageTest_1097, SetAndClearXmpPacket_1097) {
    image_->setXmpPacket("<x:xmpmeta/>");
    EXPECT_EQ(image_->xmpPacket(), "<x:xmpmeta/>");
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// ==================== clearMetadata tests ====================

TEST_F(ImageTest_1097, ClearMetadataClearsAll_1097) {
    image_->setComment("test");
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    
    image_->clearMetadata();
    
    EXPECT_TRUE(image_->comment().empty());
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// ==================== ICC Profile tests ====================

TEST_F(ImageTest_1097, DefaultIccProfileNotDefined_1097) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1097, ClearIccProfile_1097) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

// ==================== good() tests ====================

TEST_F(ImageTest_1097, GoodOnFreshImage_1097) {
    // MemIo should report good
    EXPECT_TRUE(image_->good());
}

// ==================== mimeType tests ====================

TEST_F(ImageTest_1097, MimeType_1097) {
    EXPECT_EQ(image_->mimeType(), "application/x-test");
}

// ==================== imageType tests ====================

TEST_F(ImageTest_1097, ImageTypeIsNone_1097) {
    EXPECT_EQ(image_->imageType(), Exiv2::ImageType::none);
}

// ==================== Static method tests ====================

TEST_F(ImageTest_1097, IsBigOrLittleEndianPlatform_1097) {
    // One of them must be true, and they should be complementary
    bool big = Exiv2::Image::isBigEndianPlatform();
    bool little = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_NE(big, little);
}

// ==================== byteSwap tests ====================

TEST_F(ImageTest_1097, ByteSwap16NoSwap_1097) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1097, ByteSwap16WithSwap_1097) {
    uint16_t val = 0x1234;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x3412);
}

TEST_F(ImageTest_1097, ByteSwap32NoSwap_1097) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1097, ByteSwap32WithSwap_1097) {
    uint32_t val = 0x12345678;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x78563412u);
}

TEST_F(ImageTest_1097, ByteSwap64NoSwap_1097) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1097, ByteSwap64WithSwap_1097) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0807060504030201ULL);
}

// ==================== isStringType tests ====================

TEST_F(ImageTest_1097, IsStringType_1097) {
    // Type 2 is ASCII in TIFF
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
    // Type 1 (BYTE) should not be string type
    EXPECT_FALSE(Exiv2::Image::isStringType(1));
}

// ==================== isShortType tests ====================

TEST_F(ImageTest_1097, IsShortType_1097) {
    // Type 3 is SHORT in TIFF
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
    EXPECT_FALSE(Exiv2::Image::isShortType(2));
}

// ==================== isLongType tests ====================

TEST_F(ImageTest_1097, IsLongType_1097) {
    // Type 4 is LONG in TIFF
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
    EXPECT_FALSE(Exiv2::Image::isLongType(3));
}

// ==================== isRationalType tests ====================

TEST_F(ImageTest_1097, IsRationalType_1097) {
    // Type 5 is RATIONAL in TIFF
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
    EXPECT_FALSE(Exiv2::Image::isRationalType(4));
}

// ==================== is2ByteType tests ====================

TEST_F(ImageTest_1097, Is2ByteType_1097) {
    // SHORT (3) is 2 bytes
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

// ==================== is4ByteType tests ====================

TEST_F(ImageTest_1097, Is4ByteType_1097) {
    // LONG (4) is 4 bytes
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
}

// ==================== is8ByteType tests ====================

TEST_F(ImageTest_1097, Is8ByteType_1097) {
    // RATIONAL (5) is 8 bytes
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
    EXPECT_FALSE(Exiv2::Image::is8ByteType(4));
}

// ==================== setMetadata tests ====================

TEST_F(ImageTest_1097, SetMetadataCopiesFromOtherImage_1097) {
    auto other = createTestImage();
    other->setComment("Other comment");
    Exiv2::ExifData exif;
    exif["Exif.Image.Make"] = "CopyTest";
    other->setExifData(exif);

    image_->setMetadata(*other);
    
    EXPECT_EQ(image_->comment(), "Other comment");
    EXPECT_FALSE(image_->exifData().empty());
}

// ==================== nativePreviews tests ====================

TEST_F(ImageTest_1097, NativePreviewsDefaultEmpty_1097) {
    EXPECT_TRUE(image_->nativePreviews().empty());
}

// ==================== io() tests ====================

TEST_F(ImageTest_1097, IoAccessible_1097) {
    // Just verify we can access io without crashing
    const Exiv2::BasicIo& io = image_->io();
    (void)io;
    SUCCEED();
}

// ==================== byteSwap2/4/8 from DataBuf ====================

TEST_F(ImageTest_1097, ByteSwap2FromDataBuf_1097) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    
    uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
    
    // One should be 0x1234, the other 0x3412, depending on platform endianness
    EXPECT_NE(noSwap, swapped);
}

TEST_F(ImageTest_1097, ByteSwap4FromDataBuf_1097) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    buf.data()[2] = 0x56;
    buf.data()[3] = 0x78;
    
    uint32_t noSwap = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t swapped = Exiv2::Image::byteSwap4(buf, 0, true);
    
    EXPECT_NE(noSwap, swapped);
}

TEST_F(ImageTest_1097, ByteSwap8FromDataBuf_1097) {
    Exiv2::DataBuf buf(16);
    for (int i = 0; i < 8; i++) {
        buf.data()[i] = static_cast<uint8_t>(i + 1);
    }
    
    uint64_t noSwap = Exiv2::Image::byteSwap8(buf, 0, false);
    uint64_t swapped = Exiv2::Image::byteSwap8(buf, 0, true);
    
    EXPECT_NE(noSwap, swapped);
}

// ==================== Boundary: byteSwap with zero values ====================

TEST_F(ImageTest_1097, ByteSwap16ZeroValue_1097) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), false), 0u);
}

TEST_F(ImageTest_1097, ByteSwap32ZeroValue_1097) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint32_t>(0), true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint32_t>(0), false), 0u);
}

TEST_F(ImageTest_1097, ByteSwap64ZeroValue_1097) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint64_t>(0), true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint64_t>(0), false), 0u);
}

// ==================== Boundary: byteSwap with max values ====================

TEST_F(ImageTest_1097, ByteSwap16MaxValue_1097) {
    uint16_t maxVal = 0xFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(maxVal, true), maxVal);
    EXPECT_EQ(Exiv2::Image::byteSwap(maxVal, false), maxVal);
}

TEST_F(ImageTest_1097, ByteSwap32MaxValue_1097) {
    uint32_t maxVal = 0xFFFFFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(maxVal, true), maxVal);
    EXPECT_EQ(Exiv2::Image::byteSwap(maxVal, false), maxVal);
}

TEST_F(ImageTest_1097, ByteSwap64MaxValue_1097) {
    uint64_t maxVal = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(maxVal, true), maxVal);
    EXPECT_EQ(Exiv2::Image::byteSwap(maxVal, false), maxVal);
}

// ==================== Double swap should return original ====================

TEST_F(ImageTest_1097, ByteSwap16DoubleSwapReturnsOriginal_1097) {
    uint16_t val = 0xABCD;
    uint16_t result = Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true);
    EXPECT_EQ(result, val);
}

TEST_F(ImageTest_1097, ByteSwap32DoubleSwapReturnsOriginal_1097) {
    uint32_t val = 0xDEADBEEF;
    uint32_t result = Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true);
    EXPECT_EQ(result, val);
}

TEST_F(ImageTest_1097, ByteSwap64DoubleSwapReturnsOriginal_1097) {
    uint64_t val = 0xDEADBEEFCAFEBABEULL;
    uint64_t result = Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true);
    EXPECT_EQ(result, val);
}

// ==================== setTypeSupported tests ====================

TEST_F(ImageTest_1097, SetTypeSupportedChangesMetadataSupport_1097) {
    auto img = createTestImage(0);
    EXPECT_FALSE(img->supportsMetadata(Exiv2::mdExif));
    
    img->setTypeSupported(Exiv2::ImageType::none, Exiv2::mdExif | Exiv2::mdIptc);
    EXPECT_TRUE(img->supportsMetadata(Exiv2::mdExif));
    EXPECT_TRUE(img->supportsMetadata(Exiv2::mdIptc));
    EXPECT_FALSE(img->supportsMetadata(Exiv2::mdXmp));
}
