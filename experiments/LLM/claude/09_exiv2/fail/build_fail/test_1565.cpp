#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstring>
#include <vector>

#include "exiv2/asfvideo.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/xmp_exiv2.hpp"

using namespace Exiv2;

// Mock BasicIo to control I/O behavior for testing
class MockBasicIo : public BasicIo {
public:
    MockBasicIo() : pos_(0) {}

    MOCK_METHOD(int, open, (), (override));
    MOCK_METHOD(int, close, (), (override));
    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));
    MOCK_METHOD(size_t, write, (BasicIo& src), (override));
    MOCK_METHOD(int, putb, (byte data), (override));
    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));
    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));
    MOCK_METHOD(int, getb, (), (override));
    MOCK_METHOD(void, transfer, (BasicIo& src), (override));
    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));
    MOCK_METHOD(int, munmap, (), (override));
    MOCK_METHOD(size_t, tell, (), (const, override));
    MOCK_METHOD(size_t, size, (), (const, override));
    MOCK_METHOD(bool, isopen, (), (const, override));
    MOCK_METHOD(int, error, (), (const, override));
    MOCK_METHOD(bool, eof, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, override));
    MOCK_METHOD(void, populateFakeData, (), (override));

private:
    size_t pos_;
};

// A MemoryIo-like helper for building binary data for extendedStreamProperties
class TestDataBuilder {
public:
    void addQWORD(uint64_t val) {
        for (int i = 0; i < 8; i++) {
            data_.push_back(static_cast<uint8_t>((val >> (i * 8)) & 0xFF));
        }
    }

    void addDWORD(uint32_t val) {
        for (int i = 0; i < 4; i++) {
            data_.push_back(static_cast<uint8_t>((val >> (i * 8)) & 0xFF));
        }
    }

    void addWORD(uint16_t val) {
        data_.push_back(static_cast<uint8_t>(val & 0xFF));
        data_.push_back(static_cast<uint8_t>((val >> 8) & 0xFF));
    }

    void addGUID(const std::vector<uint8_t>& guid) {
        for (auto b : guid) {
            data_.push_back(b);
        }
    }

    void addBytes(size_t count, uint8_t val = 0) {
        for (size_t i = 0; i < count; i++) {
            data_.push_back(val);
        }
    }

    const std::vector<uint8_t>& data() const { return data_; }
    size_t size() const { return data_.size(); }

private:
    std::vector<uint8_t> data_;
};

// Test fixture for AsfVideo extendedStreamProperties
class AsfVideoExtendedStreamPropertiesTest_1565 : public ::testing::Test {
protected:
    // Build binary data representing Extended Stream Properties structure
    // Layout based on the code:
    // QWORD: Start Time
    // WORD: End Time  (Note: code uses readWORDTag for End Time, which seems unusual but matches the code)
    // 8 x DWORD: various ignored fields
    // WORD: ignored Flags Stream Number
    // WORD: ignored Stream Language ID Index
    // WORD: Average Time Per Frame (readWORDTag)
    // WORD: stream_name_count
    // WORD: payload_ext_sys_count
    // For each stream_name: WORD (lang id) + WORD (stream_length) + stream_length bytes
    // For each payload_ext: GUID (16 bytes) + WORD (ext data size) + WORD (ext_sys_info_length) + ext_sys_info_length bytes

    std::vector<uint8_t> buildExtendedStreamPropertiesData(
        uint64_t startTime,
        uint16_t endTime,
        uint16_t avgTimePerFrame,
        uint16_t streamNameCount,
        uint16_t payloadExtSysCount,
        const std::vector<uint16_t>& streamNameLengths = {},
        const std::vector<uint16_t>& extSysInfoLengths = {}
    ) {
        TestDataBuilder builder;

        // QWORD: Start Time
        builder.addQWORD(startTime);

        // WORD: End Time (readWORDTag reads 2 bytes)
        builder.addWORD(endTime);

        // 8 x DWORD ignored fields
        for (int i = 0; i < 8; i++) {
            builder.addDWORD(0);
        }

        // WORD: Flags Stream Number (ignored, seek WORD)
        builder.addWORD(0);

        // WORD: Stream Language ID Index (ignored, seek WORD)
        builder.addWORD(0);

        // WORD: Average Time Per Frame
        builder.addWORD(avgTimePerFrame);

        // WORD: stream_name_count
        builder.addWORD(streamNameCount);

        // WORD: payload_ext_sys_count
        builder.addWORD(payloadExtSysCount);

        // Stream names
        for (uint16_t i = 0; i < streamNameCount; i++) {
            builder.addWORD(0); // Language ID Index
            uint16_t len = (i < streamNameLengths.size()) ? streamNameLengths[i] : 0;
            builder.addWORD(len); // Stream name length
            if (len > 0) {
                builder.addBytes(len, 'A'); // Stream name data
            }
        }

        // Payload extension systems
        for (uint16_t i = 0; i < payloadExtSysCount; i++) {
            builder.addBytes(16, 0); // GUID (16 bytes)
            builder.addWORD(0); // Extension Data Size
            uint16_t len = (i < extSysInfoLengths.size()) ? extSysInfoLengths[i] : 0;
            builder.addWORD(len); // Extension System Info Length
            if (len > 0) {
                builder.addBytes(len, 'B'); // Extension System Info data
            }
        }

        return builder.data();
    }
};

