#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <memory>

// Since Image is abstract (readMetadata/writeMetadata are pure virtual in practice),
// we need a concrete subclass for testing. We'll use a minimal test image class.
// However, looking at the interface, we can use ImageFactory or create a MemIo-based approach.

// Concrete test image that allows us to instantiate Image for testing
class TestImage : public Exiv2::Image {
public:
    TestImage(std::unique_ptr<Exiv2::BasicIo> io)
        : Exiv2::Image(Exiv2::ImageType::none, 0xFFFF, std::move(io)) {}

    void readMetadata() override {}
    void writeMetadata() override {}
    std::string mimeType() const override { return "application/octet-stream"; }
};

class ImageTest_1090 : public ::testing::Test {
protected:
    void SetUp() override {
        auto io = std::make_unique<Exiv2::MemIo>();
        image_ = std::make_unique<TestImage>(std::move(io));
    }

    std::unique_ptr<TestImage> image_;
};

// ==================== pixelWidth / pixelHeight ====================

TEST_F(ImageTest_1090, PixelWidthDefaultIsZero_1090) {
    EXPECT_EQ(0u, image_->pixelWidth());
}

TEST_F(ImageTest_1090, PixelHeightDefaultIsZero_1090) {
    EXPECT_EQ(0u, image_->pixelHeight());
}

// ==================== comment ====================

TEST_F(ImageTest_1090, CommentDefaultIsEmpty_1090) {
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1090, SetAndGetComment_1090) {
    image_->setComment("Test comment");
    EXPECT_EQ("Test comment", image_->comment());
}

TEST_F(ImageTest_1090, ClearComment_1090) {
    image_->setComment("Test comment");
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1090, SetEmptyComment_1090) {
    image_->setComment("");
    EXPECT_TRUE(image_->comment().empty());
}

// ==================== byteOrder ====================

TEST_F(ImageTest_1090, ByteOrderDefaultIsInvalid_1090) {
    EXPECT_EQ(Exiv2::invalidByteOrder, image_->byteOrder());
}

TEST_F(ImageTest_1090, SetByteOrderBigEndian_1090) {
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(Exiv2::bigEndian, image_->byteOrder());
}

TEST_F(ImageTest_1090, SetByteOrderLittleEndian_1090) {
    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(Exiv2::littleEndian, image_->byteOrder());
}

// ==================== writeXmpFromPacket ====================

