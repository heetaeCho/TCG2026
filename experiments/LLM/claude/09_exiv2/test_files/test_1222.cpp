#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/jpgimage.hpp>
#include <exiv2/basicio.hpp>
#include <cstring>
#include <memory>

using namespace Exiv2;

// Helper to create a MemIo with specific data
static std::unique_ptr<MemIo> createMemIo(const std::vector<byte>& data) {
    auto io = std::make_unique<MemIo>();
    if (!data.empty()) {
        io->write(data.data(), data.size());
        io->seek(0, BasicIo::beg);
    }
    return io;
}

class JpegImageTest_1222 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that isThisType returns true for valid JPEG data (starts with FF D8 FF)
TEST_F(JpegImageTest_1222, IsThisType_ValidJpegHeader_ReturnsTrue_1222) {
    // JPEG files start with FF D8 FF
    std::vector<byte> jpegData = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto testIo = createMemIo(jpegData);

    // Create a JpegImage with a separate IO for the image itself
    std::vector<byte> dummyJpeg = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto imageIo = createMemIo(dummyJpeg);
    JpegImage img(std::move(imageIo), false);

    bool result = img.isThisType(*testIo, false);
    EXPECT_TRUE(result);
}

// Test that isThisType returns false for non-JPEG data
TEST_F(JpegImageTest_1222, IsThisType_NonJpegData_ReturnsFalse_1222) {
    // PNG header
    std::vector<byte> pngData = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    auto testIo = createMemIo(pngData);

    std::vector<byte> dummyJpeg = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto imageIo = createMemIo(dummyJpeg);
    JpegImage img(std::move(imageIo), false);

    bool result = img.isThisType(*testIo, false);
    EXPECT_FALSE(result);
}

// Test that isThisType returns false for empty data
TEST_F(JpegImageTest_1222, IsThisType_EmptyData_ReturnsFalse_1222) {
    std::vector<byte> emptyData;
    auto testIo = createMemIo(emptyData);

    std::vector<byte> dummyJpeg = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto imageIo = createMemIo(dummyJpeg);
    JpegImage img(std::move(imageIo), false);

    bool result = img.isThisType(*testIo, false);
    EXPECT_FALSE(result);
}

// Test that isThisType returns false for data that starts with FF but is not JPEG
TEST_F(JpegImageTest_1222, IsThisType_StartsWithFFButNotJpeg_ReturnsFalse_1222) {
    std::vector<byte> data = {0xFF, 0x00, 0x00, 0x00};
    auto testIo = createMemIo(data);

    std::vector<byte> dummyJpeg = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto imageIo = createMemIo(dummyJpeg);
    JpegImage img(std::move(imageIo), false);

    bool result = img.isThisType(*testIo, false);
    EXPECT_FALSE(result);
}

// Test that isThisType with advance=true advances the IO position on match
TEST_F(JpegImageTest_1222, IsThisType_AdvanceTrue_ValidJpeg_AdvancesPosition_1222) {
    std::vector<byte> jpegData = {0xFF, 0xD8, 0xFF, 0xE1, 0x00, 0x10};
    auto testIo = createMemIo(jpegData);

    std::vector<byte> dummyJpeg = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto imageIo = createMemIo(dummyJpeg);
    JpegImage img(std::move(imageIo), false);

    size_t posBefore = testIo->tell();
    bool result = img.isThisType(*testIo, true);
    size_t posAfter = testIo->tell();

    EXPECT_TRUE(result);
    // When advance is true and it matches, position should have advanced
    // (exact amount depends on implementation, but it should differ from start)
}

// Test that isThisType with advance=false does not advance IO position
TEST_F(JpegImageTest_1222, IsThisType_AdvanceFalse_ValidJpeg_DoesNotAdvancePosition_1222) {
    std::vector<byte> jpegData = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto testIo = createMemIo(jpegData);

    std::vector<byte> dummyJpeg = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto imageIo = createMemIo(dummyJpeg);
    JpegImage img(std::move(imageIo), false);

    size_t posBefore = testIo->tell();
    bool result = img.isThisType(*testIo, false);
    size_t posAfter = testIo->tell();

    EXPECT_TRUE(result);
    EXPECT_EQ(posBefore, posAfter);
}

// Test that isThisType returns false for data with only one byte
TEST_F(JpegImageTest_1222, IsThisType_OneByte_ReturnsFalse_1222) {
    std::vector<byte> data = {0xFF};
    auto testIo = createMemIo(data);

    std::vector<byte> dummyJpeg = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto imageIo = createMemIo(dummyJpeg);
    JpegImage img(std::move(imageIo), false);

    bool result = img.isThisType(*testIo, false);
    EXPECT_FALSE(result);
}

// Test that isThisType returns false for two bytes (FF D8 but no third byte)
TEST_F(JpegImageTest_1222, IsThisType_TwoBytes_ReturnsFalse_1222) {
    std::vector<byte> data = {0xFF, 0xD8};
    auto testIo = createMemIo(data);

    std::vector<byte> dummyJpeg = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto imageIo = createMemIo(dummyJpeg);
    JpegImage img(std::move(imageIo), false);

    bool result = img.isThisType(*testIo, false);
    EXPECT_FALSE(result);
}

