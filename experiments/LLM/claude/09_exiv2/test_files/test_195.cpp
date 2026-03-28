#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the PentaxMakerNote class from the internal namespace
namespace Exiv2 {
namespace Internal {
class PentaxMakerNote {
public:
    std::ostream& printFocalLength(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class PentaxMakerNoteTest_195 : public ::testing::Test {
protected:
    PentaxMakerNote maker_;
    std::ostringstream oss_;
};

// Test normal focal length value
TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_NormalValue_195) {
    // 5000 / 100 = 50.0 mm
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("5000");
    maker_.printFocalLength(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "50.0 mm");
}

// Test focal length with fractional result
TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_FractionalValue_195) {
    // 3550 / 100 = 35.5 mm
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("3550");
    maker_.printFocalLength(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "35.5 mm");
}

// Test focal length with zero value
TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_ZeroValue_195) {
    // 0 / 100 = 0.0 mm
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("0");
    maker_.printFocalLength(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "0.0 mm");
}

// Test focal length with small value (less than 100)
TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_SmallValue_195) {
    // 50 / 100 = 0.5 mm
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("50");
    maker_.printFocalLength(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "0.5 mm");
}

// Test focal length with large value
TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_LargeValue_195) {
    // 120000 / 100 = 1200.0 mm
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("120000");
    maker_.printFocalLength(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "1200.0 mm");
}

// Test focal length with value of exactly 100
TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_ExactlyHundred_195) {
    // 100 / 100 = 1.0 mm
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("100");
    maker_.printFocalLength(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "1.0 mm");
}

// Test that nullptr ExifData is accepted without issues
TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_NullExifData_195) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("2400");
    maker_.printFocalLength(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "24.0 mm");
}

// Test that the function returns the same ostream reference
TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_ReturnsOstream_195) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("1000");
    std::ostream& result = maker_.printFocalLength(oss_, value, nullptr);
    EXPECT_EQ(&result, &oss_);
}

// Test focal length value of 1 (very small)
TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_ValueOne_195) {
    // 1 / 100 = 0.0 mm (rounded to 1 decimal)
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("1");
    maker_.printFocalLength(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "0.0 mm");
}

// Test with a typical prime lens focal length (e.g., 50mm = 5000)
TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_TypicalPrime50mm_195) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("5000");
    maker_.printFocalLength(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "50.0 mm");
}

// Test with a typical zoom lens focal length (e.g., 18mm = 1800)
TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_TypicalZoom18mm_195) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("1800");
    maker_.printFocalLength(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "18.0 mm");
}

// Test rounding behavior with values that have more than one decimal place
TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_RoundingBehavior_195) {
    // 3333 / 100 = 33.33 -> should display as 33.3
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("3333");
    maker_.printFocalLength(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "33.3 mm");
}

// Test with negative value (boundary/error case)
TEST_F(PentaxMakerNoteTest_195, PrintFocalLength_NegativeValue_195) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.read("-5000");
    maker_.printFocalLength(oss_, value, nullptr);
    EXPECT_EQ(oss_.str(), "-50.0 mm");
}
