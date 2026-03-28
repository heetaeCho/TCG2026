#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <sstream>
#include <memory>

// We need a concrete subclass of Image since Image is abstract (has pure virtual methods)
// We'll use a minimal concrete implementation for testing purposes
namespace {

class TestImage : public Exiv2::Image {
public:
    TestImage(std::unique_ptr<Exiv2::BasicIo> io)
        : Exiv2::Image(Exiv2::ImageType::none, static_cast<uint16_t>(0xFFFF), std::move(io)) {}

    TestImage(Exiv2::ImageType type, uint16_t supportedMetadata, std::unique_ptr<Exiv2::BasicIo> io)
        : Exiv2::Image(type, supportedMetadata, std::move(io)) {}

    void readMetadata() override {}
    void writeMetadata() override {}
    std::string mimeType() const override { return "application/octet-stream"; }
};

std::unique_ptr<Exiv2::BasicIo> createMemIo() {
    return std::make_unique<Exiv2::MemIo>();
}

}  // namespace

class ImageTest_1094 : public ::testing::Test {
protected:
    void SetUp() override {
        image_ = std::make_unique<TestImage>(createMemIo());
    }

    std::unique_ptr<TestImage> image_;
};

// ==================== writeXmpFromPacket tests ====================

TEST_F(ImageTest_1094, WriteXmpFromPacketDefaultIsFalse_1094) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1094, WriteXmpFromPacketSetTrue_1094) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1094, WriteXmpFromPacketSetFalse_1094) {
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1094, WriteXmpFromPacketToggleMultipleTimes_1094) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

// ==================== byteOrder tests ====================

TEST_F(ImageTest_1094, ByteOrderDefaultIsInvalid_1094) {
    EXPECT_EQ(image_->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageTest_1094, SetByteOrderBigEndian_1094) {
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);
}

TEST_F(ImageTest_1094, SetByteOrderLittleEndian_1094) {
    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::littleEndian);
}

// ==================== pixelWidth / pixelHeight tests ====================

TEST_F(ImageTest_1094, PixelWidthDefaultIsZero_1094) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(ImageTest_1094, PixelHeightDefaultIsZero_1094) {
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// ==================== comment tests ====================

TEST_F(ImageTest_1094, CommentDefaultIsEmpty_1094) {
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1094, SetComment_1094) {
    image_->setComment("Hello World");
    EXPECT_EQ(image_->comment(), "Hello World");
}

TEST_F(ImageTest_1094, ClearComment_1094) {
    image_->setComment("Some comment");
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1094, SetCommentEmpty_1094) {
    image_->setComment("");
    EXPECT_EQ(image_->comment(), "");
}

TEST_F(ImageTest_1094, SetCommentWithSpecialCharacters_1094) {
    std::string special = "Test\n\t\r Special chars!@#$%^&*()";
    image_->setComment(special);
    EXPECT_EQ(image_->comment(), special);
}

// ==================== exifData tests ====================

TEST_F(ImageTest_1094, ExifDataDefaultIsEmpty_1094) {
    EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(ImageTest_1094, SetExifData_1094) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    EXPECT_FALSE(image_->exifData().empty());
}

TEST_F(ImageTest_1094, ClearExifData_1094) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

// ==================== iptcData tests ====================

TEST_F(ImageTest_1094, IptcDataDefaultIsEmpty_1094) {
    EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageTest_1094, SetIptcData_1094) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test Caption";
    image_->setIptcData(iptcData);
    EXPECT_FALSE(image_->iptcData().empty());
}

TEST_F(ImageTest_1094, ClearIptcData_1094) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test Caption";
    image_->setIptcData(iptcData);
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

// ==================== xmpData tests ====================

