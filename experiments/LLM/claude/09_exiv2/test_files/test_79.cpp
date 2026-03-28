#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/riffvideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace Exiv2;

// Helper function to create a minimal valid RIFF/AVI file in memory
static std::vector<uint8_t> createMinimalRiffAvi() {
    // RIFF header: "RIFF" + size(4 bytes LE) + "AVI "
    // Minimal: just the RIFF container with AVI type
    std::vector<uint8_t> data;
    
    // "RIFF"
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    // Size placeholder (will fill later) - 4 bytes LE
    size_t sizePos = data.size();
    data.push_back(0); data.push_back(0); data.push_back(0); data.push_back(0);
    // "AVI "
    data.push_back('A'); data.push_back('V'); data.push_back('I'); data.push_back(' ');
    
    // Update size: total size - 8 (RIFF + size field)
    uint32_t riffSize = static_cast<uint32_t>(data.size() - 8);
    data[sizePos]     = static_cast<uint8_t>(riffSize & 0xFF);
    data[sizePos + 1] = static_cast<uint8_t>((riffSize >> 8) & 0xFF);
    data[sizePos + 2] = static_cast<uint8_t>((riffSize >> 16) & 0xFF);
    data[sizePos + 3] = static_cast<uint8_t>((riffSize >> 24) & 0xFF);
    
    return data;
}

// Helper to create a more complete RIFF/AVI with hdrl list
static std::vector<uint8_t> createRiffAviWithHeader() {
    std::vector<uint8_t> data;
    
    auto writeStr = [&](const char* s) {
        for (int i = 0; i < 4; i++) data.push_back(s[i]);
    };
    auto writeU32 = [&](uint32_t v) {
        data.push_back(v & 0xFF);
        data.push_back((v >> 8) & 0xFF);
        data.push_back((v >> 16) & 0xFF);
        data.push_back((v >> 24) & 0xFF);
    };
    
    // Build the inner content first
    std::vector<uint8_t> inner;
    auto innerWriteStr = [&](const char* s) {
        for (int i = 0; i < 4; i++) inner.push_back(s[i]);
    };
    auto innerWriteU32 = [&](uint32_t v) {
        inner.push_back(v & 0xFF);
        inner.push_back((v >> 8) & 0xFF);
        inner.push_back((v >> 16) & 0xFF);
        inner.push_back((v >> 24) & 0xFF);
    };
    
    // hdrl LIST containing avih chunk
    // avih chunk: 56 bytes of data
    std::vector<uint8_t> avih_data(56, 0);
    // Set some values: dwMicroSecPerFrame = 33333 (~30fps)
    uint32_t microSecPerFrame = 33333;
    avih_data[0] = microSecPerFrame & 0xFF;
    avih_data[1] = (microSecPerFrame >> 8) & 0xFF;
    avih_data[2] = (microSecPerFrame >> 16) & 0xFF;
    avih_data[3] = (microSecPerFrame >> 24) & 0xFF;
    // dwWidth at offset 32
    uint32_t width = 640;
    avih_data[32] = width & 0xFF;
    avih_data[33] = (width >> 8) & 0xFF;
    // dwHeight at offset 36
    uint32_t height = 480;
    avih_data[36] = height & 0xFF;
    avih_data[37] = (height >> 8) & 0xFF;
    
    // hdrl list content: "avih" chunk
    std::vector<uint8_t> hdrl_content;
    auto hdrlWriteStr = [&](const char* s) {
        for (int i = 0; i < 4; i++) hdrl_content.push_back(s[i]);
    };
    auto hdrlWriteU32 = [&](uint32_t v) {
        hdrl_content.push_back(v & 0xFF);
        hdrl_content.push_back((v >> 8) & 0xFF);
        hdrl_content.push_back((v >> 16) & 0xFF);
        hdrl_content.push_back((v >> 24) & 0xFF);
    };
    
    hdrlWriteStr("avih");
    hdrlWriteU32(static_cast<uint32_t>(avih_data.size()));
    hdrl_content.insert(hdrl_content.end(), avih_data.begin(), avih_data.end());
    
    // Build hdrl LIST
    innerWriteStr("LIST");
    innerWriteU32(static_cast<uint32_t>(hdrl_content.size() + 4)); // +4 for "hdrl"
    innerWriteStr("hdrl");
    inner.insert(inner.end(), hdrl_content.begin(), hdrl_content.end());
    
    // RIFF header
    writeStr("RIFF");
    writeU32(static_cast<uint32_t>(inner.size() + 4)); // +4 for "AVI "
    writeStr("AVI ");
    data.insert(data.end(), inner.begin(), inner.end());
    
    return data;
}

