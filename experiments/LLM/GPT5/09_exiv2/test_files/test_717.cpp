// TEST_ID 717
// Unit tests for Exiv2::Internal::PanasonicMakerNote::printPitchAngle
//
// Constraints honored:
// - Treat implementation as a black box (no internal state access).
// - Test only observable behavior: ostream output + returned stream reference.
// - Cover normal, boundary-ish, and error-ish observable cases.

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>

// Exiv2 headers (expected available in the codebase)
#include "exif.hpp"              // Exiv2::ExifData
#include "value.hpp"             // Exiv2::Value
#include "panasonicmn_int.hpp"   // Exiv2::Internal::PanasonicMakerNote

namespace {

class PanasonicMakerNoteTest_717 : public ::testing::Test {
 protected:
  Exiv2::Internal::PanasonicMakerNote sut_;
  Exiv2::ExifData exif_;  // not used by implementation, but part of signature
};

static std::unique_ptr<Exiv2::Value> MakeSignedShortValue(int64_t v) {
  // Keep it simple: use a signed short value type since the function casts to int16_t.
  // This avoids depending on parsing of strings, endianness, etc.
  auto val = Exiv2::Value::create(Exiv2::signedShort);
  val->read(v);
  return val;
}

TEST_F(PanasonicMakerNoteTest_717, ReturnsSameStreamReference_717) {
  std::ostringstream os;
  auto value = MakeSignedShortValue(0);

  std::ostream& ret = sut_.printPitchAngle(os, *value, &exif_);

  EXPECT_EQ(&ret, &os);
}

TEST_F(PanasonicMakerNoteTest_717, FormatsZeroAsOneDecimal_717) {
  std::ostringstream os;
  auto value = MakeSignedShortValue(0);

  sut_.printPitchAngle(os, *value, &exif_);

  EXPECT_EQ(os.str(), "0.0");
}

TEST_F(PanasonicMakerNoteTest_717, NegatesAndScalesByTenth_PositiveInput_717) {
  // Input 15 -> i=15 -> output -1.5 (with one decimal)
  std::ostringstream os;
  auto value = MakeSignedShortValue(15);

  sut_.printPitchAngle(os, *value, &exif_);

  EXPECT_EQ(os.str(), "-1.5");
}

TEST_F(PanasonicMakerNoteTest_717, NegatesAndScalesByTenth_NegativeInput_717) {
  // Input -15 -> i=-15 -> output +1.5
  std::ostringstream os;
  auto value = MakeSignedShortValue(-15);

  sut_.printPitchAngle(os, *value, &exif_);

  EXPECT_EQ(os.str(), "1.5");
}

TEST_F(PanasonicMakerNoteTest_717, RoundsToSingleDecimal_717) {
  // Input 14 -> -1.4 exactly
  std::ostringstream os1;
  auto v14 = MakeSignedShortValue(14);
  sut_.printPitchAngle(os1, *v14, &exif_);
  EXPECT_EQ(os1.str(), "-1.4");

  // Input 16 -> -1.6 exactly
  std::ostringstream os2;
  auto v16 = MakeSignedShortValue(16);
  sut_.printPitchAngle(os2, *v16, &exif_);
  EXPECT_EQ(os2.str(), "-1.6");
}

TEST_F(PanasonicMakerNoteTest_717, HandlesInt16MinAndMaxCasting_717) {
  // The function casts value.toInt64() to int16_t; test the boundaries of int16_t.
  {
    std::ostringstream os;
    auto value = MakeSignedShortValue(std::numeric_limits<int16_t>::max());  // 32767 -> -3276.7
    sut_.printPitchAngle(os, *value, &exif_);
    EXPECT_EQ(os.str(), "-3276.7");
  }
  {
    std::ostringstream os;
    auto value = MakeSignedShortValue(std::numeric_limits<int16_t>::min());  // -32768 -> +3276.8
    sut_.printPitchAngle(os, *value, &exif_);
    EXPECT_EQ(os.str(), "3276.8");
  }
}

TEST_F(PanasonicMakerNoteTest_717, IgnoresExifDataPointerWhenNull_717) {
  // Observable behavior: should still produce same formatted output.
  std::ostringstream os;
  auto value = MakeSignedShortValue(25);  // -> -2.5

  sut_.printPitchAngle(os, *value, nullptr);

  EXPECT_EQ(os.str(), "-2.5");
}

TEST_F(PanasonicMakerNoteTest_717, AppendsToExistingStreamContents_717) {
  std::ostringstream os;
  os << "prefix:";
  auto value = MakeSignedShortValue(10);  // -> -1.0

  sut_.printPitchAngle(os, *value, &exif_);

  EXPECT_EQ(os.str(), "prefix:-1.0");
}

}  // namespace