// File: test_asfvideo_codecList_1568.cpp
// TEST_ID: 1568

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "exiv2/asfvideo.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

namespace {

// A simple in-memory BasicIo implementation for feeding bytes to Exiv2 parsers.
// This is a test collaborator (not the class under test).
class BufferIo final : public Exiv2::BasicIo {
 public:
  using byte = Exiv2::byte;

  explicit BufferIo(std::vector<byte> data) : data_(std::move(data)) {}

  int open() override { open_ = true; return 0; }
  int close() override { open_ = false; return 0; }
  const bool isopen() override { return open_; }
  const int error() override { return 0; }
  const bool eof() override { return pos_ >= data_.size(); }
  const std::string& path() override { return path_; }

  size_t read(byte* buf, size_t rcount) override {
    if (!buf || rcount == 0) return 0;
    const size_t remaining = (pos_ <= data_.size()) ? (data_.size() - pos_) : 0;
    const size_t n = (rcount < remaining) ? rcount : remaining;
    if (n > 0) {
      std::memcpy(buf, data_.data() + pos_, n);
      pos_ += n;
    }
    return n;
  }

  Exiv2::DataBuf read(size_t /*rcount*/) override {
    // Not needed for these tests; codecList() in Exiv2 typically uses read(byte*, n) / readOrThrow.
    return Exiv2::DataBuf();
  }

  int seek(int64_t offset, Exiv2::BasicIo::Position pos) override {
    int64_t base = 0;
    switch (pos) {
      case Exiv2::BasicIo::beg: base = 0; break;
      case Exiv2::BasicIo::cur: base = static_cast<int64_t>(pos_); break;
      case Exiv2::BasicIo::end: base = static_cast<int64_t>(data_.size()); break;
      default: base = 0; break;
    }
    const int64_t np = base + offset;
    if (np < 0) {
      pos_ = 0;
      return 1;
    }
    if (static_cast<size_t>(np) > data_.size()) {
      pos_ = data_.size();
      return 1;
    }
    pos_ = static_cast<size_t>(np);
    return 0;
  }

  const size_t tell() override { return pos_; }
  const size_t size() override { return data_.size(); }

  // Unused write-related API for these tests.
  size_t write(const byte* /*data*/, size_t /*wcount*/) override { return 0; }
  size_t write(Exiv2::BasicIo& /*src*/) override { return 0; }
  int putb(byte /*data*/) override { return 0; }
  int getb() override { return -1; }
  void transfer(Exiv2::BasicIo& /*src*/) override {}
  byte* mmap(bool /*isWriteable*/) override { return nullptr; }
  int munmap() override { return 0; }
  void populateFakeData() override {}

 private:
  std::vector<byte> data_;
  size_t pos_{0};
  bool open_{true};
  std::string path_{"(BufferIo)"};
};

// Expose protected codecList() for direct testing (black-box over the public/protected interface).
class TestAsfVideo final : public Exiv2::AsfVideo {
 public:
  using Exiv2::AsfVideo::AsfVideo;
  using Exiv2::AsfVideo::codecList;  // protected -> public
};

// Helpers to build little-endian test payloads.
static void AppendU16LE(std::vector<Exiv2::byte>& out, uint16_t v) {
  out.push_back(static_cast<Exiv2::byte>(v & 0xFF));
  out.push_back(static_cast<Exiv2::byte>((v >> 8) & 0xFF));
}

static void AppendU32LE(std::vector<Exiv2::byte>& out, uint32_t v) {
  out.push_back(static_cast<Exiv2::byte>(v & 0xFF));
  out.push_back(static_cast<Exiv2::byte>((v >> 8) & 0xFF));
  out.push_back(static_cast<Exiv2::byte>((v >> 16) & 0xFF));
  out.push_back(static_cast<Exiv2::byte>((v >> 24) & 0xFF));
}

static void AppendAscii(std::vector<Exiv2::byte>& out, const std::string& s) {
  out.insert(out.end(), s.begin(), s.end());
}

static void AppendUtf16LeAscii(std::vector<Exiv2::byte>& out, const std::string& s) {
  // Encode ASCII chars as UTF-16LE (char, 0x00).
  for (char c : s) {
    out.push_back(static_cast<Exiv2::byte>(static_cast<unsigned char>(c)));
    out.push_back(static_cast<Exiv2::byte>(0x00));
  }
}

}  // namespace

class AsfVideoCodecListTest_1568 : public ::testing::Test {
 protected:
  static std::unique_ptr<TestAsfVideo> MakeVideoFromBytes_1568(std::vector<Exiv2::byte> bytes) {
    auto io = std::make_unique<BufferIo>(std::move(bytes));
    return std::make_unique<TestAsfVideo>(std::move(io));
  }
};

