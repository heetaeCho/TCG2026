#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/image.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>
#include <memory>
#include <sstream>

using namespace Exiv2;

// We need a concrete Image subclass since Image is abstract (has pure virtual methods)
// We'll use a minimal approach by creating a test image via ImageFactory or using MemIo
// Since Image itself is abstract, we need to find a way to instantiate it.
// We'll create a minimal concrete subclass for testing purposes.

class TestImage_1071 : public Exiv2::Image {
public:
    TestImage_1071(std::unique_ptr<BasicIo> io)
        : Image(ImageType::none, mdExif | mdIptc | mdXmp | mdComment, std::move(io)) {}

    void readMetadata() override {}
    void writeMetadata() override {}
};

class ImageTest_1071 : public ::testing::Test {
protected:
    void SetUp() override {
        XmpParser::initialize();
        auto io = std::make_unique<MemIo>();
        image_ = std::make_unique<TestImage_1071>(std::move(io));
    }

    void TearDown() override {
        image_.reset();
        XmpParser::terminate();
    }

    std::unique_ptr<TestImage_1071> image_;
};

// Test that xmpPacket() returns empty string when xmpData is empty and no packet is set
TEST_F(ImageTest_1071, XmpPacketReturnsEmptyWhenNoData_1071) {
    std::string& packet = image_->xmpPacket();
    EXPECT_TRUE(packet.empty());
}

// Test that setting xmpPacket directly returns the set value when writeXmpFromPacket is true
TEST_F(ImageTest_1071, XmpPacketReturnsSetPacketWhenWriteFromPacket_1071) {
    std::string testPacket = "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\"><rdf:RDF></rdf:RDF></x:xmpmeta>";
    image_->setXmpPacket(testPacket);
    image_->writeXmpFromPacket(true);
    std::string& packet = image_->xmpPacket();
    EXPECT_EQ(packet, testPacket);
}

// Test that xmpPacket() encodes xmpData when writeXmpFromPacket is false and xmpData is not empty
TEST_F(ImageTest_1071, XmpPacketEncodesWhenXmpDataNotEmptyAndWriteFromPacketFalse_1071) {
    XmpData& xmpData = image_->xmpData();
    xmpData["Xmp.dc.title"] = "Test Title";
    image_->writeXmpFromPacket(false);
    std::string& packet = image_->xmpPacket();
    // The packet should not be empty after encoding
    EXPECT_FALSE(packet.empty());
}

// Test that xmpPacket() returns the raw packet when writeXmpFromPacket is true even with xmpData
TEST_F(ImageTest_1071, XmpPacketReturnsRawPacketWhenWriteFromPacketTrue_1071) {
    std::string testPacket = "some raw xmp packet";
    image_->setXmpPacket(testPacket);
    image_->writeXmpFromPacket(true);
    // Also set some xmp data
    XmpData& xmpData = image_->xmpData();
    xmpData["Xmp.dc.title"] = "Test Title";
    std::string& packet = image_->xmpPacket();
    // When writeXmpFromPacket is true, xmpPacket should return the stored packet as-is
    EXPECT_EQ(packet, testPacket);
}

// Test that clearing xmpData makes xmpPacket return empty (or unchanged packet)
TEST_F(ImageTest_1071, XmpPacketAfterClearXmpData_1071) {
    XmpData& xmpData = image_->xmpData();
    xmpData["Xmp.dc.title"] = "Test Title";
    image_->writeXmpFromPacket(false);
    // First call to encode
    std::string& packet1 = image_->xmpPacket();
    EXPECT_FALSE(packet1.empty());

    // Clear xmp data
    image_->clearXmpData();
    std::string& packet2 = image_->xmpPacket();
    // After clearing, xmpData is empty, so it should return the packet as-is (not re-encode)
    // The behavior depends on whether the packet was cleared too
}

