#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/error.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

class DateValueTest_863 : public ::testing::Test {
protected:
    void SetUp() override {
        // Suppress warnings during tests
        LogMsg::setLevel(LogMsg::mute);
    }

    void TearDown() override {
        LogMsg::setLevel(LogMsg::warn);
    }
};

// ==================== read(const std::string&) tests ====================

TEST_F(DateValueTest_863, ReadValidDateWithDashes_863) {
    DateValue dv;
    int result = dv.read("2023-06-15");
    EXPECT_EQ(0, result);
    EXPECT_EQ(2023, dv.getDate().year);
    EXPECT_EQ(6, dv.getDate().month);
    EXPECT_EQ(15, dv.getDate().day);
}

TEST_F(DateValueTest_863, ReadValidDateWithoutDashes_863) {
    DateValue dv;
    int result = dv.read("20230615");
    EXPECT_EQ(0, result);
    EXPECT_EQ(2023, dv.getDate().year);
    EXPECT_EQ(6, dv.getDate().month);
    EXPECT_EQ(15, dv.getDate().day);
}

TEST_F(DateValueTest_863, ReadDateTooShort_863) {
    DateValue dv;
    int result = dv.read("2023061");
    EXPECT_EQ(1, result);
}

TEST_F(DateValueTest_863, ReadEmptyString_863) {
    DateValue dv;
    int result = dv.read("");
    EXPECT_EQ(1, result);
}

TEST_F(DateValueTest_863, ReadDateWithInvalidMonth_863) {
    DateValue dv;
    int result = dv.read("2023-13-15");
    EXPECT_EQ(1, result);
    EXPECT_EQ(0, dv.getDate().month);
    EXPECT_EQ(0, dv.getDate().day);
}

TEST_F(DateValueTest_863, ReadDateWithInvalidDay_863) {
    DateValue dv;
    int result = dv.read("2023-06-32");
    EXPECT_EQ(1, result);
    EXPECT_EQ(0, dv.getDate().month);
    EXPECT_EQ(0, dv.getDate().day);
}

TEST_F(DateValueTest_863, ReadDateMonth12Day31_863) {
    DateValue dv;
    int result = dv.read("2023-12-31");
    EXPECT_EQ(0, result);
    EXPECT_EQ(2023, dv.getDate().year);
    EXPECT_EQ(12, dv.getDate().month);
    EXPECT_EQ(31, dv.getDate().day);
}

TEST_F(DateValueTest_863, ReadDateMonth00_863) {
    DateValue dv;
    int result = dv.read("2023-00-15");
    EXPECT_EQ(0, result);
    EXPECT_EQ(0, dv.getDate().month);
    EXPECT_EQ(15, dv.getDate().day);
}

TEST_F(DateValueTest_863, ReadDateDay00_863) {
    DateValue dv;
    int result = dv.read("2023-06-00");
    EXPECT_EQ(0, result);
    EXPECT_EQ(6, dv.getDate().month);
    EXPECT_EQ(0, dv.getDate().day);
}

TEST_F(DateValueTest_863, ReadDateWithNonDigitYear_863) {
    DateValue dv;
    int result = dv.read("20a3-06-15");
    EXPECT_EQ(1, result);
}

TEST_F(DateValueTest_863, ReadDateWithNonDigitMonth_863) {
    DateValue dv;
    int result = dv.read("2023-0a-15");
    EXPECT_EQ(1, result);
}

TEST_F(DateValueTest_863, ReadDateWithNonDigitDay_863) {
    DateValue dv;
    int result = dv.read("2023-06-1a");
    EXPECT_EQ(1, result);
}

TEST_F(DateValueTest_863, ReadDateWithoutDashesNonDigit_863) {
    DateValue dv;
    int result = dv.read("2023a615");
    EXPECT_EQ(1, result);
}

TEST_F(DateValueTest_863, ReadDateWithWrongSeparatorFormat_863) {
    DateValue dv;
    int result = dv.read("2023/06/15");
    EXPECT_EQ(1, result);
}

