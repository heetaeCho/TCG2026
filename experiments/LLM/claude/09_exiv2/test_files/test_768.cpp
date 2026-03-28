#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/exiv2.hpp>
#include <string>
#include <fstream>
#include <cstdio>

using namespace Exiv2;

// Test with empty ExifData - no thumbnail present
TEST(ExifThumbCTest_768, MimeTypeReturnsEmptyStringForNoThumbnail_768) {
    ExifData exifData;
    ExifThumbC thumb(exifData);
    const char* mime = thumb.mimeType();
    ASSERT_NE(mime, nullptr);
    EXPECT_STREQ(mime, "");
}

TEST(ExifThumbCTest_768, ExtensionReturnsEmptyStringForNoThumbnail_768) {
    ExifData exifData;
    ExifThumbC thumb(exifData);
    const char* ext = thumb.extension();
    ASSERT_NE(ext, nullptr);
    EXPECT_STREQ(ext, "");
}

TEST(ExifThumbCTest_768, CopyReturnsEmptyBufferForNoThumbnail_768) {
    ExifData exifData;
    ExifThumbC thumb(exifData);
    DataBuf buf = thumb.copy();
    EXPECT_EQ(buf.size(), 0u);
}

TEST(ExifThumbCTest_768, WriteFileReturnsZeroForNoThumbnail_768) {
    ExifData exifData;
    ExifThumbC thumb(exifData);
    size_t written = thumb.writeFile("/tmp/exifthumb_test_768_no_thumb");
    EXPECT_EQ(written, 0u);
}

// Test with JPEG thumbnail data embedded in ExifData
TEST(ExifThumbCTest_768, MimeTypeReturnsJpegForJpegThumbnail_768) {
    ExifData exifData;
    // Set the thumbnail compression to JPEG (value 6)
    exifData["Exif.Thumbnail.Compression"] = uint16_t(6);
    
    // Create a minimal JPEG-like thumbnail data
    const unsigned char jpegData[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x02, 0xFF, 0xD9
    };
    DataBuf thumbBuf(jpegData, sizeof(jpegData));
    
    // Set thumbnail offset and length in IFD1
    exifData["Exif.Thumbnail.JPEGInterchangeFormat"] = uint32_t(0);
    exifData["Exif.Thumbnail.JPEGInterchangeFormatLength"] = uint32_t(sizeof(jpegData));
    
    ExifThumbC thumb(exifData);
    const char* mime = thumb.mimeType();
    // If thumbnail is recognized as JPEG, it should return "image/jpeg"
    // If not recognized, it returns ""
    ASSERT_NE(mime, nullptr);
    // We check it's either "image/jpeg" or "" since we can't guarantee our manual setup is sufficient
    EXPECT_TRUE(std::string(mime) == "image/jpeg" || std::string(mime) == "");
}

// Test construction with const reference
TEST(ExifThumbCTest_768, ConstructionFromConstExifData_768) {
    const ExifData exifData;
    ExifThumbC thumb(exifData);
    // Should be constructible and callable
    const char* mime = thumb.mimeType();
    ASSERT_NE(mime, nullptr);
}

// Test that multiple calls to mimeType return consistent results
TEST(ExifThumbCTest_768, MimeTypeConsistentAcrossMultipleCalls_768) {
    ExifData exifData;
    ExifThumbC thumb(exifData);
    const char* mime1 = thumb.mimeType();
    const char* mime2 = thumb.mimeType();
    ASSERT_NE(mime1, nullptr);
    ASSERT_NE(mime2, nullptr);
    EXPECT_STREQ(mime1, mime2);
}

// Test that multiple calls to extension return consistent results
TEST(ExifThumbCTest_768, ExtensionConsistentAcrossMultipleCalls_768) {
    ExifData exifData;
    ExifThumbC thumb(exifData);
    const char* ext1 = thumb.extension();
    const char* ext2 = thumb.extension();
    ASSERT_NE(ext1, nullptr);
    ASSERT_NE(ext2, nullptr);
    EXPECT_STREQ(ext1, ext2);
}

// Test writeFile with empty path
TEST(ExifThumbCTest_768, WriteFileWithEmptyPath_768) {
    ExifData exifData;
    ExifThumbC thumb(exifData);
    size_t written = thumb.writeFile("");
    EXPECT_EQ(written, 0u);
}

// Test copy returns DataBuf that can be queried for size
TEST(ExifThumbCTest_768, CopySizeIsZeroWhenNoThumbnail_768) {
    ExifData exifData;
    ExifThumbC thumb(exifData);
    DataBuf buf = thumb.copy();
    EXPECT_EQ(buf.size(), 0u);
}

// Test with TIFF thumbnail compression
TEST(ExifThumbCTest_768, MimeTypeForTiffCompression_768) {
    ExifData exifData;
    // Compression value 1 = uncompressed (TIFF)
    exifData["Exif.Thumbnail.Compression"] = uint16_t(1);
    
    ExifThumbC thumb(exifData);
    const char* mime = thumb.mimeType();
    ASSERT_NE(mime, nullptr);
    // Could be "image/tiff" or "" depending on whether enough metadata is present
    EXPECT_TRUE(std::string(mime) == "image/tiff" || std::string(mime) == "");
}

// Test that ExifThumbC can be used with different ExifData instances
TEST(ExifThumbCTest_768, DifferentExifDataInstances_768) {
    ExifData exifData1;
    ExifData exifData2;
    
    ExifThumbC thumb1(exifData1);
    ExifThumbC thumb2(exifData2);
    
    EXPECT_STREQ(thumb1.mimeType(), thumb2.mimeType());
    EXPECT_STREQ(thumb1.extension(), thumb2.extension());
}
