#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>

#include <memory>
#include <sstream>
#include <cstring>

// Since Image is abstract (readMetadata/writeMetadata are pure virtual in many subclasses),
// we need a concrete subclass for testing. We'll create a minimal one.
namespace {

class TestImage : public Exiv2::Image {
public:
    TestImage(std::unique_ptr<Exiv2::BasicIo> io)
        : Exiv2::Image(Exiv2::ImageType::none, 0xFFFF, std::move(io)) {}

    void readMetadata() override {}
    void writeMetadata() override {}
    std::string mimeType() const override { return "application/test"; }
};

std::unique_ptr<TestImage> createTestImage() {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<TestImage>(std::move(io));
}

}  // namespace

// ============================================================
// Test Fixture
// ============================================================
class ImageTest_1095 : public ::testing::Test {
protected:
    void SetUp() override {
        image_ = createTestImage();
    }

    std::unique_ptr<TestImage> image_;
};

// ============================================================
// nativePreviews tests
// ============================================================
TEST_F(ImageTest_1095, NativePreviewsInitiallyEmpty_1095) {
    const Exiv2::NativePreviewList& previews = image_->nativePreviews();
    EXPECT_TRUE(previews.empty());
}

// ============================================================
// Pixel dimensions tests
// ============================================================
TEST_F(ImageTest_1095, PixelWidthInitiallyZero_1095) {
    EXPECT_EQ(0u, image_->pixelWidth());
}

TEST_F(ImageTest_1095, PixelHeightInitiallyZero_1095) {
    EXPECT_EQ(0u, image_->pixelHeight());
}

// ============================================================
// Comment tests
// ============================================================
TEST_F(ImageTest_1095, CommentInitiallyEmpty_1095) {
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1095, SetCommentAndRetrieve_1095) {
    image_->setComment("Hello World");
    EXPECT_EQ("Hello World", image_->comment());
}

TEST_F(ImageTest_1095, ClearComment_1095) {
    image_->setComment("Some comment");
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1095, SetEmptyComment_1095) {
    image_->setComment("");
    EXPECT_EQ("", image_->comment());
}

TEST_F(ImageTest_1095, SetCommentOverwritesPrevious_1095) {
    image_->setComment("First");
    image_->setComment("Second");
    EXPECT_EQ("Second", image_->comment());
}

// ============================================================
// ExifData tests
// ============================================================
TEST_F(ImageTest_1095, ExifDataInitiallyEmpty_1095) {
    EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(ImageTest_1095, SetExifData_1095) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    EXPECT_FALSE(image_->exifData().empty());
}

TEST_F(ImageTest_1095, ClearExifData_1095) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

// ============================================================
// IptcData tests
// ============================================================
TEST_F(ImageTest_1095, IptcDataInitiallyEmpty_1095) {
    EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageTest_1095, SetIptcData_1095) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "TestCaption";
    image_->setIptcData(iptcData);
    EXPECT_FALSE(image_->iptcData().empty());
}

TEST_F(ImageTest_1095, ClearIptcData_1095) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "TestCaption";
    image_->setIptcData(iptcData);
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

// ============================================================
// XmpData tests
// ============================================================
TEST_F(ImageTest_1095, XmpDataInitiallyEmpty_1095) {
    EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageTest_1095, SetXmpData_1095) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test Title";
    image_->setXmpData(xmpData);
    EXPECT_FALSE(image_->xmpData().empty());
}

TEST_F(ImageTest_1095, ClearXmpData_1095) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test Title";
    image_->setXmpData(xmpData);
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// ============================================================
// XmpPacket tests
// ============================================================
TEST_F(ImageTest_1095, XmpPacketInitiallyEmpty_1095) {
    EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageTest_1095, SetXmpPacket_1095) {
    image_->setXmpPacket("<xmp>test</xmp>");
    EXPECT_EQ("<xmp>test</xmp>", image_->xmpPacket());
}

