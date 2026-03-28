#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <cstdint>

// We need Exiv2 headers for Value and ExifData types
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// Include the implementation
#include "minoltamn_int.hpp"

// If the header doesn't expose the class directly, we may need to use the namespace
using namespace Exiv2;
using namespace Exiv2::Internal;

class MinoltaMakerNoteTest_1005 : public ::testing::Test {
protected:
    MinoltaMakerNote makerNote;
    std::ostringstream os;
};

// Test normal date value encoding: 2024/03/15
// Encoded as: 2024 * 65536 + 3 * 256 + 15 = 132710415
TEST_F(MinoltaMakerNoteTest_1005, PrintMinoltaDateStd_NormalDate_1005) {
    // year=2024, month=3, day=15
    // value = 2024*65536 + 3*256 + 15 = 132644864 + 768 + 15 = 132645647
    int64_t encoded = 2024LL * 65536 + 3 * 256 + 15;
    auto value = Value::AutoPtr(new ValueType<int32_t>());
    dynamic_cast<ValueType<int32_t>*>(value.get())->value_.push_back(static_cast<int32_t>(encoded));
    
    makerNote.printMinoltaDateStd(os, *value, nullptr);
    
    EXPECT_EQ(os.str(), "2024:03:15");
}

// Test date with month and day as single digits (should be zero-padded)
// year=2000, month=1, day=1
TEST_F(MinoltaMakerNoteTest_1005, PrintMinoltaDateStd_SingleDigitMonthDay_1005) {
    int64_t encoded = 2000LL * 65536 + 1 * 256 + 1;
    auto value = Value::AutoPtr(new ValueType<int32_t>());
    dynamic_cast<ValueType<int32_t>*>(value.get())->value_.push_back(static_cast<int32_t>(encoded));
    
    makerNote.printMinoltaDateStd(os, *value, nullptr);
    
    EXPECT_EQ(os.str(), "2000:01:01");
}

// Test date with December 31
TEST_F(MinoltaMakerNoteTest_1005, PrintMinoltaDateStd_December31_1005) {
    int64_t encoded = 2023LL * 65536 + 12 * 256 + 31;
    auto value = Value::AutoPtr(new ValueType<int32_t>());
    dynamic_cast<ValueType<int32_t>*>(value.get())->value_.push_back(static_cast<int32_t>(encoded));
    
    makerNote.printMinoltaDateStd(os, *value, nullptr);
    
    EXPECT_EQ(os.str(), "2023:12:31");
}

// Test with value zero: year=0, month=0, day=0
TEST_F(MinoltaMakerNoteTest_1005, PrintMinoltaDateStd_ZeroValue_1005) {
    auto value = Value::AutoPtr(new ValueType<int32_t>());
    dynamic_cast<ValueType<int32_t>*>(value.get())->value_.push_back(0);
    
    makerNote.printMinoltaDateStd(os, *value, nullptr);
    
    EXPECT_EQ(os.str(), "0:00:00");
}

// Test with a typical Minolta camera date: year=2005, month=06, day=20
TEST_F(MinoltaMakerNoteTest_1005, PrintMinoltaDateStd_TypicalMinoltaDate_1005) {
    int64_t encoded = 2005LL * 65536 + 6 * 256 + 20;
    auto value = Value::AutoPtr(new ValueType<int32_t>());
    dynamic_cast<ValueType<int32_t>*>(value.get())->value_.push_back(static_cast<int32_t>(encoded));
    
    makerNote.printMinoltaDateStd(os, *value, nullptr);
    
    EXPECT_EQ(os.str(), "2005:06:20");
}

// Test with year=1999, month=10, day=25
TEST_F(MinoltaMakerNoteTest_1005, PrintMinoltaDateStd_Year1999_1005) {
    int64_t encoded = 1999LL * 65536 + 10 * 256 + 25;
    auto value = Value::AutoPtr(new ValueType<int32_t>());
    dynamic_cast<ValueType<int32_t>*>(value.get())->value_.push_back(static_cast<int32_t>(encoded));
    
    makerNote.printMinoltaDateStd(os, *value, nullptr);
    
    EXPECT_EQ(os.str(), "1999:10:25");
}

// Test return value - should return the same ostream reference
TEST_F(MinoltaMakerNoteTest_1005, PrintMinoltaDateStd_ReturnsOstream_1005) {
    int64_t encoded = 2020LL * 65536 + 7 * 256 + 4;
    auto value = Value::AutoPtr(new ValueType<int32_t>());
    dynamic_cast<ValueType<int32_t>*>(value.get())->value_.push_back(static_cast<int32_t>(encoded));
    
    std::ostream& result = makerNote.printMinoltaDateStd(os, *value, nullptr);
    
    EXPECT_EQ(&result, &os);
}

// Test with month=0 and day=0 but valid year
TEST_F(MinoltaMakerNoteTest_1005, PrintMinoltaDateStd_ZeroMonthDay_1005) {
    int64_t encoded = 2010LL * 65536 + 0 * 256 + 0;
    auto value = Value::AutoPtr(new ValueType<int32_t>());
    dynamic_cast<ValueType<int32_t>*>(value.get())->value_.push_back(static_cast<int32_t>(encoded));
    
    makerNote.printMinoltaDateStd(os, *value, nullptr);
    
    EXPECT_EQ(os.str(), "2010:00:00");
}

// Test with ExifData pointer being nullptr (should not crash)
TEST_F(MinoltaMakerNoteTest_1005, PrintMinoltaDateStd_NullExifData_1005) {
    int64_t encoded = 2015LL * 65536 + 11 * 256 + 28;
    auto value = Value::AutoPtr(new ValueType<int32_t>());
    dynamic_cast<ValueType<int32_t>*>(value.get())->value_.push_back(static_cast<int32_t>(encoded));
    
    EXPECT_NO_THROW(makerNote.printMinoltaDateStd(os, *value, nullptr));
    EXPECT_EQ(os.str(), "2015:11:28");
}

// Test with small year value (year=1)
TEST_F(MinoltaMakerNoteTest_1005, PrintMinoltaDateStd_SmallYear_1005) {
    int64_t encoded = 1LL * 65536 + 1 * 256 + 1;
    auto value = Value::AutoPtr(new ValueType<int32_t>());
    dynamic_cast<ValueType<int32_t>*>(value.get())->value_.push_back(static_cast<int32_t>(encoded));
    
    makerNote.printMinoltaDateStd(os, *value, nullptr);
    
    EXPECT_EQ(os.str(), "1:01:01");
}

// Test boundary: day=255 (max value for byte), month=255
TEST_F(MinoltaMakerNoteTest_1005, PrintMinoltaDateStd_MaxMonthDayByte_1005) {
    int64_t encoded = 1LL * 65536 + 255 * 256 + 255;
    auto value = Value::AutoPtr(new ValueType<int32_t>());
    dynamic_cast<ValueType<int32_t>*>(value.get())->value_.push_back(static_cast<int32_t>(encoded));
    
    makerNote.printMinoltaDateStd(os, *value, nullptr);
    
    EXPECT_EQ(os.str(), "1:255:255");
}
