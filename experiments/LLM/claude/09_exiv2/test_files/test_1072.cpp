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

using namespace Exiv2;

// A concrete test image class that allows controlling supported metadata
class TestImage : public Image {
public:
    TestImage(uint16_t supportedMetadata)
        : Image(ImageType::none, supportedMetadata, std::make_unique<MemIo>()) {}

    void readMetadata() override {}
    void writeMetadata() override {}
    std::string mimeType() const override { return "application/octet-stream"; }
};

class ImageTest_1072 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that setMetadata copies exif data when exif write is supported
TEST_F(ImageTest_1072, SetMetadataCopiesExifData_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage src(allMetadata);
    TestImage dst(allMetadata);

    // Add some exif data to source
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("TestCamera");
    src.exifData().add(key, value.get());

    ASSERT_FALSE(src.exifData().empty());
    ASSERT_TRUE(dst.exifData().empty());

    dst.setMetadata(src);

    EXPECT_FALSE(dst.exifData().empty());
}

// Test that setMetadata copies IPTC data when IPTC write is supported
TEST_F(ImageTest_1072, SetMetadataCopiesIptcData_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage src(allMetadata);
    TestImage dst(allMetadata);

    Exiv2::IptcKey iptcKey("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("Test Caption");
    src.iptcData().add(iptcKey, value.get());

    ASSERT_FALSE(src.iptcData().empty());
    ASSERT_TRUE(dst.iptcData().empty());

    dst.setMetadata(src);

    EXPECT_FALSE(dst.iptcData().empty());
}

// Test that setMetadata copies comment when comment write is supported
TEST_F(ImageTest_1072, SetMetadataCopiesComment_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage src(allMetadata);
    TestImage dst(allMetadata);

    src.setComment("Hello World");
    ASSERT_EQ(src.comment(), "Hello World");

    dst.setMetadata(src);

    EXPECT_EQ(dst.comment(), "Hello World");
}

// Test that setMetadata copies XMP data when XMP write is supported
TEST_F(ImageTest_1072, SetMetadataCopiesXmpData_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage src(allMetadata);
    TestImage dst(allMetadata);

    src.setXmpPacket("<x:xmpmeta>test</x:xmpmeta>");

    dst.setMetadata(src);

    EXPECT_EQ(dst.xmpPacket(), src.xmpPacket());
}

// Test that setMetadata does NOT copy exif when exif is not supported
TEST_F(ImageTest_1072, SetMetadataSkipsExifWhenNotSupported_1072) {
    uint16_t srcMeta = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    uint16_t dstMeta = mdIptc | mdComment | mdXmp | mdIccProfile; // No exif support

    TestImage src(srcMeta);
    TestImage dst(dstMeta);

    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("TestCamera");
    src.exifData().add(key, value.get());

    dst.setMetadata(src);

    EXPECT_TRUE(dst.exifData().empty());
}

// Test that setMetadata does NOT copy IPTC when IPTC is not supported
TEST_F(ImageTest_1072, SetMetadataSkipsIptcWhenNotSupported_1072) {
    uint16_t srcMeta = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    uint16_t dstMeta = mdExif | mdComment | mdXmp | mdIccProfile; // No IPTC support

    TestImage src(srcMeta);
    TestImage dst(dstMeta);

    Exiv2::IptcKey iptcKey("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("Test Caption");
    src.iptcData().add(iptcKey, value.get());

    dst.setMetadata(src);

    EXPECT_TRUE(dst.iptcData().empty());
}

// Test that setMetadata does NOT copy comment when comment is not supported
TEST_F(ImageTest_1072, SetMetadataSkipsCommentWhenNotSupported_1072) {
    uint16_t srcMeta = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    uint16_t dstMeta = mdExif | mdIptc | mdXmp | mdIccProfile; // No comment support

    TestImage src(srcMeta);
    TestImage dst(dstMeta);

    src.setComment("Hello World");

    dst.setMetadata(src);

    EXPECT_EQ(dst.comment(), "");
}

// Test that setMetadata does NOT copy XMP when XMP is not supported
TEST_F(ImageTest_1072, SetMetadataSkipsXmpWhenNotSupported_1072) {
    uint16_t srcMeta = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    uint16_t dstMeta = mdExif | mdIptc | mdComment | mdIccProfile; // No XMP support

    TestImage src(srcMeta);
    TestImage dst(dstMeta);

    src.setXmpPacket("<x:xmpmeta>test</x:xmpmeta>");

    dst.setMetadata(src);

    EXPECT_TRUE(dst.xmpPacket().empty());
}

// Test clearMetadata clears all metadata
TEST_F(ImageTest_1072, ClearMetadataClearsAll_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    img.setComment("Test comment");
    img.setXmpPacket("<xmp>test</xmp>");

    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("TestCamera");
    img.exifData().add(key, value.get());

    img.clearMetadata();

    EXPECT_TRUE(img.exifData().empty());
    EXPECT_TRUE(img.iptcData().empty());
    EXPECT_TRUE(img.xmpData().empty());
    EXPECT_EQ(img.comment(), "");
}

// Test setComment and comment round-trip
TEST_F(ImageTest_1072, SetAndGetComment_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    img.setComment("My comment");
    EXPECT_EQ(img.comment(), "My comment");
}

// Test clearComment
TEST_F(ImageTest_1072, ClearComment_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    img.setComment("My comment");
    img.clearComment();
    EXPECT_EQ(img.comment(), "");
}

// Test clearExifData
TEST_F(ImageTest_1072, ClearExifData_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("TestCamera");
    img.exifData().add(key, value.get());

    ASSERT_FALSE(img.exifData().empty());
    img.clearExifData();
    EXPECT_TRUE(img.exifData().empty());
}

// Test clearIptcData
TEST_F(ImageTest_1072, ClearIptcData_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    Exiv2::IptcKey iptcKey("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("Caption");
    img.iptcData().add(iptcKey, value.get());

    ASSERT_FALSE(img.iptcData().empty());
    img.clearIptcData();
    EXPECT_TRUE(img.iptcData().empty());
}

// Test clearXmpData
TEST_F(ImageTest_1072, ClearXmpData_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    img.clearXmpData();
    EXPECT_TRUE(img.xmpData().empty());
}

// Test clearXmpPacket
TEST_F(ImageTest_1072, ClearXmpPacket_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    img.setXmpPacket("<xmp>data</xmp>");
    ASSERT_FALSE(img.xmpPacket().empty());
    img.clearXmpPacket();
    EXPECT_TRUE(img.xmpPacket().empty());
}

// Test setByteOrder and byteOrder
TEST_F(ImageTest_1072, SetAndGetByteOrder_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    img.setByteOrder(bigEndian);
    EXPECT_EQ(img.byteOrder(), bigEndian);

    img.setByteOrder(littleEndian);
    EXPECT_EQ(img.byteOrder(), littleEndian);
}

// Test initial byteOrder is invalidByteOrder
TEST_F(ImageTest_1072, InitialByteOrderIsInvalid_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    EXPECT_EQ(img.byteOrder(), invalidByteOrder);
}

// Test writeXmpFromPacket flag
TEST_F(ImageTest_1072, WriteXmpFromPacketFlag_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    img.writeXmpFromPacket(true);
    EXPECT_TRUE(img.writeXmpFromPacket());

    img.writeXmpFromPacket(false);
    EXPECT_FALSE(img.writeXmpFromPacket());
}

// Test pixelWidth and pixelHeight default to 0
TEST_F(ImageTest_1072, DefaultPixelDimensionsAreZero_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    EXPECT_EQ(img.pixelWidth(), 0u);
    EXPECT_EQ(img.pixelHeight(), 0u);
}

// Test good() reflects io state
TEST_F(ImageTest_1072, GoodReflectsIoState_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    // MemIo should be in a good state by default
    EXPECT_TRUE(img.good());
}

// Test checkMode for supported metadata
TEST_F(ImageTest_1072, CheckModeForSupportedMetadata_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    EXPECT_NE(img.checkMode(mdExif), amNone);
    EXPECT_NE(img.checkMode(mdIptc), amNone);
    EXPECT_NE(img.checkMode(mdComment), amNone);
    EXPECT_NE(img.checkMode(mdXmp), amNone);
    EXPECT_NE(img.checkMode(mdIccProfile), amNone);
}

// Test checkMode for unsupported metadata returns amNone
TEST_F(ImageTest_1072, CheckModeForUnsupportedMetadata_1072) {
    uint16_t noMetadata = mdNone;
    TestImage img(noMetadata);

    EXPECT_EQ(img.checkMode(mdExif), amNone);
    EXPECT_EQ(img.checkMode(mdIptc), amNone);
    EXPECT_EQ(img.checkMode(mdComment), amNone);
    EXPECT_EQ(img.checkMode(mdXmp), amNone);
    EXPECT_EQ(img.checkMode(mdIccProfile), amNone);
}

// Test supportsMetadata
TEST_F(ImageTest_1072, SupportsMetadata_1072) {
    uint16_t exifOnly = mdExif;
    TestImage img(exifOnly);

    EXPECT_TRUE(img.supportsMetadata(mdExif));
    EXPECT_FALSE(img.supportsMetadata(mdIptc));
    EXPECT_FALSE(img.supportsMetadata(mdComment));
}

// Test imageType
TEST_F(ImageTest_1072, ImageType_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    EXPECT_EQ(img.imageType(), ImageType::none);
}

// Test byteSwap static methods
TEST_F(ImageTest_1072, ByteSwap16_1072) {
    uint16_t val = 0x0102;
    uint16_t swapped = Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0201);

    uint16_t notSwapped = Image::byteSwap(val, false);
    EXPECT_EQ(notSwapped, val);
}

TEST_F(ImageTest_1072, ByteSwap32_1072) {
    uint32_t val = 0x01020304;
    uint32_t swapped = Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x04030201u);

    uint32_t notSwapped = Image::byteSwap(val, false);
    EXPECT_EQ(notSwapped, val);
}

TEST_F(ImageTest_1072, ByteSwap64_1072) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t swapped = Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0807060504030201ULL);

    uint64_t notSwapped = Image::byteSwap(val, false);
    EXPECT_EQ(notSwapped, val);
}

