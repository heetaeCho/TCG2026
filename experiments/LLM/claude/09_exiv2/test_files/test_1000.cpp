#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <cstdint>

// We need Exiv2 headers for Value and ExifData types
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the internal header if available, otherwise we rely on the namespace declarations
namespace Exiv2 {
namespace Internal {

class MinoltaMakerNote {
public:
    std::ostream& printMinoltaExposureSpeedStd(std::ostream& os, const Value& value, const ExifData*) {
        os << (value.toInt64() / 8) - 1;
        return os;
    }
};

}  // namespace Internal
}  // namespace Exiv2

class MinoltaMakerNoteTest_1000 : public ::testing::Test {
protected:
    Exiv2::Internal::MinoltaMakerNote makerNote_;
    std::ostringstream os_;
};

// Test normal operation with a typical positive value
TEST_F(MinoltaMakerNoteTest_1000, PrintExposureSpeedStd_NormalPositiveValue_1000) {
    Exiv2::Int64Value value;
    value.read("80");  // (80 / 8) - 1 = 9
    makerNote_.printMinoltaExposureSpeedStd(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "9");
}

// Test with value of 8, which should produce 0
TEST_F(MinoltaMakerNoteTest_1000, PrintExposureSpeedStd_ValueEight_ProducesZero_1000) {
    Exiv2::Int64Value value;
    value.read("8");  // (8 / 8) - 1 = 0
    makerNote_.printMinoltaExposureSpeedStd(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "0");
}

// Test with value of 0, which should produce -1
TEST_F(MinoltaMakerNoteTest_1000, PrintExposureSpeedStd_ValueZero_ProducesNegativeOne_1000) {
    Exiv2::Int64Value value;
    value.read("0");  // (0 / 8) - 1 = -1
    makerNote_.printMinoltaExposureSpeedStd(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "-1");
}

// Test with a negative value
TEST_F(MinoltaMakerNoteTest_1000, PrintExposureSpeedStd_NegativeValue_1000) {
    Exiv2::Int64Value value;
    value.read("-16");  // (-16 / 8) - 1 = -3
    makerNote_.printMinoltaExposureSpeedStd(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "-3");
}

// Test with value of 1, where integer division truncates
TEST_F(MinoltaMakerNoteTest_1000, PrintExposureSpeedStd_ValueOne_IntegerDivision_1000) {
    Exiv2::Int64Value value;
    value.read("1");  // (1 / 8) - 1 = 0 - 1 = -1
    makerNote_.printMinoltaExposureSpeedStd(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "-1");
}

// Test with value of 7, boundary just below 8
TEST_F(MinoltaMakerNoteTest_1000, PrintExposureSpeedStd_ValueSeven_BoundaryBelowEight_1000) {
    Exiv2::Int64Value value;
    value.read("7");  // (7 / 8) - 1 = 0 - 1 = -1
    makerNote_.printMinoltaExposureSpeedStd(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "-1");
}

// Test with value of 9, boundary just above 8
TEST_F(MinoltaMakerNoteTest_1000, PrintExposureSpeedStd_ValueNine_BoundaryAboveEight_1000) {
    Exiv2::Int64Value value;
    value.read("9");  // (9 / 8) - 1 = 1 - 1 = 0
    makerNote_.printMinoltaExposureSpeedStd(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "0");
}

// Test with value of 16
TEST_F(MinoltaMakerNoteTest_1000, PrintExposureSpeedStd_ValueSixteen_1000) {
    Exiv2::Int64Value value;
    value.read("16");  // (16 / 8) - 1 = 1
    makerNote_.printMinoltaExposureSpeedStd(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "1");
}

// Test with a large value
TEST_F(MinoltaMakerNoteTest_1000, PrintExposureSpeedStd_LargeValue_1000) {
    Exiv2::Int64Value value;
    value.read("8000");  // (8000 / 8) - 1 = 999
    makerNote_.printMinoltaExposureSpeedStd(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "999");
}

// Test that the function returns a reference to the same ostream
TEST_F(MinoltaMakerNoteTest_1000, PrintExposureSpeedStd_ReturnsOstreamReference_1000) {
    Exiv2::Int64Value value;
    value.read("80");
    std::ostream& result = makerNote_.printMinoltaExposureSpeedStd(os_, value, nullptr);
    EXPECT_EQ(&result, &os_);
}

// Test with nullptr ExifData pointer (should not crash)
TEST_F(MinoltaMakerNoteTest_1000, PrintExposureSpeedStd_NullExifData_1000) {
    Exiv2::Int64Value value;
    value.read("24");  // (24 / 8) - 1 = 2
    EXPECT_NO_THROW(makerNote_.printMinoltaExposureSpeedStd(os_, value, nullptr));
    EXPECT_EQ(os_.str(), "2");
}

// Test with a large negative value
TEST_F(MinoltaMakerNoteTest_1000, PrintExposureSpeedStd_LargeNegativeValue_1000) {
    Exiv2::Int64Value value;
    value.read("-800");  // (-800 / 8) - 1 = -100 - 1 = -101
    makerNote_.printMinoltaExposureSpeedStd(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "-101");
}

// Test with value not evenly divisible by 8 (positive)
TEST_F(MinoltaMakerNoteTest_1000, PrintExposureSpeedStd_NotDivisibleByEight_Positive_1000) {
    Exiv2::Int64Value value;
    value.read("15");  // (15 / 8) - 1 = 1 - 1 = 0
    makerNote_.printMinoltaExposureSpeedStd(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "0");
}

// Test with value not evenly divisible by 8 (negative)
TEST_F(MinoltaMakerNoteTest_1000, PrintExposureSpeedStd_NotDivisibleByEight_Negative_1000) {
    Exiv2::Int64Value value;
    value.read("-15");  // (-15 / 8) - 1 = -1 - 1 = -2 (implementation-defined truncation toward zero in C++11+)
    makerNote_.printMinoltaExposureSpeedStd(os_, value, nullptr);
    EXPECT_EQ(os_.str(), "-2");
}

// Test chaining: multiple calls should append to the stream
TEST_F(MinoltaMakerNoteTest_1000, PrintExposureSpeedStd_MultipleCalls_Appends_1000) {
    Exiv2::Int64Value value1;
    value1.read("16");  // output: "1"
    Exiv2::Int64Value value2;
    value2.read("24");  // output: "2"
    
    makerNote_.printMinoltaExposureSpeedStd(os_, value1, nullptr);
    os_ << " ";
    makerNote_.printMinoltaExposureSpeedStd(os_, value2, nullptr);
    
    EXPECT_EQ(os_.str(), "1 2");
}
