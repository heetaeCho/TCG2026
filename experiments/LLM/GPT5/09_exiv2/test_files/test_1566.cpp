// ============================================================================
// TEST_ID: 1566
// File: test_asfvideo_degradablejpegmedia_1566.cpp
// ============================================================================

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <vector>

#include "exiv2/asfvideo.hpp"
#include "exiv2/basicio.hpp"

namespace {

// A minimal in-memory BasicIo implementation to drive AsfVideo via its public/protected interface.
// This is an external collaborator (I/O dependency), so implementing a test double is allowed.
class MemBasicIo final : public Exiv2::BasicIo {
 public:
  explicit MemBasicIo(std::vector<Exiv2::byte> data) : data_(std::move(data)) {}

  int open() override {
    open_ = true;
    err_ = 0;
    return 0;
  }

  int close() override {
    open_ = false;
    return 0;
  }

  size_t read(Exiv2::byte* buf, size_t rcount) override {
    if (!open_) {
      err_ = 1;
      return 0;
    }
    const size_t avail = (pos_ < data_.size()) ? (data_.size() - pos_) : 0;
    const size_t n = (rcount < avail) ? rcount : avail;
    for (size_t i = 0; i < n; ++i) {
      buf[i] = data_[pos_ + i];
    }
    pos_ += n;
    if (n < rcount) {
      eof_ = true;
    }
    return n;
  }

  Exiv2::DataBuf read(size_t /*rcount*/) override {
    // Not needed for these tests; keep behavior simple and consistent.
    return Exiv2::DataBuf();
  }

  int seek(int64_t offset, Exiv2::BasicIo::Position pos) override {
    if (!open_) {
      err_ = 1;
      return 1;
    }

    int64_t base = 0;
    if (pos == Exiv2::BasicIo::beg) {
      base = 0;
    } else if (pos == Exiv2::BasicIo::cur) {
      base = static_cast<int64_t>(pos_);
    } else {  // end
      base = static_cast<int64_t>(data_.size());
    }

    const int64_t next = base + offset;
    if (next < 0) {
      err_ = 1;
      return 1;
    }
    pos_ = static_cast<size_t>(next);
    eof_ = (pos_ >= data_.size());
    err_ = 0;
    return 0;
  }

  const size_t tell() override { return pos_; }
  const size_t size() override { return data_.size(); }
  const bool isopen() override { return open_; }
  const int error() override { return err_; }
  const bool eof() override { return eof_; }

  // Unused virtuals for this test; provide minimal safe stubs.
  size_t write(const Exiv2::byte* /*data*/, size_t /*wcount*/) override { return 0; }
  size_t write(Exiv2::BasicIo& /*src*/) override { return 0; }
  int putb(Exiv2::byte /*data*/) override { return 0; }
  int getb() override { return -1; }
  Exiv2::byte* mmap(bool /*isWriteable*/) override { return nullptr; }
  int munmap() override { return 0; }
  const std::string& path() override { return path_; }
  void transfer(Exiv2::BasicIo& /*src*/) override {}
  void populateFakeData() override {}

 private:
  std::vector<Exiv2::byte> data_;
  size_t pos_{0};
  bool open_{false};
  bool eof_{false};
  int err_{0};
  std::string path_{};
};

// Expose the protected method for unit testing without touching internal state.
class TestableAsfVideo final : public Exiv2::AsfVideo {
 public:
  explicit TestableAsfVideo(std::unique_ptr<Exiv2::BasicIo> io) : Exiv2::AsfVideo(std::move(io)) {}
  using Exiv2::AsfVideo::DegradableJPEGMedia;
};

// Helper to append bytes.
static void AppendBytes(std::vector<Exiv2::byte>& out, std::initializer_list<uint8_t> bytes) {
  for (uint8_t b : bytes) out.push_back(static_cast<Exiv2::byte>(b));
}

static std::vector<Exiv2::byte> BuildPayload(
    uint8_t width_byte, uint8_t height_byte, uint16_t interchange_len, uint8_t interchange_fill) {
  std::vector<Exiv2::byte> buf;

  // width DWORD: choose same-byte pattern so endianness doesn't matter for expected value.
  AppendBytes(buf, {width_byte, width_byte, width_byte, width_byte});
  // height DWORD
  AppendBytes(buf, {height_byte, height_byte, height_byte, height_byte});
  // 3 reserved WORDs => 6 bytes
  AppendBytes(buf, {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF});

  // interchange_data_length WORD. Use same-byte pattern too.
  const uint8_t len_b = static_cast<uint8_t>(interchange_len & 0xFF);
  // Keep it symmetric (len_b == high byte) by requiring interchange_len == len_b * 257 in tests.
  AppendBytes(buf, {len_b, len_b});

  // interchange data payload
  for (uint16_t i = 0; i < interchange_len; ++i) {
    buf.push_back(static_cast<Exiv2::byte>(interchange_fill));
  }
  return buf;
}

class AsfVideoDegradableJPEGMediaTest_1566 : public ::testing::Test {
 protected:
  static constexpr int64_t kHeaderBytesBeforeInterchange = 4 + 4 + 6 + 2;  // width+height+reserved+len

