#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <sstream>
#include <memory>

// Since Image is abstract (has pure virtual methods like readMetadata/writeMetadata),
// we need a concrete subclass for testing. We'll use a minimal concrete implementation.
// However, we can also use ImageFactory to create images from memory.

namespace {

// A minimal concrete Image subclass for testing non-virtual and static methods
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

class ImageTest_1070 : public ::testing::Test {
protected:
    void SetUp() override {
        image_ = createTestImage();
    }

    std::unique_ptr<TestImage> image_;
};

// --- XmpData tests ---

TEST_F(ImageTest_1070, XmpDataReturnsReference_1070) {
    Exiv2::XmpData& xmp = image_->xmpData();
    EXPECT_TRUE(xmp.empty());
}

TEST_F(ImageTest_1070, SetXmpDataAndRetrieve_1070) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test Title";
    image_->setXmpData(xmpData);
    
    Exiv2::XmpData& retrieved = image_->xmpData();
    EXPECT_FALSE(retrieved.empty());
}

TEST_F(ImageTest_1070, ClearXmpData_1070) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test Title";
    image_->setXmpData(xmpData);
    EXPECT_FALSE(image_->xmpData().empty());
    
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// --- ExifData tests ---

TEST_F(ImageTest_1070, ExifDataReturnsReference_1070) {
    Exiv2::ExifData& exif = image_->exifData();
    EXPECT_TRUE(exif.empty());
}

TEST_F(ImageTest_1070, SetExifDataAndRetrieve_1070) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    
    Exiv2::ExifData& retrieved = image_->exifData();
    EXPECT_FALSE(retrieved.empty());
}

TEST_F(ImageTest_1070, ClearExifData_1070) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    EXPECT_FALSE(image_->exifData().empty());
    
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

// --- IptcData tests ---

TEST_F(ImageTest_1070, IptcDataReturnsReference_1070) {
    Exiv2::IptcData& iptc = image_->iptcData();
    EXPECT_TRUE(iptc.empty());
}

TEST_F(ImageTest_1070, SetIptcDataAndRetrieve_1070) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test Caption";
    image_->setIptcData(iptcData);
    
    Exiv2::IptcData& retrieved = image_->iptcData();
    EXPECT_FALSE(retrieved.empty());
}

TEST_F(ImageTest_1070, ClearIptcData_1070) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test Caption";
    image_->setIptcData(iptcData);
    EXPECT_FALSE(image_->iptcData().empty());
    
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

// --- Comment tests ---

TEST_F(ImageTest_1070, CommentInitiallyEmpty_1070) {
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1070, SetCommentAndRetrieve_1070) {
    image_->setComment("Hello World");
    EXPECT_EQ(image_->comment(), "Hello World");
}

TEST_F(ImageTest_1070, ClearComment_1070) {
    image_->setComment("Hello World");
    EXPECT_EQ(image_->comment(), "Hello World");
    
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1070, SetCommentEmpty_1070) {
    image_->setComment("");
    EXPECT_TRUE(image_->comment().empty());
}

// --- XmpPacket tests ---

TEST_F(ImageTest_1070, XmpPacketInitiallyEmpty_1070) {
    EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageTest_1070, SetXmpPacketAndRetrieve_1070) {
    std::string packet = "<x:xmpmeta></x:xmpmeta>";
    image_->setXmpPacket(packet);
    EXPECT_EQ(image_->xmpPacket(), packet);
}

TEST_F(ImageTest_1070, ClearXmpPacket_1070) {
    image_->setXmpPacket("<x:xmpmeta></x:xmpmeta>");
    EXPECT_FALSE(image_->xmpPacket().empty());
    
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// --- ByteOrder tests ---

TEST_F(ImageTest_1070, ByteOrderInitiallyInvalid_1070) {
    EXPECT_EQ(image_->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageTest_1070, SetByteOrderBigEndian_1070) {
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);
}

TEST_F(ImageTest_1070, SetByteOrderLittleEndian_1070) {
    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::littleEndian);
}

// --- PixelWidth/Height tests ---

TEST_F(ImageTest_1070, PixelWidthInitiallyZero_1070) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(ImageTest_1070, PixelHeightInitiallyZero_1070) {
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// --- WriteXmpFromPacket tests ---

TEST_F(ImageTest_1070, WriteXmpFromPacketInitiallyFalse_1070) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1070, SetWriteXmpFromPacketTrue_1070) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1070, SetWriteXmpFromPacketFalse_1070) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// --- good() test ---

