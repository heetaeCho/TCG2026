#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstring>
#include <vector>

#include "exiv2/asfvideo.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

// We need a mock BasicIo to control what the AsfVideo reads
class MockBasicIo : public Exiv2::BasicIo {
public:
    MockBasicIo() : Exiv2::BasicIo(), data_(), pos_(0), size_(0) {}

    void setData(const std::vector<uint8_t>& d) {
        data_ = d;
        size_ = d.size();
        pos_ = 0;
    }

    int open() override { return 0; }
    int close() override { return 0; }

    size_t write(const Exiv2::byte* data, size_t wcount) override { return 0; }
    size_t write(BasicIo& src) override { return 0; }
    int putb(Exiv2::byte data) override { return 0; }

    Exiv2::DataBuf read(size_t rcount) override {
        Exiv2::DataBuf buf(rcount);
        size_t bytesRead = read(buf.data(), rcount);
        if (bytesRead < rcount) {
            buf = Exiv2::DataBuf(buf.data(), bytesRead);
        }
        return buf;
    }

    size_t read(Exiv2::byte* buf, size_t rcount) override {
        if (pos_ >= size_) return 0;
        size_t toRead = std::min(rcount, size_ - pos_);
        std::memcpy(buf, data_.data() + pos_, toRead);
        pos_ += toRead;
        return toRead;
    }

    int getb() override {
        if (pos_ >= size_) return EOF;
        return data_[pos_++];
    }

    void transfer(BasicIo& src) override {}

    int seek(int64_t offset, Position pos) override {
        switch (pos) {
            case beg: pos_ = static_cast<size_t>(offset); break;
            case cur: pos_ += static_cast<size_t>(offset); break;
            case end: pos_ = size_ + static_cast<size_t>(offset); break;
        }
        if (pos_ > size_) pos_ = size_;
        return 0;
    }

    Exiv2::byte* mmap(bool isWriteable) override { return nullptr; }
    int munmap() override { return 0; }

    size_t tell() const override { return pos_; }
    size_t size() const override { return size_; }
    bool isopen() const override { return true; }
    int error() const override { return 0; }
    bool eof() const override { return pos_ >= size_; }
    const std::string& path() const override {
        static std::string p = "mock";
        return p;
    }
    void populateFakeData() override {}

private:
    std::vector<uint8_t> data_;
    size_t pos_;
    size_t size_;
};

// Helper to write a little-endian uint16_t
static void writeLE16(std::vector<uint8_t>& buf, uint16_t val) {
    buf.push_back(static_cast<uint8_t>(val & 0xFF));
    buf.push_back(static_cast<uint8_t>((val >> 8) & 0xFF));
}

// Helper to write a little-endian uint32_t
static void writeLE32(std::vector<uint8_t>& buf, uint32_t val) {
    buf.push_back(static_cast<uint8_t>(val & 0xFF));
    buf.push_back(static_cast<uint8_t>((val >> 8) & 0xFF));
    buf.push_back(static_cast<uint8_t>((val >> 16) & 0xFF));
    buf.push_back(static_cast<uint8_t>((val >> 24) & 0xFF));
}

// Helper to write a wide string (UTF-16LE, each char is 2 bytes)
static void writeWideString(std::vector<uint8_t>& buf, const std::string& str) {
    for (char c : str) {
        buf.push_back(static_cast<uint8_t>(c));
        buf.push_back(0);
    }
}

// Helper to write a byte string
static void writeString(std::vector<uint8_t>& buf, const std::string& str) {
    for (char c : str) {
        buf.push_back(static_cast<uint8_t>(c));
    }
}

class AsfVideoCodecListTest_1568 : public ::testing::Test {
protected:
    // Since AsfVideo's constructor takes a unique_ptr<BasicIo>, and codecList() is protected,
    // we need to use readMetadata or find another way. However, codecList is protected.
    // We'll create a derived class to expose it for testing.
};

// Since codecList() is protected, we need a test wrapper
class TestableAsfVideo : public Exiv2::AsfVideo {
public:
    explicit TestableAsfVideo(std::unique_ptr<Exiv2::BasicIo> io)
        : Exiv2::AsfVideo(std::move(io)) {}

    void callCodecList() {
        codecList();
    }