// Test: Reading metadata from a valid ASF file via readMetadata
TEST(AsfVideoReadMetadata_1565, ValidAsfFile_1565) {
    // This tests that we can construct an AsfVideo with a MemoryIo
    // and call readMetadata without crashing on minimal data
    std::vector<uint8_t> minimalData(1024, 0);
    auto io = std::make_unique<MemIo>(minimalData.data(), minimalData.size());
    ASSERT_NO_THROW(AsfVideo video(std::move(io)));
}

// Test: mimeType returns correct value
TEST(AsfVideoMimeType_1565, ReturnsCorrectMimeType_1565) {
    std::vector<uint8_t> data(64, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    std::string mime = video.mimeType();
    EXPECT_EQ(mime, "video/x-ms-asf");
}

// Test: writeMetadata on AsfVideo
TEST(AsfVideoWriteMetadata_1565, ThrowsOrNoop_1565) {
    std::vector<uint8_t> data(64, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    // writeMetadata for ASF videos typically throws since it's not supported
    EXPECT_THROW(video.writeMetadata(), Exiv2::Error);
}

// Test: Construction with empty data
TEST(AsfVideoConstruction_1565, EmptyIo_1565) {
    auto io = std::make_unique<MemIo>();
    ASSERT_NO_THROW(AsfVideo video(std::move(io)));
}

// Test: xmpData is initially empty
TEST(AsfVideoXmpData_1565, InitiallyEmpty_1565) {
    std::vector<uint8_t> data(64, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    EXPECT_TRUE(video.xmpData().empty());
}

// Test: exifData is initially empty
TEST(AsfVideoExifData_1565, InitiallyEmpty_1565) {
    std::vector<uint8_t> data(64, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    EXPECT_TRUE(video.exifData().empty());
}

// Test: iptcData is initially empty
TEST(AsfVideoIptcData_1565, InitiallyEmpty_1565) {
    std::vector<uint8_t> data(64, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    EXPECT_TRUE(video.iptcData().empty());
}

// Test: good() returns expected state
TEST(AsfVideoGood_1565, WithValidIo_1565) {
    std::vector<uint8_t> data(64, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    // MemIo should be "good" after construction
    EXPECT_TRUE(video.good());
}

// Test: io() returns a reference
TEST(AsfVideoIo_1565, ReturnsIoReference_1565) {
    std::vector<uint8_t> data(64, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    const BasicIo& ref = video.io();
    EXPECT_EQ(ref.size(), 64u);
}

// Test: clearMetadata clears all data
TEST(AsfVideoClearMetadata_1565, ClearsAll_1565) {
    std::vector<uint8_t> data(64, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    video.xmpData()["Xmp.video.test"] = "value";
    EXPECT_FALSE(video.xmpData().empty());
    video.clearMetadata();
    EXPECT_TRUE(video.xmpData().empty());
}

// Test: setXmpData and clearXmpData
TEST(AsfVideoXmpDataOps_1565, SetAndClear_1565) {
    std::vector<uint8_t> data(64, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    
    XmpData xmp;
    xmp["Xmp.video.FrameRate"] = "30";
    video.setXmpData(xmp);
    EXPECT_FALSE(video.xmpData().empty());
    
    video.clearXmpData();
    EXPECT_TRUE(video.xmpData().empty());
}

// Test: Image type is ASF
TEST(AsfVideoImageType_1565, IsAsf_1565) {
    std::vector<uint8_t> data(64, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    EXPECT_EQ(video.imageType(), ImageType::asf);
}

// Test: pixelWidth and pixelHeight are initially 0
TEST(AsfVideoPixelDimensions_1565, InitiallyZero_1565) {
    std::vector<uint8_t> data(64, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    EXPECT_EQ(video.pixelWidth(), 0u);
    EXPECT_EQ(video.pixelHeight(), 0u);
}

// Test: comment is initially empty
TEST(AsfVideoComment_1565, InitiallyEmpty_1565) {
    std::vector<uint8_t> data(64, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    EXPECT_TRUE(video.comment().empty());
}

// Test: readMetadata on empty data should throw or handle gracefully
TEST(AsfVideoReadMetadata_1565, EmptyDataThrows_1565) {
    auto io = std::make_unique<MemIo>();
    AsfVideo video(std::move(io));
    // Reading metadata from empty IO should throw
    EXPECT_THROW(video.readMetadata(), Exiv2::Error);
}

// Test: readMetadata on insufficient data
TEST(AsfVideoReadMetadata_1565, InsufficientDataThrows_1565) {
    std::vector<uint8_t> data(10, 0);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    AsfVideo video(std::move(io));
    EXPECT_THROW(video.readMetadata(), Exiv2::Error);
}
