// ============================================================================
// File: bmffimage_parseTiff_test.cpp
// Test ID: 1196
// Unit tests for Exiv2::BmffImage::parseTiff(uint32_t, uint64_t, uint64_t)
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "exiv2/bmffimage.hpp"
#include "exiv2/basicio.hpp"

namespace {

using Exiv2::BasicIo;
using Exiv2::BmffImage;
using Exiv2::byte;

class FakeBasicIo final : public BasicIo {
 public:
  struct Call {
    enum Kind { kTell, kSize, kSeek, kRead } kind;
    int64_t offset = 0;
    BasicIo::Position pos = BasicIo::beg;
    size_t count = 0;
  };

  explicit FakeBasicIo(std::vector<byte> bytes) : data_(std::move(bytes)) {}

  // Configure to simulate short reads (return less than requested).
  // If 0, read returns full requested (up to EOF).
  void set_max_return_per_read(size_t n) { max_return_per_read_ = n; }

  const std::vector<Call>& calls() const { return calls_; }
  void clear_calls() { calls_.clear(); }

  // ---- BasicIo overrides used by parseTiff ----
  size_t read(byte* buf, size_t rcount) override {
    calls_.push_back(Call{Call::kRead, 0, BasicIo::beg, rcount});

    if (!buf) return 0;

    if (pos_ > data_.size()) return 0;

    size_t available = data_.size() - pos_;
    size_t to_copy = (rcount < available) ? rcount : available;

    if (max_return_per_read_ != 0 && to_copy > max_return_per_read_) {
      to_copy = max_return_per_read_;
    }

    if (to_copy > 0) {
      std::memcpy(buf, data_.data() + pos_, to_copy);
      pos_ += to_copy;
    }
    return to_copy;
  }

  int seek(int64_t offset, Position pos) override {
    calls_.push_back(Call{Call::kSeek, offset, pos, 0});

    int64_t base = 0;
    if (pos == BasicIo::beg) {
      base = 0;
    } else if (pos == BasicIo::cur) {
      base = static_cast<int64_t>(pos_);
    } else {  // end
      base = static_cast<int64_t>(data_.size());
    }

    int64_t np = base + offset;
    if (np < 0) return 1;  // emulate failure
    pos_ = static_cast<size_t>(np);
    return 0;
  }

  const size_t tell() override {
    calls_.push_back(Call{Call::kTell, 0, BasicIo::beg, 0});
    return pos_;
  }

  const size_t size() override {
    calls_.push_back(Call{Call::kSize, 0, BasicIo::beg, 0});
    return data_.size();
  }

 private:
  std::vector<byte> data_;
  size_t pos_ = 0;
  size_t max_return_per_read_ = 0;
  std::vector<Call> calls_;
};

class BmffImageParseTiffTest_1196 : public ::testing::Test {
 protected:
  static std::unique_ptr<BmffImage> MakeImage(std::unique_ptr<FakeBasicIo> io,
                                              size_t max_box_depth = 10,
                                              FakeBasicIo** raw_io_out = nullptr) {
    FakeBasicIo* raw = io.get();
    auto img = std::make_unique<BmffImage>(std::unique_ptr<BasicIo>(std::move(io)),
                                          /*create=*/false, max_box_depth);
    if (raw_io_out) *raw_io_out = raw;
    return img;
  }

  static size_t CountCalls(const FakeBasicIo& io, FakeBasicIo::Call::Kind k) {
    size_t n = 0;
    for (const auto& c : io.calls()) {
      if (c.kind == k) ++n;
    }
    return n;
  }

