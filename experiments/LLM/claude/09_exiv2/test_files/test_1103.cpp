#include <gtest/gtest.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <cstring>
#include <vector>

using namespace Exiv2;

class ImageFactoryTest_1103 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test getType with nullptr/empty data
TEST_F(ImageFactoryTest_1103, GetTypeWithNullData_1103) {
    const byte emptyData[] = {0};
    ImageType type = ImageFactory::getType(emptyData, 0);
    EXPECT_EQ(type, ImageType::none);
}

// Test getType with random garbage data that doesn't match any image format
TEST_F(ImageFactoryTest_1103, GetTypeWithGarbageData_1103) {
    const byte garbageData[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    ImageType type = ImageFactory::getType(garbageData, sizeof(garbageData));
    EXPECT_EQ(type, ImageType::none);
}

// Test getType with JPEG magic bytes
TEST_F(ImageFactoryTest_1103, GetTypeWithJpegData_1103) {
    // JPEG starts with FF D8 FF
    std::vector<byte> jpegData = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46,
                                   0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
                                   0x00, 0x01, 0x00, 0x00};
    ImageType type = ImageFactory::getType(jpegData.data(), jpegData.size());
    EXPECT_EQ(type, ImageType::jpeg);
}

// Test getType with PNG magic bytes
TEST_F(ImageFactoryTest_1103, GetTypeWithPngData_1103) {
    // PNG magic: 89 50 4E 47 0D 0A 1A 0A
    std::vector<byte> pngData = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
                                  0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52};
    ImageType type = ImageFactory::getType(pngData.data(), pngData.size());
    EXPECT_EQ(type, ImageType::png);
}

// Test getType with TIFF (little-endian) magic bytes
TEST_F(ImageFactoryTest_1103, GetTypeWithTiffLEData_1103) {
    // TIFF LE: 49 49 2A 00
    std::vector<byte> tiffData = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    ImageType type = ImageFactory::getType(tiffData.data(), tiffData.size());
    // TIFF type could be tiff or some variant, just check it's not none
    EXPECT_NE(type, ImageType::none);
}

// Test getType with TIFF (big-endian) magic bytes
TEST_F(ImageFactoryTest_1103, GetTypeWithTiffBEData_1103) {
    // TIFF BE: 4D 4D 00 2A
    std::vector<byte> tiffData = {0x4D, 0x4D, 0x00, 0x2A, 0x00, 0x00, 0x00, 0x08,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    ImageType type = ImageFactory::getType(tiffData.data(), tiffData.size());
    EXPECT_NE(type, ImageType::none);
}

// Test getType with very small data (1 byte)
TEST_F(ImageFactoryTest_1103, GetTypeWithSingleByte_1103) {
    const byte singleByte[] = {0xFF};
    ImageType type = ImageFactory::getType(singleByte, 1);
    EXPECT_EQ(type, ImageType::none);
}

// Test getType with only two bytes (partial JPEG header)
TEST_F(ImageFactoryTest_1103, GetTypeWithPartialJpegHeader_1103) {
    const byte partialJpeg[] = {0xFF, 0xD8};
    ImageType type = ImageFactory::getType(partialJpeg, sizeof(partialJpeg));
    // Only 2 bytes - may or may not be recognized
    // We just verify it doesn't crash
    (void)type;
}

// Test getType with WebP data
TEST_F(ImageFactoryTest_1103, GetTypeWithWebPData_1103) {
    // WebP: RIFF....WEBP
    std::vector<byte> webpData = {
        0x52, 0x49, 0x46, 0x46,  // RIFF
        0x00, 0x00, 0x00, 0x00,  // file size
        0x57, 0x45, 0x42, 0x50,  // WEBP
        0x56, 0x50, 0x38, 0x20,  // VP8
        0x00, 0x00, 0x00, 0x00
    };
    ImageType type = ImageFactory::getType(webpData.data(), webpData.size());
    EXPECT_EQ(type, ImageType::webp);
}

// Test getType with BMP-like data (not typically supported by exiv2, should be none)
TEST_F(ImageFactoryTest_1103, GetTypeWithBmpData_1103) {
    // BMP: 42 4D
    std::vector<byte> bmpData = {0x42, 0x4D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x36, 0x00, 0x00, 0x00};
    ImageType type = ImageFactory::getType(bmpData.data(), bmpData.size());
    EXPECT_EQ(type, ImageType::bmp);
}

// Test open with invalid data - should throw or return null
TEST_F(ImageFactoryTest_1103, OpenWithGarbageDataThrows_1103) {
    const byte garbageData[] = {0x01, 0x02, 0x03, 0x04};
    EXPECT_THROW(ImageFactory::open(garbageData, sizeof(garbageData)), Error);
}

// Test open with valid JPEG data
TEST_F(ImageFactoryTest_1103, OpenWithJpegData_1103) {
    // Minimal JPEG: FF D8 FF E0 ... FF D9
    std::vector<byte> jpegData = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
        0x4A, 0x46, 0x49, 0x46, 0x00, 0x01,
        0x01, 0x00, 0x00, 0x01, 0x00, 0x01,
        0x00, 0x00, 0xFF, 0xD9
    };
    auto image = ImageFactory::open(jpegData.data(), jpegData.size());
    EXPECT_NE(image, nullptr);
}

// Test open with empty data
TEST_F(ImageFactoryTest_1103, OpenWithEmptyDataThrows_1103) {
    const byte emptyData[] = {0};
    EXPECT_THROW(ImageFactory::open(emptyData, 0), Error);
}

