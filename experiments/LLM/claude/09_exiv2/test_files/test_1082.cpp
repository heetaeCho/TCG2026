#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <sstream>
#include <memory>

// A concrete subclass of Image for testing, since Image has pure virtual methods
// We use a minimal concrete image type - JpegImage or create a test wrapper
// Since Image is abstract, we need a concrete subclass for testing

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
    std::string mimeType() const override { return "application/octet-stream"; }
};

std::unique_ptr<TestImage> createTestImage() {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<TestImage>(std::move(io));
}

} // anonymous namespace

class ImageTest_1082 : public ::testing::Test {
protected:
    std::unique_ptr<TestImage> image_;

    void SetUp() override {
        image_ = createTestImage();
    }
};

// ==================== clearComment tests ====================

TEST_F(ImageTest_1082, ClearCommentOnEmptyComment_1082) {
    // Comment should already be empty by default
    image_->clearComment();
    EXPECT_EQ(image_->comment(), "");
}

TEST_F(ImageTest_1082, ClearCommentAfterSettingComment_1082) {
    image_->setComment("Hello, World!");
    EXPECT_EQ(image_->comment(), "Hello, World!");
    image_->clearComment();
    EXPECT_EQ(image_->comment(), "");
}

TEST_F(ImageTest_1082, ClearCommentMultipleTimes_1082) {
    image_->setComment("Test");
    image_->clearComment();
    image_->clearComment();
    EXPECT_EQ(image_->comment(), "");
}

// ==================== setComment / comment tests ====================

TEST_F(ImageTest_1082, SetCommentNormal_1082) {
    image_->setComment("A test comment");
    EXPECT_EQ(image_->comment(), "A test comment");
}

TEST_F(ImageTest_1082, SetCommentEmptyString_1082) {
    image_->setComment("");
    EXPECT_EQ(image_->comment(), "");
}

TEST_F(ImageTest_1082, SetCommentOverwrite_1082) {
    image_->setComment("First");
    image_->setComment("Second");
    EXPECT_EQ(image_->comment(), "Second");
}

TEST_F(ImageTest_1082, SetCommentWithSpecialChars_1082) {
    std::string special = "Comment with\nnewline\tand\ttabs";
    image_->setComment(special);
    EXPECT_EQ(image_->comment(), special);
}

TEST_F(ImageTest_1082, SetCommentWithUnicode_1082) {
    std::string unicode = "Ünïcödé tëst 日本語";
    image_->setComment(unicode);
    EXPECT_EQ(image_->comment(), unicode);
}

TEST_F(ImageTest_1082, SetCommentLongString_1082) {
    std::string longStr(10000, 'x');
    image_->setComment(longStr);
    EXPECT_EQ(image_->comment(), longStr);
}

// ==================== ExifData tests ====================

TEST_F(ImageTest_1082, ExifDataInitiallyEmpty_1082) {
    EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(ImageTest_1082, SetExifDataAndRetrieve_1082) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    EXPECT_FALSE(image_->exifData().empty());
}

TEST_F(ImageTest_1082, ClearExifData_1082) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

// ==================== IptcData tests ====================

TEST_F(ImageTest_1082, IptcDataInitiallyEmpty_1082) {
    EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageTest_1082, SetIptcDataAndRetrieve_1082) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "TestCaption";
    image_->setIptcData(iptcData);
    EXPECT_FALSE(image_->iptcData().empty());
}

TEST_F(ImageTest_1082, ClearIptcData_1082) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "TestCaption";
    image_->setIptcData(iptcData);
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

// ==================== XmpData tests ====================

TEST_F(ImageTest_1082, XmpDataInitiallyEmpty_1082) {
    EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageTest_1082, SetXmpDataAndRetrieve_1082) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "TestTitle";
    image_->setXmpData(xmpData);
    EXPECT_FALSE(image_->xmpData().empty());
}

TEST_F(ImageTest_1082, ClearXmpData_1082) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "TestTitle";
    image_->setXmpData(xmpData);
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// ==================== XmpPacket tests ====================

TEST_F(ImageTest_1082, XmpPacketInitiallyEmpty_1082) {
    EXPECT_EQ(image_->xmpPacket(), "");
}

TEST_F(ImageTest_1082, SetXmpPacketAndRetrieve_1082) {
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    image_->setXmpPacket(packet);
    EXPECT_EQ(image_->xmpPacket(), packet);
}

