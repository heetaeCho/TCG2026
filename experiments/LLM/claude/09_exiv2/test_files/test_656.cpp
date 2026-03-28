#include <gtest/gtest.h>
#include <exiv2/quicktimevideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <cstring>
#include <fstream>
#include <memory>

// Helper to create a minimal QuickTime file in memory
static std::vector<uint8_t> createMinimalQuickTimeData() {
    // Minimal QuickTime file: just an 'ftyp' box
    // Box: size (4 bytes) + type (4 bytes) + data
    std::vector<uint8_t> data;
    
    // ftyp box
    uint32_t ftypSize = 20; // size of ftyp box
    // size in big-endian
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
    // compatible brand
    data.push_back('q'); data.push_back('t'); data.push_back(' '); data.push_back(' ');
    
    return data;
}

static std::unique_ptr<Exiv2::BasicIo> createMemIoFromData(const std::vector<uint8_t>& data) {
    return std::make_unique<Exiv2::MemIo>(data.data(), data.size());
}

class QuickTimeVideoTest_656 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that mimeType returns the expected MIME type for QuickTime
TEST_F(QuickTimeVideoTest_656, MimeTypeReturnsVideoQuicktime_656) {
    auto data = createMinimalQuickTimeData();
    auto io = createMemIoFromData(data);
    Exiv2::QuickTimeVideo qtv(std::move(io), 1000);
    
    EXPECT_EQ(qtv.mimeType(), "video/quicktime");
}

// Test that mimeType is consistent across multiple calls
TEST_F(QuickTimeVideoTest_656, MimeTypeConsistentAcrossMultipleCalls_656) {
    auto data = createMinimalQuickTimeData();
    auto io = createMemIoFromData(data);
    Exiv2::QuickTimeVideo qtv(std::move(io), 1000);
    
    std::string first = qtv.mimeType();
    std::string second = qtv.mimeType();
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, "video/quicktime");
}

// Test construction with different max_recursion_depth values
TEST_F(QuickTimeVideoTest_656, ConstructionWithZeroRecursionDepth_656) {
    auto data = createMinimalQuickTimeData();
    auto io = createMemIoFromData(data);
    
    // Should not throw during construction
    EXPECT_NO_THROW(Exiv2::QuickTimeVideo qtv(std::move(io), 0));
}

TEST_F(QuickTimeVideoTest_656, ConstructionWithLargeRecursionDepth_656) {
    auto data = createMinimalQuickTimeData();
    auto io = createMemIoFromData(data);
    
    EXPECT_NO_THROW(Exiv2::QuickTimeVideo qtv(std::move(io), 100000));
}

// Test writeMetadata throws (QuickTime videos are typically read-only in exiv2)
TEST_F(QuickTimeVideoTest_656, WriteMetadataThrows_656) {
    auto data = createMinimalQuickTimeData();
    auto io = createMemIoFromData(data);
    Exiv2::QuickTimeVideo qtv(std::move(io), 1000);
    
    EXPECT_THROW(qtv.writeMetadata(), Exiv2::Error);
}

// Test readMetadata on a minimal QuickTime file
TEST_F(QuickTimeVideoTest_656, ReadMetadataMinimalFile_656) {
    auto data = createMinimalQuickTimeData();
    auto io = createMemIoFromData(data);
    Exiv2::QuickTimeVideo qtv(std::move(io), 1000);
    
    // Should not throw on a minimal valid QuickTime file
    EXPECT_NO_THROW(qtv.readMetadata());
}

// Test readMetadata on empty data
TEST_F(QuickTimeVideoTest_656, ReadMetadataEmptyFile_656) {
    std::vector<uint8_t> emptyData;
    auto io = createMemIoFromData(emptyData);
    Exiv2::QuickTimeVideo qtv(std::move(io), 1000);
    
    // Reading metadata from empty file - may throw or handle gracefully
    try {
        qtv.readMetadata();
    } catch (const Exiv2::Error&) {
        // Expected - empty file is not a valid QuickTime
    }
}

// Test readMetadata with very small (truncated) data
TEST_F(QuickTimeVideoTest_656, ReadMetadataTruncatedData_656) {
    std::vector<uint8_t> truncated = {0x00, 0x00, 0x00};
    auto io = createMemIoFromData(truncated);
    Exiv2::QuickTimeVideo qtv(std::move(io), 1000);
    
    // Should handle truncated data gracefully
    try {
        qtv.readMetadata();
    } catch (const Exiv2::Error&) {
        // Expected for invalid data
    }
}

// Test readMetadata with corrupted box size
TEST_F(QuickTimeVideoTest_656, ReadMetadataCorruptedBoxSize_656) {
    std::vector<uint8_t> data;
    // Box with size pointing way beyond data
    data.push_back(0xFF); data.push_back(0xFF); data.push_back(0xFF); data.push_back(0xFF);
    data.push_back('f'); data.push_back('t'); data.push_back('y'); data.push_back('p');
    
    auto io = createMemIoFromData(data);
    Exiv2::QuickTimeVideo qtv(std::move(io), 1000);
    
    try {
        qtv.readMetadata();
    } catch (const Exiv2::Error&) {
        // Expected for corrupted data
    }
}

