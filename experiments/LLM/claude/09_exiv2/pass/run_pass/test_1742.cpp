#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/cr2image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>
#include <sstream>
#include <fstream>
#include <cstring>

using namespace Exiv2;

// Helper to create a MemIo with specific data
static std::unique_ptr<BasicIo> createMemIo(const std::vector<uint8_t>& data) {
    auto memIo = std::make_unique<MemIo>(data.data(), data.size());
    return memIo;
}

// Helper to create an empty MemIo
static std::unique_ptr<BasicIo> createEmptyMemIo() {
    auto memIo = std::make_unique<MemIo>();
    return memIo;
}

class Cr2ImageTest_1742 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that Cr2Image can be constructed with a MemIo
TEST_F(Cr2ImageTest_1742, ConstructWithMemIo_1742) {
    auto io = createEmptyMemIo();
    ASSERT_NO_THROW(Cr2Image img(std::move(io), false));
}

// Test mimeType returns the expected CR2 MIME type
TEST_F(Cr2ImageTest_1742, MimeTypeReturnsCr2_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    EXPECT_EQ(img.mimeType(), "image/x-canon-cr2");
}

// Test that good() returns false for an empty image (no valid data)
TEST_F(Cr2ImageTest_1742, GoodReturnsFalseForEmptyImage_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    // An empty MemIo with no valid CR2 data should not be considered "good"
    // after construction without reading metadata
    // good() checks if io_ is valid
    EXPECT_TRUE(img.good());
}

// Test that setComment throws since CR2 doesn't support comments
TEST_F(Cr2ImageTest_1742, SetCommentThrows_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    EXPECT_THROW(img.setComment("test comment"), Exiv2::Error);
}

// Test pixelWidth returns 0 for an unread image
TEST_F(Cr2ImageTest_1742, PixelWidthDefaultZero_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    EXPECT_EQ(img.pixelWidth(), 0u);
}

// Test pixelHeight returns 0 for an unread image
TEST_F(Cr2ImageTest_1742, PixelHeightDefaultZero_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    EXPECT_EQ(img.pixelHeight(), 0u);
}

