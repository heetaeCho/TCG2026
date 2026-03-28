// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_canonmn_int_printSi0x0017_963.cpp
//
// Unit tests for Exiv2::Internal::CanonMakerNote::printSi0x0017
// Constraints respected:
// - Black-box: no inference of internal logic beyond observable I/O.
// - Only uses public interface shown (and Exiv2 public Value suggests).
// - No private state access.

#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <limits>
#include <sstream>
#include <string>

#include <exiv2/exiv2.hpp>

// The class under test lives in canonmn_int.cpp; in Exiv2, CanonMakerNote is internal.
// Most Exiv2 builds expose Internal headers via internal includes; in the test suite,
// it's typically fine to include the internal header if available.
// If your build exposes CanonMakerNote via a different header, adjust include below.
#include "canonmn_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::Value;
using Exiv2::Value::UniquePtr;

// Helper: build a UShort value with a single element.
static UniquePtr MakeUShortValue(uint16_t v) {
  UniquePtr val = Exiv2::Value::create(Exiv2::unsignedShort);
  // Use read() with ASCII text, as Exiv2 Value supports parsing from strings.
  // This avoids relying on any internal array APIs.
  std::ostringstream oss;
  oss << v;
  val->read(oss.str());
  return val;
}

// Helper: build a value of a specific type from a string payload.
static UniquePtr MakeValue(Exiv2::TypeId type, const std::string& payload) {
  UniquePtr val = Exiv2::Value::create(type);
  val->read(payload);
  return val;
}

static std::string PrintToString(Exiv2::Internal::CanonMakerNote& mn,
                                 const Value& value,
                                 const ExifData* exif = nullptr) {
  std::ostringstream os;
  mn.printSi0x0017(os, value, exif);
  return os.str();
}

}  // namespace

// TEST_ID 963

TEST(CanonMakerNoteTest_963, TypeNotUnsignedShort_PassesThroughValue_963) {
  Exiv2::Internal::CanonMakerNote mn;

  // Use a different type than unsignedShort, e.g., unsignedLong
  auto val = MakeValue(Exiv2::unsignedLong, "12345");

  const std::string out = PrintToString(mn, *val, nullptr);

  // Observable behavior: for non-unsignedShort, it should stream "value" as-is.
  // We don't assume exact formatting; we compare against streaming the value itself.
  std::ostringstream expected;
  expected << *val;

  EXPECT_EQ(out, expected.str());
}

TEST(CanonMakerNoteTest_963, CountZero_PassesThroughValue_963) {
  Exiv2::Internal::CanonMakerNote mn;

  // Create unsignedShort but with empty payload => count() should become 0 for many Value types.
  // This test is written to be robust: we compare output to operator<< on the same Value,
  // regardless of how the Value chooses to represent an "empty" value.
  auto val = MakeValue(Exiv2::unsignedShort, "");

  const std::string out = PrintToString(mn, *val, nullptr);

  std::ostringstream expected;
  expected << *val;

  EXPECT_EQ(out, expected.str());
}

