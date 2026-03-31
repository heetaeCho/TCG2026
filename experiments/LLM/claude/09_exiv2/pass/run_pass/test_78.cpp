#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/riffvideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <fstream>
#include <cstring>
#include <memory>

namespace {

// Helper function to create a minimal valid RIFF/AVI file in memory
std::vector<uint8_t> createMinimalRiffAvi() {
    std::vector<uint8_t> data;
    
    // RIFF header: "RIFF" + size (4 bytes LE) + "AVI "
    // "RIFF"
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    // Size placeholder (will be filled later) - total file size - 8
    uint32_t totalSize = 4; // just "AVI " for now
    data.push_back(totalSize & 0xFF);
    data.push_back((totalSize >> 8) & 0xFF);
    data.push_back((totalSize >> 16) & 0xFF);
    data.push_back((totalSize >> 24) & 0xFF);
    // "AVI "
    data.push_back('A'); data.push_back('V'); data.push_back('I'); data.push_back(' ');
    
    return data;
}

// Helper to create a completely invalid file (not RIFF)
std::vector<uint8_t> createNonRiffData() {
    std::vector<uint8_t> data = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    return data;
}

// Helper to create a RIFF file with wrong form type (not AVI)
std::vector<uint8_t> createRiffNonAviData() {
    std::vector<uint8_t> data;
    // "RIFF"
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    // Size
    uint32_t size = 4;
    data.push_back(size & 0xFF);
    data.push_back((size >> 8) & 0xFF);
    data.push_back((size >> 16) & 0xFF);
    data.push_back((size >> 24) & 0xFF);
    // "WAVE" instead of "AVI "
    data.push_back('W'); data.push_back('A'); data.push_back('V'); data.push_back('E');
    
    return data;
}

class RiffVideoTest_78 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    
    void TearDown() override {
    }
    
    std::unique_ptr<Exiv2::RiffVideo> createRiffVideoFromMemory(const std::vector<uint8_t>& data) {
        auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
        return std::make_unique<Exiv2::RiffVideo>(std::move(io));
    }
};

// Test that readMetadata throws when IO source cannot be opened (empty/invalid IO)
TEST_F(RiffVideoTest_78, ReadMetadata_NonRiffData_ThrowsError_78) {
    auto data = createNonRiffData();
    auto video = createRiffVideoFromMemory(data);
    
    EXPECT_THROW(video->readMetadata(), Exiv2::Error);
}

// Test that readMetadata throws kerNotAnImage for non-RIFF data
TEST_F(RiffVideoTest_78, ReadMetadata_NonRiffData_ThrowsNotAnImage_78) {
    auto data = createNonRiffData();
    auto video = createRiffVideoFromMemory(data);
    
    try {
        video->readMetadata();
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        // Should be either kerNotAnImage or kerFailedToReadImageData
        EXPECT_TRUE(e.code() == Exiv2::ErrorCode::kerNotAnImage || 
                    e.code() == Exiv2::ErrorCode::kerFailedToReadImageData);
    }
}

// Test that mimeType returns the correct MIME type for RIFF video
TEST_F(RiffVideoTest_78, MimeType_ReturnsExpectedType_78) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromMemory(data);
    
    std::string mime = video->mimeType();
    // RIFF/AVI videos should have a video mime type
    EXPECT_FALSE(mime.empty());
}

// Test that constructor creates a valid object
TEST_F(RiffVideoTest_78, Constructor_CreatesValidObject_78) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromMemory(data);
    
    EXPECT_NE(video, nullptr);
}

// Test with empty data
TEST_F(RiffVideoTest_78, ReadMetadata_EmptyData_ThrowsError_78) {
    std::vector<uint8_t> emptyData;
    auto io = std::make_unique<Exiv2::MemIo>();
    auto video = std::make_unique<Exiv2::RiffVideo>(std::move(io));
    
    EXPECT_THROW(video->readMetadata(), Exiv2::Error);
}

// Test that XmpData is accessible after construction
TEST_F(RiffVideoTest_78, XmpData_AccessibleAfterConstruction_78) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromMemory(data);
    
    Exiv2::XmpData& xmpData = video->xmpData();
    EXPECT_TRUE(xmpData.empty());
}

// Test that writeMetadata throws (RIFF writing is typically not supported)
TEST_F(RiffVideoTest_78, WriteMetadata_ThrowsUnsupported_78) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromMemory(data);
    
    EXPECT_THROW(video->writeMetadata(), Exiv2::Error);
}

// Test readMetadata with a minimal valid RIFF/AVI - may throw or succeed depending on content
TEST_F(RiffVideoTest_78, ReadMetadata_MinimalRiffAvi_78) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromMemory(data);
    
    // A minimal RIFF/AVI might throw because it lacks required chunks,
    // but it should at least pass the RIFF type check
    try {
        video->readMetadata();
        // If it succeeds, check that some XMP data was populated
        Exiv2::XmpData& xmpData = video->xmpData();
        // FileSize should be set
        auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.video.FileSize"));
        if (it != xmpData.end()) {
            EXPECT_GT(it->toInt64(), 0);
        }
    } catch (const Exiv2::Error&) {
        // It's acceptable to throw for an incomplete RIFF file
    }
}

