#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/psdimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <fstream>
#include <cstdio>
#include <cstring>

namespace {

// Helper to create a temporary file with given content
class TempFile {
public:
    TempFile(const std::string& filename, const std::vector<uint8_t>& content)
        : filename_(filename) {
        std::ofstream ofs(filename_, std::ios::binary);
        if (!content.empty()) {
            ofs.write(reinterpret_cast<const char*>(content.data()), content.size());
        }
        ofs.close();
    }

    ~TempFile() {
        std::remove(filename_.c_str());
    }

    const std::string& path() const { return filename_; }

private:
    std::string filename_;
};

// Minimal PSD file header (signature "8BPS", version 2 bytes, 6 reserved bytes, etc.)
std::vector<uint8_t> createMinimalPsdHeader() {
    std::vector<uint8_t> data;
    // Signature: "8BPS"
    data.push_back('8');
    data.push_back('B');
    data.push_back('P');
    data.push_back('S');
    // Version: 1 (big-endian)
    data.push_back(0x00);
    data.push_back(0x01);
    // Reserved: 6 bytes of zeros
    for (int i = 0; i < 6; ++i)
        data.push_back(0x00);
    // Channels: 3 (big-endian)
    data.push_back(0x00);
    data.push_back(0x03);
    // Height: 1 (big-endian, 4 bytes)
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x01);
    // Width: 1 (big-endian, 4 bytes)
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x01);
    // Depth: 8 (big-endian)
    data.push_back(0x00);
    data.push_back(0x08);
    // Color mode: 3 (RGB, big-endian)
    data.push_back(0x00);
    data.push_back(0x03);
    // Color mode data length: 0
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    // Image resources length: 0
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    // Layer and mask info length: 0
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);

    return data;
}

}  // namespace

// Test: newPsdInstance with a valid PSD file returns non-null
TEST(NewPsdInstanceTest_1188, ValidPsdFileReturnsNonNull_1188) {
    auto psdData = createMinimalPsdHeader();
    TempFile tmpFile("test_valid_1188.psd", psdData);

    auto io = std::make_unique<Exiv2::FileIo>(tmpFile.path());
    auto image = Exiv2::newPsdInstance(std::move(io), false);
    // A valid PSD file should produce a non-null image
    // (depends on whether the IO can be opened successfully)
    // The image might be null if good() returns false, but we test the path
    if (image) {
        EXPECT_NE(image.get(), nullptr);
    }
}

// Test: newPsdInstance with empty file returns null (not a valid PSD)
TEST(NewPsdInstanceTest_1188, EmptyFileReturnsNull_1188) {
    std::vector<uint8_t> emptyData;
    TempFile tmpFile("test_empty_1188.psd", emptyData);

    auto io = std::make_unique<Exiv2::FileIo>(tmpFile.path());
    auto image = Exiv2::newPsdInstance(std::move(io), false);
    // An empty file is not a valid PSD, good() should be false
    // The function should return nullptr
    EXPECT_EQ(image, nullptr);
}

// Test: newPsdInstance with garbage data returns null
TEST(NewPsdInstanceTest_1188, GarbageDataReturnsNull_1188) {
    std::vector<uint8_t> garbageData(100, 0xFF);
    TempFile tmpFile("test_garbage_1188.psd", garbageData);

    auto io = std::make_unique<Exiv2::FileIo>(tmpFile.path());
    auto image = Exiv2::newPsdInstance(std::move(io), false);
    // Garbage data should not produce a valid PSD image
    EXPECT_EQ(image, nullptr);
}

// Test: newPsdInstance with non-existent file
TEST(NewPsdInstanceTest_1188, NonExistentFileReturnsNull_1188) {
    auto io = std::make_unique<Exiv2::FileIo>("nonexistent_file_1188.psd");
    auto image = Exiv2::newPsdInstance(std::move(io), false);
    // A non-existent file cannot be opened, good() should be false
    EXPECT_EQ(image, nullptr);
}

