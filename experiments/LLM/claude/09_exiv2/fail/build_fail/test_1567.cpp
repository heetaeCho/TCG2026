#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/asfvideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>
#include <cstring>
#include <memory>
#include <vector>

// Helper constants matching the ones used in the implementation
static const size_t WORD = 2;
static const size_t DWORD = 4;
static const size_t GUID = 16;

// The Audio_Media GUID: {4167671360, 23373, 4559, {168, 253, 0, 128, 95, 92, 68, 43}}
// In little-endian byte representation
static const uint8_t AudioMediaGUID[] = {
    0x40, 0x9E, 0x69, 0xF8,  // 4167671360 = 0xF8699E40
    0x4D, 0x5B,              // 23373 = 0x5B4D
    0xCF, 0x11,              // 4559 = 0x11CF
    0xA8, 0xFD, 0x00, 0x80, 0x5F, 0x5C, 0x44, 0x2B
};

// The Video_Media GUID: {3155816384, 23373, 4559, {168, 253, 0, 128, 95, 92, 68, 43}}
static const uint8_t VideoMediaGUID[] = {
    0xC0, 0xEF, 0x19, 0xBC,  // 3155816384 = 0xBC19EFC0
    0x4D, 0x5B,              // 23373 = 0x5B4D
    0xCF, 0x11,              // 4559 = 0x11CF
    0xA8, 0xFD, 0x00, 0x80, 0x5F, 0x5C, 0x44, 0x2B
};

// An unknown GUID (all zeros)
static const uint8_t UnknownGUID[16] = {0};

// Helper to build a binary stream for streamProperties()
// Layout after the initial GUID read:
//   - Stream Type GUID (16 bytes) - already read
//   - Error Correction Type GUID (16 bytes) - skipped via seek
//   - Time Offset (8 bytes, QWORD, little-endian)
//   - Specific Data Length (4 bytes, DWORD, little-endian)
//   - Correction Data Length (4 bytes, DWORD, little-endian)
//   - Flags (2 bytes, WORD) - skipped
//   - Reserved (4 bytes, DWORD) - skipped
//   - Specific Data (specific_data_length bytes) - skipped
//   - Correction Data (correction_data_length bytes) - skipped
static std::vector<uint8_t> buildStreamPropertiesData(
    const uint8_t* streamTypeGUID,
    uint64_t timeOffset,
    uint32_t specificDataLen,
    uint32_t correctionDataLen)
{
    std::vector<uint8_t> data;

    // Stream Type GUID (16 bytes)
    data.insert(data.end(), streamTypeGUID, streamTypeGUID + 16);

    // Error Correction Type GUID (16 bytes) - will be skipped
    for (size_t i = 0; i < 16; ++i)
        data.push_back(0);

    // Time Offset (8 bytes, little-endian QWORD)
    for (int i = 0; i < 8; ++i)
        data.push_back(static_cast<uint8_t>((timeOffset >> (i * 8)) & 0xFF));

    // Specific Data Length (4 bytes, little-endian DWORD)
    for (int i = 0; i < 4; ++i)
        data.push_back(static_cast<uint8_t>((specificDataLen >> (i * 8)) & 0xFF));

    // Correction Data Length (4 bytes, little-endian DWORD)
    for (int i = 0; i < 4; ++i)
        data.push_back(static_cast<uint8_t>((correctionDataLen >> (i * 8)) & 0xFF));

    // Flags (2 bytes, WORD)
    data.push_back(0);
    data.push_back(0);

    // Reserved (4 bytes, DWORD)
    for (int i = 0; i < 4; ++i)
        data.push_back(0);

    // Specific Data
    for (uint32_t i = 0; i < specificDataLen; ++i)
        data.push_back(0xAA);

    // Correction Data
    for (uint32_t i = 0; i < correctionDataLen; ++i)
        data.push_back(0xBB);

    return data;
}

class AsfVideoStreamPropertiesTest_1567 : public ::testing::Test {
protected:
    std::unique_ptr<Exiv2::AsfVideo> createAsfVideoFromData(const std::vector<uint8_t>& data) {
        auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
        return std::make_unique<Exiv2::AsfVideo>(std::move(io));
    }
};

// Test: Video stream sets Xmp.video.TimeOffset
TEST_F(AsfVideoStreamPropertiesTest_1567, VideoStreamSetsVideoTimeOffset_1567) {
    uint64_t expectedTimeOffset = 12345;
    auto data = buildStreamPropertiesData(VideoMediaGUID, expectedTimeOffset, 0, 0);
    auto video = createAsfVideoFromData(data);

    video->streamProperties();

    auto& xmpData = video->xmpData();
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.video.TimeOffset"));
    ASSERT_NE(it, xmpData.end());
    EXPECT_EQ(it->toInt64(), static_cast<int64_t>(expectedTimeOffset));
}

// Test: Audio stream sets Xmp.audio.TimeOffset
TEST_F(AsfVideoStreamPropertiesTest_1567, AudioStreamSetsAudioTimeOffset_1567) {
    uint64_t expectedTimeOffset = 67890;
    auto data = buildStreamPropertiesData(AudioMediaGUID, expectedTimeOffset, 0, 0);
    auto video = createAsfVideoFromData(data);

    video->streamProperties();

    auto& xmpData = video->xmpData();
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.audio.TimeOffset"));
    ASSERT_NE(it, xmpData.end());
    EXPECT_EQ(it->toInt64(), static_cast<int64_t>(expectedTimeOffset));
}

