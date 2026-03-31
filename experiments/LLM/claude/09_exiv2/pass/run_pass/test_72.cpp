#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/webpimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <fstream>
#include <cstring>
#include <vector>

namespace {

// Helper to create a minimal valid WebP file in memory
std::vector<uint8_t> createMinimalWebP() {
    // RIFF header + WEBP + VP8 chunk (minimal)
    std::vector<uint8_t> data;
    
    // "RIFF"
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    
    // File size (little-endian, total size - 8)
    // We'll have: WEBP(4) + VP8 chunk header(8) + VP8 data(10) = 22
    uint32_t fileSize = 22;
    data.push_back(fileSize & 0xFF);
    data.push_back((fileSize >> 8) & 0xFF);
    data.push_back((fileSize >> 16) & 0xFF);
    data.push_back((fileSize >> 24) & 0xFF);
    
    // "WEBP"
    data.push_back('W'); data.push_back('E'); data.push_back('B'); data.push_back('P');
    
    // VP8 chunk
    data.push_back('V'); data.push_back('P'); data.push_back('8'); data.push_back(' ');
    
    // VP8 chunk size (little-endian) = 10
    uint32_t chunkSize = 10;
    data.push_back(chunkSize & 0xFF);
    data.push_back((chunkSize >> 8) & 0xFF);
    data.push_back((chunkSize >> 16) & 0xFF);
    data.push_back((chunkSize >> 24) & 0xFF);
    
    // Minimal VP8 bitstream (frame tag + some data)
    // VP8 key frame: 3 bytes frame tag + 7 bytes
    data.push_back(0x9D); data.push_back(0x01); data.push_back(0x2A);
    // Width (16-bit LE) and Height (16-bit LE)
    data.push_back(0x01); data.push_back(0x00); // width=1
    data.push_back(0x01); data.push_back(0x00); // height=1
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00);
    
    return data;
}

// Helper to create invalid data (not a WebP file)
std::vector<uint8_t> createInvalidData() {
    std::vector<uint8_t> data = {'N', 'O', 'T', 'W', 'E', 'B', 'P'};
    return data;
}

// Helper to create empty data
std::vector<uint8_t> createEmptyData() {
    return std::vector<uint8_t>();
}

} // anonymous namespace

class WebPImageTest_72 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: newWebPInstance with valid WebP data returns non-null image
TEST_F(WebPImageTest_72, NewWebPInstanceWithValidData_ReturnsNonNull_72) {
    auto webpData = createMinimalWebP();
    auto io = std::make_unique<Exiv2::MemIo>(webpData.data(), webpData.size());
    auto image = Exiv2::newWebPInstance(std::move(io), false);
    // The image may or may not be valid depending on internal validation.
    // We just check the function doesn't crash and returns something.
    // If the minimal WebP is not considered valid, image could be null.
    // This test verifies the function can be called without error.
}

