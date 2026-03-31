#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/gifimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace Exiv2;

// Helper function to create a valid GIF87a file in memory
static std::vector<byte> createValidGif87a(uint16_t width = 100, uint16_t height = 80) {
    std::vector<byte> data;
    // GIF87a header
    data.push_back('G');
    data.push_back('I');
    data.push_back('F');
    data.push_back('8');
    data.push_back('7');
    data.push_back('a');
    // Logical Screen Descriptor: width (little-endian)
    data.push_back(static_cast<byte>(width & 0xFF));
    data.push_back(static_cast<byte>((width >> 8) & 0xFF));
    // Logical Screen Descriptor: height (little-endian)
    data.push_back(static_cast<byte>(height & 0xFF));
    data.push_back(static_cast<byte>((height >> 8) & 0xFF));
    // Packed field, background color index, pixel aspect ratio
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    // Trailer
    data.push_back(0x3B);
    return data;
}

// Helper function to create a valid GIF89a file in memory
static std::vector<byte> createValidGif89a(uint16_t width = 200, uint16_t height = 150) {
    std::vector<byte> data;
    // GIF89a header
    data.push_back('G');
    data.push_back('I');
    data.push_back('F');
    data.push_back('8');
    data.push_back('9');
    data.push_back('a');
    // Logical Screen Descriptor: width (little-endian)
    data.push_back(static_cast<byte>(width & 0xFF));
    data.push_back(static_cast<byte>((width >> 8) & 0xFF));
    // Logical Screen Descriptor: height (little-endian)
    data.push_back(static_cast<byte>(height & 0xFF));
    data.push_back(static_cast<byte>((height >> 8) & 0xFF));
    // Packed field, background color index, pixel aspect ratio
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    // Trailer
    data.push_back(0x3B);
    return data;
}

