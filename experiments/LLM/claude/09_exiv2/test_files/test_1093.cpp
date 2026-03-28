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
#include <cstring>

// We need a concrete subclass of Image since Image is abstract (has pure virtual methods)
// We'll use a minimal concrete implementation for testing purposes.
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

class ImageTest_1093 : public ::testing::Test {
protected:
    void SetUp() override {
        image_ = createTestImage();
    }

    std::unique_ptr<TestImage> image_;
};

// ===================== io() tests =====================

TEST_F(ImageTest_1093, IoReturnsValidReference_1093) {
    Exiv2::BasicIo& io = image_->io();
    // The io object should be valid - we can check it's accessible
    (void)io;
    SUCCEED();
}

// ===================== good() tests =====================

TEST_F(ImageTest_1093, GoodReturnsTrueForValidMemIo_1093) {
    // A freshly created MemIo-based image should report good
    EXPECT_TRUE(image_->good());
}

// ===================== byteOrder / setByteOrder tests =====================

TEST_F(ImageTest_1093, DefaultByteOrderIsInvalid_1093) {
    EXPECT_EQ(image_->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageTest_1093, SetByteOrderLittleEndian_1093) {
    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::littleEndian);
}

TEST_F(ImageTest_1093, SetByteOrderBigEndian_1093) {
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);
}

// ===================== pixelWidth / pixelHeight tests =====================

TEST_F(ImageTest_1093, DefaultPixelWidthIsZero_1093) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(ImageTest_1093, DefaultPixelHeightIsZero_1093) {
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// ===================== comment tests =====================

TEST_F(ImageTest_1093, DefaultCommentIsEmpty_1093) {
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1093, SetCommentStoresComment_1093) {
    image_->setComment("Hello World");
    EXPECT_EQ(image_->comment(), "Hello World");
}

TEST_F(ImageTest_1093, ClearCommentRemovesComment_1093) {
    image_->setComment("test comment");
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1093, SetEmptyComment_1093) {
    image_->setComment("");
    EXPECT_TRUE(image_->comment().empty());
}

// ===================== ExifData tests =====================

TEST_F(ImageTest_1093, DefaultExifDataIsEmpty_1093) {
    EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(ImageTest_1093, SetExifDataStoresData_1093) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    EXPECT_FALSE(image_->exifData().empty());
}

TEST_F(ImageTest_1093, ClearExifDataRemovesData_1093) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

// ===================== IptcData tests =====================

TEST_F(ImageTest_1093, DefaultIptcDataIsEmpty_1093) {
    EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageTest_1093, SetIptcDataStoresData_1093) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test Caption";
    image_->setIptcData(iptcData);
    EXPECT_FALSE(image_->iptcData().empty());
}

TEST_F(ImageTest_1093, ClearIptcDataRemovesData_1093) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test Caption";
    image_->setIptcData(iptcData);
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

// ===================== XmpData tests =====================

TEST_F(ImageTest_1093, DefaultXmpDataIsEmpty_1093) {
    EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageTest_1093, ClearXmpDataRemovesData_1093) {
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// ===================== XmpPacket tests =====================

TEST_F(ImageTest_1093, DefaultXmpPacketIsEmpty_1093) {
    EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageTest_1093, SetXmpPacketStoresData_1093) {
    std::string xmpPacket = "<x:xmpmeta></x:xmpmeta>";
    image_->setXmpPacket(xmpPacket);
    EXPECT_EQ(image_->xmpPacket(), xmpPacket);
}

TEST_F(ImageTest_1093, ClearXmpPacketRemovesData_1093) {
    image_->setXmpPacket("<x:xmpmeta></x:xmpmeta>");
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// ===================== writeXmpFromPacket tests =====================

TEST_F(ImageTest_1093, DefaultWriteXmpFromPacketIsFalse_1093) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1093, SetWriteXmpFromPacketTrue_1093) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1093, SetWriteXmpFromPacketFalse_1093) {
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// ===================== ICC Profile tests =====================

TEST_F(ImageTest_1093, DefaultIccProfileNotDefined_1093) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1093, ClearIccProfile_1093) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

// ===================== clearMetadata tests =====================