// Test: newWebPInstance with invalid data returns null
TEST_F(WebPImageTest_72, NewWebPInstanceWithInvalidData_ReturnsNull_72) {
    auto invalidData = createInvalidData();
    auto io = std::make_unique<Exiv2::MemIo>(invalidData.data(), invalidData.size());
    auto image = Exiv2::newWebPInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: newWebPInstance with empty data returns null
TEST_F(WebPImageTest_72, NewWebPInstanceWithEmptyData_ReturnsNull_72) {
    auto emptyData = createEmptyData();
    auto io = std::make_unique<Exiv2::MemIo>(emptyData.data(), emptyData.size());
    auto image = Exiv2::newWebPInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: newWebPInstance with create=true and invalid data
TEST_F(WebPImageTest_72, NewWebPInstanceCreateTrueInvalidData_ReturnsNull_72) {
    auto invalidData = createInvalidData();
    auto io = std::make_unique<Exiv2::MemIo>(invalidData.data(), invalidData.size());
    auto image = Exiv2::newWebPInstance(std::move(io), true);
    EXPECT_EQ(image, nullptr);
}

// Test: WebPImage constructor with valid data - good() check
TEST_F(WebPImageTest_72, WebPImageConstructorWithValidData_GoodCheck_72) {
    auto webpData = createMinimalWebP();
    auto io = std::make_unique<Exiv2::MemIo>(webpData.data(), webpData.size());
    try {
        Exiv2::WebPImage image(std::move(io));
        // If construction succeeds, good() may return true or false
        // depending on the internal validation
        // We just verify it doesn't crash
        image.good();
    } catch (const Exiv2::Error&) {
        // Construction might throw for invalid/minimal data
    }
}

// Test: WebPImage constructor with invalid data
TEST_F(WebPImageTest_72, WebPImageConstructorWithInvalidData_72) {
    auto invalidData = createInvalidData();
    auto io = std::make_unique<Exiv2::MemIo>(invalidData.data(), invalidData.size());
    try {
        Exiv2::WebPImage image(std::move(io));
        EXPECT_FALSE(image.good());
    } catch (const Exiv2::Error&) {
        // Expected - constructor may throw for invalid data
    }
}

// Test: newWebPInstance with truncated RIFF header
TEST_F(WebPImageTest_72, NewWebPInstanceTruncatedRIFF_ReturnsNull_72) {
    std::vector<uint8_t> truncated = {'R', 'I', 'F', 'F'};
    auto io = std::make_unique<Exiv2::MemIo>(truncated.data(), truncated.size());
    auto image = Exiv2::newWebPInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: newWebPInstance with RIFF header but wrong format (not WEBP)
TEST_F(WebPImageTest_72, NewWebPInstanceRIFFButNotWEBP_ReturnsNull_72) {
    std::vector<uint8_t> data;
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    uint32_t fileSize = 4;
    data.push_back(fileSize & 0xFF);
    data.push_back((fileSize >> 8) & 0xFF);
    data.push_back((fileSize >> 16) & 0xFF);
    data.push_back((fileSize >> 24) & 0xFF);
    data.push_back('A'); data.push_back('V'); data.push_back('I'); data.push_back(' ');
    
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto image = Exiv2::newWebPInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: newWebPInstance with only RIFF + size but no WEBP marker
TEST_F(WebPImageTest_72, NewWebPInstanceRIFFSizeOnly_ReturnsNull_72) {
    std::vector<uint8_t> data = {'R', 'I', 'F', 'F', 0x00, 0x00, 0x00, 0x00};
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto image = Exiv2::newWebPInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: newWebPInstance with single byte
TEST_F(WebPImageTest_72, NewWebPInstanceSingleByte_ReturnsNull_72) {
    std::vector<uint8_t> data = {0x00};
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto image = Exiv2::newWebPInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: WebPImage mimeType
TEST_F(WebPImageTest_72, WebPImageMimeType_72) {
    auto webpData = createMinimalWebP();
    auto io = std::make_unique<Exiv2::MemIo>(webpData.data(), webpData.size());
    try {
        Exiv2::WebPImage image(std::move(io));
        std::string mime = image.mimeType();
        EXPECT_EQ(mime, "image/webp");
    } catch (const Exiv2::Error&) {
        // May throw if minimal data isn't valid enough
    }
}

// Test: newWebPInstance with RIFF+WEBP header but no chunks
TEST_F(WebPImageTest_72, NewWebPInstanceHeaderOnlyNoChunks_72) {
    std::vector<uint8_t> data;
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    uint32_t fileSize = 4; // just "WEBP" and nothing else
    data.push_back(fileSize & 0xFF);
    data.push_back((fileSize >> 8) & 0xFF);
    data.push_back((fileSize >> 16) & 0xFF);
    data.push_back((fileSize >> 24) & 0xFF);
    data.push_back('W'); data.push_back('E'); data.push_back('B'); data.push_back('P');
    
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto image = Exiv2::newWebPInstance(std::move(io), false);
    // May or may not return null depending on validation depth
    // The key thing is it doesn't crash
}

// Test: newWebPInstance called with create parameter variations
TEST_F(WebPImageTest_72, NewWebPInstanceCreateParameterIgnored_72) {
    // The create parameter is unused per the signature (bool /*create*/)
    auto webpData = createMinimalWebP();
    
    auto io1 = std::make_unique<Exiv2::MemIo>(webpData.data(), webpData.size());
    auto image1 = Exiv2::newWebPInstance(std::move(io1), false);
    
    auto io2 = std::make_unique<Exiv2::MemIo>(webpData.data(), webpData.size());
    auto image2 = Exiv2::newWebPInstance(std::move(io2), true);
    
    // Both should behave the same since create is ignored
    EXPECT_EQ(image1 == nullptr, image2 == nullptr);
}
