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
// (readMetadata, writeMetadata) that need to be implemented.
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

class ImageTest_1069 : public ::testing::Test {
protected:
    std::unique_ptr<TestImage> createTestImage() {
        auto io = std::make_unique<Exiv2::MemIo>();
        return std::make_unique<TestImage>(std::move(io));
    }
};

// ============================================================
// Tests for iptcData()
// ============================================================

TEST_F(ImageTest_1069, IptcDataReturnsReference_1069) {
    auto img = createTestImage();
    Exiv2::IptcData& iptc = img->iptcData();
    // Initially should be empty
    EXPECT_TRUE(iptc.empty());
}

TEST_F(ImageTest_1069, SetIptcDataAndRetrieve_1069) {
    auto img = createTestImage();
    Exiv2::IptcData iptcData;
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::string);
    val->read("Test Caption");
    iptcData.add(key, val.get());

    img->setIptcData(iptcData);
    Exiv2::IptcData& retrieved = img->iptcData();
    EXPECT_FALSE(retrieved.empty());
    EXPECT_EQ(retrieved.count(), 1u);
}

TEST_F(ImageTest_1069, ClearIptcData_1069) {
    auto img = createTestImage();
    Exiv2::IptcData iptcData;
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::string);
    val->read("Test Caption");
    iptcData.add(key, val.get());
    img->setIptcData(iptcData);

    EXPECT_FALSE(img->iptcData().empty());
    img->clearIptcData();
    EXPECT_TRUE(img->iptcData().empty());
}

// ============================================================
// Tests for exifData()
// ============================================================

TEST_F(ImageTest_1069, ExifDataReturnsReference_1069) {
    auto img = createTestImage();
    Exiv2::ExifData& exif = img->exifData();
    EXPECT_TRUE(exif.empty());
}

TEST_F(ImageTest_1069, SetExifDataAndRetrieve_1069) {
    auto img = createTestImage();
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";

    img->setExifData(exifData);
    Exiv2::ExifData& retrieved = img->exifData();
    EXPECT_FALSE(retrieved.empty());
}

TEST_F(ImageTest_1069, ClearExifData_1069) {
    auto img = createTestImage();
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    img->setExifData(exifData);

    EXPECT_FALSE(img->exifData().empty());
    img->clearExifData();
    EXPECT_TRUE(img->exifData().empty());
}

// ============================================================
// Tests for xmpData()
// ============================================================

TEST_F(ImageTest_1069, XmpDataReturnsReference_1069) {
    auto img = createTestImage();
    Exiv2::XmpData& xmp = img->xmpData();
    EXPECT_TRUE(xmp.empty());
}

TEST_F(ImageTest_1069, SetXmpDataAndRetrieve_1069) {
    auto img = createTestImage();
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test Title";

    img->setXmpData(xmpData);
    Exiv2::XmpData& retrieved = img->xmpData();
    EXPECT_FALSE(retrieved.empty());
}

TEST_F(ImageTest_1069, ClearXmpData_1069) {
    auto img = createTestImage();
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test Title";
    img->setXmpData(xmpData);

    EXPECT_FALSE(img->xmpData().empty());
    img->clearXmpData();
    EXPECT_TRUE(img->xmpData().empty());
}

// ============================================================
// Tests for xmpPacket()
// ============================================================

TEST_F(ImageTest_1069, XmpPacketInitiallyEmpty_1069) {
    auto img = createTestImage();
    std::string& pkt = img->xmpPacket();
    EXPECT_TRUE(pkt.empty());
}

TEST_F(ImageTest_1069, SetXmpPacketAndRetrieve_1069) {
    auto img = createTestImage();
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    img->setXmpPacket(packet);
    EXPECT_EQ(img->xmpPacket(), packet);
}

TEST_F(ImageTest_1069, ClearXmpPacket_1069) {
    auto img = createTestImage();
    img->setXmpPacket("<x:xmpmeta>test</x:xmpmeta>");
    EXPECT_FALSE(img->xmpPacket().empty());
    img->clearXmpPacket();
    EXPECT_TRUE(img->xmpPacket().empty());
}

// ============================================================
// Tests for comment()
// ============================================================

TEST_F(ImageTest_1069, CommentInitiallyEmpty_1069) {
    auto img = createTestImage();
    EXPECT_TRUE(img->comment().empty());
}

TEST_F(ImageTest_1069, SetCommentAndRetrieve_1069) {
    auto img = createTestImage();
    std::string comment = "This is a test comment";
    img->setComment(comment);
    EXPECT_EQ(img->comment(), comment);
}

TEST_F(ImageTest_1069, ClearComment_1069) {
    auto img = createTestImage();
    img->setComment("Some comment");
    EXPECT_FALSE(img->comment().empty());
    img->clearComment();
    EXPECT_TRUE(img->comment().empty());
}

// ============================================================
// Tests for byteOrder()
// ============================================================

