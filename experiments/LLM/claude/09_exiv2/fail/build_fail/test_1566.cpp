#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstring>
#include <exiv2/asfvideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/xmp_exiv2.hpp>

using namespace Exiv2;

// Helper to create a MemIo with specific binary data for DegradableJPEGMedia
// The function reads:
//   1. DWORD (4 bytes LE) for width
//   2. DWORD (4 bytes LE) for height
//   3. 3 * WORD (6 bytes) reserved - skipped
//   4. WORD (2 bytes LE) for interchange_data_length
//   5. interchange_data_length bytes - skipped

static std::unique_ptr<byte[]> buildDegradableJPEGMediaData(
    uint32_t width, uint32_t height, 
    uint16_t interchange_data_length,
    const byte* interchange_data,
    size_t& totalSize)
{
    // 4 (width) + 4 (height) + 6 (3 reserved WORDs) + 2 (interchange_data_length) + interchange_data_length
    totalSize = 4 + 4 + 6 + 2 + interchange_data_length;
    auto data = std::make_unique<byte[]>(totalSize);
    size_t offset = 0;

    // Write width as little-endian DWORD
    data[offset++] = static_cast<byte>(width & 0xFF);
    data[offset++] = static_cast<byte>((width >> 8) & 0xFF);
    data[offset++] = static_cast<byte>((width >> 16) & 0xFF);
    data[offset++] = static_cast<byte>((width >> 24) & 0xFF);

    // Write height as little-endian DWORD
    data[offset++] = static_cast<byte>(height & 0xFF);
    data[offset++] = static_cast<byte>((height >> 8) & 0xFF);
    data[offset++] = static_cast<byte>((height >> 16) & 0xFF);
    data[offset++] = static_cast<byte>((height >> 24) & 0xFF);

    // 3 Reserved WORDs (6 bytes)
    for (int i = 0; i < 6; i++) {
        data[offset++] = 0x00;
    }

    // Write interchange_data_length as little-endian WORD
    data[offset++] = static_cast<byte>(interchange_data_length & 0xFF);
    data[offset++] = static_cast<byte>((interchange_data_length >> 8) & 0xFF);

    // Write interchange data
    if (interchange_data && interchange_data_length > 0) {
        std::memcpy(&data[offset], interchange_data, interchange_data_length);
        offset += interchange_data_length;
    }

    return data;
}

class AsfVideoTest_1566 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Normal operation with typical width and height values
TEST_F(AsfVideoTest_1566, DegradableJPEGMedia_NormalWidthHeight_1566)
{
    uint32_t width = 1920;
    uint32_t height = 1080;
    uint16_t interchange_len = 0;
    size_t totalSize;
    auto data = buildDegradableJPEGMediaData(width, height, interchange_len, nullptr, totalSize);

    auto io = std::make_unique<MemIo>(data.get(), totalSize);
    io->open();
    AsfVideo video(std::move(io));

    video.DegradableJPEGMedia();

    XmpData& xmpData = video.xmpData();
    auto widthIt = xmpData.findKey(XmpKey("Xmp.video.Width"));
    auto heightIt = xmpData.findKey(XmpKey("Xmp.video.Height"));

    ASSERT_NE(widthIt, xmpData.end());
    ASSERT_NE(heightIt, xmpData.end());
    EXPECT_EQ(widthIt->toInt64(), static_cast<int64_t>(width));
    EXPECT_EQ(heightIt->toInt64(), static_cast<int64_t>(height));
    EXPECT_EQ(video.pixelWidth(), width);
    EXPECT_EQ(video.pixelHeight(), height);
}