TEST_F(ImageTest_1070, GoodReturnsTrueForValidIo_1070) {
    // MemIo should be good by default
    EXPECT_TRUE(image_->good());
}

// --- io() test ---

TEST_F(ImageTest_1070, IoReturnsValidReference_1070) {
    const Exiv2::BasicIo& io = image_->io();
    // Just checking we can access it without crash
    (void)io;
}

// --- NativePreviews tests ---

TEST_F(ImageTest_1070, NativePreviewsInitiallyEmpty_1070) {
    const Exiv2::NativePreviewList& previews = image_->nativePreviews();
    EXPECT_TRUE(previews.empty());
}

// --- ClearMetadata tests ---

TEST_F(ImageTest_1070, ClearMetadataClearsAll_1070) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test Caption";
    image_->setIptcData(iptcData);
    
    image_->setComment("Test Comment");
    
    image_->clearMetadata();
    
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->comment().empty());
}

// --- SetMetadata tests ---

TEST_F(ImageTest_1070, SetMetadataFromAnotherImage_1070) {
    auto srcImage = createTestImage();
    
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    srcImage->setExifData(exifData);
    
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Caption";
    srcImage->setIptcData(iptcData);
    
    srcImage->setComment("Test comment");
    
    image_->setMetadata(*srcImage);
    
    EXPECT_FALSE(image_->exifData().empty());
    EXPECT_FALSE(image_->iptcData().empty());
    EXPECT_EQ(image_->comment(), "Test comment");
}

// --- ICC Profile tests ---

TEST_F(ImageTest_1070, IccProfileNotDefinedInitially_1070) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1070, ClearIccProfile_1070) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1070, IccProfileInitiallyEmpty_1070) {
    const Exiv2::DataBuf& profile = image_->iccProfile();
    EXPECT_EQ(profile.size(), 0u);
}

// --- Static method tests ---

TEST_F(ImageTest_1070, EndianPlatformConsistency_1070) {
    // Platform must be either big or little endian, not both
    bool isBig = Exiv2::Image::isBigEndianPlatform();
    bool isLittle = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_NE(isBig, isLittle);
}

TEST_F(ImageTest_1070, ByteSwap16NoSwap_1070) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1070, ByteSwap16WithSwap_1070) {
    uint16_t val = 0x1234;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x3412);
}

TEST_F(ImageTest_1070, ByteSwap32NoSwap_1070) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1070, ByteSwap32WithSwap_1070) {
    uint32_t val = 0x12345678;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x78563412u);
}

TEST_F(ImageTest_1070, ByteSwap64NoSwap_1070) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1070, ByteSwap64WithSwap_1070) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0807060504030201ULL);
}

TEST_F(ImageTest_1070, ByteSwap16Zero_1070) {
    uint16_t val = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0u);
}

TEST_F(ImageTest_1070, ByteSwap32Zero_1070) {
    uint32_t val = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0u);
}

TEST_F(ImageTest_1070, ByteSwap64Zero_1070) {
    uint64_t val = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0ULL);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0ULL);
}

TEST_F(ImageTest_1070, ByteSwap16Max_1070) {
    uint16_t val = 0xFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFu);
}

TEST_F(ImageTest_1070, ByteSwap32Max_1070) {
    uint32_t val = 0xFFFFFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFFFFFu);
}

// --- isStringType tests ---

TEST_F(ImageTest_1070, IsStringTypeForAscii_1070) {
    // TIFF ASCII type = 2
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
}

TEST_F(ImageTest_1070, IsStringTypeForNonString_1070) {
    // Type 3 is SHORT, should not be string type
    EXPECT_FALSE(Exiv2::Image::isStringType(3));
}

// --- isShortType tests ---

TEST_F(ImageTest_1070, IsShortTypeForShort_1070) {
    // TIFF SHORT = 3
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
}

TEST_F(ImageTest_1070, IsShortTypeForNonShort_1070) {
    EXPECT_FALSE(Exiv2::Image::isShortType(2));
}

// --- isLongType tests ---

TEST_F(ImageTest_1070, IsLongTypeForLong_1070) {
    // TIFF LONG = 4
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
}

TEST_F(ImageTest_1070, IsLongTypeForNonLong_1070) {
    EXPECT_FALSE(Exiv2::Image::isLongType(3));
}

// --- isRationalType tests ---

TEST_F(ImageTest_1070, IsRationalTypeForRational_1070) {
    // TIFF RATIONAL = 5
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
}

TEST_F(ImageTest_1070, IsRationalTypeForNonRational_1070) {
    EXPECT_FALSE(Exiv2::Image::isRationalType(4));
}

