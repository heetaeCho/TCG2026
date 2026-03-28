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

// We need a concrete Image subclass since Image is abstract (has pure virtual methods)
// We'll use a minimal concrete subclass for testing purposes.
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

}  // namespace

class ImageTest_1091 : public ::testing::Test {
protected:
    std::unique_ptr<TestImage> img;

    void SetUp() override {
        img = createTestImage();
    }
};

// ========== pixelWidth / pixelHeight ==========

TEST_F(ImageTest_1091, PixelWidthDefaultIsZero_1091) {
    EXPECT_EQ(img->pixelWidth(), 0u);
}

TEST_F(ImageTest_1091, PixelHeightDefaultIsZero_1091) {
    EXPECT_EQ(img->pixelHeight(), 0u);
}

// ========== comment ==========

TEST_F(ImageTest_1091, CommentDefaultIsEmpty_1091) {
    EXPECT_TRUE(img->comment().empty());
}

TEST_F(ImageTest_1091, SetCommentAndRetrieve_1091) {
    img->setComment("Hello, World!");
    EXPECT_EQ(img->comment(), "Hello, World!");
}

TEST_F(ImageTest_1091, ClearComment_1091) {
    img->setComment("test comment");
    img->clearComment();
    EXPECT_TRUE(img->comment().empty());
}

TEST_F(ImageTest_1091, SetCommentEmpty_1091) {
    img->setComment("");
    EXPECT_TRUE(img->comment().empty());
}

// ========== ExifData ==========

TEST_F(ImageTest_1091, ExifDataDefaultIsEmpty_1091) {
    EXPECT_TRUE(img->exifData().empty());
}

TEST_F(ImageTest_1091, SetExifDataAndRetrieve_1091) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    img->setExifData(exifData);
    EXPECT_FALSE(img->exifData().empty());
}

TEST_F(ImageTest_1091, ClearExifData_1091) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    img->setExifData(exifData);
    img->clearExifData();
    EXPECT_TRUE(img->exifData().empty());
}

// ========== IptcData ==========

TEST_F(ImageTest_1091, IptcDataDefaultIsEmpty_1091) {
    EXPECT_TRUE(img->iptcData().empty());
}

TEST_F(ImageTest_1091, SetIptcDataAndRetrieve_1091) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test Caption";
    img->setIptcData(iptcData);
    EXPECT_FALSE(img->iptcData().empty());
}

TEST_F(ImageTest_1091, ClearIptcData_1091) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test Caption";
    img->setIptcData(iptcData);
    img->clearIptcData();
    EXPECT_TRUE(img->iptcData().empty());
}

// ========== XmpData ==========

TEST_F(ImageTest_1091, XmpDataDefaultIsEmpty_1091) {
    EXPECT_TRUE(img->xmpData().empty());
}

TEST_F(ImageTest_1091, ClearXmpData_1091) {
    img->clearXmpData();
    EXPECT_TRUE(img->xmpData().empty());
}

// ========== XmpPacket ==========

TEST_F(ImageTest_1091, XmpPacketDefaultIsEmpty_1091) {
    EXPECT_TRUE(img->xmpPacket().empty());
}

TEST_F(ImageTest_1091, SetXmpPacketAndRetrieve_1091) {
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    img->setXmpPacket(packet);
    EXPECT_EQ(img->xmpPacket(), packet);
}

TEST_F(ImageTest_1091, ClearXmpPacket_1091) {
    img->setXmpPacket("<x:xmpmeta>test</x:xmpmeta>");
    img->clearXmpPacket();
    EXPECT_TRUE(img->xmpPacket().empty());
}

// ========== writeXmpFromPacket ==========

TEST_F(ImageTest_1091, WriteXmpFromPacketDefaultIsFalse_1091) {
    EXPECT_FALSE(img->writeXmpFromPacket());
}

TEST_F(ImageTest_1091, SetWriteXmpFromPacketTrue_1091) {
    img->writeXmpFromPacket(true);
    EXPECT_TRUE(img->writeXmpFromPacket());
}