// Test: Zero width and height
TEST_F(AsfVideoTest_1566, DegradableJPEGMedia_ZeroDimensions_1566)
{
    uint32_t width = 0;
    uint32_t height = 0;
    uint16_t interchange_len = 0;
    size_t totalSize;
    auto data = buildDegradableJPEGMediaData(width, height, interchange_len, nullptr, totalSize);

    auto io = std::make_unique<MemIo>(data.get(), totalSize);
    io->open();
    AsfVideo video(std::move(io));

    video.DegradableJPEGMedia();

    XmpData& xmpData = video.xmpData();
    auto widthIt = xmpData.findKey(XmpKey("Xmp.video.Width"));
    auto heightIt = xmpData.findKey(XmpKey("Xmp.video.Height"));

    ASSERT_NE(widthIt, xmpData.end());
    ASSERT_NE(heightIt, xmpData.end());
    EXPECT_EQ(widthIt->toInt64(), 0);
    EXPECT_EQ(heightIt->toInt64(), 0);
    EXPECT_EQ(video.pixelWidth(), 0u);
    EXPECT_EQ(video.pixelHeight(), 0u);
}

// Test: With non-zero interchange data that gets skipped
TEST_F(AsfVideoTest_1566, DegradableJPEGMedia_WithInterchangeData_1566)
{
    uint32_t width = 640;
    uint32_t height = 480;
    byte interchangeData[] = {0xDE, 0xAD, 0xBE, 0xEF, 0x01, 0x02, 0x03, 0x04};
    uint16_t interchange_len = sizeof(interchangeData);
    size_t totalSize;
    auto data = buildDegradableJPEGMediaData(width, height, interchange_len, interchangeData, totalSize);

    auto io = std::make_unique<MemIo>(data.get(), totalSize);
    io->open();
    AsfVideo video(std::move(io));

    video.DegradableJPEGMedia();

    XmpData& xmpData = video.xmpData();
    auto widthIt = xmpData.findKey(XmpKey("Xmp.video.Width"));
    auto heightIt = xmpData.findKey(XmpKey("Xmp.video.Height"));

    ASSERT_NE(widthIt, xmpData.end());
    ASSERT_NE(heightIt, xmpData.end());
    EXPECT_EQ(widthIt->toInt64(), static_cast<int64_t>(width));
    EXPECT_EQ(heightIt->toInt64(), static_cast<int64_t>(height));

    // Verify the io position is after all the data (width+height+reserved+interchange_len_field+interchange_data)
    EXPECT_EQ(video.io().tell(), totalSize);
}

// Test: Large width and height values
TEST_F(AsfVideoTest_1566, DegradableJPEGMedia_LargeDimensions_1566)
{
    uint32_t width = 7680;   // 8K resolution
    uint32_t height = 4320;
    uint16_t interchange_len = 0;
    size_t totalSize;
    auto data = buildDegradableJPEGMediaData(width, height, interchange_len, nullptr, totalSize);

    auto io = std::make_unique<MemIo>(data.get(), totalSize);
    io->open();
    AsfVideo video(std::move(io));

    video.DegradableJPEGMedia();

    XmpData& xmpData = video.xmpData();
    auto widthIt = xmpData.findKey(XmpKey("Xmp.video.Width"));
    auto heightIt = xmpData.findKey(XmpKey("Xmp.video.Height"));

    ASSERT_NE(widthIt, xmpData.end());
    ASSERT_NE(heightIt, xmpData.end());
    EXPECT_EQ(widthIt->toInt64(), static_cast<int64_t>(width));
    EXPECT_EQ(heightIt->toInt64(), static_cast<int64_t>(height));
    EXPECT_EQ(video.pixelWidth(), width);
    EXPECT_EQ(video.pixelHeight(), height);
}

// Test: Maximum uint16_t interchange data length
TEST_F(AsfVideoTest_1566, DegradableJPEGMedia_MaxInterchangeDataLength_1566)
{
    uint32_t width = 320;
    uint32_t height = 240;
    uint16_t interchange_len = 256;  // reasonable large value
    std::vector<byte> interchangeData(interchange_len, 0xAB);
    size_t totalSize;
    auto data = buildDegradableJPEGMediaData(width, height, interchange_len, interchangeData.data(), totalSize);

    auto io = std::make_unique<MemIo>(data.get(), totalSize);
    io->open();
    AsfVideo video(std::move(io));

    video.DegradableJPEGMedia();

    EXPECT_EQ(video.pixelWidth(), width);
    EXPECT_EQ(video.pixelHeight(), height);
    EXPECT_EQ(video.io().tell(), totalSize);
}