    Exiv2::XmpData& getXmpData() {
        return xmpData();
    }
};

// Build data buffer for codecList:
// First 16 bytes: GUID (skipped via seek)
// Then DWORD: entries_count
// For each entry:
//   WORD: codec_type (multiplied by 2 in code, if result==1 => "Xmp.video", else "Xmp.audio")
//   WORD: codec_name_length (multiplied by 2 in code to get byte count for wchar reading)
//   [codec_name_length*2 bytes of wchar data]
//   WORD: codec_desc_length (NOT multiplied by 2 in code for reading, but used as-is for wchar reading)
//   [codec_desc_length bytes of wchar data]
//   WORD: codec_info_length
//   [codec_info_length bytes of string data]

TEST(AsfVideoCodecListTest_1568, ZeroEntries_1568) {
    auto mockIo = std::make_unique<MockBasicIo>();

    std::vector<uint8_t> data;
    // 16 bytes for GUID (will be skipped)
    for (int i = 0; i < 16; i++) data.push_back(0);
    // entries_count = 0
    writeLE32(data, 0);

    // Pad some extra data so size is reasonable
    for (int i = 0; i < 64; i++) data.push_back(0);

    mockIo->setData(data);

    TestableAsfVideo video(std::move(mockIo));
    EXPECT_NO_THROW(video.callCodecList());
    EXPECT_TRUE(video.getXmpData().empty());
}

TEST(AsfVideoCodecListTest_1568, SingleVideoCodecEntry_1568) {
    auto mockIo = std::make_unique<MockBasicIo>();

    std::vector<uint8_t> data;
    // 16 bytes for GUID
    for (int i = 0; i < 16; i++) data.push_back(0);

    // entries_count = 1
    writeLE32(data, 1);

    // codec_type: we want codec_type * 2 == 1, but codec_type is uint16_t,
    // and 1/2 = 0 in integer, so codec_type*2 == 1 is impossible for integer.
    // Actually looking at the code: uint16_t codec_type = readWORDTag(io_) * 2;
    // So if we read 0, codec_type = 0 => "Xmp.audio"
    // If we read 1, codec_type = 2 => "Xmp.audio"
    // For codec_type == 1, we'd need readWORDTag to return 0.5 which isn't possible.
    // So "Xmp.video" case might never be triggered with integer multiplication...
    // Unless the check is meant differently. Let's test with codec_type resulting in audio.

    // codec_type raw = 1 => codec_type = 1*2 = 2 => "Xmp.audio"
    writeLE16(data, 1);

    // codec_name_length raw = 3 => actual = 3*2 = 6 bytes to read
    writeLE16(data, 3);
    // Write 6 bytes of wchar data: "ABC" in UTF-16LE
    writeWideString(data, "ABC");

    // codec_desc_length = 4 (bytes to read as wchar)
    writeLE16(data, 4);
    // Write 4 bytes of wchar data: "DE"
    writeWideString(data, "DE");

    // codec_info_length = 3
    writeLE16(data, 3);
    // Write 3 bytes of string data
    writeString(data, "xyz");

    // Pad extra data
    for (int i = 0; i < 128; i++) data.push_back(0);

    mockIo->setData(data);

    TestableAsfVideo video(std::move(mockIo));
    EXPECT_NO_THROW(video.callCodecList());

    auto& xmp = video.getXmpData();
    // Should have audio codec entries
    EXPECT_FALSE(xmp.empty());
}

TEST(AsfVideoCodecListTest_1568, CodecInfoLengthZeroThrows_1568) {
    // codec_info_length = 0 should trigger enforce failure (kerCorruptedMetadata)
    auto mockIo = std::make_unique<MockBasicIo>();

    std::vector<uint8_t> data;
    // 16 bytes for GUID
    for (int i = 0; i < 16; i++) data.push_back(0);

    // entries_count = 1
    writeLE32(data, 1);

    // codec_type raw = 0 => codec_type = 0 => "Xmp.audio"
    writeLE16(data, 0);

    // codec_name_length raw = 0 => actual = 0 => skip name
    writeLE16(data, 0);

    // codec_desc_length = 0 => skip desc
    writeLE16(data, 0);

    // codec_info_length = 0 => should fail enforce
    writeLE16(data, 0);

    // Pad
    for (int i = 0; i < 128; i++) data.push_back(0);

    mockIo->setData(data);

    TestableAsfVideo video(std::move(mockIo));
    EXPECT_THROW(video.callCodecList(), Exiv2::Error);
}

