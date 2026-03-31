#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <memory>

using namespace Exiv2;

// A concrete subclass of Image for testing purposes, since Image has pure virtual methods
class TestImage : public Exiv2::Image {
public:
    TestImage(std::unique_ptr<BasicIo> io)
        : Image(ImageType::none, mdExif | mdIptc | mdXmp | mdComment, std::move(io)) {}

    void readMetadata() override {}
    void writeMetadata() override {}
};

class ImageTest_1089 : public ::testing::Test {
protected:
    void SetUp() override {
        auto io = std::make_unique<MemIo>();
        image_ = std::make_unique<TestImage>(std::move(io));
    }

    std::unique_ptr<TestImage> image_;
};

// Test default byte order
TEST_F(ImageTest_1089, DefaultByteOrder_1089) {
    EXPECT_EQ(image_->byteOrder(), invalidByteOrder);
}

// Test setting byte order to little endian
TEST_F(ImageTest_1089, SetByteOrderLittleEndian_1089) {
    image_->setByteOrder(littleEndian);
    EXPECT_EQ(image_->byteOrder(), littleEndian);
}

// Test setting byte order to big endian
TEST_F(ImageTest_1089, SetByteOrderBigEndian_1089) {
    image_->setByteOrder(bigEndian);
    EXPECT_EQ(image_->byteOrder(), bigEndian);
}

// Test setting byte order back to invalid
TEST_F(ImageTest_1089, SetByteOrderInvalid_1089) {
    image_->setByteOrder(littleEndian);
    image_->setByteOrder(invalidByteOrder);
    EXPECT_EQ(image_->byteOrder(), invalidByteOrder);
}

