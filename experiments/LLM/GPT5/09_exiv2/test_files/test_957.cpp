// ----------------------------------------------------------------------------
// Unit Tests for CanonMakerNote::printSi0x000c (TEST_ID: 957)
// File under test: ./TestProjects/exiv2/src/canonmn_int.cpp
// ----------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <cstdint>
#include <sstream>
#include <string>

#include "canonmn_int.hpp"  // CanonMakerNote (and Value / ExifData in Exiv2)

// These tests treat CanonMakerNote as a black box and validate only observable
// behavior via the public interface: the returned stream and its textual output.

namespace {

// Helper: call printSi0x000c and return the produced string.
static std::string CallPrint(Exiv2::Internal::CanonMakerNote& mn, const Exiv2::Value& v) {
  std::ostringstream oss;
  // Interface takes ExifData* but does not require it for observable output in this function.
  mn.printSi0x000c(oss, v, nullptr);
  return oss.str();
}

// Helper: verify returned ostream& is the same object passed in.
static bool ReturnsSameStream(Exiv2::Internal::CanonMakerNote& mn, const Exiv2::Value& v) {
  std::ostringstream oss;
  std::ostream& ret = mn.printSi0x000c(oss, v, nullptr);
  return &ret == static_cast<std::ostream*>(&oss);
}

}  // namespace

class CanonMakerNoteTest_957 : public ::testing::Test {
 protected:
  Exiv2::Internal::CanonMakerNote mn_;
};

TEST_F(CanonMakerNoteTest_957, ReturnsSameStreamReference_957) {
  // Normal operation: method should return the same stream reference for chaining.
  Exiv2::Value v;  // default-constructed; we don't assume its value, only stream reference behavior.
  EXPECT_TRUE(ReturnsSameStream(mn_, v));
}

TEST_F(CanonMakerNoteTest_957, ZeroValuePrintsDoubleDash_957) {
  // Normal operation / special case: 0 prints "--".
  Exiv2::Value v;
  // We only rely on Value interface to set an integer-ish content. Most Exiv2 Value
  // types support read("0"). If this fails in your build, replace with the correct
  // concrete Value type used in your codebase (e.g., Exiv2::Value::UniquePtr with
  // Exiv2::Value::create(Exiv2::unsignedShort) / etc.).
  ASSERT_NO_THROW(v.read("0"));
  EXPECT_EQ(CallPrint(mn_, v), "--");
}

TEST_F(CanonMakerNoteTest_957, NonZeroValueIncludesCelsiusSuffix_957) {
  // Normal operation: non-zero produces a temperature string ending with " °C".
  Exiv2::Value v;
  ASSERT_NO_THROW(v.read("1"));
  const std::string out = CallPrint(mn_, v);
  ASSERT_GE(out.size(), std::string(" °C").size());
  EXPECT_EQ(out.substr(out.size() - std::string(" °C").size()), " °C");
}

TEST_F(CanonMakerNoteTest_957, NonZeroValueProducesNumberAndUnit_957) {
  // Normal operation: output should look like "<number> °C" for non-zero inputs.
  Exiv2::Value v;
  ASSERT_NO_THROW(v.read("200"));
  const std::string out = CallPrint(mn_, v);

  // Should contain the unit with a space before it.
  const std::string unit = " °C";
  const auto pos = out.rfind(unit);
  ASSERT_NE(pos, std::string::npos);

  // Prefix (before unit) should be parseable as an integer (optionally negative).
  const std::string numPart = out.substr(0, pos);
  ASSERT_FALSE(numPart.empty());

  // Validate numeric form without asserting the exact internal conversion formula.
  // Accept optional leading '-' and then digits.
  size_t i = 0;
  if (numPart[0] == '-') i = 1;
  ASSERT_LT(i, numPart.size());
  for (; i < numPart.size(); ++i) {
    ASSERT_TRUE(numPart[i] >= '0' && numPart[i] <= '9') << "Non-digit in output: " << out;
  }
}

TEST_F(CanonMakerNoteTest_957, BoundaryNonZeroSmallestPositive_957) {
  // Boundary: smallest positive value (1) should not print "--" and should include unit.
  Exiv2::Value v;
  ASSERT_NO_THROW(v.read("1"));
  const std::string out = CallPrint(mn_, v);
  EXPECT_NE(out, "--");
  EXPECT_NE(out.find("°C"), std::string::npos);
}

TEST_F(CanonMakerNoteTest_957, BoundaryLargeValueDoesNotCrashAndPrintsUnit_957) {
  // Boundary: large value should not crash and should still include the unit.
  // We avoid assuming exact numeric result; just check it produces something sensible.
  Exiv2::Value v;
  ASSERT_NO_THROW(v.read("9223372036854775807"));  // int64 max as text
  const std::string out = CallPrint(mn_, v);
  EXPECT_NE(out, "--");
  EXPECT_NE(out.find("°C"), std::string::npos);
}

TEST_F(CanonMakerNoteTest_957, NegativeValueDoesNotCrashAndPrintsUnit_957) {
  // Exceptional/boundary: negative values (if representable by Value) should be handled.
  // We only verify it doesn't produce "--" (since toInt64()!=0) and includes unit.
  Exiv2::Value v;
  ASSERT_NO_THROW(v.read("-1"));
  const std::string out = CallPrint(mn_, v);
  EXPECT_NE(out, "--");
  EXPECT_NE(out.find("°C"), std::string::npos);
}

TEST_F(CanonMakerNoteTest_957, NullExifDataPointerIsAccepted_957) {
  // Boundary: ExifData* is nullable at call-site; verify call works with nullptr.
  Exiv2::Value v;
  ASSERT_NO_THROW(v.read("1"));
  std::ostringstream oss;
  EXPECT_NO_THROW(mn_.printSi0x000c(oss, v, nullptr));
  EXPECT_FALSE(oss.str().empty());
}

TEST_F(CanonMakerNoteTest_957, StreamChainingAppendsToExistingStream_957) {
  // Normal operation: should append to existing stream contents and allow chaining.
  Exiv2::Value v;
  ASSERT_NO_THROW(v.read("1"));

  std::ostringstream oss;
  oss << "prefix:";
  std::ostream& ret = mn_.printSi0x000c(oss, v, nullptr);
  ret << ":suffix";

  const std::string out = oss.str();
  EXPECT_TRUE(out.rfind("prefix:", 0) == 0);  // starts with "prefix:"
  EXPECT_NE(out.find(":suffix"), std::string::npos);
}

TEST_F(CanonMakerNoteTest_957, InvalidValueContentThrowsOrProducesOutput_957) {
  // Exceptional case: If Value cannot parse non-numeric content, it may throw on read().
  // If it does not throw, printSi0x000c should still be callable without crashing.
  Exiv2::Value v;
  try {
    v.read("not-a-number");
  } catch (...) {
    SUCCEED() << "Value::read rejected non-numeric input (acceptable).";
    return;
  }

  // If read succeeded, printing should not crash; output should be non-empty.
  std::ostringstream oss;
  EXPECT_NO_THROW(mn_.printSi0x000c(oss, v, nullptr));
  EXPECT_FALSE(oss.str().empty());
}