TEST(AsfVideoCodecListTest_1568, CodecInfoLengthExceedsSizeThrows_1568) {
    // codec_info_length > remaining data should trigger enforce failure
    auto mockIo = std::make_unique<MockBasicIo>();

    std::vector<uint8_t> data;
    // 16 bytes for GUID
    for (int i = 0; i < 16; i++) data.push_back(0);

    // entries_count = 1
    writeLE32(data, 1);

    // codec_type raw = 0
    writeLE16(data, 0);

    // codec_name_length raw = 0
    writeLE16(data, 0);

    // codec_desc_length = 0
    writeLE16(data, 0);

    // codec_info_length = 60000 (way more than remaining data)
    writeLE16(data, 60000);

    // Very small padding
    for (int i = 0; i < 10; i++) data.push_back(0);

    mockIo->setData(data);

    TestableAsfVideo video(std::move(mockIo));
    EXPECT_THROW(video.callCodecList(), Exiv2::Error);
}

TEST(AsfVideoCodecListTest_1568, MultipleEntries_1568) {
    auto mockIo = std::make_unique<MockBasicIo>();

    std::vector<uint8_t> data;
    // 16 bytes for GUID
    for (int i = 0; i < 16; i++) data.push_back(0);

    // entries_count = 2
    writeLE32(data, 2);

    // --- Entry 1: audio codec ---
    writeLE16(data, 0); // codec_type raw=0, *2=0, => "Xmp.audio"
    writeLE16(data, 2); // codec_name_length raw=2, *2=4 bytes
    writeWideString(data, "AB"); // 4 bytes
    writeLE16(data, 2); // codec_desc_length=2 bytes
    writeWideString(data, "C"); // actually only 2 bytes for 1 wchar
    writeLE16(data, 1); // codec_info_length=1
    writeString(data, "X"); // 1 byte

    // --- Entry 2: also audio ---
    writeLE16(data, 2); // codec_type raw=2, *2=4, => "Xmp.audio"
    writeLE16(data, 0); // codec_name_length=0, skip
    writeLE16(data, 0); // codec_desc_length=0, skip
    writeLE16(data, 2); // codec_info_length=2
    writeString(data, "YZ"); // 2 bytes

    // Pad extra
    for (int i = 0; i < 256; i++) data.push_back(0);

    mockIo->setData(data);

    TestableAsfVideo video(std::move(mockIo));
    EXPECT_NO_THROW(video.callCodecList());

    auto& xmp = video.getXmpData();
    EXPECT_FALSE(xmp.empty());
}

TEST(AsfVideoCodecListTest_1568, SkipNameWhenLengthZero_1568) {
    auto mockIo = std::make_unique<MockBasicIo>();

    std::vector<uint8_t> data;
    // 16 bytes for GUID
    for (int i = 0; i < 16; i++) data.push_back(0);

    // entries_count = 1
    writeLE32(data, 1);

    writeLE16(data, 0); // codec_type raw=0
    writeLE16(data, 0); // codec_name_length=0 (skip name)
    writeLE16(data, 0); // codec_desc_length=0 (skip desc)
    writeLE16(data, 1); // codec_info_length=1
    writeString(data, "Z");

    // Pad
    for (int i = 0; i < 128; i++) data.push_back(0);

    mockIo->setData(data);

    TestableAsfVideo video(std::move(mockIo));
    EXPECT_NO_THROW(video.callCodecList());

    auto& xmp = video.getXmpData();
    // Should only have CodecInfo, not CodecName or CodecDescription
    auto it = xmp.findKey(Exiv2::XmpKey("Xmp.audio.CodecInfo"));
    EXPECT_NE(it, xmp.end());
}

TEST(AsfVideoCodecListTest_1568, MimeType_1568) {
    auto mockIo = std::make_unique<MockBasicIo>();
    std::vector<uint8_t> data(256, 0);
    mockIo->setData(data);

    Exiv2::AsfVideo video(std::move(mockIo));
    std::string mime = video.mimeType();
    EXPECT_FALSE(mime.empty());
}