TEST_F(ImageTest_1093, ClearMetadataClearsAll_1093) {
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

// ===================== setMetadata tests =====================

TEST_F(ImageTest_1093, SetMetadataCopiesFromOther_1093) {
    auto otherImage = createTestImage();
    otherImage->setComment("copied comment");
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "CopiedMake";
    otherImage->setExifData(exifData);
    
    image_->setMetadata(*otherImage);
    
    EXPECT_EQ(image_->comment(), "copied comment");
    EXPECT_FALSE(image_->exifData().empty());
}

// ===================== nativePreviews tests =====================

TEST_F(ImageTest_1093, DefaultNativePreviewsIsEmpty_1093) {
    EXPECT_TRUE(image_->nativePreviews().empty());
}

// ===================== imageType tests =====================

TEST_F(ImageTest_1093, ImageTypeReturnsCorrectType_1093) {
    EXPECT_EQ(image_->imageType(), Exiv2::ImageType::none);
}

// ===================== Static method tests =====================

TEST_F(ImageTest_1093, IsBigEndianOrLittleEndianPlatform_1093) {
    // Platform must be either big or little endian
    bool isBig = Exiv2::Image::isBigEndianPlatform();
    bool isLittle = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_NE(isBig, isLittle);
}

TEST_F(ImageTest_1093, IsStringTypeForAscii_1093) {
    // TIFF ASCII type is 2
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
}

TEST_F(ImageTest_1093, IsStringTypeForNonString_1093) {
    // TIFF SHORT type is 3
    EXPECT_FALSE(Exiv2::Image::isStringType(3));
}

TEST_F(ImageTest_1093, IsShortTypeForShort_1093) {
    // TIFF SHORT is 3
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
}

TEST_F(ImageTest_1093, IsShortTypeForNonShort_1093) {
    EXPECT_FALSE(Exiv2::Image::isShortType(2));
}

TEST_F(ImageTest_1093, IsLongTypeForLong_1093) {
    // TIFF LONG is 4
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
}

TEST_F(ImageTest_1093, IsLongTypeForNonLong_1093) {
    EXPECT_FALSE(Exiv2::Image::isLongType(2));
}

TEST_F(ImageTest_1093, IsRationalTypeForRational_1093) {
    // TIFF RATIONAL is 5
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
}

TEST_F(ImageTest_1093, IsRationalTypeForNonRational_1093) {
    EXPECT_FALSE(Exiv2::Image::isRationalType(2));
}

TEST_F(ImageTest_1093, Is2ByteTypeForShort_1093) {
    // SHORT (3) is 2-byte type
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
}

TEST_F(ImageTest_1093, Is2ByteTypeForNon2Byte_1093) {
    // LONG (4) is not a 2-byte type
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

TEST_F(ImageTest_1093, Is4ByteTypeForLong_1093) {
    // LONG (4) is 4-byte type
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
}

TEST_F(ImageTest_1093, Is4ByteTypeForNon4Byte_1093) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
}

TEST_F(ImageTest_1093, Is8ByteTypeForRational_1093) {
    // RATIONAL (5) is 8-byte type
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
}

TEST_F(ImageTest_1093, Is8ByteTypeForNon8Byte_1093) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(3));
}

// ===================== byteSwap tests =====================

TEST_F(ImageTest_1093, ByteSwap16NoSwap_1093) {
    uint16_t value = 0x0102;
    uint16_t result = Exiv2::Image::byteSwap(value, false);
    EXPECT_EQ(result, 0x0102);
}

TEST_F(ImageTest_1093, ByteSwap16WithSwap_1093) {
    uint16_t value = 0x0102;
    uint16_t result = Exiv2::Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x0201);
}

TEST_F(ImageTest_1093, ByteSwap32NoSwap_1093) {
    uint32_t value = 0x01020304;
    uint32_t result = Exiv2::Image::byteSwap(value, false);
    EXPECT_EQ(result, 0x01020304u);
}

TEST_F(ImageTest_1093, ByteSwap32WithSwap_1093) {
    uint32_t value = 0x01020304;
    uint32_t result = Exiv2::Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x04030201u);
}

TEST_F(ImageTest_1093, ByteSwap64NoSwap_1093) {
    uint64_t value = 0x0102030405060708ULL;
    uint64_t result = Exiv2::Image::byteSwap(value, false);
    EXPECT_EQ(result, 0x0102030405060708ULL);
}

TEST_F(ImageTest_1093, ByteSwap64WithSwap_1093) {
    uint64_t value = 0x0102030405060708ULL;
    uint64_t result = Exiv2::Image::byteSwap(value, true);
    EXPECT_EQ(result, 0x0807060504030201ULL);
}

// ===================== byteSwap2/4/8 from DataBuf tests =====================

