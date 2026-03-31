#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/cr2image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>
#include <memory>
#include <fstream>
#include <cstdio>
#include <string>

using namespace Exiv2;

// Helper to create a temporary file with given content
class TempFile {
public:
    TempFile(const std::string& name, const std::vector<uint8_t>& data) : filename_(name) {
        std::ofstream ofs(filename_, std::ios::binary);
        if (!data.empty()) {
            ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
        }
    }
    ~TempFile() {
        std::remove(filename_.c_str());
    }
    const std::string& path() const { return filename_; }
private:
    std::string filename_;
};

class Cr2ImageTest_1743 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test: Creating a Cr2Image with a valid (but non-CR2) file should succeed construction
TEST_F(Cr2ImageTest_1743, ConstructWithValidIo_1743) {
    std::vector<uint8_t> emptyData(100, 0);
    TempFile tmp("test_construct_1743.cr2", emptyData);
    auto io = std::make_unique<FileIo>(tmp.path());
    ASSERT_NO_THROW(Cr2Image img(std::move(io), false));
}

// Test: readMetadata on a non-existent file should throw
TEST_F(Cr2ImageTest_1743, ReadMetadataFileNotFound_1743) {
    auto io = std::make_unique<FileIo>("nonexistent_file_1743.cr2");
    Cr2Image img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test: readMetadata on an empty file should throw (not a valid CR2)
TEST_F(Cr2ImageTest_1743, ReadMetadataEmptyFile_1743) {
    std::vector<uint8_t> emptyData;
    TempFile tmp("test_empty_1743.cr2", emptyData);
    auto io = std::make_unique<FileIo>(tmp.path());
    Cr2Image img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test: readMetadata on a file with random garbage data should throw
TEST_F(Cr2ImageTest_1743, ReadMetadataGarbageData_1743) {
    std::vector<uint8_t> garbageData(1024, 0xAB);
    TempFile tmp("test_garbage_1743.cr2", garbageData);
    auto io = std::make_unique<FileIo>(tmp.path());
    Cr2Image img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test: readMetadata on a file with too-small data that looks nothing like CR2
TEST_F(Cr2ImageTest_1743, ReadMetadataTooSmallFile_1743) {
    std::vector<uint8_t> smallData = {0x00, 0x01, 0x02};
    TempFile tmp("test_small_1743.cr2", smallData);
    auto io = std::make_unique<FileIo>(tmp.path());
    Cr2Image img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test: mimeType returns the expected CR2 MIME type
TEST_F(Cr2ImageTest_1743, MimeTypeIsCr2_1743) {
    std::vector<uint8_t> dummyData(100, 0);
    TempFile tmp("test_mime_1743.cr2", dummyData);
    auto io = std::make_unique<FileIo>(tmp.path());
    Cr2Image img(std::move(io), false);
    EXPECT_EQ(img.mimeType(), "image/x-canon-cr2");
}

// Test: setComment should throw (CR2 does not support comments typically)
TEST_F(Cr2ImageTest_1743, SetCommentThrows_1743) {
    std::vector<uint8_t> dummyData(100, 0);
    TempFile tmp("test_comment_1743.cr2", dummyData);
    auto io = std::make_unique<FileIo>(tmp.path());
    Cr2Image img(std::move(io), false);
    EXPECT_THROW(img.setComment("test comment"), Error);
}

// Test: good() should be true after construction with existing file
TEST_F(Cr2ImageTest_1743, GoodAfterConstruction_1743) {
    std::vector<uint8_t> dummyData(100, 0);
    TempFile tmp("test_good_1743.cr2", dummyData);
    auto io = std::make_unique<FileIo>(tmp.path());
    Cr2Image img(std::move(io), false);
    EXPECT_TRUE(img.good());
}

// Test: good() should return false for a non-existent file
TEST_F(Cr2ImageTest_1743, GoodReturnsFalseForBadIo_1743) {
    auto io = std::make_unique<FileIo>("does_not_exist_1743.cr2");
    Cr2Image img(std::move(io), false);
    EXPECT_FALSE(img.good());
}

// Test: exifData() returns a reference (initially empty before readMetadata)
TEST_F(Cr2ImageTest_1743, ExifDataInitiallyEmpty_1743) {
    std::vector<uint8_t> dummyData(100, 0);
    TempFile tmp("test_exif_1743.cr2", dummyData);
    auto io = std::make_unique<FileIo>(tmp.path());
    Cr2Image img(std::move(io), false);
    EXPECT_TRUE(img.exifData().empty());
}

// Test: iptcData() returns a reference (initially empty)
TEST_F(Cr2ImageTest_1743, IptcDataInitiallyEmpty_1743) {
    std::vector<uint8_t> dummyData(100, 0);
    TempFile tmp("test_iptc_1743.cr2", dummyData);
    auto io = std::make_unique<FileIo>(tmp.path());
    Cr2Image img(std::move(io), false);
    EXPECT_TRUE(img.iptcData().empty());
}

// Test: xmpData() returns a reference (initially empty)
TEST_F(Cr2ImageTest_1743, XmpDataInitiallyEmpty_1743) {
    std::vector<uint8_t> dummyData(100, 0);
    TempFile tmp("test_xmp_1743.cr2", dummyData);
    auto io = std::make_unique<FileIo>(tmp.path());
    Cr2Image img(std::move(io), false);
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: pixelWidth and pixelHeight are 0 before reading metadata
TEST_F(Cr2ImageTest_1743, PixelDimensionsDefaultZero_1743) {
    std::vector<uint8_t> dummyData(100, 0);
    TempFile tmp("test_dims_1743.cr2", dummyData);
    auto io = std::make_unique<FileIo>(tmp.path());
    Cr2Image img(std::move(io), false);
    EXPECT_EQ(img.pixelWidth(), 0u);
    EXPECT_EQ(img.pixelHeight(), 0u);
}

// Test: readMetadata with data that has valid TIFF header but is not CR2 should throw
TEST_F(Cr2ImageTest_1743, ReadMetadataValidTiffButNotCr2_1743) {
    // A minimal TIFF little-endian header: "II" + 42 + offset 8
    std::vector<uint8_t> tiffData = {
        0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    TempFile tmp("test_tiff_not_cr2_1743.cr2", tiffData);
    auto io = std::make_unique<FileIo>(tmp.path());
    Cr2Image img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test: writeMetadata on an invalid/non-CR2 file should throw
TEST_F(Cr2ImageTest_1743, WriteMetadataOnInvalidFile_1743) {
    std::vector<uint8_t> dummyData(100, 0);
    TempFile tmp("test_write_1743.cr2", dummyData);
    auto io = std::make_unique<FileIo>(tmp.path());
    Cr2Image img(std::move(io), false);
    EXPECT_THROW(img.writeMetadata(), Error);
}

// Test: clearMetadata clears exif, iptc, and xmp data
TEST_F(Cr2ImageTest_1743, ClearMetadata_1743) {
    std::vector<uint8_t> dummyData(100, 0);
    TempFile tmp("test_clear_1743.cr2", dummyData);
    auto io = std::make_unique<FileIo>(tmp.path());
    Cr2Image img(std::move(io), false);
    img.clearMetadata();
    EXPECT_TRUE(img.exifData().empty());
    EXPECT_TRUE(img.iptcData().empty());
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: MemIo based construction with empty memory - readMetadata should throw
TEST_F(Cr2ImageTest_1743, ReadMetadataFromEmptyMemIo_1743) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test: MemIo with garbage data - readMetadata should throw
TEST_F(Cr2ImageTest_1743, ReadMetadataFromGarbageMemIo_1743) {
    std::vector<uint8_t> garbageData(512, 0xFF);
    auto io = std::make_unique<MemIo>(garbageData.data(), garbageData.size());
    Cr2Image img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test: byteOrder is invalidByteOrder before readMetadata
TEST_F(Cr2ImageTest_1743, ByteOrderInvalidBeforeRead_1743) {
    std::vector<uint8_t> dummyData(100, 0);
    TempFile tmp("test_bo_1743.cr2", dummyData);
    auto io = std::make_unique<FileIo>(tmp.path());
    Cr2Image img(std::move(io), false);
    EXPECT_EQ(img.byteOrder(), invalidByteOrder);
}

// Test: io() returns a reference to the underlying IO object
TEST_F(Cr2ImageTest_1743, IoAccessible_1743) {
    std::vector<uint8_t> dummyData(100, 0);
    TempFile tmp("test_io_1743.cr2", dummyData);
    auto io = std::make_unique<FileIo>(tmp.path());
    Cr2Image img(std::move(io), false);
    EXPECT_EQ(img.io().path(), tmp.path());
}

// Test: readMetadata with data that has a valid CR2 magic but truncated should throw
TEST_F(Cr2ImageTest_1743, ReadMetadataTruncatedCr2Header_1743) {
    // CR2 starts with "II" (little-endian), 0x002A (TIFF magic), then CR2 specific signature at offset 8
    // CR2 signature: "CR" at bytes 8-9, major version 2 at byte 10, minor version 0 at byte 11
    std::vector<uint8_t> truncatedCr2 = {
        0x49, 0x49, // "II" - little endian
        0x2A, 0x00, // TIFF magic 42
        0x10, 0x00, 0x00, 0x00, // IFD0 offset
        0x43, 0x52, // "CR"
        0x02, 0x00, // CR2 version 2.0
        0x00, 0x00, 0x00, 0x00 // Truncated - RAW IFD offset
    };
    TempFile tmp("test_truncated_cr2_1743.cr2", truncatedCr2);
    auto io = std::make_unique<FileIo>(tmp.path());
    Cr2Image img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test: Supports metadata check
TEST_F(Cr2ImageTest_1743, SupportsExifMetadata_1743) {
    std::vector<uint8_t> dummyData(100, 0);
    TempFile tmp("test_supports_1743.cr2", dummyData);
    auto io = std::make_unique<FileIo>(tmp.path());
    Cr2Image img(std::move(io), false);
    EXPECT_TRUE(img.supportsMetadata(MetadataId::mdExif));
    EXPECT_TRUE(img.supportsMetadata(MetadataId::mdIptc));
    EXPECT_TRUE(img.supportsMetadata(MetadataId::mdXmp));
}