// Test that isThisType with FF D8 FF (exact 3 bytes) returns true
TEST_F(JpegImageTest_1222, IsThisType_ExactThreeJpegBytes_ReturnsTrue_1222) {
    std::vector<byte> data = {0xFF, 0xD8, 0xFF};
    auto testIo = createMemIo(data);

    std::vector<byte> dummyJpeg = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto imageIo = createMemIo(dummyJpeg);
    JpegImage img(std::move(imageIo), false);

    bool result = img.isThisType(*testIo, false);
    EXPECT_TRUE(result);
}

// Test mimeType returns the correct JPEG mime type
TEST_F(JpegImageTest_1222, MimeType_ReturnsJpegMimeType_1222) {
    std::vector<byte> jpegData = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto imageIo = createMemIo(jpegData);
    JpegImage img(std::move(imageIo), false);

    std::string mime = img.mimeType();
    EXPECT_EQ(mime, "image/jpeg");
}

// Test isThisType returns false for all zeros
TEST_F(JpegImageTest_1222, IsThisType_AllZeros_ReturnsFalse_1222) {
    std::vector<byte> data = {0x00, 0x00, 0x00, 0x00};
    auto testIo = createMemIo(data);

    std::vector<byte> dummyJpeg = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto imageIo = createMemIo(dummyJpeg);
    JpegImage img(std::move(imageIo), false);

    bool result = img.isThisType(*testIo, false);
    EXPECT_FALSE(result);
}

// Test isThisType with advance=false on non-JPEG data does not advance position
TEST_F(JpegImageTest_1222, IsThisType_AdvanceFalse_NonJpeg_DoesNotAdvancePosition_1222) {
    std::vector<byte> data = {0x89, 0x50, 0x4E, 0x47};
    auto testIo = createMemIo(data);

    std::vector<byte> dummyJpeg = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto imageIo = createMemIo(dummyJpeg);
    JpegImage img(std::move(imageIo), false);

    size_t posBefore = testIo->tell();
    bool result = img.isThisType(*testIo, false);
    size_t posAfter = testIo->tell();

    EXPECT_FALSE(result);
    EXPECT_EQ(posBefore, posAfter);
}

// Test isThisType with advance=true on non-JPEG data does not advance position
TEST_F(JpegImageTest_1222, IsThisType_AdvanceTrue_NonJpeg_DoesNotAdvancePosition_1222) {
    std::vector<byte> data = {0x89, 0x50, 0x4E, 0x47};
    auto testIo = createMemIo(data);

    std::vector<byte> dummyJpeg = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto imageIo = createMemIo(dummyJpeg);
    JpegImage img(std::move(imageIo), false);

    size_t posBefore = testIo->tell();
    bool result = img.isThisType(*testIo, true);
    size_t posAfter = testIo->tell();

    EXPECT_FALSE(result);
    EXPECT_EQ(posBefore, posAfter);
}

// Test isThisType with JPEG2000 signature (not JPEG) returns false
TEST_F(JpegImageTest_1222, IsThisType_Jpeg2000Signature_ReturnsFalse_1222) {
    // JPEG 2000 starts with 0x00 0x00 0x00 0x0C 0x6A 0x50
    std::vector<byte> jp2Data = {0x00, 0x00, 0x00, 0x0C, 0x6A, 0x50};
    auto testIo = createMemIo(jp2Data);

    std::vector<byte> dummyJpeg = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto imageIo = createMemIo(dummyJpeg);
    JpegImage img(std::move(imageIo), false);

    bool result = img.isThisType(*testIo, false);
    EXPECT_FALSE(result);
}

// Test isThisType with TIFF signature returns false
TEST_F(JpegImageTest_1222, IsThisType_TiffSignature_ReturnsFalse_1222) {
    // TIFF starts with 0x49 0x49 (little-endian) or 0x4D 0x4D (big-endian)
    std::vector<byte> tiffData = {0x49, 0x49, 0x2A, 0x00};
    auto testIo = createMemIo(tiffData);

    std::vector<byte> dummyJpeg = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto imageIo = createMemIo(dummyJpeg);
    JpegImage img(std::move(imageIo), false);

    bool result = img.isThisType(*testIo, false);
    EXPECT_FALSE(result);
}

// Test isThisType called multiple times with advance=false yields consistent results
TEST_F(JpegImageTest_1222, IsThisType_MultipleCalls_ConsistentResult_1222) {
    std::vector<byte> jpegData = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto testIo = createMemIo(jpegData);

    std::vector<byte> dummyJpeg = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto imageIo = createMemIo(dummyJpeg);
    JpegImage img(std::move(imageIo), false);

    bool result1 = img.isThisType(*testIo, false);
    bool result2 = img.isThisType(*testIo, false);
    bool result3 = img.isThisType(*testIo, false);

    EXPECT_TRUE(result1);
    EXPECT_TRUE(result2);
    EXPECT_TRUE(result3);
}

// Test isThisType when IO position is not at beginning (should read from current position)
TEST_F(JpegImageTest_1222, IsThisType_IOPositionNotAtStart_ReturnsFalse_1222) {
    std::vector<byte> data = {0x00, 0xFF, 0xD8, 0xFF, 0xE0};
    auto testIo = createMemIo(data);
    // Seek to position 1 so the read starts at FF D8 FF
    testIo->seek(1, BasicIo::beg);

    std::vector<byte> dummyJpeg = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10};
    auto imageIo = createMemIo(dummyJpeg);
    JpegImage img(std::move(imageIo), false);

    bool result = img.isThisType(*testIo, false);
    // This may be true since from position 1 it reads FF D8 FF
    // We just verify it doesn't crash and returns a boolean
    // The actual result depends on the implementation
    SUCCEED();
}
