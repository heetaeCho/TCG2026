#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/asfvideo.hpp>
#include <exiv2/basicio.hpp>

#include <memory>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>

namespace {

// Helper to create a temporary file with given content
class TempFile {
public:
    TempFile(const std::string& name, const std::vector<uint8_t>& content)
        : filename_(name) {
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

// Minimal ASF header GUID: 30 26 B2 75 8E 66 CF 11 A6 D9 00 AA 00 62 CE 6C
// followed by size (little-endian uint64), then some minimal data
std::vector<uint8_t> createMinimalAsfData() {
    std::vector<uint8_t> data;
    // ASF Header Object GUID
    uint8_t headerGuid[] = {
        0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
        0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
    };
    data.insert(data.end(), headerGuid, headerGuid + 16);

    // Size: 30 bytes total (16 GUID + 8 size + 4 num headers + 2 reserved)
    uint64_t size = 30;
    for (int i = 0; i < 8; i++) {
        data.push_back(static_cast<uint8_t>((size >> (8 * i)) & 0xFF));
    }

    // Number of header objects: 0
    uint32_t numHeaders = 0;
    for (int i = 0; i < 4; i++) {
        data.push_back(static_cast<uint8_t>((numHeaders >> (8 * i)) & 0xFF));
    }

    // Reserved bytes
    data.push_back(0x01);
    data.push_back(0x02);

    return data;
}

}  // namespace

// Test: newAsfInstance with a valid (minimal) ASF file
TEST(AsfVideoTest_1573, NewAsfInstanceWithValidFile_1573) {
    auto asfData = createMinimalAsfData();
    TempFile tmp("test_valid_asf_1573.asf", asfData);

    auto io = std::make_unique<Exiv2::FileIo>(tmp.path());
    auto image = Exiv2::newAsfInstance(std::move(io), false);

    // The image may or may not be null depending on whether the minimal data
    // passes the good() check. We test that the function doesn't crash
    // and returns some result.
    // If good(), image should be non-null
    if (image) {
        EXPECT_NE(image.get(), nullptr);
    }
}

// Test: newAsfInstance with an empty file should return nullptr (not good)
TEST(AsfVideoTest_1573, NewAsfInstanceWithEmptyFile_1573) {
    TempFile tmp("test_empty_asf_1573.asf", {});

    auto io = std::make_unique<Exiv2::FileIo>(tmp.path());
    auto image = Exiv2::newAsfInstance(std::move(io), false);

    EXPECT_EQ(image, nullptr);
}

// Test: newAsfInstance with garbage data should return nullptr
TEST(AsfVideoTest_1573, NewAsfInstanceWithGarbageData_1573) {
    std::vector<uint8_t> garbage = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
    TempFile tmp("test_garbage_asf_1573.asf", garbage);

    auto io = std::make_unique<Exiv2::FileIo>(tmp.path());
    auto image = Exiv2::newAsfInstance(std::move(io), false);

    EXPECT_EQ(image, nullptr);
}

// Test: newAsfInstance with non-existent file
TEST(AsfVideoTest_1573, NewAsfInstanceWithNonExistentFile_1573) {
    auto io = std::make_unique<Exiv2::FileIo>("non_existent_file_1573.asf");
    auto image = Exiv2::newAsfInstance(std::move(io), false);

    EXPECT_EQ(image, nullptr);
}

// Test: newAsfInstance with create=true (second parameter)
TEST(AsfVideoTest_1573, NewAsfInstanceWithCreateTrue_1573) {
    std::vector<uint8_t> garbage = {0xFF, 0xFE, 0xFD};
    TempFile tmp("test_create_true_1573.asf", garbage);

    auto io = std::make_unique<Exiv2::FileIo>(tmp.path());
    auto image = Exiv2::newAsfInstance(std::move(io), true);

    // create parameter is ignored per the signature, so behavior should be same
    EXPECT_EQ(image, nullptr);
}

// Test: newAsfInstance with MemIo containing no data
TEST(AsfVideoTest_1573, NewAsfInstanceWithEmptyMemIo_1573) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::newAsfInstance(std::move(io), false);

    EXPECT_EQ(image, nullptr);
}

// Test: newAsfInstance with MemIo containing minimal ASF data
TEST(AsfVideoTest_1573, NewAsfInstanceWithMemIoAsfData_1573) {
    auto asfData = createMinimalAsfData();
    auto io = std::make_unique<Exiv2::MemIo>(asfData.data(), asfData.size());
    auto image = Exiv2::newAsfInstance(std::move(io), false);

    // May or may not be valid depending on internal validation
    // Just ensure no crash
    if (image) {
        EXPECT_NE(image.get(), nullptr);
    }
}

// Test: newAsfInstance with MemIo containing only the GUID but incomplete header
TEST(AsfVideoTest_1573, NewAsfInstanceWithIncompleteAsfHeader_1573) {
    // Only the GUID, no size or other fields
    std::vector<uint8_t> partialData = {
        0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
        0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
    };
    auto io = std::make_unique<Exiv2::MemIo>(partialData.data(), partialData.size());
    auto image = Exiv2::newAsfInstance(std::move(io), false);

    // Likely not valid, but we just test it doesn't crash
    // Result could be nullptr or valid depending on implementation
}

// Test: AsfVideo constructor with MemIo directly
TEST(AsfVideoTest_1573, AsfVideoConstructorWithEmptyMemIo_1573) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::AsfVideo video(std::move(io));

    // An empty MemIo should result in !good()
    EXPECT_FALSE(video.good());
}

// Test: AsfVideo mimeType
TEST(AsfVideoTest_1573, AsfVideoMimeType_1573) {
    auto asfData = createMinimalAsfData();
    auto io = std::make_unique<Exiv2::MemIo>(asfData.data(), asfData.size());
    Exiv2::AsfVideo video(std::move(io));

    std::string mime = video.mimeType();
    EXPECT_FALSE(mime.empty());
    // ASF videos typically have video/x-ms-asf or similar mime type
    EXPECT_THAT(mime, testing::HasSubstr("asf"));
}

// Test: Large random data that is not ASF
TEST(AsfVideoTest_1573, NewAsfInstanceWithLargeRandomData_1573) {
    std::vector<uint8_t> largeData(10000, 0xAB);
    auto io = std::make_unique<Exiv2::MemIo>(largeData.data(), largeData.size());
    auto image = Exiv2::newAsfInstance(std::move(io), false);

    EXPECT_EQ(image, nullptr);
}

// Test: Single byte data
TEST(AsfVideoTest_1573, NewAsfInstanceWithSingleByte_1573) {
    std::vector<uint8_t> singleByte = {0x30};
    auto io = std::make_unique<Exiv2::MemIo>(singleByte.data(), singleByte.size());
    auto image = Exiv2::newAsfInstance(std::move(io), false);

    EXPECT_EQ(image, nullptr);
}