// Helper to write data to a temp file and return the path
static std::string writeTempFile(const std::vector<byte>& data, const std::string& suffix = ".gif") {
    std::string path = std::tmpnam(nullptr) + suffix;
    std::ofstream ofs(path, std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
    ofs.close();
    return path;
}

class GifImageTest_211 : public ::testing::Test {
protected:
    void TearDown() override {
        for (const auto& f : tempFiles_) {
            std::remove(f.c_str());
        }
    }

    std::string createTempFile(const std::vector<byte>& data) {
        std::string path = writeTempFile(data);
        tempFiles_.push_back(path);
        return path;
    }

    std::vector<std::string> tempFiles_;
};

// Test: Valid GIF87a file reads metadata successfully and reports correct dimensions
TEST_F(GifImageTest_211, ReadMetadata_ValidGif87a_211) {
    uint16_t expectedWidth = 320;
    uint16_t expectedHeight = 240;
    auto data = createValidGif87a(expectedWidth, expectedHeight);
    std::string path = createTempFile(data);

    auto io = std::make_unique<FileIo>(path);
    GifImage gif(std::move(io));

    ASSERT_NO_THROW(gif.readMetadata());
    EXPECT_EQ(gif.pixelWidth(), expectedWidth);
    EXPECT_EQ(gif.pixelHeight(), expectedHeight);
}

// Test: Valid GIF89a file reads metadata successfully and reports correct dimensions
TEST_F(GifImageTest_211, ReadMetadata_ValidGif89a_211) {
    uint16_t expectedWidth = 640;
    uint16_t expectedHeight = 480;
    auto data = createValidGif89a(expectedWidth, expectedHeight);
    std::string path = createTempFile(data);

    auto io = std::make_unique<FileIo>(path);
    GifImage gif(std::move(io));

    ASSERT_NO_THROW(gif.readMetadata());
    EXPECT_EQ(gif.pixelWidth(), expectedWidth);
    EXPECT_EQ(gif.pixelHeight(), expectedHeight);
}

// Test: Reading metadata from a non-existent file throws an error
TEST_F(GifImageTest_211, ReadMetadata_NonExistentFile_ThrowsError_211) {
    auto io = std::make_unique<FileIo>("/nonexistent/path/to/file.gif");
    GifImage gif(std::move(io));

    EXPECT_THROW(gif.readMetadata(), Error);
}

// Test: Reading metadata from a file that is not a GIF throws an error
TEST_F(GifImageTest_211, ReadMetadata_NotAGifFile_ThrowsError_211) {
    std::vector<byte> data = {'P', 'N', 'G', ' ', 'n', 'o', 't', ' ', 'g', 'i', 'f',
                              0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::string path = createTempFile(data);

    auto io = std::make_unique<FileIo>(path);
    GifImage gif(std::move(io));

    EXPECT_THROW(gif.readMetadata(), Error);
}

// Test: Reading metadata from an empty file throws an error
TEST_F(GifImageTest_211, ReadMetadata_EmptyFile_ThrowsError_211) {
    std::vector<byte> data;
    std::string path = createTempFile(data);

    auto io = std::make_unique<FileIo>(path);
    GifImage gif(std::move(io));

    EXPECT_THROW(gif.readMetadata(), Error);
}

// Test: GIF with minimum dimensions (1x1)
TEST_F(GifImageTest_211, ReadMetadata_MinimumDimensions_211) {
    auto data = createValidGif87a(1, 1);
    std::string path = createTempFile(data);

    auto io = std::make_unique<FileIo>(path);
    GifImage gif(std::move(io));

    ASSERT_NO_THROW(gif.readMetadata());
    EXPECT_EQ(gif.pixelWidth(), 1u);
    EXPECT_EQ(gif.pixelHeight(), 1u);
}

// Test: GIF with maximum 16-bit dimensions (65535x65535)
TEST_F(GifImageTest_211, ReadMetadata_MaxDimensions_211) {
    auto data = createValidGif87a(65535, 65535);
    std::string path = createTempFile(data);

    auto io = std::make_unique<FileIo>(path);
    GifImage gif(std::move(io));

    ASSERT_NO_THROW(gif.readMetadata());
    EXPECT_EQ(gif.pixelWidth(), 65535u);
    EXPECT_EQ(gif.pixelHeight(), 65535u);
}

// Test: GIF with zero dimensions
TEST_F(GifImageTest_211, ReadMetadata_ZeroDimensions_211) {
    auto data = createValidGif87a(0, 0);
    std::string path = createTempFile(data);

    auto io = std::make_unique<FileIo>(path);
    GifImage gif(std::move(io));

    ASSERT_NO_THROW(gif.readMetadata());
    EXPECT_EQ(gif.pixelWidth(), 0u);
    EXPECT_EQ(gif.pixelHeight(), 0u);
}

// Test: MIME type is "image/gif"
TEST_F(GifImageTest_211, MimeType_ReturnsImageGif_211) {
    auto data = createValidGif87a();
    std::string path = createTempFile(data);

    auto io = std::make_unique<FileIo>(path);
    GifImage gif(std::move(io));

    EXPECT_EQ(gif.mimeType(), "image/gif");
}

// Test: writeMetadata throws (GIF writing is not supported)
TEST_F(GifImageTest_211, WriteMetadata_ThrowsError_211) {
    auto data = createValidGif87a();
    std::string path = createTempFile(data);

    auto io = std::make_unique<FileIo>(path);
    GifImage gif(std::move(io));

    EXPECT_THROW(gif.writeMetadata(), Error);
}

// Test: setExifData throws (not supported for GIF)
TEST_F(GifImageTest_211, SetExifData_ThrowsError_211) {
    auto data = createValidGif87a();
    std::string path = createTempFile(data);

    auto io = std::make_unique<FileIo>(path);
    GifImage gif(std::move(io));

    ExifData exifData;
    EXPECT_THROW(gif.setExifData(exifData), Error);
}

// Test: setIptcData throws (not supported for GIF)
TEST_F(GifImageTest_211, SetIptcData_ThrowsError_211) {
    auto data = createValidGif87a();
    std::string path = createTempFile(data);

    auto io = std::make_unique<FileIo>(path);
    GifImage gif(std::move(io));

    IptcData iptcData;
    EXPECT_THROW(gif.setIptcData(iptcData), Error);
}

// Test: setComment throws (not supported for GIF)
TEST_F(GifImageTest_211, SetComment_ThrowsError_211) {
    auto data = createValidGif87a();
    std::string path = createTempFile(data);

    auto io = std::make_unique<FileIo>(path);
    GifImage gif(std::move(io));

    EXPECT_THROW(gif.setComment("test comment"), Error);
}

// Test: Truncated GIF file (only header, no dimensions)
TEST_F(GifImageTest_211, ReadMetadata_TruncatedFile_OnlyHeader_211) {
    std::vector<byte> data = {'G', 'I', 'F', '8', '9', 'a'};
    std::string path = createTempFile(data);

    auto io = std::make_unique<FileIo>(path);
    GifImage gif(std::move(io));

    // The header is valid but there's no dimension data - should not crash
    // Depending on implementation, it may succeed with 0 dimensions or throw
    try {
        gif.readMetadata();
        // If it doesn't throw, dimensions should be 0 (no data read)
        EXPECT_EQ(gif.pixelWidth(), 0u);
        EXPECT_EQ(gif.pixelHeight(), 0u);
    } catch (const Error&) {
        // Also acceptable if it throws
        SUCCEED();
    }
}

// Test: File with invalid GIF version
TEST_F(GifImageTest_211, ReadMetadata_InvalidGifVersion_ThrowsError_211) {
    std::vector<byte> data = {'G', 'I', 'F', '8', '0', 'a',
                              0x40, 0x01, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x3B};
    std::string path = createTempFile(data);

    auto io = std::make_unique<FileIo>(path);
    GifImage gif(std::move(io));

    EXPECT_THROW(gif.readMetadata(), Error);
}

// Test: MemIo-based GIF reading with valid GIF89a
TEST_F(GifImageTest_211, ReadMetadata_MemIo_ValidGif89a_211) {
    uint16_t expectedWidth = 512;
    uint16_t expectedHeight = 384;
    auto data = createValidGif89a(expectedWidth, expectedHeight);

    auto io = std::make_unique<MemIo>(data.data(), data.size());
    GifImage gif(std::move(io));

    ASSERT_NO_THROW(gif.readMetadata());
    EXPECT_EQ(gif.pixelWidth(), expectedWidth);
    EXPECT_EQ(gif.pixelHeight(), expectedHeight);
}

// Test: MemIo with empty data throws error
TEST_F(GifImageTest_211, ReadMetadata_MemIo_EmptyData_ThrowsError_211) {
    auto io = std::make_unique<MemIo>();
    GifImage gif(std::move(io));

    EXPECT_THROW(gif.readMetadata(), Error);
}

// Test: MemIo with non-GIF data throws error
TEST_F(GifImageTest_211, ReadMetadata_MemIo_NonGifData_ThrowsError_211) {
    std::vector<byte> data = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10}; // JPEG-like
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    GifImage gif(std::move(io));

    EXPECT_THROW(gif.readMetadata(), Error);
}

// Test: Clearing metadata after reading
TEST_F(GifImageTest_211, ReadMetadata_ClearsExistingMetadata_211) {
    auto data = createValidGif89a(100, 100);
    std::string path = createTempFile(data);

    auto io = std::make_unique<FileIo>(path);
    GifImage gif(std::move(io));

    // Read metadata twice - should work without issues
    ASSERT_NO_THROW(gif.readMetadata());
    ASSERT_NO_THROW(gif.readMetadata());
    EXPECT_EQ(gif.pixelWidth(), 100u);
    EXPECT_EQ(gif.pixelHeight(), 100u);
}

// Test: Asymmetric dimensions
TEST_F(GifImageTest_211, ReadMetadata_AsymmetricDimensions_211) {
    uint16_t expectedWidth = 1;
    uint16_t expectedHeight = 65535;
    auto data = createValidGif87a(expectedWidth, expectedHeight);
    std::string path = createTempFile(data);

    auto io = std::make_unique<FileIo>(path);
    GifImage gif(std::move(io));

    ASSERT_NO_THROW(gif.readMetadata());
    EXPECT_EQ(gif.pixelWidth(), expectedWidth);
    EXPECT_EQ(gif.pixelHeight(), expectedHeight);
}

// Test: good() returns true for valid GIF
TEST_F(GifImageTest_211, Good_ValidGif_ReturnsTrue_211) {
    auto data = createValidGif87a();
    std::string path = createTempFile(data);

    auto io = std::make_unique<FileIo>(path);
    GifImage gif(std::move(io));

    EXPECT_TRUE(gif.good());
}

// Test: Partial header (less than 6 bytes)
TEST_F(GifImageTest_211, ReadMetadata_PartialHeader_ThrowsError_211) {
    std::vector<byte> data = {'G', 'I', 'F'};
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    GifImage gif(std::move(io));

    EXPECT_THROW(gif.readMetadata(), Error);
}
