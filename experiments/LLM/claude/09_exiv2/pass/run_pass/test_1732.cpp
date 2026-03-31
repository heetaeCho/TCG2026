#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/tiffimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/error.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>

#include <fstream>
#include <cstring>
#include <memory>
#include <sstream>

using namespace Exiv2;

// Helper to create a minimal valid TIFF file in memory
static std::vector<byte> createMinimalTiff(ByteOrder bo = littleEndian) {
    std::vector<byte> data;
    
    if (bo == littleEndian) {
        // Byte order: II (little endian)
        data.push_back('I');
        data.push_back('I');
        // Magic number 42
        data.push_back(0x2A);
        data.push_back(0x00);
        // Offset to first IFD (8)
        data.push_back(0x08);
        data.push_back(0x00);
        data.push_back(0x00);
        data.push_back(0x00);
        // IFD with 0 entries
        data.push_back(0x00);
        data.push_back(0x00);
        // Next IFD offset = 0 (no more IFDs)
        data.push_back(0x00);
        data.push_back(0x00);
        data.push_back(0x00);
        data.push_back(0x00);
    } else {
        // Byte order: MM (big endian)
        data.push_back('M');
        data.push_back('M');
        // Magic number 42
        data.push_back(0x00);
        data.push_back(0x2A);
        // Offset to first IFD (8)
        data.push_back(0x00);
        data.push_back(0x00);
        data.push_back(0x00);
        data.push_back(0x08);
        // IFD with 0 entries
        data.push_back(0x00);
        data.push_back(0x00);
        // Next IFD offset = 0
        data.push_back(0x00);
        data.push_back(0x00);
        data.push_back(0x00);
        data.push_back(0x00);
    }
    
    return data;
}

