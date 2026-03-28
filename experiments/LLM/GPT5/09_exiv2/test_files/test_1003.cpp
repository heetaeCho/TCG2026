// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_minoltamn_int_printMinoltaExposureCompensationStd_1003.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <sstream>
#include <string>

// This internal class may not have a public header. Include the implementation
// file to access the class under test.
#include "minoltamn_int.cpp"

#include <exiv2/value.hpp>

namespace {

class MinoltaMakerNoteTest_1003 : public ::testing::Test {
 protected:
  Exiv2::Internal::MinoltaMakerNote uut_{};

  static Exiv2::Value::UniquePtr MakeSignedLongValue(const std::string& text) {
    // Use Exiv2's public Value factory + parsing.
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedLong);
    EXPECT_NE(v.get(), nullptr);
    EXPECT_EQ(0, v->read(text));
    return v;
  }
};

TEST_F(MinoltaMakerNoteTest_1003, PrintsQuotientForPositiveExactMultiple_1003) {
  auto v = MakeSignedLongValue("256");

  std::ostringstream oss;
  std::ostream& ret = uut_.printMinoltaExposureCompensationStd(oss, *v, nullptr);

  EXPECT_EQ(&ret, &oss);
  EXPECT_EQ("1", oss.str());
}

TEST_F(MinoltaMakerNoteTest_1003, PrintsZeroForZeroInput_1003) {
  auto v = MakeSignedLongValue("0");

  std::ostringstream oss;
  uut_.printMinoltaExposureCompensationStd(oss, *v, nullptr);

  EXPECT_EQ("0", oss.str());
}

TEST_F(MinoltaMakerNoteTest_1003, PrintsQuotientForNegativeExactMultiple_1003) {
  auto v = MakeSignedLongValue("-256");

  std::ostringstream oss;
  uut_.printMinoltaExposureCompensationStd(oss, *v, nullptr);

  EXPECT_EQ("-1", oss.str());
}

TEST_F(MinoltaMakerNoteTest_1003, TruncatesTowardZeroForNonMultiple_1003) {
  // Observable behavior: integer division when printing.
  auto v = MakeSignedLongValue("255");

  std::ostringstream oss;
  uut_.printMinoltaExposureCompensationStd(oss, *v, nullptr);

  EXPECT_EQ("0", oss.str());
}

TEST_F(MinoltaMakerNoteTest_1003, HandlesLargeMagnitudeValues_1003) {
  const std::int64_t in = std::numeric_limits<std::int64_t>::max();
  const std::int64_t expected = in / 256;

  auto v = MakeSignedLongValue(std::to_string(in));

  std::ostringstream oss;
  uut_.printMinoltaExposureCompensationStd(oss, *v, nullptr);

  EXPECT_EQ(std::to_string(expected), oss.str());
}

TEST_F(MinoltaMakerNoteTest_1003, DoesNotThrowAndReturnsStreamEvenIfStreamFailed_1003) {
  auto v = MakeSignedLongValue("256");

  std::ostringstream oss;
  oss.setstate(std::ios::failbit);

  EXPECT_NO_THROW({
    std::ostream& ret = uut_.printMinoltaExposureCompensationStd(oss, *v, nullptr);
    EXPECT_EQ(&ret, &oss);
  });

  // With failbit set, insertion may not produce output.
  EXPECT_TRUE(oss.fail());
}

}  // namespace