TEST_F(ImageTest_1069, ByteOrderDefaultInvalid_1069) {
    auto img = createTestImage();
    EXPECT_EQ(img->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageTest_1069, SetByteOrderBigEndian_1069) {
    auto img = createTestImage();
    img->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(img->byteOrder(), Exiv2::bigEndian);
}

TEST_F(ImageTest_1069, SetByteOrderLittleEndian_1069) {
    auto img = createTestImage();
    img->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(img->byteOrder(), Exiv2::littleEndian);
}

// ============================================================
// Tests for pixelWidth() and pixelHeight()
// ============================================================

TEST_F(ImageTest_1069, PixelWidthInitiallyZero_1069) {
    auto img = createTestImage();
    EXPECT_EQ(img->pixelWidth(), 0u);
}

TEST_F(ImageTest_1069, PixelHeightInitiallyZero_1069) {
    auto img = createTestImage();
    EXPECT_EQ(img->pixelHeight(), 0u);
}

// ============================================================
// Tests for writeXmpFromPacket()
// ============================================================

TEST_F(ImageTest_1069, WriteXmpFromPacketDefaultFalse_1069) {
    auto img = createTestImage();
    EXPECT_FALSE(img->writeXmpFromPacket());
}

TEST_F(ImageTest_1069, SetWriteXmpFromPacketTrue_1069) {
    auto img = createTestImage();
    img->writeXmpFromPacket(true);
    EXPECT_TRUE(img->writeXmpFromPacket());
}

TEST_F(ImageTest_1069, SetWriteXmpFromPacketFalse_1069) {
    auto img = createTestImage();
    img->writeXmpFromPacket(true);
    img->writeXmpFromPacket(false);
    EXPECT_FALSE(img->writeXmpFromPacket());
}

// ============================================================
// Tests for clearMetadata()
// ============================================================

TEST_F(ImageTest_1069, ClearMetadataClearsAll_1069) {
    auto img = createTestImage();
    
    // Set some data
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    img->setExifData(exifData);
    
    Exiv2::IptcData iptcData;
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::string);
    val->read("Test");
    iptcData.add(key, val.get());
    img->setIptcData(iptcData);
    
    img->setComment("A comment");
    
    // Clear all
    img->clearMetadata();
    
    EXPECT_TRUE(img->exifData().empty());
    EXPECT_TRUE(img->iptcData().empty());
    EXPECT_TRUE(img->comment().empty());
}

// ============================================================
// Tests for setMetadata()
// ============================================================

TEST_F(ImageTest_1069, SetMetadataFromAnotherImage_1069) {
    auto src = createTestImage();
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "SourceMake";
    src->setExifData(exifData);
    src->setComment("Source comment");

    auto dst = createTestImage();
    EXPECT_TRUE(dst->exifData().empty());
    EXPECT_TRUE(dst->comment().empty());

    dst->setMetadata(*src);
    EXPECT_FALSE(dst->exifData().empty());
    EXPECT_EQ(dst->comment(), "Source comment");
}

// ============================================================
// Tests for good()
// ============================================================

TEST_F(ImageTest_1069, GoodReturnsTrueForValidIo_1069) {
    auto img = createTestImage();
    // MemIo should be "good" by default
    EXPECT_TRUE(img->good());
}

// ============================================================
// Tests for io()
// ============================================================

TEST_F(ImageTest_1069, IoReturnsReference_1069) {
    auto img = createTestImage();
    const Exiv2::BasicIo& io = img->io();
    // Just verify it doesn't throw and returns something
    (void)io;
    SUCCEED();
}

// ============================================================
// Tests for nativePreviews()
// ============================================================

TEST_F(ImageTest_1069, NativePreviewsInitiallyEmpty_1069) {
    auto img = createTestImage();
    const Exiv2::NativePreviewList& previews = img->nativePreviews();
    EXPECT_TRUE(previews.empty());
}

// ============================================================
// Tests for ICC profile
// ============================================================

TEST_F(ImageTest_1069, IccProfileNotDefinedInitially_1069) {
    auto img = createTestImage();
    EXPECT_FALSE(img->iccProfileDefined());
}

TEST_F(ImageTest_1069, ClearIccProfile_1069) {
    auto img = createTestImage();
    img->clearIccProfile();
    EXPECT_FALSE(img->iccProfileDefined());
}

// ============================================================
// Tests for static type checking methods
// ============================================================

TEST_F(ImageTest_1069, IsStringType_1069) {
    // Type 2 is ASCII in TIFF
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
    // Type 1 is BYTE, not string
    EXPECT_FALSE(Exiv2::Image::isStringType(1));
}

TEST_F(ImageTest_1069, IsShortType_1069) {
    // Type 3 is SHORT in TIFF
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
    EXPECT_FALSE(Exiv2::Image::isShortType(1));
}

TEST_F(ImageTest_1069, IsLongType_1069) {
    // Type 4 is LONG in TIFF
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
    EXPECT_FALSE(Exiv2::Image::isLongType(1));
}

TEST_F(ImageTest_1069, IsRationalType_1069) {
    // Type 5 is RATIONAL in TIFF
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
    EXPECT_FALSE(Exiv2::Image::isRationalType(1));
}

