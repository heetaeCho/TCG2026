#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/gifimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>
#include <fstream>
#include <cstring>

namespace {

// Helper to create a minimal valid GIF87a file in memory
std::vector<unsigned char> createMinimalGif87a() {
    std::vector<unsigned char> data;
    // Header: GIF87a
    data.push_back('G'); data.push_back('I'); data.push_back('F');
    data.push_back('8'); data.push_back('7'); data.push_back('a');
    // Logical Screen Descriptor
    // Width: 1 (little-endian)
    data.push_back(0x01); data.push_back(0x00);
    // Height: 1 (little-endian)
    data.push_back(0x01); data.push_back(0x00);
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
std::vector<unsigned char> createMinimalGif89a() {
    std::vector<unsigned char> data;
    // Header: GIF89a
    data.push_back('G'); data.push_back('I'); data.push_back('F');
    data.push_back('8'); data.push_back('9'); data.push_back('a');
    // Logical Screen Descriptor
    data.push_back(0x01); data.push_back(0x00); // width
    data.push_back(0x01); data.push_back(0x00); // height
    data.push_back(0x00); // packed
    data.push_back(0x00); // bg color
    data.push_back(0x00); // aspect ratio
    // Trailer
    data.push_back(0x3B);
    return data;
}

class GifImageTest_210 : public ::testing::Test {
protected:
    std::unique_ptr<Exiv2::GifImage> createGifImageFromData(const std::vector<unsigned char>& data) {
        auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
        return std::make_unique<Exiv2::GifImage>(std::move(io));
    }
};

// Test that mimeType returns the correct MIME type for GIF images
TEST_F(GifImageTest_210, MimeTypeReturnsImageGif_210) {
    auto data = createMinimalGif89a();
    auto gif = createGifImageFromData(data);
    EXPECT_EQ(gif->mimeType(), "image/gif");
}

// Test that mimeType is consistent across multiple calls
TEST_F(GifImageTest_210, MimeTypeIsConsistent_210) {
    auto data = createMinimalGif89a();
    auto gif = createGifImageFromData(data);
    std::string first = gif->mimeType();
    std::string second = gif->mimeType();
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, "image/gif");
}

// Test that setExifData throws or is a no-op (GIF doesn't support EXIF)
TEST_F(GifImageTest_210, SetExifDataThrowsOrNoOp_210) {
    auto data = createMinimalGif89a();
    auto gif = createGifImageFromData(data);
    Exiv2::ExifData exifData;
    EXPECT_THROW(gif->setExifData(exifData), Exiv2::Error);
}

// Test that setIptcData throws or is a no-op (GIF doesn't support IPTC)
TEST_F(GifImageTest_210, SetIptcDataThrowsOrNoOp_210) {
    auto data = createMinimalGif89a();
    auto gif = createGifImageFromData(data);
    Exiv2::IptcData iptcData;
    EXPECT_THROW(gif->setIptcData(iptcData), Exiv2::Error);
}

// Test that setComment throws or is a no-op (GIF doesn't support comments via this interface)
TEST_F(GifImageTest_210, SetCommentThrowsOrNoOp_210) {
    auto data = createMinimalGif89a();
    auto gif = createGifImageFromData(data);
    EXPECT_THROW(gif->setComment("test comment"), Exiv2::Error);
}

// Test that writeMetadata throws (GIF writing is not supported)
TEST_F(GifImageTest_210, WriteMetadataThrows_210) {
    auto data = createMinimalGif89a();
    auto gif = createGifImageFromData(data);
    EXPECT_THROW(gif->writeMetadata(), Exiv2::Error);
}

// Test readMetadata with a valid GIF87a file
TEST_F(GifImageTest_210, ReadMetadataGif87a_210) {
    auto data = createMinimalGif87a();
    auto gif = createGifImageFromData(data);
    EXPECT_NO_THROW(gif->readMetadata());
}

// Test readMetadata with a valid GIF89a file
TEST_F(GifImageTest_210, ReadMetadataGif89a_210) {
    auto data = createMinimalGif89a();
    auto gif = createGifImageFromData(data);
    EXPECT_NO_THROW(gif->readMetadata());
}

// Test readMetadata with empty data (should throw)
TEST_F(GifImageTest_210, ReadMetadataEmptyDataThrows_210) {
    std::vector<unsigned char> emptyData;
    auto io = std::make_unique<Exiv2::MemIo>(emptyData.data(), emptyData.size());
    auto gif = std::make_unique<Exiv2::GifImage>(std::move(io));
    EXPECT_THROW(gif->readMetadata(), Exiv2::Error);
}

// Test readMetadata with invalid/corrupt header
TEST_F(GifImageTest_210, ReadMetadataInvalidHeaderThrows_210) {
    std::vector<unsigned char> badData = {'N', 'O', 'T', 'G', 'I', 'F'};
    auto gif = createGifImageFromData(badData);
    EXPECT_THROW(gif->readMetadata(), Exiv2::Error);
}

// Test readMetadata with truncated GIF header (too short)
TEST_F(GifImageTest_210, ReadMetadataTruncatedHeaderThrows_210) {
    std::vector<unsigned char> truncated = {'G', 'I', 'F'};
    auto gif = createGifImageFromData(truncated);
    EXPECT_THROW(gif->readMetadata(), Exiv2::Error);
}

// Test that pixel width and height are read correctly from a valid GIF
TEST_F(GifImageTest_210, ReadMetadataPixelDimensions_210) {
    auto data = createMinimalGif89a();
    auto gif = createGifImageFromData(data);
    gif->readMetadata();
    EXPECT_EQ(gif->pixelWidth(), 1);
    EXPECT_EQ(gif->pixelHeight(), 1);
}

// Test readMetadata with a GIF that has larger dimensions
TEST_F(GifImageTest_210, ReadMetadataLargerDimensions_210) {
    std::vector<unsigned char> data;
    data.push_back('G'); data.push_back('I'); data.push_back('F');
    data.push_back('8'); data.push_back('9'); data.push_back('a');
    // Width: 320 = 0x0140 (little-endian: 0x40, 0x01)
    data.push_back(0x40); data.push_back(0x01);
    // Height: 240 = 0x00F0 (little-endian: 0xF0, 0x00)
    data.push_back(0xF0); data.push_back(0x00);
    data.push_back(0x00); // packed
    data.push_back(0x00); // bg color
    data.push_back(0x00); // aspect ratio
    data.push_back(0x3B); // trailer
    auto gif = createGifImageFromData(data);
    gif->readMetadata();
    EXPECT_EQ(gif->pixelWidth(), 320);
    EXPECT_EQ(gif->pixelHeight(), 240);
}

// Test readMetadata with header that says GIF but wrong version
TEST_F(GifImageTest_210, ReadMetadataWrongVersionThrows_210) {
    std::vector<unsigned char> data;
    data.push_back('G'); data.push_back('I'); data.push_back('F');
    data.push_back('8'); data.push_back('0'); data.push_back('a');
    // Logical Screen Descriptor
    data.push_back(0x01); data.push_back(0x00);
    data.push_back(0x01); data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x3B);
    auto gif = createGifImageFromData(data);
    EXPECT_THROW(gif->readMetadata(), Exiv2::Error);
}

