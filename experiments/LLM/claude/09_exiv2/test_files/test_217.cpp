#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/rafimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <sstream>
#include <fstream>
#include <cstring>

namespace {

// Helper to create a minimal RAF file header for testing
std::vector<unsigned char> createMinimalRafData() {
    // RAF files start with "FUJIFILMCCD-RAW " (16 bytes magic)
    std::vector<unsigned char> data(1024, 0);
    const char* magic = "FUJIFILMCCD-RAW ";
    std::memcpy(data.data(), magic, 16);
    // Fill version info (bytes 16-19)
    data[16] = '0';
    data[17] = '2';
    data[18] = '0';
    data[19] = '1';
    // Rest is zeros which may or may not be valid, but enough for some tests
    return data;
}

class RafImageTest_217 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    std::unique_ptr<Exiv2::RafImage> createRafImageFromMemory(const std::vector<unsigned char>& data) {
        auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
        return std::make_unique<Exiv2::RafImage>(std::move(io), false);
    }

    std::unique_ptr<Exiv2::RafImage> createEmptyRafImage() {
        auto io = std::make_unique<Exiv2::MemIo>();
        return std::make_unique<Exiv2::RafImage>(std::move(io), false);
    }
};

// Test that mimeType returns the correct MIME type for RAF images
TEST_F(RafImageTest_217, MimeTypeReturnsCorrectValue_217) {
    auto data = createMinimalRafData();
    auto image = createRafImageFromMemory(data);
    EXPECT_EQ(image->mimeType(), "image/x-fuji-raf");
}

// Test that mimeType is consistent across multiple calls
TEST_F(RafImageTest_217, MimeTypeConsistentAcrossCalls_217) {
    auto data = createMinimalRafData();
    auto image = createRafImageFromMemory(data);
    std::string mime1 = image->mimeType();
    std::string mime2 = image->mimeType();
    EXPECT_EQ(mime1, mime2);
    EXPECT_EQ(mime1, "image/x-fuji-raf");
}

// Test that setExifData does not throw (RAF images don't support writing EXIF directly)
TEST_F(RafImageTest_217, SetExifDataThrowsOrNoOp_217) {
    auto data = createMinimalRafData();
    auto image = createRafImageFromMemory(data);
    Exiv2::ExifData exifData;
    // setExifData on RAF should throw since RAF doesn't support direct EXIF writing
    EXPECT_THROW(image->setExifData(exifData), Exiv2::Error);
}

// Test that setIptcData does not throw or throws appropriately
TEST_F(RafImageTest_217, SetIptcDataThrowsOrNoOp_217) {
    auto data = createMinimalRafData();
    auto image = createRafImageFromMemory(data);
    Exiv2::IptcData iptcData;
    EXPECT_THROW(image->setIptcData(iptcData), Exiv2::Error);
}

// Test that setComment throws or is no-op for RAF images
TEST_F(RafImageTest_217, SetCommentThrowsOrNoOp_217) {
    auto data = createMinimalRafData();
    auto image = createRafImageFromMemory(data);
    EXPECT_THROW(image->setComment("test comment"), Exiv2::Error);
}

// Test that readMetadata on empty IO throws
TEST_F(RafImageTest_217, ReadMetadataOnEmptyIOThrows_217) {
    auto image = createEmptyRafImage();
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test that readMetadata on too-small data throws
TEST_F(RafImageTest_217, ReadMetadataOnSmallDataThrows_217) {
    std::vector<unsigned char> tinyData(10, 0);
    auto image = createRafImageFromMemory(tinyData);
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test that readMetadata on data with wrong magic throws
TEST_F(RafImageTest_217, ReadMetadataOnInvalidMagicThrows_217) {
    std::vector<unsigned char> badData(1024, 0);
    const char* badMagic = "NOT_A_RAF_FILE!!";
    std::memcpy(badData.data(), badMagic, 16);
    auto image = createRafImageFromMemory(badData);
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test that writeMetadata throws on empty IO
TEST_F(RafImageTest_217, WriteMetadataOnEmptyIOThrows_217) {
    auto image = createEmptyRafImage();
    EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
}

// Test that pixelWidth returns 0 before readMetadata
TEST_F(RafImageTest_217, PixelWidthBeforeReadMetadata_217) {
    auto data = createMinimalRafData();
    auto image = createRafImageFromMemory(data);
    // Before reading metadata, pixel dimensions should be 0
    EXPECT_EQ(image->pixelWidth(), 0u);
}

// Test that pixelHeight returns 0 before readMetadata
TEST_F(RafImageTest_217, PixelHeightBeforeReadMetadata_217) {
    auto data = createMinimalRafData();
    auto image = createRafImageFromMemory(data);
    EXPECT_EQ(image->pixelHeight(), 0u);
}

// Test printStructure with kprNone on minimal data
TEST_F(RafImageTest_217, PrintStructureNone_217) {
    auto data = createMinimalRafData();
    auto image = createRafImageFromMemory(data);
    std::ostringstream oss;
    // kprNone should not produce output or should not throw
    EXPECT_NO_THROW(image->printStructure(oss, Exiv2::kpsNone, 0));
}

// Test creation with create=true on empty IO
TEST_F(RafImageTest_217, CreateNewRafImage_217) {
    auto io = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW({
        auto image = std::make_unique<Exiv2::RafImage>(std::move(io), true);
    });
}

// Test that readMetadata with valid RAF header but incomplete offsets throws
TEST_F(RafImageTest_217, ReadMetadataIncompleteOffsetsThrows_217) {
    // Create data with valid magic but insufficient data for offset parsing
    std::vector<unsigned char> data(64, 0);
    const char* magic = "FUJIFILMCCD-RAW ";
    std::memcpy(data.data(), magic, 16);
    auto image = createRafImageFromMemory(data);
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test that the image type is recognized properly
TEST_F(RafImageTest_217, ImageTypeCheck_217) {
    auto data = createMinimalRafData();
    auto image = createRafImageFromMemory(data);
    // RafImage should report itself as RAF type
    EXPECT_EQ(image->imageType(), Exiv2::ImageType::raf);
}

}  // namespace
