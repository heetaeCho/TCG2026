#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the header that contains the MinoltaMakerNote class
// Since we only have the .cpp snippet, we include what's needed
namespace Exiv2 {
namespace Internal {
class MinoltaMakerNote {
public:
    std::ostream& printMinoltaFNumberStd(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

// We need to link against the actual implementation from the library.
// The tests below treat the implementation as a black box.

class MinoltaMakerNoteTest_1002 : public ::testing::Test {
protected:
    Exiv2::Internal::MinoltaMakerNote makerNote_;
    std::ostringstream oss_;
};

// Test normal operation: value that yields a positive F-number result
TEST_F(MinoltaMakerNoteTest_1002, PrintFNumberStd_NormalValue_1002) {
    // (value / 8) - 1
    // For value = 24: (24/8) - 1 = 3 - 1 = 2
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(24);

    makerNote_.printMinoltaFNumberStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "2");
}

// Test with value = 16: (16/8) - 1 = 2 - 1 = 1
TEST_F(MinoltaMakerNoteTest_1002, PrintFNumberStd_Value16_1002) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(16);

    makerNote_.printMinoltaFNumberStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "1");
}

// Test with value = 8: (8/8) - 1 = 1 - 1 = 0
TEST_F(MinoltaMakerNoteTest_1002, PrintFNumberStd_Value8_Boundary_1002) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(8);

    makerNote_.printMinoltaFNumberStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "0");
}

// Test with value = 0: (0/8) - 1 = 0 - 1 = -1
TEST_F(MinoltaMakerNoteTest_1002, PrintFNumberStd_ValueZero_1002) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(0);

    makerNote_.printMinoltaFNumberStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "-1");
}

// Test with a negative value: (-8/8) - 1 = -1 - 1 = -2
TEST_F(MinoltaMakerNoteTest_1002, PrintFNumberStd_NegativeValue_1002) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(-8);

    makerNote_.printMinoltaFNumberStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "-2");
}

// Test with a large value: (800/8) - 1 = 100 - 1 = 99
TEST_F(MinoltaMakerNoteTest_1002, PrintFNumberStd_LargeValue_1002) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(800);

    makerNote_.printMinoltaFNumberStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "99");
}

// Test with value not divisible by 8: (10/8) - 1 = 1 - 1 = 0 (integer division)
TEST_F(MinoltaMakerNoteTest_1002, PrintFNumberStd_NotDivisibleBy8_1002) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(10);

    makerNote_.printMinoltaFNumberStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "0");
}

// Test with value = 1: (1/8) - 1 = 0 - 1 = -1 (integer division)
TEST_F(MinoltaMakerNoteTest_1002, PrintFNumberStd_Value1_1002) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(1);

    makerNote_.printMinoltaFNumberStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "-1");
}

// Test with value = 7: (7/8) - 1 = 0 - 1 = -1 (integer division)
TEST_F(MinoltaMakerNoteTest_1002, PrintFNumberStd_Value7_1002) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(7);

    makerNote_.printMinoltaFNumberStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "-1");
}

// Test that the function returns the same ostream reference
TEST_F(MinoltaMakerNoteTest_1002, PrintFNumberStd_ReturnsOstream_1002) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(24);

    std::ostream& result = makerNote_.printMinoltaFNumberStd(oss_, value, nullptr);
    EXPECT_EQ(&result, &oss_);
}

// Test with ExifData pointer being nullptr (should work without crashing)
TEST_F(MinoltaMakerNoteTest_1002, PrintFNumberStd_NullExifData_1002) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(32);

    // (32/8) - 1 = 4 - 1 = 3
    EXPECT_NO_THROW(makerNote_.printMinoltaFNumberStd(oss_, value, nullptr));
    EXPECT_EQ(oss_.str(), "3");
}

// Test with ExifData pointer being non-null (function should ignore it)
TEST_F(MinoltaMakerNoteTest_1002, PrintFNumberStd_NonNullExifData_1002) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(32);

    Exiv2::ExifData exifData;
    // (32/8) - 1 = 3
    makerNote_.printMinoltaFNumberStd(oss_, value, &exifData);
    EXPECT_EQ(oss_.str(), "3");
}

// Test with value = 9: (9/8) - 1 = 1 - 1 = 0
TEST_F(MinoltaMakerNoteTest_1002, PrintFNumberStd_Value9_1002) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(9);

    makerNote_.printMinoltaFNumberStd(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "0");
}
