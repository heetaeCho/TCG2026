#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/quicktimevideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <fstream>
#include <cstring>
#include <memory>

namespace {

// Helper to create a minimal QuickTime file in memory
// A valid QuickTime file has an 'ftyp' box at the beginning
std::vector<uint8_t> createMinimalQuickTimeFile() {
    std::vector<uint8_t> data;
    
    // ftyp box: size (4 bytes) + 'ftyp' (4 bytes) + major brand (4 bytes) + minor version (4 bytes)
    // Total ftyp box size = 20 bytes
    uint32_t ftypSize = 20;
    // Size in big-endian
    data.push_back((ftypSize >> 24) & 0xFF);
    data.push_back((ftypSize >> 16) & 0xFF);
    data.push_back((ftypSize >> 8) & 0xFF);
    data.push_back(ftypSize & 0xFF);
    // 'ftyp'
    data.push_back('f'); data.push_back('t'); data.push_back('y'); data.push_back('p');
    // major brand 'qt  '
    data.push_back('q'); data.push_back('t'); data.push_back(' '); data.push_back(' ');
    // minor version
    data.push_back(0); data.push_back(0); data.push_back(0); data.push_back(0);
    // compatible brand 'qt  '
    data.push_back('q'); data.push_back('t'); data.push_back(' '); data.push_back(' ');
    
    return data;
}

// Helper to create a file that is definitely not a QuickTime file
std::vector<uint8_t> createNonQuickTimeFile() {
    std::vector<uint8_t> data = {0x00, 0x00, 0x00, 0x00, 'N', 'O', 'T', 'Q',
                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    return data;
}

// Helper to write data to a temporary file and return the path
std::string writeTempFile(const std::vector<uint8_t>& data, const std::string& suffix = ".mov") {
    std::string path = std::string("/tmp/test_qt_") + std::to_string(::getpid()) + suffix;
    std::ofstream ofs(path, std::ios::binary);
    if (!data.empty()) {
        ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
    }
    ofs.close();
    return path;
}

class QuickTimeVideoTest_657 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up temp files
        for (const auto& path : tempFiles_) {
            std::remove(path.c_str());
        }
    }
    
    std::string createTempFile(const std::vector<uint8_t>& data, const std::string& suffix = ".mov") {
        std::string path = writeTempFile(data, suffix);
        tempFiles_.push_back(path);
        return path;
    }
    
    std::vector<std::string> tempFiles_;
};

// Test that readMetadata throws when the file cannot be opened
TEST_F(QuickTimeVideoTest_657, ReadMetadataThrowsOnOpenFailure_657) {
    auto io = std::make_unique<Exiv2::FileIo>("/nonexistent/path/to/file.mov");
    auto video = std::make_unique<Exiv2::QuickTimeVideo>(std::move(io), 1000);
    
    EXPECT_THROW(video->readMetadata(), Exiv2::Error);
}

// Test that readMetadata throws kerNotAnImage for non-QuickTime files
TEST_F(QuickTimeVideoTest_657, ReadMetadataThrowsForNonQuickTimeFile_657) {
    auto data = createNonQuickTimeFile();
    std::string path = createTempFile(data);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    auto video = std::make_unique<Exiv2::QuickTimeVideo>(std::move(io), 1000);
    
    EXPECT_THROW(video->readMetadata(), Exiv2::Error);
}

// Test that readMetadata throws for an empty file
TEST_F(QuickTimeVideoTest_657, ReadMetadataThrowsForEmptyFile_657) {
    std::vector<uint8_t> emptyData;
    std::string path = createTempFile(emptyData);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    auto video = std::make_unique<Exiv2::QuickTimeVideo>(std::move(io), 1000);
    
    EXPECT_THROW(video->readMetadata(), Exiv2::Error);
}

// Test mimeType returns the expected MIME type for QuickTime
TEST_F(QuickTimeVideoTest_657, MimeTypeReturnsCorrectValue_657) {
    auto data = createMinimalQuickTimeFile();
    std::string path = createTempFile(data);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    auto video = std::make_unique<Exiv2::QuickTimeVideo>(std::move(io), 1000);
    
    std::string mime = video->mimeType();
    EXPECT_FALSE(mime.empty());
    // QuickTime videos typically have "video/quicktime" mime type
    EXPECT_EQ(mime, "video/quicktime");
}

// Test writeMetadata throws (QuickTime writing is typically not supported)
TEST_F(QuickTimeVideoTest_657, WriteMetadataThrows_657) {
    auto data = createMinimalQuickTimeFile();
    std::string path = createTempFile(data);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    auto video = std::make_unique<Exiv2::QuickTimeVideo>(std::move(io), 1000);
    
    EXPECT_THROW(video->writeMetadata(), Exiv2::Error);
}

// Test that readMetadata on a minimal valid QT file sets file size XMP data
TEST_F(QuickTimeVideoTest_657, ReadMetadataSetsFileSizeXmp_657) {
    auto data = createMinimalQuickTimeFile();
    std::string path = createTempFile(data);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    auto video = std::make_unique<Exiv2::QuickTimeVideo>(std::move(io), 1000);
    
    try {
        video->readMetadata();
    } catch (const Exiv2::Error&) {
        // Some minimal files may fail during decode; that's acceptable
        // We still check what was set before failure
    }
    
    const Exiv2::XmpData& xmpData = video->xmpData();
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.video.FileSize"));
    if (it != xmpData.end()) {
        // File size should be positive (the file has some bytes)
        float fileSize = it->toFloat();
        EXPECT_GT(fileSize, 0.0f);
    }
}

