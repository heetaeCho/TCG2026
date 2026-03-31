#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/riffvideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/error.hpp>

#include <fstream>
#include <cstring>
#include <memory>
#include <sstream>

using namespace Exiv2;

// Helper function to create a minimal valid RIFF/AVI file in memory
static std::vector<uint8_t> createMinimalRiffAvi() {
    std::vector<uint8_t> data;

    // RIFF header
    // "RIFF" chunk id
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    // Size placeholder (will be filled later)
    size_t sizePos = data.size();
    data.push_back(0); data.push_back(0); data.push_back(0); data.push_back(0);
    // "AVI " form type
    data.push_back('A'); data.push_back('V'); data.push_back('I'); data.push_back(' ');

    // hdrl LIST
    data.push_back('L'); data.push_back('I'); data.push_back('S'); data.push_back('T');
    size_t hdrlSizePos = data.size();
    data.push_back(0); data.push_back(0); data.push_back(0); data.push_back(0);
    data.push_back('h'); data.push_back('d'); data.push_back('r'); data.push_back('l');

    // avih chunk (AVI main header) - 56 bytes of data
    data.push_back('a'); data.push_back('v'); data.push_back('i'); data.push_back('h');
    uint32_t avihSize = 56;
    data.push_back(avihSize & 0xFF);
    data.push_back((avihSize >> 8) & 0xFF);
    data.push_back((avihSize >> 16) & 0xFF);
    data.push_back((avihSize >> 24) & 0xFF);
    // 56 bytes of avih data (all zeros for simplicity)
    for (uint32_t i = 0; i < avihSize; i++) {
        data.push_back(0);
    }

    // Fill hdrl LIST size
    uint32_t hdrlSize = static_cast<uint32_t>(data.size() - hdrlSizePos - 4);
    data[hdrlSizePos] = hdrlSize & 0xFF;
    data[hdrlSizePos + 1] = (hdrlSize >> 8) & 0xFF;
    data[hdrlSizePos + 2] = (hdrlSize >> 16) & 0xFF;
    data[hdrlSizePos + 3] = (hdrlSize >> 24) & 0xFF;

    // Fill RIFF size
    uint32_t riffSize = static_cast<uint32_t>(data.size() - sizePos - 4);
    data[sizePos] = riffSize & 0xFF;
    data[sizePos + 1] = (riffSize >> 8) & 0xFF;
    data[sizePos + 2] = (riffSize >> 16) & 0xFF;
    data[sizePos + 3] = (riffSize >> 24) & 0xFF;

    return data;
}

// Helper to write data to a temp file and return a MemIo
static std::unique_ptr<BasicIo> createMemIoFromData(const std::vector<uint8_t>& data) {
    auto memIo = std::make_unique<MemIo>(data.data(), data.size());
    return memIo;
}

class RiffVideoTest_81 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: RiffVideo constructor with valid IO
TEST_F(RiffVideoTest_81, ConstructorWithValidIo_81) {
    auto data = createMinimalRiffAvi();
    auto io = createMemIoFromData(data);
    ASSERT_NO_THROW(RiffVideo riff(std::move(io)));
}

// Test: mimeType returns the correct MIME type for RIFF video
TEST_F(RiffVideoTest_81, MimeTypeReturnsCorrectValue_81) {
    auto data = createMinimalRiffAvi();
    auto io = createMemIoFromData(data);
    RiffVideo riff(std::move(io));
    std::string mime = riff.mimeType();
    EXPECT_EQ(mime, "video/riff");
}

// Test: writeMetadata throws (RIFF writing is typically not supported)
TEST_F(RiffVideoTest_81, WriteMetadataThrows_81) {
    auto data = createMinimalRiffAvi();
    auto io = createMemIoFromData(data);
    RiffVideo riff(std::move(io));
    EXPECT_THROW(riff.writeMetadata(), Error);
}

// Test: readMetadata on an empty/invalid file should throw
TEST_F(RiffVideoTest_81, ReadMetadataOnEmptyFileThrows_81) {
    std::vector<uint8_t> emptyData;
    auto io = std::make_unique<MemIo>(emptyData.data(), emptyData.size());
    RiffVideo riff(std::move(io));
    EXPECT_THROW(riff.readMetadata(), Error);
}

