// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>

#include <cstdint>
#include <sstream>
#include <string>

// Include the implementation file so we can unit-test the internal static helper
// as a black-box formatter (no private-state access).
#include "fujimn_int.cpp"

namespace {

using Exiv2::ExifData;
using Exiv2::Internal::printFujiWhiteBalanceFineTune;

class FujiWhiteBalanceFineTuneTest_622 : public ::testing::Test {
 protected:
  static std::string Call(const Exiv2::Value& v) {
    std::ostringstream os;
    printFujiWhiteBalanceFineTune(os, v, static_cast<const ExifData*>(nullptr));
    return os.str();
  }

  static std::string ParenWrapped(const Exiv2::Value& v) {
    std::ostringstream vs;
    vs << v;
    return "(" + vs.str() + ")";
  }

  static Exiv2::Value::UniquePtr MakeSignedLongFromText(const char* text) {
    auto v = Exiv2::Value::create(Exiv2::signedLong);
    v->read(text);
    return v;
  }

  static Exiv2::Value::UniquePtr MakeUnsignedLongFromText(const char* text) {
    auto v = Exiv2::Value::create(Exiv2::unsignedLong);
    v->read(text);
    return v;
  }
};

TEST_F(FujiWhiteBalanceFineTuneTest_622, FormatsTwoSignedLongsDivisibleBy20_622) {
  auto v = MakeSignedLongFromText("20 40");  // size should be 8 for two signedLong values
  ASSERT_NE(v, nullptr);

  const std::string out = Call(*v);
  EXPECT_EQ(out, "R: 1 B: 2");
}

TEST_F(FujiWhiteBalanceFineTuneTest_622, FormatsNegativeMultiplesOf20_622) {
  auto v = MakeSignedLongFromText("-20 0");
  ASSERT_NE(v, nullptr);

  const std::string out = Call(*v);
  EXPECT_EQ(out, "R: -1 B: 0");
}

TEST_F(FujiWhiteBalanceFineTuneTest_622, FallsBackWhenFirstIsNotDivisibleBy20_622) {
  auto v = MakeSignedLongFromText("21 40");
  ASSERT_NE(v, nullptr);

  const std::string out = Call(*v);
  EXPECT_EQ(out, ParenWrapped(*v));
}

TEST_F(FujiWhiteBalanceFineTuneTest_622, FallsBackWhenSecondIsNotDivisibleBy20_622) {
  auto v = MakeSignedLongFromText("20 41");
  ASSERT_NE(v, nullptr);

  const std::string out = Call(*v);
  EXPECT_EQ(out, ParenWrapped(*v));
}

TEST_F(FujiWhiteBalanceFineTuneTest_622, FallsBackWhenSizeIsNotEightBytes_622) {
  // One signedLong value -> typically 4 bytes, not 8.
  auto v = MakeSignedLongFromText("20");
  ASSERT_NE(v, nullptr);

  const std::string out = Call(*v);
  EXPECT_EQ(out, ParenWrapped(*v));
}

TEST_F(FujiWhiteBalanceFineTuneTest_622, FallsBackWhenTypeIsNotSignedLong_622) {
  // Even if values are multiples of 20, wrong type should fall back.
  auto v = MakeUnsignedLongFromText("20 40");
  ASSERT_NE(v, nullptr);

  const std::string out = Call(*v);
  EXPECT_EQ(out, ParenWrapped(*v));
}

}  // namespace