TEST(CanonMakerNoteTest_963, FormatsAsNumberWithTwoDecimals_ForTypicalInput_963) {
  Exiv2::Internal::CanonMakerNote mn;

  // Use a simple representative value.
  // We don't re-implement the algorithm; instead, we assert observable formatting properties:
  // - Output is not identical to default Value streaming (i.e., it transforms output)
  // - Output looks like a fixed-point number with exactly 2 digits after decimal
  auto val = MakeUShortValue(0);

  const std::string out = PrintToString(mn, *val, nullptr);

  std::ostringstream defaultStream;
  defaultStream << *val;

  // For a valid unsignedShort with non-zero count, observable behavior is a formatted number.
  EXPECT_NE(out, defaultStream.str());

  // Check it resembles something like "-6.00" / "0.00" etc: optional sign, digits, '.', 2 digits.
  // We avoid being too strict about leading digits to keep portability.
  ASSERT_GE(out.size(), 4u);
  const auto dotPos = out.find('.');
  ASSERT_NE(dotPos, std::string::npos);
  ASSERT_LT(dotPos + 2, out.size());
  EXPECT_TRUE(std::isdigit(static_cast<unsigned char>(out[dotPos + 1])));
  EXPECT_TRUE(std::isdigit(static_cast<unsigned char>(out[dotPos + 2])));

  // Ensure there are exactly two decimal digits (no extra trailing digits).
  // Allow possible trailing spaces? Exiv2 typically doesn't add them; still, trim right for safety.
  std::string trimmed = out;
  while (!trimmed.empty() && std::isspace(static_cast<unsigned char>(trimmed.back()))) trimmed.pop_back();
  const auto dotPos2 = trimmed.find('.');
  ASSERT_NE(dotPos2, std::string::npos);
  ASSERT_EQ(dotPos2 + 3, trimmed.size());  // ".dd" ends string
}

TEST(CanonMakerNoteTest_963, UsesExifDataPointer_NullptrAccepted_963) {
  Exiv2::Internal::CanonMakerNote mn;

  auto val = MakeUShortValue(16);

  // Should not crash and should produce consistent output whether ExifData is null or non-null
  // (function signature includes ExifData*, but behavior may not depend on it).
  const std::string outNull = PrintToString(mn, *val, nullptr);

  ExifData exif;
  const std::string outNonNull = PrintToString(mn, *val, &exif);

  EXPECT_EQ(outNull, outNonNull);
}

TEST(CanonMakerNoteTest_963, Boundary_UShortMax_ProducesFiniteNumericText_963) {
  Exiv2::Internal::CanonMakerNote mn;

  auto val = MakeUShortValue(std::numeric_limits<uint16_t>::max());

  const std::string out = PrintToString(mn, *val, nullptr);

  // Output should still be a parseable finite number string (no NaN/inf).
  // We don't assume exact value; only observable that it is numeric and finite.
  char* end = nullptr;
  const double parsed = std::strtod(out.c_str(), &end);

  ASSERT_NE(end, out.c_str());           // parsed something
  ASSERT_EQ(*end, '\0');                 // consumed all (no junk)
  EXPECT_TRUE(std::isfinite(parsed));    // not inf/nan
}

TEST(CanonMakerNoteTest_963, Boundary_UShortOne_StillTwoDecimals_963) {
  Exiv2::Internal::CanonMakerNote mn;

  auto val = MakeUShortValue(1);

  const std::string out = PrintToString(mn, *val, nullptr);

  // Must contain a decimal point and exactly two digits after it (post-trim).
  std::string trimmed = out;
  while (!trimmed.empty() && std::isspace(static_cast<unsigned char>(trimmed.back()))) trimmed.pop_back();

  const auto dotPos = trimmed.find('.');
  ASSERT_NE(dotPos, std::string::npos);
  ASSERT_LT(dotPos + 2, trimmed.size());
  EXPECT_TRUE(std::isdigit(static_cast<unsigned char>(trimmed[dotPos + 1])));
  EXPECT_TRUE(std::isdigit(static_cast<unsigned char>(trimmed[dotPos + 2])));
  EXPECT_EQ(dotPos + 3, trimmed.size());
}

TEST(CanonMakerNoteTest_963, MultipleCalls_DoNotAccumulateIntoStreamUnexpectedly_963) {
  Exiv2::Internal::CanonMakerNote mn;

  auto val = MakeUShortValue(8);

  std::ostringstream os;
  mn.printSi0x0017(os, *val, nullptr);
  const std::string first = os.str();

  // Call again on a new stream should yield same output text for same input
  std::ostringstream os2;
  mn.printSi0x0017(os2, *val, nullptr);
  const std::string second = os2.str();

  EXPECT_EQ(first, second);
}