TEST_F(ImageTest_1091, SetWriteXmpFromPacketFalse_1091) {
    img->writeXmpFromPacket(true);
    img->writeXmpFromPacket(false);
    EXPECT_FALSE(img->writeXmpFromPacket());
}

// ========== byteOrder ==========

TEST_F(ImageTest_1091, ByteOrderDefaultIsInvalid_1091) {
    EXPECT_EQ(img->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageTest_1091, SetByteOrderLittleEndian_1091) {
    img->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(img->byteOrder(), Exiv2::littleEndian);
}

TEST_F(ImageTest_1091, SetByteOrderBigEndian_1091) {
    img->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(img->byteOrder(), Exiv2::bigEndian);
}

// ========== good ==========

TEST_F(ImageTest_1091, GoodReturnsBasedOnIoState_1091) {
    // MemIo should initially be in a good state
    EXPECT_TRUE(img->good());
}

// ========== io ==========

TEST_F(ImageTest_1091, IoReturnsReference_1091) {
    const Exiv2::BasicIo& io = img->io();
    // Just verify it doesn't crash and returns a reference
    (void)io;
}

// ========== mimeType ==========

TEST_F(ImageTest_1091, MimeTypeReturnsExpected_1091) {
    EXPECT_EQ(img->mimeType(), "application/octet-stream");
}

// ========== clearMetadata ==========

TEST_F(ImageTest_1091, ClearMetadataClearsAll_1091) {
    img->setComment("test");
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "Test";
    img->setExifData(exifData);
    
    img->clearMetadata();
    
    EXPECT_TRUE(img->comment().empty());
    EXPECT_TRUE(img->exifData().empty());
    EXPECT_TRUE(img->iptcData().empty());
    EXPECT_TRUE(img->xmpData().empty());
    EXPECT_TRUE(img->xmpPacket().empty());
}

// ========== setMetadata ==========

TEST_F(ImageTest_1091, SetMetadataFromAnotherImage_1091) {
    auto img2 = createTestImage();
    img2->setComment("copied comment");
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "CopiedMake";
    img2->setExifData(exifData);
    
    img->setMetadata(*img2);
    
    EXPECT_EQ(img->comment(), "copied comment");
    EXPECT_FALSE(img->exifData().empty());
}

// ========== ICC Profile ==========

TEST_F(ImageTest_1091, IccProfileDefaultNotDefined_1091) {
    EXPECT_FALSE(img->iccProfileDefined());
}

TEST_F(ImageTest_1091, ClearIccProfile_1091) {
    img->clearIccProfile();
    EXPECT_FALSE(img->iccProfileDefined());
}

// ========== nativePreviews ==========

TEST_F(ImageTest_1091, NativePreviewsDefaultIsEmpty_1091) {
    EXPECT_TRUE(img->nativePreviews().empty());
}

// ========== imageType ==========

TEST_F(ImageTest_1091, ImageTypeReturnsSetType_1091) {
    EXPECT_EQ(img->imageType(), Exiv2::ImageType::none);
}

// ========== Static utility functions ==========

TEST_F(ImageTest_1091, IsBigEndianOrLittleEndian_1091) {
    // One must be true, and they should be complementary
    bool isBig = Exiv2::Image::isBigEndianPlatform();
    bool isLittle = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_NE(isBig, isLittle);
}

// ========== byteSwap uint16_t ==========

TEST_F(ImageTest_1091, ByteSwap16NoSwap_1091) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x1234u);
}

TEST_F(ImageTest_1091, ByteSwap16WithSwap_1091) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x3412u);
}

TEST_F(ImageTest_1091, ByteSwap16Zero_1091) {
    uint16_t val = 0x0000;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x0000u);
}

TEST_F(ImageTest_1091, ByteSwap16Max_1091) {
    uint16_t val = 0xFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFu);
}

// ========== byteSwap uint32_t ==========