TEST_F(ImageTest_1090, WriteXmpFromPacketDefaultIsFalse_1090) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1090, SetWriteXmpFromPacketTrue_1090) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1090, SetWriteXmpFromPacketFalse_1090) {
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// ==================== good ====================

TEST_F(ImageTest_1090, GoodReturnsTrueForValidIo_1090) {
    // MemIo with no data should still be "good" in some sense
    // This tests the observable behavior
    EXPECT_TRUE(image_->good());
}

// ==================== io ====================

TEST_F(ImageTest_1090, IoReturnsReference_1090) {
    const Exiv2::BasicIo& io = image_->io();
    // Just verify we can access the io reference without crashing
    EXPECT_NO_THROW((void)io.size());
}

// ==================== ExifData ====================

TEST_F(ImageTest_1090, ExifDataDefaultIsEmpty_1090) {
    EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(ImageTest_1090, SetAndClearExifData_1090) {
    Exiv2::ExifData exifData;
    image_->setExifData(exifData);
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

// ==================== IptcData ====================

TEST_F(ImageTest_1090, IptcDataDefaultIsEmpty_1090) {
    EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageTest_1090, SetAndClearIptcData_1090) {
    Exiv2::IptcData iptcData;
    image_->setIptcData(iptcData);
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

// ==================== XmpData ====================

TEST_F(ImageTest_1090, XmpDataDefaultIsEmpty_1090) {
    EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageTest_1090, SetAndClearXmpData_1090) {
    Exiv2::XmpData xmpData;
    image_->setXmpData(xmpData);
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// ==================== XmpPacket ====================

TEST_F(ImageTest_1090, XmpPacketDefaultIsEmpty_1090) {
    EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageTest_1090, SetAndClearXmpPacket_1090) {
    image_->setXmpPacket("<xmp>test</xmp>");
    EXPECT_EQ("<xmp>test</xmp>", image_->xmpPacket());
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// ==================== ICC Profile ====================

TEST_F(ImageTest_1090, IccProfileDefaultNotDefined_1090) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1090, ClearIccProfile_1090) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

// ==================== clearMetadata ====================

TEST_F(ImageTest_1090, ClearMetadataClearsAll_1090) {
    image_->setComment("test");
    image_->clearMetadata();
    EXPECT_TRUE(image_->comment().empty());
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_TRUE(image_->xmpPacket().empty());
    EXPECT_FALSE(image_->iccProfileDefined());
}

// ==================== setMetadata ====================

TEST_F(ImageTest_1090, SetMetadataFromAnotherImage_1090) {
    auto io2 = std::make_unique<Exiv2::MemIo>();
    TestImage other(std::move(io2));
    other.setComment("other comment");

    image_->setMetadata(other);
    EXPECT_EQ("other comment", image_->comment());
}

// ==================== nativePreviews ====================

TEST_F(ImageTest_1090, NativePreviewsDefaultIsEmpty_1090) {
    EXPECT_TRUE(image_->nativePreviews().empty());
}

// ==================== imageType ====================

TEST_F(ImageTest_1090, ImageTypeReturnsCorrectType_1090) {
    EXPECT_EQ(Exiv2::ImageType::none, image_->imageType());
}

// ==================== Static methods: byteSwap ====================

TEST_F(ImageTest_1090, ByteSwap16NoSwap_1090) {
    uint16_t val = 0x1234;
    EXPECT_EQ(0x1234u, Exiv2::Image::byteSwap(val, false));
}

TEST_F(ImageTest_1090, ByteSwap16WithSwap_1090) {
    uint16_t val = 0x1234;
    EXPECT_EQ(0x3412u, Exiv2::Image::byteSwap(val, true));
}

TEST_F(ImageTest_1090, ByteSwap32NoSwap_1090) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(0x12345678u, Exiv2::Image::byteSwap(val, false));
}

TEST_F(ImageTest_1090, ByteSwap32WithSwap_1090) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(0x78563412u, Exiv2::Image::byteSwap(val, true));
}

TEST_F(ImageTest_1090, ByteSwap64NoSwap_1090) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(0x0102030405060708ULL, Exiv2::Image::byteSwap(val, false));
}

TEST_F(ImageTest_1090, ByteSwap64WithSwap_1090) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(0x0807060504030201ULL, Exiv2::Image::byteSwap(val, true));
}

// ==================== Static methods: byteSwap with DataBuf ====================

TEST_F(ImageTest_1090, ByteSwap2NoSwap_1090) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    EXPECT_EQ(0x1234u, Exiv2::Image::byteSwap2(buf, 0, false));
}

TEST_F(ImageTest_1090, ByteSwap2WithSwap_1090) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    EXPECT_EQ(0x3412u, Exiv2::Image::byteSwap2(buf, 0, true));
}

TEST_F(ImageTest_1090, ByteSwap4NoSwap_1090) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    buf.data()[2] = 0x56;
    buf.data()[3] = 0x78;
    EXPECT_EQ(0x12345678u, Exiv2::Image::byteSwap4(buf, 0, false));
}

TEST_F(ImageTest_1090, ByteSwap4WithSwap_1090) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    buf.data()[2] = 0x56;
    buf.data()[3] = 0x78;
    EXPECT_EQ(0x78563412u, Exiv2::Image::byteSwap4(buf, 0, true));
}