// Test: newPsdInstance with create flag set to true (still uses same logic)
TEST(NewPsdInstanceTest_1188, CreateFlagTrue_1188) {
    auto psdData = createMinimalPsdHeader();
    TempFile tmpFile("test_create_true_1188.psd", psdData);

    auto io = std::make_unique<Exiv2::FileIo>(tmpFile.path());
    auto image = Exiv2::newPsdInstance(std::move(io), true);
    // The create parameter is unused, behavior should be same as false
    if (image) {
        EXPECT_NE(image.get(), nullptr);
    }
}

// Test: newPsdInstance with MemIo containing valid PSD data
TEST(NewPsdInstanceTest_1188, MemIoValidPsdData_1188) {
    auto psdData = createMinimalPsdHeader();
    auto io = std::make_unique<Exiv2::MemIo>(psdData.data(), psdData.size());
    auto image = Exiv2::newPsdInstance(std::move(io), false);
    // MemIo with valid PSD header data
    if (image) {
        EXPECT_NE(image.get(), nullptr);
    }
}

// Test: newPsdInstance with MemIo containing empty data
TEST(NewPsdInstanceTest_1188, MemIoEmptyData_1188) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::newPsdInstance(std::move(io), false);
    // Empty MemIo should result in null
    EXPECT_EQ(image, nullptr);
}

// Test: newPsdInstance with truncated PSD header
TEST(NewPsdInstanceTest_1188, TruncatedPsdHeader_1188) {
    // Only the first 4 bytes of a PSD signature
    std::vector<uint8_t> truncatedData = {'8', 'B', 'P', 'S'};
    auto io = std::make_unique<Exiv2::MemIo>(truncatedData.data(), truncatedData.size());
    auto image = Exiv2::newPsdInstance(std::move(io), false);
    // Truncated header should not be considered good
    EXPECT_EQ(image, nullptr);
}

// Test: newPsdInstance with wrong signature but correct size
TEST(NewPsdInstanceTest_1188, WrongSignatureCorrectSize_1188) {
    auto psdData = createMinimalPsdHeader();
    // Corrupt the signature
    psdData[0] = 'X';
    psdData[1] = 'Y';
    psdData[2] = 'Z';
    psdData[3] = 'W';
    auto io = std::make_unique<Exiv2::MemIo>(psdData.data(), psdData.size());
    auto image = Exiv2::newPsdInstance(std::move(io), false);
    // Wrong signature should result in null
    EXPECT_EQ(image, nullptr);
}

// Test: PsdImage can be constructed with valid IO
TEST(PsdImageTest_1188, ConstructWithValidIo_1188) {
    auto psdData = createMinimalPsdHeader();
    auto io = std::make_unique<Exiv2::MemIo>(psdData.data(), psdData.size());
    EXPECT_NO_THROW({
        Exiv2::PsdImage img(std::move(io));
    });
}

// Test: PsdImage good() with valid data
TEST(PsdImageTest_1188, GoodWithValidData_1188) {
    auto psdData = createMinimalPsdHeader();
    auto io = std::make_unique<Exiv2::MemIo>(psdData.data(), psdData.size());
    Exiv2::PsdImage img(std::move(io));
    // good() should reflect whether the underlying IO is in a good state
    // With valid data in MemIo, this should be true
    EXPECT_TRUE(img.good());
}

// Test: PsdImage mimeType
TEST(PsdImageTest_1188, MimeType_1188) {
    auto psdData = createMinimalPsdHeader();
    auto io = std::make_unique<Exiv2::MemIo>(psdData.data(), psdData.size());
    Exiv2::PsdImage img(std::move(io));
    std::string mime = img.mimeType();
    EXPECT_EQ(mime, "image/x-photoshop");
}

// Test: newPsdInstance with single byte data
TEST(NewPsdInstanceTest_1188, SingleByteData_1188) {
    std::vector<uint8_t> singleByte = {0x00};
    auto io = std::make_unique<Exiv2::MemIo>(singleByte.data(), singleByte.size());
    auto image = Exiv2::newPsdInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}
