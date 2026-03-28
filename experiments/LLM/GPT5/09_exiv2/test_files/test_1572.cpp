// ============================================================================
// TEST_ID: 1572
// Unit tests for Exiv2::AsfVideo::fileProperties()
// File: ./TestProjects/exiv2/src/asfvideo.cpp (partial)
// ============================================================================

#include <gtest/gtest.h>

#if __has_include(<gmock/gmock.h>)
#include <gmock/gmock.h>
#endif

#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "exiv2/asfvideo.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

#if __has_include("exiv2/exceptions.hpp")
#include "exiv2/exceptions.hpp"
#endif

namespace {

// --- Minimal deterministic BasicIo test double --------------------------------
// Provides a read/seek/tell API backed by an in-memory buffer, and records seeks.
class RecordingMemIo final : public Exiv2::BasicIo {
 public:
  explicit RecordingMemIo(std::vector<Exiv2::byte> data) : data_(std::move(data)) {}

  size_t read(Exiv2::byte* buf, size_t rcount) override {
    if (!buf || rcount == 0) return 0;
    const size_t remaining = (pos_ < data_.size()) ? (data_.size() - pos_) : 0;
    const size_t n = (rcount < remaining) ? rcount : remaining;
    if (n > 0) {
      std::memcpy(buf, data_.data() + pos_, n);
      pos_ += n;
    }
    return n;
  }

  int seek(int64_t offset, Exiv2::BasicIo::Position pos) override {
    ++seek_calls_;
    last_seek_pos_ = pos;
    last_seek_offset_ = offset;

    int64_t base = 0;
    switch (pos) {
      case Exiv2::BasicIo::beg:
        base = 0;
        break;
      case Exiv2::BasicIo::cur:
        base = static_cast<int64_t>(pos_);
        break;
      case Exiv2::BasicIo::end:
        base = static_cast<int64_t>(data_.size());
        break;
      default:
        base = 0;
        break;
    }

    const int64_t newpos = base + offset;
    if (newpos < 0) {
      pos_ = 0;
      return 1;
    }
    pos_ = static_cast<size_t>(newpos);
    return 0;
  }

  const size_t tell() override { return pos_; }
  const size_t size() override { return data_.size(); }

  // Keep other virtuals as simple defaults
  int open() override { return 0; }
  int close() override { return 0; }
  const bool isopen() override { return true; }
  const int error() override { return 0; }
  const bool eof() override { return pos_ >= data_.size(); }
  const std::string& path() override { return path_; }

  // Recording accessors
  int seek_calls() const { return seek_calls_; }
  int64_t last_seek_offset() const { return last_seek_offset_; }
  Exiv2::BasicIo::Position last_seek_pos() const { return last_seek_pos_; }

 private:
  std::vector<Exiv2::byte> data_;
  size_t pos_{0};

  int seek_calls_{0};
  int64_t last_seek_offset_{0};
  Exiv2::BasicIo::Position last_seek_pos_{Exiv2::BasicIo::beg};

  std::string path_{"mem://recording"};
};

// --- Test hook to access protected fileProperties() ----------------------------
class TestAsfVideo final : public Exiv2::AsfVideo {
 public:
  explicit TestAsfVideo(std::unique_ptr<Exiv2::BasicIo> io) : Exiv2::AsfVideo(std::move(io)) {}
  void CallFileProperties() { fileProperties(); }  // protected -> public for tests
};

// Build a buffer matching what fileProperties() reads:
// GUID(16) + 6*QWORD(8) + skip(3*DWORD=12) + DWORD(4)
static std::vector<Exiv2::byte> MakeFilePropertiesBuffer(const std::array<Exiv2::byte, 16>& guid_bytes,
                                                         Exiv2::byte qword_fill,
                                                         Exiv2::byte skip_fill,
                                                         Exiv2::byte dword_fill) {
  std::vector<Exiv2::byte> v;
  v.insert(v.end(), guid_bytes.begin(), guid_bytes.end());

  // 6 QWORD tags (8 bytes each)
  for (int i = 0; i < 6 * 8; ++i) v.push_back(qword_fill);

  // skip Flags, Min Data Packet Size, Max Data Packet Size: 3 * DWORD = 12 bytes
  for (int i = 0; i < 12; ++i) v.push_back(skip_fill);

  // MaxBitRate DWORD (4 bytes)
  for (int i = 0; i < 4; ++i) v.push_back(dword_fill);

  return v;
}

// Helper: read XMP datum as int64 if possible, else fall back to string compare.
static void ExpectXmpInt64Eq(Exiv2::XmpData& xmp, const std::string& key, int64_t expected) {
  // operator[] creates if missing; so check via toInt64 after ensuring it was set by logic.
  // We avoid asserting count increments directly because operator[] may insert.
  const int64_t v = xmp[key].toInt64(0);
  EXPECT_EQ(v, expected) << "Key: " << key;
}

class AsfVideoFilePropertiesTest_1572 : public ::testing::Test {
 protected:
  static constexpr size_t kGuidSize = 16;
  static constexpr size_t kDword = 4;
};

TEST_F(AsfVideoFilePropertiesTest_1572, PopulatesXmpAndSeeksPastThreeDWORDs_1572) {
  // Arrange
  const std::array<Exiv2::byte, 16> guid = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                                           0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};

