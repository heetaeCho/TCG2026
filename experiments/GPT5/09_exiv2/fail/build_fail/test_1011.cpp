// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <sstream>
#include <string>

// NOTE: MinoltaMakerNote is an internal type implemented in a .cpp. For unit testing
// internal code in this codebase, we include the implementation file directly.
#include "minoltamn_int.cpp"

namespace {

using Exiv2::Internal::MinoltaMakerNote;

static Exiv2::Value::UniquePtr makeSignedLongValue(int64_t v) {
  auto val = Exiv2::Value::create(Exiv2::signedLong);
  // Keep inputs within 32-bit signed range for signedLong.
  val->read(std::to_string(static_cast<long>(v)));
  return val;
}

class MinoltaMakerNoteTest_1011 : public ::testing::Test {
 protected:
  MinoltaMakerNote sut_;
};

TEST_F(MinoltaMakerNoteTest_1011, ReturnsSameStreamReference_1011) {
  auto v = makeSignedLongValue(300);
  std::ostringstream os;

  std::ostream& ret = sut_.printMinoltaExposureCompensation5D(os, *v, nullptr);

  EXPECT_EQ(&ret, &os);
}

TEST_F(MinoltaMakerNoteTest_1011, OutputsZeroAtBaseOffset300_1011) {
  auto v = makeSignedLongValue(300);
  std::ostringstream os;

  sut_.printMinoltaExposureCompensation5D(os, *v, nullptr);

  EXPECT_EQ(os.str(), "0.00");
}

TEST_F(MinoltaMakerNoteTest_1011, FormatsTwoDecimalsForSmallPositiveDelta_1011) {
  auto v = makeSignedLongValue(301);  // (301 - 300) / 100 = 0.01
  std::ostringstream os;

  sut_.printMinoltaExposureCompensation5D(os, *v, nullptr);

  EXPECT_EQ(os.str(), "0.01");
}

TEST_F(MinoltaMakerNoteTest_1011, FormatsTwoDecimalsForSmallNegativeDelta_1011) {
  auto v = makeSignedLongValue(299);  // (299 - 300) / 100 = -0.01
  std::ostringstream os;

  sut_.printMinoltaExposureCompensation5D(os, *v, nullptr);

  EXPECT_EQ(os.str(), "-0.01");
}

TEST_F(MinoltaMakerNoteTest_1011, HandlesLargerPositiveValue_1011) {
  auto v = makeSignedLongValue(400);  // (400 - 300) / 100 = 1.00
  std::ostringstream os;

  sut_.printMinoltaExposureCompensation5D(os, *v, nullptr);

  EXPECT_EQ(os.str(), "1.00");
}

TEST_F(MinoltaMakerNoteTest_1011, HandlesNegativeInputValue_1011) {
  auto v = makeSignedLongValue(-100);  // (-100 - 300) / 100 = -4.00
  std::ostringstream os;

  sut_.printMinoltaExposureCompensation5D(os, *v, nullptr);

  EXPECT_EQ(os.str(), "-4.00");
}

TEST_F(MinoltaMakerNoteTest_1011, IgnoresExifDataPointerWhenNull_1011) {
  auto v = makeSignedLongValue(350);  // (350 - 300) / 100 = 0.50
  std::ostringstream os;

  // Observable behavior: should produce output without requiring ExifData.
  sut_.printMinoltaExposureCompensation5D(os, *v, nullptr);

  EXPECT_EQ(os.str(), "0.50");
}

}  // namespace