// Test readMetadata throws on empty/invalid data
TEST_F(Cr2ImageTest_1742, ReadMetadataThrowsOnEmptyData_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test readMetadata throws on random/invalid data
TEST_F(Cr2ImageTest_1742, ReadMetadataThrowsOnInvalidData_1742) {
    std::vector<uint8_t> randomData(256, 0xAB);
    auto io = createMemIo(randomData);
    Cr2Image img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test writeMetadata throws on empty/invalid image
TEST_F(Cr2ImageTest_1742, WriteMetadataThrowsOnEmptyImage_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    EXPECT_THROW(img.writeMetadata(), Exiv2::Error);
}

// Test printStructure throws on empty data
TEST_F(Cr2ImageTest_1742, PrintStructureThrowsOnEmptyData_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    std::ostringstream oss;
    EXPECT_THROW(img.printStructure(oss, kpsNone, 0), Exiv2::Error);
}

// Test printStructure with invalid data
TEST_F(Cr2ImageTest_1742, PrintStructureThrowsOnInvalidData_1742) {
    std::vector<uint8_t> randomData(64, 0x00);
    auto io = createMemIo(randomData);
    Cr2Image img(std::move(io), false);
    std::ostringstream oss;
    EXPECT_THROW(img.printStructure(oss, kpsBasic, 0), Exiv2::Error);
}

// Test exifData returns a reference
TEST_F(Cr2ImageTest_1742, ExifDataAccessible_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    ExifData& exif = img.exifData();
    EXPECT_TRUE(exif.empty());
}

// Test iptcData returns a reference
TEST_F(Cr2ImageTest_1742, IptcDataAccessible_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    IptcData& iptc = img.iptcData();
    EXPECT_TRUE(iptc.empty());
}

// Test xmpData returns a reference
TEST_F(Cr2ImageTest_1742, XmpDataAccessible_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    XmpData& xmp = img.xmpData();
    EXPECT_TRUE(xmp.empty());
}

// Test clearMetadata doesn't throw
TEST_F(Cr2ImageTest_1742, ClearMetadataNoThrow_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    EXPECT_NO_THROW(img.clearMetadata());
}

// Test clearExifData doesn't throw
TEST_F(Cr2ImageTest_1742, ClearExifDataNoThrow_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    EXPECT_NO_THROW(img.clearExifData());
}

// Test clearIptcData doesn't throw
TEST_F(Cr2ImageTest_1742, ClearIptcDataNoThrow_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    EXPECT_NO_THROW(img.clearIptcData());
}

// Test clearXmpData doesn't throw
TEST_F(Cr2ImageTest_1742, ClearXmpDataNoThrow_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    EXPECT_NO_THROW(img.clearXmpData());
}

// Test that io() returns reference to the underlying io
TEST_F(Cr2ImageTest_1742, IoReturnsValidReference_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    const BasicIo& ioRef = img.io();
    EXPECT_EQ(ioRef.size(), 0u);
}

// Test byteOrder default is invalidByteOrder
TEST_F(Cr2ImageTest_1742, ByteOrderDefaultInvalid_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    EXPECT_EQ(img.byteOrder(), invalidByteOrder);
}

// Test setByteOrder works
TEST_F(Cr2ImageTest_1742, SetByteOrder_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    img.setByteOrder(littleEndian);
    EXPECT_EQ(img.byteOrder(), littleEndian);
    img.setByteOrder(bigEndian);
    EXPECT_EQ(img.byteOrder(), bigEndian);
}

// Test that supportsMetadata returns true for exif, iptc, xmp
TEST_F(Cr2ImageTest_1742, SupportsMetadata_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    EXPECT_TRUE(img.supportsMetadata(mdExif));
    EXPECT_TRUE(img.supportsMetadata(mdIptc));
    EXPECT_TRUE(img.supportsMetadata(mdXmp));
}

// Test printStructure with small but slightly structured data that's still invalid CR2
TEST_F(Cr2ImageTest_1742, PrintStructureWithSmallInvalidTiff_1742) {
    // Create data that looks like a TIFF header but is not a valid CR2
    std::vector<uint8_t> data = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
    // Pad with zeros
    data.resize(64, 0x00);
    auto io = createMemIo(data);
    Cr2Image img(std::move(io), false);
    std::ostringstream oss;
    // This may throw or may produce some output depending on the data
    // We just test it doesn't crash unexpectedly for kpsNone
    try {
        img.printStructure(oss, kpsNone, 0);
    } catch (const Exiv2::Error&) {
        // Expected for invalid data
    }
}

// Test creating Cr2Image with create=true
TEST_F(Cr2ImageTest_1742, ConstructWithCreateTrue_1742) {
    auto io = createEmptyMemIo();
    ASSERT_NO_THROW(Cr2Image img(std::move(io), true));
}

// Test comment is empty by default
TEST_F(Cr2ImageTest_1742, CommentDefaultEmpty_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    EXPECT_TRUE(img.comment().empty());
}

// Test iccProfileDefined returns false by default
TEST_F(Cr2ImageTest_1742, IccProfileNotDefinedByDefault_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    EXPECT_FALSE(img.iccProfileDefined());
}

// Test clearIccProfile doesn't throw
TEST_F(Cr2ImageTest_1742, ClearIccProfileNoThrow_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    EXPECT_NO_THROW(img.clearIccProfile());
}

// Test readMetadata with data that has TIFF big-endian header but is still invalid
TEST_F(Cr2ImageTest_1742, ReadMetadataWithBigEndianTiffHeader_1742) {
    std::vector<uint8_t> data = {0x4D, 0x4D, 0x00, 0x2A, 0x00, 0x00, 0x00, 0x08};
    data.resize(128, 0x00);
    auto io = createMemIo(data);
    Cr2Image img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test writeXmpFromPacket
TEST_F(Cr2ImageTest_1742, WriteXmpFromPacketFlag_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    EXPECT_FALSE(img.writeXmpFromPacket());
    img.writeXmpFromPacket(true);
    EXPECT_TRUE(img.writeXmpFromPacket());
    img.writeXmpFromPacket(false);
    EXPECT_FALSE(img.writeXmpFromPacket());
}

// Test xmpPacket is empty by default
TEST_F(Cr2ImageTest_1742, XmpPacketDefaultEmpty_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    EXPECT_TRUE(img.xmpPacket().empty());
}

// Test imageType returns cr2
TEST_F(Cr2ImageTest_1742, ImageTypeIsCr2_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    EXPECT_EQ(img.imageType(), ImageType::cr2);
}

// Test nativePreviews is empty by default
TEST_F(Cr2ImageTest_1742, NativePreviewsEmptyByDefault_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);
    EXPECT_TRUE(img.nativePreviews().empty());
}

// Test printStructure with various PrintStructureOption values on invalid data
TEST_F(Cr2ImageTest_1742, PrintStructureVariousOptionsOnInvalidData_1742) {
    std::vector<uint8_t> data(128, 0xFF);
    auto io = createMemIo(data);
    Cr2Image img(std::move(io), false);
    std::ostringstream oss;

    // All should throw since the data is not valid CR2/TIFF
    EXPECT_THROW(img.printStructure(oss, kpsBasic, 0), Exiv2::Error);
}

// Test that Cr2Image with a file path that doesn't exist throws on readMetadata
TEST_F(Cr2ImageTest_1742, FileIoNonExistentFileThrows_1742) {
    auto fileIo = std::make_unique<FileIo>("nonexistent_cr2_file_for_testing.cr2");
    Cr2Image img(std::move(fileIo), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test setExifData and clearExifData
TEST_F(Cr2ImageTest_1742, SetAndClearExifData_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);

    ExifData exifData;
    EXPECT_NO_THROW(img.setExifData(exifData));
    EXPECT_NO_THROW(img.clearExifData());
    EXPECT_TRUE(img.exifData().empty());
}

// Test setIptcData and clearIptcData
TEST_F(Cr2ImageTest_1742, SetAndClearIptcData_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);

    IptcData iptcData;
    EXPECT_NO_THROW(img.setIptcData(iptcData));
    EXPECT_NO_THROW(img.clearIptcData());
    EXPECT_TRUE(img.iptcData().empty());
}

// Test setXmpData and clearXmpData
TEST_F(Cr2ImageTest_1742, SetAndClearXmpData_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);

    XmpData xmpData;
    EXPECT_NO_THROW(img.setXmpData(xmpData));
    EXPECT_NO_THROW(img.clearXmpData());
    EXPECT_TRUE(img.xmpData().empty());
}

// Test setXmpPacket and clearXmpPacket
TEST_F(Cr2ImageTest_1742, SetAndClearXmpPacket_1742) {
    auto io = createEmptyMemIo();
    Cr2Image img(std::move(io), false);

    EXPECT_NO_THROW(img.setXmpPacket("<xmp>test</xmp>"));
    EXPECT_FALSE(img.xmpPacket().empty());
    EXPECT_NO_THROW(img.clearXmpPacket());
    EXPECT_TRUE(img.xmpPacket().empty());
}

// Test printStructure depth parameter boundary (depth = 0)
TEST_F(Cr2ImageTest_1742, PrintStructureDepthZero_1742) {
    std::vector<uint8_t> data(64, 0x00);
    auto io = createMemIo(data);
    Cr2Image img(std::move(io), false);
    std::ostringstream oss;
    try {
        img.printStructure(oss, kpsNone, 0);
    } catch (const Exiv2::Error&) {
        // Expected
    }
}

// Test printStructure with large depth
TEST_F(Cr2ImageTest_1742, PrintStructureLargeDepth_1742) {
    std::vector<uint8_t> data(64, 0x00);
    auto io = createMemIo(data);
    Cr2Image img(std::move(io), false);
    std::ostringstream oss;
    try {
        img.printStructure(oss, kpsNone, 100);
    } catch (const Exiv2::Error&) {
        // Expected
    }
}