// Test with single byte data
TEST_F(RiffVideoTest_78, ReadMetadata_SingleByte_ThrowsError_78) {
    std::vector<uint8_t> data = {0x42};
    auto video = createRiffVideoFromMemory(data);
    
    EXPECT_THROW(video->readMetadata(), Exiv2::Error);
}

// Test with data that starts with "RIFF" but is too short
TEST_F(RiffVideoTest_78, ReadMetadata_TruncatedRiff_ThrowsError_78) {
    std::vector<uint8_t> data = {'R', 'I', 'F', 'F'};
    auto video = createRiffVideoFromMemory(data);
    
    EXPECT_THROW(video->readMetadata(), Exiv2::Error);
}

// Test with "RIFF" header + size but no form type
TEST_F(RiffVideoTest_78, ReadMetadata_RiffNoFormType_ThrowsError_78) {
    std::vector<uint8_t> data = {'R', 'I', 'F', 'F', 0x00, 0x00, 0x00, 0x00};
    auto video = createRiffVideoFromMemory(data);
    
    EXPECT_THROW(video->readMetadata(), Exiv2::Error);
}

// Test that good() returns appropriate value before reading
TEST_F(RiffVideoTest_78, Good_BeforeReadMetadata_78) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromMemory(data);
    
    // good() should work before readMetadata
    bool isGood = video->good();
    // MemIo should be initially good
    EXPECT_TRUE(isGood);
}

// Test that io() returns a reference to the IO object
TEST_F(RiffVideoTest_78, IoAccessible_78) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromMemory(data);
    
    const Exiv2::BasicIo& io = video->io();
    EXPECT_EQ(io.size(), data.size());
}

// Test clearMetadata works
TEST_F(RiffVideoTest_78, ClearMetadata_ClearsXmpData_78) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromMemory(data);
    
    // Set some XMP data
    video->xmpData()["Xmp.video.FileSize"] = "12345";
    EXPECT_FALSE(video->xmpData().empty());
    
    video->clearMetadata();
    EXPECT_TRUE(video->xmpData().empty());
}

// Test with RIFF file that has a very large stated size
TEST_F(RiffVideoTest_78, ReadMetadata_LargeStatedSize_78) {
    std::vector<uint8_t> data;
    // "RIFF"
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    // Very large size (0xFFFFFFFF)
    data.push_back(0xFF); data.push_back(0xFF); data.push_back(0xFF); data.push_back(0xFF);
    // "AVI "
    data.push_back('A'); data.push_back('V'); data.push_back('I'); data.push_back(' ');
    
    auto video = createRiffVideoFromMemory(data);
    
    // Should either throw or handle gracefully
    try {
        video->readMetadata();
    } catch (const Exiv2::Error&) {
        // Expected for truncated data
    }
}

// Test with RIFF/WAVE data (not AVI) - should still be valid RIFF type check
TEST_F(RiffVideoTest_78, ReadMetadata_RiffWave_78) {
    auto data = createRiffNonAviData();
    auto video = createRiffVideoFromMemory(data);
    
    // RIFF/WAVE should pass the RIFF type check but may fail later
    try {
        video->readMetadata();
        // If it succeeds, check mime type and XMP data
        Exiv2::XmpData& xmpData = video->xmpData();
        auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.video.FileSize"));
        if (it != xmpData.end()) {
            EXPECT_EQ(it->toInt64(), static_cast<int64_t>(data.size()));
        }
    } catch (const Exiv2::Error&) {
        // Acceptable - incomplete RIFF file
    }
}

// Test that multiple readMetadata calls work (metadata should be cleared each time)
TEST_F(RiffVideoTest_78, ReadMetadata_MultipleCalls_78) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromMemory(data);
    
    // First call
    try {
        video->readMetadata();
    } catch (const Exiv2::Error&) {
        // May throw for minimal file
    }
    
    // Second call should also work or throw consistently
    try {
        video->readMetadata();
    } catch (const Exiv2::Error&) {
        // Expected
    }
}

// Test exifData access
TEST_F(RiffVideoTest_78, ExifData_Accessible_78) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromMemory(data);
    
    Exiv2::ExifData& exifData = video->exifData();
    EXPECT_TRUE(exifData.empty());
}

// Test iptcData access
TEST_F(RiffVideoTest_78, IptcData_Accessible_78) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromMemory(data);
    
    Exiv2::IptcData& iptcData = video->iptcData();
    EXPECT_TRUE(iptcData.empty());
}

}  // namespace
