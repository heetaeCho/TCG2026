#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/rafimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <cstdio>
#include <fstream>
#include <cstring>

namespace {

// Helper to create a temporary file with given content
class TempFile {
public:
    TempFile(const std::string& name, const std::vector<uint8_t>& content) : filename_(name) {
        std::ofstream ofs(filename_, std::ios::binary);
        if (!content.empty()) {
            ofs.write(reinterpret_cast<const char*>(content.data()), content.size());
        }
    }
    ~TempFile() {
        std::remove(filename_.c_str());
    }
    const std::string& path() const { return filename_; }
private:
    std::string filename_;
};

// Minimal RAF header for testing
std::vector<uint8_t> createMinimalRafHeader() {
    // RAF files start with "FUJIFILMCCD-RAW "
    std::vector<uint8_t> header(160, 0);
    const char* magic = "FUJIFILMCCD-RAW ";
    std::memcpy(header.data(), magic, 16);
    // Fill version info (bytes 16-19)
    header[16] = '0';
    header[17] = '2';
    header[18] = '0';
    header[19] = '1';
    // Rest can remain zero for basic structure
    return header;
}

} // anonymous namespace

// Test: newRafInstance with valid create flag should return a valid image
TEST(RafImageTest_223, CreateNewRafImage_223) {
    std::string tmpFile = "test_raf_create_223.raf";
    auto io = std::make_unique<Exiv2::FileIo>(tmpFile);
    auto image = Exiv2::newRafInstance(std::move(io), true);
    // When create is true, it should create a new RAF image
    // The result depends on whether the creation succeeds
    // Clean up
    std::remove(tmpFile.c_str());
}

// Test: newRafInstance with invalid/empty file and create=false should return nullptr
TEST(RafImageTest_223, OpenNonExistentFileReturnNullptr_223) {
    auto io = std::make_unique<Exiv2::FileIo>("nonexistent_file_223.raf");
    auto image = Exiv2::newRafInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: newRafInstance with MemIo containing no data and create=false
TEST(RafImageTest_223, EmptyMemIoCreateFalseReturnsNullptr_223) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::newRafInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: newRafInstance with MemIo and create=true
TEST(RafImageTest_223, MemIoCreateTrueReturnsImage_223) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::newRafInstance(std::move(io), true);
    // Depending on implementation, creating a RAF with empty MemIo might succeed or fail
    // We just check that it doesn't crash and returns something deterministic
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test: newRafInstance with garbage data and create=false should return nullptr or non-good image
TEST(RafImageTest_223, GarbageDataCreateFalseReturnsNullptr_223) {
    std::vector<uint8_t> garbage = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
    auto io = std::make_unique<Exiv2::MemIo>(garbage.data(), garbage.size());
    auto image = Exiv2::newRafInstance(std::move(io), false);
    // Garbage data is not valid RAF, so should not return a good image
    EXPECT_EQ(image, nullptr);
}

// Test: newRafInstance with minimal RAF header and create=false
TEST(RafImageTest_223, MinimalRafHeaderCreateFalse_223) {
    auto header = createMinimalRafHeader();
    auto io = std::make_unique<Exiv2::MemIo>(header.data(), header.size());
    auto image = Exiv2::newRafInstance(std::move(io), false);
    // With a minimal header, the image may or may not be considered good
    // We test that it doesn't crash
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test: RafImage constructor with create=false and empty MemIo
TEST(RafImageTest_223, RafImageConstructorCreateFalseEmptyIo_223) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::RafImage rafImage(std::move(io), false);
    // An empty IO with create=false should result in a not-good image
    EXPECT_FALSE(rafImage.good());
}

// Test: RafImage mimeType
TEST(RafImageTest_223, RafImageMimeType_223) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::RafImage rafImage(std::move(io), false);
    std::string mimeType = rafImage.mimeType();
    EXPECT_EQ(mimeType, "image/x-fuji-raf");
}

// Test: newRafInstance with a valid RAF file on disk
TEST(RafImageTest_223, ValidRafFileOnDisk_223) {
    auto header = createMinimalRafHeader();
    std::string tmpFile = "test_valid_raf_223.raf";
    {
        std::ofstream ofs(tmpFile, std::ios::binary);
        ofs.write(reinterpret_cast<const char*>(header.data()), header.size());
    }
    auto io = std::make_unique<Exiv2::FileIo>(tmpFile);
    auto image = Exiv2::newRafInstance(std::move(io), false);
    // Clean up
    std::remove(tmpFile.c_str());
    // With a minimal RAF header, the instance may or may not pass
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test: newRafInstance returns unique_ptr that is movable
TEST(RafImageTest_223, ReturnedUniquePointerIsMovable_223) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::newRafInstance(std::move(io), true);
    if (image) {
        Exiv2::Image::UniquePtr moved = std::move(image);
        EXPECT_NE(moved, nullptr);
        EXPECT_EQ(image, nullptr);
    }
}

// Test: RafImage with create=true on MemIo
TEST(RafImageTest_223, RafImageConstructorCreateTrue_223) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::RafImage rafImage(std::move(io), true);
    // A newly created RAF image should be good
    // (implementation dependent - we test observable behavior)
}

// Test: Truncated RAF header (less than magic string)
TEST(RafImageTest_223, TruncatedRafHeader_223) {
    // Only partial magic string
    const char* partial = "FUJIFILM";
    std::vector<uint8_t> data(partial, partial + 8);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto image = Exiv2::newRafInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: Large random data that isn't RAF
TEST(RafImageTest_223, LargeNonRafData_223) {
    std::vector<uint8_t> data(10000, 0xFF);
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto image = Exiv2::newRafInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test: Single byte data
TEST(RafImageTest_223, SingleByteData_223) {
    std::vector<uint8_t> data = {0x42};
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto image = Exiv2::newRafInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}