TEST_F(ImageTest_1090, ByteSwap8NoSwap_1090) {
    Exiv2::DataBuf buf(16);
    buf.data()[0] = 0x01;
    buf.data()[1] = 0x02;
    buf.data()[2] = 0x03;
    buf.data()[3] = 0x04;
    buf.data()[4] = 0x05;
    buf.data()[5] = 0x06;
    buf.data()[6] = 0x07;
    buf.data()[7] = 0x08;
    EXPECT_EQ(0x0102030405060708ULL, Exiv2::Image::byteSwap8(buf, 0, false));
}

TEST_F(ImageTest_1090, ByteSwap8WithSwap_1090) {
    Exiv2::DataBuf buf(16);
    buf.data()[0] = 0x01;
    buf.data()[1] = 0x02;
    buf.data()[2] = 0x03;
    buf.data()[3] = 0x04;
    buf.data()[4] = 0x05;
    buf.data()[5] = 0x06;
    buf.data()[6] = 0x07;
    buf.data()[7] = 0x08;
    EXPECT_EQ(0x0807060504030201ULL, Exiv2::Image::byteSwap8(buf, 0, true));
}

// ==================== Static methods: platform endianness ====================

TEST_F(ImageTest_1090, PlatformEndianConsistency_1090) {
    // Exactly one of these should be true
    bool isBig = Exiv2::Image::isBigEndianPlatform();
    bool isLittle = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_NE(isBig, isLittle);
}

// ==================== Static type checking methods ====================

TEST_F(ImageTest_1090, IsStringType_1090) {
    // ASCII type = 2 in TIFF
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
    EXPECT_FALSE(Exiv2::Image::isStringType(3)); // SHORT
}

TEST_F(ImageTest_1090, IsShortType_1090) {
    // SHORT = 3, SSHORT = 8
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
    EXPECT_TRUE(Exiv2::Image::isShortType(8));
    EXPECT_FALSE(Exiv2::Image::isShortType(2));
}

TEST_F(ImageTest_1090, IsLongType_1090) {
    // LONG = 4, SLONG = 9
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
    EXPECT_TRUE(Exiv2::Image::isLongType(9));
    EXPECT_FALSE(Exiv2::Image::isLongType(3));
}

TEST_F(ImageTest_1090, IsRationalType_1090) {
    // RATIONAL = 5, SRATIONAL = 10
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
    EXPECT_TRUE(Exiv2::Image::isRationalType(10));
    EXPECT_FALSE(Exiv2::Image::isRationalType(4));
}

