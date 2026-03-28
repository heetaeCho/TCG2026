// TEST_ID 2199
// Unit tests for Exiv2::AsfVideo::HeaderReader
//
// File under test: ./TestProjects/exiv2/src/asfvideo.cpp
//
// Constraints honored:
// - Treat implementation as black box (test only via public interface / observable effects)
// - No private-state access
// - Use test doubles only for external dependency (BasicIo)

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "exiv2/asfvideo.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/types.hpp"
#include "exiv2/error.hpp"

namespace {

class VectorBasicIo final : public Exiv2::BasicIo {
 public:
  explicit VectorBasicIo(std::vector<Exiv2::byte> data, size_t start_pos = 0, bool short_read = false)
      : data_(std::move(data)), pos_(start_pos), short_read_(short_read) {}

  size_t read(Exiv2::byte* buf, size_t rcount) override {
    if (!buf || rcount == 0) return 0;

    // Optional behavior to force readOrThrow() to throw (by returning too few bytes).
    size_t requested = rcount;
    if (short_read_ && rcount > 0) {
      requested = rcount - 1;  // always short by 1 when possible
    }

    const size_t avail = (pos_ < data_.size()) ? (data_.size() - pos_) : 0;
    const size_t n = std::min(requested, avail);
    if (n > 0) {
      std::copy_n(data_.data() + pos_, n, buf);
      pos_ += n;
    }
    return n;
  }

  int seek(int64_t offset, Exiv2::Position pos) override {
    // Minimal, sufficient implementation for these tests.
    int64_t base = 0;
    switch (pos) {
      case Exiv2::Position::beg:
        base = 0;
        break;
      case Exiv2::Position::cur:
        base = static_cast<int64_t>(pos_);
        break;
      case Exiv2::Position::end:
        base = static_cast<int64_t>(data_.size());
        break;
      default:
        base = 0;
        break;
    }

    const int64_t target = base + offset;
    if (target < 0) return -1;
    pos_ = static_cast<size_t>(target);
    return 0;
  }

  const size_t tell() override { return pos_; }
  const size_t size() override { return data_.size(); }

 private:
  std::vector<Exiv2::byte> data_;
  size_t pos_{0};
  bool short_read_{false};
};

static std::vector<Exiv2::byte> MakeBytes(size_t n, Exiv2::byte value) {
  return std::vector<Exiv2::byte>(n, value);
}

static void Append(std::vector<Exiv2::byte>& dst, const std::vector<Exiv2::byte>& src) {
  dst.insert(dst.end(), src.begin(), src.end());
}

}  // namespace

class HeaderReaderTest_2199 : public ::testing::Test {};

// Normal-ish: enough bytes, GUID gets read, and remaining size computed when size_ >= GUID + QWORD.
TEST_F(HeaderReaderTest_2199, ReadsGuidAndComputesRemainingWhenEnoughData_2199) {
  // Build buffer: [GUID(16 bytes)] [QWORD(8 bytes)]
  // Use 8 identical bytes for size so endianness does not affect the numeric value.
  // 0x01 repeated -> value is 0x0101010101010101 in both little/big-endian interpretations.
  std::vector<Exiv2::byte> buf;
  std::vector<Exiv2::byte> guid(Exiv2::GUID);
  for (size_t i = 0; i < guid.size(); ++i) guid[i] = static_cast<Exiv2::byte>(i);

  Append(buf, guid);
  Append(buf, MakeBytes(Exiv2::QWORD, static_cast<Exiv2::byte>(0x01)));

  auto io = std::make_unique<VectorBasicIo>(buf, /*start_pos=*/0);

  Exiv2::AsfVideo::HeaderReader hr(io);

  // GUID should be available via getId().
  ASSERT_EQ(hr.getId().size(), Exiv2::GUID);
  EXPECT_EQ(hr.getId().cmpBytes(0, guid.data(), guid.size()), 0);

  // tell() should have advanced by GUID + QWORD due to the reads done in the ctor.
  EXPECT_EQ(io->tell(), Exiv2::GUID + Exiv2::QWORD);

  // With repeated 0x01 bytes, size should be that same endian-invariant value.
  const uint64_t expected_size = 0x0101010101010101ULL;
  EXPECT_EQ(hr.getSize(), expected_size);

  // remaining_size_ should be size - GUID - QWORD when size >= GUID + QWORD.
  const uint64_t expected_remaining = expected_size - static_cast<uint64_t>(Exiv2::GUID + Exiv2::QWORD);
  EXPECT_EQ(hr.getRemainingSize(), expected_remaining);
}

// Boundary: insufficient bytes (size < tell + GUID + QWORD) -> ctor should not read and sizes remain defaults.
TEST_F(HeaderReaderTest_2199, DoesNothingWhenNotEnoughBytesAvailable_2199) {
  // Provide fewer than GUID + QWORD bytes.
  std::vector<Exiv2::byte> buf = MakeBytes(Exiv2::GUID + Exiv2::QWORD - 1, static_cast<Exiv2::byte>(0xAB));
  auto io = std::make_unique<VectorBasicIo>(buf, /*start_pos=*/0);

  Exiv2::AsfVideo::HeaderReader hr(io);

  // No reads should have occurred (tell stays 0).
  EXPECT_EQ(io->tell(), 0u);

  // Defaults are observable through getters.
  EXPECT_EQ(hr.getSize(), 0u);
  EXPECT_EQ(hr.getRemainingSize(), 0u);

  // Id buffer is constructed with GUID size (do not assert contents).
  EXPECT_EQ(hr.getId().size(), Exiv2::GUID);
}

// Boundary: exactly GUID + QWORD bytes available; size field all zeros -> size=0 (endian-invariant), remaining stays 0.
TEST_F(HeaderReaderTest_2199, HandlesExactMinimumBytesWithZeroSizeField_2199) {
  std::vector<Exiv2::byte> buf;
  std::vector<Exiv2::byte> guid(Exiv2::GUID);
  for (size_t i = 0; i < guid.size(); ++i) guid[i] = static_cast<Exiv2::byte>(0xF0 + i);

  Append(buf, guid);
  Append(buf, MakeBytes(Exiv2::QWORD, static_cast<Exiv2::byte>(0x00)));

  auto io = std::make_unique<VectorBasicIo>(buf, /*start_pos=*/0);

  Exiv2::AsfVideo::HeaderReader hr(io);

  EXPECT_EQ(io->tell(), Exiv2::GUID + Exiv2::QWORD);

  ASSERT_EQ(hr.getId().size(), Exiv2::GUID);
  EXPECT_EQ(hr.getId().cmpBytes(0, guid.data(), guid.size()), 0);

  EXPECT_EQ(hr.getSize(), 0u);
  EXPECT_EQ(hr.getRemainingSize(), 0u);
}

// Exceptional/error: condition passes (enough bytes), but underlying read returns too few bytes -> readOrThrow should throw.
TEST_F(HeaderReaderTest_2199, ThrowsWhenGuidReadIsShort_2199) {
  // Make buffer large enough so the size>=tell+GUID+QWORD check passes.
  std::vector<Exiv2::byte> buf = MakeBytes(Exiv2::GUID + Exiv2::QWORD, static_cast<Exiv2::byte>(0x55));
  auto io = std::make_unique<VectorBasicIo>(buf, /*start_pos=*/0, /*short_read=*/true);

  EXPECT_ANY_THROW({
    Exiv2::AsfVideo::HeaderReader hr(io);
    (void)hr;
  });
}