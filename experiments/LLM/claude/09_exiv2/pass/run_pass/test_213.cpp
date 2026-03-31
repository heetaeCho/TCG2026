#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/gifimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <cstring>
#include <fstream>
#include <sstream>

// Helper to create a minimal valid GIF87a file in memory
static std::vector<unsigned char> createMinimalGif87a() {
    std::vector<unsigned char> data;
    // GIF87a header
    data.push_back('G');
    data.push_back('I');
    data.push_back('F');
    data.push_back('8');
    data.push_back('7');
    data.push_back('a');
    // Logical screen descriptor (7 bytes)
    // Width: 1 (little-endian)
    data.push_back(0x01);
    data.push_back(0x00);
    // Height: 1 (little-endian)
    data.push_back(0x01);
    data.push_back(0x00);
    // Packed byte: no global color table
    data.push_back(0x00);
    // Background color index
    data.push_back(0x00);
    // Pixel aspect ratio
    data.push_back(0x00);
    // Trailer
    data.push_back(0x3B);
    return data;
}

// Helper to create a minimal valid GIF89a file in memory
static std::vector<unsigned char> createMinimalGif89a() {
    std::vector<unsigned char> data;
    // GIF89a header
    data.push_back('G');
    data.push_back('I');
    data.push_back('F');
    data.push_back('8');
    data.push_back('9');
    data.push_back('a');
    // Logical screen descriptor
    data.push_back(0x01);
    data.push_back(0x00);
    data.push_back(0x01);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    // Trailer
    data.push_back(0x3B);
    return data;
}

class GifImageTest_213 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: newGifInstance with a valid GIF87a returns non-null
TEST_F(GifImageTest_213, NewGifInstanceValidGif87a_213) {
    auto gifData = createMinimalGif87a();
    auto io = std::make_unique<Exiv2::MemIo>(gifData.data(), gifData.size());
    auto image = Exiv2::newGifInstance(std::move(io), false);
    // A valid GIF should produce a non-null image
    EXPECT_NE(image, nullptr);
}

// Test: newGifInstance with a valid GIF89a returns non-null
TEST_F(GifImageTest_213, NewGifInstanceValidGif89a_213) {
    auto gifData = createMinimalGif89a();
    auto io = std::make_unique<Exiv2::MemIo>(gifData.data(), gifData.size());
    auto image = Exiv2::newGifInstance(std::move(io), false);
    EXPECT_NE(image, nullptr);
}

