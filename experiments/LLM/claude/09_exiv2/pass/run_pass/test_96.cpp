#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/matroskavideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>

#include <fstream>
#include <cstring>
#include <memory>

namespace {

// Helper to create a minimal valid MKV file in memory
// MKV/WebM files start with EBML header: 0x1A 0x45 0xDF 0xA3
std::vector<uint8_t> createMinimalMkvData() {
    // EBML Header element ID: 0x1A45DFA3
    // Followed by size and minimal content
    // This is a very minimal EBML header
    std::vector<uint8_t> data = {
        0x1A, 0x45, 0xDF, 0xA3,  // EBML element ID
        0x93,                      // Size = 19 bytes (VINT encoding, 1 byte)
        // EBMLVersion
        0x42, 0x86, 0x81, 0x01,
        // EBMLReadVersion
        0x42, 0xF7, 0x81, 0x01,
        // EBMLMaxIDLength
        0x42, 0xF2, 0x81, 0x04,
        // EBMLMaxSizeLength
        0x42, 0xF3, 0x81, 0x08,
        // DocType "matroska"
        0x42, 0x82, 0x88, 0x6D, 0x61, 0x74, 0x72, 0x6F, 0x73, 0x6B, 0x61,
        // Padding/end - just enough to not crash
    };
    // Add a Segment element (0x18538067) with size 0 to terminate
    data.push_back(0x18);
    data.push_back(0x53);
    data.push_back(0x80);
    data.push_back(0x67);
    data.push_back(0x01);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);

    return data;
}

// Create data that is definitely not an MKV file
std::vector<uint8_t> createNonMkvData() {
    std::vector<uint8_t> data = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08
    };
    return data;
}

// Write data to a temporary file and return the path
std::string writeTempFile(const std::vector<uint8_t>& data, const std::string& suffix) {
    std::string path = std::string("test_matroska_") + suffix + ".mkv";
    std::ofstream ofs(path, std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
    ofs.close();
    return path;
}

void removeTempFile(const std::string& path) {
    std::remove(path.c_str());
}

} // anonymous namespace

class MatroskaVideoTest_96 : public ::testing::Test {
protected:
    void TearDown() override {
        for (const auto& f : tempFiles_) {
            removeTempFile(f);
        }
    }

    std::string createTempFile(const std::vector<uint8_t>& data, const std::string& suffix) {
        std::string path = writeTempFile(data, suffix);
        tempFiles_.push_back(path);
        return path;
    }

    std::vector<std::string> tempFiles_;
};

// Test that mimeType returns the expected MIME type for Matroska video
TEST_F(MatroskaVideoTest_96, MimeType_96) {
    auto data = createMinimalMkvData();
    std::string path = createTempFile(data, "mimetype");

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::MatroskaVideo mkv(std::move(io));

    std::string mime = mkv.mimeType();
    EXPECT_EQ(mime, "video/matroska");
}

// Test readMetadata on a non-MKV file throws kerNotAnImage
TEST_F(MatroskaVideoTest_96, ReadMetadataOnNonMkvThrows_96) {
    auto data = createNonMkvData();
    std::string path = createTempFile(data, "nonmkv");

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::MatroskaVideo mkv(std::move(io));

    EXPECT_THROW(mkv.readMetadata(), Exiv2::Error);
}

// Test readMetadata on a file that doesn't exist throws kerDataSourceOpenFailed
TEST_F(MatroskaVideoTest_96, ReadMetadataOnNonexistentFileThrows_96) {
    auto io = std::make_unique<Exiv2::FileIo>("nonexistent_file_for_test_96.mkv");
    Exiv2::MatroskaVideo mkv(std::move(io));

    EXPECT_THROW(mkv.readMetadata(), Exiv2::Error);
}

// Test readMetadata on empty data throws an error
TEST_F(MatroskaVideoTest_96, ReadMetadataOnEmptyFileThrows_96) {
    std::vector<uint8_t> emptyData;
    std::string path = createTempFile(emptyData, "empty");

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::MatroskaVideo mkv(std::move(io));

    EXPECT_THROW(mkv.readMetadata(), Exiv2::Error);
}

// Test that writeMetadata throws since MKV writing is not supported
TEST_F(MatroskaVideoTest_96, WriteMetadataThrows_96) {
    auto data = createMinimalMkvData();
    std::string path = createTempFile(data, "writemeta");

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::MatroskaVideo mkv(std::move(io));

    EXPECT_THROW(mkv.writeMetadata(), Exiv2::Error);
}