TEST_F(ImageTest_1094, XmpDataDefaultIsEmpty_1094) {
    EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageTest_1094, ClearXmpData_1094) {
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// ==================== xmpPacket tests ====================

TEST_F(ImageTest_1094, XmpPacketDefaultIsEmpty_1094) {
    EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageTest_1094, SetXmpPacket_1094) {
    std::string packet = "<xmp>test</xmp>";
    image_->setXmpPacket(packet);
    EXPECT_EQ(image_->xmpPacket(), packet);
}

TEST_F(ImageTest_1094, ClearXmpPacket_1094) {
    image_->setXmpPacket("<xmp>test</xmp>");
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// ==================== clearMetadata tests ====================

TEST_F(ImageTest_1094, ClearMetadataClearsAll_1094) {
    image_->setComment("Test comment");
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

// ==================== setMetadata tests ====================

TEST_F(ImageTest_1094, SetMetadataFromAnotherImage_1094) {
    auto source = std::make_unique<TestImage>(createMemIo());
    source->setComment("Source comment");
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "SourceMake";
    source->setExifData(exifData);

    image_->setMetadata(*source);

    EXPECT_EQ(image_->comment(), "Source comment");
    EXPECT_FALSE(image_->exifData().empty());
}

// ==================== iccProfile tests ====================

TEST_F(ImageTest_1094, IccProfileDefaultNotDefined_1094) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1094, ClearIccProfile_1094) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

// ==================== good tests ====================

TEST_F(ImageTest_1094, GoodWithMemIo_1094) {
    // A MemIo should be in a good state
    EXPECT_TRUE(image_->good());
}

// ==================== io tests ====================

TEST_F(ImageTest_1094, IoReturnsReference_1094) {
    const Exiv2::BasicIo& io = image_->io();
    // Just verify we can access io without crashing
    SUCCEED();
}

// ==================== nativePreviews tests ====================

TEST_F(ImageTest_1094, NativePreviewsDefaultIsEmpty_1094) {
    EXPECT_TRUE(image_->nativePreviews().empty());
}

// ==================== imageType tests ====================

TEST_F(ImageTest_1094, ImageTypeReturnsConstructedType_1094) {
    auto img = std::make_unique<TestImage>(Exiv2::ImageType::none, 0xFFFF, createMemIo());
    EXPECT_EQ(img->imageType(), Exiv2::ImageType::none);
}

// ==================== Static method tests ====================

TEST_F(ImageTest_1094, IsBigOrLittleEndianPlatform_1094) {
    // One of these must be true
    bool isBig = Exiv2::Image::isBigEndianPlatform();
    bool isLittle = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_TRUE(isBig || isLittle);
    EXPECT_NE(isBig, isLittle);
}

TEST_F(ImageTest_1094, IsLittleEndianPlatformConsistent_1094) {
    EXPECT_EQ(Exiv2::Image::isLittleEndianPlatform(), !Exiv2::Image::isBigEndianPlatform());
}

// ==================== byteSwap tests ====================

TEST_F(ImageTest_1094, ByteSwap16NoSwap_1094) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x1234);
}

TEST_F(ImageTest_1094, ByteSwap16Swap_1094) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x3412);
}

TEST_F(ImageTest_1094, ByteSwap32NoSwap_1094) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x12345678u);
}

TEST_F(ImageTest_1094, ByteSwap32Swap_1094) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x78563412u);
}

TEST_F(ImageTest_1094, ByteSwap64NoSwap_1094) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x0102030405060708ULL);
}

TEST_F(ImageTest_1094, ByteSwap64Swap_1094) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x0807060504030201ULL);
}

TEST_F(ImageTest_1094, ByteSwap16Zero_1094) {
    uint16_t val = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0);
}

TEST_F(ImageTest_1094, ByteSwap32Zero_1094) {
    uint32_t val = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0u);
}

TEST_F(ImageTest_1094, ByteSwap64Zero_1094) {
    uint64_t val = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0ULL);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0ULL);
}

TEST_F(ImageTest_1094, ByteSwap16DoubleSwapReturnsOriginal_1094) {
    uint16_t val = 0xABCD;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(Exiv2::Image::byteSwap(swapped, true), val);
}

TEST_F(ImageTest_1094, ByteSwap32DoubleSwapReturnsOriginal_1094) {
    uint32_t val = 0xDEADBEEF;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(Exiv2::Image::byteSwap(swapped, true), val);
}

TEST_F(ImageTest_1094, ByteSwap64DoubleSwapReturnsOriginal_1094) {
    uint64_t val = 0xDEADBEEFCAFEBABEULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(Exiv2::Image::byteSwap(swapped, true), val);
}

// ==================== isStringType tests ====================

TEST_F(ImageTest_1094, IsStringTypeForAscii_1094) {
    // Typically TIFF type 2 is ASCII
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
}

TEST_F(ImageTest_1094, IsStringTypeForNonString_1094) {
    // Type 3 is SHORT, not a string type
    EXPECT_FALSE(Exiv2::Image::isStringType(3));
}

// ==================== isShortType tests ====================

TEST_F(ImageTest_1094, IsShortTypeForShort_1094) {
    // TIFF type 3 is SHORT
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
}

TEST_F(ImageTest_1094, IsShortTypeForNonShort_1094) {
    EXPECT_FALSE(Exiv2::Image::isShortType(2));
}

// ==================== isLongType tests ====================

TEST_F(ImageTest_1094, IsLongTypeForLong_1094) {
    // TIFF type 4 is LONG
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
}

TEST_F(ImageTest_1094, IsLongTypeForNonLong_1094) {
    EXPECT_FALSE(Exiv2::Image::isLongType(3));
}

// ==================== isRationalType tests ====================

TEST_F(ImageTest_1094, IsRationalTypeForRational_1094) {
    // TIFF type 5 is RATIONAL
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
}

TEST_F(ImageTest_1094, IsRationalTypeForNonRational_1094) {
    EXPECT_FALSE(Exiv2::Image::isRationalType(4));
}

// ==================== is2ByteType tests ====================

TEST_F(ImageTest_1094, Is2ByteTypeForShort_1094) {
    // SHORT (3) is 2 bytes
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
}

// ==================== is4ByteType tests ====================

TEST_F(ImageTest_1094, Is4ByteTypeForLong_1094) {
    // LONG (4) is 4 bytes
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
}

// ==================== is8ByteType tests ====================

TEST_F(ImageTest_1094, Is8ByteTypeForRational_1094) {
    // RATIONAL (5) is 8 bytes
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
}

