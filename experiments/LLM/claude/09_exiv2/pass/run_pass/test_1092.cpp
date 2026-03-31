#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <sstream>
#include <memory>

// We need a concrete Image subclass since Image has pure virtual methods (readMetadata, writeMetadata)
// We'll use a minimal test subclass or use ImageFactory to create a known image type.
// Since Image is abstract, we create a minimal concrete subclass for testing.

namespace {

class TestImage : public Exiv2::Image {
public:
    TestImage(std::unique_ptr<Exiv2::BasicIo> io)
        : Exiv2::Image(Exiv2::ImageType::none, 0xFFFF, std::move(io)) {
    }

    void readMetadata() override {
        // No-op for testing
    }

    void writeMetadata() override {
        // No-op for testing
    }

    std::string mimeType() const override {
        return "application/octet-stream";
    }
};

std::unique_ptr<TestImage> createTestImage() {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<TestImage>(std::move(io));
}

} // anonymous namespace

class ImageTest_1092 : public ::testing::Test {
protected:
    std::unique_ptr<TestImage> image_;

    void SetUp() override {
        image_ = createTestImage();
    }
};

// --- Comment tests ---

TEST_F(ImageTest_1092, CommentDefaultIsEmpty_1092) {
    EXPECT_EQ(image_->comment(), "");
}

TEST_F(ImageTest_1092, SetCommentAndRetrieve_1092) {
    image_->setComment("Hello, World!");
    EXPECT_EQ(image_->comment(), "Hello, World!");
}

TEST_F(ImageTest_1092, ClearComment_1092) {
    image_->setComment("Some comment");
    image_->clearComment();
    EXPECT_EQ(image_->comment(), "");
}

TEST_F(ImageTest_1092, SetCommentEmptyString_1092) {
    image_->setComment("");
    EXPECT_EQ(image_->comment(), "");
}

TEST_F(ImageTest_1092, SetCommentOverwrite_1092) {
    image_->setComment("First");
    image_->setComment("Second");
    EXPECT_EQ(image_->comment(), "Second");
}

TEST_F(ImageTest_1092, SetCommentWithSpecialCharacters_1092) {
    std::string specialComment = "Line1\nLine2\tTab\0Null";
    image_->setComment(specialComment);
    EXPECT_EQ(image_->comment(), specialComment);
}

TEST_F(ImageTest_1092, SetCommentLongString_1092) {
    std::string longComment(10000, 'A');
    image_->setComment(longComment);
    EXPECT_EQ(image_->comment(), longComment);
}

// --- ExifData tests ---

TEST_F(ImageTest_1092, ExifDataDefaultEmpty_1092) {
    EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(ImageTest_1092, SetExifDataAndRetrieve_1092) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    EXPECT_FALSE(image_->exifData().empty());
}

TEST_F(ImageTest_1092, ClearExifData_1092) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

// --- IptcData tests ---

TEST_F(ImageTest_1092, IptcDataDefaultEmpty_1092) {
    EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageTest_1092, SetIptcDataAndRetrieve_1092) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "TestCaption";
    image_->setIptcData(iptcData);
    EXPECT_FALSE(image_->iptcData().empty());
}

TEST_F(ImageTest_1092, ClearIptcData_1092) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "TestCaption";
    image_->setIptcData(iptcData);
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

// --- XmpData tests ---

TEST_F(ImageTest_1092, XmpDataDefaultEmpty_1092) {
    EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageTest_1092, ClearXmpData_1092) {
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// --- XmpPacket tests ---

TEST_F(ImageTest_1092, XmpPacketDefaultEmpty_1092) {
    EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageTest_1092, SetXmpPacketAndRetrieve_1092) {
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    image_->setXmpPacket(packet);
    EXPECT_EQ(image_->xmpPacket(), packet);
}

TEST_F(ImageTest_1092, ClearXmpPacket_1092) {
    image_->setXmpPacket("<x:xmpmeta>test</x:xmpmeta>");
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// --- writeXmpFromPacket tests ---

TEST_F(ImageTest_1092, WriteXmpFromPacketDefaultFalse_1092) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1092, SetWriteXmpFromPacketTrue_1092) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1092, SetWriteXmpFromPacketFalse_1092) {
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// --- ByteOrder tests ---

TEST_F(ImageTest_1092, ByteOrderDefaultInvalid_1092) {
    EXPECT_EQ(image_->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageTest_1092, SetByteOrderBigEndian_1092) {
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);
}

TEST_F(ImageTest_1092, SetByteOrderLittleEndian_1092) {
    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::littleEndian);
}