TEST_F(DateValueTest_863, ReadDateWith9CharsInvalid_863) {
    DateValue dv;
    int result = dv.read("2023-0615");
    EXPECT_EQ(1, result);
}

TEST_F(DateValueTest_863, ReadDateYear0000_863) {
    DateValue dv;
    int result = dv.read("0000-01-01");
    EXPECT_EQ(0, result);
    EXPECT_EQ(0, dv.getDate().year);
    EXPECT_EQ(1, dv.getDate().month);
    EXPECT_EQ(1, dv.getDate().day);
}

TEST_F(DateValueTest_863, ReadDateWithoutDashesAllZeros_863) {
    DateValue dv;
    int result = dv.read("00000000");
    EXPECT_EQ(0, result);
    EXPECT_EQ(0, dv.getDate().year);
    EXPECT_EQ(0, dv.getDate().month);
    EXPECT_EQ(0, dv.getDate().day);
}

TEST_F(DateValueTest_863, ReadDateLongerThan10WithDashes_863) {
    DateValue dv;
    int result = dv.read("2023-06-15extra");
    EXPECT_EQ(0, result);
    EXPECT_EQ(2023, dv.getDate().year);
    EXPECT_EQ(6, dv.getDate().month);
    EXPECT_EQ(15, dv.getDate().day);
}

TEST_F(DateValueTest_863, ReadDateExactly10Chars_863) {
    DateValue dv;
    int result = dv.read("2023-06-15");
    EXPECT_EQ(0, result);
    EXPECT_EQ(2023, dv.getDate().year);
    EXPECT_EQ(6, dv.getDate().month);
    EXPECT_EQ(15, dv.getDate().day);
}

TEST_F(DateValueTest_863, ReadDateWithFirstDashButNotSecond_863) {
    DateValue dv;
    int result = dv.read("2023-06115");
    EXPECT_EQ(1, result);
}

// ==================== Constructor tests ====================

TEST_F(DateValueTest_863, DefaultConstructor_863) {
    DateValue dv;
    EXPECT_EQ(0, dv.getDate().year);
    EXPECT_EQ(0, dv.getDate().month);
    EXPECT_EQ(0, dv.getDate().day);
}

TEST_F(DateValueTest_863, ParameterizedConstructor_863) {
    DateValue dv(2023, 6, 15);
    EXPECT_EQ(2023, dv.getDate().year);
    EXPECT_EQ(6, dv.getDate().month);
    EXPECT_EQ(15, dv.getDate().day);
}

// ==================== setDate tests ====================

TEST_F(DateValueTest_863, SetDate_863) {
    DateValue dv;
    DateValue::Date d;
    d.year = 2020;
    d.month = 3;
    d.day = 25;
    dv.setDate(d);
    EXPECT_EQ(2020, dv.getDate().year);
    EXPECT_EQ(3, dv.getDate().month);
    EXPECT_EQ(25, dv.getDate().day);
}

// ==================== count and size tests ====================

TEST_F(DateValueTest_863, CountReturns1_863) {
    DateValue dv;
    EXPECT_EQ(1u, dv.count());
}

TEST_F(DateValueTest_863, SizeReturns8_863) {
    DateValue dv;
    EXPECT_EQ(8u, dv.size());
}

// ==================== write tests ====================

TEST_F(DateValueTest_863, WriteFormatsCorrectly_863) {
    DateValue dv(2023, 6, 15);
    std::ostringstream os;
    dv.write(os);
    EXPECT_EQ("2023-06-15", os.str());
}

TEST_F(DateValueTest_863, WriteFormatsWithLeadingZeros_863) {
    DateValue dv(2023, 1, 5);
    std::ostringstream os;
    dv.write(os);
    EXPECT_EQ("2023-01-05", os.str());
}

// ==================== copy tests ====================

TEST_F(DateValueTest_863, CopyToBuffer_863) {
    DateValue dv(2023, 6, 15);
    byte buf[8];
    std::memset(buf, 0, sizeof(buf));
    size_t copied = dv.copy(buf, littleEndian);
    EXPECT_EQ(8u, copied);
    // The copy should write "20230615" as ASCII
    std::string result(reinterpret_cast<char*>(buf), 8);
    EXPECT_EQ("20230615", result);
}