// Test: Video stream with zero time offset
TEST_F(AsfVideoStreamPropertiesTest_1567, VideoStreamZeroTimeOffset_1567) {
    uint64_t expectedTimeOffset = 0;
    auto data = buildStreamPropertiesData(VideoMediaGUID, expectedTimeOffset, 0, 0);
    auto video = createAsfVideoFromData(data);

    video->streamProperties();

    auto& xmpData = video->xmpData();
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.video.TimeOffset"));
    ASSERT_NE(it, xmpData.end());
    EXPECT_EQ(it->toInt64(), 0);
}

// Test: Audio stream with large time offset
TEST_F(AsfVideoStreamPropertiesTest_1567, AudioStreamLargeTimeOffset_1567) {
    uint64_t expectedTimeOffset = 0xFFFFFFFF;
    auto data = buildStreamPropertiesData(AudioMediaGUID, expectedTimeOffset, 0, 0);
    auto video = createAsfVideoFromData(data);

    video->streamProperties();

    auto& xmpData = video->xmpData();
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.audio.TimeOffset"));
    ASSERT_NE(it, xmpData.end());
    EXPECT_EQ(it->toInt64(), static_cast<int64_t>(expectedTimeOffset));
}

// Test: Video stream with non-zero specific and correction data lengths
TEST_F(AsfVideoStreamPropertiesTest_1567, VideoStreamWithSpecificAndCorrectionData_1567) {
    uint64_t expectedTimeOffset = 42;
    uint32_t specificDataLen = 10;
    uint32_t correctionDataLen = 5;
    auto data = buildStreamPropertiesData(VideoMediaGUID, expectedTimeOffset, specificDataLen, correctionDataLen);
    auto video = createAsfVideoFromData(data);

    video->streamProperties();

    auto& xmpData = video->xmpData();
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.video.TimeOffset"));
    ASSERT_NE(it, xmpData.end());
    EXPECT_EQ(it->toInt64(), 42);
}

// Test: Unknown GUID does not set any XMP data
TEST_F(AsfVideoStreamPropertiesTest_1567, UnknownGUIDNoXmpSet_1567) {
    auto data = buildStreamPropertiesData(UnknownGUID, 100, 0, 0);
    auto video = createAsfVideoFromData(data);

    video->streamProperties();

    auto& xmpData = video->xmpData();
    auto itVideo = xmpData.findKey(Exiv2::XmpKey("Xmp.video.TimeOffset"));
    auto itAudio = xmpData.findKey(Exiv2::XmpKey("Xmp.audio.TimeOffset"));
    EXPECT_EQ(itVideo, xmpData.end());
    EXPECT_EQ(itAudio, xmpData.end());
}

// Test: Video stream does NOT set audio TimeOffset
TEST_F(AsfVideoStreamPropertiesTest_1567, VideoStreamDoesNotSetAudioTimeOffset_1567) {
    auto data = buildStreamPropertiesData(VideoMediaGUID, 999, 0, 0);
    auto video = createAsfVideoFromData(data);

    video->streamProperties();

    auto& xmpData = video->xmpData();
    auto itAudio = xmpData.findKey(Exiv2::XmpKey("Xmp.audio.TimeOffset"));
    EXPECT_EQ(itAudio, xmpData.end());
}

// Test: Audio stream does NOT set video TimeOffset
TEST_F(AsfVideoStreamPropertiesTest_1567, AudioStreamDoesNotSetVideoTimeOffset_1567) {
    auto data = buildStreamPropertiesData(AudioMediaGUID, 999, 0, 0);
    auto video = createAsfVideoFromData(data);

    video->streamProperties();

    auto& xmpData = video->xmpData();
    auto itVideo = xmpData.findKey(Exiv2::XmpKey("Xmp.video.TimeOffset"));
    EXPECT_EQ(itVideo, xmpData.end());
}

// Test: Insufficient data for initial GUID read throws exception
TEST_F(AsfVideoStreamPropertiesTest_1567, InsufficientDataThrowsException_1567) {
    // Only provide 8 bytes when 16 are needed for the stream type GUID
    std::vector<uint8_t> data(8, 0);
    auto video = createAsfVideoFromData(data);

    EXPECT_THROW(video->streamProperties(), Exiv2::Error);
}

// Test: Empty data throws exception
TEST_F(AsfVideoStreamPropertiesTest_1567, EmptyDataThrowsException_1567) {
    std::vector<uint8_t> data;
    auto io = std::make_unique<Exiv2::MemIo>();
    auto video = std::make_unique<Exiv2::AsfVideo>(std::move(io));

    EXPECT_THROW(video->streamProperties(), Exiv2::Error);
}

// Test: Audio stream with specific data length > 0
TEST_F(AsfVideoStreamPropertiesTest_1567, AudioStreamWithSpecificData_1567) {
    uint64_t expectedTimeOffset = 77777;
    uint32_t specificDataLen = 20;
    uint32_t correctionDataLen = 10;
    auto data = buildStreamPropertiesData(AudioMediaGUID, expectedTimeOffset, specificDataLen, correctionDataLen);
    auto video = createAsfVideoFromData(data);

    video->streamProperties();

    auto& xmpData = video->xmpData();
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.audio.TimeOffset"));
    ASSERT_NE(it, xmpData.end());
    EXPECT_EQ(it->toInt64(), static_cast<int64_t>(expectedTimeOffset));
}

// Test: Mime type of AsfVideo is correct
TEST_F(AsfVideoStreamPropertiesTest_1567, MimeTypeIsCorrect_1567) {
    std::vector<uint8_t> data(256, 0);
    auto video = createAsfVideoFromData(data);
    EXPECT_EQ(video->mimeType(), "video/asf");
}