// Test getType with GIF data
TEST_F(ImageFactoryTest_1103, GetTypeWithGifData_1103) {
    // GIF89a magic
    std::vector<byte> gifData = {0x47, 0x49, 0x46, 0x38, 0x39, 0x61,
                                  0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00};
    ImageType type = ImageFactory::getType(gifData.data(), gifData.size());
    EXPECT_EQ(type, ImageType::gif);
}

// Test checkMode with known type and metadata id
TEST_F(ImageFactoryTest_1103, CheckModeJpegExif_1103) {
    AccessMode mode = ImageFactory::checkMode(ImageType::jpeg, MetadataId::mdExif);
    // JPEG supports Exif, should be read-write
    EXPECT_EQ(mode, amReadWrite);
}

// Test checkMode with a type that doesn't support certain metadata
TEST_F(ImageFactoryTest_1103, CheckModeForUnsupportedMetadata_1103) {
    AccessMode mode = ImageFactory::checkMode(ImageType::none, MetadataId::mdExif);
    EXPECT_EQ(mode, amNone);
}

// Test getType consistency: getType from bytes should match getType from BasicIo
TEST_F(ImageFactoryTest_1103, GetTypeConsistencyBytesVsIo_1103) {
    std::vector<byte> jpegData = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
        0x4A, 0x46, 0x49, 0x46, 0x00, 0x01,
        0x01, 0x00, 0x00, 0x01, 0x00, 0x01,
        0x00, 0x00
    };
    
    ImageType typeFromBytes = ImageFactory::getType(jpegData.data(), jpegData.size());
    
    MemIo memIo(jpegData.data(), jpegData.size());
    ImageType typeFromIo = ImageFactory::getType(memIo);
    
    EXPECT_EQ(typeFromBytes, typeFromIo);
}

// Test getType with CR2 (Canon RAW) magic bytes
TEST_F(ImageFactoryTest_1103, GetTypeWithCR2LikeData_1103) {
    // CR2 starts like TIFF with CR2 signature at offset 8
    std::vector<byte> cr2Data = {
        0x49, 0x49, 0x2A, 0x00, 0x10, 0x00, 0x00, 0x00,
        0x43, 0x52, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    ImageType type = ImageFactory::getType(cr2Data.data(), cr2Data.size());
    // Should recognize as some image type (cr2 or tiff variant)
    // Just verify no crash
    (void)type;
}

// Test open with MemIo
TEST_F(ImageFactoryTest_1103, OpenWithMemIo_1103) {
    std::vector<byte> jpegData = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
        0x4A, 0x46, 0x49, 0x46, 0x00, 0x01,
        0x01, 0x00, 0x00, 0x01, 0x00, 0x01,
        0x00, 0x00, 0xFF, 0xD9
    };
    auto io = std::make_unique<MemIo>(jpegData.data(), jpegData.size());
    auto image = ImageFactory::open(std::move(io));
    EXPECT_NE(image, nullptr);
}

// Test that all-zero data returns none type
TEST_F(ImageFactoryTest_1103, GetTypeWithAllZeroData_1103) {
    std::vector<byte> zeroData(100, 0x00);
    ImageType type = ImageFactory::getType(zeroData.data(), zeroData.size());
    EXPECT_EQ(type, ImageType::none);
}

// Test that all-0xFF data returns none type (not a valid image)
TEST_F(ImageFactoryTest_1103, GetTypeWithAllFFData_1103) {
    std::vector<byte> ffData(100, 0xFF);
    ImageType type = ImageFactory::getType(ffData.data(), ffData.size());
    // All 0xFF doesn't form a valid recognized format
    // Could be none or some partial match - verify no crash at minimum
    (void)type;
}

// Test create with MemIo
TEST_F(ImageFactoryTest_1103, CreateJpegInMemory_1103) {
    auto image = ImageFactory::create(ImageType::jpeg);
    EXPECT_NE(image, nullptr);
}

// Test create with unsupported/none type
TEST_F(ImageFactoryTest_1103, CreateWithNoneTypeThrows_1103) {
    EXPECT_THROW(ImageFactory::create(ImageType::none), Error);
}

// Test checkMode for IPTC on JPEG
TEST_F(ImageFactoryTest_1103, CheckModeJpegIptc_1103) {
    AccessMode mode = ImageFactory::checkMode(ImageType::jpeg, MetadataId::mdIptc);
    EXPECT_EQ(mode, amReadWrite);
}

// Test checkMode for XMP on JPEG
TEST_F(ImageFactoryTest_1103, CheckModeJpegXmp_1103) {
    AccessMode mode = ImageFactory::checkMode(ImageType::jpeg, MetadataId::mdXmp);
    EXPECT_EQ(mode, amReadWrite);
}

// Test checkMode for PNG
TEST_F(ImageFactoryTest_1103, CheckModePngExif_1103) {
    AccessMode mode = ImageFactory::checkMode(ImageType::png, MetadataId::mdExif);
    EXPECT_NE(mode, amNone);
}

// Test with large random data
TEST_F(ImageFactoryTest_1103, GetTypeWithLargeRandomData_1103) {
    std::vector<byte> largeData(10000);
    for (size_t i = 0; i < largeData.size(); ++i) {
        largeData[i] = static_cast<byte>(i % 256);
    }
    ImageType type = ImageFactory::getType(largeData.data(), largeData.size());
    // Just verify no crash
    (void)type;
}

// Test getType with EXV signature
TEST_F(ImageFactoryTest_1103, GetTypeWithExvData_1103) {
    // EXV files have a specific header
    // Based on exiv2 format
    const byte exvMagic[] = {0xFF, 0x01, 'E', 'x', 'i', 'v', '2', 0xFF, 0xE1};
    ImageType type = ImageFactory::getType(exvMagic, sizeof(exvMagic));
    // Could be exv or none depending on header validation
    (void)type;
}
