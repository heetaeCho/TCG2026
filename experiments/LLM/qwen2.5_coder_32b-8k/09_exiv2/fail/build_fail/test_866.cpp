#include <gtest/gtest.h>

#include "exiv2/value.hpp"

#include <string>



namespace {



class DateValueTest_866 : public ::testing::Test {

protected:

    Exiv2::DateValue dateValue;

};



TEST_F(DateValueTest_866, DefaultConstructorInitializesDate_866) {

    const auto& date = dateValue.getDate();

    EXPECT_EQ(date.year(), 0);

    EXPECT_EQ(date.month(), 0);

    EXPECT_EQ(date.day(), 0);

}



TEST_F(DateValueTest_866, ParameterizedConstructorSetsCorrectDate_866) {

    Exiv2::DateValue specificDate(2023, 10, 5);

    const auto& date = specificDate.getDate();

    EXPECT_EQ(date.year(), 2023);

    EXPECT_EQ(date.month(), 10);

    EXPECT_EQ(date.day(), 5);

}



TEST_F(DateValueTest_866, SetDateUpdatesTheDateCorrectly_866) {

    Exiv2::Date newDate(2024, 1, 1);

    dateValue.setDate(newDate);

    const auto& date = dateValue.getDate();

    EXPECT_EQ(date.year(), 2024);

    EXPECT_EQ(date.month(), 1);

    EXPECT_EQ(date.day(), 1);

}



TEST_F(DateValueTest_866, ReadFromBufferUpdatesDateCorrectly_866) {

    // Assuming the buffer contains a valid date representation

    std::byte buf[] = {0x23, 0x0A, 0x05}; // Example byte values representing year, month, day

    dateValue.read(reinterpret_cast<const uint8_t*>(buf), sizeof(buf), Exiv2::bigEndian);

    const auto& date = dateValue.getDate();

    EXPECT_EQ(date.year(), 2023);

    EXPECT_EQ(date.month(), 10);

    EXPECT_EQ(date.day(), 5);

}



TEST_F(DateValueTest_866, ReadFromStringUpdatesDateCorrectly_866) {

    std::string dateString = "2023-10-05";

    dateValue.read(dateString);

    const auto& date = dateValue.getDate();

    EXPECT_EQ(date.year(), 2023);

    EXPECT_EQ(date.month(), 10);

    EXPECT_EQ(date.day(), 5);

}



TEST_F(DateValueTest_866, CopyMethodReturnsCorrectSize_866) {

    std::byte buf[10];

    size_t copiedSize = dateValue.copy(buf, Exiv2::bigEndian);

    EXPECT_EQ(copiedSize, sizeof(Exiv2::Date));

}



TEST_F(DateValueTest_866, CountMethodReturnsOneForSingleDate_866) {

    EXPECT_EQ(dateValue.count(), 1);

}



TEST_F(DateValueTest_866, SizeMethodReturnsCorrectSize_866) {

    EXPECT_EQ(dateValue.size(), sizeof(Exiv2::Date));

}



TEST_F(DateValueTest_866, WriteToStreamOutputsCorrectFormat_866) {

    std::ostringstream oss;

    dateValue.write(oss);

    // Assuming the default date (0-0-0) is represented as "0000:00:00" in output

    EXPECT_EQ(oss.str(), "0000:00:00");

}



TEST_F(DateValueTest_866, ToInt64ReturnsCorrectValue_866) {

    Exiv2::Date newDate(2023, 10, 5);

    dateValue.setDate(newDate);

    int64_t value = dateValue.toInt64(0);

    // Assuming the implementation returns a packed integer representation of the date

    EXPECT_EQ(value, static_cast<int64_t>(2023) * 10000 + 10 * 100 + 5);

}



TEST_F(DateValueTest_866, ToUint32ReturnsCorrectValue_866) {

    Exiv2::Date newDate(2023, 10, 5);

    dateValue.setDate(newDate);

    uint32_t value = dateValue.toUint32(0);

    // Assuming the implementation returns a packed integer representation of the date

    EXPECT_EQ(value, static_cast<uint32_t>(2023) * 10000 + 10 * 100 + 5);

}



TEST_F(DateValueTest_866, ToFloatReturnsCorrectValue_866) {

    Exiv2::Date newDate(2023, 10, 5);

    dateValue.setDate(newDate);

    float value = dateValue.toFloat(0);

    // Assuming the implementation returns a packed integer representation of the date as a float

    EXPECT_FLOAT_EQ(value, static_cast<float>(2023) * 10000 + 10 * 100 + 5);

}



TEST_F(DateValueTest_866, ToRationalReturnsCorrectValue_866) {

    Exiv2::Date newDate(2023, 10, 5);

    dateValue.setDate(newDate);

    Exiv2::Rational value = dateValue.toRational(0);

    // Assuming the implementation returns a packed integer representation of the date as a rational

    EXPECT_EQ(value.first, static_cast<int64_t>(2023) * 10000 + 10 * 100 + 5);

    EXPECT_EQ(value.second, 1);

}



} // namespace
