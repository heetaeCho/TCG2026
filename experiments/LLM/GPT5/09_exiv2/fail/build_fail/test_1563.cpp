// TEST_ID 1563
// Unit tests for Exiv2::AsfVideo::decodeBlock (black-box via public shim)
//
// File: test_asfvideo_decodeblock_1563.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "exiv2/asfvideo.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/types.hpp"

namespace {

using Exiv2::BasicIo;
using Exiv2::byte;
using Exiv2::DataBuf;
using Exiv2::ErrorCode;

// Simple in-memory BasicIo implementation suitable for driving AsfVideo parsing.
// It also records seekOrThrow calls (external interaction verification).
class MemBasicIo final : public Exiv2::BasicIo {
 public:
  explicit MemBasicIo(std::vector<byte> data) : data_(std::move(data)) {}

  // --- BasicIo overrides used by AsfVideo / HeaderReader ---
  size_t read(byte* buf, size_t rcount) override {
    const size_t avail = (pos_ < data_.size()) ? (data_.size() - pos_) : 0;
    const size_t n = (rcount < avail) ? rcount : avail;
    if (n > 0) {
      std::memcpy(buf, data_.data() + pos_, n);
      pos_ += n;
    }
    if (n < rcount) {
      eof_ = true;
    }
    return n;
  }

  DataBuf read(size_t rcount) override {
    DataBuf b(rcount);
    const size_t n = read(b.data(0), rcount);
    if (n < rcount) {
      // Keep size as requested; consumer should decide if partial reads are acceptable.
      // (We avoid inferring internal behavior; this is a generic in-memory read.)
    }
    return b;
  }

  int seek(int64_t offset, Exiv2::BasicIo::Position pos) override {
    int64_t base = 0;
    if (pos == Exiv2::BasicIo::beg) base = 0;
    else if (pos == Exiv2::BasicIo::cur) base = static_cast<int64_t>(pos_);
    else if (pos == Exiv2::BasicIo::end) base = static_cast<int64_t>(data_.size());

    const int64_t np = base + offset;
    if (np < 0) return -1;
    pos_ = static_cast<size_t>(np);
    if (pos_ > data_.size()) {
      // BasicIo typically allows seeking past end; mark eof.
      eof_ = true;
    }
    return 0;
  }

  const size_t tell() override { return pos_; }
  const size_t size() override { return data_.size(); }

  void seekOrThrow(int64_t offset, Exiv2::BasicIo::Position pos, ErrorCode err) override {
    ++seek_or_throw_calls_;
    last_seek_offset_ = offset;
    last_seek_pos_ = pos;
    last_seek_err_ = err;
    // Perform the seek as well (no throw here; CUT decides error handling).
    (void)seek(offset, pos);
  }

  // --- helpers for assertions ---
  int seekOrThrowCalls() const { return seek_or_throw_calls_; }
  int64_t lastSeekOffset() const { return last_seek_offset_; }
  Exiv2::BasicIo::Position lastSeekPos() const { return last_seek_pos_; }
  ErrorCode lastSeekErr() const { return last_seek_err_; }

 private:
  std::vector<byte> data_;
  size_t pos_{0};
  bool eof_{false};