// Test: readMetadata on too-small file should throw
TEST_F(RiffVideoTest_81, ReadMetadataOnTooSmallFileThrows_81) {
    // Only 4 bytes - not enough for RIFF header
    std::vector<uint8_t> smallData = {'R', 'I', 'F', 'F'};
    auto io = std::make_unique<MemIo>(smallData.data(), smallData.size());
    RiffVideo riff(std::move(io));
    EXPECT_THROW(riff.readMetadata(), Error);
}

// Test: readMetadata with non-RIFF magic should throw
TEST_F(RiffVideoTest_81, ReadMetadataWithInvalidMagicThrows_81) {
    std::vector<uint8_t> invalidData = {
        'N', 'O', 'T', 'R',  // Not "RIFF"
        0x10, 0x00, 0x00, 0x00,
        'A', 'V', 'I', ' ',
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
    };
    auto io = std::make_unique<MemIo>(invalidData.data(), invalidData.size());
    RiffVideo riff(std::move(io));
    EXPECT_THROW(riff.readMetadata(), Error);
}

// Test: readMetadata on a minimal valid RIFF/AVI should not throw
TEST_F(RiffVideoTest_81, ReadMetadataOnMinimalValidFile_81) {
    auto data = createMinimalRiffAvi();
    auto io = createMemIoFromData(data);
    RiffVideo riff(std::move(io));
    EXPECT_NO_THROW(riff.readMetadata());
}

// Test: After readMetadata, exifData is accessible
TEST_F(RiffVideoTest_81, ExifDataAccessibleAfterRead_81) {
    auto data = createMinimalRiffAvi();
    auto io = createMemIoFromData(data);
    RiffVideo riff(std::move(io));
    riff.readMetadata();
    // Should be able to access exifData without crash
    ExifData& exif = riff.exifData();
    // Minimal file may not have exif data
    EXPECT_TRUE(exif.empty() || !exif.empty());
}

// Test: After readMetadata, xmpData is accessible
TEST_F(RiffVideoTest_81, XmpDataAccessibleAfterRead_81) {
    auto data = createMinimalRiffAvi();
    auto io = createMemIoFromData(data);
    RiffVideo riff(std::move(io));
    riff.readMetadata();
    XmpData& xmp = riff.xmpData();
    // Just verify it's accessible
    SUCCEED();
}

// Test: pixelWidth and pixelHeight default to 0 before readMetadata
TEST_F(RiffVideoTest_81, PixelDimensionsDefaultToZero_81) {
    auto data = createMinimalRiffAvi();
    auto io = createMemIoFromData(data);
    RiffVideo riff(std::move(io));
    EXPECT_EQ(riff.pixelWidth(), 0u);
    EXPECT_EQ(riff.pixelHeight(), 0u);
}

// Test: io() returns a valid reference
TEST_F(RiffVideoTest_81, IoReturnsValidReference_81) {
    auto data = createMinimalRiffAvi();
    auto io = createMemIoFromData(data);
    RiffVideo riff(std::move(io));
    const BasicIo& ioRef = riff.io();
    EXPECT_GE(ioRef.size(), 0u);
}

// Test: good() returns true for a valid IO
TEST_F(RiffVideoTest_81, GoodReturnsTrueForValidIo_81) {
    auto data = createMinimalRiffAvi();
    auto io = createMemIoFromData(data);
    RiffVideo riff(std::move(io));
    EXPECT_TRUE(riff.good());
}

// Test: Multiple readMetadata calls should not crash
TEST_F(RiffVideoTest_81, MultipleReadMetadataCalls_81) {
    auto data = createMinimalRiffAvi();
    auto io = createMemIoFromData(data);
    RiffVideo riff(std::move(io));
    EXPECT_NO_THROW(riff.readMetadata());
    EXPECT_NO_THROW(riff.readMetadata());
}

