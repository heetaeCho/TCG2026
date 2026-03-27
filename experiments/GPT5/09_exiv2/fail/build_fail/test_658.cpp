// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_quicktimevideo_decodeblock_658.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/quicktimevideo.hpp"
#include "exiv2/types.hpp"

namespace {

using Exiv2::byte;

static std::vector<byte> U32BE(uint32_t v) {
  return {
      static_cast<byte>((v >> 24) & 0xff),
      static_cast<byte>((v >> 16) & 0xff),
      static_cast<byte>((v >> 8) & 0xff),
      static_cast<byte>((v >> 0) & 0xff),
  };
}

static std::vector<byte> U64BE(uint64_t v) {
  return {
      static_cast<byte>((v >> 56) & 0xff),
      static_cast<byte>((v >> 48) & 0xff),
      static_cast<byte>((v >> 40) & 0xff),
      static_cast<byte>((v >> 32) & 0xff),
      static_cast<byte>((v >> 24) & 0xff),
      static_cast<byte>((v >> 16) & 0xff),
      static_cast<byte>((v >> 8) & 0xff),
      static_cast<byte>((v >> 0) & 0xff),
  };
}

static void Append(std::vector<byte>& dst, const std::vector<byte>& src) {
  dst.insert(dst.end(), src.begin(), src.end());
}

static void Append4(std::vector<byte>& dst, const char (&s)[5]) {
  dst.push_back(static_cast<byte>(s[0]));
  dst.push_back(static_cast<byte>(s[1]));
  dst.push_back(static_cast<byte>(s[2]));
  dst.push_back(static_cast<byte>(s[3]));
}

// A minimal in-memory BasicIo implementation suitable for driving decodeBlock()
// via observable behavior (success/throw).
class VectorIo final : public Exiv2::BasicIo {
 public:
  explicit VectorIo(std::vector<byte> data) : data_(std::move(data)) {}

  size_t read(byte* buf, size_t rcount) override {
    if (pos_ >= data_.size()) {
      eof_ = true;
      return 0;
    }
    const size_t avail = data_.size() - pos_;
    const size_t n = (rcount < avail) ? rcount : avail;
    if (n == 0) {
      eof_ = true;
      return 0;
    }
    std::memcpy(buf, data_.data() + pos_, n);
    pos_ += n;
    if (pos_ >= data_.size()) eof_ = true;
    return n;
  }

  Exiv2::DataBuf read(size_t rcount) override {
    Exiv2::DataBuf b(rcount);
    const size_t n = read(b.data(), rcount);
    if (n < rcount) {
      // Shrink to what was actually read (matches typical semantics).
      b.resize(n);
    }
    return b;
  }

  int seek(int64_t offset, Exiv2::Position pos) override {
    int64_t base = 0;
    switch (pos) {
      case Exiv2::beg:
        base = 0;
        break;
      case Exiv2::cur:
        base = static_cast<int64_t>(pos_);
        break;
      case Exiv2::end:
        base = static_cast<int64_t>(data_.size());
        break;
    }
    const int64_t np = base + offset;
    if (np < 0) return 1;
    pos_ = static_cast<size_t>(np);
    eof_ = (pos_ >= data_.size());
    return 0;
  }

  const size_t tell() override { return pos_; }
  const size_t size() override { return data_.size(); }
  const bool eof() override { return eof_; }
  const bool isopen() override { return true; }
  const int error() override { return 0; }
  const std::string& path() override { return path_; }

 private:
  std::vector<byte> data_;
  size_t pos_{0};
  bool eof_{false};
  std::string path_{"VectorIo"};
};

// Expose protected decodeBlock for testing without touching private state.
class TestQuickTimeVideo final : public Exiv2::QuickTimeVideo {
 public:
  TestQuickTimeVideo(std::unique_ptr<Exiv2::BasicIo> io, size_t max_depth)
      : Exiv2::QuickTimeVideo(std::move(io), max_depth) {}