TEST_F(ImageTest_1093, ByteSwap2FromDataBufNoSwap_1093) {
    Exiv2::DataBuf buf(4);
    buf.write_uint8(0, 0x01);
    buf.write_uint8(1, 0x02);
    uint16_t result = Exiv2::Image::byteSwap2(buf, 0, false);
    // Should read the bytes as-is (platform dependent, but no swap)
    uint16_t expected;
    std::memcpy(&expected, buf.c_data(), 2);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageTest_1093, ByteSwap4FromDataBufNoSwap_1093) {
    Exiv2::DataBuf buf(8);
    buf.write_uint8(0, 0x01);
    buf.write_uint8(1, 0x02);
    buf.write_uint8(2, 0x03);
    buf.write_uint8(3, 0x04);
    uint32_t result = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t expected;
    std::memcpy(&expected, buf.c_data(), 4);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageTest_1093, ByteSwap8FromDataBufNoSwap_1093) {
    Exiv2::DataBuf buf(16);
    for (size_t i = 0; i < 8; ++i) {
        buf.write_uint8(i, static_cast<uint8_t>(i + 1));
    }
    uint64_t result = Exiv2::Image::byteSwap8(buf, 0, false);
    uint64_t expected;
    std::memcpy(&expected, buf.c_data(), 8);
    EXPECT_EQ(result, expected);
}

// ===================== byteSwap boundary: zero values =====================

TEST_F(ImageTest_1093, ByteSwap16ZeroNoSwap_1093) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), false), 0u);
}

TEST_F(ImageTest_1093, ByteSwap16ZeroWithSwap_1093) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), true), 0u);
}

TEST_F(ImageTest_1093, ByteSwap32ZeroWithSwap_1093) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint32_t>(0), true), 0u);
}

TEST_F(ImageTest_1093, ByteSwap64ZeroWithSwap_1093) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint64_t>(0), true), 0u);
}

// ===================== byteSwap boundary: max values =====================

TEST_F(ImageTest_1093, ByteSwap16MaxNoSwap_1093) {
    uint16_t max16 = 0xFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(max16, false), 0xFFFF);
}

TEST_F(ImageTest_1093, ByteSwap16MaxWithSwap_1093) {
    uint16_t max16 = 0xFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(max16, true), 0xFFFF);
}

TEST_F(ImageTest_1093, ByteSwap32MaxWithSwap_1093) {
    uint32_t max32 = 0xFFFFFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(max32, true), 0xFFFFFFFFu);
}

// ===================== Double swap returns original =====================

TEST_F(ImageTest_1093, DoubleByteSwap16ReturnsOriginal_1093) {
    uint16_t original = 0xABCD;
    uint16_t swapped = Exiv2::Image::byteSwap(original, true);
    uint16_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, original);
}

TEST_F(ImageTest_1093, DoubleByteSwap32ReturnsOriginal_1093) {
    uint32_t original = 0xAABBCCDD;
    uint32_t swapped = Exiv2::Image::byteSwap(original, true);
    uint32_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, original);
}

TEST_F(ImageTest_1093, DoubleByteSwap64ReturnsOriginal_1093) {
    uint64_t original = 0x1122334455667788ULL;
    uint64_t swapped = Exiv2::Image::byteSwap(original, true);
    uint64_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, original);
}

// ===================== isLongLongType tests =====================

TEST_F(ImageTest_1093, IsLongLongTypeForNonLongLong_1093) {
    EXPECT_FALSE(Exiv2::Image::isLongLongType(4)); // LONG is not LONG8
}

// ===================== Multiple set/clear cycles =====================

TEST_F(ImageTest_1093, MultipleClearSetCyclesComment_1093) {
    for (int i = 0; i < 5; ++i) {
        std::string comment = "Comment " + std::to_string(i);
        image_->setComment(comment);
        EXPECT_EQ(image_->comment(), comment);
        image_->clearComment();
        EXPECT_TRUE(image_->comment().empty());
    }
}

TEST_F(ImageTest_1093, SetCommentWithSpecialCharacters_1093) {
    std::string special = "Hello\nWorld\t\"Special' chars & <xml> © ™";
    image_->setComment(special);
    EXPECT_EQ(image_->comment(), special);
}

// ===================== mimeType test =====================

TEST_F(ImageTest_1093, MimeTypeReturnsString_1093) {
    std::string mime = image_->mimeType();
    // Should return some string (implementation defined for base class)
    // Just verify it doesn't throw
    SUCCEED();
}

// ===================== setTypeSupported test =====================

TEST_F(ImageTest_1093, SetTypeSupportedChangesType_1093) {
    image_->setTypeSupported(Exiv2::ImageType::jpeg, 0xFFFF);
    EXPECT_EQ(image_->imageType(), Exiv2::ImageType::jpeg);
}
