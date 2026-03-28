// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for Exiv2::Internal::print0xa404
//
// File under test: ./TestProjects/exiv2/src/tags_int.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <utility>

// Exiv2 headers (adjust include paths if your test project differs)
#include "exif.hpp"
#include "value.hpp"

namespace {

// A small helper to build a Value holding a Rational, without depending on internals.
// We use Exiv2's public Value factory.
inline Exiv2::Value::UniquePtr MakeURationalValue(uint32_t num, uint32_t den) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedRational);
  // "num/den" is a standard Exiv2 textual form for rationals.
  v->read(std::to_string(num) + "/" + std::to_string(den));
  return v;
}

}  // namespace

class Print0xA404Test_1414 : public ::testing::Test {};

TEST_F(Print0xA404Test_1414, DenominatorZero_PrintsDigitalZoomNotUsed_1414) {
  auto v = MakeURationalValue(123, 0);

  std::ostringstream os;
  Exiv2::Internal::print0xa404(os, *v, nullptr);

  // Observable behavior: for denominator==0, a fixed message is printed.
  // We do not assume localization strings; we only check it contains the English default.
  // If your build localizes _, you can relax this to "not used" only.
  const std::string out = os.str();
  EXPECT_NE(out.find("Digital zoom not used"), std::string::npos) << out;
}

TEST_F(Print0xA404Test_1414, SimpleRational_FormatsOneDecimal_1414) {
  auto v = MakeURationalValue(3, 2);  // 1.5

  std::ostringstream os;
  Exiv2::Internal::print0xa404(os, *v, nullptr);

  EXPECT_EQ(os.str(), "1.5");
}

TEST_F(Print0xA404Test_1414, RoundsToOneDecimal_1414) {
  // 1/3 = 0.333..., should round to 0.3 with one decimal.
  auto v = MakeURationalValue(1, 3);

  std::ostringstream os;
  Exiv2::Internal::print0xa404(os, *v, nullptr);

  EXPECT_EQ(os.str(), "0.3");
}

TEST_F(Print0xA404Test_1414, WholeNumber_PrintsWithOneDecimal_1414) {
  auto v = MakeURationalValue(2, 1);  // 2.0

  std::ostringstream os;
  Exiv2::Internal::print0xa404(os, *v, nullptr);

  EXPECT_EQ(os.str(), "2.0");
}

TEST_F(Print0xA404Test_1414, ExifDataPointerDoesNotAffectOutput_1414) {
  auto v = MakeURationalValue(5, 2);  // 2.5

  Exiv2::ExifData exif;
  std::ostringstream os1;
  std::ostringstream os2;

  Exiv2::Internal::print0xa404(os1, *v, nullptr);
  Exiv2::Internal::print0xa404(os2, *v, &exif);

  EXPECT_EQ(os1.str(), os2.str());
}

TEST_F(Print0xA404Test_1414, CanAppendToExistingStreamContent_1414) {
  auto v = MakeURationalValue(1, 2);  // 0.5

  std::ostringstream os;
  os << "prefix:";
  Exiv2::Internal::print0xa404(os, *v, nullptr);

  EXPECT_EQ(os.str(), "prefix:0.5");
}