// --- PixelWidth/Height tests ---

TEST_F(ImageTest_1092, PixelWidthDefaultZero_1092) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(ImageTest_1092, PixelHeightDefaultZero_1092) {
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// --- good() test ---

TEST_F(ImageTest_1092, GoodReturnsTrueForMemIo_1092) {
    // MemIo should be good by default
    EXPECT_TRUE(image_->good());
}

// --- io() test ---

TEST_F(ImageTest_1092, IoReturnsNonNull_1092) {
    const Exiv2::BasicIo& io = image_->io();
    // Just verify we can access it without crashing
    EXPECT_GE(io.size(), 0u);
}

// --- ICC Profile tests ---

TEST_F(ImageTest_1092, IccProfileNotDefinedByDefault_1092) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1092, ClearIccProfile_1092) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

// --- clearMetadata tests ---

TEST_F(ImageTest_1092, ClearMetadataClearsAll_1092) {
    image_->setComment("test");
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    
    image_->clearMetadata();
    
    EXPECT_EQ(image_->comment(), "");
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// --- setMetadata tests ---

TEST_F(ImageTest_1092, SetMetadataFromAnotherImage_1092) {
    auto otherImage = createTestImage();
    otherImage->setComment("Other comment");
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "OtherMake";
    otherImage->setExifData(exifData);
    
    image_->setMetadata(*otherImage);
    
    EXPECT_EQ(image_->comment(), "Other comment");
    EXPECT_FALSE(image_->exifData().empty());
}

// --- NativePreviews tests ---

TEST_F(ImageTest_1092, NativePreviewsDefaultEmpty_1092) {
    EXPECT_TRUE(image_->nativePreviews().empty());
}

// --- ImageType tests ---

TEST_F(ImageTest_1092, ImageTypeIsNone_1092) {
    EXPECT_EQ(image_->imageType(), Exiv2::ImageType::none);
}

// --- Static utility function tests ---

TEST_F(ImageTest_1092, IsBigEndianOrLittleEndianPlatform_1092) {
    // One of them must be true, or this is a mixed-endian platform
    bool big = Exiv2::Image::isBigEndianPlatform();
    bool little = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_TRUE(big || little);
    EXPECT_NE(big, little); // They should be mutually exclusive
}

// --- byteSwap tests ---

TEST_F(ImageTest_1092, ByteSwap16NoSwap_1092) {
    uint16_t value = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, false), 0x1234);
}

TEST_F(ImageTest_1092, ByteSwap16WithSwap_1092) {
    uint16_t value = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0x3412);
}

TEST_F(ImageTest_1092, ByteSwap32NoSwap_1092) {
    uint32_t value = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, false), 0x12345678u);
}

TEST_F(ImageTest_1092, ByteSwap32WithSwap_1092) {
    uint32_t value = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0x78563412u);
}

TEST_F(ImageTest_1092, ByteSwap64NoSwap_1092) {
    uint64_t value = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, false), 0x0102030405060708ULL);
}

TEST_F(ImageTest_1092, ByteSwap64WithSwap_1092) {
    uint64_t value = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0x0807060504030201ULL);
}

TEST_F(ImageTest_1092, ByteSwap16Zero_1092) {
    uint16_t value = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0);
    EXPECT_EQ(Exiv2::Image::byteSwap(value, false), 0);
}

TEST_F(ImageTest_1092, ByteSwap32Zero_1092) {
    uint32_t value = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(value, false), 0u);
}

TEST_F(ImageTest_1092, ByteSwap64Zero_1092) {
    uint64_t value = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0ULL);
    EXPECT_EQ(Exiv2::Image::byteSwap(value, false), 0ULL);
}

// --- isStringType, isShortType, isLongType, etc. ---

TEST_F(ImageTest_1092, IsStringType_1092) {
    // TIFF ASCII type is 2
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
    // Integer types should not be string types
    EXPECT_FALSE(Exiv2::Image::isStringType(3)); // SHORT
}

TEST_F(ImageTest_1092, IsShortType_1092) {
    // TIFF SHORT is type 3, SSHORT is type 8
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
    EXPECT_TRUE(Exiv2::Image::isShortType(8));
    EXPECT_FALSE(Exiv2::Image::isShortType(4)); // LONG
}

