// -----------------------------------------------------------------------------
// Unit tests for Exiv2::Internal::OlympusMnHeader::read
// File: makernote_int.cpp (partial interface)
// TEST_ID: 1439
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

// Exiv2 public/common types
#include "exiv2/types.hpp"

// Class under test lives in an internal header in Exiv2. In Exiv2's test tree,
// internal headers are typically includable. If your build exposes a different
// path, adjust accordingly.
#include "makernote_int.hpp"

namespace {

using Exiv2::byte;
using Exiv2::ByteOrder;

// Helper: build a buffer with a given prefix and extra bytes.
static std::vector<byte> MakeBuf(std::initializer_list<byte> prefix, size_t extra = 0, byte fill = 0x00) {
  std::vector<byte> v(prefix.begin(), prefix.end());
  v.resize(v.size() + extra, fill);
  return v;
}

// Helper: create a 6-byte "signature-like" prefix (what read() compares).
static std::array<byte, 6> As6(std::initializer_list<byte> six) {
  std::array<byte, 6> a{};
  size_t i = 0;
  for (byte b : six) {
    if (i < 6) a[i++] = b;
  }
  // if fewer than 6 provided, remaining are 0.
  return a;
}

class OlympusMnHeaderTest_1439 : public ::testing::Test {
protected:
  Exiv2::Internal::OlympusMnHeader hdr_;
};

TEST_F(OlympusMnHeaderTest_1439, ReadReturnsFalseWhenDataNull_1439) {
  const byte* p = nullptr;
  const size_t size = 64;
  EXPECT_FALSE(hdr_.read(p, size, ByteOrder::littleEndian));
}

TEST_F(OlympusMnHeaderTest_1439, ReadReturnsFalseWhenSizeTooSmall_1439) {
  // We don't know sizeOfSignature(), but we can still test boundary by using size 0.
  std::vector<byte> buf = MakeBuf({0x00, 0x01, 0x02, 0x03}, 0);
  EXPECT_FALSE(hdr_.read(buf.data(), 0, ByteOrder::littleEndian));
}

TEST_F(OlympusMnHeaderTest_1439, ReadReturnsFalseForNonMatchingPrefix_1439) {
  // For Olympus makernotes, the common signature is "OLYMP\0" (6 bytes "OLYMP\0" or "OLYMP\0"?).
  // We must NOT assume the exact signature, so we instead test that a clearly random prefix
  // that is unlikely to match yields false when size is reasonably large.
  std::vector<byte> buf = MakeBuf({0xDE, 0xAD, 0xBE, 0xEF, 0xAA, 0x55}, 32, 0x11);
  EXPECT_FALSE(hdr_.read(buf.data(), buf.size(), ByteOrder::littleEndian));
}

TEST_F(OlympusMnHeaderTest_1439, ReadIgnoresByteOrderParameterForOutcome_1439) {
  // Observable behavior: the provided ByteOrder is not used in the visible snippet,
  // so the result should be the same for a given buffer regardless of ByteOrder.
  std::vector<byte> buf = MakeBuf({0xDE, 0xAD, 0xBE, 0xEF, 0xAA, 0x55}, 32, 0x22);

  const bool le = hdr_.read(buf.data(), buf.size(), ByteOrder::littleEndian);

  // Re-create a new instance to avoid relying on any internal state between calls.
  Exiv2::Internal::OlympusMnHeader hdr2;
  const bool be = hdr2.read(buf.data(), buf.size(), ByteOrder::bigEndian);

  EXPECT_EQ(le, be);
}

TEST_F(OlympusMnHeaderTest_1439, ReadDoesNotCrashOnLargeInput_1439) {
  // Stress-ish: large buffer should not crash and should return a bool deterministically.
  std::vector<byte> buf(4096, static_cast<byte>(0x7F));
  // Put a non-matching 6-byte prefix.
  buf[0] = 0x00; buf[1] = 0x01; buf[2] = 0x02; buf[3] = 0x03; buf[4] = 0x04; buf[5] = 0x05;

  EXPECT_NO_THROW({
    const bool ok = hdr_.read(buf.data(), buf.size(), ByteOrder::littleEndian);
    (void)ok;
  });
}

TEST_F(OlympusMnHeaderTest_1439, ReadIsRepeatableWithSameInput_1439) {
  // Black-box observable: calling read twice with same args should produce same return value.
  std::vector<byte> buf = MakeBuf({0x10, 0x20, 0x30, 0x40, 0x50, 0x60}, 16, 0x33);

  const bool r1 = hdr_.read(buf.data(), buf.size(), ByteOrder::littleEndian);
  const bool r2 = hdr_.read(buf.data(), buf.size(), ByteOrder::littleEndian);

  EXPECT_EQ(r1, r2);
}

TEST_F(OlympusMnHeaderTest_1439, ReadReturnsFalseWhenSizeOneByte_1439) {
  // Another boundary case: size=1 should be less than any reasonable signature size.
  std::vector<byte> buf = MakeBuf({0x00}, 0);
  EXPECT_FALSE(hdr_.read(buf.data(), 1, ByteOrder::littleEndian));
}

}  // namespace