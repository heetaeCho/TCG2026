#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/riffvideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <cstring>
#include <memory>
#include <vector>

using namespace Exiv2;

// We need a mock HeaderReader since HeaderReader reads from IO in constructor.
// We'll create a helper that builds valid RIFF data and uses HeaderReader properly.

namespace {

// Helper to create a minimal AVI file in memory with specific chunk structure
std::vector<uint8_t> createMinimalRiffData(const std::string& chunkId, uint32_t chunkSize, 
                                            const std::vector<uint8_t>& chunkData = {}) {
    std::vector<uint8_t> data;
    
    // RIFF header
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    
    // RIFF size (placeholder, will be filled)
    uint32_t riffSize = 4 + 8 + chunkSize; // "AVI " + chunk header + chunk data
    for (int i = 0; i < 4; i++) {
        data.push_back(static_cast<uint8_t>((riffSize >> (i * 8)) & 0xFF));
    }
    
    // AVI form type
    data.push_back('A'); data.push_back('V'); data.push_back('I'); data.push_back(' ');
    
    // Chunk ID (4 bytes)
    for (size_t i = 0; i < 4 && i < chunkId.size(); i++) {
        data.push_back(static_cast<uint8_t>(chunkId[i]));
    }
    for (size_t i = chunkId.size(); i < 4; i++) {
        data.push_back(' ');
    }
    
    // Chunk size (4 bytes, little-endian)
    for (int i = 0; i < 4; i++) {
        data.push_back(static_cast<uint8_t>((chunkSize >> (i * 8)) & 0xFF));
    }
    
    // Chunk data
    if (!chunkData.empty()) {
        data.insert(data.end(), chunkData.begin(), chunkData.end());
    } else {
        // Fill with zeros
        for (uint32_t i = 0; i < chunkSize; i++) {
            data.push_back(0);
        }
    }
    
    return data;
}

// Create avih chunk data (56 bytes minimum)
std::vector<uint8_t> createAvihData() {
    std::vector<uint8_t> data(56, 0);
    // dwMicroSecPerFrame
    uint32_t usPerFrame = 33333; // ~30fps
    std::memcpy(data.data(), &usPerFrame, 4);
    return data;
}

// Create strh chunk data (56 bytes minimum)  
std::vector<uint8_t> createStrhData() {
    std::vector<uint8_t> data(56, 0);
    // fccType = "vids"
    data[0] = 'v'; data[1] = 'i'; data[2] = 'd'; data[3] = 's';
    return data;
}

} // anonymous namespace

class RiffVideoTest_80 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    
    std::unique_ptr<RiffVideo> createRiffVideoFromData(const std::vector<uint8_t>& data) {
        auto io = std::make_unique<MemIo>(data.data(), data.size());
        return std::make_unique<RiffVideo>(std::move(io));
    }
};

