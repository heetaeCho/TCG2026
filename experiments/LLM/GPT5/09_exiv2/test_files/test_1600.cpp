// TEST_ID 1600
// File: test_sonymn_int_print_wbshift_abgm_precise_1600.cpp

#include <gtest/gtest.h>

#include <iomanip>
#include <limits>
#include <sstream>
#include <string>

#include <exiv2/exiv2.hpp>

#if __has_include("sonymn_int.hpp")
#include "sonymn_int.hpp"
#elif __has_include("exiv2/sonymn_int.hpp")
#include "exiv2/sonymn_int.hpp"
#endif

namespace {

using Exiv2::TypeId;
using Exiv2::Value;

Value::UniquePtr MakeValue(TypeId type, const std::string& text) {
  auto v = Value::create(type);
  v->read(text);
  return v;
}

class SonyMakerNotePrintWBShiftABGMPreciseTest_1600 : public ::testing::Test {
 protected:
  Exiv2::Internal::SonyMakerNote uut_;
};

TEST_F(SonyMakerNotePrintWBShiftABGMPreciseTest_1600, WrapsValueWhenCountIsNotTwo_1600) {
  // count == 1, type == signedLong
  auto v = MakeValue(Exiv2::signedLong, "1000");
  std::ostringstream os;

  uut_.printWBShiftABGMPrecise(os, *v, nullptr);

  const std::string out = os.str();
  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNotePrintWBShiftABGMPreciseTest_1600, WrapsValueWhenTypeIsNotSignedLong_1600) {
  // count == 2, type != signedLong
  auto v = MakeValue(Exiv2::unsignedLong, "1000 2000");
  std::ostringstream os;

  uut_.printWBShiftABGMPrecise(os, *v, nullptr);

  const std::string out = os.str();
  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNotePrintWBShiftABGMPreciseTest_1600, FormatsZerosWithoutPrefixes_1600) {
  auto v = MakeValue(Exiv2::signedLong, "0 0");
  std::ostringstream os;

  uut_.printWBShiftABGMPrecise(os, *v, nullptr);

  EXPECT_EQ(os.str(), "A/B: 0, G/M: 0");
}

TEST_F(SonyMakerNotePrintWBShiftABGMPreciseTest_1600, FormatsPositiveAndNegativeWithPrefixesAndTwoDecimals_1600) {
  // temp0 = 1500/1000 = 1.5 -> B1.50
  // temp1 = -2500/1000 = -2.5 -> G2.50
  auto v = MakeValue(Exiv2::signedLong, "1500 -2500");
  std::ostringstream os;

  uut_.printWBShiftABGMPrecise(os, *v, nullptr);

  EXPECT_EQ(os.str(), "A/B: B1.50, G/M: G2.50");
}

TEST_F(SonyMakerNotePrintWBShiftABGMPreciseTest_1600, FormatsNegativeAndPositiveWithPrefixesAndTwoDecimals_1600) {
  // temp0 = -1234/1000 = -1.234 -> A1.23 (rounded)
  // temp1 = 5678/1000 = 5.678 -> M5.68 (rounded)
  auto v = MakeValue(Exiv2::signedLong, "-1234 5678");
  std::ostringstream os;

  uut_.printWBShiftABGMPrecise(os, *v, nullptr);

  EXPECT_EQ(os.str(), "A/B: A1.23, G/M: M5.68");
}

TEST_F(SonyMakerNotePrintWBShiftABGMPreciseTest_1600, BoundaryNearZeroRoundsToTwoDecimalsWithCorrectPrefix_1600) {
  // temp0 = 1/1000 = 0.001 -> B0.00
  // temp1 = -1/1000 = -0.001 -> G0.00
  auto v = MakeValue(Exiv2::signedLong, "1 -1");
  std::ostringstream os;

  uut_.printWBShiftABGMPrecise(os, *v, nullptr);

  EXPECT_EQ(os.str(), "A/B: B0.00, G/M: G0.00");
}

TEST_F(SonyMakerNotePrintWBShiftABGMPreciseTest_1600, KeepsZeroAsPlainZeroWhenOnlySecondIsNonZero_1600) {
  // First is exactly 0 -> prints "0" (no prefix / decimals), second prints with prefix and two decimals.
  auto v = MakeValue(Exiv2::signedLong, "0 1230");  // 1.23
  std::ostringstream os;

  uut_.printWBShiftABGMPrecise(os, *v, nullptr);

  EXPECT_EQ(os.str(), "A/B: 0, G/M: M1.23");
}

TEST_F(SonyMakerNotePrintWBShiftABGMPreciseTest_1600, RestoresStreamFlagsAfterCall_1600) {
  auto v = MakeValue(Exiv2::signedLong, "1000 2000");  // non-zero triggers formatting manipulations
  std::ostringstream os;

  // Set some flags we can check are restored.
  os.setf(std::ios::showbase);
  os.setf(std::ios::hex, std::ios::basefield);
  const std::ios::fmtflags before_flags = os.flags();

  uut_.printWBShiftABGMPrecise(os, *v, nullptr);

  EXPECT_EQ(os.flags(), before_flags);
}

}  // namespace