// Test: IO position advances correctly past all fields
TEST_F(AsfVideoTest_1566, DegradableJPEGMedia_IOPositionCorrect_1566)
{
    uint32_t width = 100;
    uint32_t height = 200;
    uint16_t interchange_len = 10;
    std::vector<byte> interchangeData(interchange_len, 0x55);
    size_t totalSize;
    auto data = buildDegradableJPEGMediaData(width, height, interchange_len, interchangeData.data(), totalSize);

    auto io = std::make_unique<MemIo>(data.get(), totalSize);
    io->open();
    AsfVideo video(std::move(io));

    size_t expectedEndPos = 4 + 4 + 6 + 2 + interchange_len;
    video.DegradableJPEGMedia();

    EXPECT_EQ(video.io().tell(), expectedEndPos);
}

// Test: Width set to 1 and height set to 1 (minimum non-zero)
TEST_F(AsfVideoTest_1566, DegradableJPEGMedia_MinimalDimensions_1566)
{
    uint32_t width = 1;
    uint32_t height = 1;
    uint16_t interchange_len = 0;
    size_t totalSize;
    auto data = buildDegradableJPEGMediaData(width, height, interchange_len, nullptr, totalSize);

    auto io = std::make_unique<MemIo>(data.get(), totalSize);
    io->open();
    AsfVideo video(std::move(io));

    video.DegradableJPEGMedia();

    EXPECT_EQ(video.pixelWidth(), 1u);
    EXPECT_EQ(video.pixelHeight(), 1u);
}

// Test: Verify XmpData keys are correctly named
TEST_F(AsfVideoTest_1566, DegradableJPEGMedia_XmpKeyNames_1566)
{
    uint32_t width = 800;
    uint32_t height = 600;
    uint16_t interchange_len = 0;
    size_t totalSize;
    auto data = buildDegradableJPEGMediaData(width, height, interchange_len, nullptr, totalSize);

    auto io = std::make_unique<MemIo>(data.get(), totalSize);
    io->open();
    AsfVideo video(std::move(io));

    video.DegradableJPEGMedia();

    XmpData& xmpData = video.xmpData();

    // Verify exact key names
    auto widthIt = xmpData.findKey(XmpKey("Xmp.video.Width"));
    auto heightIt = xmpData.findKey(XmpKey("Xmp.video.Height"));

    EXPECT_NE(widthIt, xmpData.end());
    EXPECT_NE(heightIt, xmpData.end());

    EXPECT_EQ(widthIt->key(), "Xmp.video.Width");
    EXPECT_EQ(heightIt->key(), "Xmp.video.Height");
}

// Test: AsfVideo constructor and mimeType
TEST_F(AsfVideoTest_1566, MimeType_1566)
{
    auto io = std::make_unique<MemIo>();
    AsfVideo video(std::move(io));

    EXPECT_EQ(video.mimeType(), "video/asf");
}

// Test: Width with high byte values
TEST_F(AsfVideoTest_1566, DegradableJPEGMedia_HighByteWidth_1566)
{
    uint32_t width = 0x0000FFFF;  // 65535
    uint32_t height = 0x0000FFFF;
    uint16_t interchange_len = 0;
    size_t totalSize;
    auto data = buildDegradableJPEGMediaData(width, height, interchange_len, nullptr, totalSize);

    auto io = std::make_unique<MemIo>(data.get(), totalSize);
    io->open();
    AsfVideo video(std::move(io));

    video.DegradableJPEGMedia();

    EXPECT_EQ(video.pixelWidth(), width);
    EXPECT_EQ(video.pixelHeight(), height);
}
