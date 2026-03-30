// File: test_sonymn_int_printWBShiftABGM_1592.cpp
// TEST_ID: 1592

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

// Internal header that declares Exiv2::Internal::SonyMakerNote.
// Adjust include path if your build uses a different relative location.
#include "sonymn_int.hpp"

#include <cstdint>
#include <limits>
#include <memory>
#include <sstream>
#include <string>

namespace {

using Exiv2::ExifData;
using Exiv2::Internal::SonyMakerNote;
using Exiv2::TypeId;

class SonyMakerNotePrintWBShiftABGMTest_1592 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::Value> MakeValue(TypeId type, const std::string& readStr) {
    auto v = Exiv2::Value::create(type);
    v->read(readStr);
    return v;
  }

  static std::string CallPrint(const Exiv2::Value& value) {
    SonyMakerNote mn;
    std::ostringstream os;
    mn.printWBShiftABGM(os, value, static_cast<const ExifData*>(nullptr));
    return os.str();
  }

  static std::string ParenthesizedValue(const Exiv2::Value& value) {
    std::ostringstream os;
    os << "(" << value << ")";
    return os.str();
  }
};

TEST_F(SonyMakerNotePrintWBShiftABGMTest_1592, FormatsZeroZero_1592) {
  auto v = MakeValue(Exiv2::signedLong, "0 0");
  ASSERT_NE(v, nullptr);

  const std::string out = CallPrint(*v);
  EXPECT_EQ(out, "A/B: 0, G/M: 0");
}

TEST_F(SonyMakerNotePrintWBShiftABGMTest_1592, FormatsNegativeNegative_AsAandG_1592) {
  auto v = MakeValue(Exiv2::signedLong, "-2 -3");
  ASSERT_NE(v, nullptr);

  const std::string out = CallPrint(*v);
  EXPECT_EQ(out, "A/B: A2, G/M: G3");
}

TEST_F(SonyMakerNotePrintWBShiftABGMTest_1592, FormatsPositivePositive_AsBandM_1592) {
  auto v = MakeValue(Exiv2::signedLong, "5 4");
  ASSERT_NE(v, nullptr);

  const std::string out = CallPrint(*v);
  EXPECT_EQ(out, "A/B: B5, G/M: M4");
}

TEST_F(SonyMakerNotePrintWBShiftABGMTest_1592, FormatsMixedSigns_1592) {
  auto v = MakeValue(Exiv2::signedLong, "-1 2");
  ASSERT_NE(v, nullptr);

  const std::string out = CallPrint(*v);
  EXPECT_EQ(out, "A/B: A1, G/M: M2");
}

TEST_F(SonyMakerNotePrintWBShiftABGMTest_1592, Boundary_LargeMagnitudeValues_1592) {
  // Avoid INT64_MIN to prevent potential negation overflow in any implementation.
  const int64_t nearMin = (std::numeric_limits<int64_t>::min() + 1);
  const int64_t nearMax = std::numeric_limits<int64_t>::max();

  std::ostringstream in;
  in << nearMin << " " << nearMax;

  auto v = MakeValue(Exiv2::signedLong, in.str());
  ASSERT_NE(v, nullptr);

  std::ostringstream expected;
  expected << "A/B: A" << -(nearMin) << ", G/M: M" << nearMax;

  const std::string out = CallPrint(*v);
  EXPECT_EQ(out, expected.str());
}

TEST_F(SonyMakerNotePrintWBShiftABGMTest_1592, ErrorCase_WrongCount_ReturnsParenthesizedValue_1592) {
  auto v = MakeValue(Exiv2::signedLong, "7");  // count != 2
  ASSERT_NE(v, nullptr);

  const std::string out = CallPrint(*v);
  EXPECT_EQ(out, ParenthesizedValue(*v));
}

TEST_F(SonyMakerNotePrintWBShiftABGMTest_1592, ErrorCase_WrongType_ReturnsParenthesizedValue_1592) {
  // Two elements, but not signedLong.
  auto v = MakeValue(Exiv2::unsignedLong, "1 2");
  ASSERT_NE(v, nullptr);

  const std::string out = CallPrint(*v);
  EXPECT_EQ(out, ParenthesizedValue(*v));
}

}  // namespace