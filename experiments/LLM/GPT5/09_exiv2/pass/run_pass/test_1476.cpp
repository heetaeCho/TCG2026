// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_panasonic_mn_header_1476.cpp

#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include "makernote_int.hpp"   // Exiv2::Internal::PanasonicMnHeader (project header)
#include "types.hpp"           // Exiv2::byte, Exiv2::ByteOrder (project header)

namespace {

// Helper: build a buffer with a chosen 9-byte signature prefix and extra payload.
static std::array<Exiv2::byte, 64> MakeBufferWithPrefix(const char* nineBytes) {
  std::array<Exiv2::byte, 64> buf{};
  std::memset(buf.data(), 0, buf.size());
  std::memcpy(buf.data(), nineBytes, 9);
  // Fill the rest with non-zero pattern so we don't accidentally rely on zeros.
  for (size_t i = 9; i < buf.size(); ++i) buf[i] = static_cast<Exiv2::byte>(0xA5);
  return buf;
}

}  // namespace

TEST(PanasonicMnHeaderTest_1476, ReadReturnsFalseOnNullData_1476) {
  Exiv2::Internal::PanasonicMnHeader hdr;

  // Null pointer should be rejected regardless of size / byte order.
  EXPECT_FALSE(hdr.read(nullptr, 0, Exiv2::littleEndian));
  EXPECT_FALSE(hdr.read(nullptr, 64, Exiv2::bigEndian));
}

TEST(PanasonicMnHeaderTest_1476, ReadReturnsFalseWhenSizeIsZeroEvenIfPointerValid_1476) {
  Exiv2::Internal::PanasonicMnHeader hdr;

  const auto buf = MakeBufferWithPrefix("Panasonic");  // common Panasonic signature prefix (9 bytes)
  EXPECT_FALSE(hdr.read(buf.data(), 0, Exiv2::littleEndian));
}

TEST(PanasonicMnHeaderTest_1476, ReadReturnsFalseWhenSignatureDoesNotMatch_1476) {
  Exiv2::Internal::PanasonicMnHeader hdr;

  // Provide a clearly wrong 9-byte prefix.
  const auto buf = MakeBufferWithPrefix("NotPanas");  // 8 chars; still provide 9 bytes via memcpy below
  // Ensure the first 9 bytes are not "Panasonic"
  std::array<Exiv2::byte, 64> wrong = buf;
  wrong[8] = static_cast<Exiv2::byte>('!');  // make 9th byte different, definitely mismatch

  EXPECT_FALSE(hdr.read(wrong.data(), wrong.size(), Exiv2::littleEndian));
  EXPECT_FALSE(hdr.read(wrong.data(), wrong.size(), Exiv2::bigEndian));
}

TEST(PanasonicMnHeaderTest_1476, ReadReturnsTrueWithMatchingSignatureAndSufficientSize_1476) {
  Exiv2::Internal::PanasonicMnHeader hdr;

  // The implementation compares the first 9 bytes against an internal signature.
  // Use a buffer large enough to satisfy any internal minimum size check.
  const auto buf = MakeBufferWithPrefix("Panasonic");  // 9-byte prefix

  EXPECT_TRUE(hdr.read(buf.data(), buf.size(), Exiv2::littleEndian));
}

TEST(PanasonicMnHeaderTest_1476, ReadCanBeCalledMultipleTimes_1476) {
  Exiv2::Internal::PanasonicMnHeader hdr;

  const auto good = MakeBufferWithPrefix("Panasonic");
  auto bad = MakeBufferWithPrefix("Panasonic");
  bad[0] = static_cast<Exiv2::byte>('X');  // force mismatch

  // First succeeds, second fails, third succeeds again (only observable behavior: return value).
  EXPECT_TRUE(hdr.read(good.data(), good.size(), Exiv2::littleEndian));
  EXPECT_FALSE(hdr.read(bad.data(), bad.size(), Exiv2::littleEndian));
  EXPECT_TRUE(hdr.read(good.data(), good.size(), Exiv2::bigEndian));
}