// Test default pixel dimensions
TEST_F(ImageTest_1089, DefaultPixelWidth_1089) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(ImageTest_1089, DefaultPixelHeight_1089) {
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// Test default comment is empty
TEST_F(ImageTest_1089, DefaultCommentEmpty_1089) {
    EXPECT_TRUE(image_->comment().empty());
}

// Test setComment and comment
TEST_F(ImageTest_1089, SetComment_1089) {
    image_->setComment("Hello World");
    EXPECT_EQ(image_->comment(), "Hello World");
}

// Test clearComment
TEST_F(ImageTest_1089, ClearComment_1089) {
    image_->setComment("Test comment");
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

// Test setComment with empty string
TEST_F(ImageTest_1089, SetCommentEmpty_1089) {
    image_->setComment("");
    EXPECT_TRUE(image_->comment().empty());
}

// Test good() with valid MemIo
TEST_F(ImageTest_1089, GoodReturnsTrue_1089) {
    EXPECT_TRUE(image_->good());
}

// Test io() returns a reference
TEST_F(ImageTest_1089, IoReturnsReference_1089) {
    const BasicIo& io = image_->io();
    // Just ensure we can call it without crashing
    (void)io;
}

// Test exifData access
TEST_F(ImageTest_1089, ExifDataAccess_1089) {
    ExifData& exif = image_->exifData();
    EXPECT_TRUE(exif.empty());
}

// Test setExifData and clearExifData
TEST_F(ImageTest_1089, SetAndClearExifData_1089) {
    ExifData exifData;
    image_->setExifData(exifData);
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

// Test iptcData access
TEST_F(ImageTest_1089, IptcDataAccess_1089) {
    IptcData& iptc = image_->iptcData();
    EXPECT_TRUE(iptc.empty());
}

// Test setIptcData and clearIptcData
TEST_F(ImageTest_1089, SetAndClearIptcData_1089) {
    IptcData iptcData;
    image_->setIptcData(iptcData);
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

// Test xmpData access
TEST_F(ImageTest_1089, XmpDataAccess_1089) {
    XmpData& xmp = image_->xmpData();
    EXPECT_TRUE(xmp.empty());
}

// Test setXmpData and clearXmpData
TEST_F(ImageTest_1089, SetAndClearXmpData_1089) {
    XmpData xmpData;
    image_->setXmpData(xmpData);
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// Test xmpPacket access
TEST_F(ImageTest_1089, XmpPacketAccess_1089) {
    std::string& packet = image_->xmpPacket();
    EXPECT_TRUE(packet.empty());
}

// Test setXmpPacket and clearXmpPacket
TEST_F(ImageTest_1089, SetAndClearXmpPacket_1089) {
    image_->setXmpPacket("<xmp>test</xmp>");
    EXPECT_FALSE(image_->xmpPacket().empty());
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// Test writeXmpFromPacket flag
TEST_F(ImageTest_1089, DefaultWriteXmpFromPacket_1089) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1089, SetWriteXmpFromPacketTrue_1089) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1089, SetWriteXmpFromPacketFalse_1089) {
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// Test nativePreviews
TEST_F(ImageTest_1089, NativePreviewsEmpty_1089) {
    const NativePreviewList& previews = image_->nativePreviews();
    EXPECT_TRUE(previews.empty());
}

// Test clearMetadata clears everything
TEST_F(ImageTest_1089, ClearMetadata_1089) {
    image_->setComment("some comment");
    image_->clearMetadata();
    EXPECT_TRUE(image_->comment().empty());
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->xmpData().empty());
}

// Test imageType
TEST_F(ImageTest_1089, ImageType_1089) {
    EXPECT_EQ(image_->imageType(), ImageType::none);
}

// Test iccProfile initially not defined
TEST_F(ImageTest_1089, IccProfileNotDefined_1089) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

// Test clearIccProfile
TEST_F(ImageTest_1089, ClearIccProfile_1089) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

// Test iccProfile returns empty DataBuf when not set
TEST_F(ImageTest_1089, IccProfileEmptyWhenNotSet_1089) {
    const DataBuf& profile = image_->iccProfile();
    EXPECT_EQ(profile.size(), 0u);
}

// Test static byteSwap for uint16_t with no swap
TEST_F(ImageTest_1089, ByteSwap16NoSwap_1089) {
    uint16_t val = 0x1234;
    uint16_t result = Image::byteSwap(val, false);
    EXPECT_EQ(result, 0x1234);
}

// Test static byteSwap for uint16_t with swap
TEST_F(ImageTest_1089, ByteSwap16WithSwap_1089) {
    uint16_t val = 0x1234;
    uint16_t result = Image::byteSwap(val, true);
    EXPECT_EQ(result, 0x3412);
}

// Test static byteSwap for uint32_t with no swap
TEST_F(ImageTest_1089, ByteSwap32NoSwap_1089) {
    uint32_t val = 0x12345678;
    uint32_t result = Image::byteSwap(val, false);
    EXPECT_EQ(result, 0x12345678u);
}

// Test static byteSwap for uint32_t with swap
TEST_F(ImageTest_1089, ByteSwap32WithSwap_1089) {
    uint32_t val = 0x12345678;
    uint32_t result = Image::byteSwap(val, true);
    EXPECT_EQ(result, 0x78563412u);
}

// Test static byteSwap for uint64_t with no swap
TEST_F(ImageTest_1089, ByteSwap64NoSwap_1089) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t result = Image::byteSwap(val, false);
    EXPECT_EQ(result, 0x0102030405060708ULL);
}

// Test static byteSwap for uint64_t with swap
TEST_F(ImageTest_1089, ByteSwap64WithSwap_1089) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t result = Image::byteSwap(val, true);
    EXPECT_EQ(result, 0x0807060504030201ULL);
}

// Test platform endianness detection (one must be true)
TEST_F(ImageTest_1089, PlatformEndianness_1089) {
    bool big = Image::isBigEndianPlatform();
    bool little = Image::isLittleEndianPlatform();
    // Exactly one should be true
    EXPECT_NE(big, little);
}

// Test isStringType
TEST_F(ImageTest_1089, IsStringType_1089) {
    // ASCII type (2) is a string type in TIFF
    EXPECT_TRUE(Image::isStringType(2));
    // SHORT type (3) is not a string type
    EXPECT_FALSE(Image::isStringType(3));
}

// Test isShortType
TEST_F(ImageTest_1089, IsShortType_1089) {
    // SHORT = 3
    EXPECT_TRUE(Image::isShortType(3));
    // LONG = 4
    EXPECT_FALSE(Image::isShortType(4));
}

// Test isLongType
TEST_F(ImageTest_1089, IsLongType_1089) {
    // LONG = 4
    EXPECT_TRUE(Image::isLongType(4));
    // SHORT = 3
    EXPECT_FALSE(Image::isLongType(3));
}

// Test isRationalType
TEST_F(ImageTest_1089, IsRationalType_1089) {
    // RATIONAL = 5
    EXPECT_TRUE(Image::isRationalType(5));
    // LONG = 4
    EXPECT_FALSE(Image::isRationalType(4));
}

// Test is2ByteType
TEST_F(ImageTest_1089, Is2ByteType_1089) {
    // SHORT (3) is 2 bytes
    EXPECT_TRUE(Image::is2ByteType(3));
    // LONG (4) is not 2 bytes
    EXPECT_FALSE(Image::is2ByteType(4));
}

// Test is4ByteType
TEST_F(ImageTest_1089, Is4ByteType_1089) {
    // LONG (4) is 4 bytes
    EXPECT_TRUE(Image::is4ByteType(4));
    // SHORT (3) is not 4 bytes
    EXPECT_FALSE(Image::is4ByteType(3));
}

// Test is8ByteType
TEST_F(ImageTest_1089, Is8ByteType_1089) {
    // RATIONAL (5) is 8 bytes
    EXPECT_TRUE(Image::is8ByteType(5));
    // LONG (4) is not 8 bytes
    EXPECT_FALSE(Image::is8ByteType(4));
}

// Test byteSwap2 with DataBuf
TEST_F(ImageTest_1089, ByteSwap2_1089) {
    uint8_t data[] = {0x12, 0x34};
    DataBuf buf(data, sizeof(data));
    uint16_t result_no_swap = Image::byteSwap2(buf, 0, false);
    uint16_t result_swap = Image::byteSwap2(buf, 0, true);
    // One should be the byte-swapped version of the other
    EXPECT_EQ(result_no_swap, Image::byteSwap(result_swap, true));
}

// Test byteSwap4 with DataBuf
TEST_F(ImageTest_1089, ByteSwap4_1089) {
    uint8_t data[] = {0x12, 0x34, 0x56, 0x78};
    DataBuf buf(data, sizeof(data));
    uint32_t result_no_swap = Image::byteSwap4(buf, 0, false);
    uint32_t result_swap = Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(result_no_swap, Image::byteSwap(result_swap, true));
}

// Test byteSwap8 with DataBuf
TEST_F(ImageTest_1089, ByteSwap8_1089) {
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    DataBuf buf(data, sizeof(data));
    uint64_t result_no_swap = Image::byteSwap8(buf, 0, false);
    uint64_t result_swap = Image::byteSwap8(buf, 0, true);
    EXPECT_EQ(result_no_swap, Image::byteSwap(result_swap, true));
}

// Test setMetadata copies metadata from another image
TEST_F(ImageTest_1089, SetMetadataFromAnotherImage_1089) {
    auto io2 = std::make_unique<MemIo>();
    TestImage other(std::move(io2));
    other.setComment("copied comment");

    image_->setMetadata(other);
    EXPECT_EQ(image_->comment(), "copied comment");
}

// Test byteSwap boundary: zero values
TEST_F(ImageTest_1089, ByteSwapZero16_1089) {
    EXPECT_EQ(Image::byteSwap(static_cast<uint16_t>(0), true), 0u);
    EXPECT_EQ(Image::byteSwap(static_cast<uint16_t>(0), false), 0u);
}

TEST_F(ImageTest_1089, ByteSwapZero32_1089) {
    EXPECT_EQ(Image::byteSwap(static_cast<uint32_t>(0), true), 0u);
    EXPECT_EQ(Image::byteSwap(static_cast<uint32_t>(0), false), 0u);
}

TEST_F(ImageTest_1089, ByteSwapZero64_1089) {
    EXPECT_EQ(Image::byteSwap(static_cast<uint64_t>(0), true), 0u);
    EXPECT_EQ(Image::byteSwap(static_cast<uint64_t>(0), false), 0u);
}

// Test byteSwap max values
TEST_F(ImageTest_1089, ByteSwapMax16_1089) {
    uint16_t max16 = 0xFFFF;
    EXPECT_EQ(Image::byteSwap(max16, true), 0xFFFF);
    EXPECT_EQ(Image::byteSwap(max16, false), 0xFFFF);
}

TEST_F(ImageTest_1089, ByteSwapMax32_1089) {
    uint32_t max32 = 0xFFFFFFFF;
    EXPECT_EQ(Image::byteSwap(max32, true), 0xFFFFFFFFu);
    EXPECT_EQ(Image::byteSwap(max32, false), 0xFFFFFFFFu);
}

TEST_F(ImageTest_1089, ByteSwapMax64_1089) {
    uint64_t max64 = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_EQ(Image::byteSwap(max64, true), 0xFFFFFFFFFFFFFFFFULL);
    EXPECT_EQ(Image::byteSwap(max64, false), 0xFFFFFFFFFFFFFFFFULL);
}

// Test double swap returns original value
TEST_F(ImageTest_1089, DoubleSwapReturnsOriginal16_1089) {
    uint16_t val = 0xABCD;
    EXPECT_EQ(Image::byteSwap(Image::byteSwap(val, true), true), val);
}

TEST_F(ImageTest_1089, DoubleSwapReturnsOriginal32_1089) {
    uint32_t val = 0xDEADBEEF;
    EXPECT_EQ(Image::byteSwap(Image::byteSwap(val, true), true), val);
}

TEST_F(ImageTest_1089, DoubleSwapReturnsOriginal64_1089) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Image::byteSwap(Image::byteSwap(val, true), true), val);
}

