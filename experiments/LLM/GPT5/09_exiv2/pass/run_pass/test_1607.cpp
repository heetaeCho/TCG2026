// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_sonymn_int_printLensSpec_1607.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

// Internal header (part of Exiv2 codebase)
#include "sonymn_int.hpp"

#include <sstream>
#include <string>

namespace {

using Exiv2::ExifData;
using Exiv2::Internal::SonyMakerNote;
using Exiv2::Value;
using Exiv2::unsignedByte;

Value::UniquePtr MakeUByteValueFromList(const std::initializer_list<int>& bytes) {
  auto v = Value::create(unsignedByte);
  std::ostringstream os;
  bool first = true;
  for (int b : bytes) {
    if (!first) os << ' ';
    first = false;
    os << b;
  }
  v->read(os.str());
  return v;
}

}  // namespace

class SonyMakerNotePrintLensSpecTest_1607 : public ::testing::Test {
protected:
  SonyMakerNote smn_;
};

TEST_F(SonyMakerNotePrintLensSpecTest_1607, CountNotEight_PrintsParenthesizedValue_1607) {
  auto v = Value::create(unsignedByte);
  v->read("1 2 3");  // count != 8

  std::ostringstream oss;
  auto& ret = smn_.printLensSpec(oss, *v, nullptr);

  EXPECT_EQ(&ret, &oss);
  const std::string out = oss.str();
  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNotePrintLensSpecTest_1607, TypeNotUnsignedByte_PrintsParenthesizedValue_1607) {
  // 8 components but NOT unsignedByte type
  auto v = Value::create(Exiv2::asciiString);
  v->read("0 0 0 0 0 0 0 0");

  std::ostringstream oss;
  auto& ret = smn_.printLensSpec(oss, *v, nullptr);

  EXPECT_EQ(&ret, &oss);
  const std::string out = oss.str();
  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNotePrintLensSpecTest_1607, AllZeros_PrintsUnknown_1607) {
  auto v = MakeUByteValueFromList({0, 0, 0, 0, 0, 0, 0, 0});

  std::ostringstream oss;
  smn_.printLensSpec(oss, *v, nullptr);

  EXPECT_EQ(oss.str(), "Unknown");
}

TEST_F(SonyMakerNotePrintLensSpecTest_1607, FocalLenMinZero_PrintsUnknown_1607) {
  // focalLenMin (index 2) is 0, but not all zeros overall.
  auto v = MakeUByteValueFromList({0, 0, 0, 0, 0, 0x35, 0, 1});

  std::ostringstream oss;
  smn_.printLensSpec(oss, *v, nullptr);

  EXPECT_EQ(oss.str(), "Unknown");
}

TEST_F(SonyMakerNotePrintLensSpecTest_1607, ApertureMinZero_PrintsUnknown_1607) {
  // apertureMin (index 5) is 0, but not all zeros overall.
  auto v = MakeUByteValueFromList({0, 0, 0x35, 0, 0, 0, 0, 1});

  std::ostringstream oss;
  smn_.printLensSpec(oss, *v, nullptr);

  EXPECT_EQ(oss.str(), "Unknown");
}

TEST_F(SonyMakerNotePrintLensSpecTest_1607, ValidFixedLens_PrintsMmAndAperture_1607) {
  // focalLenMin=0x35 -> "35"
  // focalLenMax1=0, focalLenMax2=0 -> no zoom range
  // apertureMin=0x35 -> "F3.5", apertureMax=0 -> no aperture range
  auto v = MakeUByteValueFromList({0, 0, 0x35, 0, 0, 0x35, 0, 0});

  std::ostringstream oss;
  auto& ret = smn_.printLensSpec(oss, *v, nullptr);

  EXPECT_EQ(&ret, &oss);
  const std::string out = oss.str();
  EXPECT_NE(out.find("mm"), std::string::npos);
  EXPECT_NE(out.find(" F"), std::string::npos);
  EXPECT_NE(out.find("35mm"), std::string::npos);
  EXPECT_NE(out.find("F3.5"), std::string::npos);
  EXPECT_EQ(out.find('-'), std::string::npos);  // no ranges expected for this input
}

TEST_F(SonyMakerNotePrintLensSpecTest_1607, ValidZoomLensWithApertureRange_PrintsRanges_1607) {
  // focalLenMin=0x35 -> "35"
  // focalLenMax1=0, focalLenMax2=0x70 -> "-70"
  // apertureMin=0x35 -> "F3.5"
  // apertureMax=0x40 -> "-4.0"
  auto v = MakeUByteValueFromList({0, 0, 0x35, 0, 0x70, 0x35, 0x40, 0});

  std::ostringstream oss;
  smn_.printLensSpec(oss, *v, nullptr);

  const std::string out = oss.str();
  EXPECT_NE(out.find("35-70mm"), std::string::npos);
  EXPECT_NE(out.find("F3.5-4.0"), std::string::npos);
}