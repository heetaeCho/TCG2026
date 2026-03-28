// =================================================================================================
// TEST_ID: 832
// File: ./TestProjects/exiv2/src/value.cpp (partial)
// Under test: Exiv2::XmpValue::read(const byte* buf, size_t len, ByteOrder)
// Notes:
//  - We treat implementation as a black box.
//  - Observable behavior from this interface is only the returned int and "no-crash" behavior.
//  - The overload XmpValue::read(std::string) is not provided here; tests assume the real codebase
//    defines it and links accordingly.
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "exiv2/value.hpp"   // expected to provide Exiv2::XmpValue, Exiv2::ByteOrder, Exiv2::byte

namespace {

// Helper: convert std::string to Exiv2 byte buffer.
static std::vector<Exiv2::byte> ToBytes(const std::string& s) {
  return std::vector<Exiv2::byte>(s.begin(), s.end());
}

class XmpValueReadByteBufferTest_832 : public ::testing::Test {};

}  // namespace

// Normal operation: same input content should yield same result regardless of which buffer is used.
TEST_F(XmpValueReadByteBufferTest_832, SameContentDifferentBuffersReturnSame_832) {
  Exiv2::XmpValue v;

  const std::string payload = "abc123XYZ";
  auto bytes1 = ToBytes(payload);
  auto bytes2 = ToBytes(payload);

  const int r1 = v.read(bytes1.data(), bytes1.size(), Exiv2::ByteOrder::invalidByteOrder);
  const int r2 = v.read(bytes2.data(), bytes2.size(), Exiv2::ByteOrder::littleEndian);

  EXPECT_EQ(r1, r2);
}

// Normal operation: byteOrder parameter is ignored in this overload; varying it should not change return.
TEST_F(XmpValueReadByteBufferTest_832, ByteOrderDoesNotAffectReturnForSameBytes_832) {
  Exiv2::XmpValue v;

  const std::string payload = "some xmp-ish text";
  auto bytes = ToBytes(payload);

  const int r_invalid = v.read(bytes.data(), bytes.size(), Exiv2::ByteOrder::invalidByteOrder);
  const int r_le = v.read(bytes.data(), bytes.size(), Exiv2::ByteOrder::littleEndian);
  const int r_be = v.read(bytes.data(), bytes.size(), Exiv2::ByteOrder::bigEndian);

  EXPECT_EQ(r_invalid, r_le);
  EXPECT_EQ(r_invalid, r_be);
}

// Boundary: empty input (len=0) should be handled without crashing; should be consistent.
TEST_F(XmpValueReadByteBufferTest_832, EmptyInputLenZeroIsHandled_832) {
  Exiv2::XmpValue v;

  // For len=0, buf should not be dereferenced; still pass a valid pointer.
  Exiv2::byte dummy = 0;

  const int r1 = v.read(&dummy, 0u, Exiv2::ByteOrder::invalidByteOrder);
  const int r2 = v.read(&dummy, 0u, Exiv2::ByteOrder::littleEndian);

  EXPECT_EQ(r1, r2);
}

// Boundary: buffer may contain embedded NULs; len controls size and should be accepted.
TEST_F(XmpValueReadByteBufferTest_832, EmbeddedNullBytesAreIncludedByLen_832) {
  Exiv2::XmpValue v;

  std::vector<Exiv2::byte> bytes = {
      static_cast<Exiv2::byte>('A'),
      static_cast<Exiv2::byte>(0),
      static_cast<Exiv2::byte>('B'),
      static_cast<Exiv2::byte>(0),
      static_cast<Exiv2::byte>('C'),
  };

  const int r1 = v.read(bytes.data(), bytes.size(), Exiv2::ByteOrder::invalidByteOrder);

  // Same content copied into another buffer should yield same return.
  auto bytes2 = bytes;
  const int r2 = v.read(bytes2.data(), bytes2.size(), Exiv2::ByteOrder::bigEndian);

  EXPECT_EQ(r1, r2);
}

// Boundary: only the first 'len' bytes should be considered; extra trailing bytes beyond len should not matter.
TEST_F(XmpValueReadByteBufferTest_832, OnlyLenBytesAreConsidered_832) {
  Exiv2::XmpValue v;

  std::vector<Exiv2::byte> bytes = ToBytes("prefix");
  bytes.push_back(static_cast<Exiv2::byte>('X'));
  bytes.push_back(static_cast<Exiv2::byte>('Y'));
  bytes.push_back(static_cast<Exiv2::byte>('Z'));

  // Read only "prefix"
  const int r_prefix = v.read(bytes.data(), 6u, Exiv2::ByteOrder::invalidByteOrder);

  // Compare with a buffer that contains exactly "prefix"
  auto exact = ToBytes("prefix");
  const int r_exact = v.read(exact.data(), exact.size(), Exiv2::ByteOrder::invalidByteOrder);

  EXPECT_EQ(r_prefix, r_exact);
}

// Exceptional/error-ish (observable): calling with nullptr and len=0 should be safe if implementation does not touch buf.
// We only assert "no crash" and that repeated calls behave consistently.
// (Do NOT call with nullptr and len>0; that would be undefined for std::string construction.)
TEST_F(XmpValueReadByteBufferTest_832, NullptrWithZeroLenDoesNotCrash_832) {
  Exiv2::XmpValue v;

  const int r1 = v.read(nullptr, 0u, Exiv2::ByteOrder::invalidByteOrder);
  const int r2 = v.read(nullptr, 0u, Exiv2::ByteOrder::littleEndian);

  EXPECT_EQ(r1, r2);
}