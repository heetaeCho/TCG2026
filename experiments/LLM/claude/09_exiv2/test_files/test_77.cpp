#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/riffvideo.hpp>
#include <exiv2/basicio.hpp>
#include <cstring>
#include <fstream>

using namespace Exiv2;

// Helper to create a minimal valid RIFF/AVI file in memory
static std::vector<uint8_t> createMinimalRiffAvi() {
    // Minimal RIFF AVI header:
    // "RIFF" + size(4 bytes) + "AVI " 
    // Total minimum: 12 bytes for the outer RIFF container
    std::vector<uint8_t> data;
    
    // "RIFF"
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    // Size of remaining data (4 bytes, little-endian) - just "AVI " = 4 bytes
    uint32_t size = 4;
    data.push_back(size & 0xFF);
    data.push_back((size >> 8) & 0xFF);
    data.push_back((size >> 16) & 0xFF);
    data.push_back((size >> 24) & 0xFF);
    // "AVI "
    data.push_back('A'); data.push_back('V'); data.push_back('I'); data.push_back(' ');
    
    return data;
}

static std::vector<uint8_t> createInvalidRiffData() {
    // Not a RIFF file - just random bytes
    std::vector<uint8_t> data = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    return data;
}

static std::vector<uint8_t> createEmptyData() {
    return {};
}

class RiffVideoTest_77 : public ::testing::Test {
protected:
    std::unique_ptr<RiffVideo> createRiffVideoFromData(const std::vector<uint8_t>& data) {
        auto memIo = std::make_unique<MemIo>(data.data(), data.size());
        return std::make_unique<RiffVideo>(std::move(memIo));
    }
};

// Test: mimeType returns the correct MIME type
TEST_F(RiffVideoTest_77, MimeTypeReturnsCorrectValue_77) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromData(data);
    EXPECT_EQ(video->mimeType(), "video/riff");
}

// Test: mimeType is consistent across multiple calls
TEST_F(RiffVideoTest_77, MimeTypeIsConsistent_77) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromData(data);
    std::string first = video->mimeType();
    std::string second = video->mimeType();
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, "video/riff");
}

// Test: Construction with valid RIFF data does not throw
TEST_F(RiffVideoTest_77, ConstructionWithValidDataNoThrow_77) {
    auto data = createMinimalRiffAvi();
    EXPECT_NO_THROW({
        auto memIo = std::make_unique<MemIo>(data.data(), data.size());
        RiffVideo video(std::move(memIo));
    });
}

// Test: Construction with empty data does not throw during construction
TEST_F(RiffVideoTest_77, ConstructionWithEmptyData_77) {
    auto data = createEmptyData();
    EXPECT_NO_THROW({
        auto memIo = std::make_unique<MemIo>(data.data(), data.size());
        RiffVideo video(std::move(memIo));
    });
}

// Test: readMetadata on invalid data throws or handles gracefully
TEST_F(RiffVideoTest_77, ReadMetadataInvalidDataThrows_77) {
    auto data = createInvalidRiffData();
    auto video = createRiffVideoFromData(data);
    EXPECT_THROW(video->readMetadata(), Exiv2::Error);
}

// Test: readMetadata on empty file throws
TEST_F(RiffVideoTest_77, ReadMetadataEmptyFileThrows_77) {
    auto data = createEmptyData();
    auto video = createRiffVideoFromData(data);
    EXPECT_THROW(video->readMetadata(), Exiv2::Error);
}

// Test: readMetadata on minimal valid RIFF/AVI does not throw
TEST_F(RiffVideoTest_77, ReadMetadataMinimalValidFile_77) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromData(data);
    EXPECT_NO_THROW(video->readMetadata());
}

// Test: writeMetadata throws (RIFF write is typically not supported)
TEST_F(RiffVideoTest_77, WriteMetadataThrows_77) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromData(data);
    EXPECT_THROW(video->writeMetadata(), Exiv2::Error);
}

// Test: mimeType after readMetadata still returns correct value
TEST_F(RiffVideoTest_77, MimeTypeAfterReadMetadata_77) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromData(data);
    try {
        video->readMetadata();
    } catch (...) {
        // Ignore if it fails
    }
    EXPECT_EQ(video->mimeType(), "video/riff");
}

// Test: Construction preserves the image type
TEST_F(RiffVideoTest_77, ImageTypeIsRiff_77) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromData(data);
    EXPECT_EQ(video->imageType(), ImageType::riff);
}

// Test: readMetadata with truncated RIFF header (only "RIFF" without size)
TEST_F(RiffVideoTest_77, ReadMetadataTruncatedHeader_77) {
    std::vector<uint8_t> data = {'R', 'I', 'F', 'F'};
    auto video = createRiffVideoFromData(data);
    EXPECT_THROW(video->readMetadata(), Exiv2::Error);
}

// Test: readMetadata with RIFF header but wrong form type (not AVI)
TEST_F(RiffVideoTest_77, ReadMetadataWrongFormType_77) {
    std::vector<uint8_t> data;
    // "RIFF"
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    // Size = 4
    uint32_t size = 4;
    data.push_back(size & 0xFF);
    data.push_back((size >> 8) & 0xFF);
    data.push_back((size >> 16) & 0xFF);
    data.push_back((size >> 24) & 0xFF);
    // "WAVE" instead of "AVI "
    data.push_back('W'); data.push_back('A'); data.push_back('V'); data.push_back('E');
    
    auto video = createRiffVideoFromData(data);
    // May throw or handle - depends on implementation
    try {
        video->readMetadata();
    } catch (const Exiv2::Error&) {
        // Expected for non-AVI RIFF
        SUCCEED();
        return;
    }
    // If it doesn't throw, still valid behavior
    SUCCEED();
}

// Test: Multiple readMetadata calls on same object
TEST_F(RiffVideoTest_77, MultipleReadMetadataCalls_77) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromData(data);
    
    // First call
    EXPECT_NO_THROW(video->readMetadata());
    // Second call - should also work (re-read)
    EXPECT_NO_THROW(video->readMetadata());
}

// Test: Verify that after construction, IO is accessible
TEST_F(RiffVideoTest_77, IoAccessibleAfterConstruction_77) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromData(data);
    EXPECT_NE(&video->io(), nullptr);
}

// Test: RIFF with size larger than actual data
TEST_F(RiffVideoTest_77, ReadMetadataOversizedHeader_77) {
    std::vector<uint8_t> data;
    // "RIFF"
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    // Size = 1000000 (way larger than actual data)
    uint32_t size = 1000000;
    data.push_back(size & 0xFF);
    data.push_back((size >> 8) & 0xFF);
    data.push_back((size >> 16) & 0xFF);
    data.push_back((size >> 24) & 0xFF);
    // "AVI "
    data.push_back('A'); data.push_back('V'); data.push_back('I'); data.push_back(' ');
    
    auto video = createRiffVideoFromData(data);
    // Should handle gracefully - either succeed partially or throw
    try {
        video->readMetadata();
        SUCCEED();
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}