  static int64_t ExpectedEndPos(uint16_t interchange_len) {
    return kHeaderBytesBeforeInterchange + interchange_len;
  }
};

}  // namespace

TEST_F(AsfVideoDegradableJPEGMediaTest_1566, SetsWidthHeightAndAdvancesPosition_WithZeroInterchange_1566) {
  // interchange_len = 0x0000
  const uint8_t width_b = 0x11;   // 0x11111111
  const uint8_t height_b = 0x22;  // 0x22222222
  const uint16_t interchange_len = 0x0000;

  auto io = std::make_unique<MemBasicIo>(BuildPayload(width_b, height_b, interchange_len, 0x77));
  io->open();

  TestableAsfVideo video(std::move(io));

  ASSERT_NO_THROW(video.DegradableJPEGMedia());

  // Verify observable metadata effects via public interface.
  EXPECT_EQ(video.xmpData()["Xmp.video.Width"].toInt64(0), 0x11111111);
  EXPECT_EQ(video.xmpData()["Xmp.video.Height"].toInt64(0), 0x22222222);

  // Verify observable I/O position via public io() API.
  EXPECT_EQ(static_cast<int64_t>(video.io().tell()), ExpectedEndPos(interchange_len));
}

TEST_F(AsfVideoDegradableJPEGMediaTest_1566, SetsWidthHeightAndSkipsInterchangeData_NonZeroInterchange_1566) {
  // Choose a symmetric WORD length: 0x0505 == 1285, but keep it small: 0x0202 == 514 also ok.
  // We'll use 0x0505 to ensure seek skip is non-trivial but still manageable.
  const uint8_t width_b = 0x33;   // 0x33333333
  const uint8_t height_b = 0x44;  // 0x44444444
  const uint16_t interchange_len = 0x0505;  // symmetric bytes

  auto io = std::make_unique<MemBasicIo>(BuildPayload(width_b, height_b, interchange_len, 0x99));
  io->open();

  TestableAsfVideo video(std::move(io));

  ASSERT_NO_THROW(video.DegradableJPEGMedia());

  EXPECT_EQ(video.xmpData()["Xmp.video.Width"].toInt64(0), 0x33333333);
  EXPECT_EQ(video.xmpData()["Xmp.video.Height"].toInt64(0), 0x44444444);

  EXPECT_EQ(static_cast<int64_t>(video.io().tell()), ExpectedEndPos(interchange_len));
}

TEST_F(AsfVideoDegradableJPEGMediaTest_1566, ThrowsWhenBufferTooSmallForWidth_1566) {
  // Provide less than 4 bytes so reading the first DWORD cannot complete.
  std::vector<Exiv2::byte> buf;
  AppendBytes(buf, {0x11, 0x11, 0x11});  // only 3 bytes

  auto io = std::make_unique<MemBasicIo>(std::move(buf));
  io->open();

  TestableAsfVideo video(std::move(io));

  // Error behavior is implementation-defined; verify it is observable as an exception.
  EXPECT_ANY_THROW(video.DegradableJPEGMedia());
}

TEST_F(AsfVideoDegradableJPEGMediaTest_1566, ThrowsWhenInterchangeLengthExceedsAvailableData_1566) {
  const uint8_t width_b = 0x55;   // 0x55555555
  const uint8_t height_b = 0x66;  // 0x66666666
  const uint16_t interchange_len = 0x0404;  // symmetric bytes (1028)

  // Build payload but truncate interchange data so skipping/reading cannot complete safely.
  auto full = BuildPayload(width_b, height_b, interchange_len, 0xAB);
  // Remove most of the interchange bytes (leave only 10 bytes).
  const size_t min_keep = static_cast<size_t>(AsfVideoDegradableJPEGMediaTest_1566::kHeaderBytesBeforeInterchange + 10);
  if (full.size() > min_keep) full.resize(min_keep);

  auto io = std::make_unique<MemBasicIo>(std::move(full));
  io->open();

  TestableAsfVideo video(std::move(io));

  EXPECT_ANY_THROW(video.DegradableJPEGMedia());
}