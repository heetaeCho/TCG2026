// File: test_panasonicmn_int_print0x0033_710.cpp
// Unit tests for ./TestProjects/exiv2/src/panasonicmn_int.cpp
//
// Constraints respected:
// - Treat implementation as a black box (no re-implementation assumptions beyond visible behavior).
// - Test only observable behavior via public interface (ostream output).
// - No private state access.

#include <gtest/gtest.h>

#include <ostream>
#include <sstream>
#include <string>

// Exiv2 headers (adjust include paths if your test harness uses different layout)
#include "exif.hpp"          // Exiv2::ExifData
#include "value.hpp"         // Exiv2::Value, Exiv2::Value::UniquePtr
#include "types.hpp"         // Exiv2::TypeId (if needed)

// Internal header / implementation access.
// If your build exposes an internal header for PanasonicMakerNote, include it instead.
// In some Exiv2 test setups, internal classes are available via *_int.hpp headers.
#include "panasonicmn_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::Value;

class PanasonicMakerNoteTest_710 : public ::testing::Test {
 protected:
  Exiv2::Internal::PanasonicMakerNote uut_;
  ExifData exif_;  // passed as pointer; not required to be populated for these tests

  static Value::UniquePtr MakeAsciiValue(const std::string& s) {
    // We only rely on Value API to create a Value that prints as the string we set.
    // Using ASCII is the most common for date-time strings in Exiv2 tests.
    Value::UniquePtr v = Value::create(Exiv2::asciiString);
    v->read(s);
    return v;
  }
};

TEST_F(PanasonicMakerNoteTest_710, PrintsNotSetForSentinelString_710) {
  auto v = MakeAsciiValue("9999:99:99 00:00:00");

  std::ostringstream os;
  uut_.print0x0033(os, *v, &exif_);

  // Observable behavior: output is "not set" for the sentinel.
  EXPECT_EQ("not set", os.str());
}

TEST_F(PanasonicMakerNoteTest_710, PrintsOriginalValueForNormalDateTime_710) {
  auto v = MakeAsciiValue("2020:01:02 03:04:05");

  std::ostringstream os;
  uut_.print0x0033(os, *v, &exif_);

  // Observable behavior: output equals the value's stream representation.
  // For an ASCII Value created via read(string), this should match the same string.
  EXPECT_EQ("2020:01:02 03:04:05", os.str());
}

TEST_F(PanasonicMakerNoteTest_710, PrintsOriginalValueForEmptyString_710) {
  auto v = MakeAsciiValue("");

  std::ostringstream os;
  uut_.print0x0033(os, *v, &exif_);

  // Boundary: empty string should NOT map to "not set" (only the exact sentinel does).
  EXPECT_EQ("", os.str());
}

TEST_F(PanasonicMakerNoteTest_710, PrintsOriginalValueForNearSentinelButDifferent_710) {
  // Boundary: almost-sentinel but not exact should be printed as-is.
  auto v = MakeAsciiValue("9999:99:99 00:00:01");

  std::ostringstream os;
  uut_.print0x0033(os, *v, &exif_);

  EXPECT_EQ("9999:99:99 00:00:01", os.str());
}

TEST_F(PanasonicMakerNoteTest_710, AppendsToExistingStreamContent_710) {
  auto v = MakeAsciiValue("2021:12:31 23:59:59");

  std::ostringstream os;
  os << "prefix:";
  uut_.print0x0033(os, *v, &exif_);

  // Stream interaction: should append to the existing stream content.
  EXPECT_EQ("prefix:2021:12:31 23:59:59", os.str());
}

TEST_F(PanasonicMakerNoteTest_710, ReturnsSameStreamReference_710) {
  auto v = MakeAsciiValue("2022:02:02 02:02:02");

  std::ostringstream os;
  std::ostream& ret = uut_.print0x0033(os, *v, &exif_);

  // Observable behavior: returns the same stream object passed in.
  EXPECT_EQ(&os, &ret);
}

TEST_F(PanasonicMakerNoteTest_710, AcceptsNullExifDataPointer_710) {
  auto v = MakeAsciiValue("2019:03:04 05:06:07");

  std::ostringstream os;
  // Exceptional-ish / robustness: interface allows nullptr; behavior should remain observable.
  uut_.print0x0033(os, *v, nullptr);

  EXPECT_EQ("2019:03:04 05:06:07", os.str());
}

}  // namespace