// =================================================================================================
// TestProjects/exiv2/tests/unit/test_tags_int_printUcs2_1380.cpp
// Unit tests for ./TestProjects/exiv2/src/tags_int.cpp (printUcs2)
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/value.hpp>
#include <exiv2/types.hpp>

#include <sstream>
#include <string>
#include <vector>

// The function under test lives in Exiv2::Internal.
// In the Exiv2 codebase this is typically declared in a private/internal header.
// Adjust include path if your project exposes it differently.
#include "tags_int.hpp"

namespace {

using Exiv2::byte;
using Exiv2::TypeId;
using Exiv2::Value;

std::string StreamValueDirect(const Value& value) {
  std::ostringstream os;
  os << value;
  return os.str();
}

std::string StreamViaPrintUcs2(const Value& value) {
  std::ostringstream os;
  // ExifData* is unused by the implementation; pass nullptr.
  Exiv2::Internal::printUcs2(os, value, nullptr);
  return os.str();
}

Value::UniquePtr MakeValue(TypeId type) {
  auto v = Value::create(type);
  EXPECT_NE(v.get(), nullptr);
  return v;
}

Value::UniquePtr MakeUnsignedByteValue(const std::vector<byte>& bytes) {
  auto v = MakeValue(Exiv2::unsignedByte);
  if (!bytes.empty()) {
    // Use the public Value interface to populate the data.
    // Byte order is part of the interface; choose invalidByteOrder to match typical usage
    // and avoid relying on internal implementation details.
    v->read(bytes.data(), bytes.size(), Exiv2::invalidByteOrder);
  }
  return v;
}

}  // namespace

// -------------------------------------------------------------------------------------------------

class PrintUcs2Test_1380 : public ::testing::Test {};

// Normal operation: for non-unsignedByte types, printUcs2 should fall back to streaming `value`.
TEST_F(PrintUcs2Test_1380, NonUnsignedByteFallsBackToValueStream_1380) {
  auto v = MakeValue(Exiv2::asciiString);
  ASSERT_NE(v.get(), nullptr);

  // Populate with a simple ASCII string via the public interface.
  const char* txt = "hello";
  v->read(reinterpret_cast<const byte*>(txt), std::strlen(txt), Exiv2::invalidByteOrder);

  const std::string out = StreamViaPrintUcs2(*v);
  const std::string fallback = StreamValueDirect(*v);

  EXPECT_EQ(out, fallback);
}

// Boundary: unsignedByte with size==0 should fall back to streaming `value`.
TEST_F(PrintUcs2Test_1380, UnsignedByteEmptyFallsBackToValueStream_1380) {
  auto v = MakeUnsignedByteValue({});
  ASSERT_NE(v.get(), nullptr);

  const std::string out = StreamViaPrintUcs2(*v);
  const std::string fallback = StreamValueDirect(*v);

  EXPECT_EQ(out, fallback);
}

// Normal/boundary: UCS-2LE bytes representing "A".
// Some builds may not have charset conversion available; accept either converted output ("A")
// or fallback to `operator<<` output.
TEST_F(PrintUcs2Test_1380, UnsignedByteUcs2leSingleCharPrintsConvertedOrFallsBack_1380) {
  // "A" in UCS-2LE: 0x41 0x00
  auto v = MakeUnsignedByteValue({0x41, 0x00});
  ASSERT_NE(v.get(), nullptr);

  const std::string out = StreamViaPrintUcs2(*v);
  const std::string fallback = StreamValueDirect(*v);
  const std::string expected = "A";

  EXPECT_TRUE(out == expected || out == fallback);
}

// Boundary: odd number of bytes should not crash.
// If conversion is available, the last odd byte is typically ignored; accept converted ("A")
// or fallback stream output.
TEST_F(PrintUcs2Test_1380, UnsignedByteOddSizeDoesNotCrashConvertedOrFallsBack_1380) {
  // "A" UCS-2LE plus an extra dangling byte.
  auto v = MakeUnsignedByteValue({0x41, 0x00, 0xFF});
  ASSERT_NE(v.get(), nullptr);

  const std::string out = StreamViaPrintUcs2(*v);
  const std::string fallback = StreamValueDirect(*v);
  const std::string expected = "A";

  EXPECT_TRUE(out == expected || out == fallback);
}

// Normal: trailing UCS-2 null terminators should not appear in converted output.
// Accept either "A" (converted) or fallback stream.
TEST_F(PrintUcs2Test_1380, UnsignedByteTrailingNullPairsTrimmedConvertedOrFallsBack_1380) {
  // "A" UCS-2LE then multiple trailing 0x00 0x00 pairs.
  auto v = MakeUnsignedByteValue({0x41, 0x00, 0x00, 0x00, 0x00, 0x00});
  ASSERT_NE(v.get(), nullptr);

  const std::string out = StreamViaPrintUcs2(*v);
  const std::string fallback = StreamValueDirect(*v);
  const std::string expected = "A";

  EXPECT_TRUE(out == expected || out == fallback);
}

// Normal: multi-character UCS-2LE ("AB").
// Accept either converted ("AB") or fallback stream.
TEST_F(PrintUcs2Test_1380, UnsignedByteMultiCharConvertedOrFallsBack_1380) {
  // "A" "B" in UCS-2LE: 41 00 42 00
  auto v = MakeUnsignedByteValue({0x41, 0x00, 0x42, 0x00});
  ASSERT_NE(v.get(), nullptr);

  const std::string out = StreamViaPrintUcs2(*v);
  const std::string fallback = StreamValueDirect(*v);
  const std::string expected = "AB";

  EXPECT_TRUE(out == expected || out == fallback);
}

// Boundary/error-ish: size==1 becomes empty after UCS-2 pairing rules; should not crash.
// Output can be empty (if conversion succeeds on empty string) or fallback.
TEST_F(PrintUcs2Test_1380, UnsignedByteSingleByteDoesNotCrashEmptyOrFallsBack_1380) {
  auto v = MakeUnsignedByteValue({0x00});
  ASSERT_NE(v.get(), nullptr);

  const std::string out = StreamViaPrintUcs2(*v);
  const std::string fallback = StreamValueDirect(*v);

  EXPECT_TRUE(out.empty() || out == fallback);
}