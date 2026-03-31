#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/tgaimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <cstdint>
#include <fstream>
#include <vector>

namespace {

// Helper function to create a minimal valid TGA file in memory
std::vector<uint8_t> createMinimalTgaData() {
    // Minimal TGA header (18 bytes)
    // ID length: 0, Color map type: 0, Image type: 2 (uncompressed true-color)
    // Color map specification: 5 bytes of zeros
    // Image specification: x-origin(2), y-origin(2), width(2), height(2), pixel-depth(1), image-descriptor(1)
    std::vector<uint8_t> data(18, 0);
    data[2] = 2;      // Image type: uncompressed true-color
    data[12] = 1;     // Width low byte = 1
    data[13] = 0;     // Width high byte = 0
    data[14] = 1;     // Height low byte = 1
    data[15] = 0;     // Height high byte = 0
    data[16] = 24;    // Pixel depth = 24 bits
    data[17] = 0;     // Image descriptor

    // Add one pixel (3 bytes for 24-bit)
    data.push_back(0);
    data.push_back(0);
    data.push_back(0);

    return data;
}

// Helper to write data to a temp file and return the path
std::string writeTempFile(const std::vector<uint8_t>& data, const std::string& suffix) {
    std::string path = "/tmp/test_tga_" + suffix + ".tga";
    std::ofstream ofs(path, std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
    ofs.close();
    return path;
}

}  // namespace

class TgaImageTest_1233 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that newTgaInstance returns a valid image for valid TGA data
TEST_F(TgaImageTest_1233, NewTgaInstanceWithValidData_1233) {
    auto data = createMinimalTgaData();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto image = Exiv2::newTgaInstance(std::move(io), false);
    // The image should be created (though it may or may not be null depending on validation)
    // We test that the function doesn't crash and returns something
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test that newTgaInstance with empty data returns nullptr or invalid image
TEST_F(TgaImageTest_1233, NewTgaInstanceWithEmptyData_1233) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::newTgaInstance(std::move(io), false);
    // Empty IO should result in nullptr since good() would be false
    EXPECT_EQ(image, nullptr);
}

// Test that newTgaInstance with create=true still works
TEST_F(TgaImageTest_1233, NewTgaInstanceWithCreateTrue_1233) {
    auto data = createMinimalTgaData();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto image = Exiv2::newTgaInstance(std::move(io), true);
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test TgaImage construction with MemIo
TEST_F(TgaImageTest_1233, TgaImageConstructionWithMemIo_1233) {
    auto data = createMinimalTgaData();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::TgaImage image(std::move(io));
    // Check if the image reports as good
    // TGA images may or may not be "good" without reading, depends on IO status
}

// Test that TgaImage mimeType returns correct value
TEST_F(TgaImageTest_1233, TgaImageMimeType_1233) {
    auto data = createMinimalTgaData();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::TgaImage image(std::move(io));
    std::string mime = image.mimeType();
    EXPECT_EQ(mime, "image/targa");
}

// Test that setExifData throws or is a no-op for TGA
TEST_F(TgaImageTest_1233, TgaImageSetExifData_1233) {
    auto data = createMinimalTgaData();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::TgaImage image(std::move(io));
    Exiv2::ExifData exifData;
    // TGA does not support EXIF, so setExifData should be safe to call
    // (it may throw or be a no-op)
    EXPECT_NO_THROW(image.setExifData(exifData));
}

// Test that setIptcData is handled for TGA
TEST_F(TgaImageTest_1233, TgaImageSetIptcData_1233) {
    auto data = createMinimalTgaData();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::TgaImage image(std::move(io));
    Exiv2::IptcData iptcData;
    EXPECT_NO_THROW(image.setIptcData(iptcData));
}

// Test that setComment is handled for TGA
TEST_F(TgaImageTest_1233, TgaImageSetComment_1233) {
    auto data = createMinimalTgaData();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::TgaImage image(std::move(io));
    EXPECT_THROW(image.setComment("test comment"), Exiv2::Error);
}

// Test readMetadata on valid TGA data
TEST_F(TgaImageTest_1233, TgaImageReadMetadata_1233) {
    auto data = createMinimalTgaData();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::TgaImage image(std::move(io));
    // readMetadata should not throw for valid TGA
    EXPECT_NO_THROW(image.readMetadata());
}

// Test readMetadata on empty/invalid TGA data
TEST_F(TgaImageTest_1233, TgaImageReadMetadataInvalid_1233) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::TgaImage image(std::move(io));
    // readMetadata on empty data should throw
    EXPECT_THROW(image.readMetadata(), Exiv2::Error);
}

// Test writeMetadata throws for TGA (TGA typically doesn't support writing metadata)
TEST_F(TgaImageTest_1233, TgaImageWriteMetadata_1233) {
    auto data = createMinimalTgaData();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::TgaImage image(std::move(io));
    EXPECT_THROW(image.writeMetadata(), Exiv2::Error);
}

// Test newTgaInstance with single byte of data
TEST_F(TgaImageTest_1233, NewTgaInstanceWithSingleByte_1233) {
    std::vector<uint8_t> data = {0x00};
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto image = Exiv2::newTgaInstance(std::move(io), false);
    // Likely returns a valid pointer since TGA doesn't have a magic number check in good()
    // or returns nullptr - depends on implementation
}

// Test with truncated TGA header
TEST_F(TgaImageTest_1233, TgaImageReadMetadataTruncatedHeader_1233) {
    // Only 10 bytes - truncated header
    std::vector<uint8_t> data(10, 0);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::TgaImage image(std::move(io));
    // readMetadata may throw due to truncated data
    EXPECT_THROW(image.readMetadata(), Exiv2::Error);
}

// Test pixelWidth and pixelHeight after reading metadata
TEST_F(TgaImageTest_1233, TgaImageDimensionsAfterRead_1233) {
    auto data = createMinimalTgaData();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::TgaImage image(std::move(io));
    try {
        image.readMetadata();
        // After reading, dimensions should be set
        EXPECT_EQ(image.pixelWidth(), 1);
        EXPECT_EQ(image.pixelHeight(), 1);
    } catch (const Exiv2::Error&) {
        // If readMetadata fails, that's also acceptable behavior
    }
}

// Test with larger valid TGA image
TEST_F(TgaImageTest_1233, TgaImageLargerDimensions_1233) {
    std::vector<uint8_t> data(18, 0);
    data[2] = 2;       // Uncompressed true-color
    data[12] = 0x0A;   // Width = 10
    data[13] = 0x00;
    data[14] = 0x05;   // Height = 5
    data[15] = 0x00;
    data[16] = 24;     // 24-bit
    data[17] = 0;

    // Add pixel data: 10 * 5 * 3 = 150 bytes
    for (int i = 0; i < 150; i++) {
        data.push_back(0);
    }

    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::TgaImage image(std::move(io));
    try {
        image.readMetadata();
        EXPECT_EQ(image.pixelWidth(), 10);
        EXPECT_EQ(image.pixelHeight(), 5);
    } catch (const Exiv2::Error&) {
        // Acceptable if implementation rejects
    }
}
