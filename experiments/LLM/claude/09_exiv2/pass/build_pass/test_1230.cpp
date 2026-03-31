#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/tgaimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>
#include <memory>
#include <sstream>

class TgaImageTest_1230 : public ::testing::Test {
protected:
    std::unique_ptr<Exiv2::TgaImage> createTgaImageFromMemory(const std::vector<uint8_t>& data) {
        auto memIo = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
        return std::make_unique<Exiv2::TgaImage>(std::move(memIo));
    }

    std::unique_ptr<Exiv2::TgaImage> createTgaImageEmpty() {
        auto memIo = std::make_unique<Exiv2::MemIo>();
        return std::make_unique<Exiv2::TgaImage>(std::move(memIo));
    }
};

TEST_F(TgaImageTest_1230, MimeTypeReturnsTarga_1230) {
    auto image = createTgaImageEmpty();
    EXPECT_EQ("image/targa", image->mimeType());
}

TEST_F(TgaImageTest_1230, MimeTypeIsConsistent_1230) {
    auto image = createTgaImageEmpty();
    std::string mime1 = image->mimeType();
    std::string mime2 = image->mimeType();
    EXPECT_EQ(mime1, mime2);
}

TEST_F(TgaImageTest_1230, SetExifDataDoesNotThrow_1230) {
    auto image = createTgaImageEmpty();
    Exiv2::ExifData exifData;
    EXPECT_NO_THROW(image->setExifData(exifData));
}

TEST_F(TgaImageTest_1230, SetIptcDataDoesNotThrow_1230) {
    auto image = createTgaImageEmpty();
    Exiv2::IptcData iptcData;
    EXPECT_NO_THROW(image->setIptcData(iptcData));
}

TEST_F(TgaImageTest_1230, SetCommentDoesNotThrow_1230) {
    auto image = createTgaImageEmpty();
    EXPECT_NO_THROW(image->setComment("test comment"));
}

TEST_F(TgaImageTest_1230, SetCommentWithEmptyStringDoesNotThrow_1230) {
    auto image = createTgaImageEmpty();
    EXPECT_NO_THROW(image->setComment(""));
}

TEST_F(TgaImageTest_1230, WriteMetadataThrowsOnEmptyIo_1230) {
    auto image = createTgaImageEmpty();
    EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
}

TEST_F(TgaImageTest_1230, ReadMetadataOnEmptyDataThrows_1230) {
    auto image = createTgaImageEmpty();
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

TEST_F(TgaImageTest_1230, ReadMetadataOnTooSmallDataThrows_1230) {
    std::vector<uint8_t> smallData(5, 0);
    auto image = createTgaImageFromMemory(smallData);
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

TEST_F(TgaImageTest_1230, ReadMetadataOnMinimalValidHeader_1230) {
    // TGA header is 18 bytes minimum
    // Construct a minimal TGA header
    std::vector<uint8_t> tgaHeader(18, 0);
    // ID length = 0
    tgaHeader[0] = 0;
    // Color map type = 0 (no color map)
    tgaHeader[1] = 0;
    // Image type = 2 (uncompressed true-color)
    tgaHeader[2] = 2;
    // Width (little-endian) = 1
    tgaHeader[12] = 1;
    tgaHeader[13] = 0;
    // Height (little-endian) = 1
    tgaHeader[14] = 1;
    tgaHeader[15] = 0;
    // Pixel depth = 24
    tgaHeader[16] = 24;
    // Image descriptor
    tgaHeader[17] = 0;

    // Add pixel data (1 pixel, 3 bytes for 24-bit)
    tgaHeader.push_back(0);
    tgaHeader.push_back(0);
    tgaHeader.push_back(0);

    auto image = createTgaImageFromMemory(tgaHeader);
    EXPECT_NO_THROW(image->readMetadata());
}

TEST_F(TgaImageTest_1230, ConstructionWithValidIo_1230) {
    auto memIo = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW(Exiv2::TgaImage tga(std::move(memIo)));
}

TEST_F(TgaImageTest_1230, SetExifDataAfterExifDataDoesNotThrow_1230) {
    auto image = createTgaImageEmpty();
    Exiv2::ExifData exifData1;
    Exiv2::ExifData exifData2;
    EXPECT_NO_THROW(image->setExifData(exifData1));
    EXPECT_NO_THROW(image->setExifData(exifData2));
}

TEST_F(TgaImageTest_1230, SetIptcDataAfterIptcDataDoesNotThrow_1230) {
    auto image = createTgaImageEmpty();
    Exiv2::IptcData iptcData1;
    Exiv2::IptcData iptcData2;
    EXPECT_NO_THROW(image->setIptcData(iptcData1));
    EXPECT_NO_THROW(image->setIptcData(iptcData2));
}

TEST_F(TgaImageTest_1230, SetCommentWithLongStringDoesNotThrow_1230) {
    auto image = createTgaImageEmpty();
    std::string longComment(10000, 'A');
    EXPECT_NO_THROW(image->setComment(longComment));
}

TEST_F(TgaImageTest_1230, ReadMetadataWithPartialHeader_1230) {
    // 17 bytes - one byte short of full header
    std::vector<uint8_t> partialHeader(17, 0);
    auto image = createTgaImageFromMemory(partialHeader);
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

TEST_F(TgaImageTest_1230, PixelWidthAndHeightAfterReadMetadata_1230) {
    std::vector<uint8_t> tgaHeader(18, 0);
    tgaHeader[0] = 0;
    tgaHeader[1] = 0;
    tgaHeader[2] = 2;
    // Width = 100 (little-endian)
    tgaHeader[12] = 100;
    tgaHeader[13] = 0;
    // Height = 50 (little-endian)
    tgaHeader[14] = 50;
    tgaHeader[15] = 0;
    tgaHeader[16] = 24;
    tgaHeader[17] = 0;

    // Add pixel data (100*50*3 bytes)
    for (int i = 0; i < 100 * 50 * 3; ++i) {
        tgaHeader.push_back(0);
    }

    auto image = createTgaImageFromMemory(tgaHeader);
    EXPECT_NO_THROW(image->readMetadata());
    EXPECT_EQ(100u, image->pixelWidth());
    EXPECT_EQ(50u, image->pixelHeight());
}
