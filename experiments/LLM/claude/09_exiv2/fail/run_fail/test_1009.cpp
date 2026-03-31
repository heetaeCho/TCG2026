#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the MinoltaMakerNote class from the internal namespace
namespace Exiv2 {
namespace Internal {
class MinoltaMakerNote {
public:
    std::ostream& printMinoltaBrightnessStd(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

// Since the implementation is in minoltamn_int.cpp, we replicate the declaration
// and rely on linking with the actual implementation.
// However, given the partial code provided, we can test the function behavior.

namespace {

class MinoltaMakerNoteTest_1009 : public ::testing::Test {
protected:
    Exiv2::Internal::MinoltaMakerNote makerNote_;
    std::ostringstream oss_;
};

// Test normal positive value: value=48 => (48/8)-6 = 6-6 = 0
TEST_F(MinoltaMakerNoteTest_1009, BrightnessStdZeroResult_1009) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(48);
    makerNote_.printMinoltaBrightnessStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "0");
}

// Test normal positive value: value=96 => (96/8)-6 = 12-6 = 6
TEST_F(MinoltaMakerNoteTest_1009, BrightnessStdPositiveResult_1009) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(96);
    makerNote_.printMinoltaBrightnessStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "6");
}

// Test value=0 => (0/8)-6 = 0-6 = -6
TEST_F(MinoltaMakerNoteTest_1009, BrightnessStdValueZero_1009) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(0);
    makerNote_.printMinoltaBrightnessStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "-6");
}

// Test negative value: value=-48 => (-48/8)-6 = -6-6 = -12
TEST_F(MinoltaMakerNoteTest_1009, BrightnessStdNegativeInput_1009) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(-48);
    makerNote_.printMinoltaBrightnessStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "-12");
}

// Test value=8 => (8/8)-6 = 1-6 = -5
TEST_F(MinoltaMakerNoteTest_1009, BrightnessStdValueEight_1009) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(8);
    makerNote_.printMinoltaBrightnessStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "-5");
}

// Test value that is not a multiple of 8: value=1 => (1/8)-6 = 0-6 = -6 (integer division)
TEST_F(MinoltaMakerNoteTest_1009, BrightnessStdNonMultipleOfEight_1009) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(1);
    makerNote_.printMinoltaBrightnessStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "-6");
}

// Test value=7 => (7/8)-6 = 0-6 = -6 (integer division truncates toward zero)
TEST_F(MinoltaMakerNoteTest_1009, BrightnessStdValueSeven_1009) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(7);
    makerNote_.printMinoltaBrightnessStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "-6");
}

// Test value=9 => (9/8)-6 = 1-6 = -5
TEST_F(MinoltaMakerNoteTest_1009, BrightnessStdValueNine_1009) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(9);
    makerNote_.printMinoltaBrightnessStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "-5");
}

// Test large positive value: value=1000 => (1000/8)-6 = 125-6 = 119
TEST_F(MinoltaMakerNoteTest_1009, BrightnessStdLargePositive_1009) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(1000);
    makerNote_.printMinoltaBrightnessStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "119");
}

// Test large negative value: value=-1000 => (-1000/8)-6 = -125-6 = -131
TEST_F(MinoltaMakerNoteTest_1009, BrightnessStdLargeNegative_1009) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(-1000);
    makerNote_.printMinoltaBrightnessStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "-131");
}

// Test that the function returns the ostream reference (chaining)
TEST_F(MinoltaMakerNoteTest_1009, BrightnessStdReturnsOstream_1009) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(48);
    std::ostream& result = makerNote_.printMinoltaBrightnessStd(oss_, value, nullptr);
    EXPECT_EQ(&result, &oss_);
}

// Test with nullptr ExifData (should still work since it's unused)
TEST_F(MinoltaMakerNoteTest_1009, BrightnessStdNullExifData_1009) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(16);
    makerNote_.printMinoltaBrightnessStd(oss_, value, nullptr);
    // (16/8)-6 = 2-6 = -4
    EXPECT_EQ(oss_.str(), "-4");
}

// Test negative value not multiple of 8: value=-1 => (-1/8)-6 = 0-6 = -6 (C++ truncation toward zero)
TEST_F(MinoltaMakerNoteTest_1009, BrightnessStdNegativeOneInput_1009) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(-1);
    makerNote_.printMinoltaBrightnessStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "-6");
}

// Test negative value: value=-7 => (-7/8)-6 = 0-6 = -6 (C++ integer division truncates toward zero)
TEST_F(MinoltaMakerNoteTest_1009, BrightnessStdNegativeSevenInput_1009) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(-7);
    makerNote_.printMinoltaBrightnessStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "-6");
}

// Test negative value: value=-9 => (-9/8)-6 = -1-6 = -7
TEST_F(MinoltaMakerNoteTest_1009, BrightnessStdNegativeNineInput_1009) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(-9);
    makerNote_.printMinoltaBrightnessStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "-7");
}

}  // namespace