  static const FakeBasicIo::Call* FindLastSeek(const FakeBasicIo& io) {
    const FakeBasicIo::Call* last = nullptr;
    for (const auto& c : io.calls()) {
      if (c.kind == FakeBasicIo::Call::kSeek) last = &c;
    }
    return last;
  }
};

// --- Normal operation: restores original position (seek back to restore) ---
TEST_F(BmffImageParseTiffTest_1196, RestoresOriginalIoPositionAfterParse_1196) {
  // Arrange: make data large enough and include "II" so TIFF marker can be found.
  std::vector<byte> bytes(64, static_cast<byte>(0));
  bytes[0] = static_cast<byte>('I');
  bytes[1] = static_cast<byte>('I');

  FakeBasicIo* raw = nullptr;
  auto image = MakeImage(std::make_unique<FakeBasicIo>(bytes), /*max_box_depth=*/10, &raw);
  ASSERT_NE(raw, nullptr);

  // Move position away from 0 so we can verify restore behavior.
  ASSERT_EQ(raw->seek(10, BasicIo::beg), 0);
  raw->clear_calls();

  // Act
  EXPECT_NO_THROW(image->parseTiff(/*root_tag=*/0x1234u, /*length=*/32u, /*start=*/0u));

  // Assert: should have sought to start and then restored to prior tell().
  // We avoid assuming exact number of seeks, but require that the last seek is restore->beg.
  ASSERT_GE(CountCalls(*raw, FakeBasicIo::Call::kTell), 1u);
  ASSERT_GE(CountCalls(*raw, FakeBasicIo::Call::kSeek), 2u);

  const FakeBasicIo::Call* last_seek = FindLastSeek(*raw);
  ASSERT_NE(last_seek, nullptr);
  EXPECT_EQ(last_seek->pos, BasicIo::beg);
  EXPECT_EQ(last_seek->offset, 10);  // restore position
}

// --- Normal operation: reads expected number of bytes when length > 8 ---
TEST_F(BmffImageParseTiffTest_1196, ReadsExactLengthWhenLengthGreaterThanEight_1196) {
  std::vector<byte> bytes(128, static_cast<byte>(0));
  bytes[5] = static_cast<byte>('M');
  bytes[6] = static_cast<byte>('M');  // marker somewhere in buffer

  FakeBasicIo* raw = nullptr;
  auto image = MakeImage(std::make_unique<FakeBasicIo>(bytes), 10, &raw);
  ASSERT_NE(raw, nullptr);

  raw->clear_calls();

  const uint64_t start = 7;
  const uint64_t length = 50;

  EXPECT_NO_THROW(image->parseTiff(/*root_tag=*/0x8765u, length, start));

  // At least one read() call should have occurred with rcount == length.
  bool saw_expected_read = false;
  for (const auto& c : raw->calls()) {
    if (c.kind == FakeBasicIo::Call::kRead && c.count == static_cast<size_t>(length)) {
      saw_expected_read = true;
      break;
    }
  }
  EXPECT_TRUE(saw_expected_read);
}

// --- Boundary: length == 8 -> must not call read() because exif.size() > 8 is required ---
TEST_F(BmffImageParseTiffTest_1196, DoesNotReadWhenLengthIsEightOrLess_1196) {
  std::vector<byte> bytes(64, static_cast<byte>(0));
  FakeBasicIo* raw = nullptr;
  auto image = MakeImage(std::make_unique<FakeBasicIo>(bytes), 10, &raw);
  ASSERT_NE(raw, nullptr);

  raw->clear_calls();

  EXPECT_NO_THROW(image->parseTiff(/*root_tag=*/0x1u, /*length=*/8u, /*start=*/0u));

  // Should not read any bytes when length <= 8 (condition is exif.size() > 8).
  EXPECT_EQ(CountCalls(*raw, FakeBasicIo::Call::kRead), 0u);

  // Still should restore position (tell + at least one seek to restore).
  EXPECT_GE(CountCalls(*raw, FakeBasicIo::Call::kTell), 1u);
  EXPECT_GE(CountCalls(*raw, FakeBasicIo::Call::kSeek), 1u);
}

// --- Boundary: short read -> read() called but decode path not taken; must still restore ---
TEST_F(BmffImageParseTiffTest_1196, RestoresPositionEvenIfReadReturnsShort_1196) {
  std::vector<byte> bytes(128, static_cast<byte>(0));
  // Put marker so if full read happened, decode could be attempted; but we force short read.
  bytes[0] = static_cast<byte>('I');
  bytes[1] = static_cast<byte>('I');

  auto fake = std::make_unique<FakeBasicIo>(bytes);
  fake->set_max_return_per_read(4);  // force short read
  FakeBasicIo* raw = nullptr;
  auto image = MakeImage(std::move(fake), 10, &raw);
  ASSERT_NE(raw, nullptr);

  ASSERT_EQ(raw->seek(20, BasicIo::beg), 0);
  raw->clear_calls();

  EXPECT_NO_THROW(image->parseTiff(/*root_tag=*/0x2u, /*length=*/32u, /*start=*/0u));

  const FakeBasicIo::Call* last_seek = FindLastSeek(*raw);
  ASSERT_NE(last_seek, nullptr);
  EXPECT_EQ(last_seek->pos, BasicIo::beg);
  EXPECT_EQ(last_seek->offset, 20);
  EXPECT_GE(CountCalls(*raw, FakeBasicIo::Call::kRead), 1u);
}

// --- Error: start > io size -> enforce should throw (observable as exception) ---
TEST_F(BmffImageParseTiffTest_1196, ThrowsWhenStartIsBeyondIoSize_1196) {
  std::vector<byte> bytes(10, static_cast<byte>(0));
  auto image = MakeImage(std::make_unique<FakeBasicIo>(bytes));

  EXPECT_ANY_THROW(image->parseTiff(/*root_tag=*/0x1u, /*length=*/1u, /*start=*/11u));
}

// --- Error: length > (io size - start) -> enforce should throw ---
TEST_F(BmffImageParseTiffTest_1196, ThrowsWhenLengthExceedsRemainingBytes_1196) {
  std::vector<byte> bytes(10, static_cast<byte>(0));
  auto image = MakeImage(std::make_unique<FakeBasicIo>(bytes));

  // start = 8 leaves only 2 bytes; request length 3 -> should fail
  EXPECT_ANY_THROW(image->parseTiff(/*root_tag=*/0x1u, /*length=*/3u, /*start=*/8u));
}

// --- Error: start > int64_t max -> enforce should throw ---
TEST_F(BmffImageParseTiffTest_1196, ThrowsWhenStartExceedsInt64Max_1196) {
  std::vector<byte> bytes(1, static_cast<byte>(0));
  auto image = MakeImage(std::make_unique<FakeBasicIo>(bytes));

  const uint64_t too_big_start =
      static_cast<uint64_t>(std::numeric_limits<int64_t>::max()) + 1ull;

  EXPECT_ANY_THROW(image->parseTiff(/*root_tag=*/0x1u, /*length=*/0u, /*start=*/too_big_start));
}

// --- Error: length > size_t max -> enforce should throw (only meaningful on narrower size_t) ---
TEST_F(BmffImageParseTiffTest_1196, ThrowsWhenLengthExceedsSizeTMax_1196) {
  std::vector<byte> bytes(16, static_cast<byte>(0));
  auto image = MakeImage(std::make_unique<FakeBasicIo>(bytes));

  const uint64_t too_big_length =
      static_cast<uint64_t>(std::numeric_limits<size_t>::max()) + 1ull;

  // start must be within file size checks first; start=0 is fine, then length check should trip.
  EXPECT_ANY_THROW(image->parseTiff(/*root_tag=*/0x1u, /*length=*/too_big_length, /*start=*/0u));
}

}  // namespace