#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

class DateValueTest_867 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor
TEST_F(DateValueTest_867, DefaultConstructor_867) {
    DateValue dv;
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 0);
    EXPECT_EQ(date.month, 0);
    EXPECT_EQ(date.day, 0);
}

// Test parameterized constructor
TEST_F(DateValueTest_867, ParameterizedConstructor_867) {
    DateValue dv(2023, 12, 25);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 12);
    EXPECT_EQ(date.day, 25);
}

// Test count returns size
TEST_F(DateValueTest_867, CountReturnsSize_867) {
    DateValue dv(2023, 1, 1);
    EXPECT_EQ(dv.count(), dv.size());
}

// Test size
TEST_F(DateValueTest_867, SizeValue_867) {
    DateValue dv(2023, 6, 15);
    EXPECT_GT(dv.size(), 0u);
}

// Test setDate
TEST_F(DateValueTest_867, SetDate_867) {
    DateValue dv;
    DateValue::Date date;
    date.year = 2000;
    date.month = 6;
    date.day = 15;
    dv.setDate(date);
    const DateValue::Date& result = dv.getDate();
    EXPECT_EQ(result.year, 2000);
    EXPECT_EQ(result.month, 6);
    EXPECT_EQ(result.day, 15);
}

// Test read from string with valid date
TEST_F(DateValueTest_867, ReadFromStringValid_867) {
    DateValue dv;
    int rc = dv.read("2023-07-04");
    EXPECT_EQ(rc, 0);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 7);
    EXPECT_EQ(date.day, 4);
}

// Test read from string with another valid format
TEST_F(DateValueTest_867, ReadFromStringAnotherFormat_867) {
    DateValue dv;
    int rc = dv.read("2000-01-01");
    EXPECT_EQ(rc, 0);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2000);
    EXPECT_EQ(date.month, 1);
    EXPECT_EQ(date.day, 1);
}

// Test read from string with invalid date
TEST_F(DateValueTest_867, ReadFromStringInvalid_867) {
    DateValue dv;
    int rc = dv.read("not-a-date");
    EXPECT_NE(rc, 0);
}

// Test read from string with empty string
TEST_F(DateValueTest_867, ReadFromStringEmpty_867) {
    DateValue dv;
    int rc = dv.read("");
    EXPECT_NE(rc, 0);
}

// Test write to ostream
TEST_F(DateValueTest_867, WriteToOstream_867) {
    DateValue dv(2023, 12, 25);
    std::ostringstream os;
    dv.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    // The output should contain the date in some format
    EXPECT_NE(result.find("2023"), std::string::npos);
}

// Test write default date to ostream
TEST_F(DateValueTest_867, WriteDefaultDateToOstream_867) {
    DateValue dv;
    std::ostringstream os;
    dv.write(os);
    std::string result = os.str();
    // Even default date should produce some output
    EXPECT_FALSE(result.empty());
}

// Test toInt64
TEST_F(DateValueTest_867, ToInt64_867) {
    DateValue dv(2023, 7, 4);
    int64_t val = dv.toInt64(0);
    // The value should represent the date in some numeric form (e.g., YYYYMMDD)
    EXPECT_NE(val, 0);
}

// Test toUint32
TEST_F(DateValueTest_867, ToUint32_867) {
    DateValue dv(2023, 7, 4);
    uint32_t val = dv.toUint32(0);
    EXPECT_NE(val, 0u);
}

// Test toFloat
TEST_F(DateValueTest_867, ToFloat_867) {
    DateValue dv(2023, 7, 4);
    float val = dv.toFloat(0);
    EXPECT_NE(val, 0.0f);
}

// Test toRational
TEST_F(DateValueTest_867, ToRational_867) {
    DateValue dv(2023, 7, 4);
    Rational val = dv.toRational(0);
    EXPECT_NE(val.first, 0);
}

// Test copy to buffer
TEST_F(DateValueTest_867, CopyToBuffer_867) {
    DateValue dv(2023, 7, 4);
    byte buf[16];
    std::memset(buf, 0, sizeof(buf));
    size_t copied = dv.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test read from byte buffer
TEST_F(DateValueTest_867, ReadFromByteBuffer_867) {
    // First create a DateValue and copy to buffer, then read back
    DateValue dv1(2023, 7, 4);
    byte buf[16];
    std::memset(buf, 0, sizeof(buf));
    size_t sz = dv1.copy(buf, littleEndian);

    DateValue dv2;
    int rc = dv2.read(buf, sz, littleEndian);
    EXPECT_EQ(rc, 0);
    const DateValue::Date& date = dv2.getDate();
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 7);
    EXPECT_EQ(date.day, 4);
}

// Test clone
TEST_F(DateValueTest_867, Clone_867) {
    DateValue dv(2023, 12, 25);
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    const DateValue::Date& date = cloned->getDate();
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 12);
    EXPECT_EQ(date.day, 25);
}

// Test boundary: leap year date
TEST_F(DateValueTest_867, LeapYearDate_867) {
    DateValue dv;
    int rc = dv.read("2024-02-29");
    EXPECT_EQ(rc, 0);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2024);
    EXPECT_EQ(date.month, 2);
    EXPECT_EQ(date.day, 29);
}

// Test boundary: year boundaries
TEST_F(DateValueTest_867, YearBoundary_867) {
    DateValue dv(9999, 12, 31);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 9999);
    EXPECT_EQ(date.month, 12);
    EXPECT_EQ(date.day, 31);
}

// Test count for default constructed value
TEST_F(DateValueTest_867, CountForDefault_867) {
    DateValue dv;
    // count() should equal size()
    EXPECT_EQ(dv.count(), dv.size());
}

// Test that setDate then getDate roundtrips
TEST_F(DateValueTest_867, SetDateGetDateRoundtrip_867) {
    DateValue dv;
    DateValue::Date date;
    date.year = 1999;
    date.month = 11;
    date.day = 30;
    dv.setDate(date);
    const DateValue::Date& retrieved = dv.getDate();
    EXPECT_EQ(retrieved.year, 1999);
    EXPECT_EQ(retrieved.month, 11);
    EXPECT_EQ(retrieved.day, 30);
}

// Test multiple reads overwrite previous value
TEST_F(DateValueTest_867, MultipleReadsOverwrite_867) {
    DateValue dv;
    dv.read("2020-01-01");
    EXPECT_EQ(dv.getDate().year, 2020);

    dv.read("2021-06-15");
    EXPECT_EQ(dv.getDate().year, 2021);
    EXPECT_EQ(dv.getDate().month, 6);
    EXPECT_EQ(dv.getDate().day, 15);
}

// Test write output format contains expected components
TEST_F(DateValueTest_867, WriteOutputFormat_867) {
    DateValue dv(1999, 1, 2);
    std::ostringstream os;
    dv.write(os);
    std::string result = os.str();
    EXPECT_NE(result.find("1999"), std::string::npos);
}

// Test consistency between toInt64 and toUint32
TEST_F(DateValueTest_867, ConsistencyInt64Uint32_867) {
    DateValue dv(2023, 7, 4);
    int64_t i64 = dv.toInt64(0);
    uint32_t u32 = dv.toUint32(0);
    // They should represent the same date numerically
    EXPECT_EQ(static_cast<int64_t>(u32), i64);
}