class RiffVideoTest_79 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    
    void TearDown() override {
    }
    
    std::unique_ptr<RiffVideo> createRiffVideoFromData(const std::vector<uint8_t>& data) {
        auto io = std::make_unique<MemIo>(data.data(), data.size());
        return std::make_unique<RiffVideo>(std::move(io));
    }
};

// Test: Constructor creates a valid RiffVideo object
TEST_F(RiffVideoTest_79, ConstructorCreatesValidObject_79) {
    auto data = createMinimalRiffAvi();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    ASSERT_NO_THROW(RiffVideo video(std::move(io)));
}

// Test: mimeType returns correct MIME type for RIFF video
TEST_F(RiffVideoTest_79, MimeTypeReturnsCorrectType_79) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromData(data);
    EXPECT_EQ(video->mimeType(), "video/riff");
}

// Test: readMetadata on minimal RIFF file
TEST_F(RiffVideoTest_79, ReadMetadataMinimalRiff_79) {
    auto data = createRiffAviWithHeader();
    auto video = createRiffVideoFromData(data);
    ASSERT_NO_THROW(video->readMetadata());
}

// Test: readMetadata on empty/invalid data throws
TEST_F(RiffVideoTest_79, ReadMetadataEmptyDataThrows_79) {
    std::vector<uint8_t> emptyData;
    auto io = std::make_unique<MemIo>(emptyData.data(), emptyData.size());
    auto video = std::make_unique<RiffVideo>(std::move(io));
    EXPECT_THROW(video->readMetadata(), Error);
}

// Test: readMetadata on truncated RIFF header throws
TEST_F(RiffVideoTest_79, ReadMetadataTruncatedHeaderThrows_79) {
    std::vector<uint8_t> truncData = {'R', 'I', 'F', 'F'};
    auto io = std::make_unique<MemIo>(truncData.data(), truncData.size());
    auto video = std::make_unique<RiffVideo>(std::move(io));
    EXPECT_THROW(video->readMetadata(), Error);
}

// Test: readMetadata on non-RIFF data throws
TEST_F(RiffVideoTest_79, ReadMetadataNonRiffThrows_79) {
    std::vector<uint8_t> nonRiff = {'N', 'O', 'T', 'R', 0, 0, 0, 0, 'A', 'V', 'I', ' '};
    auto io = std::make_unique<MemIo>(nonRiff.data(), nonRiff.size());
    auto video = std::make_unique<RiffVideo>(std::move(io));
    EXPECT_THROW(video->readMetadata(), Error);
}

// Test: writeMetadata throws (RIFF write is typically not supported)
TEST_F(RiffVideoTest_79, WriteMetadataThrows_79) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromData(data);
    EXPECT_THROW(video->writeMetadata(), Error);
}

// Test: good() returns true for valid io
TEST_F(RiffVideoTest_79, GoodReturnsTrueForValidIo_79) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromData(data);
    EXPECT_TRUE(video->good());
}

// Test: pixelWidth and pixelHeight initially zero
TEST_F(RiffVideoTest_79, PixelDimensionsInitiallyZero_79) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromData(data);
    EXPECT_EQ(video->pixelWidth(), 0u);
    EXPECT_EQ(video->pixelHeight(), 0u);
}

// Test: After readMetadata on valid AVI, dimensions may be populated
TEST_F(RiffVideoTest_79, ReadMetadataPopulatesDimensions_79) {
    auto data = createRiffAviWithHeader();
    auto video = createRiffVideoFromData(data);
    ASSERT_NO_THROW(video->readMetadata());
    // Dimensions should be set from the avih chunk
    EXPECT_EQ(video->pixelWidth(), 640u);
    EXPECT_EQ(video->pixelHeight(), 480u);
}

