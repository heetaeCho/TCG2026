// SPDX-License-Identifier: GPL-2.0-or-later
// Tests for Exiv2::Internal::CanonMakerNote::printFiFocusDistance
// File under test: ./TestProjects/exiv2/src/canonmn_int.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <vector>

#include "exiv2/exiv2.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::Internal::CanonMakerNote;
using Exiv2::Value;
using Exiv2::ValueType;
using Exiv2::signedShort;

class CanonMakerNotePrintFiFocusDistanceTest_965 : public ::testing::Test {
 protected:
  CanonMakerNote sut_;
  ExifData exif_;  // not used by implementation, but passed for interface completeness
};

static std::string CallPrint(CanonMakerNote& sut, const Value& v, const ExifData* exif) {
  std::ostringstream os;
  sut.printFiFocusDistance(os, v, exif);
  return os.str();
}

TEST_F(CanonMakerNotePrintFiFocusDistanceTest_965, NonSignedShortTypeStreamsValue_965) {
  // When typeId != signedShort, it should stream `value` as-is.
  Exiv2::UShortValue v;
  v.read("123");  // count() should be > 0

  const std::string out = CallPrint(sut_, v, &exif_);

  std::ostringstream expected;
  expected << v;
  EXPECT_EQ(out, expected.str());
}

TEST_F(CanonMakerNotePrintFiFocusDistanceTest_965, SignedShortWithZeroCountStreamsValue_965) {
  // When count() == 0, it should stream `value` as-is.
  Exiv2::SShortValue v;
  // Do not read any data -> keep count() == 0.

  ASSERT_EQ(v.typeId(), signedShort);
  ASSERT_EQ(v.count(), 0U);

  const std::string out = CallPrint(sut_, v, &exif_);

  std::ostringstream expected;
  expected << v;
  EXPECT_EQ(out, expected.str());
}

TEST_F(CanonMakerNotePrintFiFocusDistanceTest_965, SignedShortMinusOnePrintsInfinite_965) {
  Exiv2::SShortValue v;
  v.read("-1");
  ASSERT_EQ(v.typeId(), signedShort);
  ASSERT_GT(v.count(), 0U);

  const std::string out = CallPrint(sut_, v, &exif_);
  EXPECT_EQ(out, "Infinite");
}

TEST_F(CanonMakerNotePrintFiFocusDistanceTest_965, SignedShortZeroPrintsZeroMetersWithTwoDecimals_965) {
  Exiv2::SShortValue v;
  v.read("0");

  const std::string out = CallPrint(sut_, v, &exif_);
  EXPECT_EQ(out, "0.00 m");
}

TEST_F(CanonMakerNotePrintFiFocusDistanceTest_965, SignedShortPositiveValueFormatsMetersWithTwoDecimals_965) {
  // 1234 -> 12.34 m
  Exiv2::SShortValue v;
  v.read("1234");

  const std::string out = CallPrint(sut_, v, &exif_);
  EXPECT_EQ(out, "12.34 m");
}

TEST_F(CanonMakerNotePrintFiFocusDistanceTest_965, SignedShortValueRoundsToTwoDecimals_965) {
  // 1 -> 0.01 m
  Exiv2::SShortValue v;
  v.read("1");

  const std::string out = CallPrint(sut_, v, &exif_);
  EXPECT_EQ(out, "0.01 m");
}

TEST_F(CanonMakerNotePrintFiFocusDistanceTest_965, AcceptsNullExifDataPointer_965) {
  // ExifData* is allowed to be null (observable: should not crash and should still format).
  Exiv2::SShortValue v;
  v.read("200");  // 2.00 m

  const std::string out = CallPrint(sut_, v, nullptr);
  EXPECT_EQ(out, "2.00 m");
}

TEST_F(CanonMakerNotePrintFiFocusDistanceTest_965, SignedShortWithMultipleValuesUsesFirstToInt64_965) {
  // Observable behavior: implementation calls value.toInt64() (single number result).
  // We only assert output equals what the same Value would produce when passed through the function.
  Exiv2::SShortValue v;
  v.read("300 400");  // count() > 0

  const std::string out = CallPrint(sut_, v, &exif_);

  // We can at least validate it's not the raw streaming (since typeId==signedShort and count>0),
  // and that it ends with " m" (unless it were -1, which it isn't).
  EXPECT_FALSE(out.empty());
  EXPECT_NE(out, (std::ostringstream{} << v).str());
  EXPECT_TRUE(out.size() >= 2 && out.find(" m") != std::string::npos);
}

}  // namespace