TEST_F(ImageTest_1069, Is2ByteType_1069) {
    // SHORT (3) is 2 bytes
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

TEST_F(ImageTest_1069, Is4ByteType_1069) {
    // LONG (4) is 4 bytes
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
}

TEST_F(ImageTest_1069, Is8ByteType_1069) {
    // RATIONAL (5) is 8 bytes
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
    EXPECT_FALSE(Exiv2::Image::is8ByteType(3));
}

// ============================================================
// Tests for static byteSwap methods
// ============================================================

TEST_F(ImageTest_1069, ByteSwap16NoSwap_1069) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x1234u);
}

TEST_F(ImageTest_1069, ByteSwap16WithSwap_1069) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x3412u);
}

TEST_F(ImageTest_1069, ByteSwap32NoSwap_1069) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x12345678u);
}

TEST_F(ImageTest_1069, ByteSwap32WithSwap_1069) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x78563412u);
}

TEST_F(ImageTest_1069, ByteSwap64NoSwap_1069) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x0102030405060708ULL);
}

TEST_F(ImageTest_1069, ByteSwap64WithSwap_1069) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x0807060504030201ULL);
}

// ============================================================
// Tests for platform endianness (just verify they return a bool)
// ============================================================

TEST_F(ImageTest_1069, EndianPlatformConsistency_1069) {
    bool big = Exiv2::Image::isBigEndianPlatform();
    bool little = Exiv2::Image::isLittleEndianPlatform();
    // Exactly one should be true
    EXPECT_NE(big, little);
}

// ============================================================
// Tests for byteSwap2, byteSwap4, byteSwap8 with DataBuf
// ============================================================

TEST_F(ImageTest_1069, ByteSwap2FromBuf_1069) {
    Exiv2::DataBuf buf(4);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    
    uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
    
    // One should be the byte-swapped version of the other
    EXPECT_NE(noSwap, swapped);
}

TEST_F(ImageTest_1069, ByteSwap4FromBuf_1069) {
    Exiv2::DataBuf buf(8);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    buf.write_uint8(2, 0x56);
    buf.write_uint8(3, 0x78);
    
    uint32_t noSwap = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t swapped = Exiv2::Image::byteSwap4(buf, 0, true);
    
    EXPECT_NE(noSwap, swapped);
}

TEST_F(ImageTest_1069, ByteSwap8FromBuf_1069) {
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

// ============================================================
// Tests for imageType()
// ============================================================

TEST_F(ImageTest_1069, ImageTypeReturnsCorrectType_1069) {
    auto img = createTestImage();
    EXPECT_EQ(img->imageType(), Exiv2::ImageType::none);
}

// ============================================================
// Boundary: ByteSwap with zero values
// ============================================================

TEST_F(ImageTest_1069, ByteSwap16Zero_1069) {
    uint16_t val = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0u);
}

TEST_F(ImageTest_1069, ByteSwap32Zero_1069) {
    uint32_t val = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0u);
}

TEST_F(ImageTest_1069, ByteSwap64Zero_1069) {
    uint64_t val = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0ULL);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0ULL);
}

// ============================================================
// Boundary: ByteSwap with max values
// ============================================================

TEST_F(ImageTest_1069, ByteSwap16Max_1069) {
    uint16_t val = 0xFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFu);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0xFFFFu);
}

TEST_F(ImageTest_1069, ByteSwap32Max_1069) {
    uint32_t val = 0xFFFFFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFFFFFu);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0xFFFFFFFFu);
}

TEST_F(ImageTest_1069, ByteSwap64Max_1069) {
    uint64_t val = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFFFFFFFFFFFFFULL);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0xFFFFFFFFFFFFFFFFULL);
}

// ============================================================
// Test setting empty comment
// ============================================================

TEST_F(ImageTest_1069, SetEmptyComment_1069) {
    auto img = createTestImage();
    img->setComment("");
    EXPECT_TRUE(img->comment().empty());
}

// ============================================================
// Test setting comment with special characters
// ============================================================

TEST_F(ImageTest_1069, SetCommentWithSpecialChars_1069) {
    auto img = createTestImage();
    std::string specialComment = "Hello\nWorld\t\"Quoted\"";
    img->setComment(specialComment);
    EXPECT_EQ(img->comment(), specialComment);
}

// ============================================================
// Test mimeType (default)
// ============================================================

TEST_F(ImageTest_1069, MimeTypeDefault_1069) {
    auto img = createTestImage();
    std::string mime = img->mimeType();
    // Just check it returns something (default for ImageType::none)
    EXPECT_FALSE(mime.empty());
}

// ============================================================
// Test double-setting metadata replaces previous
// ============================================================

TEST_F(ImageTest_1069, SetIptcDataReplacesExisting_1069) {
    auto img = createTestImage();
    
    Exiv2::IptcData iptc1;
    Exiv2::IptcKey key1("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr val1 = Exiv2::Value::create(Exiv2::string);
    val1->read("First");
    iptc1.add(key1, val1.get());
    img->setIptcData(iptc1);
    EXPECT_EQ(img->iptcData().count(), 1u);
    
    Exiv2::IptcData iptc2;
    img->setIptcData(iptc2);
    EXPECT_TRUE(img->iptcData().empty());
}
