#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <cstdint>

// We need to include or replicate the minimal interface for Value and ExifData
// Since we're treating the implementation as a black box, we need the Exiv2 headers
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the header that declares the class under test
// Based on the file path, this would be:
#include "minoltamn_int.hpp"

namespace {

class MinoltaMakerNoteTest_1001 : public ::testing::Test {
protected:
    Exiv2::Internal::MinoltaMakerNote makerNote_;
    std::ostringstream os_;
};

// Test normal operation with a typical positive value
TEST_F(MinoltaMakerNoteTest_1001, PrintExposureTimeStd_NormalPositiveValue_1001) {
    // value = 56 => (56/8) - 6 = 7 - 6 = 1
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(56);
    
    auto& result = makerNote_.printMinoltaExposureTimeStd(os_, value, nullptr);
    
    EXPECT_EQ(os_.str(), "1");
    EXPECT_EQ(&result, &os_);
}

// Test with value that produces zero result
TEST_F(MinoltaMakerNoteTest_1001, PrintExposureTimeStd_ResultIsZero_1001) {
    // value = 48 => (48/8) - 6 = 6 - 6 = 0
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(48);
    
    makerNote_.printMinoltaExposureTimeStd(os_, value, nullptr);
    
    EXPECT_EQ(os_.str(), "0");
}

// Test with value that produces negative result
TEST_F(MinoltaMakerNoteTest_1001, PrintExposureTimeStd_NegativeResult_1001) {
    // value = 8 => (8/8) - 6 = 1 - 6 = -5
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(8);
    
    makerNote_.printMinoltaExposureTimeStd(os_, value, nullptr);
    
    EXPECT_EQ(os_.str(), "-5");
}

// Test with value zero
TEST_F(MinoltaMakerNoteTest_1001, PrintExposureTimeStd_ZeroValue_1001) {
    // value = 0 => (0/8) - 6 = 0 - 6 = -6
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(0);
    
    makerNote_.printMinoltaExposureTimeStd(os_, value, nullptr);
    
    EXPECT_EQ(os_.str(), "-6");
}

// Test with a larger value
TEST_F(MinoltaMakerNoteTest_1001, PrintExposureTimeStd_LargeValue_1001) {
    // value = 160 => (160/8) - 6 = 20 - 6 = 14
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(160);
    
    makerNote_.printMinoltaExposureTimeStd(os_, value, nullptr);
    
    EXPECT_EQ(os_.str(), "14");
}

// Test with value not divisible by 8 (integer division truncation)
TEST_F(MinoltaMakerNoteTest_1001, PrintExposureTimeStd_NotDivisibleBy8_1001) {
    // value = 50 => (50/8) - 6 = 6 - 6 = 0 (integer division: 50/8 = 6)
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(50);
    
    makerNote_.printMinoltaExposureTimeStd(os_, value, nullptr);
    
    EXPECT_EQ(os_.str(), "0");
}

// Test with value = 1 (boundary near zero)
TEST_F(MinoltaMakerNoteTest_1001, PrintExposureTimeStd_ValueOne_1001) {
    // value = 1 => (1/8) - 6 = 0 - 6 = -6
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(1);
    
    makerNote_.printMinoltaExposureTimeStd(os_, value, nullptr);
    
    EXPECT_EQ(os_.str(), "-6");
}

// Test with value = 7 (just below 8, integer division should give 0)
TEST_F(MinoltaMakerNoteTest_1001, PrintExposureTimeStd_ValueSeven_1001) {
    // value = 7 => (7/8) - 6 = 0 - 6 = -6
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(7);
    
    makerNote_.printMinoltaExposureTimeStd(os_, value, nullptr);
    
    EXPECT_EQ(os_.str(), "-6");
}

// Test with negative input value
TEST_F(MinoltaMakerNoteTest_1001, PrintExposureTimeStd_NegativeInputValue_1001) {
    // value = -16 => (-16/8) - 6 = -2 - 6 = -8
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(-16);
    
    makerNote_.printMinoltaExposureTimeStd(os_, value, nullptr);
    
    EXPECT_EQ(os_.str(), "-8");
}

// Test that the function returns a reference to the same ostream
TEST_F(MinoltaMakerNoteTest_1001, PrintExposureTimeStd_ReturnsOstreamReference_1001) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(48);
    
    std::ostream& returnedOs = makerNote_.printMinoltaExposureTimeStd(os_, value, nullptr);
    
    EXPECT_EQ(&returnedOs, &os_);
}

// Test with value = 8 (exactly one unit)
TEST_F(MinoltaMakerNoteTest_1001, PrintExposureTimeStd_ValueEight_1001) {
    // value = 8 => (8/8) - 6 = 1 - 6 = -5
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(8);
    
    makerNote_.printMinoltaExposureTimeStd(os_, value, nullptr);
    
    EXPECT_EQ(os_.str(), "-5");
}

// Test chaining - writing to stream that already has content
TEST_F(MinoltaMakerNoteTest_1001, PrintExposureTimeStd_AppendToExistingStream_1001) {
    os_ << "prefix:";
    
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(96); // (96/8) - 6 = 12 - 6 = 6
    
    makerNote_.printMinoltaExposureTimeStd(os_, value, nullptr);
    
    EXPECT_EQ(os_.str(), "prefix:6");
}

// Test with ExifData pointer being nullptr (should work fine)
TEST_F(MinoltaMakerNoteTest_1001, PrintExposureTimeStd_NullExifData_1001) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(80); // (80/8) - 6 = 10 - 6 = 4
    
    // Should not crash with nullptr ExifData
    EXPECT_NO_THROW(makerNote_.printMinoltaExposureTimeStd(os_, value, nullptr));
    EXPECT_EQ(os_.str(), "4");
}

} // namespace
