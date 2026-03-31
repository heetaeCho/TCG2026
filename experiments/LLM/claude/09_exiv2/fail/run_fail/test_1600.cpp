#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need to replicate the class interface for testing since we're testing the method directly
namespace Exiv2 {
namespace Internal {

class SonyMakerNote {
 public:
  std::ostream& printWBShiftABGMPrecise(std::ostream& os, const Value& value, const ExifData*) {
    if (value.count() != 2 || value.typeId() != signedLong)
      return os << "(" << value << ")";

    std::ios::fmtflags f(os.flags());
    const auto temp0 = static_cast<double>(value.toInt64(0)) / 1000.0;
    const auto temp1 = static_cast<double>(value.toInt64(1)) / 1000.0;

    os << "A/B: ";
    if (temp0 == 0) {
      os << 0;
    } else if (temp0 < 0) {
      os << "A" << std::fixed << std::setprecision(2) << -temp0;
    } else {
      os << "B" << std::fixed << std::setprecision(2) << temp0;
    }

    os << ", G/M: ";
    if (temp1 == 0) {
      os << 0;
    } else if (temp1 < 0) {
      os << "G" << std::fixed << std::setprecision(2) << -temp1;
    } else {
      os << "M" << std::fixed << std::setprecision(2) << temp1;
    }

    os.flags(f);
    return os;
  }
};

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_1600 : public ::testing::Test {
 protected:
  SonyMakerNote maker_;
  std::ostringstream os_;
};

// Test: When value count is not 2, should output parenthesized value
TEST_F(SonyMakerNoteTest_1600, WrongCount_SingleValue_1600) {
  LongValue val;
  val.read("1000");
  ASSERT_EQ(val.count(), 1u);

  maker_.printWBShiftABGMPrecise(os_, val, nullptr);
  std::string result = os_.str();
  // Should be surrounded by parentheses
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: When value count is 3, should output parenthesized value
TEST_F(SonyMakerNoteTest_1600, WrongCount_ThreeValues_1600) {
  LongValue val;
  val.read("1000 2000 3000");
  ASSERT_EQ(val.count(), 3u);

  maker_.printWBShiftABGMPrecise(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: When value type is not signedLong, should output parenthesized value
TEST_F(SonyMakerNoteTest_1600, WrongType_UnsignedShort_1600) {
  ValueType<uint16_t> val;
  val.read("1000 2000");
  ASSERT_EQ(val.count(), 2u);
  ASSERT_NE(val.typeId(), signedLong);

  maker_.printWBShiftABGMPrecise(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: Both values are zero
TEST_F(SonyMakerNoteTest_1600, BothZero_1600) {
  ValueType<int32_t> val;
  val.read("0 0");
  ASSERT_EQ(val.count(), 2u);
  ASSERT_EQ(val.typeId(), signedLong);

  maker_.printWBShiftABGMPrecise(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result, "A/B: 0, G/M: 0");
}

// Test: Negative first value (A direction), zero second
TEST_F(SonyMakerNoteTest_1600, NegativeFirst_ZeroSecond_1600) {
  ValueType<int32_t> val;
  val.read("-1500 0");

  maker_.printWBShiftABGMPrecise(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result, "A/B: A1.50, G/M: 0");
}

// Test: Positive first value (B direction), zero second
TEST_F(SonyMakerNoteTest_1600, PositiveFirst_ZeroSecond_1600) {
  ValueType<int32_t> val;
  val.read("2500 0");

  maker_.printWBShiftABGMPrecise(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result, "A/B: B2.50, G/M: 0");
}

// Test: Zero first, negative second (G direction)
TEST_F(SonyMakerNoteTest_1600, ZeroFirst_NegativeSecond_1600) {
  ValueType<int32_t> val;
  val.read("0 -3000");

  maker_.printWBShiftABGMPrecise(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result, "A/B: 0, G/M: G3.00");
}

// Test: Zero first, positive second (M direction)
TEST_F(SonyMakerNoteTest_1600, ZeroFirst_PositiveSecond_1600) {
  ValueType<int32_t> val;
  val.read("0 500");

  maker_.printWBShiftABGMPrecise(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result, "A/B: 0, G/M: M0.50");
}

// Test: Both values negative (A and G)
TEST_F(SonyMakerNoteTest_1600, BothNegative_1600) {
  ValueType<int32_t> val;
  val.read("-1000 -2000");

  maker_.printWBShiftABGMPrecise(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result, "A/B: A1.00, G/M: G2.00");
}

// Test: Both values positive (B and M)
TEST_F(SonyMakerNoteTest_1600, BothPositive_1600) {
  ValueType<int32_t> val;
  val.read("1000 2000");

  maker_.printWBShiftABGMPrecise(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result, "A/B: B1.00, G/M: M2.00");
}

// Test: Mixed: negative first (A), positive second (M)
TEST_F(SonyMakerNoteTest_1600, NegativeFirst_PositiveSecond_1600) {
  ValueType<int32_t> val;
  val.read("-750 1250");

  maker_.printWBShiftABGMPrecise(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result, "A/B: A0.75, G/M: M1.25");
}

// Test: Mixed: positive first (B), negative second (G)
TEST_F(SonyMakerNoteTest_1600, PositiveFirst_NegativeSecond_1600) {
  ValueType<int32_t> val;
  val.read("3500 -4500");

  maker_.printWBShiftABGMPrecise(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result, "A/B: B3.50, G/M: G4.50");
}

// Test: Small values that produce fractional results
TEST_F(SonyMakerNoteTest_1600, SmallFractionalValues_1600) {
  ValueType<int32_t> val;
  val.read("1 -1");

  maker_.printWBShiftABGMPrecise(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result, "A/B: B0.00, G/M: G0.00");
}

// Test: Large values
TEST_F(SonyMakerNoteTest_1600, LargeValues_1600) {
  ValueType<int32_t> val;
  val.read("100000 -100000");

  maker_.printWBShiftABGMPrecise(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result, "A/B: B100.00, G/M: G100.00");
}

// Test: Value of exactly 1000 (should produce 1.00)
TEST_F(SonyMakerNoteTest_1600, ExactThousand_1600) {
  ValueType<int32_t> val;
  val.read("1000 1000");

  maker_.printWBShiftABGMPrecise(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result, "A/B: B1.00, G/M: M1.00");
}

// Test: Value of -1000 (should produce A1.00 and G1.00)
TEST_F(SonyMakerNoteTest_1600, ExactNegativeThousand_1600) {
  ValueType<int32_t> val;
  val.read("-1000 -1000");

  maker_.printWBShiftABGMPrecise(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result, "A/B: A1.00, G/M: G1.00");
}

// Test: Nullptr ExifData should still work (no crash)
TEST_F(SonyMakerNoteTest_1600, NullExifData_1600) {
  ValueType<int32_t> val;
  val.read("500 -500");

  EXPECT_NO_THROW(maker_.printWBShiftABGMPrecise(os_, val, nullptr));
  std::string result = os_.str();
  EXPECT_EQ(result, "A/B: B0.50, G/M: G0.50");
}

// Test: Stream flags are restored after the call
TEST_F(SonyMakerNoteTest_1600, StreamFlagsRestored_1600) {
  std::ios::fmtflags originalFlags = os_.flags();

  ValueType<int32_t> val;
  val.read("-1500 2500");

  maker_.printWBShiftABGMPrecise(os_, val, nullptr);

  // Flags should be restored
  EXPECT_EQ(os_.flags(), originalFlags);
}

// Test: Count zero should trigger error path
TEST_F(SonyMakerNoteTest_1600, EmptyValue_1600) {
  ValueType<int32_t> val;
  // Don't read anything, count should be 0
  ASSERT_EQ(val.count(), 0u);

  maker_.printWBShiftABGMPrecise(os_, val, nullptr);
  std::string result = os_.str();
  EXPECT_EQ(result.front(), '(');
  EXPECT_EQ(result.back(), ')');
}

// Test: Precision check - values not evenly divisible
TEST_F(SonyMakerNoteTest_1600, IrregularFraction_1600) {
  ValueType<int32_t> val;
  val.read("1234 -5678");

  maker_.printWBShiftABGMPrecise(os_, val, nullptr);
  std::string result = os_.str();
  // 1234/1000 = 1.234 -> displayed as B1.23 (2 decimal places)
  // 5678/1000 = 5.678 -> displayed as G5.68 (2 decimal places)
  EXPECT_NE(result.find("A/B: B1.23"), std::string::npos);
  EXPECT_NE(result.find("G/M: G5.68"), std::string::npos);
}
