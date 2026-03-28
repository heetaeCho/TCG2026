// TEST_ID 1564
// File: test_asfvideo_decodeheader_1564.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "exiv2/asfvideo.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/types.hpp"
#include "exiv2/error.hpp"

namespace {

// A small BasicIo test double that drives BasicIo::readOrThrow/seekOrThrow through
// overridden virtual read()/seek()/tell().
class FakeBasicIo final : public Exiv2::BasicIo {
 public:
  explicit FakeBasicIo(std::vector<Exiv2::byte> bytes) : data_(std::move(bytes)) {}

  // Controls
  void setSeekFail(bool v) { seekFail_ = v; }
  void setOpen(bool v) { open_ = v; }

  // Observability
  int64_t lastSeekOffset() const { return lastSeekOffset_; }
  Exiv2::BasicIo::Position lastSeekPos() const { return lastSeekPos_; }
  bool seekWasCalled() const { return seekCalled_; }

  // BasicIo overrides
  int open() override {
    open_ = true;
    return 0;
  }
  int close() override {
    open_ = false;
    return 0;
  }

  size_t read(Exiv2::byte* buf, size_t rcount) override {
    const size_t avail = (pos_ < data_.size()) ? (data_.size() - pos_) : 0U;
    const size_t n = (rcount < avail) ? rcount : avail;
    if (n > 0) {
      std::memcpy(buf, data_.data() + pos_, n);
      pos_ += n;
    }
    return n;
  }

  int seek(int64_t offset, Position pos) override {
    seekCalled_ = true;
    lastSeekOffset_ = offset;
    lastSeekPos_ = pos;

    if (seekFail_) return -1;

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
        return -1;
    }

    const int64_t newPos = base + offset;
    if (newPos < 0) return -1;
    if (static_cast<size_t>(newPos) > data_.size()) return -1;

    pos_ = static_cast<size_t>(newPos);
    return 0;
  }

  const size_t tell() override { return pos_; }
  const size_t size() override { return data_.size(); }
  const bool isopen() override { return open_; }
  const int error() override { return 0; }
  const bool eof() override { return pos_ >= data_.size(); }
  const std::string& path() override { return path_; }

 private:
  std::vector<Exiv2::byte> data_;
  size_t pos_{0};

  bool open_{true};
  bool seekFail_{false};

  bool seekCalled_{false};
  int64_t lastSeekOffset_{0};
  Exiv2::BasicIo::Position lastSeekPos_{Exiv2::BasicIo::beg};

  std::string path_;
};

// Expose protected decodeHeader() for testing without touching internals.
class TestableAsfVideo final : public Exiv2::AsfVideo {
 public:
  explicit TestableAsfVideo(std::unique_ptr<Exiv2::BasicIo> io) : Exiv2::AsfVideo(std::move(io)) {}
  void decodeHeaderPublic() { decodeHeader(); }
};

static std::vector<Exiv2::byte> ULongLE(uint32_t v) {
  return {
      static_cast<Exiv2::byte>(v & 0xFF),
      static_cast<Exiv2::byte>((v >> 8) & 0xFF),
      static_cast<Exiv2::byte>((v >> 16) & 0xFF),
      static_cast<Exiv2::byte>((v >> 24) & 0xFF),
  };
}

}  // namespace

class AsfVideoDecodeHeaderTest_1564 : public ::testing::Test {};

TEST_F(AsfVideoDecodeHeaderTest_1564, ZeroHeaders_SeeksPastReservedTags_1564) {
  // nb_headers = 0 (little-endian), no further data needed because loop won't run.
  std::vector<Exiv2::byte> bytes = ULongLE(0);
  auto* rawIo = new FakeBasicIo(bytes);
  std::unique_ptr<Exiv2::BasicIo> io(rawIo);

  TestableAsfVideo video(std::move(io));

  EXPECT_NO_THROW(video.decodeHeaderPublic());

  // After reading 4 bytes, decodeHeader seeks to tell() + (BYTE*2) from beg => 4 + 2 = 6.
  EXPECT_TRUE(rawIo->seekWasCalled());
  EXPECT_EQ(rawIo->lastSeekPos(), Exiv2::BasicIo::beg);
  EXPECT_EQ(rawIo->lastSeekOffset(), 6);
  EXPECT_EQ(rawIo->tell(), static_cast<size_t>(6));
}

TEST_F(AsfVideoDecodeHeaderTest_1564, ReadTooShort_Throws_1564) {
  // Provide fewer than DWORD (4) bytes so BasicIo::readOrThrow should fail.
  std::vector<Exiv2::byte> bytes = {0x00, 0x00, 0x00};  // 3 bytes only
  auto io = std::make_unique<FakeBasicIo>(bytes);
  TestableAsfVideo video(std::move(io));

  EXPECT_ANY_THROW(video.decodeHeaderPublic());
}

TEST_F(AsfVideoDecodeHeaderTest_1564, SeekFailure_Throws_1564) {
  // nb_headers = 0 so we only exercise the reserved-tags seek path.
  std::vector<Exiv2::byte> bytes = ULongLE(0);
  auto* rawIo = new FakeBasicIo(bytes);
  rawIo->setSeekFail(true);
  std::unique_ptr<Exiv2::BasicIo> io(rawIo);

  TestableAsfVideo video(std::move(io));

  EXPECT_ANY_THROW(video.decodeHeaderPublic());

  EXPECT_TRUE(rawIo->seekWasCalled());
  EXPECT_EQ(rawIo->lastSeekPos(), Exiv2::BasicIo::beg);
  // Even though seek fails, the requested offset should still be the computed one.
  EXPECT_EQ(rawIo->lastSeekOffset(), 6);
}

TEST_F(AsfVideoDecodeHeaderTest_1564, NbHeadersAtUint32Max_ThrowsCorruptedMetadata_1564) {
  // decodeHeader enforces nb_headers < uint32_t max. If equal, it should throw.
  const uint32_t kMax = std::numeric_limits<uint32_t>::max();
  std::vector<Exiv2::byte> bytes = ULongLE(kMax);

  auto io = std::make_unique<FakeBasicIo>(bytes);
  TestableAsfVideo video(std::move(io));

  EXPECT_ANY_THROW(video.decodeHeaderPublic());
}