TEST_F(ImageTest_1095, ClearXmpPacket_1095) {
    image_->setXmpPacket("<xmp>test</xmp>");
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// ============================================================
// writeXmpFromPacket tests
// ============================================================
TEST_F(ImageTest_1095, WriteXmpFromPacketDefaultFalse_1095) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1095, SetWriteXmpFromPacketTrue_1095) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1095, SetWriteXmpFromPacketFalse_1095) {
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// ============================================================
// ByteOrder tests
// ============================================================
TEST_F(ImageTest_1095, ByteOrderDefaultInvalid_1095) {
    EXPECT_EQ(Exiv2::invalidByteOrder, image_->byteOrder());
}

TEST_F(ImageTest_1095, SetByteOrderLittleEndian_1095) {
    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(Exiv2::littleEndian, image_->byteOrder());
}

TEST_F(ImageTest_1095, SetByteOrderBigEndian_1095) {
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(Exiv2::bigEndian, image_->byteOrder());
}

// ============================================================
// good() tests
// ============================================================
TEST_F(ImageTest_1095, GoodOnFreshImage_1095) {
    // MemIo should be "good" initially
    EXPECT_TRUE(image_->good());
}

// ============================================================
// io() tests
// ============================================================
TEST_F(ImageTest_1095, IoReturnsValidReference_1095) {
    const Exiv2::BasicIo& io = image_->io();
    // The io object should exist; size of empty MemIo is 0
    EXPECT_EQ(0u, io.size());
}

// ============================================================
// mimeType tests
// ============================================================
TEST_F(ImageTest_1095, MimeTypeReturnsExpected_1095) {
    EXPECT_EQ("application/test", image_->mimeType());
}

// ============================================================
// clearMetadata tests
// ============================================================
TEST_F(ImageTest_1095, ClearMetadataClearsAll_1095) {
    // Set various metadata
    image_->setComment("test comment");
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Cap";
    image_->setIptcData(iptcData);

    image_->clearMetadata();

    EXPECT_TRUE(image_->comment().empty());
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// ============================================================
// setMetadata tests
// ============================================================
TEST_F(ImageTest_1095, SetMetadataFromAnotherImage_1095) {
    auto otherImage = createTestImage();
    otherImage->setComment("other comment");
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Model"] = "TestModel";
    otherImage->setExifData(exifData);

    image_->setMetadata(*otherImage);

    EXPECT_EQ("other comment", image_->comment());
    EXPECT_FALSE(image_->exifData().empty());
}

// ============================================================
// ICC Profile tests
// ============================================================
TEST_F(ImageTest_1095, IccProfileNotDefinedInitially_1095) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1095, ClearIccProfile_1095) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

// ============================================================
// Static utility: isStringType
// ============================================================
TEST_F(ImageTest_1095, IsStringTypeAscii_1095) {
    // TIFF type 2 is ASCII
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
}

TEST_F(ImageTest_1095, IsStringTypeNonString_1095) {
    // TIFF type 3 is SHORT
    EXPECT_FALSE(Exiv2::Image::isStringType(3));
}

// ============================================================
// Static utility: isShortType
// ============================================================
TEST_F(ImageTest_1095, IsShortType_1095) {
    // TIFF type 3 = SHORT, type 8 = SSHORT
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
    EXPECT_TRUE(Exiv2::Image::isShortType(8));
    EXPECT_FALSE(Exiv2::Image::isShortType(4));
}

// ============================================================
// Static utility: isLongType
// ============================================================
TEST_F(ImageTest_1095, IsLongType_1095) {
    // TIFF type 4 = LONG, type 9 = SLONG
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
    EXPECT_TRUE(Exiv2::Image::isLongType(9));
    EXPECT_FALSE(Exiv2::Image::isLongType(3));
}

// ============================================================
// Static utility: isRationalType
// ============================================================
TEST_F(ImageTest_1095, IsRationalType_1095) {
    // TIFF type 5 = RATIONAL, type 10 = SRATIONAL
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
    EXPECT_TRUE(Exiv2::Image::isRationalType(10));
    EXPECT_FALSE(Exiv2::Image::isRationalType(4));
}

// ============================================================
// Static utility: is2ByteType
// ============================================================
TEST_F(ImageTest_1095, Is2ByteType_1095) {
    // SHORT(3) and SSHORT(8) are 2-byte types
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
    EXPECT_TRUE(Exiv2::Image::is2ByteType(8));
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

// ============================================================
// Static utility: is4ByteType
// ============================================================
TEST_F(ImageTest_1095, Is4ByteType_1095) {
    // LONG(4), SLONG(9), FLOAT(11) are 4-byte types
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
    EXPECT_TRUE(Exiv2::Image::is4ByteType(9));
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
}

// ============================================================
// Static utility: is8ByteType
// ============================================================
TEST_F(ImageTest_1095, Is8ByteType_1095) {
    // RATIONAL(5), SRATIONAL(10), DOUBLE(12) are 8-byte types
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
    EXPECT_TRUE(Exiv2::Image::is8ByteType(10));
    EXPECT_FALSE(Exiv2::Image::is8ByteType(4));
}

// ============================================================
// Static utility: byteSwap uint16_t
// ============================================================
TEST_F(ImageTest_1095, ByteSwap16NoSwap_1095) {
    uint16_t val = 0x0102;
    EXPECT_EQ(val, Exiv2::Image::byteSwap(val, false));
}

TEST_F(ImageTest_1095, ByteSwap16WithSwap_1095) {
    uint16_t val = 0x0102;
    uint16_t expected = 0x0201;
    EXPECT_EQ(expected, Exiv2::Image::byteSwap(val, true));
}

// ============================================================
// Static utility: byteSwap uint32_t
// ============================================================
TEST_F(ImageTest_1095, ByteSwap32NoSwap_1095) {
    uint32_t val = 0x01020304;
    EXPECT_EQ(val, Exiv2::Image::byteSwap(val, false));
}

TEST_F(ImageTest_1095, ByteSwap32WithSwap_1095) {
    uint32_t val = 0x01020304;
    uint32_t expected = 0x04030201;
    EXPECT_EQ(expected, Exiv2::Image::byteSwap(val, true));
}

// ============================================================
// Static utility: byteSwap uint64_t
// ============================================================
TEST_F(ImageTest_1095, ByteSwap64NoSwap_1095) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(val, Exiv2::Image::byteSwap(val, false));
}

TEST_F(ImageTest_1095, ByteSwap64WithSwap_1095) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t expected = 0x0807060504030201ULL;
    EXPECT_EQ(expected, Exiv2::Image::byteSwap(val, true));
}