  // Use same-byte fills so numeric results are endianness-stable for this test.
  // QWORD bytes all 0x01 => value 0x0101010101010101
  // DWORD bytes all 0x02 => value 0x02020202
  auto buf = MakeFilePropertiesBuffer(guid, /*qword_fill=*/0x01, /*skip_fill=*/0xEE, /*dword_fill=*/0x02);

  auto io = std::make_unique<RecordingMemIo>(buf);
  RecordingMemIo* io_raw = io.get();

  TestAsfVideo video(std::move(io));

  // Act
  ASSERT_NO_THROW(video.CallFileProperties());

  // Assert: XMP keys set
  Exiv2::XmpData& xmp = video.xmpData();

  // FileID should match GUIDTag conversion exactly (public API).
  const std::string expected_guid_str = Exiv2::AsfVideo::GUIDTag(guid.data()).to_string();
  EXPECT_EQ(xmp["Xmp.video.FileID"].toString(), expected_guid_str);

  // Values for QWORD tags are stable because all bytes are identical.
  const int64_t expected_qword = static_cast<int64_t>(0x0101010101010101ULL);
  ExpectXmpInt64Eq(xmp, "Xmp.video.FileLength", expected_qword);
  ExpectXmpInt64Eq(xmp, "Xmp.video.CreationDate", expected_qword);
  ExpectXmpInt64Eq(xmp, "Xmp.video.DataPackets", expected_qword);
  ExpectXmpInt64Eq(xmp, "Xmp.video.duration", expected_qword);
  ExpectXmpInt64Eq(xmp, "Xmp.video.SendDuration", expected_qword);
  ExpectXmpInt64Eq(xmp, "Xmp.video.Preroll", expected_qword);

  const int64_t expected_dword = static_cast<int64_t>(0x02020202U);
  ExpectXmpInt64Eq(xmp, "Xmp.video.MaxBitRate", expected_dword);

  // Verify the explicit external interaction: seek(tell()+DWORD+DWORD+DWORD, beg)
  // At the moment of that seek call, tell() should be at:
  // GUID(16) + 6*QWORD(48) = 64
  const int64_t expected_seek_abs = static_cast<int64_t>(kGuidSize + 6 * 8 + 3 * kDword);  // 16+48+12 = 76
  EXPECT_GE(io_raw->seek_calls(), 1);
  EXPECT_EQ(io_raw->last_seek_pos(), Exiv2::BasicIo::beg);
  EXPECT_EQ(io_raw->last_seek_offset(), expected_seek_abs);
}

TEST_F(AsfVideoFilePropertiesTest_1572, SucceedsWithExactlyMinimumRequiredBytes_1572) {
  // Arrange: exactly GUID + 6*QWORD + 12 skip + 4 maxbitrate, nothing extra.
  const std::array<Exiv2::byte, 16> guid = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                           0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
  auto buf = MakeFilePropertiesBuffer(guid, /*qword_fill=*/0xAA, /*skip_fill=*/0xBB, /*dword_fill=*/0xCC);

  TestAsfVideo video(std::make_unique<RecordingMemIo>(buf));

  // Act / Assert
  EXPECT_NO_THROW(video.CallFileProperties());

  // Spot-check presence/non-empty values (format is implementation-defined for numbers),
  // while still black-boxing internal parsing.
  Exiv2::XmpData& xmp = video.xmpData();
  EXPECT_FALSE(xmp["Xmp.video.FileID"].toString().empty());
  EXPECT_FALSE(xmp["Xmp.video.FileLength"].toString().empty());
  EXPECT_FALSE(xmp["Xmp.video.MaxBitRate"].toString().empty());
}

TEST_F(AsfVideoFilePropertiesTest_1572, ThrowsWhenGuidCannotBeRead_1572) {
  // Arrange: fewer than GUID(16) bytes triggers io_->readOrThrow(..., kerCorruptedMetadata)
  std::vector<Exiv2::byte> too_short = {0x01, 0x02, 0x03};  // 3 bytes only

  TestAsfVideo video(std::make_unique<RecordingMemIo>(too_short));

  // Act / Assert
#if __has_include("exiv2/exceptions.hpp")
  EXPECT_THROW(video.CallFileProperties(), Exiv2::Error);
#else
  // Fallback: if the project doesn't expose Exiv2::Error here, at least require an exception.
  EXPECT_THROW(video.CallFileProperties(), std::exception);
#endif
}

}  // namespace