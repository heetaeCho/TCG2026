// File: test_riffvideo_headerreader_2152.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/riffvideo.hpp"

namespace {

class FakeBasicIo : public Exiv2::BasicIo {
 public:
  explicit FakeBasicIo(std::vector<Exiv2::byte> data, std::size_t initial_pos = 0)
      : data_(std::move(data)), pos_(initial_pos) {}

  // Minimal surface used by RiffVideo::HeaderReader's constructor path.
  const size_t tell() override { return pos_; }
  const size_t size() override { return data_.size(); }

  // HeaderReader (via internal helpers) is expected to read bytes from the stream.
  size_t read(Exiv2::byte* buf, size_t rcount) override {
    if (buf == nullptr || rcount == 0) return 0;
    const std::size_t avail = (pos_ < data_.size()) ? (data_.size() - pos_) : 0;
    const std::size_t n = (rcount < avail) ? rcount : avail;
    for (std::size_t i = 0; i < n; ++i) {
      buf[i] = data_[pos_ + i];
    }
    pos_ += n;
    return n;
  }

  int seek(int64_t offset, Exiv2::Position pos) override {
    std::size_t base = 0;
    switch (pos) {
      case Exiv2::beg:
        base = 0;
        break;
      case Exiv2::cur:
        base = pos_;
        break;
      case Exiv2::end:
        base = data_.size();
        break;
      default:
        base = pos_;
        break;
    }

    // Keep it simple: clamp to [0, size].
    int64_t target_signed = static_cast<int64_t>(base) + offset;
    if (target_signed < 0) {
      pos_ = 0;
    } else {
      std::size_t target = static_cast<std::size_t>(target_signed);
      pos_ = (target > data_.size()) ? data_.size() : target;
    }
    return 0;
  }

 private:
  std::vector<Exiv2::byte> data_;
  std::size_t pos_{0};
};

static std::vector<Exiv2::byte> MakeBytes(std::size_t n, Exiv2::byte fill = 0) {
  return std::vector<Exiv2::byte>(n, fill);
}

}  // namespace

// NOTE: We treat HeaderReader as a black box. These tests only validate observable behavior:
// construction success/failure and that accessors are callable after successful construction.

class RiffVideoHeaderReaderTest_2152 : public ::testing::Test {};

// The TEST_ID is 2152
TEST_F(RiffVideoHeaderReaderTest_2152, CtorThrowsWhenLessThanMinimumBytesRemaining_2152) {
  // Condition (from the provided snippet) requires: io->size() > io->tell() + DWORD + DWORD.
  // Here: size=7, tell=0 => 7 > 8 is false => should throw.
  auto io = Exiv2::BasicIo::UniquePtr(new FakeBasicIo(MakeBytes(7), /*initial_pos=*/0));
  EXPECT_ANY_THROW({ Exiv2::RiffVideo::HeaderReader reader(io); });
}

// The TEST_ID is 2152
TEST_F(RiffVideoHeaderReaderTest_2152, CtorThrowsWhenExactlyMinimumBytesRemaining_2152) {
  // size=8, tell=0 => 8 > 8 is false => should throw.
  auto io = Exiv2::BasicIo::UniquePtr(new FakeBasicIo(MakeBytes(8), /*initial_pos=*/0));
  EXPECT_ANY_THROW({ Exiv2::RiffVideo::HeaderReader reader(io); });
}

// The TEST_ID is 2152
TEST_F(RiffVideoHeaderReaderTest_2152, CtorDoesNotThrowWhenOneMoreThanMinimumBytesRemaining_2152) {
  // size=9, tell=0 => 9 > 8 is true => constructor should not fail the precondition.
  // Provide at least 8 bytes that internal reading helpers might consume.
  auto bytes = MakeBytes(9);
  bytes[0] = 'R';
  bytes[1] = 'I';
  bytes[2] = 'F';
  bytes[3] = 'F';
  // Next 4 bytes remain 0; extra trailing byte remains 0.
  auto io = Exiv2::BasicIo::UniquePtr(new FakeBasicIo(std::move(bytes), /*initial_pos=*/0));

  EXPECT_NO_THROW({
    Exiv2::RiffVideo::HeaderReader reader(io);

    // Accessors should be callable after successful construction.
    const std::string id1 = reader.getId();
    const std::string id2 = reader.getId();
    const uint64_t s1 = reader.getSize();
    const uint64_t s2 = reader.getSize();

    // Basic consistency (no assumptions about parsing specifics).
    EXPECT_EQ(id1, id2);
    EXPECT_EQ(s1, s2);
  });
}

// The TEST_ID is 2152
TEST_F(RiffVideoHeaderReaderTest_2152, CtorRespectsTellOffsetAndThrowsWhenNotEnoughBytesFromCurrentPos_2152) {
  // size=10, tell=2 => 10 > 2+8 => 10 > 10 is false => should throw.
  auto io = Exiv2::BasicIo::UniquePtr(new FakeBasicIo(MakeBytes(10), /*initial_pos=*/2));
  EXPECT_ANY_THROW({ Exiv2::RiffVideo::HeaderReader reader(io); });
}

// The TEST_ID is 2152
TEST_F(RiffVideoHeaderReaderTest_2152, CtorRespectsTellOffsetAndSucceedsWhenEnoughBytesFromCurrentPos_2152) {
  // size=10, tell=1 => 10 > 1+8 => 10 > 9 is true => should not throw precondition.
  // Ensure there are enough bytes after position 1 for any internal reads.
  auto bytes = MakeBytes(10);
  // Put a recognizable 4-byte tag starting at current position (1).
  bytes[1] = 'T';
  bytes[2] = 'E';
  bytes[3] = 'S';
  bytes[4] = 'T';
  auto io = Exiv2::BasicIo::UniquePtr(new FakeBasicIo(std::move(bytes), /*initial_pos=*/1));

  EXPECT_NO_THROW({
    Exiv2::RiffVideo::HeaderReader reader(io);

    // Accessors callable and stable.
    EXPECT_EQ(reader.getId(), reader.getId());
    EXPECT_EQ(reader.getSize(), reader.getSize());
  });
}