// ============================================================
// Platform endianness: at least one must be true
// ============================================================
TEST_F(ImageTest_1095, PlatformEndianness_1095) {
    bool big = Exiv2::Image::isBigEndianPlatform();
    bool little = Exiv2::Image::isLittleEndianPlatform();
    // Exactly one should be true
    EXPECT_NE(big, little);
}

// ============================================================
// imageType tests
// ============================================================
TEST_F(ImageTest_1095, ImageTypeReturnsNone_1095) {
    EXPECT_EQ(Exiv2::ImageType::none, image_->imageType());
}

// ============================================================
// Boundary: byteSwap with zero values
// ============================================================
TEST_F(ImageTest_1095, ByteSwap16Zero_1095) {
    EXPECT_EQ(0u, Exiv2::Image::byteSwap(static_cast<uint16_t>(0), true));
    EXPECT_EQ(0u, Exiv2::Image::byteSwap(static_cast<uint16_t>(0), false));
}

TEST_F(ImageTest_1095, ByteSwap32Zero_1095) {
    EXPECT_EQ(0u, Exiv2::Image::byteSwap(static_cast<uint32_t>(0), true));
    EXPECT_EQ(0u, Exiv2::Image::byteSwap(static_cast<uint32_t>(0), false));
}

TEST_F(ImageTest_1095, ByteSwap64Zero_1095) {
    EXPECT_EQ(0u, Exiv2::Image::byteSwap(static_cast<uint64_t>(0), true));
    EXPECT_EQ(0u, Exiv2::Image::byteSwap(static_cast<uint64_t>(0), false));
}

// ============================================================
// Boundary: byteSwap with max values
// ============================================================
TEST_F(ImageTest_1095, ByteSwap16Max_1095) {
    uint16_t val = 0xFFFF;
    EXPECT_EQ(val, Exiv2::Image::byteSwap(val, true));
    EXPECT_EQ(val, Exiv2::Image::byteSwap(val, false));
}

TEST_F(ImageTest_1095, ByteSwap32Max_1095) {
    uint32_t val = 0xFFFFFFFF;
    EXPECT_EQ(val, Exiv2::Image::byteSwap(val, true));
    EXPECT_EQ(val, Exiv2::Image::byteSwap(val, false));
}