// Test platform endianness consistency
TEST_F(ImageTest_1072, PlatformEndianness_1072) {
    bool big = Image::isBigEndianPlatform();
    bool little = Image::isLittleEndianPlatform();
    // Exactly one should be true
    EXPECT_NE(big, little);
}

// Test isStringType
TEST_F(ImageTest_1072, IsStringType_1072) {
    // ASCII type is 2 in TIFF
    EXPECT_TRUE(Image::isStringType(2));
    // LONG type is 4 - not a string type
    EXPECT_FALSE(Image::isStringType(4));
}

// Test isShortType
TEST_F(ImageTest_1072, IsShortType_1072) {
    // SHORT type is 3 in TIFF
    EXPECT_TRUE(Image::isShortType(3));
    EXPECT_FALSE(Image::isShortType(4));
}

// Test isLongType
TEST_F(ImageTest_1072, IsLongType_1072) {
    // LONG type is 4 in TIFF
    EXPECT_TRUE(Image::isLongType(4));
    EXPECT_FALSE(Image::isLongType(3));
}

// Test isRationalType
TEST_F(ImageTest_1072, IsRationalType_1072) {
    // RATIONAL is 5, SRATIONAL is 10
    EXPECT_TRUE(Image::isRationalType(5));
    EXPECT_TRUE(Image::isRationalType(10));
    EXPECT_FALSE(Image::isRationalType(4));
}

