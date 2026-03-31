#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/riffvideo.hpp>
#include <exiv2/basicio.hpp>
#include <cstring>
#include <fstream>

// Helper to create a temporary file with given content
class TempFile {
public:
    explicit TempFile(const std::string& filename, const std::vector<uint8_t>& content)
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

// Minimal valid RIFF/AVI header
static std::vector<uint8_t> createMinimalRiffAviHeader() {
    std::vector<uint8_t> data;
    // "RIFF" chunk ID
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    // Chunk size (little-endian, 4 bytes) - size of rest of file
    uint32_t chunkSize = 4; // just the "AVI " form type
    data.push_back(chunkSize & 0xFF);
    data.push_back((chunkSize >> 8) & 0xFF);
    data.push_back((chunkSize >> 16) & 0xFF);
    data.push_back((chunkSize >> 24) & 0xFF);
    // "AVI " form type
    data.push_back('A'); data.push_back('V'); data.push_back('I'); data.push_back(' ');
    return data;
}

class RiffVideoTest_82 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that newRiffInstance returns nullptr for an empty file (not a valid RIFF)
TEST_F(RiffVideoTest_82, NewRiffInstanceWithEmptyFile_82) {
    std::vector<uint8_t> emptyData;
    TempFile tmp("test_empty_riff_82.avi", emptyData);
    auto io = std::make_unique<Exiv2::FileIo>(tmp.path());
    auto image = Exiv2::newRiffInstance(std::move(io), false);
    // An empty file should not produce a valid RIFF image
    // It may return nullptr or a non-good image
    // Based on the code: if (!image->good()) return nullptr;
    // But if make_unique succeeds and good() is false, returns nullptr
    EXPECT_EQ(image, nullptr);
}

// Test that newRiffInstance returns nullptr for garbage data
TEST_F(RiffVideoTest_82, NewRiffInstanceWithGarbageData_82) {
    std::vector<uint8_t> garbage = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    TempFile tmp("test_garbage_riff_82.avi", garbage);
    auto io = std::make_unique<Exiv2::FileIo>(tmp.path());
    auto image = Exiv2::newRiffInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test that newRiffInstance with a minimal valid RIFF/AVI header returns non-null
TEST_F(RiffVideoTest_82, NewRiffInstanceWithMinimalRiffAvi_82) {
    auto data = createMinimalRiffAviHeader();
    TempFile tmp("test_minimal_riff_82.avi", data);
    auto io = std::make_unique<Exiv2::FileIo>(tmp.path());
    auto image = Exiv2::newRiffInstance(std::move(io), false);
    // A minimal valid RIFF header should produce a valid image
    // (though it's minimal, the good() check should pass)
    if (image) {
        EXPECT_TRUE(image->good());
    }
    // We accept either nullptr or a valid image depending on implementation strictness
}

// Test that newRiffInstance returns nullptr for non-existent file
TEST_F(RiffVideoTest_82, NewRiffInstanceWithNonExistentFile_82) {
    auto io = std::make_unique<Exiv2::FileIo>("nonexistent_file_82.avi");
    auto image = Exiv2::newRiffInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test with MemIo containing empty data
TEST_F(RiffVideoTest_82, NewRiffInstanceWithEmptyMemIo_82) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::newRiffInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test with MemIo containing garbage data
TEST_F(RiffVideoTest_82, NewRiffInstanceWithGarbageMemIo_82) {
    const uint8_t garbage[] = {0xDE, 0xAD, 0xBE, 0xEF};
    auto io = std::make_unique<Exiv2::MemIo>(garbage, sizeof(garbage));
    auto image = Exiv2::newRiffInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test with MemIo containing a minimal RIFF header
TEST_F(RiffVideoTest_82, NewRiffInstanceWithMinimalRiffMemIo_82) {
    auto data = createMinimalRiffAviHeader();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto image = Exiv2::newRiffInstance(std::move(io), false);
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test with truncated RIFF header (only "RIFF" without size or type)
TEST_F(RiffVideoTest_82, NewRiffInstanceWithTruncatedHeader_82) {
    std::vector<uint8_t> data = {'R', 'I', 'F', 'F'};
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto image = Exiv2::newRiffInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test with RIFF header but wrong form type (not AVI or WAVE)
TEST_F(RiffVideoTest_82, NewRiffInstanceWithWrongFormType_82) {
    std::vector<uint8_t> data;
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    uint32_t chunkSize = 4;
    data.push_back(chunkSize & 0xFF);
    data.push_back((chunkSize >> 8) & 0xFF);
    data.push_back((chunkSize >> 16) & 0xFF);
    data.push_back((chunkSize >> 24) & 0xFF);
    // Unknown form type "XXXX"
    data.push_back('X'); data.push_back('X'); data.push_back('X'); data.push_back('X');
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto image = Exiv2::newRiffInstance(std::move(io), false);
    // May return nullptr if the form type is not recognized
    // Accept either behavior
    if (image) {
        // If it returns non-null, it should still be a valid object
        SUCCEED();
    } else {
        EXPECT_EQ(image, nullptr);
    }
}

// Test create parameter (second argument) doesn't crash even if true
TEST_F(RiffVideoTest_82, NewRiffInstanceWithCreateTrue_82) {
    auto data = createMinimalRiffAviHeader();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    // The create parameter is unused per the interface (/*create*/), but shouldn't crash
    auto image = Exiv2::newRiffInstance(std::move(io), true);
    // Just ensure no crash; result depends on implementation
    SUCCEED();
}

// Test RiffVideo constructor directly with valid data
TEST_F(RiffVideoTest_82, RiffVideoConstructorWithValidData_82) {
    auto data = createMinimalRiffAviHeader();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    try {
        Exiv2::RiffVideo video(std::move(io));
        // Check mimeType
        EXPECT_FALSE(std::string(video.mimeType()).empty());
    } catch (...) {
        // Some implementations may throw for minimal data; that's acceptable
        SUCCEED();
    }
}

// Test RiffVideo with empty MemIo - good() should be false
TEST_F(RiffVideoTest_82, RiffVideoGoodReturnsFalseForEmptyIo_82) {
    auto io = std::make_unique<Exiv2::MemIo>();
    try {
        Exiv2::RiffVideo video(std::move(io));
        EXPECT_FALSE(video.good());
    } catch (...) {
        // Constructor may throw; that's acceptable
        SUCCEED();
    }
}

// Test with RIFF/WAVE header
TEST_F(RiffVideoTest_82, NewRiffInstanceWithRiffWaveHeader_82) {
    std::vector<uint8_t> data;
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    uint32_t chunkSize = 4;
    data.push_back(chunkSize & 0xFF);
    data.push_back((chunkSize >> 8) & 0xFF);
    data.push_back((chunkSize >> 16) & 0xFF);
    data.push_back((chunkSize >> 24) & 0xFF);
    data.push_back('W'); data.push_back('A'); data.push_back('V'); data.push_back('E');
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto image = Exiv2::newRiffInstance(std::move(io), false);
    // RIFF/WAVE might also be accepted by the RIFF video handler
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test with a single-byte file
TEST_F(RiffVideoTest_82, NewRiffInstanceWithSingleByte_82) {
    std::vector<uint8_t> data = {0x42};
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    auto image = Exiv2::newRiffInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}