TEST_F(ImageTest_1082, ClearXmpPacket_1082) {
    image_->setXmpPacket("<x:xmpmeta>test</x:xmpmeta>");
    image_->clearXmpPacket();
    EXPECT_EQ(image_->xmpPacket(), "");
}

// ==================== clearMetadata tests ====================

TEST_F(ImageTest_1082, ClearMetadataClearsAll_1082) {
    image_->setComment("TestComment");
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    
    image_->clearMetadata();
    
    EXPECT_EQ(image_->comment(), "");
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->xmpData().empty());
}

// ==================== writeXmpFromPacket tests ====================

TEST_F(ImageTest_1082, WriteXmpFromPacketDefault_1082) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1082, WriteXmpFromPacketSetTrue_1082) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1082, WriteXmpFromPacketSetFalse_1082) {
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// ==================== byteOrder tests ====================

TEST_F(ImageTest_1082, ByteOrderDefaultInvalid_1082) {
    EXPECT_EQ(image_->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageTest_1082, SetByteOrderLittleEndian_1082) {
    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::littleEndian);
}

TEST_F(ImageTest_1082, SetByteOrderBigEndian_1082) {
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);
}

// ==================== pixelWidth / pixelHeight tests ====================

TEST_F(ImageTest_1082, PixelWidthDefaultZero_1082) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(ImageTest_1082, PixelHeightDefaultZero_1082) {
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// ==================== good() tests ====================

TEST_F(ImageTest_1082, GoodAfterConstruction_1082) {
    // MemIo should be in a good state
    EXPECT_TRUE(image_->good());
}

// ==================== iccProfile tests ====================

TEST_F(ImageTest_1082, IccProfileNotDefinedByDefault_1082) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1082, ClearIccProfileOnEmpty_1082) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

// ==================== io() tests ====================

TEST_F(ImageTest_1082, IoReturnsValidReference_1082) {
    const Exiv2::BasicIo& io = image_->io();
    // Should not crash and io should exist
    (void)io;
}

// ==================== nativePreviews tests ====================

TEST_F(ImageTest_1082, NativePreviewsInitiallyEmpty_1082) {
    EXPECT_TRUE(image_->nativePreviews().empty());
}

// ==================== static byteSwap tests ====================

TEST_F(ImageTest_1082, ByteSwap16NoSwap_1082) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1082, ByteSwap16WithSwap_1082) {
    uint16_t val = 0x1234;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x3412);
}

TEST_F(ImageTest_1082, ByteSwap32NoSwap_1082) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1082, ByteSwap32WithSwap_1082) {
    uint32_t val = 0x12345678;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x78563412u);
}

TEST_F(ImageTest_1082, ByteSwap64NoSwap_1082) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1082, ByteSwap64WithSwap_1082) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0807060504030201ULL);
}

// ==================== static platform endianness tests ====================

TEST_F(ImageTest_1082, PlatformEndianConsistency_1082) {
    // Exactly one of big/little should be true
    bool big = Exiv2::Image::isBigEndianPlatform();
    bool little = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_NE(big, little);
}

// ==================== static type check tests ====================

TEST_F(ImageTest_1082, IsStringType_1082) {
    // TIFF ASCII type is 2
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
    EXPECT_FALSE(Exiv2::Image::isStringType(3)); // SHORT
}

TEST_F(ImageTest_1082, IsShortType_1082) {
    // TIFF SHORT type is 3
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
    EXPECT_FALSE(Exiv2::Image::isShortType(2));
}

TEST_F(ImageTest_1082, IsLongType_1082) {
    // TIFF LONG type is 4
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
    EXPECT_FALSE(Exiv2::Image::isLongType(3));
}

TEST_F(ImageTest_1082, IsRationalType_1082) {
    // TIFF RATIONAL type is 5
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
    EXPECT_FALSE(Exiv2::Image::isRationalType(4));
}