// Test setMetadata with no metadata supported (nothing should be copied)
TEST_F(ImageTest_1072, SetMetadataWithNoSupport_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    uint16_t noMetadata = mdNone;

    TestImage src(allMetadata);
    TestImage dst(noMetadata);

    src.setComment("Test");

    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    value->read("Camera");
    src.exifData().add(key, value.get());

    dst.setMetadata(src);

    EXPECT_TRUE(dst.exifData().empty());
    EXPECT_TRUE(dst.iptcData().empty());
    EXPECT_EQ(dst.comment(), "");
    EXPECT_TRUE(dst.xmpPacket().empty());
}

// Test setXmpPacket round-trip
TEST_F(ImageTest_1072, SetAndGetXmpPacket_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    std::string xmpData = "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">test</x:xmpmeta>";
    img.setXmpPacket(xmpData);
    EXPECT_EQ(img.xmpPacket(), xmpData);
}

// Test setting empty comment
TEST_F(ImageTest_1072, SetEmptyComment_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    img.setComment("");
    EXPECT_EQ(img.comment(), "");
}

// Test ICC profile operations
TEST_F(ImageTest_1072, IccProfileDefaultNotDefined_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    EXPECT_FALSE(img.iccProfileDefined());
}

// Test clearIccProfile
TEST_F(ImageTest_1072, ClearIccProfile_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    img.clearIccProfile();
    EXPECT_FALSE(img.iccProfileDefined());
}

// Test nativePreviews initially empty
TEST_F(ImageTest_1072, NativePreviewsInitiallyEmpty_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    EXPECT_TRUE(img.nativePreviews().empty());
}

// Test mimeType
TEST_F(ImageTest_1072, MimeType_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    // Our TestImage returns "application/octet-stream"
    EXPECT_EQ(img.mimeType(), "application/octet-stream");
}

// Test io() returns valid reference
TEST_F(ImageTest_1072, IoReturnsValidReference_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage img(allMetadata);

    const BasicIo& io = img.io();
    // MemIo path is empty
    EXPECT_EQ(io.path(), "");
}

// Test is2ByteType
TEST_F(ImageTest_1072, Is2ByteType_1072) {
    // SHORT(3) and SSHORT(8) are 2-byte types
    EXPECT_TRUE(Image::is2ByteType(3));
    EXPECT_TRUE(Image::is2ByteType(8));
    EXPECT_FALSE(Image::is2ByteType(4));
}

// Test is4ByteType
TEST_F(ImageTest_1072, Is4ByteType_1072) {
    // LONG(4) and SLONG(9) are 4-byte types
    EXPECT_TRUE(Image::is4ByteType(4));
    EXPECT_TRUE(Image::is4ByteType(9));
    EXPECT_FALSE(Image::is4ByteType(3));
}

