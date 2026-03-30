// ***************************************************************** -*- C++ -*-
// Unit tests for: Exiv2::Internal::MinoltaMakerNote::printMinoltaExposureTimeStd
// File under test: ./TestProjects/exiv2/src/minoltamn_int.cpp
//
// Constraints respected:
// - Black-box testing based only on public interface & observable output.
// - No private state access.
// - Boundary + error-ish (observable) cases included.
//
// TEST_ID: 1001
// *****************************************************************

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>

// Include the Exiv2 internal header(s) as used by your codebase.
// Adjust include path if needed.
#include "minoltamn_int.hpp"

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

namespace {

using Exiv2::ExifData;
using Exiv2::Internal::MinoltaMakerNote;

// Helper: create a Value holding a signed integer (int64) using Exiv2's public API.
static Exiv2::Value::UniquePtr MakeInt64Value(const int64_t v) {
  auto val = Exiv2::Value::create(Exiv2::signedLong8);
  // setValue(string) is a public, observable way to populate values across Exiv2 value types.
  // For signedLong8, the string form should parse as an int64.
  val->setValue(std::to_string(v));
  return val;
}

class MinoltaMakerNoteTest_1001 : public ::testing::Test {
 protected:
  MinoltaMakerNote uut_;
  ExifData exif_;  // The interface accepts ExifData* but the implementation ignores it (black-box safe).
};

TEST_F(MinoltaMakerNoteTest_1001, PrintsComputedValueForZero_1001) {
  auto value = MakeInt64Value(0);

  std::ostringstream oss;
  ASSERT_NO_THROW(uut_.printMinoltaExposureTimeStd(oss, *value, &exif_));

  // Observable behavior from implementation: os << (toInt64()/8) - 6
  EXPECT_EQ(oss.str(), "-6");
}

TEST_F(MinoltaMakerNoteTest_1001, PrintsComputedValueForPositiveMultipleOfEight_1001) {
  auto value = MakeInt64Value(8);  // 8/8=1, 1-6=-5

  std::ostringstream oss;
  uut_.printMinoltaExposureTimeStd(oss, *value, &exif_);

  EXPECT_EQ(oss.str(), "-5");
}

TEST_F(MinoltaMakerNoteTest_1001, PrintsComputedValueForNegativeMultipleOfEight_1001) {
  auto value = MakeInt64Value(-8);  // -8/8=-1, -1-6=-7

  std::ostringstream oss;
  uut_.printMinoltaExposureTimeStd(oss, *value, &exif_);

  EXPECT_EQ(oss.str(), "-7");
}

TEST_F(MinoltaMakerNoteTest_1001, UsesTruncatingDivisionTowardZeroForNonMultipleOfEight_1001) {
  // In C++, integer division truncates toward zero. This is observable via output.
  // 15/8 = 1 -> 1-6 = -5
  auto value = MakeInt64Value(15);

  std::ostringstream oss;
  uut_.printMinoltaExposureTimeStd(oss, *value, &exif_);

  EXPECT_EQ(oss.str(), "-5");
}

TEST_F(MinoltaMakerNoteTest_1001, UsesTruncatingDivisionTowardZeroForNegativeNonMultipleOfEight_1001) {
  // -15/8 = -1 (toward zero) -> -1-6 = -7
  auto value = MakeInt64Value(-15);

  std::ostringstream oss;
  uut_.printMinoltaExposureTimeStd(oss, *value, &exif_);

  EXPECT_EQ(oss.str(), "-7");
}

TEST_F(MinoltaMakerNoteTest_1001, AppendsToExistingStreamContent_1001) {
  auto value = MakeInt64Value(0);

  std::ostringstream oss;
  oss << "prefix:";
  uut_.printMinoltaExposureTimeStd(oss, *value, &exif_);

  EXPECT_EQ(oss.str(), "prefix:-6");
}

TEST_F(MinoltaMakerNoteTest_1001, ReturnsSameOstreamReference_1001) {
  auto value = MakeInt64Value(8);

  std::ostringstream oss;
  std::ostream& ret = uut_.printMinoltaExposureTimeStd(oss, *value, &exif_);

  // Observable: returned reference should be the same stream object.
  EXPECT_EQ(&ret, static_cast<std::ostream*>(&oss));
  EXPECT_EQ(oss.str(), "-5");
}

TEST_F(MinoltaMakerNoteTest_1001, AcceptsNullExifDataPointer_1001) {
  auto value = MakeInt64Value(0);

  std::ostringstream oss;
  ASSERT_NO_THROW(uut_.printMinoltaExposureTimeStd(oss, *value, nullptr));
  EXPECT_EQ(oss.str(), "-6");
}

TEST_F(MinoltaMakerNoteTest_1001, HandlesLargePositiveInt64WithoutThrowing_1001) {
  // Use a value that avoids overflow in (v/8) - 6 within int64:
  // v/8 <= INT64_MAX, subtracting 6 stays in range if v/8 >= INT64_MIN+6 (true for positive).
  const int64_t v = std::numeric_limits<int64_t>::max();

  auto value = MakeInt64Value(v);

  std::ostringstream oss;
  ASSERT_NO_THROW(uut_.printMinoltaExposureTimeStd(oss, *value, &exif_));

  // Compute expected using the same well-defined integer operations on int64.
  const int64_t expected = (v / 8) - 6;
  EXPECT_EQ(oss.str(), std::to_string(expected));
}

TEST_F(MinoltaMakerNoteTest_1001, HandlesLargeNegativeInt64WithoutThrowing_1001) {
  // Use a value where (v/8) - 6 remains representable.
  // For INT64_MIN, v/8 is still in-range, but (v/8) - 6 could underflow.
  // So we choose a safer large negative that won't underflow when subtracting 6.
  const int64_t v = std::numeric_limits<int64_t>::min() + 64;  // padding

  auto value = MakeInt64Value(v);

  std::ostringstream oss;
  ASSERT_NO_THROW(uut_.printMinoltaExposureTimeStd(oss, *value, &exif_));

  const int64_t expected = (v / 8) - 6;
  EXPECT_EQ(oss.str(), std::to_string(expected));
}

}  // namespace