// Test that GifImage can be constructed with MemIo
TEST_F(GifImageTest_210, ConstructionWithMemIo_210) {
    auto data = createMinimalGif89a();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    EXPECT_NO_THROW(auto gif = std::make_unique<Exiv2::GifImage>(std::move(io)));
}

// Test that after readMetadata, exifData is empty for GIF
TEST_F(GifImageTest_210, ExifDataEmptyAfterRead_210) {
    auto data = createMinimalGif89a();
    auto gif = createGifImageFromData(data);
    gif->readMetadata();
    EXPECT_TRUE(gif->exifData().empty());
}

// Test that after readMetadata, iptcData is empty for GIF
TEST_F(GifImageTest_210, IptcDataEmptyAfterRead_210) {
    auto data = createMinimalGif89a();
    auto gif = createGifImageFromData(data);
    gif->readMetadata();
    EXPECT_TRUE(gif->iptcData().empty());
}

// Test readMetadata with truncated logical screen descriptor
TEST_F(GifImageTest_210, ReadMetadataTruncatedLSD_210) {
    std::vector<unsigned char> data;
    data.push_back('G'); data.push_back('I'); data.push_back('F');
    data.push_back('8'); data.push_back('9'); data.push_back('a');
    // Only partial LSD (missing some bytes)
    data.push_back(0x01);
    auto gif = createGifImageFromData(data);
    EXPECT_THROW(gif->readMetadata(), Exiv2::Error);
}

}  // namespace