// Test is8ByteType
TEST_F(ImageTest_1072, Is8ByteType_1072) {
    // RATIONAL(5) and SRATIONAL(10) are 8-byte types
    EXPECT_TRUE(Image::is8ByteType(5));
    EXPECT_TRUE(Image::is8ByteType(10));
    EXPECT_FALSE(Image::is8ByteType(4));
}

// Test setMetadata copies ICC profile when supported
TEST_F(ImageTest_1072, SetMetadataCopiesIccProfile_1072) {
    uint16_t allMetadata = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    TestImage src(allMetadata);
    TestImage dst(allMetadata);

    // Create a minimal ICC profile-like data buffer
    const uint8_t iccData[] = {0, 0, 0, 128, // size = 128 in big-endian
                                'a', 'c', 's', 'p'}; // 'acsp' signature at offset 36
    // For a real ICC profile we'd need proper structure, but let's test with bTestValid=false
    DataBuf buf(128);
    std::memset(buf.data(), 0, 128);
    // Set size field (bytes 0-3) to 128 big-endian
    buf.data()[0] = 0;
    buf.data()[1] = 0;
    buf.data()[2] = 0;
    buf.data()[3] = 128;
    // Set 'acsp' at offset 36
    buf.data()[36] = 'a';
    buf.data()[37] = 'c';
    buf.data()[38] = 's';
    buf.data()[39] = 'p';

    src.setIccProfile(std::move(buf), false);
    ASSERT_TRUE(src.iccProfileDefined());

    dst.setMetadata(src);

    EXPECT_TRUE(dst.iccProfileDefined());
}

// Test setMetadata skips ICC profile when not supported
TEST_F(ImageTest_1072, SetMetadataSkipsIccProfileWhenNotSupported_1072) {
    uint16_t srcMeta = mdExif | mdIptc | mdComment | mdXmp | mdIccProfile;
    uint16_t dstMeta = mdExif | mdIptc | mdComment | mdXmp; // No ICC support

    TestImage src(srcMeta);
    TestImage dst(dstMeta);

    DataBuf buf(128);
    std::memset(buf.data(), 0, 128);
    buf.data()[0] = 0; buf.data()[1] = 0; buf.data()[2] = 0; buf.data()[3] = 128;
    buf.data()[36] = 'a'; buf.data()[37] = 'c'; buf.data()[38] = 's'; buf.data()[39] = 'p';

    src.setIccProfile(std::move(buf), false);

    dst.setMetadata(src);

    EXPECT_FALSE(dst.iccProfileDefined());
}

// Test byteSwap2 from DataBuf
TEST_F(ImageTest_1072, ByteSwap2FromDataBuf_1072) {
    DataBuf buf(4);
    buf.data()[0] = 0x01;
    buf.data()[1] = 0x02;

    uint16_t swapped = Image::byteSwap2(buf, 0, true);
    EXPECT_EQ(swapped, 0x0201);

    uint16_t notSwapped = Image::byteSwap2(buf, 0, false);
    EXPECT_EQ(notSwapped, 0x0102);
}

// Test byteSwap4 from DataBuf
TEST_F(ImageTest_1072, ByteSwap4FromDataBuf_1072) {
    DataBuf buf(8);
    buf.data()[0] = 0x01;
    buf.data()[1] = 0x02;
    buf.data()[2] = 0x03;
    buf.data()[3] = 0x04;

    uint32_t swapped = Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(swapped, 0x04030201u);

    uint32_t notSwapped = Image::byteSwap4(buf, 0, false);
    EXPECT_EQ(notSwapped, 0x01020304u);
}

// Test byteSwap8 from DataBuf
TEST_F(ImageTest_1072, ByteSwap8FromDataBuf_1072) {
    DataBuf buf(16);
    buf.data()[0] = 0x01;
    buf.data()[1] = 0x02;
    buf.data()[2] = 0x03;
    buf.data()[3] = 0x04;
    buf.data()[4] = 0x05;
    buf.data()[5] = 0x06;
    buf.data()[6] = 0x07;
    buf.data()[7] = 0x08;

    uint64_t swapped = Image::byteSwap8(buf, 0, true);
    EXPECT_EQ(swapped, 0x0807060504030201ULL);

    uint64_t notSwapped = Image::byteSwap8(buf, 0, false);
    EXPECT_EQ(notSwapped, 0x0102030405060708ULL);
}

// Test setTypeSupported
TEST_F(ImageTest_1072, SetTypeSupported_1072) {
    TestImage img(mdNone);

    EXPECT_FALSE(img.supportsMetadata(mdExif));
    img.setTypeSupported(ImageType::none, mdExif | mdIptc);
    EXPECT_TRUE(img.supportsMetadata(mdExif));
    EXPECT_TRUE(img.supportsMetadata(mdIptc));
}