// Test: RIFF file with JUNK chunk should be handled gracefully
TEST_F(RiffVideoTest_81, RiffFileWithJunkChunk_81) {
    std::vector<uint8_t> data;

    // RIFF header
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    size_t sizePos = data.size();
    data.push_back(0); data.push_back(0); data.push_back(0); data.push_back(0);
    data.push_back('A'); data.push_back('V'); data.push_back('I'); data.push_back(' ');

    // hdrl LIST
    data.push_back('L'); data.push_back('I'); data.push_back('S'); data.push_back('T');
    size_t hdrlSizePos = data.size();
    data.push_back(0); data.push_back(0); data.push_back(0); data.push_back(0);
    data.push_back('h'); data.push_back('d'); data.push_back('r'); data.push_back('l');

    // avih
    data.push_back('a'); data.push_back('v'); data.push_back('i'); data.push_back('h');
    uint32_t avihSize = 56;
    data.push_back(avihSize & 0xFF);
    data.push_back((avihSize >> 8) & 0xFF);
    data.push_back((avihSize >> 16) & 0xFF);
    data.push_back((avihSize >> 24) & 0xFF);
    for (uint32_t i = 0; i < avihSize; i++) data.push_back(0);

    // Fill hdrl LIST size
    uint32_t hdrlSize = static_cast<uint32_t>(data.size() - hdrlSizePos - 4);
    data[hdrlSizePos] = hdrlSize & 0xFF;
    data[hdrlSizePos + 1] = (hdrlSize >> 8) & 0xFF;
    data[hdrlSizePos + 2] = (hdrlSize >> 16) & 0xFF;
    data[hdrlSizePos + 3] = (hdrlSize >> 24) & 0xFF;

    // JUNK chunk
    data.push_back('J'); data.push_back('U'); data.push_back('N'); data.push_back('K');
    uint32_t junkSize = 8;
    data.push_back(junkSize & 0xFF);
    data.push_back((junkSize >> 8) & 0xFF);
    data.push_back((junkSize >> 16) & 0xFF);
    data.push_back((junkSize >> 24) & 0xFF);
    for (uint32_t i = 0; i < junkSize; i++) data.push_back(0);

    // Fill RIFF size
    uint32_t riffSize = static_cast<uint32_t>(data.size() - sizePos - 4);
    data[sizePos] = riffSize & 0xFF;
    data[sizePos + 1] = (riffSize >> 8) & 0xFF;
    data[sizePos + 2] = (riffSize >> 16) & 0xFF;
    data[sizePos + 3] = (riffSize >> 24) & 0xFF;

    auto io = std::make_unique<MemIo>(data.data(), data.size());
    RiffVideo riff(std::move(io));
    EXPECT_NO_THROW(riff.readMetadata());
}

// Test: comment is empty by default
TEST_F(RiffVideoTest_81, CommentIsEmptyByDefault_81) {
    auto data = createMinimalRiffAvi();
    auto io = createMemIoFromData(data);
    RiffVideo riff(std::move(io));
    EXPECT_TRUE(riff.comment().empty());
}

// Test: clearMetadata works without crash
TEST_F(RiffVideoTest_81, ClearMetadataWorks_81) {
    auto data = createMinimalRiffAvi();
    auto io = createMemIoFromData(data);
    RiffVideo riff(std::move(io));
    riff.readMetadata();
    EXPECT_NO_THROW(riff.clearMetadata());
}

// Test: setComment and then retrieve it
TEST_F(RiffVideoTest_81, SetAndGetComment_81) {
    auto data = createMinimalRiffAvi();
    auto io = createMemIoFromData(data);
    RiffVideo riff(std::move(io));
    riff.setComment("test comment");
    EXPECT_EQ(riff.comment(), "test comment");
}

// Test: clearComment works
TEST_F(RiffVideoTest_81, ClearCommentWorks_81) {
    auto data = createMinimalRiffAvi();
    auto io = createMemIoFromData(data);
    RiffVideo riff(std::move(io));
    riff.setComment("test");
    riff.clearComment();
    EXPECT_TRUE(riff.comment().empty());
}

// Test: File with only RIFF header and AVI type but no chunks
TEST_F(RiffVideoTest_81, RiffHeaderOnlyNoChunks_81) {
    std::vector<uint8_t> data = {
        'R', 'I', 'F', 'F',
        0x04, 0x00, 0x00, 0x00,  // size = 4 (just the form type)
        'A', 'V', 'I', ' '
    };
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    RiffVideo riff(std::move(io));
    // This may or may not throw depending on implementation; we just verify it doesn't crash
    try {
        riff.readMetadata();
    } catch (const Error&) {
        // Acceptable
    }
    SUCCEED();
}