TEST_F(AsfVideoCodecListTest_1568, PopulatesAudioKeysForSingleEntry_1568) {
  // Build: [16 reserved GUID bytes] + entries_count(1) + one codec entry:
  // codec_type(word) -> multiplied by 2 internally; choose 0 so it won't equal 1 (observably audio branch).
  // name_len(word) -> multiplied by 2 internally (UTF-16LE bytes length). Use 4 => 8 bytes for "TEST".
  // desc_len(word) -> passed directly to readStringWcharTag; use 8 bytes => "DESC" UTF-16LE.
  // info_len(word) -> must be >0 and < (size - tell). Use 4 bytes => "INFO".
  std::vector<Exiv2::byte> b;
  b.resize(16, 0x00);                 // GUID reserved
  AppendU32LE(b, 1);                  // entries_count = 1
  AppendU16LE(b, 0);                  // codec_type raw
  AppendU16LE(b, 4);                  // codec_name_length raw (wchar count); internal *2 => 8 bytes
  AppendUtf16LeAscii(b, "TEST");      // 8 bytes
  AppendU16LE(b, 8);                  // codec_desc_length (bytes)
  AppendUtf16LeAscii(b, "DESC");      // 8 bytes
  AppendU16LE(b, 4);                  // codec_info_length (bytes)
  AppendAscii(b, "INFO");             // 4 bytes

  auto video = MakeVideoFromBytes_1568(std::move(b));
  ASSERT_NO_THROW(video->codecList());

  // Verify observable effect: XMP keys exist with non-empty values.
  auto& xd = video->xmpData();

  const std::string base = "Xmp.audio";
  EXPECT_FALSE(xd[base + ".CodecName"].toString().empty());
  EXPECT_FALSE(xd[base + ".CodecDescription"].toString().empty());
  EXPECT_EQ(xd[base + ".CodecInfo"].toString(), "INFO");
}

TEST_F(AsfVideoCodecListTest_1568, OmitsCodecNameWhenLengthIsZero_1568) {
  std::vector<Exiv2::byte> b;
  b.resize(16, 0x00);
  AppendU32LE(b, 1);

  AppendU16LE(b, 0);   // codec_type raw -> audio path
  AppendU16LE(b, 0);   // codec_name_length raw => 0 => no name read
  AppendU16LE(b, 0);   // codec_desc_length => 0 => no description read
  AppendU16LE(b, 3);   // codec_info_length => 3
  AppendAscii(b, "ABC");

  auto video = MakeVideoFromBytes_1568(std::move(b));
  ASSERT_NO_THROW(video->codecList());

  auto& xd = video->xmpData();
  const std::string base = "Xmp.audio";

  // operator[] will create if missing, so check presence via findKey using XmpKey would be ideal.
  // Here we verify behavior by reading and expecting empty for absent optional fields (best-effort black-box check).
  // CodecInfo must be present and equal to "ABC".
  EXPECT_EQ(xd[base + ".CodecInfo"].toString(), "ABC");

  // Optional fields: if not set, toString() should be empty.
  EXPECT_TRUE(xd[base + ".CodecName"].toString().empty());
  EXPECT_TRUE(xd[base + ".CodecDescription"].toString().empty());
}

TEST_F(AsfVideoCodecListTest_1568, HandlesMultipleEntries_1568) {
  std::vector<Exiv2::byte> b;
  b.resize(16, 0x00);
  AppendU32LE(b, 2);  // two entries

  // Entry 1
  AppendU16LE(b, 0);
  AppendU16LE(b, 2);             // name wchar count => 4 bytes
  AppendUtf16LeAscii(b, "A1");   // 4 bytes
  AppendU16LE(b, 0);             // desc length 0
  AppendU16LE(b, 2);             // info length 2
  AppendAscii(b, "I1");

  // Entry 2
  AppendU16LE(b, 0);
  AppendU16LE(b, 2);
  AppendUtf16LeAscii(b, "A2");
  AppendU16LE(b, 0);
  AppendU16LE(b, 2);
  AppendAscii(b, "I2");

  auto video = MakeVideoFromBytes_1568(std::move(b));
  ASSERT_NO_THROW(video->codecList());

  // Both entries write to the same key family; last write should be observable in CodecInfo at least.
  auto& xd = video->xmpData();
  const std::string base = "Xmp.audio";
  EXPECT_EQ(xd[base + ".CodecInfo"].toString(), "I2");
}

TEST_F(AsfVideoCodecListTest_1568, ThrowsOnZeroCodecInfoLength_1568) {
  std::vector<Exiv2::byte> b;
  b.resize(16, 0x00);
  AppendU32LE(b, 1);

  AppendU16LE(b, 0);
  AppendU16LE(b, 0);  // name len 0
  AppendU16LE(b, 0);  // desc len 0
  AppendU16LE(b, 0);  // codec_info_length => enforce(codec_info_length && ...) should fail

  auto video = MakeVideoFromBytes_1568(std::move(b));
  EXPECT_THROW(video->codecList(), Exiv2::Error);
}

TEST_F(AsfVideoCodecListTest_1568, ThrowsWhenCodecInfoLengthConsumesRemainingBytes_1568) {
  // enforce requires codec_info_length < io_->size() - io_->tell()
  // Make remaining exactly equal, so it should throw.
  std::vector<Exiv2::byte> b;
  b.resize(16, 0x00);
  AppendU32LE(b, 1);

  AppendU16LE(b, 0);
  AppendU16LE(b, 0);  // name len 0
  AppendU16LE(b, 0);  // desc len 0

  // At this point, we'll add codec_info_length and then exactly that many bytes remaining.
  AppendU16LE(b, 4);
  AppendAscii(b, "DATA");  // remaining == 4

  auto video = MakeVideoFromBytes_1568(std::move(b));
  EXPECT_THROW(video->codecList(), Exiv2::Error);
}