TEST_F(ImageTest_1095, ByteSwap64Max_1095) {
    uint64_t val = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_EQ(val, Exiv2::Image::byteSwap(val, true));
    EXPECT_EQ(val, Exiv2::Image::byteSwap(val, false));
}

// ============================================================
// isStringType boundary: type 0
// ============================================================
TEST_F(ImageTest_1095, IsStringTypeZero_1095) {
    EXPECT_FALSE(Exiv2::Image::isStringType(0));
}

// ============================================================
// isLongLongType
// ============================================================
TEST_F(ImageTest_1095, IsLongLongType_1095) {
    // TIFF type 16 = LONG8, type 17 = SLONG8
    EXPECT_TRUE(Exiv2::Image::isLongLongType(16));
    EXPECT_TRUE(Exiv2::Image::isLongLongType(17));
    EXPECT_FALSE(Exiv2::Image::isLongLongType(4));
}

// ============================================================
// byteSwap2 from DataBuf
// ============================================================
TEST_F(ImageTest_1095, ByteSwap2FromBuf_1095) {
    Exiv2::DataBuf buf(4);
    buf.write_uint8(0, 0x01);
    buf.write_uint8(1, 0x02);
    
    uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
    
    // One should be the byte-swap of the other
    EXPECT_EQ(noSwap, Exiv2::Image::byteSwap(swapped, true));
}

// ============================================================
// byteSwap4 from DataBuf
// ============================================================
TEST_F(ImageTest_1095, ByteSwap4FromBuf_1095) {
    Exiv2::DataBuf buf(8);
    buf.write_uint8(0, 0x01);
    buf.write_uint8(1, 0x02);
    buf.write_uint8(2, 0x03);
    buf.write_uint8(3, 0x04);
    
    uint32_t noSwap = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t swapped = Exiv2::Image::byteSwap4(buf, 0, true);
    
    EXPECT_EQ(noSwap, Exiv2::Image::byteSwap(swapped, true));
}

// ============================================================
// byteSwap8 from DataBuf
// ============================================================
TEST_F(ImageTest_1095, ByteSwap8FromBuf_1095) {
    Exiv2::DataBuf buf(16);
    for (size_t i = 0; i < 8; ++i) {
        buf.write_uint8(i, static_cast<uint8_t>(i + 1));
    }
    
    uint64_t noSwap = Exiv2::Image::byteSwap8(buf, 0, false);
    uint64_t swapped = Exiv2::Image::byteSwap8(buf, 0, true);
    
    EXPECT_EQ(noSwap, Exiv2::Image::byteSwap(swapped, true));
}

// ============================================================
// setIccProfile with valid ICC header
// ============================================================
TEST_F(ImageTest_1095, SetIccProfileDefinesIt_1095) {
    // Minimal ICC profile: 128-byte header + tag table
    // The ICC signature "acsp" at offset 36
    Exiv2::DataBuf icc(128);
    std::memset(icc.data(), 0, 128);
    // Set profile size at offset 0 (big-endian)
    icc.write_uint8(0, 0);
    icc.write_uint8(1, 0);
    icc.write_uint8(2, 0);
    icc.write_uint8(3, 128);
    // Set "acsp" signature at offset 36
    icc.write_uint8(36, 'a');
    icc.write_uint8(37, 'c');
    icc.write_uint8(38, 's');
    icc.write_uint8(39, 'p');

    image_->setIccProfile(std::move(icc), false);
    EXPECT_TRUE(image_->iccProfileDefined());
}

// ============================================================
// Multiple clear operations should not crash
// ============================================================
TEST_F(ImageTest_1095, MultipleClearsDoNotCrash_1095) {
    image_->clearMetadata();
    image_->clearMetadata();
    image_->clearExifData();
    image_->clearIptcData();
    image_->clearXmpData();
    image_->clearXmpPacket();
    image_->clearComment();
    image_->clearIccProfile();
    SUCCEED();
}

// ============================================================
// Copy constructor is deleted
// ============================================================
TEST_F(ImageTest_1095, ImageIsNotCopyable_1095) {
    EXPECT_FALSE(std::is_copy_constructible<Exiv2::Image>::value);
    EXPECT_FALSE(std::is_copy_assignable<Exiv2::Image>::value);
}