// Test using MemIo with non-MKV data throws
TEST_F(MatroskaVideoTest_96, ReadMetadataMemIoNonMkvThrows_96) {
    auto data = createNonMkvData();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::MatroskaVideo mkv(std::move(io));

    EXPECT_THROW(mkv.readMetadata(), Exiv2::Error);
}

// Test using MemIo with empty data throws
TEST_F(MatroskaVideoTest_96, ReadMetadataMemIoEmptyThrows_96) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::MatroskaVideo mkv(std::move(io));

    EXPECT_THROW(mkv.readMetadata(), Exiv2::Error);
}

// Test that readMetadata on data with only EBML magic but truncated throws or handles gracefully
TEST_F(MatroskaVideoTest_96, ReadMetadataTruncatedEbmlHeader_96) {
    // Just the EBML ID and nothing else - should fail
    std::vector<uint8_t> truncated = {0x1A, 0x45, 0xDF, 0xA3};
    std::string path = createTempFile(truncated, "truncated");

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::MatroskaVideo mkv(std::move(io));

    // Should throw some kind of error due to insufficient data
    EXPECT_THROW(mkv.readMetadata(), Exiv2::Error);
}

// Test that XMP data is accessible after construction (initially empty)
TEST_F(MatroskaVideoTest_96, XmpDataInitiallyEmpty_96) {
    auto data = createMinimalMkvData();
    std::string path = createTempFile(data, "xmpempty");

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::MatroskaVideo mkv(std::move(io));

    // Before readMetadata, xmpData should be empty
    EXPECT_TRUE(mkv.xmpData().empty());
}

// Test that good() returns true for a valid IO
TEST_F(MatroskaVideoTest_96, GoodReturnsTrueForValidIo_96) {
    auto data = createMinimalMkvData();
    std::string path = createTempFile(data, "good");

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::MatroskaVideo mkv(std::move(io));

    EXPECT_TRUE(mkv.good());
}

// Test with random/garbage data that starts with EBML magic but has corrupt content
TEST_F(MatroskaVideoTest_96, ReadMetadataCorruptEbmlContent_96) {
    std::vector<uint8_t> corrupt = {
        0x1A, 0x45, 0xDF, 0xA3,  // EBML element ID
        0x84,                      // Size = 4 bytes
        0xFF, 0xFF, 0xFF, 0xFF    // Garbage content
    };
    std::string path = createTempFile(corrupt, "corrupt");

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::MatroskaVideo mkv(std::move(io));

    // Corrupt data should cause an error
    EXPECT_THROW(mkv.readMetadata(), Exiv2::Error);
}

// Test with single byte file
TEST_F(MatroskaVideoTest_96, ReadMetadataSingleByteThrows_96) {
    std::vector<uint8_t> singleByte = {0x1A};
    std::string path = createTempFile(singleByte, "singlebyte");

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::MatroskaVideo mkv(std::move(io));

    EXPECT_THROW(mkv.readMetadata(), Exiv2::Error);
}

// Test that the image type is mkv
TEST_F(MatroskaVideoTest_96, ImageTypeIsMkv_96) {
    auto data = createMinimalMkvData();
    std::string path = createTempFile(data, "imgtype");

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::MatroskaVideo mkv(std::move(io));

    EXPECT_EQ(mkv.imageType(), Exiv2::ImageType::mkv);
}

// Test that MemIo with proper MKV-like header but WebM doctype triggers appropriate behavior
TEST_F(MatroskaVideoTest_96, ReadMetadataWebmDocType_96) {
    // EBML header with "webm" doctype
    std::vector<uint8_t> webm = {
        0x1A, 0x45, 0xDF, 0xA3,  // EBML element ID
        0x8B,                      // Size = 11 bytes
        // EBMLVersion
        0x42, 0x86, 0x81, 0x01,
        // DocType "webm"
        0x42, 0x82, 0x84, 0x77, 0x65, 0x62, 0x6D,
    };
    // This is very minimal and likely to fail during parsing, but let's verify it doesn't crash unexpectedly
    auto io = std::make_unique<Exiv2::MemIo>(webm.data(), webm.size());
    Exiv2::MatroskaVideo mkv(std::move(io));

    // May throw due to incomplete data
    EXPECT_THROW(mkv.readMetadata(), Exiv2::Error);
}

// Test clearMetadata works
TEST_F(MatroskaVideoTest_96, ClearMetadata_96) {
    auto data = createMinimalMkvData();
    std::string path = createTempFile(data, "clearmeta");

    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::MatroskaVideo mkv(std::move(io));

    mkv.clearMetadata();
    EXPECT_TRUE(mkv.xmpData().empty());
    EXPECT_TRUE(mkv.exifData().empty());
    EXPECT_TRUE(mkv.iptcData().empty());
}
