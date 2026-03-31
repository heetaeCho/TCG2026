#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/pngimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/error.hpp>
#include <memory>
#include <sstream>

using namespace Exiv2;

class PngImageTest_2175 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Creating a PngImage with create=true writes a blank PNG to memory
TEST_F(PngImageTest_2175, CreateWithMemIoWritesBlankPng_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), true);
    // The image should be valid after creation
    // The io should contain the blank PNG data (103 bytes)
    EXPECT_EQ(img.io().size(), 103u);
}

// Test: Creating a PngImage with create=false does not write data
TEST_F(PngImageTest_2175, CreateFalseDoesNotWriteData_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), false);
    EXPECT_EQ(img.io().size(), 0u);
}

// Test: mimeType returns the correct MIME type for PNG
TEST_F(PngImageTest_2175, MimeTypeReturnsPng_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), true);
    EXPECT_EQ(img.mimeType(), "image/png");
}

// Test: imageType returns png
TEST_F(PngImageTest_2175, ImageTypeIsPng_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), true);
    EXPECT_EQ(img.imageType(), ImageType::png);
}

// Test: good() returns true for a valid created PNG
TEST_F(PngImageTest_2175, GoodReturnsTrueForCreatedImage_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), true);
    EXPECT_TRUE(img.good());
}

// Test: Supports Exif metadata
TEST_F(PngImageTest_2175, SupportsExifMetadata_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), false);
    EXPECT_TRUE(img.supportsMetadata(mdExif));
}

// Test: Supports IPTC metadata
TEST_F(PngImageTest_2175, SupportsIptcMetadata_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), false);
    EXPECT_TRUE(img.supportsMetadata(mdIptc));
}

// Test: Supports XMP metadata
TEST_F(PngImageTest_2175, SupportsXmpMetadata_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), false);
    EXPECT_TRUE(img.supportsMetadata(mdXmp));
}

// Test: Supports Comment metadata
TEST_F(PngImageTest_2175, SupportsCommentMetadata_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), false);
    EXPECT_TRUE(img.supportsMetadata(mdComment));
}

// Test: readMetadata on an empty (non-created) image should throw
TEST_F(PngImageTest_2175, ReadMetadataOnEmptyImageThrows_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: readMetadata on a freshly created blank PNG
TEST_F(PngImageTest_2175, ReadMetadataOnCreatedBlankPng_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), true);
    // A blank PNG should be readable without throwing
    EXPECT_NO_THROW(img.readMetadata());
}

// Test: writeMetadata on an empty (non-created) image should throw
TEST_F(PngImageTest_2175, WriteMetadataOnEmptyImageThrows_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), false);
    EXPECT_THROW(img.writeMetadata(), Exiv2::Error);
}

// Test: writeMetadata on a created blank PNG should succeed
TEST_F(PngImageTest_2175, WriteMetadataOnCreatedPng_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), true);
    // Read first so internal state is populated
    img.readMetadata();
    EXPECT_NO_THROW(img.writeMetadata());
}

// Test: Set and clear comment
TEST_F(PngImageTest_2175, SetAndClearComment_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), true);
    img.setComment("Test comment");
    EXPECT_EQ(img.comment(), "Test comment");
    img.clearComment();
    EXPECT_EQ(img.comment(), "");
}

// Test: ExifData can be set and cleared
TEST_F(PngImageTest_2175, SetAndClearExifData_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), true);
    ExifData exifData;
    img.setExifData(exifData);
    img.clearExifData();
    EXPECT_TRUE(img.exifData().empty());
}

// Test: IptcData can be set and cleared
TEST_F(PngImageTest_2175, SetAndClearIptcData_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), true);
    IptcData iptcData;
    img.setIptcData(iptcData);
    img.clearIptcData();
    EXPECT_TRUE(img.iptcData().empty());
}

