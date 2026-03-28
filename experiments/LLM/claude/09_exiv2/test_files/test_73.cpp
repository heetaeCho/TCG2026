#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/webpimage.hpp>
#include <exiv2/basicio.hpp>
#include <cstring>
#include <vector>

// Helper function to create a MemIo with specific content
static std::unique_ptr<Exiv2::MemIo> createMemIo(const std::vector<Exiv2::byte>& data) {
    auto memIo = std::make_unique<Exiv2::MemIo>();
    if (!data.empty()) {
        memIo->write(data.data(), data.size());
        memIo->seek(0, Exiv2::BasicIo::beg);
    }
    return memIo;
}

class WebPImageTest_73 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Valid WebP file signature should return true
TEST_F(WebPImageTest_73, ValidWebPSignature_73) {
    // RIFF????WEBP
    std::vector<Exiv2::byte> data = {
        'R', 'I', 'F', 'F',   // RIFF header
        0x00, 0x00, 0x00, 0x00, // file size (dummy)
        'W', 'E', 'B', 'P'    // WEBP identifier
    };
    auto io = createMemIo(data);
    EXPECT_TRUE(Exiv2::isWebPType(*io, false));
}

// Test: File too small (less than 12 bytes) should return false
TEST_F(WebPImageTest_73, FileTooSmall_73) {
    std::vector<Exiv2::byte> data = {'R', 'I', 'F', 'F', 0x00, 0x00, 0x00, 0x00, 'W', 'E', 'B'};
    auto io = createMemIo(data);
    EXPECT_FALSE(Exiv2::isWebPType(*io, false));
}

// Test: Empty file should return false
TEST_F(WebPImageTest_73, EmptyFile_73) {
    std::vector<Exiv2::byte> data;
    auto io = createMemIo(data);
    EXPECT_FALSE(Exiv2::isWebPType(*io, false));
}

// Test: Wrong RIFF header should return false
TEST_F(WebPImageTest_73, WrongRIFFHeader_73) {
    std::vector<Exiv2::byte> data = {
        'X', 'I', 'F', 'F',   // Wrong header
        0x00, 0x00, 0x00, 0x00,
        'W', 'E', 'B', 'P'
    };
    auto io = createMemIo(data);
    EXPECT_FALSE(Exiv2::isWebPType(*io, false));
}

// Test: Wrong WEBP identifier should return false
TEST_F(WebPImageTest_73, WrongWEBPIdentifier_73) {
    std::vector<Exiv2::byte> data = {
        'R', 'I', 'F', 'F',
        0x00, 0x00, 0x00, 0x00,
        'W', 'E', 'B', 'X'    // Wrong WEBP identifier
    };
    auto io = createMemIo(data);
    EXPECT_FALSE(Exiv2::isWebPType(*io, false));
}

// Test: Both RIFF and WEBP wrong should return false
TEST_F(WebPImageTest_73, BothHeadersWrong_73) {
    std::vector<Exiv2::byte> data = {
        'X', 'X', 'X', 'X',
        0x00, 0x00, 0x00, 0x00,
        'Y', 'Y', 'Y', 'Y'
    };
    auto io = createMemIo(data);
    EXPECT_FALSE(Exiv2::isWebPType(*io, false));
}

// Test: Exactly 12 bytes with valid signature should return true
TEST_F(WebPImageTest_73, Exactly12BytesValid_73) {
    std::vector<Exiv2::byte> data = {
        'R', 'I', 'F', 'F',
        0x01, 0x02, 0x03, 0x04,
        'W', 'E', 'B', 'P'
    };
    auto io = createMemIo(data);
    EXPECT_TRUE(Exiv2::isWebPType(*io, false));
}

// Test: File position is restored after calling isWebPType
TEST_F(WebPImageTest_73, FilePositionRestoredAfterCall_73) {
    std::vector<Exiv2::byte> data = {
        'R', 'I', 'F', 'F',
        0x00, 0x00, 0x00, 0x00,
        'W', 'E', 'B', 'P',
        0xDE, 0xAD
    };
    auto io = createMemIo(data);
    long posBefore = io->tell();
    Exiv2::isWebPType(*io, false);
    long posAfter = io->tell();
    EXPECT_EQ(posBefore, posAfter);
}

