// File: test_isAsfType_1574.cpp
#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "exiv2/basicio.hpp"

namespace Exiv2 {
// Function under test (implemented in the production codebase).
bool isAsfType(BasicIo& iIo, bool advance);
}  // namespace Exiv2

namespace {

// Minimal controllable BasicIo test double to observe interactions (read/seek/error/eof).
class TestBasicIo final : public Exiv2::BasicIo {
 public:
  explicit TestBasicIo(std::vector<Exiv2::byte> data) : data_(std::move(data)) {}

  // Controls
  void set_error_after_read(int err) { error_after_read_ = err; }
  void set_force_eof_after_read(bool eof) { force_eof_after_read_ = eof; }

  // Observability
  int seek_call_count() const { return seek_call_count_; }
  int64_t last_seek_offset() const { return last_seek_offset_; }
  Exiv2::BasicIo::Position last_seek_pos() const { return last_seek_pos_; }
  size_t read_call_count() const { return read_call_count_; }
  size_t last_read_count() const { return last_read_count_; }
  size_t tell_pos() const { return pos_; }

  // BasicIo overrides used by Exiv2::isAsfType
  size_t read(Exiv2::byte* buf, size_t rcount) override {
    ++read_call_count_;
    last_read_count_ = rcount;

    const size_t avail = (pos_ < data_.size()) ? (data_.size() - pos_) : 0;
    const size_t n = (rcount <= avail) ? rcount : avail;

    for (size_t i = 0; i < n; ++i) {
      buf[i] = data_[pos_ + i];
    }
    // If short read, fill remainder deterministically (not required by the interface, but safe for tests).
    for (size_t i = n; i < rcount; ++i) {
      buf[i] = 0;
    }

    pos_ += n;

    // Apply post-read flags so Exiv2::isAsfType observes them via error()/eof().
    if (error_after_read_ != 0) {
      error_ = error_after_read_;
    }
    if (force_eof_after_read_) {
      eof_ = true;
    }

    return n;
  }

  int seek(int64_t offset, Position pos) override {
    ++seek_call_count_;
    last_seek_offset_ = offset;
    last_seek_pos_ = pos;

    // Minimal semantics for tests:
    // - Only offset=0,beg is needed by isAsfType in the provided snippet.
    if (pos == Position::beg && offset == 0) {
      pos_ = 0;
      eof_ = false;
      return 0;
    }

    // For any other seek requests, do a conservative best-effort without throwing.
    int64_t newPos = 0;
    if (pos == Position::beg) newPos = offset;
    if (pos == Position::cur) newPos = static_cast<int64_t>(pos_) + offset;
    if (pos == Position::end) newPos = static_cast<int64_t>(data_.size()) + offset;

    if (newPos < 0) newPos = 0;
    if (static_cast<size_t>(newPos) > data_.size()) newPos = static_cast<int64_t>(data_.size());

    pos_ = static_cast<size_t>(newPos);
    eof_ = false;
    return 0;
  }

  const int error() override { return error_; }
  const bool eof() override { return eof_; }
  const size_t tell() override { return pos_; }

 private:
  std::vector<Exiv2::byte> data_;
  size_t pos_{0};

  // flags observed by isAsfType
  int error_{0};
  bool eof_{false};

  // controls
  int error_after_read_{0};
  bool force_eof_after_read_{false};

  // observability
  int seek_call_count_{0};
  int64_t last_seek_offset_{0};
  Exiv2::BasicIo::Position last_seek_pos_{Exiv2::BasicIo::beg};
  size_t read_call_count_{0};
  size_t last_read_count_{0};
};

constexpr size_t kGuidSize = 16;

// ASF header object GUID bytes (75B22630-668E-11CF-A6D9-00AA0062CE6C)
// in file byte order.
std::vector<Exiv2::byte> MakeAsfGuidPrefix() {
  return std::vector<Exiv2::byte>{
      0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
      0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C,
  };
}

std::vector<Exiv2::byte> MakeNonAsfPrefix() {
  return std::vector<Exiv2::byte>{
      0x00, 0x01, 0x02, 0x03, 0x10, 0x20, 0x30, 0x40,
      0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC,
  };
}

class IsAsfTypeTest_1574 : public ::testing::Test {};

}  // namespace

TEST_F(IsAsfTypeTest_1574, ReturnsFalseWhenIoErrorAfterRead_1574) {
  TestBasicIo io(MakeAsfGuidPrefix());
  io.set_error_after_read(1);

  const bool matched = Exiv2::isAsfType(io, /*advance=*/true);

  EXPECT_FALSE(matched);
  EXPECT_EQ(io.read_call_count(), 1u);
  EXPECT_EQ(io.last_read_count(), kGuidSize);
  // Early return on error/eof: seek should not be called.
  EXPECT_EQ(io.seek_call_count(), 0);
}

TEST_F(IsAsfTypeTest_1574, ReturnsFalseWhenIoEofAfterRead_1574) {
  TestBasicIo io(MakeAsfGuidPrefix());
  io.set_force_eof_after_read(true);

  const bool matched = Exiv2::isAsfType(io, /*advance=*/true);

  EXPECT_FALSE(matched);
  EXPECT_EQ(io.read_call_count(), 1u);
  EXPECT_EQ(io.last_read_count(), kGuidSize);
  // Early return on error/eof: seek should not be called.
  EXPECT_EQ(io.seek_call_count(), 0);
}

TEST_F(IsAsfTypeTest_1574, MatchedAdvanceFalseSeeksBackToBeginning_1574) {
  TestBasicIo io(MakeAsfGuidPrefix());

  const bool matched = Exiv2::isAsfType(io, /*advance=*/false);

  EXPECT_TRUE(matched);
  EXPECT_EQ(io.read_call_count(), 1u);
  EXPECT_EQ(io.last_read_count(), kGuidSize);

  // When advance is false, it should seek back regardless of match.
  ASSERT_EQ(io.seek_call_count(), 1);
  EXPECT_EQ(io.last_seek_offset(), 0);
  EXPECT_EQ(io.last_seek_pos(), Exiv2::BasicIo::beg);
  EXPECT_EQ(io.tell_pos(), 0u);
}

TEST_F(IsAsfTypeTest_1574, NotMatchedAdvanceTrueSeeksBackToBeginning_1574) {
  TestBasicIo io(MakeNonAsfPrefix());

  const bool matched = Exiv2::isAsfType(io, /*advance=*/true);

  EXPECT_FALSE(matched);
  EXPECT_EQ(io.read_call_count(), 1u);
  EXPECT_EQ(io.last_read_count(), kGuidSize);

  // When not matched, it should seek back even if advance is true.
  ASSERT_EQ(io.seek_call_count(), 1);
  EXPECT_EQ(io.last_seek_offset(), 0);
  EXPECT_EQ(io.last_seek_pos(), Exiv2::BasicIo::beg);
  EXPECT_EQ(io.tell_pos(), 0u);
}

TEST_F(IsAsfTypeTest_1574, MatchedAdvanceTrueDoesNotSeekAndAdvancesPosition_1574) {
  TestBasicIo io(MakeAsfGuidPrefix());

  const bool matched = Exiv2::isAsfType(io, /*advance=*/true);

  EXPECT_TRUE(matched);
  EXPECT_EQ(io.read_call_count(), 1u);
  EXPECT_EQ(io.last_read_count(), kGuidSize);

  // When advance is true and matched, it should not seek back.
  EXPECT_EQ(io.seek_call_count(), 0);
  EXPECT_EQ(io.tell_pos(), kGuidSize);
}