// Test: XmpData can be set and cleared
TEST_F(PngImageTest_2175, SetAndClearXmpData_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), true);
    XmpData xmpData;
    img.setXmpData(xmpData);
    img.clearXmpData();
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: clearMetadata clears all metadata
TEST_F(PngImageTest_2175, ClearMetadata_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), true);
    img.setComment("some comment");
    img.clearMetadata();
    EXPECT_EQ(img.comment(), "");
    EXPECT_TRUE(img.exifData().empty());
    EXPECT_TRUE(img.iptcData().empty());
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: pixelWidth and pixelHeight default to 0 before reading metadata
TEST_F(PngImageTest_2175, DefaultPixelDimensions_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), false);
    EXPECT_EQ(img.pixelWidth(), 0u);
    EXPECT_EQ(img.pixelHeight(), 0u);
}

// Test: After reading metadata from a 1x1 blank PNG, dimensions should be 1x1
TEST_F(PngImageTest_2175, PixelDimensionsAfterReadMetadata_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), true);
    img.readMetadata();
    EXPECT_EQ(img.pixelWidth(), 1u);
    EXPECT_EQ(img.pixelHeight(), 1u);
}

// Test: printStructure does not throw on a valid blank PNG with kpsNone
TEST_F(PngImageTest_2175, PrintStructureKpsNone_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), true);
    std::ostringstream oss;
    EXPECT_NO_THROW(img.printStructure(oss, kpsNone, 0));
}

// Test: printStructure with kpsBasic on a valid blank PNG
TEST_F(PngImageTest_2175, PrintStructureKpsBasic_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), true);
    std::ostringstream oss;
    EXPECT_NO_THROW(img.printStructure(oss, kpsBasic, 0));
}

// Test: Creating PngImage with invalid/corrupt data and reading metadata should throw
TEST_F(PngImageTest_2175, ReadMetadataWithCorruptDataThrows_2175) {
    const byte corruptData[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
    auto memIo = std::make_unique<MemIo>(corruptData, sizeof(corruptData));
    PngImage img(std::move(memIo), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: io() returns a reference to the underlying IO
TEST_F(PngImageTest_2175, IoReturnsValidReference_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), true);
    const BasicIo& io = img.io();
    EXPECT_EQ(io.size(), 103u);
}

// Test: ICC profile is not defined by default
TEST_F(PngImageTest_2175, IccProfileNotDefinedByDefault_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), true);
    EXPECT_FALSE(img.iccProfileDefined());
}

// Test: writeXmpFromPacket defaults to false
TEST_F(PngImageTest_2175, WriteXmpFromPacketDefaultFalse_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), false);
    EXPECT_FALSE(img.writeXmpFromPacket());
}

// Test: setXmpPacket and clearXmpPacket
TEST_F(PngImageTest_2175, SetAndClearXmpPacket_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), false);
    img.setXmpPacket("<xmp>test</xmp>");
    EXPECT_EQ(img.xmpPacket(), "<xmp>test</xmp>");
    img.clearXmpPacket();
    EXPECT_EQ(img.xmpPacket(), "");
}

// Test: Round-trip write and read metadata
TEST_F(PngImageTest_2175, RoundTripWriteReadMetadata_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), true);
    img.readMetadata();
    img.setComment("round trip comment");
    img.writeMetadata();
    
    // Now re-read
    img.readMetadata();
    EXPECT_EQ(img.comment(), "round trip comment");
}

// Test: byteOrder defaults to invalidByteOrder
TEST_F(PngImageTest_2175, DefaultByteOrderIsInvalid_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), false);
    EXPECT_EQ(img.byteOrder(), invalidByteOrder);
}

// Test: nativePreviews is empty by default
TEST_F(PngImageTest_2175, NativePreviewsEmptyByDefault_2175) {
    auto memIo = std::make_unique<MemIo>();
    PngImage img(std::move(memIo), false);
    EXPECT_TRUE(img.nativePreviews().empty());
}