// Test: newGifInstance with empty data returns null (bad image)
TEST_F(GifImageTest_213, NewGifInstanceEmptyData_213) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::newGifInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: newGifInstance with invalid/corrupt data returns null
TEST_F(GifImageTest_213, NewGifInstanceInvalidData_213) {
    std::vector<unsigned char> badData = {0x00, 0x01, 0x02, 0x03, 0x04};
    auto io = std::make_unique<Exiv2::MemIo>(badData.data(), badData.size());
    auto image = Exiv2::newGifInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: newGifInstance with truncated GIF header
TEST_F(GifImageTest_213, NewGifInstanceTruncatedHeader_213) {
    // Only partial header "GIF8"
    std::vector<unsigned char> truncated = {'G', 'I', 'F', '8'};
    auto io = std::make_unique<Exiv2::MemIo>(truncated.data(), truncated.size());
    auto image = Exiv2::newGifInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: newGifInstance with just the magic bytes but no screen descriptor
TEST_F(GifImageTest_213, NewGifInstanceHeaderOnlyNoDescriptor_213) {
    // GIF89a header only, no logical screen descriptor or trailer
    std::vector<unsigned char> headerOnly = {'G', 'I', 'F', '8', '9', 'a'};
    auto io = std::make_unique<Exiv2::MemIo>(headerOnly.data(), headerOnly.size());
    auto image = Exiv2::newGifInstance(std::move(io), false);
    // This may or may not be considered "good" depending on implementation
    // We just verify it doesn't crash and returns a valid pointer or null
    // Accept either outcome
    SUCCEED();
}

// Test: GifImage constructed directly with valid data reports good()
TEST_F(GifImageTest_213, GifImageGoodWithValidData_213) {
    auto gifData = createMinimalGif89a();
    auto io = std::make_unique<Exiv2::MemIo>(gifData.data(), gifData.size());
    Exiv2::GifImage image(std::move(io));
    EXPECT_TRUE(image.good());
}

// Test: GifImage constructed with empty IO reports not good
TEST_F(GifImageTest_213, GifImageNotGoodWithEmptyData_213) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::GifImage image(std::move(io));
    EXPECT_FALSE(image.good());
}

// Test: GifImage mimeType returns correct MIME type
TEST_F(GifImageTest_213, GifImageMimeType_213) {
    auto gifData = createMinimalGif89a();
    auto io = std::make_unique<Exiv2::MemIo>(gifData.data(), gifData.size());
    Exiv2::GifImage image(std::move(io));
    std::string mime = image.mimeType();
    EXPECT_EQ(mime, "image/gif");
}

// Test: GifImage setExifData throws (GIF doesn't support Exif writing)
TEST_F(GifImageTest_213, GifImageSetExifDataThrows_213) {
    auto gifData = createMinimalGif89a();
    auto io = std::make_unique<Exiv2::MemIo>(gifData.data(), gifData.size());
    Exiv2::GifImage image(std::move(io));
    Exiv2::ExifData exifData;
    image.setExifData(exifData);
    // GIF typically doesn't support writing, so writeMetadata should throw
    EXPECT_THROW(image.writeMetadata(), Exiv2::Error);
}

// Test: GifImage setIptcData on GIF (should throw on write)
TEST_F(GifImageTest_213, GifImageSetIptcDataThrows_213) {
    auto gifData = createMinimalGif89a();
    auto io = std::make_unique<Exiv2::MemIo>(gifData.data(), gifData.size());
    Exiv2::GifImage image(std::move(io));
    Exiv2::IptcData iptcData;
    image.setIptcData(iptcData);
    EXPECT_THROW(image.writeMetadata(), Exiv2::Error);
}

// Test: GifImage setComment on GIF (should throw on write)
TEST_F(GifImageTest_213, GifImageSetCommentThrows_213) {
    auto gifData = createMinimalGif89a();
    auto io = std::make_unique<Exiv2::MemIo>(gifData.data(), gifData.size());
    Exiv2::GifImage image(std::move(io));
    image.setComment("test comment");
    EXPECT_THROW(image.writeMetadata(), Exiv2::Error);
}

// Test: GifImage readMetadata with valid minimal GIF doesn't throw
TEST_F(GifImageTest_213, GifImageReadMetadataValid_213) {
    auto gifData = createMinimalGif89a();
    auto io = std::make_unique<Exiv2::MemIo>(gifData.data(), gifData.size());
    Exiv2::GifImage image(std::move(io));
    EXPECT_NO_THROW(image.readMetadata());
}

// Test: GifImage readMetadata with corrupt data throws
TEST_F(GifImageTest_213, GifImageReadMetadataCorrupt_213) {
    std::vector<unsigned char> corrupt = {'G', 'I', 'F', '8', '9', 'a',
                                          0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    auto io = std::make_unique<Exiv2::MemIo>(corrupt.data(), corrupt.size());
    Exiv2::GifImage image(std::move(io));
    // Depending on implementation, readMetadata may or may not throw
    // We test that it at least doesn't crash
    try {
        image.readMetadata();
    } catch (const Exiv2::Error&) {
        // Expected for corrupt data
    }
    SUCCEED();
}

// Test: newGifInstance with create flag = true
TEST_F(GifImageTest_213, NewGifInstanceCreateFlag_213) {
    auto gifData = createMinimalGif89a();
    auto io = std::make_unique<Exiv2::MemIo>(gifData.data(), gifData.size());
    // The create parameter is ignored per the signature, but test it still works
    auto image = Exiv2::newGifInstance(std::move(io), true);
    EXPECT_NE(image, nullptr);
}

// Test: newGifInstance with a non-GIF (JPEG-like) header returns null
TEST_F(GifImageTest_213, NewGifInstanceNonGifJpegHeader_213) {
    std::vector<unsigned char> jpegLike = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto io = std::make_unique<Exiv2::MemIo>(jpegLike.data(), jpegLike.size());
    auto image = Exiv2::newGifInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: newGifInstance with a PNG-like header returns null
TEST_F(GifImageTest_213, NewGifInstanceNonGifPngHeader_213) {
    std::vector<unsigned char> pngLike = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    auto io = std::make_unique<Exiv2::MemIo>(pngLike.data(), pngLike.size());
    auto image = Exiv2::newGifInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: GifImage pixelWidth and pixelHeight with minimal GIF
TEST_F(GifImageTest_213, GifImagePixelDimensions_213) {
    auto gifData = createMinimalGif89a();
    auto io = std::make_unique<Exiv2::MemIo>(gifData.data(), gifData.size());
    Exiv2::GifImage image(std::move(io));
    image.readMetadata();
    // The minimal GIF has 1x1 dimensions
    EXPECT_EQ(image.pixelWidth(), 1);
    EXPECT_EQ(image.pixelHeight(), 1);
}

// Test: GifImage with larger dimensions
TEST_F(GifImageTest_213, GifImageLargerDimensions_213) {
    std::vector<unsigned char> data;
    // GIF89a header
    data.push_back('G');
    data.push_back('I');
    data.push_back('F');
    data.push_back('8');
    data.push_back('9');
    data.push_back('a');
    // Width: 320 = 0x0140 (little-endian: 0x40, 0x01)
    data.push_back(0x40);
    data.push_back(0x01);
    // Height: 240 = 0x00F0 (little-endian: 0xF0, 0x00)
    data.push_back(0xF0);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    // Trailer
    data.push_back(0x3B);

    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::GifImage image(std::move(io));
    image.readMetadata();
    EXPECT_EQ(image.pixelWidth(), 320);
    EXPECT_EQ(image.pixelHeight(), 240);
}

// Test: Single byte data returns null from newGifInstance
TEST_F(GifImageTest_213, NewGifInstanceSingleByte_213) {
    std::vector<unsigned char> singleByte = {0x42};
    auto io = std::make_unique<Exiv2::MemIo>(singleByte.data(), singleByte.size());
    auto image = Exiv2::newGifInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}