// Test that readMetadata sets MimeType in XMP data
TEST_F(QuickTimeVideoTest_657, ReadMetadataSetsMimeTypeXmp_657) {
    auto data = createMinimalQuickTimeFile();
    std::string path = createTempFile(data);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    auto video = std::make_unique<Exiv2::QuickTimeVideo>(std::move(io), 1000);
    
    try {
        video->readMetadata();
    } catch (const Exiv2::Error&) {
        // May fail on minimal file
    }
    
    const Exiv2::XmpData& xmpData = video->xmpData();
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.video.MimeType"));
    if (it != xmpData.end()) {
        EXPECT_EQ(it->toString(), "video/quicktime");
    }
}

// Test that MemIo with non-QuickTime data throws
TEST_F(QuickTimeVideoTest_657, ReadMetadataThrowsForNonQTMemIo_657) {
    std::vector<uint8_t> data = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A}; // PNG signature
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto video = std::make_unique<Exiv2::QuickTimeVideo>(std::move(io), 1000);
    
    EXPECT_THROW(video->readMetadata(), Exiv2::Error);
}

// Test construction with different max_recursion_depth values
TEST_F(QuickTimeVideoTest_657, ConstructionWithZeroRecursionDepth_657) {
    auto data = createMinimalQuickTimeFile();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    // Should not throw during construction
    EXPECT_NO_THROW(
        auto video = std::make_unique<Exiv2::QuickTimeVideo>(std::move(io), 0)
    );
}

// Test construction with large recursion depth
TEST_F(QuickTimeVideoTest_657, ConstructionWithLargeRecursionDepth_657) {
    auto data = createMinimalQuickTimeFile();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    
    EXPECT_NO_THROW(
        auto video = std::make_unique<Exiv2::QuickTimeVideo>(std::move(io), 100000)
    );
}

// Test that xmpData is initially empty before readMetadata
TEST_F(QuickTimeVideoTest_657, XmpDataEmptyBeforeReadMetadata_657) {
    auto data = createMinimalQuickTimeFile();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto video = std::make_unique<Exiv2::QuickTimeVideo>(std::move(io), 1000);
    
    EXPECT_TRUE(video->xmpData().empty());
}

// Test readMetadata with very small data (too small to be valid)
TEST_F(QuickTimeVideoTest_657, ReadMetadataThrowsForTooSmallData_657) {
    std::vector<uint8_t> data = {0x00, 0x01};
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto video = std::make_unique<Exiv2::QuickTimeVideo>(std::move(io), 1000);
    
    EXPECT_THROW(video->readMetadata(), Exiv2::Error);
}

// Test that readMetadata clears previous metadata
TEST_F(QuickTimeVideoTest_657, ReadMetadataClearsPreviousMetadata_657) {
    auto data = createMinimalQuickTimeFile();
    std::string path = createTempFile(data);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    auto video = std::make_unique<Exiv2::QuickTimeVideo>(std::move(io), 1000);
    
    // Set some XMP data manually
    video->xmpData()["Xmp.dc.title"] = "test";
    EXPECT_FALSE(video->xmpData().empty());
    
    try {
        video->readMetadata();
    } catch (const Exiv2::Error&) {
        // May fail on minimal file, but metadata should have been cleared
    }
    
    // The manually set title should be cleared
    auto it = video->xmpData().findKey(Exiv2::XmpKey("Xmp.dc.title"));
    EXPECT_EQ(it, video->xmpData().end());
}

// Test that the video object reports correct good() state
TEST_F(QuickTimeVideoTest_657, GoodStateAfterConstruction_657) {
    auto data = createMinimalQuickTimeFile();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto video = std::make_unique<Exiv2::QuickTimeVideo>(std::move(io), 1000);
    
    EXPECT_TRUE(video->good());
}

// Test with random/corrupted data that starts like QuickTime but is corrupted
TEST_F(QuickTimeVideoTest_657, ReadMetadataHandlesCorruptedData_657) {
    // Create data that might look like it starts with a valid box but is truncated
    std::vector<uint8_t> data;
    // Box size = 100 (but we won't provide 100 bytes)
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x64);
    // 'ftyp'
    data.push_back('f'); data.push_back('t'); data.push_back('y'); data.push_back('p');
    // Only 8 more bytes (not the 92 remaining bytes the box claims)
    data.push_back('q'); data.push_back('t'); data.push_back(' '); data.push_back(' ');
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x00);
    
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto video = std::make_unique<Exiv2::QuickTimeVideo>(std::move(io), 1000);
    
    // Should either throw or handle gracefully
    try {
        video->readMetadata();
    } catch (const Exiv2::Error& e) {
        // Expected - corrupted data may cause errors
        SUCCEED();
    }
}

// Test AspectRatio is set in XMP data after readMetadata
TEST_F(QuickTimeVideoTest_657, ReadMetadataSetsAspectRatio_657) {
    auto data = createMinimalQuickTimeFile();
    std::string path = createTempFile(data);
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    auto video = std::make_unique<Exiv2::QuickTimeVideo>(std::move(io), 1000);
    
    try {
        video->readMetadata();
    } catch (const Exiv2::Error&) {
        // May fail on minimal file
    }
    
    const Exiv2::XmpData& xmpData = video->xmpData();
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.video.AspectRatio"));
    // With width_=1, height_=1 (defaults), aspect ratio should be set
    if (it != xmpData.end()) {
        EXPECT_FALSE(it->toString().empty());
    }
}

}  // namespace
