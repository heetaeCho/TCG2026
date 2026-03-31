#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <array>

using namespace Exiv2;

class TimeValueTest_877 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test normal time value with positive timezone
TEST_F(TimeValueTest_877, CopyNormalPositiveTimezone_877) {
    TimeValue tv;
    // Set time to 13:25:07+05:30
    tv.setTime(TimeValue::Time{13, 25, 7, 5, 30});
    
    std::array<byte, 64> buf{};
    size_t wrote = tv.copy(buf.data(), littleEndian);
    
    EXPECT_EQ(wrote, 11u);
    std::string result(reinterpret_cast<char*>(buf.data()), 11);
    EXPECT_EQ(result, "132507+0530");
}

// Test time value with negative timezone
TEST_F(TimeValueTest_877, CopyNegativeTimezone_877) {
    TimeValue tv;
    // Set time with negative timezone offset
    tv.setTime(TimeValue::Time{8, 30, 0, -3, 0});
    
    std::array<byte, 64> buf{};
    size_t wrote = tv.copy(buf.data(), bigEndian);
    
    EXPECT_EQ(wrote, 11u);
    std::string result(reinterpret_cast<char*>(buf.data()), 11);
    EXPECT_EQ(result, "083000-0300");
}

// Test time value at midnight with zero timezone
TEST_F(TimeValueTest_877, CopyMidnightZeroTimezone_877) {
    TimeValue tv;
    tv.setTime(TimeValue::Time{0, 0, 0, 0, 0});
    
    std::array<byte, 64> buf{};
    size_t wrote = tv.copy(buf.data(), littleEndian);
    
    EXPECT_EQ(wrote, 11u);
    std::string result(reinterpret_cast<char*>(buf.data()), 11);
    EXPECT_EQ(result, "000000+0000");
}

// Test time value at end of day boundary (23:59:59)
TEST_F(TimeValueTest_877, CopyEndOfDayBoundary_877) {
    TimeValue tv;
    tv.setTime(TimeValue::Time{23, 59, 59, 0, 0});
    
    std::array<byte, 64> buf{};
    size_t wrote = tv.copy(buf.data(), littleEndian);
    
    EXPECT_EQ(wrote, 11u);
    std::string result(reinterpret_cast<char*>(buf.data()), 11);
    EXPECT_EQ(result, "235959+0000");
}

// Test time value with maximum positive timezone offset
TEST_F(TimeValueTest_877, CopyMaxPositiveTimezone_877) {
    TimeValue tv;
    tv.setTime(TimeValue::Time{12, 0, 0, 12, 0});
    
    std::array<byte, 64> buf{};
    size_t wrote = tv.copy(buf.data(), littleEndian);
    
    EXPECT_EQ(wrote, 11u);
    std::string result(reinterpret_cast<char*>(buf.data()), 11);
    EXPECT_EQ(result, "120000+1200");
}

// Test time value with negative timezone minutes
TEST_F(TimeValueTest_877, CopyNegativeTimezoneMinutes_877) {
    TimeValue tv;
    tv.setTime(TimeValue::Time{15, 45, 30, 0, -30});
    
    std::array<byte, 64> buf{};
    size_t wrote = tv.copy(buf.data(), littleEndian);
    
    EXPECT_EQ(wrote, 11u);
    std::string result(reinterpret_cast<char*>(buf.data()), 11);
    EXPECT_EQ(result, "154530-0030");
}

// Test that the copy returns exactly 11 bytes
TEST_F(TimeValueTest_877, CopyReturnsExactly11Bytes_877) {
    TimeValue tv;
    tv.setTime(TimeValue::Time{1, 2, 3, 4, 5});
    
    std::array<byte, 64> buf{};
    size_t wrote = tv.copy(buf.data(), littleEndian);
    
    EXPECT_EQ(wrote, 11u);
}

// Test with single digit values (padding with zeros)
TEST_F(TimeValueTest_877, CopySingleDigitValuesPadded_877) {
    TimeValue tv;
    tv.setTime(TimeValue::Time{1, 2, 3, 4, 5});
    
    std::array<byte, 64> buf{};
    size_t wrote = tv.copy(buf.data(), littleEndian);
    
    EXPECT_EQ(wrote, 11u);
    std::string result(reinterpret_cast<char*>(buf.data()), 11);
    EXPECT_EQ(result, "010203+0405");
}

// Test byte order independence (both little and big endian should produce same result)
TEST_F(TimeValueTest_877, CopyByteOrderIndependent_877) {
    TimeValue tv;
    tv.setTime(TimeValue::Time{10, 20, 30, 5, 0});
    
    std::array<byte, 64> buf1{};
    std::array<byte, 64> buf2{};
    
    size_t wrote1 = tv.copy(buf1.data(), littleEndian);
    size_t wrote2 = tv.copy(buf2.data(), bigEndian);
    
    EXPECT_EQ(wrote1, wrote2);
    EXPECT_EQ(std::memcmp(buf1.data(), buf2.data(), wrote1), 0);
}

// Test with negative hour timezone
TEST_F(TimeValueTest_877, CopyNegativeHourTimezone_877) {
    TimeValue tv;
    tv.setTime(TimeValue::Time{20, 15, 45, -8, 0});
    
    std::array<byte, 64> buf{};
    size_t wrote = tv.copy(buf.data(), littleEndian);
    
    EXPECT_EQ(wrote, 11u);
    std::string result(reinterpret_cast<char*>(buf.data()), 11);
    EXPECT_EQ(result, "201545-0800");
}

// Test from string and then copy
TEST_F(TimeValueTest_877, ReadAndCopyRoundTrip_877) {
    TimeValue tv;
    int rc = tv.read("120000+0000");
    EXPECT_EQ(rc, 0);
    
    std::array<byte, 64> buf{};
    size_t wrote = tv.copy(buf.data(), littleEndian);
    
    EXPECT_EQ(wrote, 11u);
    std::string result(reinterpret_cast<char*>(buf.data()), 11);
    EXPECT_EQ(result, "120000+0000");
}

// Test from string with negative timezone and then copy
TEST_F(TimeValueTest_877, ReadNegativeTimezoneAndCopy_877) {
    TimeValue tv;
    int rc = tv.read("093045-0530");
    EXPECT_EQ(rc, 0);
    
    std::array<byte, 64> buf{};
    size_t wrote = tv.copy(buf.data(), littleEndian);
    
    EXPECT_EQ(wrote, 11u);
    std::string result(reinterpret_cast<char*>(buf.data()), 11);
    EXPECT_EQ(result, "093045-0530");
}
