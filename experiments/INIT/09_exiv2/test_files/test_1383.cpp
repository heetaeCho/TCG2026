// File: test_tags_int_print0x0000_1383.cpp
// Unit tests for: Exiv2::Internal::print0x0000
// Target: ./TestProjects/exiv2/src/tags_int.cpp

#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>   // Value, ExifData, TypeId, ByteOrder, etc.
#include <sstream>
#include <string>

namespace {

// Helper: create a Value of a given TypeId and fill it with raw bytes (if provided).
static Exiv2::Value::UniquePtr MakeValueFromBytes(Exiv2::TypeId type,
                                                 const Exiv2::byte* data,
                                                 long len) {
  auto v = Exiv2::Value::create(type);
  // For BYTE/UBYTE values, byte order is irrelevant, but the API requires it.
  v->read(data, len, Exiv2::littleEndian);
  return v;
}

}  // namespace

TEST(Print0x0000Test_1383, ReturnsSameStreamReference_1383) {
  const Exiv2::byte bytes[4] = {1, 2, 3, 4};
  auto v = MakeValueFromBytes(Exiv2::unsignedByte, bytes, 4);

  std::ostringstream os;
  std::ostream& ret = Exiv2::Internal::print0x0000(os, *v, nullptr);

  EXPECT_EQ(&ret, &os);
}

TEST(Print0x0000Test_1383, FormatsUnsignedByteSize4AsDottedQuad_1383) {
  const Exiv2::byte bytes[4] = {1, 2, 3, 4};
  auto v = MakeValueFromBytes(Exiv2::unsignedByte, bytes, 4);

  std::ostringstream os;
  Exiv2::Internal::print0x0000(os, *v, nullptr);

  EXPECT_EQ(os.str(), "1.2.3.4");
}

TEST(Print0x0000Test_1383, FormatsBoundaryUnsignedByteValues_1383) {
  const Exiv2::byte bytes[4] = {0, 255, 128, 1};
  auto v = MakeValueFromBytes(Exiv2::unsignedByte, bytes, 4);

  std::ostringstream os;
  Exiv2::Internal::print0x0000(os, *v, nullptr);

  EXPECT_EQ(os.str(), "0.255.128.1");
}

TEST(Print0x0000Test_1383, FallsBackToStreamingValueWhenSizeNot4_1383) {
  const Exiv2::byte bytes3[3] = {1, 2, 3};
  auto v = MakeValueFromBytes(Exiv2::unsignedByte, bytes3, 3);

  std::ostringstream expected;
  expected << *v;

  std::ostringstream actual;
  Exiv2::Internal::print0x0000(actual, *v, nullptr);

  EXPECT_EQ(actual.str(), expected.str());
}

TEST(Print0x0000Test_1383, FallsBackToStreamingValueWhenTypeNotUnsignedByte_1383) {
  // Use a different TypeId with 4 bytes to ensure the mismatch is type-based.
  const Exiv2::byte bytes[4] = {1, 2, 3, 4};
  auto v = MakeValueFromBytes(Exiv2::signedByte, bytes, 4);

  std::ostringstream expected;
  expected << *v;

  std::ostringstream actual;
  Exiv2::Internal::print0x0000(actual, *v, nullptr);

  EXPECT_EQ(actual.str(), expected.str());
}