// Helper to write data to a temp file and return the path
static std::string writeTempFile(const std::vector<byte>& data, const std::string& suffix = ".tif") {
    std::string path = std::tmpnam(nullptr) + suffix;
    std::ofstream ofs(path, std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
    ofs.close();
    return path;
}

class TiffImageTest_1732 : public ::testing::Test {
protected:
    void TearDown() override {
        for (const auto& f : tempFiles_) {
            std::remove(f.c_str());
        }
    }
    
    std::vector<std::string> tempFiles_;
    
    std::string createTempTiffFile(ByteOrder bo = littleEndian) {
        auto data = createMinimalTiff(bo);
        std::string path = writeTempFile(data);
        tempFiles_.push_back(path);
        return path;
    }
};

// Test that TiffImage can be created with a valid file
TEST_F(TiffImageTest_1732, Construction_1732) {
    auto data = createMinimalTiff();
    std::string path = writeTempFile(data);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<FileIo>(path);
    ASSERT_NO_THROW(TiffImage img(std::move(io), false));
}

// Test mimeType returns expected TIFF MIME type
TEST_F(TiffImageTest_1732, MimeType_1732) {
    auto data = createMinimalTiff();
    std::string path = writeTempFile(data);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    std::string mime = img.mimeType();
    EXPECT_EQ(mime, "image/tiff");
}

// Test readMetadata on a valid minimal TIFF file (little endian)
TEST_F(TiffImageTest_1732, ReadMetadataValidTiffLE_1732) {
    std::string path = createTempTiffFile(littleEndian);
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    ASSERT_NO_THROW(img.readMetadata());
}

// Test readMetadata on a valid minimal TIFF file (big endian)
TEST_F(TiffImageTest_1732, ReadMetadataValidTiffBE_1732) {
    std::string path = createTempTiffFile(bigEndian);
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    ASSERT_NO_THROW(img.readMetadata());
}

// Test readMetadata on a nonexistent file throws error
TEST_F(TiffImageTest_1732, ReadMetadataNonexistentFile_1732) {
    std::string path = "/nonexistent/path/to/file.tif";
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test readMetadata on an empty file throws error
TEST_F(TiffImageTest_1732, ReadMetadataEmptyFile_1732) {
    std::vector<byte> emptyData;
    std::string path = writeTempFile(emptyData);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test readMetadata on invalid (non-TIFF) data throws error
TEST_F(TiffImageTest_1732, ReadMetadataInvalidData_1732) {
    std::vector<byte> junkData = {'J', 'U', 'N', 'K', 'D', 'A', 'T', 'A'};
    std::string path = writeTempFile(junkData);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test that setComment throws or is unsupported for TIFF
TEST_F(TiffImageTest_1732, SetCommentUnsupported_1732) {
    std::string path = createTempTiffFile();
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    // TIFF does not support comments; setComment should throw
    EXPECT_THROW(img.setComment("test comment"), Error);
}

// Test that after readMetadata, exifData is accessible
TEST_F(TiffImageTest_1732, ExifDataAccessibleAfterRead_1732) {
    std::string path = createTempTiffFile();
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    ASSERT_NO_THROW(img.readMetadata());
    
    ExifData& exif = img.exifData();
    // Minimal TIFF may have no EXIF entries or very few
    // Just check it doesn't crash
    EXPECT_GE(exif.count(), 0u);
}

// Test that good() returns true after successful construction with valid file
TEST_F(TiffImageTest_1732, GoodAfterConstruction_1732) {
    std::string path = createTempTiffFile();
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    EXPECT_TRUE(img.good());
}

// Test pixelWidth and pixelHeight default to 0 before metadata is read
TEST_F(TiffImageTest_1732, PixelDimensionsDefault_1732) {
    std::string path = createTempTiffFile();
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    // Before reading metadata, dimensions should be default (0)
    EXPECT_EQ(img.pixelWidth(), 0u);
    EXPECT_EQ(img.pixelHeight(), 0u);
}

// Test pixelWidth and pixelHeight after reading minimal TIFF
TEST_F(TiffImageTest_1732, PixelDimensionsAfterRead_1732) {
    std::string path = createTempTiffFile();
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    ASSERT_NO_THROW(img.readMetadata());
    
    // Minimal TIFF has no image dimensions tags, so dimensions should be 0
    EXPECT_EQ(img.pixelWidth(), 0u);
    EXPECT_EQ(img.pixelHeight(), 0u);
}

// Test imageType
TEST_F(TiffImageTest_1732, ImageType_1732) {
    std::string path = createTempTiffFile();
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    EXPECT_EQ(img.imageType(), ImageType::tiff);
}

// Test iccProfile is not defined on a minimal TIFF without ICC data
TEST_F(TiffImageTest_1732, IccProfileNotDefined_1732) {
    std::string path = createTempTiffFile();
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    ASSERT_NO_THROW(img.readMetadata());
    
    EXPECT_FALSE(img.iccProfileDefined());
}

// Test clearMetadata after reading
TEST_F(TiffImageTest_1732, ClearMetadata_1732) {
    std::string path = createTempTiffFile();
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    ASSERT_NO_THROW(img.readMetadata());
    
    img.clearMetadata();
    EXPECT_TRUE(img.exifData().empty());
    EXPECT_TRUE(img.iptcData().empty());
    EXPECT_TRUE(img.xmpData().empty());
}

// Test readMetadata with truncated TIFF header (only byte order marker, no magic)
TEST_F(TiffImageTest_1732, ReadMetadataTruncatedHeader_1732) {
    std::vector<byte> truncated = {'I', 'I'}; // Only byte order, no magic number
    std::string path = writeTempFile(truncated);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test readMetadata with wrong magic number
TEST_F(TiffImageTest_1732, ReadMetadataWrongMagic_1732) {
    std::vector<byte> wrongMagic = {'I', 'I', 0x00, 0x00, 0x08, 0x00, 0x00, 0x00};
    std::string path = writeTempFile(wrongMagic);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test using MemIo with valid TIFF data
TEST_F(TiffImageTest_1732, ReadMetadataFromMemIo_1732) {
    auto data = createMinimalTiff(littleEndian);
    
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    TiffImage img(std::move(io), false);
    
    ASSERT_NO_THROW(img.readMetadata());
}

// Test using MemIo with empty data
TEST_F(TiffImageTest_1732, ReadMetadataFromEmptyMemIo_1732) {
    auto io = std::make_unique<MemIo>();
    TiffImage img(std::move(io), false);
    
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test using MemIo with garbage data
TEST_F(TiffImageTest_1732, ReadMetadataFromGarbageMemIo_1732) {
    std::vector<byte> garbage(100, 0xFF);
    
    auto io = std::make_unique<MemIo>(garbage.data(), garbage.size());
    TiffImage img(std::move(io), false);
    
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test byteOrder after reading
TEST_F(TiffImageTest_1732, ByteOrderAfterReadLE_1732) {
    auto data = createMinimalTiff(littleEndian);
    std::string path = writeTempFile(data);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    ASSERT_NO_THROW(img.readMetadata());
    EXPECT_EQ(img.byteOrder(), littleEndian);
}

// Test byteOrder after reading big endian TIFF
TEST_F(TiffImageTest_1732, ByteOrderAfterReadBE_1732) {
    auto data = createMinimalTiff(bigEndian);
    std::string path = writeTempFile(data);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    ASSERT_NO_THROW(img.readMetadata());
    EXPECT_EQ(img.byteOrder(), bigEndian);
}

// Test that iptcData and xmpData are accessible after readMetadata
TEST_F(TiffImageTest_1732, IptcAndXmpDataAccessible_1732) {
    std::string path = createTempTiffFile();
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    ASSERT_NO_THROW(img.readMetadata());
    
    IptcData& iptc = img.iptcData();
    XmpData& xmp = img.xmpData();
    
    // Minimal TIFF has no IPTC or XMP
    EXPECT_TRUE(iptc.empty());
    EXPECT_TRUE(xmp.empty());
}

// Test reading metadata twice does not crash
TEST_F(TiffImageTest_1732, ReadMetadataTwice_1732) {
    std::string path = createTempTiffFile();
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    ASSERT_NO_THROW(img.readMetadata());
    ASSERT_NO_THROW(img.readMetadata());
}

// Test printStructure does not crash
TEST_F(TiffImageTest_1732, PrintStructure_1732) {
    std::string path = createTempTiffFile();
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    std::ostringstream oss;
    // PrintStructureOption::kpsNone should be safe
    ASSERT_NO_THROW(img.printStructure(oss, kpsNone, 0));
}

// Test supportsMetadata
TEST_F(TiffImageTest_1732, SupportsMetadata_1732) {
    std::string path = createTempTiffFile();
    
    auto io = std::make_unique<FileIo>(path);
    TiffImage img(std::move(io), false);
    
    EXPECT_TRUE(img.supportsMetadata(mdExif));
    EXPECT_TRUE(img.supportsMetadata(mdIptc));
    EXPECT_TRUE(img.supportsMetadata(mdXmp));
}
