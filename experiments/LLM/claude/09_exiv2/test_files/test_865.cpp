#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>

// TEST_ID is 865

class DateValueTest_865 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that a normal date is copied correctly in YYYYMMDD format
TEST_F(DateValueTest_865, CopyNormalDate_865) {
    Exiv2::DateValue dv;
    // Set a known date via read method (string "2023-07-15" or "20230715")
    dv.read("2023-07-15");
    
    byte buf[16] = {};
    size_t len = dv.copy(buf, Exiv2::bigEndian);
    
    EXPECT_EQ(len, 8u);
    std::string result(reinterpret_cast<char*>(buf), len);
    EXPECT_EQ(result, "20230715");
}

// Test that single digit month and day are zero-padded
TEST_F(DateValueTest_865, CopyDateWithZeroPadding_865) {
    Exiv2::DateValue dv;
    dv.read("2000-01-01");
    
    byte buf[16] = {};
    size_t len = dv.copy(buf, Exiv2::littleEndian);
    
    EXPECT_EQ(len, 8u);
    std::string result(reinterpret_cast<char*>(buf), len);
    EXPECT_EQ(result, "20000101");
}

// Test boundary: year 0000 (or very small year)
TEST_F(DateValueTest_865, CopyDateYearZero_865) {
    Exiv2::DateValue dv;
    dv.read("0000-01-01");
    
    byte buf[16] = {};
    size_t len = dv.copy(buf, Exiv2::bigEndian);
    
    EXPECT_EQ(len, 8u);
    std::string result(reinterpret_cast<char*>(buf), len);
    EXPECT_EQ(result, "00000101");
}

// Test December 31st
TEST_F(DateValueTest_865, CopyDateDecember31_865) {
    Exiv2::DateValue dv;
    dv.read("1999-12-31");
    
    byte buf[16] = {};
    size_t len = dv.copy(buf, Exiv2::bigEndian);
    
    EXPECT_EQ(len, 8u);
    std::string result(reinterpret_cast<char*>(buf), len);
    EXPECT_EQ(result, "19991231");
}

// Test that byte order doesn't affect the output (since it's a text format)
TEST_F(DateValueTest_865, CopyByteOrderIndependent_865) {
    Exiv2::DateValue dv;
    dv.read("2024-06-15");
    
    byte buf1[16] = {};
    byte buf2[16] = {};
    size_t len1 = dv.copy(buf1, Exiv2::bigEndian);
    size_t len2 = dv.copy(buf2, Exiv2::littleEndian);
    
    EXPECT_EQ(len1, len2);
    EXPECT_EQ(std::memcmp(buf1, buf2, len1), 0);
}

// Test with a leap year date
TEST_F(DateValueTest_865, CopyLeapYearDate_865) {
    Exiv2::DateValue dv;
    dv.read("2024-02-29");
    
    byte buf[16] = {};
    size_t len = dv.copy(buf, Exiv2::bigEndian);
    
    EXPECT_EQ(len, 8u);
    std::string result(reinterpret_cast<char*>(buf), len);
    EXPECT_EQ(result, "20240229");
}

// Test that the return value matches the number of bytes written
TEST_F(DateValueTest_865, CopyReturnValueMatchesLength_865) {
    Exiv2::DateValue dv;
    dv.read("2023-11-05");
    
    byte buf[16] = {};
    size_t len = dv.copy(buf, Exiv2::bigEndian);
    
    // The date format YYYYMMDD is always 8 characters
    EXPECT_EQ(len, 8u);
}

// Test with a date set via the Date struct if available
TEST_F(DateValueTest_865, CopyAfterSetDate_865) {
    Exiv2::DateValue dv;
    Exiv2::DateValue::Date d;
    d.year = 2025;
    d.month = 3;
    d.day = 9;
    dv.setDate(d);
    
    byte buf[16] = {};
    size_t len = dv.copy(buf, Exiv2::bigEndian);
    
    EXPECT_EQ(len, 8u);
    std::string result(reinterpret_cast<char*>(buf), len);
    EXPECT_EQ(result, "20250309");
}

// Test default constructed DateValue
TEST_F(DateValueTest_865, CopyDefaultConstructed_865) {
    Exiv2::DateValue dv;
    
    byte buf[16] = {};
    size_t len = dv.copy(buf, Exiv2::bigEndian);
    
    // Default date should still produce 8 chars (likely 00000000)
    EXPECT_EQ(len, 8u);
}

// Test that month 10-12 are formatted without extra padding
TEST_F(DateValueTest_865, CopyTwoDigitMonth_865) {
    Exiv2::DateValue dv;
    dv.read("2023-10-25");
    
    byte buf[16] = {};
    size_t len = dv.copy(buf, Exiv2::bigEndian);
    
    EXPECT_EQ(len, 8u);
    std::string result(reinterpret_cast<char*>(buf), len);
    EXPECT_EQ(result, "20231025");
}
