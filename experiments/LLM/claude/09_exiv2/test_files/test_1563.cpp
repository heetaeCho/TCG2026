#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/asfvideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>
#include <memory>
#include <cstring>
#include <fstream>
#include <vector>

using namespace Exiv2;

// Helper to create a MemIo with specific content
class AsfVideoTest_1563 : public ::testing::Test {
protected:
    // ASF Header GUID: 30 26 B2 75 8E 66 CF 11 A6 D9 00 AA 00 62 CE 6C
    static constexpr uint8_t ASF_HEADER_GUID[] = {
        0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
        0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
    };

    std::vector<uint8_t> createMinimalAsfHeader(uint32_t numObjects = 0) {
        std::vector<uint8_t> data;

        // ASF Header Object GUID (16 bytes)
        data.insert(data.end(), ASF_HEADER_GUID, ASF_HEADER_GUID + 16);

        // Size (8 bytes, little-endian) - header object size
        // Minimum: 16 (GUID) + 8 (size) + 4 (num objects) + 2 (reserved) = 30
        uint64_t headerSize = 30;
        for (int i = 0; i < 8; i++) {
            data.push_back(static_cast<uint8_t>((headerSize >> (i * 8)) & 0xFF));
        }

        // Number of header objects (4 bytes, little-endian)
        for (int i = 0; i < 4; i++) {
            data.push_back(static_cast<uint8_t>((numObjects >> (i * 8)) & 0xFF));
        }

        // Reserved1 (1 byte) + Reserved2 (1 byte)
        data.push_back(0x01);
        data.push_back(0x02);

        return data;
    }
};

// Test that AsfVideo can be constructed with a valid IO
TEST_F(AsfVideoTest_1563, ConstructWithValidIo_1563) {
    auto io = std::make_unique<MemIo>();
    ASSERT_NO_THROW(AsfVideo video(std::move(io)));
}

// Test mimeType returns expected value
TEST_F(AsfVideoTest_1563, MimeTypeReturnsCorrectValue_1563) {
    auto io = std::make_unique<MemIo>();
    AsfVideo video(std::move(io));
    std::string mime = video.mimeType();
    EXPECT_EQ(mime, "video/x-ms-asf");
}

// Test writeMetadata throws as ASF writing is not supported
TEST_F(AsfVideoTest_1563, WriteMetadataThrows_1563) {
    auto io = std::make_unique<MemIo>();
    AsfVideo video(std::move(io));
    EXPECT_THROW(video.writeMetadata(), Error);
}

// Test readMetadata on empty IO throws
TEST_F(AsfVideoTest_1563, ReadMetadataOnEmptyIoThrows_1563) {
    auto io = std::make_unique<MemIo>();
    AsfVideo video(std::move(io));
    EXPECT_THROW(video.readMetadata(), Error);
}