TEST_F(ImageTest_1082, Is2ByteType_1082) {
    // SHORT (3) and SSHORT (8) are 2-byte types
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
    EXPECT_TRUE(Exiv2::Image::is2ByteType(8));
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

TEST_F(ImageTest_1082, Is4ByteType_1082) {
    // LONG (4) and SLONG (9) are 4-byte types
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
    EXPECT_TRUE(Exiv2::Image::is4ByteType(9));
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
}

TEST_F(ImageTest_1082, Is8ByteType_1082) {
    // RATIONAL (5) and SRATIONAL (10) are 8-byte types
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
    EXPECT_TRUE(Exiv2::Image::is8ByteType(10));
    EXPECT_FALSE(Exiv2::Image::is8ByteType(4));
}

// ==================== byteSwap with DataBuf tests ====================

TEST_F(ImageTest_1082, ByteSwap2FromBuf_1082) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    
    uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 0, false);
    EXPECT_EQ(noSwap, 0x1234);
    
    uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
    EXPECT_EQ(swapped, 0x3412);
}

TEST_F(ImageTest_1082, ByteSwap4FromBuf_1082) {
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

TEST_F(ImageTest_1082, ByteSwap8FromBuf_1082) {
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

// ==================== setMetadata tests ====================

TEST_F(ImageTest_1082, SetMetadataFromAnotherImage_1082) {
    auto otherImage = createTestImage();
    otherImage->setComment("Other comment");
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "OtherMake";
    otherImage->setExifData(exifData);
    
    image_->setMetadata(*otherImage);
    
    EXPECT_EQ(image_->comment(), "Other comment");
    EXPECT_FALSE(image_->exifData().empty());
}

// ==================== imageType tests ====================

TEST_F(ImageTest_1082, ImageTypeReturnsConstructedType_1082) {
    EXPECT_EQ(image_->imageType(), Exiv2::ImageType::none);
}

// ==================== mimeType tests ====================

TEST_F(ImageTest_1082, MimeTypeReturnsExpected_1082) {
    // Our TestImage override returns "application/octet-stream"
    EXPECT_EQ(image_->mimeType(), "application/octet-stream");
}

// ==================== ByteSwap boundary: zero values ====================

TEST_F(ImageTest_1082, ByteSwap16Zero_1082) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), false), 0u);
}

TEST_F(ImageTest_1082, ByteSwap32Zero_1082) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint32_t>(0), true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint32_t>(0), false), 0u);
}

TEST_F(ImageTest_1082, ByteSwap64Zero_1082) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint64_t>(0), true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint64_t>(0), false), 0u);
}

// ==================== ByteSwap boundary: max values ====================

TEST_F(ImageTest_1082, ByteSwap16Max_1082) {
    uint16_t maxVal = 0xFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(maxVal, true), maxVal);
    EXPECT_EQ(Exiv2::Image::byteSwap(maxVal, false), maxVal);
}

TEST_F(ImageTest_1082, ByteSwap32Max_1082) {
    uint32_t maxVal = 0xFFFFFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(maxVal, true), maxVal);
    EXPECT_EQ(Exiv2::Image::byteSwap(maxVal, false), maxVal);
}

TEST_F(ImageTest_1082, ByteSwap64Max_1082) {
    uint64_t maxVal = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(maxVal, true), maxVal);
    EXPECT_EQ(Exiv2::Image::byteSwap(maxVal, false), maxVal);
}

// ==================== ByteSwap with offset in buffer ====================

TEST_F(ImageTest_1082, ByteSwap2WithOffset_1082) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x00;
    buf.data()[1] = 0x00;
    buf.data()[2] = 0xAB;
    buf.data()[3] = 0xCD;
    
    uint16_t val = Exiv2::Image::byteSwap2(buf, 2, false);
    EXPECT_EQ(val, 0xABCD);
    
    uint16_t swapped = Exiv2::Image::byteSwap2(buf, 2, true);
    EXPECT_EQ(swapped, 0xCDAB);
}

// ==================== Double swap restores original ====================

TEST_F(ImageTest_1082, DoubleSwap16RestoresOriginal_1082) {
    uint16_t original = 0x1234;
    uint16_t swapped = Exiv2::Image::byteSwap(original, true);
    uint16_t restored = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(restored, original);
}

TEST_F(ImageTest_1082, DoubleSwap32RestoresOriginal_1082) {
    uint32_t original = 0x12345678;
    uint32_t swapped = Exiv2::Image::byteSwap(original, true);
    uint32_t restored = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(restored, original);
}

TEST_F(ImageTest_1082, DoubleSwap64RestoresOriginal_1082) {
    uint64_t original = 0x0102030405060708ULL;
    uint64_t swapped = Exiv2::Image::byteSwap(original, true);
    uint64_t restored = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(restored, original);
}
