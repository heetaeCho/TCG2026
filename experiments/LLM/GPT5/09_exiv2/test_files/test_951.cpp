// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_canonmn_int_printCsLens_951.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "canonmn_int.hpp"

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

namespace {

using Exiv2::TypeId;
using Exiv2::Value;

std::string StreamValue(const Value& v) {
  std::ostringstream oss;
  oss << v;
  return oss.str();
}

Value::UniquePtr MakeValue(TypeId type, const std::string& text) {
  Value::UniquePtr v = Value::create(type);
  EXPECT_NE(v.get(), nullptr);
  v->read(text);
  return v;
}

std::string PrintCsLensToString(Value& v) {
  Exiv2::Internal::CanonMakerNote mn;
  std::ostringstream oss;
  mn.printCsLens(oss, v, nullptr);
  return oss.str();
}

}  // namespace

// The TEST_ID is 951

TEST(CanonMakerNoteTest_951, ReturnsParenthesizedValueWhenCountLessThan3_951) {
  auto v = MakeValue(Exiv2::unsignedShort, "1 2");  // count == 2
  const std::string valueStr = StreamValue(*v);

  const std::string out = PrintCsLensToString(*v);

  EXPECT_EQ(out, "(" + valueStr + ")");
}

TEST(CanonMakerNoteTest_951, ReturnsParenthesizedValueWhenTypeIsNotUnsignedShort_951) {
  auto v = MakeValue(Exiv2::unsignedLong, "1 2 3");  // count == 3, wrong type
  const std::string valueStr = StreamValue(*v);

  const std::string out = PrintCsLensToString(*v);

  EXPECT_EQ(out, "(" + valueStr + ")");
}

TEST(CanonMakerNoteTest_951, ReturnsValueDirectlyWhenScaleFactorIsZero_951) {
  auto v = MakeValue(Exiv2::unsignedShort, "10 20 0");  // fu == 0
  const std::string valueStr = StreamValue(*v);

  const std::string out = PrintCsLensToString(*v);

  EXPECT_EQ(out, valueStr);
}

TEST(CanonMakerNoteTest_951, PrintsSingleLengthWhenBothLensValuesMatch_951) {
  // len1 = 500 / 10 = 50.0, len2 = 500 / 10 = 50.0
  auto v = MakeValue(Exiv2::unsignedShort, "500 500 10");

  const std::string out = PrintCsLensToString(*v);

  EXPECT_EQ(out, "50.0 mm");
}

TEST(CanonMakerNoteTest_951, PrintsRangeWhenLensValuesDiffer_951) {
  // len1 = 500 / 10 = 50.0, len2 = 200 / 10 = 20.0
  auto v = MakeValue(Exiv2::unsignedShort, "500 200 10");

  const std::string out = PrintCsLensToString(*v);

  EXPECT_EQ(out, "20.0 - 50.0 mm");
}

TEST(CanonMakerNoteTest_951, IgnoresExtraValuesBeyondThirdElement_951) {
  // Same as the differing case, but with extra trailing element(s).
  auto v = MakeValue(Exiv2::unsignedShort, "500 200 10 999");

  const std::string out = PrintCsLensToString(*v);

  EXPECT_EQ(out, "20.0 - 50.0 mm");
}

TEST(CanonMakerNoteTest_951, HandlesLargeUnsignedShortValuesAsBoundary_951) {
  // len1 = len2 = 65535 / 1 = 65535.0
  auto v = MakeValue(Exiv2::unsignedShort, "65535 65535 1");

  const std::string out = PrintCsLensToString(*v);

  EXPECT_EQ(out, "65535.0 mm");
}