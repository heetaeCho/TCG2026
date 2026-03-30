// SPDX-License-Identifier: GPL-2.0-or-later
// Tests for Exiv2::Internal::SigmaMnHeader::read
//
// File under test:
//   ./TestProjects/exiv2/src/makernote_int.cpp
//
// Constraints honored:
// - Treat implementation as a black box: only validate observable return value (bool).
// - No access to private state (buf_, start_, signatures).
// - Boundary + error cases (null, too-small, mismatch).
// - No mocks needed.

#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstdint>

// Exiv2 headers (adjust include paths as needed in your build)
#include "exiv2/types.hpp"       // Exiv2::byte
#include "exiv2/byteorder.hpp"   // Exiv2::ByteOrder
#include "makernote_int.hpp"     // Exiv2::Internal::SigmaMnHeader (or correct internal header)

namespace {

using Exiv2::byte;
using Exiv2::ByteOrder;
using Exiv2::Internal::SigmaMnHeader;

// Provide a best-effort ByteOrder value without assuming which one matters.
// We only need to compile and pass some value; read() should accept any ByteOrder.
static ByteOrder AnyByteOrder() {
#ifdef EXV_LITTLEENDIAN
  return Exiv2::littleEndian;
#else
  return Exiv2::bigEndian;
#endif
}

class SigmaMnHeaderTest_1496 : public ::testing::Test {};

TEST_F(SigmaMnHeaderTest_1496, ReadReturnsFalseWhenDataIsNull_1496) {
  SigmaMnHeader hdr;
  const byte* p = nullptr;
  const size_t size = 64;  // arbitrary non-zero

  EXPECT_FALSE(hdr.read(p, size, AnyByteOrder()));
}

TEST_F(SigmaMnHeaderTest_1496, ReadReturnsFalseWhenSizeIsZero_1496) {
  SigmaMnHeader hdr;
  const std::array<byte, 1> data{{static_cast<byte>(0)}};

  EXPECT_FALSE(hdr.read(data.data(), 0, AnyByteOrder()));
}

TEST_F(SigmaMnHeaderTest_1496, ReadReturnsFalseWhenSizeIsLessThanEight_1496) {
  // Signature compares 8 bytes; any size < 8 should fail.
  SigmaMnHeader hdr;
  const std::array<byte, 7> data{{static_cast<byte>('S'),
                                  static_cast<byte>('I'),
                                  static_cast<byte>('G'),
                                  static_cast<byte>('M'),
                                  static_cast<byte>('A'),
                                  static_cast<byte>('X'),
                                  static_cast<byte>('X')}};

  EXPECT_FALSE(hdr.read(data.data(), data.size(), AnyByteOrder()));
}

TEST_F(SigmaMnHeaderTest_1496, ReadReturnsFalseWhenFirstEightBytesDoNotMatchEitherSignature_1496) {
  SigmaMnHeader hdr;

  // Provide at least 8 bytes; choose values unlikely to match either signature.
  const std::array<byte, 16> data{{static_cast<byte>(0x00), static_cast<byte>(0x01),
                                   static_cast<byte>(0x02), static_cast<byte>(0x03),
                                   static_cast<byte>(0x04), static_cast<byte>(0x05),
                                   static_cast<byte>(0x06), static_cast<byte>(0x07),
                                   static_cast<byte>(0xAA), static_cast<byte>(0xBB),
                                   static_cast<byte>(0xCC), static_cast<byte>(0xDD),
                                   static_cast<byte>(0xEE), static_cast<byte>(0xFF),
                                   static_cast<byte>(0x10), static_cast<byte>(0x11)}};

  EXPECT_FALSE(hdr.read(data.data(), data.size(), AnyByteOrder()));
}

TEST_F(SigmaMnHeaderTest_1496, ReadIsDeterministicForSameInput_1496) {
  // We can't assert internal state, but for a pure "read header" style API,
  // it should at least be deterministic on the same input and argument values.
  SigmaMnHeader hdr;

  const std::array<byte, 16> data{{static_cast<byte>(0x10), static_cast<byte>(0x20),
                                   static_cast<byte>(0x30), static_cast<byte>(0x40),
                                   static_cast<byte>(0x50), static_cast<byte>(0x60),
                                   static_cast<byte>(0x70), static_cast<byte>(0x80),
                                   static_cast<byte>(0x90), static_cast<byte>(0xA0),
                                   static_cast<byte>(0xB0), static_cast<byte>(0xC0),
                                   static_cast<byte>(0xD0), static_cast<byte>(0xE0),
                                   static_cast<byte>(0xF0), static_cast<byte>(0x00)}};

  const bool r1 = hdr.read(data.data(), data.size(), AnyByteOrder());
  const bool r2 = hdr.read(data.data(), data.size(), AnyByteOrder());

  EXPECT_EQ(r1, r2);
}

TEST_F(SigmaMnHeaderTest_1496, ReadResultDoesNotDependOnByteOrderForClearlyInvalidData_1496) {
  // For clearly-invalid headers (mismatching first 8 bytes), ByteOrder should not matter.
  SigmaMnHeader hdr;

  const std::array<byte, 8> data{{static_cast<byte>(0xDE), static_cast<byte>(0xAD),
                                  static_cast<byte>(0xBE), static_cast<byte>(0xEF),
                                  static_cast<byte>(0xFE), static_cast<byte>(0xED),
                                  static_cast<byte>(0xFA), static_cast<byte>(0xCE)}};

  EXPECT_FALSE(hdr.read(data.data(), data.size(), Exiv2::littleEndian));
  EXPECT_FALSE(hdr.read(data.data(), data.size(), Exiv2::bigEndian));
}

}  // namespace