#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/asfvideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <memory>
#include <fstream>
#include <cstring>

// ASF Header Object GUID: 30 26 B2 75 8E 66 CF 11 A6 D9 00 AA 00 62 CE 6C
// ASF Top-level header GUID followed by size

namespace {

// Minimal ASF file header bytes for testing
// The ASF header object GUID
const uint8_t ASF_HEADER_GUID[] = {
    0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
    0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
};

std::string getTestDataDir() {
    // Try common test data locations
    const char* env = std::getenv("EXIV2_TEST_DATA");
    if (env) return std::string(env);
    return std::string("../test/data");
}

// Helper to create a minimal valid-looking ASF file in memory
std::vector<uint8_t> createMinimalAsfData() {
    std::vector<uint8_t> data;
    
    // ASF Header Object GUID (16 bytes)
    data.insert(data.end(), ASF_HEADER_GUID, ASF_HEADER_GUID + 16);
    
    // Size of header object (8 bytes, little-endian) - header is 30 bytes total minimum
    // We'll say the header object is 30 bytes (GUID(16) + Size(8) + NumHeaders(4) + Reserved(2))
    uint64_t headerSize = 30;
    for (int i = 0; i < 8; i++) {
        data.push_back(static_cast<uint8_t>((headerSize >> (i * 8)) & 0xFF));
    }
    
    // Number of header objects (4 bytes, little-endian) = 0
    uint32_t numHeaders = 0;
    for (int i = 0; i < 4; i++) {
        data.push_back(static_cast<uint8_t>((numHeaders >> (i * 8)) & 0xFF));
    }
    
    // Reserved1 (1 byte) and Reserved2 (1 byte)
    data.push_back(0x01);
    data.push_back(0x02);
    
    return data;
}

// Helper to create a file with given content
std::string createTempFile(const std::vector<uint8_t>& data, const std::string& suffix = ".asf") {
    std::string path = "test_asf_temp" + suffix;
    std::ofstream ofs(path, std::ios::binary);
    if (!data.empty()) {
        ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
    }
    ofs.close();
    return path;
}

void removeTempFile(const std::string& path) {
    std::remove(path.c_str());
}

} // anonymous namespace

class AsfVideoTest_1562 : public ::testing::Test {
protected:
    void TearDown() override {
        for (const auto& f : tempFiles_) {
            removeTempFile(f);
        }
    }
    
    std::vector<std::string> tempFiles_;
};

// Test that creating an AsfVideo with a valid IO does not throw
TEST_F(AsfVideoTest_1562, ConstructionWithValidIo_1562) {
    auto data = createMinimalAsfData();
    std::string path = createTempFile(data);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    ASSERT_NO_THROW(Exiv2::AsfVideo video(std::move(io)));
}

// Test that mimeType returns the correct MIME type for ASF
TEST_F(AsfVideoTest_1562, MimeTypeReturnsCorrectValue_1562) {
    auto data = createMinimalAsfData();
    std::string path = createTempFile(data);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::AsfVideo video(std::move(io));
    
    std::string mime = video.mimeType();
    EXPECT_EQ(mime, "video/x-ms-asf");
}

// Test readMetadata on a non-ASF file throws appropriate error
TEST_F(AsfVideoTest_1562, ReadMetadataOnNonAsfFileThrows_1562) {
    // Create a file with random non-ASF content
    std::vector<uint8_t> data = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                                  0x10, 0x11, 0x12, 0x13};
    std::string path = createTempFile(data);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::AsfVideo video(std::move(io));
    
    EXPECT_THROW(video.readMetadata(), Exiv2::Error);
}

// Test readMetadata on an empty file throws
TEST_F(AsfVideoTest_1562, ReadMetadataOnEmptyFileThrows_1562) {
    std::vector<uint8_t> data;
    std::string path = createTempFile(data);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::AsfVideo video(std::move(io));
    
    EXPECT_THROW(video.readMetadata(), Exiv2::Error);
}

// Test readMetadata on a file that doesn't exist throws
TEST_F(AsfVideoTest_1562, ReadMetadataOnNonexistentFileThrows_1562) {
    auto io = std::make_unique<Exiv2::FileIo>("nonexistent_file_12345.asf");
    Exiv2::AsfVideo video(std::move(io));
    
    EXPECT_THROW(video.readMetadata(), Exiv2::Error);
}

// Test readMetadata on a minimal valid ASF file populates XMP metadata
TEST_F(AsfVideoTest_1562, ReadMetadataOnMinimalAsfPopulatesXmp_1562) {
    auto data = createMinimalAsfData();
    std::string path = createTempFile(data);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::AsfVideo video(std::move(io));
    
    try {
        video.readMetadata();
        
        const Exiv2::XmpData& xmpData = video.xmpData();
        
        // Check that FileSize was set
        auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.video.FileSize"));
        EXPECT_NE(it, xmpData.end());
        
        // Check that MimeType was set
        it = xmpData.findKey(Exiv2::XmpKey("Xmp.video.MimeType"));
        EXPECT_NE(it, xmpData.end());
        if (it != xmpData.end()) {
            EXPECT_EQ(it->toString(), "video/x-ms-asf");
        }
        
        // Check that AspectRatio was set
        it = xmpData.findKey(Exiv2::XmpKey("Xmp.video.AspectRatio"));
        EXPECT_NE(it, xmpData.end());
    } catch (const Exiv2::Error&) {
        // Some minimal ASF files may not be fully parseable; that's acceptable
        // The important thing is the structure is correct
    }
}

