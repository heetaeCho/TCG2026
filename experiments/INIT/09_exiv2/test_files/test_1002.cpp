// SPDX-License-Identifier: GPL-2.0-or-later
//
// File: test_minoltamn_int_printMinoltaFNumberStd_1002.cpp
//
// Unit tests for:
//   Exiv2::Internal::MinoltaMakerNote::printMinoltaFNumberStd(std::ostream&, const Value&, const ExifData*)
//
// Constraints respected:
// - Treat implementation as a black box (test only observable output).
// - Do not access private state.
// - No internal logic re-implementation beyond deriving expected values from the public contract
//   implied by the provided interface behavior (stream output based on Value::toInt64()).

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <sstream>
#include <string>

// Exiv2 headers (adjust include paths to match your test build environment)
#include "exif.hpp"          // Exiv2::ExifData
#include "value.hpp"         // Exiv2::Value / Exiv2::Value::UniquePtr / Exiv2::ValueType
#include "minoltamn_int.hpp" // Exiv2::Internal::MinoltaMakerNote

namespace {

// Helper: create a Value holding a signed integer (SLong / int32) and set it.
static Exiv2::Value::UniquePtr makeSLongValue(int32_t v) {
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::signedLong);  // ValueTypeId
  val->read(std::to_string(v));
  return val;
}

// Helper: create a Value holding a signed 64-bit integer (SLong8) if supported;
// if not supported in this Exiv2 version, fall back to signedLong with clamping via read.
// (Tests will still exercise the method; boundary cases for 64-bit are best-effort.)
static Exiv2::Value::UniquePtr makeSLong8ValueBestEffort(int64_t v) {
  Exiv2::Value::UniquePtr val;
  try {
    val = Exiv2::Value::create(Exiv2::signedLong8);  // may not exist in older Exiv2
  } catch (...) {
    val = Exiv2::Value::create(Exiv2::signedLong);
  }
  val->read(std::to_string(v));
  return val;
}

class MinoltaMakerNotePrintMinoltaFNumberStdTest_1002 : public ::testing::Test {
 protected:
  Exiv2::Internal::MinoltaMakerNote mn_;
  Exiv2::ExifData exif_;  // not used by the method (per signature), but passed for completeness
};

}  // namespace

// --------------------------- Normal operation ---------------------------

TEST_F(MinoltaMakerNotePrintMinoltaFNumberStdTest_1002, WritesComputedValueForTypicalInput_1002) {
  // Typical value that divides by 8 evenly.
  auto value = makeSLongValue(16);  // 16/8=2; output is 2-1 => "1"
  std::ostringstream os;

  std::ostream& ret = mn_.printMinoltaFNumberStd(os, *value, &exif_);

  EXPECT_EQ(&ret, &os);
  EXPECT_EQ(os.str(), "1");
}

TEST_F(MinoltaMakerNotePrintMinoltaFNumberStdTest_1002, WritesNegativeResultWhenInputIsZero_1002) {
  // Boundary-ish: 0/8=0; output is 0-1 => "-1"
  auto value = makeSLongValue(0);
  std::ostringstream os;

  mn_.printMinoltaFNumberStd(os, *value, &exif_);

  EXPECT_EQ(os.str(), "-1");
}

TEST_F(MinoltaMakerNotePrintMinoltaFNumberStdTest_1002, AppendsToExistingStreamContent_1002) {
  auto value = makeSLongValue(24);  // 24/8=3; 3-1 => "2"
  std::ostringstream os;
  os << "prefix:";

  mn_.printMinoltaFNumberStd(os, *value, &exif_);

  EXPECT_EQ(os.str(), "prefix:2");
}

// --------------------------- Boundary conditions ---------------------------

TEST_F(MinoltaMakerNotePrintMinoltaFNumberStdTest_1002, UsesTruncatingDivisionForNonMultipleOfEight_1002) {
  // Observable behavior: integer division truncation through toInt64()/8.
  // 15/8 => 1 (truncated); 1-1 => "0"
  auto value = makeSLongValue(15);
  std::ostringstream os;

  mn_.printMinoltaFNumberStd(os, *value, &exif_);

  EXPECT_EQ(os.str(), "0");
}

TEST_F(MinoltaMakerNotePrintMinoltaFNumberStdTest_1002, HandlesNegativeValues_1002) {
  // -8/8 => -1; -1-1 => "-2"
  auto value = makeSLongValue(-8);
  std::ostringstream os;

  mn_.printMinoltaFNumberStd(os, *value, &exif_);

  EXPECT_EQ(os.str(), "-2");
}

TEST_F(MinoltaMakerNotePrintMinoltaFNumberStdTest_1002, AcceptsNullExifDataPointer_1002) {
  // Signature allows nullptr; ensure no crash and output is still produced.
  auto value = makeSLongValue(16);
  std::ostringstream os;

  mn_.printMinoltaFNumberStd(os, *value, nullptr);

  EXPECT_EQ(os.str(), "1");
}

// --------------------------- Exceptional / error cases ---------------------------

TEST_F(MinoltaMakerNotePrintMinoltaFNumberStdTest_1002, PropagatesStreamFailureState_1002) {
  // If the stream is already in a bad state, insertion should not change content.
  // We only check observable stream state and content.
  auto value = makeSLongValue(16);

  std::ostringstream os;
  os.setstate(std::ios::badbit);

  mn_.printMinoltaFNumberStd(os, *value, &exif_);

  EXPECT_TRUE(os.bad());
  // Content is unspecified with badbit; but most streams won't write.
  // We check it stays empty as an observable, conservative expectation.
  EXPECT_TRUE(os.str().empty());
}

TEST_F(MinoltaMakerNotePrintMinoltaFNumberStdTest_1002, LargeMagnitudeInputProducesSomeOutput_1002) {
  // Best-effort boundary: very large 64-bit input (if supported by Value type).
  // We avoid asserting the exact number if Value implementation clamps/changes parsing;
  // instead assert: method returns same stream and writes a non-empty sequence.
  auto value = makeSLong8ValueBestEffort(std::numeric_limits<int64_t>::max());
  std::ostringstream os;

  std::ostream& ret = mn_.printMinoltaFNumberStd(os, *value, &exif_);

  EXPECT_EQ(&ret, &os);
  EXPECT_FALSE(os.str().empty());
}