TEST_F(ImageTest_1091, ByteSwap32NoSwap_1091) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x12345678u);
}

TEST_F(ImageTest_1091, ByteSwap32WithSwap_1091) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x78563412u);
}

TEST_F(ImageTest_1091, ByteSwap32Zero_1091) {
    uint32_t val = 0x00000000;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x00000000u);
}

// ========== byteSwap uint64_t ==========

TEST_F(ImageTest_1091, ByteSwap64NoSwap_1091) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x0102030405060708ULL);
}

TEST_F(ImageTest_1091, ByteSwap64WithSwap_1091) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x0807060504030201ULL);
}

// ========== isStringType ==========

TEST_F(ImageTest_1091, IsStringTypeForAscii_1091) {
    // TIFF ASCII type is 2
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
}

TEST_F(ImageTest_1091, IsStringTypeForNonString_1091) {
    // TIFF SHORT type is 3 - should not be string
    EXPECT_FALSE(Exiv2::Image::isStringType(3));
}

// ========== isShortType ==========

TEST_F(ImageTest_1091, IsShortTypeForShort_1091) {
    // TIFF SHORT is type 3
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
}

TEST_F(ImageTest_1091, IsShortTypeForNonShort_1091) {
    EXPECT_FALSE(Exiv2::Image::isShortType(2));
}

// ========== isLongType ==========

TEST_F(ImageTest_1091, IsLongTypeForLong_1091) {
    // TIFF LONG is type 4
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
}

TEST_F(ImageTest_1091, IsLongTypeForNonLong_1091) {
    EXPECT_FALSE(Exiv2::Image::isLongType(3));
}

// ========== isRationalType ==========

TEST_F(ImageTest_1091, IsRationalTypeForRational_1091) {
    // TIFF RATIONAL is type 5
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
}

TEST_F(ImageTest_1091, IsRationalTypeForNonRational_1091) {
    EXPECT_FALSE(Exiv2::Image::isRationalType(4));
}

// ========== is2ByteType ==========

TEST_F(ImageTest_1091, Is2ByteTypeForShort_1091) {
    // SHORT (3) is 2 bytes
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
}

TEST_F(ImageTest_1091, Is2ByteTypeForLong_1091) {
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

// ========== is4ByteType ==========

TEST_F(ImageTest_1091, Is4ByteTypeForLong_1091) {
    // LONG (4) is 4 bytes
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
}

TEST_F(ImageTest_1091, Is4ByteTypeForShort_1091) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
}

// ========== is8ByteType ==========

TEST_F(ImageTest_1091, Is8ByteTypeForRational_1091) {
    // RATIONAL (5) is 8 bytes
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
}

TEST_F(ImageTest_1091, Is8ByteTypeForShort_1091) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(3));
}

// ========== byteSwap2 / byteSwap4 / byteSwap8 from DataBuf ==========

TEST_F(ImageTest_1091, ByteSwap2FromBuf_1091) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    EXPECT_EQ(Exiv2::Image::byteSwap2(buf, 0, false), 0x1234u);
    EXPECT_EQ(Exiv2::Image::byteSwap2(buf, 0, true), 0x3412u);
}

TEST_F(ImageTest_1091, ByteSwap4FromBuf_1091) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    buf.data()[2] = 0x56;
    buf.data()[3] = 0x78;
    EXPECT_EQ(Exiv2::Image::byteSwap4(buf, 0, false), 0x12345678u);
    EXPECT_EQ(Exiv2::Image::byteSwap4(buf, 0, true), 0x78563412u);
}

TEST_F(ImageTest_1091, ByteSwap8FromBuf_1091) {
    Exiv2::DataBuf buf(16);
    buf.data()[0] = 0x01;
    buf.data()[1] = 0x02;
    buf.data()[2] = 0x03;
    buf.data()[3] = 0x04;
    buf.data()[4] = 0x05;
    buf.data()[5] = 0x06;
    buf.data()[6] = 0x07;
    buf.data()[7] = 0x08;
    EXPECT_EQ(Exiv2::Image::byteSwap8(buf, 0, false), 0x0102030405060708ULL);
    EXPECT_EQ(Exiv2::Image::byteSwap8(buf, 0, true), 0x0807060504030201ULL);
}