// ==================== toInt64 / toUint32 / toFloat / toRational tests ====================

TEST_F(DateValueTest_863, ToInt64_863) {
    DateValue dv(2023, 6, 15);
    // Expected: year * 10000 + month * 100 + day = 20230615
    int64_t val = dv.toInt64(0);
    EXPECT_EQ(20230615, val);
}

TEST_F(DateValueTest_863, ToUint32_863) {
    DateValue dv(2023, 6, 15);
    uint32_t val = dv.toUint32(0);
    EXPECT_EQ(20230615u, val);
}

TEST_F(DateValueTest_863, ToFloat_863) {
    DateValue dv(2023, 6, 15);
    float val = dv.toFloat(0);
    EXPECT_FLOAT_EQ(20230615.0f, val);
}

TEST_F(DateValueTest_863, ToRational_863) {
    DateValue dv(2023, 6, 15);
    Rational r = dv.toRational(0);
    EXPECT_EQ(20230615, r.first);
    EXPECT_EQ(1, r.second);
}

// ==================== clone tests ====================

TEST_F(DateValueTest_863, Clone_863) {
    DateValue dv(2023, 6, 15);
    auto cloned = dv.clone();
    ASSERT_NE(nullptr, cloned.get());
    // Cast to DateValue to access getDate
    DateValue* clonedDv = dynamic_cast<DateValue*>(cloned.get());
    ASSERT_NE(nullptr, clonedDv);
    EXPECT_EQ(2023, clonedDv->getDate().year);
    EXPECT_EQ(6, clonedDv->getDate().month);
    EXPECT_EQ(15, clonedDv->getDate().day);
}

// ==================== read(const byte*, size_t, ByteOrder) tests ====================

TEST_F(DateValueTest_863, ReadFromByteBuffer_863) {
    DateValue dv;
    const std::string dateStr = "20230615";
    int result = dv.read(reinterpret_cast<const byte*>(dateStr.c_str()), dateStr.size(), littleEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ(2023, dv.getDate().year);
    EXPECT_EQ(6, dv.getDate().month);
    EXPECT_EQ(15, dv.getDate().day);
}

TEST_F(DateValueTest_863, ReadFromByteBufferWithDashes_863) {
    DateValue dv;
    const std::string dateStr = "2023-06-15";
    int result = dv.read(reinterpret_cast<const byte*>(dateStr.c_str()), dateStr.size(), littleEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ(2023, dv.getDate().year);
    EXPECT_EQ(6, dv.getDate().month);
    EXPECT_EQ(15, dv.getDate().day);
}

// ==================== Boundary: Month and Day boundary values ====================

TEST_F(DateValueTest_863, ReadDateMonth01Day01_863) {
    DateValue dv;
    int result = dv.read("2023-01-01");
    EXPECT_EQ(0, result);
    EXPECT_EQ(1, dv.getDate().month);
    EXPECT_EQ(1, dv.getDate().day);
}

TEST_F(DateValueTest_863, ReadDateMonth12Day31Boundary_863) {
    DateValue dv;
    int result = dv.read("9999-12-31");
    EXPECT_EQ(0, result);
    EXPECT_EQ(9999, dv.getDate().year);
    EXPECT_EQ(12, dv.getDate().month);
    EXPECT_EQ(31, dv.getDate().day);
}

TEST_F(DateValueTest_863, ReadDateWithSpacesInvalid_863) {
    DateValue dv;
    int result = dv.read("2023 06 15");
    EXPECT_EQ(1, result);
}

TEST_F(DateValueTest_863, ReadDateAllNonDigits_863) {
    DateValue dv;
    int result = dv.read("abcdefgh");
    EXPECT_EQ(1, result);
}

TEST_F(DateValueTest_863, ReadDateWithOnlyDashes_863) {
    DateValue dv;
    int result = dv.read("----.--.--");
    EXPECT_EQ(1, result);
}
