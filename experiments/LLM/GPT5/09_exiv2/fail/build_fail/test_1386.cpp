// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::Internal::print0x0007
//
// File: ./TestProjects/exiv2/src/tags_int.cpp (function under test)
// *****************************************************************

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

// Depending on the Exiv2 layout, this header is typically available for internal tag print helpers.
#include "tags_int.hpp"

#include <iomanip>
#include <limits>
#include <sstream>
#include <string>

namespace {

class Print0x0007Test_1386 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr MakeSRationalValueFromRead(const std::string& text) {
    // signedRational is commonly used for RationalValue in Exiv2; the function under test only
    // relies on Value API (count/toRational/toInt64/toFloat/streaming).
    auto v = Exiv2::Value::create(Exiv2::signedRational);
    ASSERT_NE(v.get(), nullptr);
    v->read(text);
    return v;
  }

  static std::string StreamValue(const Exiv2::Value& v) {
    std::ostringstream oss;
    oss << v;
    return oss.str();
  }

  static std::string CallPrint0x0007(const Exiv2::Value& v, std::ios::fmtflags flags = std::ios::fmtflags(0),
                                     char fill = ' ', int width = 0) {
    std::ostringstream oss;
    if (flags != std::ios::fmtflags(0)) oss.setf(flags);
    oss << std::setfill(fill);
    if (width > 0) oss << std::setw(width);
    Exiv2::Internal::print0x0007(oss, v, nullptr);
    return oss.str();
  }
};

TEST_F(Print0x0007Test_1386, CountNotThree_PrintsValueDirectly_1386) {
  auto v = MakeSRationalValueFromRead("1/1 2/1");
  ASSERT_EQ(v->count(), 2u);

  const std::string expected = StreamValue(*v);
  const std::string actual = CallPrint0x0007(*v);

  EXPECT_EQ(actual, expected);
}

TEST_F(Print0x0007Test_1386, ThreeComponents_FormatsAsHHMMSS_NoFraction_1386) {
  // 1 hour, 2 minutes, 3 seconds
  auto v = MakeSRationalValueFromRead("1/1 2/1 3/1");
  ASSERT_EQ(v->count(), 3u);

  const std::string actual = CallPrint0x0007(*v);
  EXPECT_EQ(actual, "01:02:03");
}

TEST_F(Print0x0007Test_1386, ThreeComponents_FormatsWithOneDecimalWhenFractionalSeconds_1386) {
  // 1 hour, 2 minutes, 1.5 seconds
  auto v = MakeSRationalValueFromRead("1/1 2/1 3/2");
  ASSERT_EQ(v->count(), 3u);

  const std::string actual = CallPrint0x0007(*v);
  EXPECT_EQ(actual, "01:02:01.5");
}

TEST_F(Print0x0007Test_1386, HoursWrapModulo24_1386) {
  // 25:00:00 should wrap to 01:00:00 based on observable output.
  auto v = MakeSRationalValueFromRead("25/1 0/1 0/1");
  ASSERT_EQ(v->count(), 3u);

  const std::string actual = CallPrint0x0007(*v);
  EXPECT_EQ(actual, "01:00:00");
}

TEST_F(Print0x0007Test_1386, RestoresStreamFormattingFlagsAfterSuccessfulFormatting_1386) {
  auto v = MakeSRationalValueFromRead("1/1 2/1 3/1");
  ASSERT_EQ(v->count(), 3u);

  std::ostringstream oss;
  // Set some unusual formatting before calling the function.
  oss.setf(std::ios::hex, std::ios::basefield);
  oss.setf(std::ios::showbase);
  oss << std::setfill('*') << std::setw(9);

  const auto before_flags = oss.flags();
  const auto before_fill = oss.fill();
  const auto before_width = oss.width();

  Exiv2::Internal::print0x0007(oss, *v, nullptr);

  EXPECT_EQ(oss.flags(), before_flags);
  EXPECT_EQ(oss.fill(), before_fill);
  EXPECT_EQ(oss.width(), before_width);
}

TEST_F(Print0x0007Test_1386, DenominatorZeroInAnyComponent_PrintsValueInParentheses_1386) {
  // This is an observable error/exceptional formatting path: if any rational has denominator 0,
  // output becomes "(" + value + ")".
  //
  // Note: Exiv2::Value::read typically accepts "n/d" tokens; if "1/0" is rejected in your build,
  // this test will fail at construction and should be adjusted to a different way your Value can
  // represent a rational with denominator 0.
  auto v = MakeSRationalValueFromRead("1/0 2/1 3/1");
  ASSERT_EQ(v->count(), 3u);

  const std::string expected_value = StreamValue(*v);
  const std::string actual = CallPrint0x0007(*v);

  EXPECT_EQ(actual, "(" + expected_value + ")");
}

}  // namespace