// Test readMetadata with too-small data throws
TEST_F(AsfVideoTest_1563, ReadMetadataWithTooSmallDataThrows_1563) {
    // Data smaller than GUID + QWORD = 24 bytes
    std::vector<uint8_t> data(10, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    EXPECT_THROW(video.readMetadata(), Error);
}

// Test readMetadata with corrupted header (invalid size) throws
TEST_F(AsfVideoTest_1563, ReadMetadataWithCorruptedSizeThrows_1563) {
    // Create data with valid GUID but an impossibly large size
    std::vector<uint8_t> data(24, 0);
    // Put any GUID
    std::memcpy(data.data(), ASF_HEADER_GUID, 16);
    // Set size to a very large value (larger than actual data)
    uint64_t fakeSize = 0xFFFFFFFFFFFFFFFF;
    for (int i = 0; i < 8; i++) {
        data[16 + i] = static_cast<uint8_t>((fakeSize >> (i * 8)) & 0xFF);
    }
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    EXPECT_THROW(video.readMetadata(), Error);
}

// Test readMetadata with minimal valid ASF header
TEST_F(AsfVideoTest_1563, ReadMetadataWithMinimalHeader_1563) {
    auto data = createMinimalAsfHeader(0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    // Even with a minimal header with 0 objects, readMetadata should process it
    // It may throw or succeed depending on implementation; we test it doesn't crash
    try {
        video.readMetadata();
    } catch (const Error&) {
        // Expected - minimal data may not be sufficient
    }
}

// Test readMetadata with data that has unknown GUID
TEST_F(AsfVideoTest_1563, ReadMetadataWithUnknownGuid_1563) {
    std::vector<uint8_t> data;
    
    // First, the top-level object: use the ASF Header GUID
    data.insert(data.end(), ASF_HEADER_GUID, ASF_HEADER_GUID + 16);
    
    // Size of header object = 30 + size of sub-objects
    // We'll add one unknown sub-object of minimal size
    uint64_t subObjSize = 24; // GUID(16) + size(8)
    uint64_t headerSize = 30 + subObjSize;
    for (int i = 0; i < 8; i++) {
        data.push_back(static_cast<uint8_t>((headerSize >> (i * 8)) & 0xFF));
    }
    
    // Number of header objects = 1
    uint32_t numObjects = 1;
    for (int i = 0; i < 4; i++) {
        data.push_back(static_cast<uint8_t>((numObjects >> (i * 8)) & 0xFF));
    }
    
    // Reserved
    data.push_back(0x01);
    data.push_back(0x02);
    
    // Sub-object: unknown GUID
    uint8_t unknownGuid[16] = {0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8,
                                0xF7, 0xF6, 0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0};
    data.insert(data.end(), unknownGuid, unknownGuid + 16);
    
    // Size of sub-object = 24 (just the header, no additional data)
    for (int i = 0; i < 8; i++) {
        data.push_back(static_cast<uint8_t>((subObjSize >> (i * 8)) & 0xFF));
    }
    
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    
    try {
        video.readMetadata();
    } catch (const Error&) {
        // May throw due to size enforcement
    }
}

// Test that pixel dimensions are 0 by default before readMetadata
TEST_F(AsfVideoTest_1563, DefaultPixelDimensionsAreZero_1563) {
    auto io = std::make_unique<MemIo>();
    AsfVideo video(std::move(io));
    EXPECT_EQ(video.pixelWidth(), 0u);
    EXPECT_EQ(video.pixelHeight(), 0u);
}

// Test that exifData is initially empty
TEST_F(AsfVideoTest_1563, ExifDataInitiallyEmpty_1563) {
    auto io = std::make_unique<MemIo>();
    AsfVideo video(std::move(io));
    EXPECT_TRUE(video.exifData().empty());
}

// Test that xmpData is initially empty
TEST_F(AsfVideoTest_1563, XmpDataInitiallyEmpty_1563) {
    auto io = std::make_unique<MemIo>();
    AsfVideo video(std::move(io));
    EXPECT_TRUE(video.xmpData().empty());
}

// Test readMetadata with exactly GUID+QWORD = 24 bytes of zeros
TEST_F(AsfVideoTest_1563, ReadMetadataWithExactly24ZeroBytes_1563) {
    std::vector<uint8_t> data(24, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    // The object size will be 0 which should fail enforce checks
    EXPECT_THROW(video.readMetadata(), Error);
}

// Test readMetadata with size field claiming zero remaining
TEST_F(AsfVideoTest_1563, ReadMetadataZeroSizeInObject_1563) {
    std::vector<uint8_t> data(24, 0);
    // Unknown GUID
    for (int i = 0; i < 16; i++) data[i] = static_cast<uint8_t>(i + 1);
    // Size = 0 (should trigger enforce failure)
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    EXPECT_THROW(video.readMetadata(), Error);
}

// Test that reading metadata from data with only 23 bytes fails
TEST_F(AsfVideoTest_1563, ReadMetadataTooFewBytesForBlock_1563) {
    std::vector<uint8_t> data(23, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    EXPECT_THROW(video.readMetadata(), Error);
}

// Test readMetadata with a valid-looking header but object size = 24 (minimum)
// and unknown GUID
TEST_F(AsfVideoTest_1563, ReadMetadataObjectSizeEqualsMinimum_1563) {
    std::vector<uint8_t> data;
    // Unknown GUID
    uint8_t guid[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                         0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};
    data.insert(data.end(), guid, guid + 16);
    
    // Size = 24 (GUID + QWORD, no remaining data)
    // remaining_size = size - 24 = 0, which should fail enforce(remaining_size > 0)
    uint64_t objSize = 24;
    for (int i = 0; i < 8; i++) {
        data.push_back(static_cast<uint8_t>((objSize >> (i * 8)) & 0xFF));
    }
    
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    EXPECT_THROW(video.readMetadata(), Error);
}

// Test that ImageType is asf
TEST_F(AsfVideoTest_1563, ImageTypeIsAsf_1563) {
    auto io = std::make_unique<MemIo>();
    AsfVideo video(std::move(io));
    EXPECT_EQ(video.imageType(), ImageType::asf);
}

// Test good() on freshly constructed AsfVideo with empty MemIo
TEST_F(AsfVideoTest_1563, GoodOnFreshConstruction_1563) {
    auto io = std::make_unique<MemIo>();
    AsfVideo video(std::move(io));
    // MemIo with no data should still be "good" (open succeeds)
    EXPECT_TRUE(video.good());
}

// Test that comment is initially empty
TEST_F(AsfVideoTest_1563, CommentInitiallyEmpty_1563) {
    auto io = std::make_unique<MemIo>();
    AsfVideo video(std::move(io));
    EXPECT_TRUE(video.comment().empty());
}