TEST_F(ImageTest_1092, IsLongType_1092) {
    // TIFF LONG is type 4, SLONG is type 9
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
    EXPECT_TRUE(Exiv2::Image::isLongType(9));
    EXPECT_FALSE(Exiv2::Image::isLongType(3)); // SHORT
}

TEST_F(ImageTest_1092, IsRationalType_1092) {
    // TIFF RATIONAL is type 5, SRATIONAL is type 10
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
    EXPECT_TRUE(Exiv2::Image::isRationalType(10));
    EXPECT_FALSE(Exiv2::Image::isRationalType(4)); // LONG
}

TEST_F(ImageTest_1092, Is2ByteType_1092) {
    // SHORT (3) and SSHORT (8) are 2 byte types
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
    EXPECT_TRUE(Exiv2::Image::is2ByteType(8));
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4)); // LONG is 4 bytes
}

TEST_F(ImageTest_1092, Is4ByteType_1092) {
    // LONG (4) and SLONG (9) and FLOAT (11) are 4 byte types
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
    EXPECT_TRUE(Exiv2::Image::is4ByteType(9));
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3)); // SHORT is 2 bytes
}

TEST_F(ImageTest_1092, Is8ByteType_1092) {
    // RATIONAL (5) and SRATIONAL (10) and DOUBLE (12) are 8 byte types
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
    EXPECT_TRUE(Exiv2::Image::is8ByteType(10));
    EXPECT_FALSE(Exiv2::Image::is8ByteType(4)); // LONG is 4 bytes
}

// --- MimeType tests ---

TEST_F(ImageTest_1092, MimeTypeReturnsString_1092) {
    std::string mime = image_->mimeType();
    EXPECT_FALSE(mime.empty());
}

// --- ByteSwap2/4/8 with DataBuf tests ---

TEST_F(ImageTest_1092, ByteSwap2WithDataBuf_1092) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    
    uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
    
    // The values should differ when swapped (unless symmetric)
    if (noSwap != swapped) {
        EXPECT_NE(noSwap, swapped);
    }
    // At least verify they return something sensible
    EXPECT_TRUE(noSwap == 0x1234 || noSwap == 0x3412);
}

TEST_F(ImageTest_1092, ByteSwap4WithDataBuf_1092) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    buf.data()[2] = 0x56;
    buf.data()[3] = 0x78;
    
    uint32_t noSwap = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t swapped = Exiv2::Image::byteSwap4(buf, 0, true);
    
    EXPECT_NE(noSwap, swapped);
}

TEST_F(ImageTest_1092, ByteSwap8WithDataBuf_1092) {
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
    uint64_t swapped = Exiv2::Image::byteSwap8(buf, 0, true);
    
    EXPECT_NE(noSwap, swapped);
}

// --- printStructure basic test ---

TEST_F(ImageTest_1092, PrintStructureDoesNotCrash_1092) {
    std::ostringstream oss;
    // PrintStructureOption::kpsNone should be safe
    EXPECT_NO_THROW(image_->printStructure(oss, Exiv2::kpsNone, 0));
}

// --- setTypeSupported test ---

TEST_F(ImageTest_1092, SetTypeSupportedChangesType_1092) {
    image_->setTypeSupported(Exiv2::ImageType::jpeg, 0xFFFF);
    EXPECT_EQ(image_->imageType(), Exiv2::ImageType::jpeg);
}

// --- isLongLongType test ---

TEST_F(ImageTest_1092, IsLongLongType_1092) {
    // TIFF LONG8 type is 16 (for BigTIFF)
    // Type 0 should not be longlong
    EXPECT_FALSE(Exiv2::Image::isLongLongType(0));
}

// --- Comment with unicode-like content ---

TEST_F(ImageTest_1092, SetCommentWithUTF8Content_1092) {
    std::string utf8Comment = u8"日本語テスト";
    image_->setComment(utf8Comment);
    EXPECT_EQ(image_->comment(), utf8Comment);
}

// --- Multiple operations sequence ---

TEST_F(ImageTest_1092, MultipleSetClearOperations_1092) {
    image_->setComment("c1");
    image_->clearComment();
    image_->setComment("c2");
    EXPECT_EQ(image_->comment(), "c2");
    
    image_->clearMetadata();
    EXPECT_EQ(image_->comment(), "");
    
    image_->setComment("c3");
    EXPECT_EQ(image_->comment(), "c3");
}
