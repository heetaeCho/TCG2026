// File: test_tags_int_printValue_1372.cpp
// TEST_ID: 1372
//
// Unit tests for:
//   Exiv2::Internal::printValue(std::ostream&, const Value&, const ExifData*)
//
// Constraints respected:
// - Treat implementation as a black box (no inference beyond observable behavior).
// - Only validate via public/observable behavior: stream output and returned stream reference.
// - No private state access.
// - Use gmock only if needed (not needed here).

#include <gtest/gtest.h>

#include <sstream>
#include <string>

// Exiv2 headers (paths may vary by project layout)
#include <exiv2/exiv2.hpp>

// The function under test is in internal namespace and implemented in tags_int.cpp.
// In many Exiv2 setups, it is declared in an internal header; include if available.
// If your build already exposes it via other includes, this is fine.
// If it is not visible, add the correct internal header include in your tree.
#include "tags_int.hpp"

namespace {

// Helper: create a Value instance via a known public derived type.
// We only rely on the public Value API and stream insertion behavior.
static Exiv2::Value::UniquePtr MakeAsciiValue(const std::string& s) {
  auto v = Exiv2::Value::create(Exiv2::asciiString);
  EXPECT_NE(v.get(), nullptr);
  if (v) {
    v->read(s);
  }
  return v;
}

}  // namespace

// -----------------------
// Normal operation
// -----------------------

TEST(PrintValueTest_1372, WritesValueToStream_1372) {
  auto v = MakeAsciiValue("hello");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  const Exiv2::ExifData* exif = nullptr;

  // Act
  Exiv2::Internal::printValue(os, *v, exif);

  // Assert (observable behavior: output equals streaming the value itself)
  std::ostringstream expected;
  expected << *v;
  EXPECT_EQ(os.str(), expected.str());
}

TEST(PrintValueTest_1372, ReturnsSameStreamReference_1372) {
  auto v = MakeAsciiValue("x");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  std::ostream& ref = Exiv2::Internal::printValue(os, *v, nullptr);

  // Observable: function returns the same stream object passed in.
  EXPECT_EQ(&ref, &os);
}

// -----------------------
// Boundary conditions
// -----------------------

TEST(PrintValueTest_1372, EmptyValueProducesSameAsOperatorInsertion_1372) {
  // Empty ASCII value (boundary: empty content)
  auto v = MakeAsciiValue("");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  Exiv2::Internal::printValue(os, *v, nullptr);

  std::ostringstream expected;
  expected << *v;
  EXPECT_EQ(os.str(), expected.str());
}

TEST(PrintValueTest_1372, LongValueProducesSameAsOperatorInsertion_1372) {
  // Boundary: very long input string
  std::string longStr(10'000, 'a');
  auto v = MakeAsciiValue(longStr);
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  Exiv2::Internal::printValue(os, *v, nullptr);

  std::ostringstream expected;
  expected << *v;
  EXPECT_EQ(os.str(), expected.str());
}

// -----------------------
// Exceptional / error cases (observable)
// -----------------------

TEST(PrintValueTest_1372, IgnoresExifDataPointerWhenNull_1372) {
  // The interface accepts ExifData* which may be null.
  // Observable requirement: should still print like operator<< does.
  auto v = MakeAsciiValue("with-null-exif");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  Exiv2::Internal::printValue(os, *v, nullptr);

  std::ostringstream expected;
  expected << *v;
  EXPECT_EQ(os.str(), expected.str());
}

TEST(PrintValueTest_1372, PreservesStreamFailureState_1372) {
  // Observable error-ish behavior: if stream is already in a failed state,
  // insertion should not change output and should keep failbit set.
  auto v = MakeAsciiValue("data");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  os.setstate(std::ios::failbit);  // induce failure state

  Exiv2::Internal::printValue(os, *v, nullptr);

  EXPECT_TRUE(os.fail());
  // With failbit set, most stream insertions won't write anything.
  // We only assert it matches what operator<< does under same condition.
  std::ostringstream expected;
  expected.setstate(std::ios::failbit);
  expected << *v;
  EXPECT_EQ(os.str(), expected.str());
}

// -----------------------
// External interactions
// -----------------------
// There are no external collaborators / callbacks in this interface,
// so no mocks are applicable. The "interaction" is the stream output,
// already validated above.