// Test writeXmpFromPacket getter and setter
TEST_F(ImageTest_1071, WriteXmpFromPacketDefaultIsFalse_1071) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1071, WriteXmpFromPacketSetTrue_1071) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1071, WriteXmpFromPacketSetFalse_1071) {
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// Test setXmpData and xmpData accessors
TEST_F(ImageTest_1071, SetAndGetXmpData_1071) {
    XmpData data;
    data["Xmp.dc.creator"] = "Author";
    image_->setXmpData(data);
    XmpData& retrieved = image_->xmpData();
    EXPECT_FALSE(retrieved.empty());
}

// Test clearXmpData
TEST_F(ImageTest_1071, ClearXmpData_1071) {
    XmpData& xmpData = image_->xmpData();
    xmpData["Xmp.dc.title"] = "Test";
    EXPECT_FALSE(image_->xmpData().empty());
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// Test clearXmpPacket
TEST_F(ImageTest_1071, ClearXmpPacket_1071) {
    image_->setXmpPacket("some packet");
    image_->writeXmpFromPacket(true);
    EXPECT_FALSE(image_->xmpPacket().empty());
    image_->clearXmpPacket();
    // After clearing, with writeXmpFromPacket true and empty xmpData, packet should be empty
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// Test setXmpPacket
TEST_F(ImageTest_1071, SetXmpPacket_1071) {
    std::string packet = "<?xpacket begin='...'?>";
    image_->setXmpPacket(packet);
    image_->writeXmpFromPacket(true);
    EXPECT_EQ(image_->xmpPacket(), packet);
}

// Test exifData accessor
TEST_F(ImageTest_1071, ExifDataAccessor_1071) {
    ExifData& data = image_->exifData();
    EXPECT_TRUE(data.empty());
}

// Test iptcData accessor
TEST_F(ImageTest_1071, IptcDataAccessor_1071) {
    IptcData& data = image_->iptcData();
    EXPECT_TRUE(data.empty());
}

// Test setExifData and clearExifData
TEST_F(ImageTest_1071, SetAndClearExifData_1071) {
    ExifData data;
    image_->setExifData(data);
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

// Test setIptcData and clearIptcData
TEST_F(ImageTest_1071, SetAndClearIptcData_1071) {
    IptcData data;
    image_->setIptcData(data);
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

// Test comment getter/setter
TEST_F(ImageTest_1071, SetAndGetComment_1071) {
    image_->setComment("Hello World");
    EXPECT_EQ(image_->comment(), "Hello World");
}

// Test clearComment
TEST_F(ImageTest_1071, ClearComment_1071) {
    image_->setComment("Hello");
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

// Test byteOrder
TEST_F(ImageTest_1071, ByteOrderDefault_1071) {
    EXPECT_EQ(image_->byteOrder(), invalidByteOrder);
}

TEST_F(ImageTest_1071, SetByteOrder_1071) {
    image_->setByteOrder(bigEndian);
    EXPECT_EQ(image_->byteOrder(), bigEndian);
    image_->setByteOrder(littleEndian);
    EXPECT_EQ(image_->byteOrder(), littleEndian);
}

// Test pixelWidth and pixelHeight defaults
TEST_F(ImageTest_1071, PixelDimensionsDefault_1071) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// Test good() - with MemIo it should be good
TEST_F(ImageTest_1071, GoodReturnsTrue_1071) {
    EXPECT_TRUE(image_->good());
}

// Test clearMetadata clears everything
TEST_F(ImageTest_1071, ClearMetadata_1071) {
    image_->setComment("Test comment");
    XmpData& xmpData = image_->xmpData();
    xmpData["Xmp.dc.title"] = "Test";
    image_->clearMetadata();
    EXPECT_TRUE(image_->comment().empty());
    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
}

// Test nativePreviews returns empty list by default
TEST_F(ImageTest_1071, NativePreviewsEmpty_1071) {
    const NativePreviewList& previews = image_->nativePreviews();
    EXPECT_TRUE(previews.empty());
}

// Test static byte swap functions
TEST_F(ImageTest_1071, ByteSwap16NoSwap_1071) {
    uint16_t val = 0x0102;
    EXPECT_EQ(Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1071, ByteSwap16Swap_1071) {
    uint16_t val = 0x0102;
    uint16_t swapped = Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0201);
}

TEST_F(ImageTest_1071, ByteSwap32NoSwap_1071) {
    uint32_t val = 0x01020304;
    EXPECT_EQ(Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1071, ByteSwap32Swap_1071) {
    uint32_t val = 0x01020304;
    uint32_t swapped = Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x04030201u);
}

TEST_F(ImageTest_1071, ByteSwap64NoSwap_1071) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1071, ByteSwap64Swap_1071) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t swapped = Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0807060504030201ULL);
}

// Test static platform endianness checks (mutually exclusive)
TEST_F(ImageTest_1071, PlatformEndianness_1071) {
    bool isBig = Image::isBigEndianPlatform();
    bool isLittle = Image::isLittleEndianPlatform();
    EXPECT_NE(isBig, isLittle);
}

// Test isStringType for known types
TEST_F(ImageTest_1071, IsStringType_1071) {
    // Type 2 is ASCII in TIFF
    EXPECT_TRUE(Image::isStringType(2));
    // Type 1 (BYTE) should not be string
    EXPECT_FALSE(Image::isStringType(1));
}

// Test isShortType
TEST_F(ImageTest_1071, IsShortType_1071) {
    // Type 3 is SHORT in TIFF
    EXPECT_TRUE(Image::isShortType(3));
    EXPECT_FALSE(Image::isShortType(2));
}

// Test isLongType
TEST_F(ImageTest_1071, IsLongType_1071) {
    // Type 4 is LONG in TIFF
    EXPECT_TRUE(Image::isLongType(4));
    EXPECT_FALSE(Image::isLongType(3));
}

// Test isRationalType
TEST_F(ImageTest_1071, IsRationalType_1071) {
    // Type 5 is RATIONAL in TIFF
    EXPECT_TRUE(Image::isRationalType(5));
    EXPECT_FALSE(Image::isRationalType(4));
}

// Test is2ByteType
TEST_F(ImageTest_1071, Is2ByteType_1071) {
    // SHORT (3) is 2 bytes
    EXPECT_TRUE(Image::is2ByteType(3));
    EXPECT_FALSE(Image::is2ByteType(4));
}

// Test is4ByteType
TEST_F(ImageTest_1071, Is4ByteType_1071) {
    // LONG (4) is 4 bytes
    EXPECT_TRUE(Image::is4ByteType(4));
    EXPECT_FALSE(Image::is4ByteType(3));
}

// Test is8ByteType
TEST_F(ImageTest_1071, Is8ByteType_1071) {
    // RATIONAL (5) is 8 bytes
    EXPECT_TRUE(Image::is8ByteType(5));
    EXPECT_FALSE(Image::is8ByteType(4));
}

// Test imageType
TEST_F(ImageTest_1071, ImageTypeIsNone_1071) {
    EXPECT_EQ(image_->imageType(), ImageType::none);
}

// Test iccProfile operations
TEST_F(ImageTest_1071, IccProfileDefaultNotDefined_1071) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1071, ClearIccProfile_1071) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

// Test setMetadata copies from another image
TEST_F(ImageTest_1071, SetMetadataFromAnotherImage_1071) {
    auto io2 = std::make_unique<MemIo>();
    TestImage_1071 other(std::move(io2));
    other.setComment("Copied comment");

    image_->setMetadata(other);
    EXPECT_EQ(image_->comment(), "Copied comment");
}

// Test xmpPacket() returns reference that can be modified
TEST_F(ImageTest_1071, XmpPacketReturnsMutableReference_1071) {
    image_->writeXmpFromPacket(true);
    image_->setXmpPacket("original");
    std::string& packet = image_->xmpPacket();
    packet = "modified";
    EXPECT_EQ(image_->xmpPacket(), "modified");
}

// Test encoding happens when xmpData is non-empty and writeXmpFromPacket is false
TEST_F(ImageTest_1071, XmpPacketEncodingProducesValidXmp_1071) {
    XmpData& xmpData = image_->xmpData();
    xmpData["Xmp.dc.subject"] = "test subject";
    image_->writeXmpFromPacket(false);
    std::string& packet = image_->xmpPacket();
    // Should contain some XMP content
    EXPECT_FALSE(packet.empty());
    // Should contain the namespace or property reference
    EXPECT_NE(packet.find("dc"), std::string::npos);
}

// Test that with empty xmpData and writeXmpFromPacket false, existing packet is returned as-is
TEST_F(ImageTest_1071, XmpPacketEmptyDataReturnsSamePacket_1071) {
    std::string testPacket = "existing packet content";
    image_->setXmpPacket(testPacket);
    image_->writeXmpFromPacket(false);
    // xmpData is empty, so condition (!xmpData_.empty() && !writeXmpFromPacket()) is false
    // Should return the existing packet
    std::string& packet = image_->xmpPacket();
    EXPECT_EQ(packet, testPacket);
}

// Test supportsMetadata
TEST_F(ImageTest_1071, SupportsMetadata_1071) {
    EXPECT_TRUE(image_->supportsMetadata(mdExif));
    EXPECT_TRUE(image_->supportsMetadata(mdIptc));
    EXPECT_TRUE(image_->supportsMetadata(mdXmp));
    EXPECT_TRUE(image_->supportsMetadata(mdComment));
}

// Test io accessor
TEST_F(ImageTest_1071, IoAccessor_1071) {
    const BasicIo& io = image_->io();
    // MemIo should be accessible
    EXPECT_NO_THROW(io.size());
}
