#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/orfimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>

#include <fstream>
#include <cstring>
#include <memory>
#include <sstream>

using namespace Exiv2;

// Helper to create a minimal ORF file header
// ORF files use TIFF-like structure with specific byte order marks
// Olympus ORF uses "IIRO" (little-endian with ORF magic) or similar patterns

class OrfImageTest_1551 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Create a temporary file with given content
    std::string createTempFile(const std::string& suffix, const std::vector<uint8_t>& data) {
        std::string filename = "test_orf_" + suffix + ".orf";
        std::ofstream ofs(filename, std::ios::binary);
        if (!data.empty()) {
            ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
        }
        ofs.close();
        return filename;
    }

    void removeTempFile(const std::string& filename) {
        std::remove(filename.c_str());
    }
};

// Test: Creating OrfImage with a non-existent file path
TEST_F(OrfImageTest_1551, ReadMetadata_NonExistentFile_ThrowsError_1551) {
    auto io = std::make_unique<FileIo>("non_existent_file_1551.orf");
    OrfImage orfImage(std::move(io), false);

    EXPECT_THROW(orfImage.readMetadata(), Error);
}

// Test: Creating OrfImage with empty data throws error
TEST_F(OrfImageTest_1551, ReadMetadata_EmptyFile_ThrowsError_1551) {
    std::string filename = createTempFile("empty_1551", {});
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    EXPECT_THROW(orfImage.readMetadata(), Error);
    removeTempFile(filename);
}

// Test: Creating OrfImage with invalid/random data throws error (not an ORF)
TEST_F(OrfImageTest_1551, ReadMetadata_InvalidData_ThrowsNotAnImage_1551) {
    std::vector<uint8_t> invalidData = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    std::string filename = createTempFile("invalid_1551", invalidData);
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    EXPECT_THROW(orfImage.readMetadata(), Error);
    removeTempFile(filename);
}

// Test: Creating OrfImage with JPEG data throws error (not ORF)
TEST_F(OrfImageTest_1551, ReadMetadata_JpegData_ThrowsNotAnImage_1551) {
    std::vector<uint8_t> jpegData = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46};
    std::string filename = createTempFile("jpeg_1551", jpegData);
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    EXPECT_THROW(orfImage.readMetadata(), Error);
    removeTempFile(filename);
}

// Test: mimeType returns the expected MIME type for ORF
TEST_F(OrfImageTest_1551, MimeType_ReturnsCorrectType_1551) {
    std::string filename = createTempFile("mime_1551", {0x00});
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    std::string mime = orfImage.mimeType();
    EXPECT_EQ(mime, "image/x-olympus-orf");
    removeTempFile(filename);
}

// Test: setComment throws or is unsupported for ORF
TEST_F(OrfImageTest_1551, SetComment_ThrowsOrNoOp_1551) {
    std::string filename = createTempFile("comment_1551", {0x00});
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    // ORF typically doesn't support comments, should throw
    EXPECT_THROW(orfImage.setComment("test comment"), Error);
    removeTempFile(filename);
}

// Test: Creating OrfImage with create=true
TEST_F(OrfImageTest_1551, Constructor_CreateMode_1551) {
    std::string filename = createTempFile("create_1551", {});
    auto io = std::make_unique<FileIo>(filename);
    // Should not throw during construction
    EXPECT_NO_THROW(OrfImage orfImage(std::move(io), true));
    removeTempFile(filename);
}

// Test: good() returns false for an image that hasn't been read successfully
TEST_F(OrfImageTest_1551, Good_BeforeReadMetadata_1551) {
    std::string filename = createTempFile("good_1551", {0x00});
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    // Before reading metadata, good() should still be valid based on IO
    bool result = orfImage.good();
    // Just verify it doesn't crash - the actual value depends on IO state
    (void)result;
    removeTempFile(filename);
}

// Test: ReadMetadata with truncated TIFF-like header that looks partially like ORF
TEST_F(OrfImageTest_1551, ReadMetadata_TruncatedOrfHeader_ThrowsError_1551) {
    // ORF uses "IIRO" (0x4949 0x524F) for little-endian ORF
    // or "MMOR" for big-endian - provide truncated version
    std::vector<uint8_t> truncatedData = {0x49, 0x49, 0x52, 0x4F};
    std::string filename = createTempFile("truncated_1551", truncatedData);
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    EXPECT_THROW(orfImage.readMetadata(), Error);
    removeTempFile(filename);
}

// Test: ReadMetadata with data that has ORF magic but corrupted IFD offset
TEST_F(OrfImageTest_1551, ReadMetadata_CorruptedIfdOffset_ThrowsError_1551) {
    // ORF little-endian header: 49 49 52 4F followed by IFD offset
    std::vector<uint8_t> corruptData = {
        0x49, 0x49, 0x52, 0x4F,  // ORF magic (little-endian)
        0xFF, 0xFF, 0xFF, 0xFF   // Invalid IFD offset
    };
    std::string filename = createTempFile("corrupt_ifd_1551", corruptData);
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    EXPECT_THROW(orfImage.readMetadata(), Error);
    removeTempFile(filename);
}

// Test: exifData() returns reference (accessible before readMetadata)
TEST_F(OrfImageTest_1551, ExifData_AccessBeforeRead_1551) {
    std::string filename = createTempFile("exif_1551", {0x00});
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    ExifData& exif = orfImage.exifData();
    EXPECT_TRUE(exif.empty());
    removeTempFile(filename);
}

// Test: iptcData() returns reference (accessible before readMetadata)
TEST_F(OrfImageTest_1551, IptcData_AccessBeforeRead_1551) {
    std::string filename = createTempFile("iptc_1551", {0x00});
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    IptcData& iptc = orfImage.iptcData();
    EXPECT_TRUE(iptc.empty());
    removeTempFile(filename);
}

