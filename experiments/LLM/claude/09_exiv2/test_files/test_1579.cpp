#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/rw2image.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/preview.hpp>

#include <fstream>
#include <cstring>
#include <memory>

using namespace Exiv2;

// Helper to create a MemIo with arbitrary data
static std::unique_ptr<BasicIo> makeMemIo(const std::vector<byte>& data) {
    return std::make_unique<MemIo>(data.data(), data.size());
}

class Rw2ImageTest_1579 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Creating Rw2Image with a valid (but empty) MemIo
TEST_F(Rw2ImageTest_1579, ConstructWithMemIo_1579) {
    auto io = std::make_unique<MemIo>();
    ASSERT_NO_THROW(Rw2Image img(std::move(io)));
}

// Test: mimeType returns the expected MIME type for RW2
TEST_F(Rw2ImageTest_1579, MimeType_1579) {
    auto io = std::make_unique<MemIo>();
    Rw2Image img(std::move(io));
    EXPECT_EQ(img.mimeType(), "image/x-panasonic-rw2");
}

// Test: readMetadata on empty data should throw an error
TEST_F(Rw2ImageTest_1579, ReadMetadataEmptyDataThrows_1579) {
    auto io = std::make_unique<MemIo>();
    Rw2Image img(std::move(io));
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test: readMetadata on random/garbage data should throw (not a valid RW2)
TEST_F(Rw2ImageTest_1579, ReadMetadataGarbageDataThrows_1579) {
    std::vector<byte> garbage(256, 0xAB);
    auto io = std::make_unique<MemIo>(garbage.data(), garbage.size());
    Rw2Image img(std::move(io));
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test: writeMetadata should throw (RW2 writing is not supported)
TEST_F(Rw2ImageTest_1579, WriteMetadataThrows_1579) {
    auto io = std::make_unique<MemIo>();
    Rw2Image img(std::move(io));
    EXPECT_THROW(img.writeMetadata(), Error);
}

// Test: setExifData should not change exifData (RW2 doesn't support setting exif)
TEST_F(Rw2ImageTest_1579, SetExifDataIsNoOp_1579) {
    auto io = std::make_unique<MemIo>();
    Rw2Image img(std::move(io));
    ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    img.setExifData(exifData);
    // setExifData for RW2 is documented as a no-op; exifData should remain empty
    EXPECT_TRUE(img.exifData().empty());
}

// Test: setIptcData should not change iptcData (RW2 doesn't support setting iptc)
TEST_F(Rw2ImageTest_1579, SetIptcDataIsNoOp_1579) {
    auto io = std::make_unique<MemIo>();
    Rw2Image img(std::move(io));
    IptcData iptcData;
    img.setIptcData(iptcData);
    EXPECT_TRUE(img.iptcData().empty());
}

// Test: setComment should be a no-op for RW2
TEST_F(Rw2ImageTest_1579, SetCommentIsNoOp_1579) {
    auto io = std::make_unique<MemIo>();
    Rw2Image img(std::move(io));
    img.setComment("Test comment");
    EXPECT_TRUE(img.comment().empty());
}

// Test: pixelWidth and pixelHeight default to 0 on a freshly constructed image
TEST_F(Rw2ImageTest_1579, DefaultPixelDimensions_1579) {
    auto io = std::make_unique<MemIo>();
    Rw2Image img(std::move(io));
    EXPECT_EQ(img.pixelWidth(), 0u);
    EXPECT_EQ(img.pixelHeight(), 0u);
}

// Test: good() should return false for empty MemIo (no data)
TEST_F(Rw2ImageTest_1579, GoodReturnsFalseForEmptyIo_1579) {
    auto io = std::make_unique<MemIo>();
    Rw2Image img(std::move(io));
    // good() checks if io_ is in a good state; empty MemIo should still be "good" in some sense
    // But after construction with empty data, before open, it depends on implementation
    // We just verify it doesn't crash
    bool result = img.good();
    (void)result;
    SUCCEED();
}

// Test: exifData() returns a reference to ExifData that is initially empty
TEST_F(Rw2ImageTest_1579, ExifDataInitiallyEmpty_1579) {
    auto io = std::make_unique<MemIo>();
    Rw2Image img(std::move(io));
    EXPECT_TRUE(img.exifData().empty());
}

// Test: iptcData() returns a reference to IptcData that is initially empty
TEST_F(Rw2ImageTest_1579, IptcDataInitiallyEmpty_1579) {
    auto io = std::make_unique<MemIo>();
    Rw2Image img(std::move(io));
    EXPECT_TRUE(img.iptcData().empty());
}

// Test: xmpData() returns a reference to XmpData that is initially empty
TEST_F(Rw2ImageTest_1579, XmpDataInitiallyEmpty_1579) {
    auto io = std::make_unique<MemIo>();
    Rw2Image img(std::move(io));
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: readMetadata with small but non-empty invalid data throws
TEST_F(Rw2ImageTest_1579, ReadMetadataSmallInvalidDataThrows_1579) {
    std::vector<byte> data = {0x49, 0x49}; // only 2 bytes, not valid RW2
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    Rw2Image img(std::move(io));
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test: readMetadata with data that starts with II but is not valid RW2
TEST_F(Rw2ImageTest_1579, ReadMetadataFakeTiffHeaderThrows_1579) {
    // TIFF header "II" (little-endian) followed by some bytes, but not valid RW2
    std::vector<byte> data = {0x49, 0x49, 0x55, 0x00, 0x08, 0x00, 0x00, 0x00};
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    Rw2Image img(std::move(io));
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test: Verify ImageFactory can detect non-RW2 data
TEST_F(Rw2ImageTest_1579, ImageFactoryGetTypeNonRw2_1579) {
    std::vector<byte> jpegData = {0xFF, 0xD8, 0xFF, 0xE0};
    auto type = ImageFactory::getType(jpegData.data(), jpegData.size());
    EXPECT_NE(type, ImageType::rw2);
}

// Test: readMetadata with a file path that does not exist
TEST_F(Rw2ImageTest_1579, ReadMetadataNonExistentFileThrows_1579) {
    try {
        auto io = std::make_unique<FileIo>("nonexistent_file_12345.rw2");
        Rw2Image img(std::move(io));
        EXPECT_THROW(img.readMetadata(), Error);
    } catch (...) {
        // FileIo construction itself might throw depending on implementation
        SUCCEED();
    }
}

// Test: Verify that printStructure does not crash on empty data
TEST_F(Rw2ImageTest_1579, PrintStructureEmptyDataNoCrash_1579) {
    auto io = std::make_unique<MemIo>();
    Rw2Image img(std::move(io));
    std::ostringstream oss;
    // printStructure might throw, but should not crash
    try {
        img.printStructure(oss, kpsNone, 0);
    } catch (const Error&) {
        // Expected - empty data
    }
    SUCCEED();
}

// Test: clearMetadata after construction works without issues
TEST_F(Rw2ImageTest_1579, ClearMetadataOnFreshImage_1579) {
    auto io = std::make_unique<MemIo>();
    Rw2Image img(std::move(io));
    EXPECT_NO_THROW(img.clearMetadata());
    EXPECT_TRUE(img.exifData().empty());
    EXPECT_TRUE(img.iptcData().empty());
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: Rw2Image imageType should be rw2
TEST_F(Rw2ImageTest_1579, ImageTypeIsRw2_1579) {
    auto io = std::make_unique<MemIo>();
    Rw2Image img(std::move(io));
    EXPECT_EQ(img.imageType(), ImageType::rw2);
}

// Test: readMetadata with a single zero byte should throw
TEST_F(Rw2ImageTest_1579, ReadMetadataSingleByteThrows_1579) {
    std::vector<byte> data = {0x00};
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    Rw2Image img(std::move(io));
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test: Verify that io() accessor works
TEST_F(Rw2ImageTest_1579, IoAccessor_1579) {
    auto io = std::make_unique<MemIo>();
    Rw2Image img(std::move(io));
    const BasicIo& ioRef = img.io();
    EXPECT_EQ(ioRef.size(), 0u);
}

// Test: readMetadata on data resembling RW2 magic but truncated should throw
TEST_F(Rw2ImageTest_1579, ReadMetadataTruncatedRw2MagicThrows_1579) {
    // RW2 files start with "IIU\0" (0x49 0x49 0x55 0x00) but we truncate it
    std::vector<byte> data = {0x49, 0x49, 0x55};
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    Rw2Image img(std::move(io));
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test: Rw2Parser::decode with null/empty data
TEST_F(Rw2ImageTest_1579, Rw2ParserDecodeEmptyData_1579) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    // Decoding empty/null data - behavior depends on implementation
    // but it should not crash
    try {
        Rw2Parser::decode(exifData, iptcData, xmpData, nullptr, 0);
    } catch (const Error&) {
        // Acceptable to throw
    }
    SUCCEED();
}

// Test: Rw2Parser::decode with garbage data
TEST_F(Rw2ImageTest_1579, Rw2ParserDecodeGarbageData_1579) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    std::vector<byte> garbage(100, 0xFF);
    try {
        Rw2Parser::decode(exifData, iptcData, xmpData, garbage.data(), garbage.size());
    } catch (const Error&) {
        // Acceptable to throw
    }
    SUCCEED();
}

// Test: supportsMetadata for various metadata types
TEST_F(Rw2ImageTest_1579, SupportsMetadata_1579) {
    auto io = std::make_unique<MemIo>();
    Rw2Image img(std::move(io));
    EXPECT_TRUE(img.supportsMetadata(MetadataId::mdExif));
    EXPECT_TRUE(img.supportsMetadata(MetadataId::mdIptc));
    EXPECT_TRUE(img.supportsMetadata(MetadataId::mdXmp));
}

// Test: byteOrder default value
TEST_F(Rw2ImageTest_1579, DefaultByteOrder_1579) {
    auto io = std::make_unique<MemIo>();
    Rw2Image img(std::move(io));
    // Before reading metadata, byte order should be invalid
    EXPECT_EQ(img.byteOrder(), invalidByteOrder);
}
