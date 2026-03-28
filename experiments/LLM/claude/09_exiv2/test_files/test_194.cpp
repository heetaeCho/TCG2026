#include <gtest/gtest.h>
#include <sstream>
#include <cstdint>

// We need Exiv2 headers for Value and ExifData types
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the internal header or declare the class as needed
namespace Exiv2 {
namespace Internal {
class PentaxMakerNote {
public:
  std::ostream& printFValue(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

class PentaxMakerNoteTest_194 : public ::testing::Test {
protected:
  Exiv2::Internal::PentaxMakerNote maker_;
  std::ostringstream oss_;
};

// Test normal F-value computation: value=56 => 56/10 = 5.6 => "F5.6"
TEST_F(PentaxMakerNoteTest_194, PrintFValue_Normal_56_194) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(56);
  maker_.printFValue(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "F5.6");
}

// Test F-value with value=10 => 10/10 = 1.0 => "F1"
TEST_F(PentaxMakerNoteTest_194, PrintFValue_OnePointZero_194) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(10);
  maker_.printFValue(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "F1");
}

// Test F-value with value=28 => 28/10 = 2.8 => "F2.8"
TEST_F(PentaxMakerNoteTest_194, PrintFValue_TwoPointEight_194) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(28);
  maker_.printFValue(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "F2.8");
}

// Test F-value with value=0 => 0/10 = 0.0 => "F0"
TEST_F(PentaxMakerNoteTest_194, PrintFValue_Zero_194) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(0);
  maker_.printFValue(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "F0");
}

// Test F-value with value=40 => 40/10 = 4.0 => "F4"
TEST_F(PentaxMakerNoteTest_194, PrintFValue_Four_194) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(40);
  maker_.printFValue(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "F4");
}

// Test F-value with value=220 => 220/10 = 22.0 => "F22"
TEST_F(PentaxMakerNoteTest_194, PrintFValue_TwentyTwo_194) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(220);
  maker_.printFValue(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "F22");
}

// Test F-value with value=14 => 14/10 = 1.4 => "F1.4"
TEST_F(PentaxMakerNoteTest_194, PrintFValue_OnePointFour_194) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(14);
  maker_.printFValue(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "F1.4");
}

// Test F-value with value=80 => 80/10 = 8.0 => "F8"
TEST_F(PentaxMakerNoteTest_194, PrintFValue_Eight_194) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(80);
  maker_.printFValue(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "F8");
}

// Test that the function returns the same ostream reference
TEST_F(PentaxMakerNoteTest_194, PrintFValue_ReturnsSameStream_194) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(56);
  std::ostream& result = maker_.printFValue(oss_, value, nullptr);
  EXPECT_EQ(&result, &oss_);
}

// Test F-value with a negative value: value=-10 => -10/10 = -1.0 => "F-1"
TEST_F(PentaxMakerNoteTest_194, PrintFValue_Negative_194) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(-10);
  maker_.printFValue(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "F-1");
}

// Test F-value with value=1 => 1/10 = 0.1 => "F0.1"
TEST_F(PentaxMakerNoteTest_194, PrintFValue_SmallValue_194) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(1);
  maker_.printFValue(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "F0.1");
}

// Test with nullptr ExifData (should not crash)
TEST_F(PentaxMakerNoteTest_194, PrintFValue_NullExifData_194) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(35);
  EXPECT_NO_THROW(maker_.printFValue(oss_, value, nullptr));
}

// Test F-value with large value: value=640 => 640/10 = 64.0 => "F64"
TEST_F(PentaxMakerNoteTest_194, PrintFValue_LargeValue_194) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(640);
  maker_.printFValue(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "F64");
}

// Test F-value with value=35 => 35/10 = 3.5 => "F3.5"
TEST_F(PentaxMakerNoteTest_194, PrintFValue_ThreePointFive_194) {
  Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
  value.value_.push_back(35);
  maker_.printFValue(oss_, value, nullptr);
  EXPECT_EQ(oss_.str(), "F3.5");
}