// Test: xmpData() returns reference (accessible before readMetadata)
TEST_F(OrfImageTest_1551, XmpData_AccessBeforeRead_1551) {
    std::string filename = createTempFile("xmp_1551", {0x00});
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    XmpData& xmp = orfImage.xmpData();
    EXPECT_TRUE(xmp.empty());
    removeTempFile(filename);
}

// Test: pixelWidth returns 0 before reading metadata
TEST_F(OrfImageTest_1551, PixelWidth_BeforeRead_ReturnsZero_1551) {
    std::string filename = createTempFile("pw_1551", {0x00});
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    EXPECT_EQ(orfImage.pixelWidth(), 0u);
    removeTempFile(filename);
}

// Test: pixelHeight returns 0 before reading metadata
TEST_F(OrfImageTest_1551, PixelHeight_BeforeRead_ReturnsZero_1551) {
    std::string filename = createTempFile("ph_1551", {0x00});
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    EXPECT_EQ(orfImage.pixelHeight(), 0u);
    removeTempFile(filename);
}

// Test: ReadMetadata with PNG data (definitely not ORF)
TEST_F(OrfImageTest_1551, ReadMetadata_PngData_ThrowsNotAnImage_1551) {
    std::vector<uint8_t> pngData = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    std::string filename = createTempFile("png_1551", pngData);
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    EXPECT_THROW(orfImage.readMetadata(), Error);
    removeTempFile(filename);
}

// Test: ReadMetadata with regular TIFF data (not ORF - different magic number)
TEST_F(OrfImageTest_1551, ReadMetadata_RegularTiff_ThrowsNotAnImage_1551) {
    // Regular TIFF LE: 49 49 2A 00 (standard TIFF, not ORF which uses 52 4F)
    std::vector<uint8_t> tiffData = {
        0x49, 0x49, 0x2A, 0x00,  // Standard TIFF little-endian
        0x08, 0x00, 0x00, 0x00,  // IFD offset
        0x00, 0x00               // 0 entries
    };
    std::string filename = createTempFile("tiff_1551", tiffData);
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    // This may or may not throw depending on whether regular TIFF passes ORF check
    // ORF has a different magic (0x4F52 instead of 0x002A), so it should throw
    EXPECT_THROW(orfImage.readMetadata(), Error);
    removeTempFile(filename);
}

// Test: MemIo based OrfImage with empty data
TEST_F(OrfImageTest_1551, ReadMetadata_MemIoEmpty_ThrowsError_1551) {
    auto io = std::make_unique<MemIo>();
    OrfImage orfImage(std::move(io), false);

    EXPECT_THROW(orfImage.readMetadata(), Error);
}

// Test: MemIo based OrfImage with small random data
TEST_F(OrfImageTest_1551, ReadMetadata_MemIoRandomData_ThrowsError_1551) {
    const uint8_t data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    auto io = std::make_unique<MemIo>(data, sizeof(data));
    OrfImage orfImage(std::move(io), false);

    EXPECT_THROW(orfImage.readMetadata(), Error);
}

// Test: writeMetadata on invalid file throws
TEST_F(OrfImageTest_1551, WriteMetadata_InvalidFile_ThrowsError_1551) {
    std::vector<uint8_t> invalidData = {0x00, 0x01, 0x02, 0x03};
    std::string filename = createTempFile("write_1551", invalidData);
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    EXPECT_THROW(orfImage.writeMetadata(), Error);
    removeTempFile(filename);
}

// Test: clearMetadata works without crash
TEST_F(OrfImageTest_1551, ClearMetadata_NoThrow_1551) {
    std::string filename = createTempFile("clear_1551", {0x00});
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    EXPECT_NO_THROW(orfImage.clearMetadata());
    EXPECT_TRUE(orfImage.exifData().empty());
    EXPECT_TRUE(orfImage.iptcData().empty());
    EXPECT_TRUE(orfImage.xmpData().empty());
    removeTempFile(filename);
}

// Test: io() returns reference to underlying IO
TEST_F(OrfImageTest_1551, IoAccess_ReturnsValidReference_1551) {
    std::string filename = createTempFile("io_1551", {0x00});
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    const BasicIo& ioRef = orfImage.io();
    EXPECT_EQ(ioRef.path(), filename);
    removeTempFile(filename);
}

// Test: Single byte file is not a valid ORF
TEST_F(OrfImageTest_1551, ReadMetadata_SingleByte_ThrowsError_1551) {
    std::vector<uint8_t> singleByte = {0x49};
    std::string filename = createTempFile("single_1551", singleByte);
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    EXPECT_THROW(orfImage.readMetadata(), Error);
    removeTempFile(filename);
}

// Test: Two bytes file is not a valid ORF
TEST_F(OrfImageTest_1551, ReadMetadata_TwoBytes_ThrowsError_1551) {
    std::vector<uint8_t> twoBytes = {0x49, 0x49};
    std::string filename = createTempFile("two_1551", twoBytes);
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    EXPECT_THROW(orfImage.readMetadata(), Error);
    removeTempFile(filename);
}

// Test: printStructure does not throw for basic usage (output to a stream)
TEST_F(OrfImageTest_1551, PrintStructure_InvalidFile_1551) {
    std::vector<uint8_t> invalidData = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    std::string filename = createTempFile("print_1551", invalidData);
    auto io = std::make_unique<FileIo>(filename);
    OrfImage orfImage(std::move(io), false);

    std::ostringstream oss;
    // printStructure on invalid data may throw
    EXPECT_THROW(orfImage.printStructure(oss, kpsNone, 0), Error);
    removeTempFile(filename);
}