// Test: Valid signature with extra data after header
TEST_F(WebPImageTest_73, ValidSignatureWithExtraData_73) {
    std::vector<Exiv2::byte> data = {
        'R', 'I', 'F', 'F',
        0x10, 0x00, 0x00, 0x00,
        'W', 'E', 'B', 'P',
        0x56, 0x50, 0x38, 0x20, // VP8 chunk
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    auto io = createMemIo(data);
    EXPECT_TRUE(Exiv2::isWebPType(*io, false));
}

// Test: File with 11 bytes should return false
TEST_F(WebPImageTest_73, ElevenBytes_73) {
    std::vector<Exiv2::byte> data(11, 0x00);
    auto io = createMemIo(data);
    EXPECT_FALSE(Exiv2::isWebPType(*io, false));
}

// Test: Null bytes should return false
TEST_F(WebPImageTest_73, AllNullBytes_73) {
    std::vector<Exiv2::byte> data(12, 0x00);
    auto io = createMemIo(data);
    EXPECT_FALSE(Exiv2::isWebPType(*io, false));
}

// Test: RIFF correct but WEBP is lowercase should return false
TEST_F(WebPImageTest_73, LowercaseWEBP_73) {
    std::vector<Exiv2::byte> data = {
        'R', 'I', 'F', 'F',
        0x00, 0x00, 0x00, 0x00,
        'w', 'e', 'b', 'p'    // lowercase
    };
    auto io = createMemIo(data);
    EXPECT_FALSE(Exiv2::isWebPType(*io, false));
}

// Test: Lowercase RIFF should return false
TEST_F(WebPImageTest_73, LowercaseRIFF_73) {
    std::vector<Exiv2::byte> data = {
        'r', 'i', 'f', 'f',
        0x00, 0x00, 0x00, 0x00,
        'W', 'E', 'B', 'P'
    };
    auto io = createMemIo(data);
    EXPECT_FALSE(Exiv2::isWebPType(*io, false));
}

// Test: Calling isWebPType multiple times yields same result
TEST_F(WebPImageTest_73, MultipleCallsConsistent_73) {
    std::vector<Exiv2::byte> data = {
        'R', 'I', 'F', 'F',
        0x00, 0x00, 0x00, 0x00,
        'W', 'E', 'B', 'P'
    };
    auto io = createMemIo(data);
    EXPECT_TRUE(Exiv2::isWebPType(*io, false));
    EXPECT_TRUE(Exiv2::isWebPType(*io, false));
    EXPECT_TRUE(Exiv2::isWebPType(*io, false));
}

// Test: Non-WebP RIFF file (e.g., AVI) should return false
TEST_F(WebPImageTest_73, RIFFButAVI_73) {
    std::vector<Exiv2::byte> data = {
        'R', 'I', 'F', 'F',
        0x00, 0x00, 0x00, 0x00,
        'A', 'V', 'I', ' '    // AVI format
    };
    auto io = createMemIo(data);
    EXPECT_FALSE(Exiv2::isWebPType(*io, false));
}

// Test: Non-WebP RIFF file (e.g., WAVE) should return false
TEST_F(WebPImageTest_73, RIFFButWAVE_73) {
    std::vector<Exiv2::byte> data = {
        'R', 'I', 'F', 'F',
        0x00, 0x00, 0x00, 0x00,
        'W', 'A', 'V', 'E'    // WAVE format
    };
    auto io = createMemIo(data);
    EXPECT_FALSE(Exiv2::isWebPType(*io, false));
}

// Test: Calling from non-zero position on a larger file
TEST_F(WebPImageTest_73, CalledFromNonZeroPosition_73) {
    // Add some prefix bytes, then the WebP header
    std::vector<Exiv2::byte> data = {
        0x00, 0x00, 0x00, 0x00, // 4 bytes prefix
        'R', 'I', 'F', 'F',
        0x00, 0x00, 0x00, 0x00,
        'W', 'E', 'B', 'P'
    };
    auto io = createMemIo(data);
    io->seek(4, Exiv2::BasicIo::beg);
    // Reading from position 4, the 12 bytes form valid WebP
    EXPECT_TRUE(Exiv2::isWebPType(*io, false));
    // Position should be restored to 4
    EXPECT_EQ(io->tell(), 4);
}

// Test: One byte file should return false
TEST_F(WebPImageTest_73, OneByteFile_73) {
    std::vector<Exiv2::byte> data = {0x42};
    auto io = createMemIo(data);
    EXPECT_FALSE(Exiv2::isWebPType(*io, false));
}