// Test mimeType returns something
TEST_F(ImageTest_1089, MimeType_1089) {
    std::string mime = image_->mimeType();
    // Default implementation should return some string
    (void)mime;
}

// Test supportsMetadata
TEST_F(ImageTest_1089, SupportsMetadata_1089) {
    // Image was created with mdExif | mdIptc | mdXmp | mdComment
    EXPECT_TRUE(image_->supportsMetadata(mdExif));
    EXPECT_TRUE(image_->supportsMetadata(mdIptc));
    EXPECT_TRUE(image_->supportsMetadata(mdXmp));
    EXPECT_TRUE(image_->supportsMetadata(mdComment));
}

// Test setComment with special characters
TEST_F(ImageTest_1089, SetCommentSpecialChars_1089) {
    std::string special = "Test \n\t\r comment with special chars!@#$%^&*()";
    image_->setComment(special);
    EXPECT_EQ(image_->comment(), special);
}

// Test setComment with very long string
TEST_F(ImageTest_1089, SetCommentLongString_1089) {
    std::string longStr(10000, 'A');
    image_->setComment(longStr);
    EXPECT_EQ(image_->comment(), longStr);
}

// Test isLongLongType
TEST_F(ImageTest_1089, IsLongLongType_1089) {
    // Type 0 should not be long long
    EXPECT_FALSE(Image::isLongLongType(0));
}