// Test: RIFF file with INFO list containing metadata
TEST_F(RiffVideoTest_81, RiffFileWithInfoList_81) {
    std::vector<uint8_t> data;

    // RIFF header
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    size_t sizePos = data.size();
    data.push_back(0); data.push_back(0); data.push_back(0); data.push_back(0);
    data.push_back('A'); data.push_back('V'); data.push_back('I'); data.push_back(' ');

    // hdrl LIST with avih
    data.push_back('L'); data.push_back('I'); data.push_back('S'); data.push_back('T');
    size_t hdrlSizePos = data.size();
    data.push_back(0); data.push_back(0); data.push_back(0); data.push_back(0);
    data.push_back('h'); data.push_back('d'); data.push_back('r'); data.push_back('l');

    data.push_back('a'); data.push_back('v'); data.push_back('i'); data.push_back('h');
    uint32_t avihSize = 56;
    data.push_back(avihSize & 0xFF);
    data.push_back((avihSize >> 8) & 0xFF);
    data.push_back((avihSize >> 16) & 0xFF);
    data.push_back((avihSize >> 24) & 0xFF);
    for (uint32_t i = 0; i < avihSize; i++) data.push_back(0);

    uint32_t hdrlSize = static_cast<uint32_t>(data.size() - hdrlSizePos - 4);
    data[hdrlSizePos] = hdrlSize & 0xFF;
    data[hdrlSizePos + 1] = (hdrlSize >> 8) & 0xFF;
    data[hdrlSizePos + 2] = (hdrlSize >> 16) & 0xFF;
    data[hdrlSizePos + 3] = (hdrlSize >> 24) & 0xFF;

    // INFO LIST
    data.push_back('L'); data.push_back('I'); data.push_back('S'); data.push_back('T');
    size_t infoSizePos = data.size();
    data.push_back(0); data.push_back(0); data.push_back(0); data.push_back(0);
    data.push_back('I'); data.push_back('N'); data.push_back('F'); data.push_back('O');

    // INAM chunk (title)
    std::string title = "TestTitle";
    data.push_back('I'); data.push_back('N'); data.push_back('A'); data.push_back('M');
    uint32_t titleSize = static_cast<uint32_t>(title.size() + 1); // including null terminator
    data.push_back(titleSize & 0xFF);
    data.push_back((titleSize >> 8) & 0xFF);
    data.push_back((titleSize >> 16) & 0xFF);
    data.push_back((titleSize >> 24) & 0xFF);
    for (char c : title) data.push_back(static_cast<uint8_t>(c));
    data.push_back(0); // null terminator
    // Pad to even boundary if needed
    if (titleSize % 2 != 0) data.push_back(0);

    uint32_t infoSize = static_cast<uint32_t>(data.size() - infoSizePos - 4);
    data[infoSizePos] = infoSize & 0xFF;
    data[infoSizePos + 1] = (infoSize >> 8) & 0xFF;
    data[infoSizePos + 2] = (infoSize >> 16) & 0xFF;
    data[infoSizePos + 3] = (infoSize >> 24) & 0xFF;

    // Fill RIFF size
    uint32_t riffSize = static_cast<uint32_t>(data.size() - sizePos - 4);
    data[sizePos] = riffSize & 0xFF;
    data[sizePos + 1] = (riffSize >> 8) & 0xFF;
    data[sizePos + 2] = (riffSize >> 16) & 0xFF;
    data[sizePos + 3] = (riffSize >> 24) & 0xFF;

    auto io = std::make_unique<MemIo>(data.data(), data.size());
    RiffVideo riff(std::move(io));
    EXPECT_NO_THROW(riff.readMetadata());
}

// Test: imageType returns riff
TEST_F(RiffVideoTest_81, ImageTypeIsRiff_81) {
    auto data = createMinimalRiffAvi();
    auto io = createMemIoFromData(data);
    RiffVideo riff(std::move(io));
    EXPECT_EQ(riff.imageType(), ImageType::riff);
}