// Test: exifData accessible after construction
TEST_F(RiffVideoTest_79, ExifDataAccessible_79) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromData(data);
    ExifData& exif = video->exifData();
    EXPECT_TRUE(exif.empty());
}

// Test: xmpData accessible after construction
TEST_F(RiffVideoTest_79, XmpDataAccessible_79) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromData(data);
    XmpData& xmp = video->xmpData();
    EXPECT_TRUE(xmp.empty());
}

// Test: io() returns valid reference
TEST_F(RiffVideoTest_79, IoReturnsValidReference_79) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromData(data);
    const BasicIo& io = video->io();
    EXPECT_EQ(io.size(), data.size());
}

// Test: RIFF with wrong form type (not AVI) 
TEST_F(RiffVideoTest_79, ReadMetadataWrongFormType_79) {
    std::vector<uint8_t> data;
    // "RIFF"
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    // size = 4
    data.push_back(4); data.push_back(0); data.push_back(0); data.push_back(0);
    // "WAVE" instead of "AVI "
    data.push_back('W'); data.push_back('A'); data.push_back('V'); data.push_back('E');
    
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    auto video = std::make_unique<RiffVideo>(std::move(io));
    // May throw or handle differently depending on implementation
    EXPECT_THROW(video->readMetadata(), Error);
}

// Test: readMetadata with INFO list chunk containing metadata
TEST_F(RiffVideoTest_79, ReadMetadataWithInfoList_79) {
    std::vector<uint8_t> data;
    
    auto writeStr = [&](const char* s) {
        for (int i = 0; i < 4; i++) data.push_back(s[i]);
    };
    auto writeU32 = [&](uint32_t v) {
        data.push_back(v & 0xFF);
        data.push_back((v >> 8) & 0xFF);
        data.push_back((v >> 16) & 0xFF);
        data.push_back((v >> 24) & 0xFF);
    };
    
    // Build inner content
    std::vector<uint8_t> inner;
    auto iWriteStr = [&](const char* s) {
        for (int i = 0; i < 4; i++) inner.push_back(s[i]);
    };
    auto iWriteU32 = [&](uint32_t v) {
        inner.push_back(v & 0xFF);
        inner.push_back((v >> 8) & 0xFF);
        inner.push_back((v >> 16) & 0xFF);
        inner.push_back((v >> 24) & 0xFF);
    };
    
    // avih chunk (56 bytes)
    std::vector<uint8_t> avih_data(56, 0);
    uint32_t w = 320, h = 240;
    avih_data[32] = w & 0xFF; avih_data[33] = (w >> 8) & 0xFF;
    avih_data[36] = h & 0xFF; avih_data[37] = (h >> 8) & 0xFF;
    
    // hdrl LIST
    std::vector<uint8_t> hdrl;
    auto hWriteStr = [&](const char* s) {
        for (int i = 0; i < 4; i++) hdrl.push_back(s[i]);
    };
    auto hWriteU32 = [&](uint32_t v) {
        hdrl.push_back(v & 0xFF);
        hdrl.push_back((v >> 8) & 0xFF);
        hdrl.push_back((v >> 16) & 0xFF);
        hdrl.push_back((v >> 24) & 0xFF);
    };
    hWriteStr("avih");
    hWriteU32(56);
    hdrl.insert(hdrl.end(), avih_data.begin(), avih_data.end());
    
    iWriteStr("LIST");
    iWriteU32(static_cast<uint32_t>(hdrl.size() + 4));
    iWriteStr("hdrl");
    inner.insert(inner.end(), hdrl.begin(), hdrl.end());
    
    // INFO LIST with INAM tag
    std::string title = "Test Title";
    // Pad to even length if needed
    size_t titleLen = title.size() + 1; // null terminated
    if (titleLen % 2 != 0) titleLen++;
    
    std::vector<uint8_t> info;
    auto infoWriteStr = [&](const char* s) {
        for (int i = 0; i < 4; i++) info.push_back(s[i]);
    };
    auto infoWriteU32 = [&](uint32_t v) {
        info.push_back(v & 0xFF);
        info.push_back((v >> 8) & 0xFF);
        info.push_back((v >> 16) & 0xFF);
        info.push_back((v >> 24) & 0xFF);
    };
    infoWriteStr("INAM");
    infoWriteU32(static_cast<uint32_t>(title.size() + 1));
    for (char c : title) info.push_back(c);
    info.push_back(0); // null terminator
    if (info.size() % 2 != 0) info.push_back(0); // pad
    
    iWriteStr("LIST");
    iWriteU32(static_cast<uint32_t>(info.size() + 4));
    iWriteStr("INFO");
    inner.insert(inner.end(), info.begin(), info.end());
    
    // RIFF header
    writeStr("RIFF");
    writeU32(static_cast<uint32_t>(inner.size() + 4));
    writeStr("AVI ");
    data.insert(data.end(), inner.begin(), inner.end());
    
    auto video = createRiffVideoFromData(data);
    ASSERT_NO_THROW(video->readMetadata());
    EXPECT_EQ(video->pixelWidth(), 320u);
    EXPECT_EQ(video->pixelHeight(), 240u);
}

