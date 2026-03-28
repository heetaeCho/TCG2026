// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 509
//
// Unit tests for Exiv2::Internal::Nikon3MakerNote::printFocusDistanceLd4
// File under test: ./TestProjects/exiv2/src/nikonmn_int.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <regex>
#include <sstream>
#include <string>

#include <exiv2/exiv2.hpp>

// Nikon3MakerNote is an internal class; include its header from the project.
#include "nikonmn_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::TypeId;
using Exiv2::Value;

static std::string CallPrint(Exiv2::Internal::Nikon3MakerNote& mn, const Value& v) {
  std::ostringstream os;
  mn.printFocusDistanceLd4(os, v, /*ExifData*/ nullptr);
  return os.str();
}

static std::string StreamValueOnly(const Value& v) {
  std::ostringstream os;
  os << v;
  return os.str();
}

static std::string WrapInParens(const Value& v) {
  return "(" + StreamValueOnly(v) + ")";
}

// Creates a Value of the given type and reads from the provided textual representation.
static Value::UniquePtr MakeValue(TypeId tid, const std::string& text) {
  auto v = Value::create(tid);
  // Value::read parses the textual form for that type (e.g. "0" or "1 2").
  v->read(text);
  return v;
}

// Extracts the numeric prefix from strings like "12.34 m".
static bool TryParseMeters(const std::string& s, double& out) {
  static const std::regex kRe(R"(^\s*([+-]?\d+(?:\.\d+)?)\s*m\s*$)");
  std::smatch m;
  if (!std::regex_match(s, m, kRe)) return false;
  try {
    out = std::stod(m[1].str());
    return true;
  } catch (...) {
    return false;
  }
}

class Nikon3MakerNoteTest_509 : public ::testing::Test {
 protected:
  Exiv2::Internal::Nikon3MakerNote mn_;
};

TEST_F(Nikon3MakerNoteTest_509, WrongCount_WrapsValueInParentheses_509) {
  // count != 1 (two values) should be rendered as "(<value>)".
  auto v = MakeValue(Exiv2::unsignedShort, "1 2");

  const std::string out = CallPrint(mn_, *v);

  EXPECT_EQ(out, WrapInParens(*v));
  EXPECT_TRUE(!out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(Nikon3MakerNoteTest_509, WrongType_WrapsValueInParentheses_509) {
  // typeId != unsignedShort should be rendered as "(<value>)".
  auto v = MakeValue(Exiv2::unsignedLong, "123");

  const std::string out = CallPrint(mn_, *v);

  EXPECT_EQ(out, WrapInParens(*v));
  EXPECT_TRUE(!out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(Nikon3MakerNoteTest_509, ValidTypeAndCount_Zero_PrintsNa_509) {
  // For valid (unsignedShort, count==1) and value 0, output should be "n/a".
  auto v = MakeValue(Exiv2::unsignedShort, "0");

  const std::string out = CallPrint(mn_, *v);

  EXPECT_EQ(out, "n/a");
}

TEST_F(Nikon3MakerNoteTest_509, ValidTypeAndCount_NonZero_PrintsMetersWithTwoDecimals_509) {
  auto v = MakeValue(Exiv2::unsignedShort, "1");

  const std::string out = CallPrint(mn_, *v);

  // Should be in meters and not the fallback parenthesized form.
  EXPECT_NE(out, WrapInParens(*v));
  EXPECT_NE(out, "n/a");

  // Must end with " m" and have a numeric prefix parseable as double.
  double meters = 0.0;
  ASSERT_TRUE(TryParseMeters(out, meters)) << "Unexpected output: [" << out << "]";
  EXPECT_GT(meters, 0.0);

  // Ensure two decimal places are present (format like "X.YY m").
  // (We don't assume the numeric formula, only the observable formatting.)
  EXPECT_TRUE(std::regex_match(out, std::regex(R"(^[+-]?\d+\.\d{2}\s*m$)")))
      << "Unexpected formatting: [" << out << "]";
}

TEST_F(Nikon3MakerNoteTest_509, ValidTypeAndCount_LargerInput_ProducesDifferentAndMonotonicMeters_509) {
  // Boundary-ish values within unsignedShort range.
  auto small = MakeValue(Exiv2::unsignedShort, "1");
  auto large = MakeValue(Exiv2::unsignedShort, "65535");

  const std::string out_small = CallPrint(mn_, *small);
  const std::string out_large = CallPrint(mn_, *large);

  double m_small = 0.0, m_large = 0.0;
  ASSERT_TRUE(TryParseMeters(out_small, m_small)) << "Unexpected output: [" << out_small << "]";
  ASSERT_TRUE(TryParseMeters(out_large, m_large)) << "Unexpected output: [" << out_large << "]";

  // Observable behavior expectation: different inputs should produce different numeric outputs,
  // and a larger encoded value should not reduce the printed distance.
  EXPECT_NE(m_small, m_large);
  EXPECT_LE(m_small, m_large);
}

}  // namespace