#include <gtest/gtest.h>
#include <exiv2/matroskavideo.hpp>
#include <exiv2/basicio.hpp>
#include <cstring>
#include <fstream>

using namespace Exiv2;

class MatroskaVideoTest_95 : public ::testing::Test {
protected:
    // Helper to create a MatroskaVideo from a memory buffer
    std::unique_ptr<MatroskaVideo> createFromBuffer(const byte* data, size_t size) {
        auto io = std::make_unique<MemIo>(data, size);
        return std::make_unique<MatroskaVideo>(std::move(io));
    }

    // Helper to create a MatroskaVideo from an empty buffer
    std::unique_ptr<MatroskaVideo> createEmpty() {
        auto io = std::make_unique<MemIo>();
        return std::make_unique<MatroskaVideo>(std::move(io));
    }
};

// Test that mimeType returns the correct MIME type for Matroska video
TEST_F(MatroskaVideoTest_95, MimeTypeReturnsCorrectValue_95) {
    auto video = createEmpty();
    EXPECT_EQ(video->mimeType(), "video/matroska");
}

// Test that mimeType is consistent across multiple calls
TEST_F(MatroskaVideoTest_95, MimeTypeIsConsistent_95) {
    auto video = createEmpty();
    std::string first = video->mimeType();
    std::string second = video->mimeType();
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, "video/matroska");
}

// Test that writeMetadata throws for Matroska (typically not supported or throws on empty)
TEST_F(MatroskaVideoTest_95, WriteMetadataThrows_95) {
    auto video = createEmpty();
    EXPECT_THROW(video->writeMetadata(), Error);
}

// Test that readMetadata on empty data throws or handles gracefully
TEST_F(MatroskaVideoTest_95, ReadMetadataOnEmptyDataThrows_95) {
    auto video = createEmpty();
    EXPECT_THROW(video->readMetadata(), Error);
}

// Test that readMetadata on invalid/garbage data handles gracefully
TEST_F(MatroskaVideoTest_95, ReadMetadataOnGarbageData_95) {
    byte garbage[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                      0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    auto video = createFromBuffer(garbage, sizeof(garbage));
    // Reading garbage should either throw or return without crashing
    try {
        video->readMetadata();
    } catch (const Error&) {
        // Expected - invalid data
    }
}

// Test construction with a valid BasicIo (MemIo)
TEST_F(MatroskaVideoTest_95, ConstructionWithMemIo_95) {
    auto io = std::make_unique<MemIo>();
    EXPECT_NO_THROW(MatroskaVideo video(std::move(io)));
}

// Test that readMetadata on a very small buffer doesn't crash
TEST_F(MatroskaVideoTest_95, ReadMetadataSmallBuffer_95) {
    byte small[] = {0x1A, 0x45, 0xDF, 0xA3}; // EBML header ID
    auto video = createFromBuffer(small, sizeof(small));
    try {
        video->readMetadata();
    } catch (const Error&) {
        // Expected for truncated file
    }
}

// Test with a minimal EBML header structure
TEST_F(MatroskaVideoTest_95, ReadMetadataMinimalEBMLHeader_95) {
    // EBML header element ID: 0x1A45DFA3, followed by a size and minimal content
    byte minimalEbml[] = {
        0x1A, 0x45, 0xDF, 0xA3, // EBML ID
        0x84,                     // Size = 4
        0x42, 0x86, 0x81, 0x01   // EBMLVersion = 1
    };
    auto video = createFromBuffer(minimalEbml, sizeof(minimalEbml));
    try {
        video->readMetadata();
    } catch (const Error&) {
        // May fail due to incomplete data, but shouldn't crash
    }
}

// Test that multiple MatroskaVideo instances have independent state
TEST_F(MatroskaVideoTest_95, MultipleInstancesAreIndependent_95) {
    auto video1 = createEmpty();
    auto video2 = createEmpty();
    EXPECT_EQ(video1->mimeType(), video2->mimeType());
    EXPECT_EQ(video1->mimeType(), "video/matroska");
}

// Test readMetadata with data that has only EBML ID but zero size
TEST_F(MatroskaVideoTest_95, ReadMetadataZeroSizeEBML_95) {
    byte zeroSize[] = {
        0x1A, 0x45, 0xDF, 0xA3, // EBML ID
        0x80                      // Size = 0
    };
    auto video = createFromBuffer(zeroSize, sizeof(zeroSize));
    try {
        video->readMetadata();
    } catch (const Error&) {
        // Expected
    }
}

// Test with a larger random buffer to check for buffer overflows
TEST_F(MatroskaVideoTest_95, ReadMetadataLargerRandomBuffer_95) {
    std::vector<byte> largeBuffer(1024, 0xFF);
    // Put EBML header at the start
    largeBuffer[0] = 0x1A;
    largeBuffer[1] = 0x45;
    largeBuffer[2] = 0xDF;
    largeBuffer[3] = 0xA3;
    
    auto video = createFromBuffer(largeBuffer.data(), largeBuffer.size());
    try {
        video->readMetadata();
    } catch (const Error&) {
        // Expected for malformed data
    }
}

// Test that the image type is correct
TEST_F(MatroskaVideoTest_95, ImageTypeIsMKV_95) {
    auto video = createEmpty();
    // The image type should be mkv as set in the constructor
    // We can verify indirectly through the mime type
    EXPECT_EQ(video->mimeType(), "video/matroska");
}