// Test: HeaderReader construction from valid io
TEST_F(RiffVideoTest_79, HeaderReaderFromValidIo_79) {
    // Create data that represents a chunk header: 4-byte ID + 4-byte size
    std::vector<uint8_t> headerData = {'L', 'I', 'S', 'T', 0x10, 0x00, 0x00, 0x00};
    auto io = std::make_unique<MemIo>(headerData.data(), headerData.size());
    io->open();
    
    ASSERT_NO_THROW({
        RiffVideo::HeaderReader reader(io);
        EXPECT_EQ(reader.getId(), "LIST");
        EXPECT_EQ(reader.getSize(), 16u);
    });
}

// Test: HeaderReader with zero size
TEST_F(RiffVideoTest_79, HeaderReaderZeroSize_79) {
    std::vector<uint8_t> headerData = {'J', 'U', 'N', 'K', 0x00, 0x00, 0x00, 0x00};
    auto io = std::make_unique<MemIo>(headerData.data(), headerData.size());
    io->open();
    
    RiffVideo::HeaderReader reader(io);
    EXPECT_EQ(reader.getId(), "JUNK");
    EXPECT_EQ(reader.getSize(), 0u);
}

// Test: clearMetadata works
TEST_F(RiffVideoTest_79, ClearMetadataWorks_79) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromData(data);
    ASSERT_NO_THROW(video->clearMetadata());
    EXPECT_TRUE(video->exifData().empty());
    EXPECT_TRUE(video->xmpData().empty());
}

// Test: setComment and getComment
TEST_F(RiffVideoTest_79, SetAndGetComment_79) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromData(data);
    video->setComment("test comment");
    EXPECT_EQ(video->comment(), "test comment");
}

// Test: Large size in RIFF header but truncated data
TEST_F(RiffVideoTest_79, ReadMetadataLargeSizeTruncated_79) {
    std::vector<uint8_t> data;
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    // Claim a very large size
    data.push_back(0xFF); data.push_back(0xFF); data.push_back(0xFF); data.push_back(0x0F);
    data.push_back('A'); data.push_back('V'); data.push_back('I'); data.push_back(' ');
    
    auto video = createRiffVideoFromData(data);
    // Should either throw or handle gracefully (not crash)
    try {
        video->readMetadata();
    } catch (const Error&) {
        // Expected - truncated data
    }
}

// Test: Multiple readMetadata calls
TEST_F(RiffVideoTest_79, MultipleReadMetadataCalls_79) {
    auto data = createRiffAviWithHeader();
    auto video = createRiffVideoFromData(data);
    ASSERT_NO_THROW(video->readMetadata());
    // Second call should also work (re-read)
    ASSERT_NO_THROW(video->readMetadata());
    EXPECT_EQ(video->pixelWidth(), 640u);
    EXPECT_EQ(video->pixelHeight(), 480u);
}

// Test: imageType returns riff
TEST_F(RiffVideoTest_79, ImageTypeIsRiff_79) {
    auto data = createMinimalRiffAvi();
    auto video = createRiffVideoFromData(data);
    EXPECT_EQ(video->imageType(), ImageType::riff);
}