// Test: RiffVideo can be constructed with a valid MemIo
TEST_F(RiffVideoTest_80, Construction_80) {
    std::vector<uint8_t> data(100, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    ASSERT_NO_THROW(RiffVideo video(std::move(io)));
}

// Test: mimeType returns the expected RIFF video MIME type
TEST_F(RiffVideoTest_80, MimeType_80) {
    std::vector<uint8_t> data(100, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    RiffVideo video(std::move(io));
    std::string mime = video.mimeType();
    EXPECT_FALSE(mime.empty());
    // RIFF video mime type should be video/x-msvideo or similar
    EXPECT_TRUE(mime.find("video") != std::string::npos || mime.find("riff") != std::string::npos);
}

// Test: writeMetadata throws since RIFF writing is typically unsupported
TEST_F(RiffVideoTest_80, WriteMetadataThrows_80) {
    std::vector<uint8_t> data(100, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    RiffVideo video(std::move(io));
    EXPECT_THROW(video.writeMetadata(), Error);
}

// Test: readMetadata on empty/invalid data throws or handles gracefully
TEST_F(RiffVideoTest_80, ReadMetadataOnInvalidData_80) {
    std::vector<uint8_t> data(4, 0); // too small
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    RiffVideo video(std::move(io));
    EXPECT_THROW(video.readMetadata(), Error);
}

// Test: readMetadata on a minimal valid RIFF/AVI file with avih chunk
TEST_F(RiffVideoTest_80, ReadMetadataWithAvihChunk_80) {
    auto avihData = createAvihData();
    
    std::vector<uint8_t> data;
    // RIFF header
    const char* riffId = "RIFF";
    data.insert(data.end(), riffId, riffId + 4);
    
    // We'll build the content first to know the size
    std::vector<uint8_t> content;
    // "AVI " form type
    const char* aviForm = "AVI ";
    content.insert(content.end(), aviForm, aviForm + 4);
    
    // LIST hdrl
    const char* listId = "LIST";
    content.insert(content.end(), listId, listId + 4);
    
    uint32_t hdrlContentSize = 4 + 8 + static_cast<uint32_t>(avihData.size());
    for (int i = 0; i < 4; i++)
        content.push_back(static_cast<uint8_t>((hdrlContentSize >> (i * 8)) & 0xFF));
    
    const char* hdrlType = "hdrl";
    content.insert(content.end(), hdrlType, hdrlType + 4);
    
    // avih chunk
    const char* avihId = "avih";
    content.insert(content.end(), avihId, avihId + 4);
    uint32_t avihSize = static_cast<uint32_t>(avihData.size());
    for (int i = 0; i < 4; i++)
        content.push_back(static_cast<uint8_t>((avihSize >> (i * 8)) & 0xFF));
    content.insert(content.end(), avihData.begin(), avihData.end());
    
    // RIFF size
    uint32_t riffSize = static_cast<uint32_t>(content.size());
    for (int i = 0; i < 4; i++)
        data.push_back(static_cast<uint8_t>((riffSize >> (i * 8)) & 0xFF));
    
    data.insert(data.end(), content.begin(), content.end());
    
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    RiffVideo video(std::move(io));
    
    // readMetadata should not throw on valid structure
    EXPECT_NO_THROW(video.readMetadata());
}

// Test: readMetadata on a RIFF file with JUNK chunk
TEST_F(RiffVideoTest_80, ReadMetadataWithJunkChunk_80) {
    std::vector<uint8_t> data;
    const char* riffId = "RIFF";
    data.insert(data.end(), riffId, riffId + 4);
    
    std::vector<uint8_t> content;
    const char* aviForm = "AVI ";
    content.insert(content.end(), aviForm, aviForm + 4);
    
    // JUNK chunk
    const char* junkId = "JUNK";
    content.insert(content.end(), junkId, junkId + 4);
    uint32_t junkSize = 16;
    for (int i = 0; i < 4; i++)
        content.push_back(static_cast<uint8_t>((junkSize >> (i * 8)) & 0xFF));
    for (uint32_t i = 0; i < junkSize; i++)
        content.push_back(0);
    
    uint32_t riffSize = static_cast<uint32_t>(content.size());
    for (int i = 0; i < 4; i++)
        data.push_back(static_cast<uint8_t>((riffSize >> (i * 8)) & 0xFF));
    
    data.insert(data.end(), content.begin(), content.end());
    
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    RiffVideo video(std::move(io));
    
    EXPECT_NO_THROW(video.readMetadata());
}

// Test: readMetadata on completely zeroed data
TEST_F(RiffVideoTest_80, ReadMetadataOnZeroedData_80) {
    std::vector<uint8_t> data(1024, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    RiffVideo video(std::move(io));
    EXPECT_THROW(video.readMetadata(), Error);
}

// Test: readMetadata with truncated RIFF header
TEST_F(RiffVideoTest_80, ReadMetadataWithTruncatedHeader_80) {
    // Only "RIFF" + 4 bytes size, no content
    std::vector<uint8_t> data;
    const char* riffId = "RIFF";
    data.insert(data.end(), riffId, riffId + 4);
    uint32_t size = 0;
    for (int i = 0; i < 4; i++)
        data.push_back(static_cast<uint8_t>((size >> (i * 8)) & 0xFF));
    
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    RiffVideo video(std::move(io));
    // With size=0, there's nothing to decode
    EXPECT_THROW(video.readMetadata(), Error);
}

// Test: readMetadata with a RIFF file that has an unknown chunk (should be skipped)
TEST_F(RiffVideoTest_80, ReadMetadataWithUnknownChunk_80) {
    std::vector<uint8_t> data;
    const char* riffId = "RIFF";
    data.insert(data.end(), riffId, riffId + 4);
    
    std::vector<uint8_t> content;
    const char* aviForm = "AVI ";
    content.insert(content.end(), aviForm, aviForm + 4);
    
    // Unknown chunk "XXXX"
    const char* unkId = "XXXX";
    content.insert(content.end(), unkId, unkId + 4);
    uint32_t unkSize = 8;
    for (int i = 0; i < 4; i++)
        content.push_back(static_cast<uint8_t>((unkSize >> (i * 8)) & 0xFF));
    for (uint32_t i = 0; i < unkSize; i++)
        content.push_back(0xAB);
    
    uint32_t riffSize = static_cast<uint32_t>(content.size());
    for (int i = 0; i < 4; i++)
        data.push_back(static_cast<uint8_t>((riffSize >> (i * 8)) & 0xFF));
    
    data.insert(data.end(), content.begin(), content.end());
    
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    RiffVideo video(std::move(io));
    
    // Unknown chunk should be skipped via seek
    EXPECT_NO_THROW(video.readMetadata());
}

// Test: readMetadata with valid RIFF/WAVE structure containing fmt chunk
TEST_F(RiffVideoTest_80, ReadMetadataWithWaveFmtChunk_80) {
    std::vector<uint8_t> data;
    const char* riffId = "RIFF";
    data.insert(data.end(), riffId, riffId + 4);
    
    std::vector<uint8_t> content;
    const char* waveForm = "WAVE";
    content.insert(content.end(), waveForm, waveForm + 4);
    
    // fmt chunk (16 bytes for PCM)
    const char* fmtId = "fmt ";
    content.insert(content.end(), fmtId, fmtId + 4);
    uint32_t fmtSize = 16;
    for (int i = 0; i < 4; i++)
        content.push_back(static_cast<uint8_t>((fmtSize >> (i * 8)) & 0xFF));
    
    // PCM format data
    // wFormatTag = 1 (PCM)
    content.push_back(0x01); content.push_back(0x00);
    // nChannels = 2
    content.push_back(0x02); content.push_back(0x00);
    // nSamplesPerSec = 44100
    content.push_back(0x44); content.push_back(0xAC); content.push_back(0x00); content.push_back(0x00);
    // nAvgBytesPerSec = 176400
    content.push_back(0x10); content.push_back(0xB1); content.push_back(0x02); content.push_back(0x00);
    // nBlockAlign = 4
    content.push_back(0x04); content.push_back(0x00);
    // wBitsPerSample = 16
    content.push_back(0x10); content.push_back(0x00);
    
    uint32_t riffSize = static_cast<uint32_t>(content.size());
    for (int i = 0; i < 4; i++)
        data.push_back(static_cast<uint8_t>((riffSize >> (i * 8)) & 0xFF));
    
    data.insert(data.end(), content.begin(), content.end());
    
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    RiffVideo video(std::move(io));
    
    // WAVE files may or may not be fully supported, but should not crash
    // The readMetadata may throw if it doesn't recognize WAVE as valid AVI
    // We just verify it doesn't crash unexpectedly
    try {
        video.readMetadata();
    } catch (const Error&) {
        // Acceptable - WAVE might not be fully supported as RIFF video
    }
}

// Test: RiffVideo with multiple chunks in sequence
TEST_F(RiffVideoTest_80, ReadMetadataMultipleChunks_80) {
    std::vector<uint8_t> data;
    const char* riffId = "RIFF";
    data.insert(data.end(), riffId, riffId + 4);
    
    std::vector<uint8_t> content;
    const char* aviForm = "AVI ";
    content.insert(content.end(), aviForm, aviForm + 4);
    
    // LIST hdrl with avih
    const char* listId = "LIST";
    content.insert(content.end(), listId, listId + 4);
    
    auto avihData = createAvihData();
    uint32_t hdrlSize = 4 + 8 + static_cast<uint32_t>(avihData.size());
    for (int i = 0; i < 4; i++)
        content.push_back(static_cast<uint8_t>((hdrlSize >> (i * 8)) & 0xFF));
    
    const char* hdrlType = "hdrl";
    content.insert(content.end(), hdrlType, hdrlType + 4);
    
    const char* avihId = "avih";
    content.insert(content.end(), avihId, avihId + 4);
    uint32_t avihSize = static_cast<uint32_t>(avihData.size());
    for (int i = 0; i < 4; i++)
        content.push_back(static_cast<uint8_t>((avihSize >> (i * 8)) & 0xFF));
    content.insert(content.end(), avihData.begin(), avihData.end());
    
    // JUNK chunk after the LIST
    const char* junkId = "JUNK";
    content.insert(content.end(), junkId, junkId + 4);
    uint32_t junkSize = 8;
    for (int i = 0; i < 4; i++)
        content.push_back(static_cast<uint8_t>((junkSize >> (i * 8)) & 0xFF));
    for (uint32_t i = 0; i < junkSize; i++)
        content.push_back(0);
    
    uint32_t riffSize = static_cast<uint32_t>(content.size());
    for (int i = 0; i < 4; i++)
        data.push_back(static_cast<uint8_t>((riffSize >> (i * 8)) & 0xFF));
    
    data.insert(data.end(), content.begin(), content.end());
    
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    RiffVideo video(std::move(io));
    
    EXPECT_NO_THROW(video.readMetadata());
}

// Test: RiffVideo good() status after construction
TEST_F(RiffVideoTest_80, GoodStatusAfterConstruction_80) {
    std::vector<uint8_t> data(100, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    RiffVideo video(std::move(io));
    EXPECT_TRUE(video.good());
}

// Test: Empty MemIo causes readMetadata to fail
TEST_F(RiffVideoTest_80, ReadMetadataEmptyIo_80) {
    auto io = std::make_unique<MemIo>();
    RiffVideo video(std::move(io));
    EXPECT_THROW(video.readMetadata(), Error);
}

// Test: RiffVideo with data chunk
TEST_F(RiffVideoTest_80, ReadMetadataWithDataChunk_80) {
    std::vector<uint8_t> data;
    const char* riffId = "RIFF";
    data.insert(data.end(), riffId, riffId + 4);
    
    std::vector<uint8_t> content;
    const char* aviForm = "AVI ";
    content.insert(content.end(), aviForm, aviForm + 4);
    
    // data chunk
    const char* dataId = "data";
    content.insert(content.end(), dataId, dataId + 4);
    uint32_t dataSize = 32;
    for (int i = 0; i < 4; i++)
        content.push_back(static_cast<uint8_t>((dataSize >> (i * 8)) & 0xFF));
    for (uint32_t i = 0; i < dataSize; i++)
        content.push_back(0);
    
    uint32_t riffSize = static_cast<uint32_t>(content.size());
    for (int i = 0; i < 4; i++)
        data.push_back(static_cast<uint8_t>((riffSize >> (i * 8)) & 0xFF));
    
    data.insert(data.end(), content.begin(), content.end());
    
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    RiffVideo video(std::move(io));
    
    EXPECT_NO_THROW(video.readMetadata());
}

// Test: RiffVideo with idx1 chunk
TEST_F(RiffVideoTest_80, ReadMetadataWithIdx1Chunk_80) {
    std::vector<uint8_t> data;
    const char* riffId = "RIFF";
    data.insert(data.end(), riffId, riffId + 4);
    
    std::vector<uint8_t> content;
    const char* aviForm = "AVI ";
    content.insert(content.end(), aviForm, aviForm + 4);
    
    // idx1 chunk (index entries are 16 bytes each)
    const char* idx1Id = "idx1";
    content.insert(content.end(), idx1Id, idx1Id + 4);
    uint32_t idx1Size = 32; // 2 entries
    for (int i = 0; i < 4; i++)
        content.push_back(static_cast<uint8_t>((idx1Size >> (i * 8)) & 0xFF));
    for (uint32_t i = 0; i < idx1Size; i++)
        content.push_back(0);
    
    uint32_t riffSize = static_cast<uint32_t>(content.size());
    for (int i = 0; i < 4; i++)
        data.push_back(static_cast<uint8_t>((riffSize >> (i * 8)) & 0xFF));
    
    data.insert(data.end(), content.begin(), content.end());
    
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    RiffVideo video(std::move(io));
    
    EXPECT_NO_THROW(video.readMetadata());
}

// Test: exifData access after readMetadata on valid file
TEST_F(RiffVideoTest_80, ExifDataAccessible_80) {
    auto avihData = createAvihData();
    
    std::vector<uint8_t> data;
    const char* riffId = "RIFF";
    data.insert(data.end(), riffId, riffId + 4);
    
    std::vector<uint8_t> content;
    const char* aviForm = "AVI ";
    content.insert(content.end(), aviForm, aviForm + 4);
    
    const char* listId = "LIST";
    content.insert(content.end(), listId, listId + 4);
    
    uint32_t hdrlSize = 4 + 8 + static_cast<uint32_t>(avihData.size());
    for (int i = 0; i < 4; i++)
        content.push_back(static_cast<uint8_t>((hdrlSize >> (i * 8)) & 0xFF));
    
    const char* hdrlType = "hdrl";
    content.insert(content.end(), hdrlType, hdrlType + 4);
    
    const char* avihId = "avih";
    content.insert(content.end(), avihId, avihId + 4);
    uint32_t avihSize = static_cast<uint32_t>(avihData.size());
    for (int i = 0; i < 4; i++)
        content.push_back(static_cast<uint8_t>((avihSize >> (i * 8)) & 0xFF));
    content.insert(content.end(), avihData.begin(), avihData.end());
    
    uint32_t riffSize = static_cast<uint32_t>(content.size());
    for (int i = 0; i < 4; i++)
        data.push_back(static_cast<uint8_t>((riffSize >> (i * 8)) & 0xFF));
    
    data.insert(data.end(), content.begin(), content.end());
    
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    RiffVideo video(std::move(io));
    
    try {
        video.readMetadata();
    } catch (...) {
        // May fail depending on data validity
    }
    
    // exifData should be accessible regardless
    EXPECT_NO_THROW(video.exifData());
    EXPECT_NO_THROW(video.xmpData());
}

// Test: HeaderReader with valid data
TEST_F(RiffVideoTest_80, HeaderReaderConstruction_80) {
    // Create data with a valid chunk header: 4 byte ID + 4 byte size
    std::vector<uint8_t> data;
    const char* id = "test";
    data.insert(data.end(), id, id + 4);
    uint32_t size = 100;
    for (int i = 0; i < 4; i++)
        data.push_back(static_cast<uint8_t>((size >> (i * 8)) & 0xFF));
    // Add some payload
    for (uint32_t i = 0; i < size; i++)
        data.push_back(0);
    
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    io->open();
    
    RiffVideo::HeaderReader header(io);
    
    EXPECT_EQ(header.getId(), "test");
    EXPECT_EQ(header.getSize(), 100u);
}

// Test: HeaderReader with zero-size chunk
TEST_F(RiffVideoTest_80, HeaderReaderZeroSize_80) {
    std::vector<uint8_t> data;
    const char* id = "JUNK";
    data.insert(data.end(), id, id + 4);
    uint32_t size = 0;
    for (int i = 0; i < 4; i++)
        data.push_back(static_cast<uint8_t>((size >> (i * 8)) & 0xFF));
    
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    io->open();
    
    RiffVideo::HeaderReader header(io);
    
    EXPECT_EQ(header.getId(), "JUNK");
    EXPECT_EQ(header.getSize(), 0u);
}

// Test: Seek failure on unknown chunk with insufficient data should throw
TEST_F(RiffVideoTest_80, ReadMetadataUnknownChunkSeekFailure_80) {
    std::vector<uint8_t> data;
    const char* riffId = "RIFF";
    data.insert(data.end(), riffId, riffId + 4);
    
    std::vector<uint8_t> content;
    const char* aviForm = "AVI ";
    content.insert(content.end(), aviForm, aviForm + 4);
    
    // Unknown chunk with size larger than available data
    const char* unkId = "ZZZZ";
    content.insert(content.end(), unkId, unkId + 4);
    uint32_t unkSize = 99999; // Way larger than file
    for (int i = 0; i < 4; i++)
        content.push_back(static_cast<uint8_t>((unkSize >> (i * 8)) & 0xFF));
    // Only add a few bytes
    for (int i = 0; i < 8; i++)
        content.push_back(0);
    
    uint32_t riffSize = static_cast<uint32_t>(content.size());
    for (int i = 0; i < 4; i++)
        data.push_back(static_cast<uint8_t>((riffSize >> (i * 8)) & 0xFF));
    
    data.insert(data.end(), content.begin(), content.end());
    
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    RiffVideo video(std::move(io));
    
    // The seek past the unknown chunk should fail due to insufficient data
    EXPECT_THROW(video.readMetadata(), Error);
}
