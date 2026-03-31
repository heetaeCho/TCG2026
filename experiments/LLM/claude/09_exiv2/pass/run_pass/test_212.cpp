#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/gifimage.hpp>
#include <exiv2/error.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <memory>
#include <sstream>

namespace {

// Helper to create a minimal valid GIF image in memory
std::vector<unsigned char> createMinimalGif89a() {
    // GIF89a header + minimal content
    std::vector<unsigned char> gif = {
        // Header: GIF89a
        0x47, 0x49, 0x46, 0x38, 0x39, 0x61,
        // Logical Screen Descriptor
        0x01, 0x00, // Width: 1
        0x01, 0x00, // Height: 1
        0x00,       // GCT Flag etc
        0x00,       // Background Color Index
        0x00,       // Pixel Aspect Ratio
        // Image Descriptor
        0x2C,
        0x00, 0x00, // Left
        0x00, 0x00, // Top
        0x01, 0x00, // Width: 1
        0x01, 0x00, // Height: 1
        0x00,       // Packed byte
        // LZW Minimum Code Size
        0x02,
        // Sub-block
        0x02, 0x4C, 0x01,
        // Block terminator
        0x00,
        // Trailer
        0x3B
    };
    return gif;
}

std::vector<unsigned char> createMinimalGif87a() {
    std::vector<unsigned char> gif = {
        // Header: GIF87a
        0x47, 0x49, 0x46, 0x38, 0x37, 0x61,
        // Logical Screen Descriptor
        0x01, 0x00,
        0x01, 0x00,
        0x00,
        0x00,
        0x00,
        // Image Descriptor
        0x2C,
        0x00, 0x00,
        0x00, 0x00,
        0x01, 0x00,
        0x01, 0x00,
        0x00,
        // LZW Minimum Code Size
        0x02,
        // Sub-block
        0x02, 0x4C, 0x01,
        // Block terminator
        0x00,
        // Trailer
        0x3B
    };
    return gif;
}

class GifImageTest_212 : public ::testing::Test {
protected:
    std::unique_ptr<Exiv2::GifImage> createGifImage(const std::vector<unsigned char>& data) {
        auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
        return std::make_unique<Exiv2::GifImage>(std::move(io));
    }
};

// Test that writeMetadata throws an exception since GIF writing is unsupported
TEST_F(GifImageTest_212, WriteMetadataThrowsError_212) {
    auto gifData = createMinimalGif89a();
    auto gifImage = createGifImage(gifData);
    
    try {
        gifImage->writeMetadata();
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerWritingImageFormatUnsupported);
    } catch (...) {
        FAIL() << "Expected Exiv2::Error but got a different exception";
    }
}

// Test that mimeType returns the correct MIME type for GIF
TEST_F(GifImageTest_212, MimeTypeReturnsImageGif_212) {
    auto gifData = createMinimalGif89a();
    auto gifImage = createGifImage(gifData);
    
    EXPECT_EQ(gifImage->mimeType(), "image/gif");
}

// Test that readMetadata works on a valid GIF89a image without throwing
TEST_F(GifImageTest_212, ReadMetadataValidGif89a_212) {
    auto gifData = createMinimalGif89a();
    auto gifImage = createGifImage(gifData);
    
    EXPECT_NO_THROW(gifImage->readMetadata());
}

// Test that readMetadata works on a valid GIF87a image without throwing
TEST_F(GifImageTest_212, ReadMetadataValidGif87a_212) {
    auto gifData = createMinimalGif87a();
    auto gifImage = createGifImage(gifData);
    
    EXPECT_NO_THROW(gifImage->readMetadata());
}

// Test that setExifData throws since GIF doesn't support EXIF
TEST_F(GifImageTest_212, SetExifDataThrows_212) {
    auto gifData = createMinimalGif89a();
    auto gifImage = createGifImage(gifData);
    
    Exiv2::ExifData exifData;
    try {
        gifImage->setExifData(exifData);
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerInvalidSettingForImage);
    } catch (...) {
        FAIL() << "Expected Exiv2::Error but got a different exception";
    }
}

// Test that setIptcData throws since GIF doesn't support IPTC
TEST_F(GifImageTest_212, SetIptcDataThrows_212) {
    auto gifData = createMinimalGif89a();
    auto gifImage = createGifImage(gifData);
    
    Exiv2::IptcData iptcData;
    try {
        gifImage->setIptcData(iptcData);
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerInvalidSettingForImage);
    } catch (...) {
        FAIL() << "Expected Exiv2::Error but got a different exception";
    }
}