  int seek_or_throw_calls_{0};
  int64_t last_seek_offset_{0};
  Exiv2::BasicIo::Position last_seek_pos_{Exiv2::BasicIo::beg};
  ErrorCode last_seek_err_{ErrorCode::kerSuccess};
};

// Test shim: expose protected decodeBlock() via a public wrapper.
class AsfVideoTestable final : public Exiv2::AsfVideo {
 public:
  explicit AsfVideoTestable(std::unique_ptr<BasicIo> io) : Exiv2::AsfVideo(std::move(io)) {}
  void DecodeBlockPublic() { decodeBlock(); }
};

// --- Byte helpers ---
constexpr size_t kGUID = 16;
constexpr size_t kQWORD = 8;

// Append little-endian 64-bit to vector.
static void append_u64_le(std::vector<byte>& out, uint64_t v) {
  for (int i = 0; i < 8; ++i) {
    out.push_back(static_cast<byte>((v >> (8 * i)) & 0xFF));
  }
}

// ASF GUID layout in ASF header objects is typically:
// Data1 (LE 32), Data2 (LE 16), Data3 (LE 16), Data4[8] (as-is).
static std::vector<byte> guid_bytes(uint32_t d1, uint16_t d2, uint16_t d3, const byte d4[8]) {
  std::vector<byte> g;
  g.reserve(16);
  g.push_back(static_cast<byte>(d1 & 0xFF));
  g.push_back(static_cast<byte>((d1 >> 8) & 0xFF));
  g.push_back(static_cast<byte>((d1 >> 16) & 0xFF));
  g.push_back(static_cast<byte>((d1 >> 24) & 0xFF));
  g.push_back(static_cast<byte>(d2 & 0xFF));
  g.push_back(static_cast<byte>((d2 >> 8) & 0xFF));
  g.push_back(static_cast<byte>(d3 & 0xFF));
  g.push_back(static_cast<byte>((d3 >> 8) & 0xFF));
  for (int i = 0; i < 8; ++i) g.push_back(d4[i]);
  return g;
}

// GUIDs visible in the provided GUIDReferenceTags map (examples):
// "Data" entry: {1974609462, 26254, 4559, {166,217,0,170,0,98,206,108}}
static std::vector<byte> guid_data_object() {
  const byte d4[8] = {166, 217, 0, 170, 0, 98, 206, 108};
  return guid_bytes(1974609462u, 26254u, 4559u, d4);
}

static std::vector<byte> guid_random_unknown() {
  const byte d4[8] = {1, 2, 3, 4, 5, 6, 7, 8};
  return guid_bytes(0x11223344u, 0x5566u, 0x7788u, d4);
}

// Build a minimal ASF object: [GUID(16)][Size(8)][payload...]
// Size is the declared object size in bytes (including header), as commonly used in ASF.
static std::vector<byte> make_object(const std::vector<byte>& guid16, uint64_t declared_size,
                                     size_t payload_size) {
  std::vector<byte> b;
  b.insert(b.end(), guid16.begin(), guid16.end());
  append_u64_le(b, declared_size);
  b.insert(b.end(), payload_size, static_cast<byte>(0xAB));
  return b;
}

class AsfVideoDecodeBlockTest_1563 : public ::testing::Test {};

TEST_F(AsfVideoDecodeBlockTest_1563, ThrowsWhenNotEnoughBytesForGuidAndSize_1563) {
  // Boundary: fewer than GUID(16)+QWORD(8) bytes available from current tell().
  std::vector<byte> too_small(23, 0);
  auto io = std::make_unique<MemBasicIo>(too_small);
  AsfVideoTestable asf(std::unique_ptr<BasicIo>(io.release()));

  EXPECT_THROW(asf.DecodeBlockPublic(), Exiv2::Error);
}

TEST_F(AsfVideoDecodeBlockTest_1563, ThrowsWhenDeclaredObjectSizeExceedsRemainingBytes_1563) {
  // Provide exactly 24 bytes total, but declare a non-zero object size.
  // After reading the 24-byte header, remaining bytes are 0; decodeBlock enforces size <= remaining.
  auto guid = guid_data_object();
  std::vector<byte> buf = make_object(guid, /*declared_size=*/25u, /*payload_size=*/0u);
  ASSERT_EQ(buf.size(), kGUID + kQWORD);

  auto io = std::make_unique<MemBasicIo>(buf);
  AsfVideoTestable asf(std::unique_ptr<BasicIo>(io.release()));

  EXPECT_THROW(asf.DecodeBlockPublic(), Exiv2::Error);
}

TEST_F(AsfVideoDecodeBlockTest_1563, ThrowsWhenDeclaredObjectSizeEqualsHeaderButNoRemainingData_1563) {
  // Boundary: declared size equals header size, and the file contains only the header.
  // This should violate the "object size <= remaining bytes after header" enforcement.
  auto guid = guid_data_object();
  std::vector<byte> buf = make_object(guid, /*declared_size=*/24u, /*payload_size=*/0u);
  ASSERT_EQ(buf.size(), kGUID + kQWORD);

  auto io = std::make_unique<MemBasicIo>(buf);
  AsfVideoTestable asf(std::unique_ptr<BasicIo>(io.release()));

  EXPECT_THROW(asf.DecodeBlockPublic(), Exiv2::Error);
}

TEST_F(AsfVideoDecodeBlockTest_1563, SeeksWhenTagFoundButNotProcessed_1563) {
  // Use a GUID that exists in GUIDReferenceTags but is not one of the explicitly processed ones in
  // decodeBlock() (e.g., "Data").
  const size_t payload = 10;
  const uint64_t declared_size = static_cast<uint64_t>(kGUID + kQWORD + payload);

  std::vector<byte> buf = make_object(guid_data_object(), declared_size, payload);
  ASSERT_EQ(buf.size(), declared_size);

  auto mem = std::make_unique<MemBasicIo>(buf);
  MemBasicIo* mem_raw = mem.get();  // observe collaborator interactions
  AsfVideoTestable asf(std::unique_ptr<BasicIo>(mem.release()));

  EXPECT_NO_THROW(asf.DecodeBlockPublic());

  ASSERT_EQ(mem_raw->seekOrThrowCalls(), 1);
  EXPECT_EQ(mem_raw->lastSeekPos(), Exiv2::BasicIo::beg);
  EXPECT_EQ(mem_raw->lastSeekErr(), ErrorCode::kerFailedToReadImageData);
  // Expected seek target is tell() + remaining_size; with a standard ASF object that leaves payload
  // bytes remaining, this lands at the declared object end.
  EXPECT_EQ(static_cast<size_t>(mem_raw->lastSeekOffset()), declared_size);
}

TEST_F(AsfVideoDecodeBlockTest_1563, SeeksWhenTagNotFound_1563) {
  // Use an unknown GUID so the "tag not found" branch is taken.
  const size_t payload = 7;
  const uint64_t declared_size = static_cast<uint64_t>(kGUID + kQWORD + payload);

  std::vector<byte> buf = make_object(guid_random_unknown(), declared_size, payload);
  ASSERT_EQ(buf.size(), declared_size);

  auto mem = std::make_unique<MemBasicIo>(buf);
  MemBasicIo* mem_raw = mem.get();
  AsfVideoTestable asf(std::unique_ptr<BasicIo>(mem.release()));

  EXPECT_NO_THROW(asf.DecodeBlockPublic());

  ASSERT_EQ(mem_raw->seekOrThrowCalls(), 1);
  EXPECT_EQ(mem_raw->lastSeekPos(), Exiv2::BasicIo::beg);
  EXPECT_EQ(mem_raw->lastSeekErr(), ErrorCode::kerFailedToReadImageData);
  EXPECT_EQ(static_cast<size_t>(mem_raw->lastSeekOffset()), declared_size);
}

}  // namespace