// ==================== byteSwap2/4/8 with DataBuf tests ====================

TEST_F(ImageTest_1094, ByteSwap2NoSwap_1094) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    uint16_t result = Exiv2::Image::byteSwap2(buf, 0, false);
    // Should read as-is from memory
    uint16_t expected;
    std::memcpy(&expected, buf.data(), 2);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageTest_1094, ByteSwap2Swap_1094) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    uint16_t noswap = Exiv2::Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
    EXPECT_EQ(swapped, Exiv2::Image::byteSwap(noswap, true));
}

TEST_F(ImageTest_1094, ByteSwap4NoSwap_1094) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    buf.data()[2] = 0x56;
    buf.data()[3] = 0x78;
    uint32_t result = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t expected;
    std::memcpy(&expected, buf.data(), 4);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageTest_1094, ByteSwap4Swap_1094) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    buf.data()[2] = 0x56;
    buf.data()[3] = 0x78;
    uint32_t noswap = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t swapped = Exiv2::Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(swapped, Exiv2::Image::byteSwap(noswap, true));
}

TEST_F(ImageTest_1094, ByteSwap8NoSwap_1094) {
    Exiv2::DataBuf buf(16);
    for (size_t i = 0; i < 8; ++i) {
        buf.data()[i] = static_cast<uint8_t>(i + 1);
    }
    uint64_t result = Exiv2::Image::byteSwap8(buf, 0, false);
    uint64_t expected;
    std::memcpy(&expected, buf.data(), 8);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageTest_1094, ByteSwap8Swap_1094) {
    Exiv2::DataBuf buf(16);
    for (size_t i = 0; i < 8; ++i) {
        buf.data()[i] = static_cast<uint8_t>(i + 1);
    }
    uint64_t noswap = Exiv2::Image::byteSwap8(buf, 0, false);
    uint64_t swapped = Exiv2::Image::byteSwap8(buf, 0, true);
    EXPECT_EQ(swapped, Exiv2::Image::byteSwap(noswap, true));
}

// ==================== ByteSwap2 with offset tests ====================

TEST_F(ImageTest_1094, ByteSwap2WithOffset_1094) {
    Exiv2::DataBuf buf(8);
    buf.data()[2] = 0xAB;
    buf.data()[3] = 0xCD;
    uint16_t result = Exiv2::Image::byteSwap2(buf, 2, false);
    uint16_t expected;
    std::memcpy(&expected, buf.data() + 2, 2);
    EXPECT_EQ(result, expected);
}

// ==================== mimeType tests ====================

TEST_F(ImageTest_1094, MimeTypeDefault_1094) {
    // Our test image returns "application/octet-stream"
    EXPECT_EQ(image_->mimeType(), "application/octet-stream");
}

// ==================== setTypeSupported tests ====================

TEST_F(ImageTest_1094, SetTypeSupportedChangesType_1094) {
    image_->setTypeSupported(Exiv2::ImageType::jpeg, 0xFFFF);
    EXPECT_EQ(image_->imageType(), Exiv2::ImageType::jpeg);
}

// ==================== Boundary: max uint16 for byteSwap ====================

TEST_F(ImageTest_1094, ByteSwap16Max_1094) {
    uint16_t val = 0xFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFF);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0xFFFF);
}

TEST_F(ImageTest_1094, ByteSwap32Max_1094) {
    uint32_t val = 0xFFFFFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFFFFFu);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0xFFFFFFFFu);
}

TEST_F(ImageTest_1094, ByteSwap64Max_1094) {
    uint64_t val = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFFFFFFFFFFFFFULL);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0xFFFFFFFFFFFFFFFFULL);
}

// ==================== Multiple metadata operations ====================

TEST_F(ImageTest_1094, SetAndClearMultipleMetadata_1094) {
    // Set everything
    image_->setComment("Test");
    Exiv2::ExifData exif;
    exif["Exif.Image.Make"] = "Test";
    image_->setExifData(exif);
    Exiv2::IptcData iptc;
    iptc["Iptc.Application2.Caption"] = "Test";
    image_->setIptcData(iptc);
    image_->setXmpPacket("<xmp>test</xmp>");

    EXPECT_FALSE(image_->comment().empty());
    EXPECT_FALSE(image_->exifData().empty());
    EXPECT_FALSE(image_->iptcData().empty());
    EXPECT_FALSE(image_->xmpPacket().empty());

    // Clear everything
    image_->clearMetadata();

    EXPECT_TRUE(image_->comment().empty());
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// ==================== isLongLongType tests ====================

TEST_F(ImageTest_1094, IsLongLongTypeForNonLongLong_1094) {
    // Type 3 (SHORT) should not be a long long type
    EXPECT_FALSE(Exiv2::Image::isLongLongType(3));
}

// ==================== Endianness consistency ====================

TEST_F(ImageTest_1094, PlatformEndiannessMutuallyExclusive_1094) {
    EXPECT_NE(Exiv2::Image::isBigEndianPlatform(), Exiv2::Image::isLittleEndianPlatform());
}