// --- is2ByteType tests ---

TEST_F(ImageTest_1070, Is2ByteTypeForShort_1070) {
    // SHORT (3) is 2 bytes
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
}

TEST_F(ImageTest_1070, Is2ByteTypeForNon2Byte_1070) {
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

// --- is4ByteType tests ---

TEST_F(ImageTest_1070, Is4ByteTypeForLong_1070) {
    // LONG (4) is 4 bytes
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
}

TEST_F(ImageTest_1070, Is4ByteTypeForNon4Byte_1070) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
}

// --- is8ByteType tests ---

TEST_F(ImageTest_1070, Is8ByteTypeForRational_1070) {
    // RATIONAL (5) is 8 bytes
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
}

TEST_F(ImageTest_1070, Is8ByteTypeForNon8Byte_1070) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(3));
}

// --- isLongLongType tests ---

TEST_F(ImageTest_1070, IsLongLongTypeForNonLongLong_1070) {
    EXPECT_FALSE(Exiv2::Image::isLongLongType(4));
}

// --- ByteSwap with DataBuf tests ---

TEST_F(ImageTest_1070, ByteSwap2WithDataBuf_1070) {
    Exiv2::DataBuf buf(4);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    
    uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
    
    // One should be 0x1234 and the other 0x3412, depending on how it reads
    EXPECT_NE(noSwap, swapped);
}

TEST_F(ImageTest_1070, ByteSwap4WithDataBuf_1070) {
    Exiv2::DataBuf buf(8);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    buf.write_uint8(2, 0x56);
    buf.write_uint8(3, 0x78);
    
    uint32_t noSwap = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t swapped = Exiv2::Image::byteSwap4(buf, 0, true);
    
    EXPECT_NE(noSwap, swapped);
}

TEST_F(ImageTest_1070, ByteSwap8WithDataBuf_1070) {
    Exiv2::DataBuf buf(16);
    buf.write_uint8(0, 0x01);
    buf.write_uint8(1, 0x02);
    buf.write_uint8(2, 0x03);
    buf.write_uint8(3, 0x04);
    buf.write_uint8(4, 0x05);
    buf.write_uint8(5, 0x06);
    buf.write_uint8(6, 0x07);
    buf.write_uint8(7, 0x08);
    
    uint64_t noSwap = Exiv2::Image::byteSwap8(buf, 0, false);
    uint64_t swapped = Exiv2::Image::byteSwap8(buf, 0, true);
    
    EXPECT_NE(noSwap, swapped);
}

// --- ImageType test ---

TEST_F(ImageTest_1070, ImageTypeReturnsCorrectType_1070) {
    EXPECT_EQ(image_->imageType(), Exiv2::ImageType::none);
}

// --- MimeType test ---

TEST_F(ImageTest_1070, MimeTypeReturnsExpected_1070) {
    EXPECT_EQ(image_->mimeType(), "application/octet-stream");
}

// --- Double swap should return original ---

TEST_F(ImageTest_1070, DoubleByteSwap16ReturnsOriginal_1070) {
    uint16_t val = 0xABCD;
    uint16_t result = Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true);
    EXPECT_EQ(result, val);
}

TEST_F(ImageTest_1070, DoubleByteSwap32ReturnsOriginal_1070) {
    uint32_t val = 0xDEADBEEF;
    uint32_t result = Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true);
    EXPECT_EQ(result, val);
}

TEST_F(ImageTest_1070, DoubleByteSwap64ReturnsOriginal_1070) {
    uint64_t val = 0xDEADBEEFCAFEBABEULL;
    uint64_t result = Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true);
    EXPECT_EQ(result, val);
}

// --- isPrintXMP / isPrintICC ---

TEST_F(ImageTest_1070, IsPrintXMPWithPrintStructure_1070) {
    // Testing with type 2 (ASCII) and kpsXMP option
    bool result = Exiv2::Image::isPrintXMP(2, Exiv2::kpsXMP);
    // We just verify it returns a bool without crash
    (void)result;
}

TEST_F(ImageTest_1070, IsPrintICCWithPrintStructure_1070) {
    bool result = Exiv2::Image::isPrintICC(2, Exiv2::kpsIccProfile);
    (void)result;
}

// --- SetTypeSupported test ---

TEST_F(ImageTest_1070, SetTypeSupportedChangesType_1070) {
    image_->setTypeSupported(Exiv2::ImageType::jpeg, 0xFFFF);
    EXPECT_EQ(image_->imageType(), Exiv2::ImageType::jpeg);
}