// Test isPrintXMP and isPrintICC with various options
TEST_F(ImageTest_1089, IsPrintXMP_1089) {
    // These static methods should return consistent results
    bool resultNone = Image::isPrintXMP(2, kpsNone);
    bool resultXMP = Image::isPrintXMP(2, kpsXMP);
    // At least isPrintXMP with kpsXMP and string type should potentially differ
    (void)resultNone;
    (void)resultXMP;
}

TEST_F(ImageTest_1089, IsPrintICC_1089) {
    bool resultNone = Image::isPrintICC(2, kpsNone);
    bool resultICC = Image::isPrintICC(2, kpsIccProfile);
    (void)resultNone;
    (void)resultICC;
}

// Test multiple byte order changes
TEST_F(ImageTest_1089, MultipleByteOrderChanges_1089) {
    image_->setByteOrder(littleEndian);
    EXPECT_EQ(image_->byteOrder(), littleEndian);
    image_->setByteOrder(bigEndian);
    EXPECT_EQ(image_->byteOrder(), bigEndian);
    image_->setByteOrder(littleEndian);
    EXPECT_EQ(image_->byteOrder(), littleEndian);
}

// Test setTypeSupported
TEST_F(ImageTest_1089, SetTypeSupported_1089) {
    image_->setTypeSupported(ImageType::none, mdExif);
    EXPECT_TRUE(image_->supportsMetadata(mdExif));
}

// Test printStructure doesn't crash
TEST_F(ImageTest_1089, PrintStructureNoCrash_1089) {
    std::ostringstream oss;
    EXPECT_NO_THROW(image_->printStructure(oss, kpsNone, 0));
}
