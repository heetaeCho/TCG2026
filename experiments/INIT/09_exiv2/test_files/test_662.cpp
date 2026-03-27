// File: test_isqtime_type_662.cpp
// Unit tests for Exiv2::isQTimeType(BasicIo&, bool)
// TEST_ID: 662

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

#include "exiv2/basicio.hpp"

namespace Exiv2 {
// The function is defined in ./TestProjects/exiv2/src/quicktimevideo.cpp
bool isQTimeType(BasicIo& iIo, bool advance);
}  // namespace Exiv2

namespace {

class FakeBasicIo final : public Exiv2::BasicIo {
 public:
  explicit FakeBasicIo(std::vector<Exiv2::byte> data) : data_(std::move(data)) {}

  size_t read(Exiv2::byte* buf, size_t rcount) override {
    if (force_error_) {
      error_ = 1;
      return 0;
    }
    const size_t avail = (pos_ < data_.size()) ? (data_.size() - pos_) : 0;
    const size_t n = (std::min)(rcount, avail);
    if (n > 0) {
      std::copy_n(data_.data() + pos_, n, buf);
      pos_ += n;
    }
    if (n < rcount) {
      eof_ = true;
    }
    return n;
  }

  int seek(int64_t offset, Position pos) override {
    ++seek_calls_;
    last_seek_offset_ = offset;
    last_seek_pos_ = pos;

    int64_t base = 0;
    if (pos == beg) {
      base = 0;
    } else if (pos == cur) {
      base = static_cast<int64_t>(pos_);
    } else {  // end
      base = static_cast<int64_t>(data_.size());
    }

    int64_t newPos = base + offset;
    if (newPos < 0) newPos = 0;
    const int64_t maxPos = static_cast<int64_t>(data_.size());
    if (newPos > maxPos) newPos = maxPos;

    pos_ = static_cast<size_t>(newPos);
    // Seeking resets EOF in typical IO semantics; good enough for our tests.
    eof_ = false;
    return 0;
  }

  const size_t tell() override { return pos_; }

  const int error() override { return error_; }
  const bool eof() override { return eof_; }

  // Helpers for assertions/controls
  void ForceErrorOnRead(bool v) { force_error_ = v; }

  int seek_calls() const { return seek_calls_; }
  int64_t last_seek_offset() const { return last_seek_offset_; }
  Position last_seek_pos() const { return last_seek_pos_; }

 private:
  std::vector<Exiv2::byte> data_;
  size_t pos_{0};

  bool eof_{false};
  int error_{0};
  bool force_error_{false};

  int seek_calls_{0};
  int64_t last_seek_offset_{0};
  Position last_seek_pos_{beg};
};

static std::vector<Exiv2::byte> Make12Bytes(const char a0[4], const char a4[4], const char a8[4]) {
  std::vector<Exiv2::byte> v;
  v.reserve(12);
  for (int i = 0; i < 4; ++i) v.push_back(static_cast<Exiv2::byte>(a0[i]));
  for (int i = 0; i < 4; ++i) v.push_back(static_cast<Exiv2::byte>(a4[i]));
  for (int i = 0; i < 4; ++i) v.push_back(static_cast<Exiv2::byte>(a8[i]));
  return v;
}

class IsQTimeTypeTest_662 : public ::testing::Test {};

}  // namespace

TEST_F(IsQTimeTypeTest_662, ReturnsTrueForKnownTagAndKnownFileType_662) {
  // tag at offset 4: "ftyp" (recognized by isQTimeType)
  // type at offset 8: "qt  " (present in qTimeFileType vocabulary)
  FakeBasicIo io(Make12Bytes("0000", "ftyp", "qt  "));

  const bool matched = Exiv2::isQTimeType(io, /*advance=*/true);

  EXPECT_TRUE(matched);
}

TEST_F(IsQTimeTypeTest_662, AdvanceTrueKeepsPositionAndDoesNotSeekWhenMatched_662) {
  FakeBasicIo io(Make12Bytes("0000", "ftyp", "qt  "));

  const bool matched = Exiv2::isQTimeType(io, /*advance=*/true);

  EXPECT_TRUE(matched);
  EXPECT_EQ(io.seek_calls(), 0) << "When advance=true and matched, function should not rewind";
  EXPECT_EQ(io.tell(), 12u) << "Read should have advanced position by 12 bytes";
}

TEST_F(IsQTimeTypeTest_662, AdvanceFalseRewindsToBeginningEvenWhenMatched_662) {
  FakeBasicIo io(Make12Bytes("0000", "ftyp", "qt  "));

  const bool matched = Exiv2::isQTimeType(io, /*advance=*/false);

  EXPECT_TRUE(matched);
  ASSERT_GE(io.seek_calls(), 1);
  EXPECT_EQ(io.last_seek_offset(), 0);
  EXPECT_EQ(io.last_seek_pos(), Exiv2::BasicIo::beg);
  EXPECT_EQ(io.tell(), 0u);
}

TEST_F(IsQTimeTypeTest_662, UnknownFileTypeReturnsFalseAndRewindsToBeginning_662) {
  // tag matches ("ftyp") but file type is not in vocabulary
  FakeBasicIo io(Make12Bytes("0000", "ftyp", "zzzz"));

  const bool matched = Exiv2::isQTimeType(io, /*advance=*/true);

  EXPECT_FALSE(matched);
  ASSERT_GE(io.seek_calls(), 1);
  EXPECT_EQ(io.last_seek_offset(), 0);
  EXPECT_EQ(io.last_seek_pos(), Exiv2::BasicIo::beg);
  EXPECT_EQ(io.tell(), 0u);
}

TEST_F(IsQTimeTypeTest_662, UnknownTagReturnsFalseAndRewindsToBeginning_662) {
  // tag at offset 4 does not match any known QuickTime atom tags
  FakeBasicIo io(Make12Bytes("0000", "NOPE", "qt  "));

  const bool matched = Exiv2::isQTimeType(io, /*advance=*/true);

  EXPECT_FALSE(matched);
  ASSERT_GE(io.seek_calls(), 1);
  EXPECT_EQ(io.last_seek_offset(), 0);
  EXPECT_EQ(io.last_seek_pos(), Exiv2::BasicIo::beg);
  EXPECT_EQ(io.tell(), 0u);
}

TEST_F(IsQTimeTypeTest_662, ReadErrorReturnsFalseWithoutSeeking_662) {
  FakeBasicIo io(Make12Bytes("0000", "ftyp", "qt  "));
  io.ForceErrorOnRead(true);

  const bool matched = Exiv2::isQTimeType(io, /*advance=*/true);

  EXPECT_FALSE(matched);
  EXPECT_EQ(io.seek_calls(), 0) << "On read error/eof, function returns early and should not seek";
}

TEST_F(IsQTimeTypeTest_662, EofBefore12BytesReturnsFalseWithoutSeeking_662) {
  // Only 11 bytes available -> eof() becomes true after read attempt.
  std::vector<Exiv2::byte> shortData = Make12Bytes("0000", "ftyp", "qt  ");
  shortData.pop_back();  // 11 bytes
  FakeBasicIo io(std::move(shortData));

  const bool matched = Exiv2::isQTimeType(io, /*advance=*/true);

  EXPECT_FALSE(matched);
  EXPECT_EQ(io.seek_calls(), 0) << "On eof, function returns early and should not seek";
}