TEST_F(ImageTest_1090, Is2ByteType_1090) {
    // SHORT = 3, SSHORT = 8
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
    EXPECT_TRUE(Exiv2::Image::is2ByteType(8));
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

TEST_F(ImageTest_1090, Is4ByteType_1090) {
    // LONG = 4, SLONG = 9
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
    EXPECT_TRUE(Exiv2::Image::is4ByteType(9));
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
}

TEST_F(ImageTest_1090, Is8ByteType_1090) {
    // RATIONAL = 5, SRATIONAL = 10
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
    EXPECT_TRUE(Exiv2::Image::is8ByteType(10));
    EXPECT_FALSE(Exiv2::Image::is8ByteType(4));
}

// ==================== Boundary: byteSwap with zero values ====================

TEST_F(ImageTest_1090, ByteSwap16ZeroValue_1090) {
    uint16_t val = 0x0000;
    EXPECT_EQ(0x0000u, Exiv2::Image::byteSwap(val, true));
    EXPECT_EQ(0x0000u, Exiv2::Image::byteSwap(val, false));
}

TEST_F(ImageTest_1090, ByteSwap32ZeroValue_1090) {
    uint32_t val = 0x00000000;
    EXPECT_EQ(0x00000000u, Exiv2::Image::byteSwap(val, true));
    EXPECT_EQ(0x00000000u, Exiv2::Image::byteSwap(val, false));
}

TEST_F(ImageTest_1090, ByteSwap64ZeroValue_1090) {
    uint64_t val = 0x0000000000000000ULL;
    EXPECT_EQ(0x0000000000000000ULL, Exiv2::Image::byteSwap(val, true));
    EXPECT_EQ(0x0000000000000000ULL, Exiv2::Image::byteSwap(val, false));
}

// ==================== Boundary: byteSwap max values ====================

TEST_F(ImageTest_1090, ByteSwap16MaxValue_1090) {
    uint16_t val = 0xFFFF;
    EXPECT_EQ(0xFFFFu, Exiv2::Image::byteSwap(val, true));
}

TEST_F(ImageTest_1090, ByteSwap32MaxValue_1090) {
    uint32_t val = 0xFFFFFFFF;
    EXPECT_EQ(0xFFFFFFFFu, Exiv2::Image::byteSwap(val, true));
}

TEST_F(ImageTest_1090, ByteSwap64MaxValue_1090) {
    uint64_t val = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_EQ(0xFFFFFFFFFFFFFFFFULL, Exiv2::Image::byteSwap(val, true));
}

// ==================== ByteSwap with offset ====================

TEST_F(ImageTest_1090, ByteSwap2WithOffset_1090) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x00;
    buf.data()[1] = 0x00;
    buf.data()[2] = 0xAB;
    buf.data()[3] = 0xCD;
    EXPECT_EQ(0xABCDu, Exiv2::Image::byteSwap2(buf, 2, false));
    EXPECT_EQ(0xCDABu, Exiv2::Image::byteSwap2(buf, 2, true));
}

TEST_F(ImageTest_1090, ByteSwap4WithOffset_1090) {
    Exiv2::DataBuf buf(8);
    buf.data()[2] = 0xAB;
    buf.data()[3] = 0xCD;
    buf.data()[4] = 0xEF;
    buf.data()[5] = 0x01;
    EXPECT_EQ(0xABCDEF01u, Exiv2::Image::byteSwap4(buf, 2, false));
    EXPECT_EQ(0x01EFCDABu, Exiv2::Image::byteSwap4(buf, 2, true));
}

// ==================== mimeType ====================

TEST_F(ImageTest_1090, MimeType_1090) {
    EXPECT_EQ("application/octet-stream", image_->mimeType());
}

// ==================== Double swap returns original ====================

TEST_F(ImageTest_1090, DoubleSwap16ReturnsOriginal_1090) {
    uint16_t val = 0x1234;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    uint16_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(val, doubleSwapped);
}

TEST_F(ImageTest_1090, DoubleSwap32ReturnsOriginal_1090) {
    uint32_t val = 0x12345678;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    uint32_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(val, doubleSwapped);
}

TEST_F(ImageTest_1090, DoubleSwap64ReturnsOriginal_1090) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    uint64_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(val, doubleSwapped);
}

// ==================== printStructure (basic smoke test) ====================

TEST_F(ImageTest_1090, PrintStructureDoesNotCrash_1090) {
    std::ostringstream oss;
    EXPECT_NO_THROW(image_->printStructure(oss, Exiv2::kpsNone, 0));
}

// ==================== IsLongLongType ====================

TEST_F(ImageTest_1090, IsLongLongType_1090) {
    // TIFF LONG8 types are typically higher type numbers
    EXPECT_FALSE(Exiv2::Image::isLongLongType(4)); // LONG is not LONGLONG
    EXPECT_FALSE(Exiv2::Image::isLongLongType(3)); // SHORT is not LONGLONG
}

// ==================== setTypeSupported ====================

TEST_F(ImageTest_1090, SetTypeSupported_1090) {
    image_->setTypeSupported(Exiv2::ImageType::none, 0x0000);
    // After setting supported metadata to 0, check modes
    EXPECT_EQ(Exiv2::ImageType::none, image_->imageType());
}
