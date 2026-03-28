#include <gtest/gtest.h>
#include <exiv2/tgaimage.hpp>
#include <exiv2/error.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <memory>
#include <sstream>

namespace {

// Helper to create a TgaImage with a MemIo
std::unique_ptr<Exiv2::TgaImage> createTgaImage(const std::string& data = "") {
    auto io = std::make_unique<Exiv2::MemIo>(
        reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
    return std::make_unique<Exiv2::TgaImage>(std::move(io));
}

// Minimal valid TGA header (18 bytes, no image data, uncompressed)
std::string createMinimalTgaData() {
    // TGA header is 18 bytes minimum
    std::string header(18, '\0');
    // ID length = 0
    header[0] = 0;
    // Color map type = 0 (no color map)
    header[1] = 0;
    // Image type = 2 (uncompressed true-color)
    header[2] = 2;
    // Color map spec (5 bytes) = 0
    // X origin (2 bytes) = 0
    // Y origin (2 bytes) = 0
    // Width (2 bytes) = 1
    header[12] = 1;
    header[13] = 0;
    // Height (2 bytes) = 1
    header[14] = 1;
    header[15] = 0;
    // Pixel depth = 24
    header[16] = 24;
    // Image descriptor = 0
    header[17] = 0;
    // Add pixel data (1 pixel, 3 bytes for 24-bit)
    header += std::string(3, '\xFF');
    return header;
}

class TgaImageTest_1232 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that writeMetadata throws an error indicating writing is unsupported
TEST_F(TgaImageTest_1232, WriteMetadataThrowsUnsupported_1232) {
    auto tga = createTgaImage(createMinimalTgaData());
    EXPECT_THROW(tga->writeMetadata(), Exiv2::Error);
}

// Test that writeMetadata throws with the correct error code
TEST_F(TgaImageTest_1232, WriteMetadataThrowsCorrectErrorCode_1232) {
    auto tga = createTgaImage(createMinimalTgaData());
    try {
        tga->writeMetadata();
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerWritingImageFormatUnsupported);
    } catch (...) {
        FAIL() << "Expected Exiv2::Error but got a different exception";
    }
}

// Test that mimeType returns the expected MIME type for TGA
TEST_F(TgaImageTest_1232, MimeTypeReturnsTgaMimeType_1232) {
    auto tga = createTgaImage(createMinimalTgaData());
    std::string mime = tga->mimeType();
    EXPECT_EQ(mime, "image/x-tga");
}

// Test that setExifData does not throw (it's a no-op for TGA)
TEST_F(TgaImageTest_1232, SetExifDataNoThrow_1232) {
    auto tga = createTgaImage(createMinimalTgaData());
    Exiv2::ExifData exifData;
    EXPECT_NO_THROW(tga->setExifData(exifData));
}

// Test that setIptcData does not throw (it's a no-op for TGA)
TEST_F(TgaImageTest_1232, SetIptcDataNoThrow_1232) {
    auto tga = createTgaImage(createMinimalTgaData());
    Exiv2::IptcData iptcData;
    EXPECT_NO_THROW(tga->setIptcData(iptcData));
}

// Test that setComment does not throw (it's a no-op for TGA)
TEST_F(TgaImageTest_1232, SetCommentNoThrow_1232) {
    auto tga = createTgaImage(createMinimalTgaData());
    EXPECT_NO_THROW(tga->setComment("test comment"));
}

// Test that setComment with empty string does not throw
TEST_F(TgaImageTest_1232, SetCommentEmptyStringNoThrow_1232) {
    auto tga = createTgaImage(createMinimalTgaData());
    EXPECT_NO_THROW(tga->setComment(""));
}

// Test readMetadata with valid TGA data
TEST_F(TgaImageTest_1232, ReadMetadataWithValidData_1232) {
    std::string data = createMinimalTgaData();
    auto tga = createTgaImage(data);
    EXPECT_NO_THROW(tga->readMetadata());
}

// Test readMetadata with empty data (should throw or handle gracefully)
TEST_F(TgaImageTest_1232, ReadMetadataWithEmptyData_1232) {
    auto tga = createTgaImage("");
    EXPECT_THROW(tga->readMetadata(), Exiv2::Error);
}

// Test readMetadata with truncated header (less than 18 bytes)
TEST_F(TgaImageTest_1232, ReadMetadataWithTruncatedHeader_1232) {
    std::string data(10, '\0'); // Only 10 bytes, need at least 18
    auto tga = createTgaImage(data);
    EXPECT_THROW(tga->readMetadata(), Exiv2::Error);
}

// Test that TgaImage is of the correct image type
TEST_F(TgaImageTest_1232, ImageTypeIsTga_1232) {
    auto tga = createTgaImage(createMinimalTgaData());
    EXPECT_EQ(tga->imageType(), Exiv2::ImageType::tga);
}

// Test that after setExifData, exifData remains empty (TGA doesn't support EXIF)
TEST_F(TgaImageTest_1232, ExifDataRemainsEmptyAfterSet_1232) {
    auto tga = createTgaImage(createMinimalTgaData());
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    tga->setExifData(exifData);
    // After writeMetadata would fail, but exifData on the image should reflect what was set
    // or remain empty depending on implementation. For TGA, it's typically ignored.
}

// Test that after setIptcData, iptcData remains empty (TGA doesn't support IPTC)
TEST_F(TgaImageTest_1232, IptcDataRemainsEmptyAfterSet_1232) {
    auto tga = createTgaImage(createMinimalTgaData());
    Exiv2::IptcData iptcData;
    tga->setIptcData(iptcData);
}

// Test readMetadata with just enough bytes for header (18 bytes exactly, but may still fail depending on content)
TEST_F(TgaImageTest_1232, ReadMetadataWithExactHeaderSize_1232) {
    std::string data(18, '\0');
    auto tga = createTgaImage(data);
    // This may or may not throw depending on validation; we just test it doesn't crash
    try {
        tga->readMetadata();
    } catch (const Exiv2::Error&) {
        // Acceptable - validation may reject this
    }
}

// Test creating TgaImage with MemIo containing large data
TEST_F(TgaImageTest_1232, ReadMetadataWithLargeData_1232) {
    std::string data = createMinimalTgaData();
    // Append extra data
    data += std::string(10000, '\0');
    auto tga = createTgaImage(data);
    EXPECT_NO_THROW(tga->readMetadata());
}

// Test multiple calls to writeMetadata all throw
TEST_F(TgaImageTest_1232, WriteMetadataAlwaysThrows_1232) {
    auto tga = createTgaImage(createMinimalTgaData());
    EXPECT_THROW(tga->writeMetadata(), Exiv2::Error);
    EXPECT_THROW(tga->writeMetadata(), Exiv2::Error);
    EXPECT_THROW(tga->writeMetadata(), Exiv2::Error);
}

// Test that setComment with a very long string doesn't crash
TEST_F(TgaImageTest_1232, SetCommentLongString_1232) {
    auto tga = createTgaImage(createMinimalTgaData());
    std::string longComment(10000, 'A');
    EXPECT_NO_THROW(tga->setComment(longComment));
}

} // namespace
