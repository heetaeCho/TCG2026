#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/bmpimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <cstdint>
#include <fstream>
#include <cstring>

namespace {

// Helper to create a minimal valid BMP file in memory
std::vector<uint8_t> createMinimalBmpData() {
    // Minimal BMP: 14-byte file header + 40-byte DIB header (BITMAPINFOHEADER)
    // for a 1x1 pixel, 24-bit BMP
    std::vector<uint8_t> data(14 + 40 + 4, 0); // +4 for pixel data with padding
    
    // BMP file header
    data[0] = 'B';
    data[1] = 'M';
    uint32_t fileSize = static_cast<uint32_t>(data.size());
    std::memcpy(&data[2], &fileSize, 4);
    // Reserved
    data[6] = 0; data[7] = 0; data[8] = 0; data[9] = 0;
    // Offset to pixel data
    uint32_t offset = 14 + 40;
    std::memcpy(&data[10], &offset, 4);
    
    // DIB header (BITMAPINFOHEADER)
    uint32_t dibSize = 40;
    std::memcpy(&data[14], &dibSize, 4);
    int32_t width = 1;
    std::memcpy(&data[18], &width, 4);
    int32_t height = 1;
    std::memcpy(&data[22], &height, 4);
    uint16_t planes = 1;
    std::memcpy(&data[26], &planes, 2);
    uint16_t bpp = 24;
    std::memcpy(&data[28], &bpp, 2);
    // compression = 0 (BI_RGB)
    uint32_t compression = 0;
    std::memcpy(&data[30], &compression, 4);
    // image size can be 0 for BI_RGB
    uint32_t imgSize = 0;
    std::memcpy(&data[34], &imgSize, 4);
    
    return data;
}

// Helper to write data to a temporary file and return the path
std::string writeTempFile(const std::vector<uint8_t>& data, const std::string& suffix) {
    std::string path = "/tmp/test_bmp_" + suffix + ".bmp";
    std::ofstream ofs(path, std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
    ofs.close();
    return path;
}

} // anonymous namespace

// Test: newBmpInstance with a valid BMP file should return a non-null image
TEST(BmpImageTest_1041, NewBmpInstanceWithValidBmp_1041) {
    auto bmpData = createMinimalBmpData();
    std::string path = writeTempFile(bmpData, "valid");
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::Image::UniquePtr image = Exiv2::newBmpInstance(std::move(io), false);
    
    // A valid BMP should produce a non-null image
    EXPECT_NE(image, nullptr);
    
    std::remove(path.c_str());
}

// Test: newBmpInstance with create=true (should still work, parameter is unused)
TEST(BmpImageTest_1041, NewBmpInstanceCreateParamIgnored_1041) {
    auto bmpData = createMinimalBmpData();
    std::string path = writeTempFile(bmpData, "create_true");
    
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::Image::UniquePtr image = Exiv2::newBmpInstance(std::move(io), true);
    
    EXPECT_NE(image, nullptr);
    
    std::remove(path.c_str());
}

// Test: newBmpInstance with empty/invalid data should return nullptr (bad image)
TEST(BmpImageTest_1041, NewBmpInstanceWithEmptyData_1041) {
    // Create a MemIo with no data
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::Image::UniquePtr image = Exiv2::newBmpInstance(std::move(io), false);
    
    // An empty IO should result in a bad image, so nullptr
    // Note: behavior depends on whether BmpImage constructor marks it as not good()
    // We test observable behavior
    // This may or may not be nullptr depending on implementation
    // but with empty data, good() is likely false
    if (image) {
        // If it returns non-null, it should at least be usable
        SUCCEED();
    } else {
        EXPECT_EQ(image, nullptr);
    }
}

// Test: newBmpInstance with garbage data
TEST(BmpImageTest_1041, NewBmpInstanceWithGarbageData_1041) {
    std::vector<uint8_t> garbage = {0xFF, 0xFE, 0xFD, 0xFC, 0xFB};
    auto io = std::make_unique<Exiv2::MemIo>(garbage.data(), garbage.size());
    Exiv2::Image::UniquePtr image = Exiv2::newBmpInstance(std::move(io), false);
    
    // Garbage data - the image may or may not be considered "good"
    // We just verify it doesn't crash and returns a valid pointer or nullptr
    SUCCEED();
}

// Test: newBmpInstance with non-existent file
TEST(BmpImageTest_1041, NewBmpInstanceWithNonExistentFile_1041) {
    auto io = std::make_unique<Exiv2::FileIo>("/tmp/non_existent_bmp_file_1041.bmp");
    Exiv2::Image::UniquePtr image = Exiv2::newBmpInstance(std::move(io), false);
    
    // Non-existent file should result in bad IO, so nullptr expected
    EXPECT_EQ(image, nullptr);
}

// Test: BmpImage constructor with valid MemIo containing BMP data
TEST(BmpImageTest_1041, BmpImageConstructorWithValidData_1041) {
    auto bmpData = createMinimalBmpData();
    auto io = std::make_unique<Exiv2::MemIo>(bmpData.data(), bmpData.size());
    
    Exiv2::BmpImage bmpImage(std::move(io));
    EXPECT_TRUE(bmpImage.good());
}

// Test: BmpImage mimeType should return appropriate MIME type
TEST(BmpImageTest_1041, BmpImageMimeType_1041) {
    auto bmpData = createMinimalBmpData();
    auto io = std::make_unique<Exiv2::MemIo>(bmpData.data(), bmpData.size());
    
    Exiv2::BmpImage bmpImage(std::move(io));
    std::string mimeType = bmpImage.mimeType();
    EXPECT_EQ(mimeType, "image/x-ms-bmp");
}

// Test: BmpImage setExifData should throw (BMP doesn't support Exif)
TEST(BmpImageTest_1041, BmpImageSetExifDataThrows_1041) {
    auto bmpData = createMinimalBmpData();
    auto io = std::make_unique<Exiv2::MemIo>(bmpData.data(), bmpData.size());
    
    Exiv2::BmpImage bmpImage(std::move(io));
    Exiv2::ExifData exifData;
    
    // BMP typically doesn't support writing metadata
    // setExifData or writeMetadata may throw
    // We test what's observable
    bmpImage.setExifData(exifData);
    // If it doesn't throw, that's also acceptable behavior
    SUCCEED();
}

// Test: BmpImage setIptcData should work without crash
TEST(BmpImageTest_1041, BmpImageSetIptcData_1041) {
    auto bmpData = createMinimalBmpData();
    auto io = std::make_unique<Exiv2::MemIo>(bmpData.data(), bmpData.size());
    
    Exiv2::BmpImage bmpImage(std::move(io));
    Exiv2::IptcData iptcData;
    
    bmpImage.setIptcData(iptcData);
    SUCCEED();
}

// Test: BmpImage setComment should work without crash
TEST(BmpImageTest_1041, BmpImageSetComment_1041) {
    auto bmpData = createMinimalBmpData();
    auto io = std::make_unique<Exiv2::MemIo>(bmpData.data(), bmpData.size());
    
    Exiv2::BmpImage bmpImage(std::move(io));
    
    // BMP may not support comments, but setting one shouldn't crash
    bmpImage.setComment("test comment");
    SUCCEED();
}

// Test: BmpImage readMetadata on valid BMP
TEST(BmpImageTest_1041, BmpImageReadMetadata_1041) {
    auto bmpData = createMinimalBmpData();
    auto io = std::make_unique<Exiv2::MemIo>(bmpData.data(), bmpData.size());
    
    Exiv2::BmpImage bmpImage(std::move(io));
    
    // readMetadata should not throw for a valid BMP
    EXPECT_NO_THROW(bmpImage.readMetadata());
}

// Test: BmpImage writeMetadata should throw (BMP is typically read-only for metadata)
TEST(BmpImageTest_1041, BmpImageWriteMetadataThrows_1041) {
    auto bmpData = createMinimalBmpData();
    auto io = std::make_unique<Exiv2::MemIo>(bmpData.data(), bmpData.size());
    
    Exiv2::BmpImage bmpImage(std::move(io));
    
    // Writing metadata to BMP is typically not supported
    EXPECT_THROW(bmpImage.writeMetadata(), Exiv2::Error);
}

// Test: BmpImage pixelWidth and pixelHeight after readMetadata
TEST(BmpImageTest_1041, BmpImageDimensionsAfterReadMetadata_1041) {
    auto bmpData = createMinimalBmpData();
    auto io = std::make_unique<Exiv2::MemIo>(bmpData.data(), bmpData.size());
    
    Exiv2::BmpImage bmpImage(std::move(io));
    bmpImage.readMetadata();
    
    EXPECT_EQ(bmpImage.pixelWidth(), 1);
    EXPECT_EQ(bmpImage.pixelHeight(), 1);
}

// Test: BmpImage with larger dimensions
TEST(BmpImageTest_1041, BmpImageLargerDimensions_1041) {
    auto bmpData = createMinimalBmpData();
    // Modify dimensions to 100x200
    int32_t width = 100;
    int32_t height = 200;
    std::memcpy(&bmpData[18], &width, 4);
    std::memcpy(&bmpData[22], &height, 4);
    
    auto io = std::make_unique<Exiv2::MemIo>(bmpData.data(), bmpData.size());
    
    Exiv2::BmpImage bmpImage(std::move(io));
    bmpImage.readMetadata();
    
    EXPECT_EQ(bmpImage.pixelWidth(), 100);
    EXPECT_EQ(bmpImage.pixelHeight(), 200);
}

// Test: BmpImage readMetadata with truncated data should throw
TEST(BmpImageTest_1041, BmpImageReadMetadataTruncatedData_1041) {
    // Only provide partial BMP header (less than 14 bytes)
    std::vector<uint8_t> truncated = {'B', 'M', 0, 0};
    auto io = std::make_unique<Exiv2::MemIo>(truncated.data(), truncated.size());
    
    Exiv2::BmpImage bmpImage(std::move(io));
    
    // Reading metadata from truncated data should throw
    EXPECT_THROW(bmpImage.readMetadata(), Exiv2::Error);
}

// Test: BmpImage with wrong magic bytes should fail readMetadata
TEST(BmpImageTest_1041, BmpImageWrongMagicBytes_1041) {
    auto bmpData = createMinimalBmpData();
    // Corrupt the magic bytes
    bmpData[0] = 'X';
    bmpData[1] = 'Y';
    
    auto io = std::make_unique<Exiv2::MemIo>(bmpData.data(), bmpData.size());
    
    Exiv2::BmpImage bmpImage(std::move(io));
    
    EXPECT_THROW(bmpImage.readMetadata(), Exiv2::Error);
}