// Test that readMetadata respects max recursion depth (zero depth)
TEST_F(QuickTimeVideoTest_656, ReadMetadataWithZeroRecursionDepth_656) {
    auto data = createMinimalQuickTimeData();
    auto io = createMemIoFromData(data);
    Exiv2::QuickTimeVideo qtv(std::move(io), 0);
    
    // With zero recursion depth, may throw or return early
    try {
        qtv.readMetadata();
    } catch (const Exiv2::Error&) {
        // Acceptable behavior
    }
}

// Test construction with a valid file having moov box
TEST_F(QuickTimeVideoTest_656, ReadMetadataWithMoovBox_656) {
    std::vector<uint8_t> data;
    
    // ftyp box
    uint32_t ftypSize = 20;
    data.push_back((ftypSize >> 24) & 0xFF);
    data.push_back((ftypSize >> 16) & 0xFF);
    data.push_back((ftypSize >> 8) & 0xFF);
    data.push_back(ftypSize & 0xFF);
    data.push_back('f'); data.push_back('t'); data.push_back('y'); data.push_back('p');
    data.push_back('q'); data.push_back('t'); data.push_back(' '); data.push_back(' ');
    data.push_back(0); data.push_back(0); data.push_back(0); data.push_back(0);
    data.push_back('q'); data.push_back('t'); data.push_back(' '); data.push_back(' ');
    
    // Empty moov box (just header)
    uint32_t moovSize = 8;
    data.push_back((moovSize >> 24) & 0xFF);
    data.push_back((moovSize >> 16) & 0xFF);
    data.push_back((moovSize >> 8) & 0xFF);
    data.push_back(moovSize & 0xFF);
    data.push_back('m'); data.push_back('o'); data.push_back('o'); data.push_back('v');
    
    auto io = createMemIoFromData(data);
    Exiv2::QuickTimeVideo qtv(std::move(io), 1000);
    
    EXPECT_NO_THROW(qtv.readMetadata());
}

// Test that multiple readMetadata calls work
TEST_F(QuickTimeVideoTest_656, ReadMetadataMultipleCalls_656) {
    auto data = createMinimalQuickTimeData();
    auto io = createMemIoFromData(data);
    Exiv2::QuickTimeVideo qtv(std::move(io), 1000);
    
    EXPECT_NO_THROW(qtv.readMetadata());
    // Second call should also work (re-reads from beginning)
    EXPECT_NO_THROW(qtv.readMetadata());
}

// Test with data containing unknown box types
TEST_F(QuickTimeVideoTest_656, ReadMetadataUnknownBoxTypes_656) {
    std::vector<uint8_t> data;
    
    // Unknown box 'xxxx' with size 12 (8 header + 4 data)
    uint32_t boxSize = 12;
    data.push_back((boxSize >> 24) & 0xFF);
    data.push_back((boxSize >> 16) & 0xFF);
    data.push_back((boxSize >> 8) & 0xFF);
    data.push_back(boxSize & 0xFF);
    data.push_back('x'); data.push_back('x'); data.push_back('x'); data.push_back('x');
    data.push_back(0); data.push_back(0); data.push_back(0); data.push_back(0);
    
    auto io = createMemIoFromData(data);
    Exiv2::QuickTimeVideo qtv(std::move(io), 1000);
    
    // Should handle unknown box types gracefully
    try {
        qtv.readMetadata();
    } catch (const Exiv2::Error&) {
        // Acceptable
    }
}

// Test mimeType does not depend on file content
TEST_F(QuickTimeVideoTest_656, MimeTypeIndependentOfContent_656) {
    std::vector<uint8_t> emptyData;
    auto io = createMemIoFromData(emptyData);
    Exiv2::QuickTimeVideo qtv(std::move(io), 1000);
    
    // mimeType should return the same value regardless of file content
    EXPECT_EQ(qtv.mimeType(), "video/quicktime");
}

// Test with a box that has size == 0 (extends to end of file)
TEST_F(QuickTimeVideoTest_656, ReadMetadataZeroSizeBox_656) {
    std::vector<uint8_t> data;
    
    // Box with size = 0 means it extends to end of file
    data.push_back(0); data.push_back(0); data.push_back(0); data.push_back(0);
    data.push_back('m'); data.push_back('d'); data.push_back('a'); data.push_back('t');
    // Some data
    data.push_back(0xDE); data.push_back(0xAD);
    
    auto io = createMemIoFromData(data);
    Exiv2::QuickTimeVideo qtv(std::move(io), 1000);
    
    try {
        qtv.readMetadata();
    } catch (const Exiv2::Error&) {
        // Acceptable
    }
}