  void CallDecodeBlock(size_t recursion_depth, const std::string& entered_from) {
    decodeBlock(recursion_depth, entered_from);
  }
};

class QuickTimeVideoDecodeBlockTest_658 : public ::testing::Test {
 protected:
  static std::unique_ptr<TestQuickTimeVideo> MakeVideo(size_t max_depth, std::vector<byte> bytes) {
    auto io = std::make_unique<VectorIo>(std::move(bytes));
    return std::make_unique<TestQuickTimeVideo>(std::move(io), max_depth);
  }
};

TEST_F(QuickTimeVideoDecodeBlockTest_658, Valid32BitAtomHeaderSize8DoesNotThrow_658) {
  // size=8, type="test", no payload.
  std::vector<byte> bytes;
  Append(bytes, U32BE(8));
  Append4(bytes, "test");

  auto v = MakeVideo(/*max_depth=*/8, std::move(bytes));
  EXPECT_NO_THROW(v->CallDecodeBlock(/*recursion_depth=*/0, /*entered_from=*/"root"));
}

TEST_F(QuickTimeVideoDecodeBlockTest_658, RecursionDepthAtMaxThrows_658) {
  // Any bytes are fine; recursion depth check happens first.
  std::vector<byte> bytes;
  Append(bytes, U32BE(8));
  Append4(bytes, "test");

  auto v = MakeVideo(/*max_depth=*/1, std::move(bytes));
  EXPECT_ANY_THROW(v->CallDecodeBlock(/*recursion_depth=*/1, /*entered_from=*/"root"));
}

TEST_F(QuickTimeVideoDecodeBlockTest_658, SizeLessThanHeaderThrows_658) {
  // size=4 (< hdrsize 8) should fail the size>=hdrsize enforce.
  std::vector<byte> bytes;
  Append(bytes, U32BE(4));
  Append4(bytes, "test");

  auto v = MakeVideo(/*max_depth=*/8, std::move(bytes));
  EXPECT_ANY_THROW(v->CallDecodeBlock(/*recursion_depth=*/0, /*entered_from=*/"root"));
}

TEST_F(QuickTimeVideoDecodeBlockTest_658, SizeMinusHeaderExceedsRemainingThrows_658) {
  // size=12 => payload=4, but file provides only header (8). Remaining after header is 0.
  std::vector<byte> bytes;
  Append(bytes, U32BE(12));
  Append4(bytes, "test");

  auto v = MakeVideo(/*max_depth=*/8, std::move(bytes));
  EXPECT_ANY_THROW(v->CallDecodeBlock(/*recursion_depth=*/0, /*entered_from=*/"root"));
}

TEST_F(QuickTimeVideoDecodeBlockTest_658, ExtendedSize64BitWhenSizeIs1DoesNotThrow_658) {
  // size field=1 triggers 64-bit size read. Use extended size = 16 (hdrsize becomes 16, payload 0).
  std::vector<byte> bytes;
  Append(bytes, U32BE(1));
  Append4(bytes, "test");
  Append(bytes, U64BE(16));

  auto v = MakeVideo(/*max_depth=*/8, std::move(bytes));
  EXPECT_NO_THROW(v->CallDecodeBlock(/*recursion_depth=*/0, /*entered_from=*/"root"));
}

TEST_F(QuickTimeVideoDecodeBlockTest_658, SizeZeroEnteredFromMetaReadsExtraAndCanSucceed_658) {
  // For entered_from=="meta" and initial size==0:
  // - decodeBlock reads first 4 (0), then reads next 4 into buf (these bytes become the "size" value).
  // Provide "type" bytes as big-endian 8, then provide 4 more bytes for the special readOrThrow.
  std::vector<byte> bytes;
  Append(bytes, U32BE(0));   // initial size = 0
  Append(bytes, U32BE(8));   // treated as size when entered_from == "meta"
  Append(bytes, U32BE(0));   // 4 extra bytes for readOrThrow(..., kerCorruptedMetadata)

  auto v = MakeVideo(/*max_depth=*/8, std::move(bytes));
  EXPECT_NO_THROW(v->CallDecodeBlock(/*recursion_depth=*/0, /*entered_from=*/"meta"));
}

}  // namespace