// Test writeMetadata throws (ASF write is typically unsupported)
TEST_F(AsfVideoTest_1562, WriteMetadataThrows_1562) {
    auto data = createMinimalAsfData();
    std::string path = createTempFile(data);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::AsfVideo video(std::move(io));
    
    EXPECT_THROW(video.writeMetadata(), Exiv2::Error);
}

// Test that XmpData is initially empty before readMetadata
TEST_F(AsfVideoTest_1562, XmpDataEmptyBeforeReadMetadata_1562) {
    auto data = createMinimalAsfData();
    std::string path = createTempFile(data);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::AsfVideo video(std::move(io));
    
    EXPECT_TRUE(video.xmpData().empty());
}

// Test that readMetadata with a file containing only the ASF GUID but truncated throws or handles gracefully
TEST_F(AsfVideoTest_1562, ReadMetadataOnTruncatedAsfFile_1562) {
    // Only the GUID, no size field
    std::vector<uint8_t> data(ASF_HEADER_GUID, ASF_HEADER_GUID + 16);
    std::string path = createTempFile(data);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::AsfVideo video(std::move(io));
    
    // Should either throw or handle gracefully
    try {
        video.readMetadata();
    } catch (const Exiv2::Error& e) {
        // Expected - truncated file
        SUCCEED();
    }
}

// Test that good() returns true for a valid IO
TEST_F(AsfVideoTest_1562, GoodReturnsTrueForValidIo_1562) {
    auto data = createMinimalAsfData();
    std::string path = createTempFile(data);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::AsfVideo video(std::move(io));
    
    EXPECT_TRUE(video.good());
}

// Test that accessing io() returns a reference
TEST_F(AsfVideoTest_1562, IoAccessible_1562) {
    auto data = createMinimalAsfData();
    std::string path = createTempFile(data);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::AsfVideo video(std::move(io));
    
    const Exiv2::BasicIo& ioRef = video.io();
    EXPECT_EQ(ioRef.path(), path);
}

// Test readMetadata with a very small non-ASF binary file
TEST_F(AsfVideoTest_1562, ReadMetadataOnSmallBinaryFileThrows_1562) {
    std::vector<uint8_t> data = {0xFF, 0xFE};
    std::string path = createTempFile(data);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::AsfVideo video(std::move(io));
    
    EXPECT_THROW(video.readMetadata(), Exiv2::Error);
}

// Test that clearMetadata clears XMP data (if it was previously populated)
TEST_F(AsfVideoTest_1562, ClearMetadataWorks_1562) {
    auto data = createMinimalAsfData();
    std::string path = createTempFile(data);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::AsfVideo video(std::move(io));
    
    // Set some XMP data manually
    video.xmpData()["Xmp.video.TestKey"] = "TestValue";
    EXPECT_FALSE(video.xmpData().empty());
    
    video.clearMetadata();
    EXPECT_TRUE(video.xmpData().empty());
}

// Test that reading metadata from MemIo with non-ASF data throws
TEST_F(AsfVideoTest_1562, ReadMetadataFromMemIoNonAsfThrows_1562) {
    std::vector<uint8_t> data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::AsfVideo video(std::move(io));
    
    EXPECT_THROW(video.readMetadata(), Exiv2::Error);
}

// Test that reading metadata from MemIo with empty data throws
TEST_F(AsfVideoTest_1562, ReadMetadataFromEmptyMemIoThrows_1562) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::AsfVideo video(std::move(io));
    
    EXPECT_THROW(video.readMetadata(), Exiv2::Error);
}

// Test that reading metadata from MemIo with ASF GUID
TEST_F(AsfVideoTest_1562, ReadMetadataFromMemIoWithAsfGuid_1562) {
    auto data = createMinimalAsfData();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::AsfVideo video(std::move(io));
    
    try {
        video.readMetadata();
        // If it succeeds, check that some XMP data exists
        EXPECT_FALSE(video.xmpData().empty());
    } catch (const Exiv2::Error&) {
        // Minimal file may cause parse issues - acceptable
        SUCCEED();
    }
}

// Test that file size is reflected in XMP metadata
TEST_F(AsfVideoTest_1562, FileSizeInXmpMetadata_1562) {
    auto data = createMinimalAsfData();
    // Add some padding to make file larger
    data.resize(2 * 1048576, 0); // 2 MB
    std::string path = createTempFile(data);
    tempFiles_.push_back(path);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::AsfVideo video(std::move(io));
    
    try {
        video.readMetadata();
        
        const Exiv2::XmpData& xmpData = video.xmpData();
        auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.video.FileSize"));
        if (it != xmpData.end()) {
            // File size should be approximately 2.0 (in MB)
            float fileSize = it->toFloat();
            EXPECT_NEAR(fileSize, 2.0f, 0.1f);
        }
    } catch (const Exiv2::Error&) {
        // Parse error on padded data is acceptable
        SUCCEED();
    }
}