// ========== ByteSwap2 with offset ==========

TEST_F(ImageTest_1091, ByteSwap2WithOffset_1091) {
    Exiv2::DataBuf buf(8);
    buf.data()[2] = 0xAB;
    buf.data()[3] = 0xCD;
    EXPECT_EQ(Exiv2::Image::byteSwap2(buf, 2, false), 0xABCDu);
    EXPECT_EQ(Exiv2::Image::byteSwap2(buf, 2, true), 0xCDABu);
}

// ========== isLongLongType ==========

TEST_F(ImageTest_1091, IsLongLongTypeCheck_1091) {
    // Type 16 is typically LONG8 in BigTIFF
    // We just check that known non-longlong types return false
    EXPECT_FALSE(Exiv2::Image::isLongLongType(3));  // SHORT
    EXPECT_FALSE(Exiv2::Image::isLongLongType(4));  // LONG
}

// ========== setTypeSupported ==========

TEST_F(ImageTest_1091, SetTypeSupportedChangesImageType_1091) {
    img->setTypeSupported(Exiv2::ImageType::jpeg, 0xFFFF);
    EXPECT_EQ(img->imageType(), Exiv2::ImageType::jpeg);
}

// ========== Edge case: multiple set/clear cycles ==========

TEST_F(ImageTest_1091, MultipleClearSetCycles_1091) {
    for (int i = 0; i < 5; ++i) {
        img->setComment("iteration " + std::to_string(i));
        EXPECT_EQ(img->comment(), "iteration " + std::to_string(i));
        img->clearComment();
        EXPECT_TRUE(img->comment().empty());
    }
}

// ========== Set comment with special characters ==========

TEST_F(ImageTest_1091, SetCommentWithSpecialCharacters_1091) {
    std::string specialComment = "Hello\nWorld\t!@#$%^&*()";
    img->setComment(specialComment);
    EXPECT_EQ(img->comment(), specialComment);
}

// ========== Set comment with very long string ==========

TEST_F(ImageTest_1091, SetCommentWithLongString_1091) {
    std::string longComment(10000, 'A');
    img->setComment(longComment);
    EXPECT_EQ(img->comment(), longComment);
}

// ========== ByteSwap roundtrip ==========

TEST_F(ImageTest_1091, ByteSwap16Roundtrip_1091) {
    uint16_t val = 0xABCD;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    uint16_t restored = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(restored, val);
}

TEST_F(ImageTest_1091, ByteSwap32Roundtrip_1091) {
    uint32_t val = 0xDEADBEEF;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    uint32_t restored = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(restored, val);
}

TEST_F(ImageTest_1091, ByteSwap64Roundtrip_1091) {
    uint64_t val = 0xDEADBEEFCAFEBABEULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    uint64_t restored = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(restored, val);
}

// ========== isPrintXMP / isPrintICC ==========

TEST_F(ImageTest_1091, IsPrintXMPWithNonXmpOption_1091) {
    // With kpsNone option, should likely return false
    EXPECT_FALSE(Exiv2::Image::isPrintXMP(2, Exiv2::kpsNone));
}

TEST_F(ImageTest_1091, IsPrintICCWithNonIccOption_1091) {
    EXPECT_FALSE(Exiv2::Image::isPrintICC(2, Exiv2::kpsNone));
}

// ========== setByteOrder and query ==========

TEST_F(ImageTest_1091, SetAndQueryByteOrder_1091) {
    img->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(img->byteOrder(), Exiv2::bigEndian);
    img->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(img->byteOrder(), Exiv2::littleEndian);
    img->setByteOrder(Exiv2::invalidByteOrder);
    EXPECT_EQ(img->byteOrder(), Exiv2::invalidByteOrder);
}