// Test that setComment throws since GIF doesn't support comments through this interface
TEST_F(GifImageTest_212, SetCommentThrows_212) {
    auto gifData = createMinimalGif89a();
    auto gifImage = createGifImage(gifData);
    
    try {
        gifImage->setComment("test comment");
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerInvalidSettingForImage);
    } catch (...) {
        FAIL() << "Expected Exiv2::Error but got a different exception";
    }
}

// Test readMetadata on invalid/corrupt data
TEST_F(GifImageTest_212, ReadMetadataInvalidDataThrows_212) {
    // Not a valid GIF at all
    std::vector<unsigned char> invalidData = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
    auto io = std::make_unique<Exiv2::MemIo>(invalidData.data(), invalidData.size());
    auto gifImage = std::make_unique<Exiv2::GifImage>(std::move(io));
    
    EXPECT_THROW(gifImage->readMetadata(), Exiv2::Error);
}

// Test readMetadata on empty data
TEST_F(GifImageTest_212, ReadMetadataEmptyDataThrows_212) {
    std::vector<unsigned char> emptyData;
    auto io = std::make_unique<Exiv2::MemIo>(emptyData.data(), emptyData.size());
    auto gifImage = std::make_unique<Exiv2::GifImage>(std::move(io));
    
    EXPECT_THROW(gifImage->readMetadata(), Exiv2::Error);
}

// Test readMetadata with truncated GIF header
TEST_F(GifImageTest_212, ReadMetadataTruncatedHeaderThrows_212) {
    // Only the first 3 bytes of a GIF header
    std::vector<unsigned char> truncated = {0x47, 0x49, 0x46};
    auto io = std::make_unique<Exiv2::MemIo>(truncated.data(), truncated.size());
    auto gifImage = std::make_unique<Exiv2::GifImage>(std::move(io));
    
    EXPECT_THROW(gifImage->readMetadata(), Exiv2::Error);
}

// Test that pixel width and height are correctly read from a valid GIF
TEST_F(GifImageTest_212, PixelDimensionsAfterReadMetadata_212) {
    auto gifData = createMinimalGif89a();
    auto gifImage = createGifImage(gifData);
    
    gifImage->readMetadata();
    
    EXPECT_EQ(gifImage->pixelWidth(), 1);
    EXPECT_EQ(gifImage->pixelHeight(), 1);
}

// Test readMetadata with wrong version string (e.g., GIF90a)
TEST_F(GifImageTest_212, ReadMetadataWrongVersionThrows_212) {
    auto gifData = createMinimalGif89a();
    // Corrupt the version: change '9' (0x39) to '0' (0x30) -> GIF80a
    gifData[4] = 0x30;
    auto gifImage = createGifImage(gifData);
    
    EXPECT_THROW(gifImage->readMetadata(), Exiv2::Error);
}

// Test that writeMetadata throws even after a successful readMetadata
TEST_F(GifImageTest_212, WriteMetadataAfterReadStillThrows_212) {
    auto gifData = createMinimalGif89a();
    auto gifImage = createGifImage(gifData);
    
    EXPECT_NO_THROW(gifImage->readMetadata());
    EXPECT_THROW(gifImage->writeMetadata(), Exiv2::Error);
}

// Test GifImage with GIF header only (no image data, just header + screen descriptor)
TEST_F(GifImageTest_212, ReadMetadataHeaderOnlyMayThrow_212) {
    std::vector<unsigned char> headerOnly = {
        0x47, 0x49, 0x46, 0x38, 0x39, 0x61,  // GIF89a
        0x0A, 0x00, // Width: 10
        0x0A, 0x00, // Height: 10
        0x00,       // GCT Flag
        0x00,       // Background
        0x00,       // Pixel Aspect
        0x3B        // Trailer
    };
    auto gifImage = createGifImage(headerOnly);
    
    // This should either succeed or throw a well-defined error
    try {
        gifImage->readMetadata();
        // If it succeeds, dimensions should be readable
        EXPECT_EQ(gifImage->pixelWidth(), 10);
        EXPECT_EQ(gifImage->pixelHeight(), 10);
    } catch (const Exiv2::Error&) {
        // Acceptable - some implementations may require image data
    }
}

}  // namespace
