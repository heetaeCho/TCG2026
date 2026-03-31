#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/asfvideo.hpp>
#include <exiv2/basicio.hpp>
#include <memory>
#include <fstream>
#include <cstring>

// Helper to create a MemIo with given data
static std::unique_ptr<Exiv2::BasicIo> makeMemIo(const std::vector<uint8_t>& data) {
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    return io;
}

// Minimal ASF header GUID: 3026B2758E66CF11A6D900AA0062CE6C
static const uint8_t ASF_HEADER_GUID[] = {
    0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
    0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
};

class AsfVideoTest_1561 : public ::testing::Test {
protected:
    // Create a minimal but valid-ish ASF buffer
    std::vector<uint8_t> createMinimalAsfData() {
        std::vector<uint8_t> data;
        // ASF Header Object GUID (16 bytes)
        data.insert(data.end(), ASF_HEADER_GUID, ASF_HEADER_GUID + 16);
        // Size of header object (8 bytes, little-endian) - minimal: 30 bytes total
        uint64_t headerSize = 30;
        for (int i = 0; i < 8; i++) {
            data.push_back(static_cast<uint8_t>((headerSize >> (8 * i)) & 0xFF));
        }
        // Number of header objects (4 bytes)
        uint32_t numHeaders = 0;
        for (int i = 0; i < 4; i++) {
            data.push_back(static_cast<uint8_t>((numHeaders >> (8 * i)) & 0xFF));
        }
        // Reserved1 (1 byte)
        data.push_back(0x01);
        // Reserved2 (1 byte)
        data.push_back(0x02);
        return data;
    }

    std::vector<uint8_t> createEmptyData() {
        return std::vector<uint8_t>();
    }
};

// Test that mimeType returns the expected value
TEST_F(AsfVideoTest_1561, MimeTypeReturnsVideoAsf_1561) {
    auto data = createMinimalAsfData();
    auto io = makeMemIo(data);
    auto asf = std::make_unique<Exiv2::AsfVideo>(std::move(io));
    EXPECT_EQ(asf->mimeType(), "video/asf");
}

// Test that mimeType is consistent across multiple calls
TEST_F(AsfVideoTest_1561, MimeTypeConsistentMultipleCalls_1561) {
    auto data = createMinimalAsfData();
    auto io = makeMemIo(data);
    auto asf = std::make_unique<Exiv2::AsfVideo>(std::move(io));
    std::string first = asf->mimeType();
    std::string second = asf->mimeType();
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, "video/asf");
}

// Test construction with empty data doesn't crash
TEST_F(AsfVideoTest_1561, ConstructionWithEmptyIo_1561) {
    auto data = createEmptyData();
    auto io = makeMemIo(data);
    EXPECT_NO_THROW({
        auto asf = std::make_unique<Exiv2::AsfVideo>(std::move(io));
    });
}

// Test that writeMetadata throws (ASF typically doesn't support writing)
TEST_F(AsfVideoTest_1561, WriteMetadataThrows_1561) {
    auto data = createMinimalAsfData();
    auto io = makeMemIo(data);
    auto asf = std::make_unique<Exiv2::AsfVideo>(std::move(io));
    EXPECT_THROW(asf->writeMetadata(), Exiv2::Error);
}

// Test readMetadata with empty/invalid data throws
TEST_F(AsfVideoTest_1561, ReadMetadataWithEmptyDataThrows_1561) {
    auto data = createEmptyData();
    auto io = makeMemIo(data);
    auto asf = std::make_unique<Exiv2::AsfVideo>(std::move(io));
    EXPECT_THROW(asf->readMetadata(), Exiv2::Error);
}

// Test readMetadata with minimal valid ASF data
TEST_F(AsfVideoTest_1561, ReadMetadataWithMinimalData_1561) {
    auto data = createMinimalAsfData();
    auto io = makeMemIo(data);
    auto asf = std::make_unique<Exiv2::AsfVideo>(std::move(io));
    // Minimal data may or may not throw depending on implementation
    // We just verify it doesn't crash unexpectedly
    try {
        asf->readMetadata();
    } catch (const Exiv2::Error&) {
        // Expected for incomplete data
    }
}

// Test readMetadata with garbage data
TEST_F(AsfVideoTest_1561, ReadMetadataWithGarbageData_1561) {
    std::vector<uint8_t> garbage(256, 0xAB);
    auto io = makeMemIo(garbage);
    auto asf = std::make_unique<Exiv2::AsfVideo>(std::move(io));
    EXPECT_THROW(asf->readMetadata(), Exiv2::Error);
}

// Test that mimeType still works after failed readMetadata
TEST_F(AsfVideoTest_1561, MimeTypeAfterFailedReadMetadata_1561) {
    auto data = createEmptyData();
    auto io = makeMemIo(data);
    auto asf = std::make_unique<Exiv2::AsfVideo>(std::move(io));
    try {
        asf->readMetadata();
    } catch (...) {
        // ignore
    }
    EXPECT_EQ(asf->mimeType(), "video/asf");
}

// Test construction with small data (just a few bytes)
TEST_F(AsfVideoTest_1561, ConstructionWithSmallData_1561) {
    std::vector<uint8_t> smallData = {0x30, 0x26, 0xB2};
    auto io = makeMemIo(smallData);
    EXPECT_NO_THROW({
        auto asf = std::make_unique<Exiv2::AsfVideo>(std::move(io));
    });
}

// Test readMetadata with only the GUID (truncated header)
TEST_F(AsfVideoTest_1561, ReadMetadataWithTruncatedHeader_1561) {
    std::vector<uint8_t> data(ASF_HEADER_GUID, ASF_HEADER_GUID + 16);
    auto io = makeMemIo(data);
    auto asf = std::make_unique<Exiv2::AsfVideo>(std::move(io));
    EXPECT_THROW(asf->readMetadata(), Exiv2::Error);
}

// Test that the image type is correct (if accessible through public interface)
TEST_F(AsfVideoTest_1561, ImageTypeIsAsf_1561) {
    auto data = createMinimalAsfData();
    auto io = makeMemIo(data);
    auto asf = std::make_unique<Exiv2::AsfVideo>(std::move(io));
    // Image base class should report the correct image type
    EXPECT_EQ(asf->imageType(), Exiv2::ImageType::asf);
}
