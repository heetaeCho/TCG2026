#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/types.cpp"

#include <ctime>



using namespace Exiv2;

using namespace testing;



TEST(exifTimeTest_1155, ValidInput_ReturnsZeroAndSetsTmStruct_1155) {

    tm timeinfo = {};

    int result = exifTime("2023:09:15 14:30:00", &timeinfo);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(timeinfo.tm_year, 123); // 2023 - 1900

    EXPECT_EQ(timeinfo.tm_mon, 8);   // September (0-based)

    EXPECT_EQ(timeinfo.tm_mday, 15);

    EXPECT_EQ(timeinfo.tm_hour, 14);

    EXPECT_EQ(timeinfo.tm_min, 30);

    EXPECT_EQ(timeinfo.tm_sec, 0);

}



TEST(exifTimeTest_1155, InvalidInput_ReturnsOneAndDoesNotModifyTmStruct_1155) {

    tm timeinfo = {0};

    int result = exifTime("invalid-date", &timeinfo);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(timeinfo.tm_year, 0);

    EXPECT_EQ(timeinfo.tm_mon, 0);

    EXPECT_EQ(timeinfo.tm_mday, 0);

    EXPECT_EQ(timeinfo.tm_hour, 0);

    EXPECT_EQ(timeinfo.tm_min, 0);

    EXPECT_EQ(timeinfo.tm_sec, 0);

}



TEST(exifTimeTest_1155, BoundaryCondition_StartOfYear_ReturnsZeroAndSetsTmStruct_1155) {

    tm timeinfo = {};

    int result = exifTime("2000:01:01 00:00:00", &timeinfo);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(timeinfo.tm_year, 100); // 2000 - 1900

    EXPECT_EQ(timeinfo.tm_mon, 0);   // January (0-based)

    EXPECT_EQ(timeinfo.tm_mday, 1);

    EXPECT_EQ(timeinfo.tm_hour, 0);

    EXPECT_EQ(timeinfo.tm_min, 0);

    EXPECT_EQ(timeinfo.tm_sec, 0);

}



TEST(exifTimeTest_1155, BoundaryCondition_EndOfYear_ReturnsZeroAndSetsTmStruct_1155) {

    tm timeinfo = {};

    int result = exifTime("2099:12:31 23:59:59", &timeinfo);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(timeinfo.tm_year, 199); // 2099 - 1900

    EXPECT_EQ(timeinfo.tm_mon, 11);  // December (0-based)

    EXPECT_EQ(timeinfo.tm_mday, 31);

    EXPECT_EQ(timeinfo.tm_hour, 23);

    EXPECT_EQ(timeinfo.tm_min, 59);

    EXPECT_EQ(timeinfo.tm_sec, 59);

}



TEST(exifTimeTest_1155, PartialBoundaryCondition_YearTooShort_ReturnsOneAndDoesNotModifyTmStruct_1155) {

    tm timeinfo = {0};

    int result = exifTime("23:09:15 14:30:00", &timeinfo);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(timeinfo.tm_year, 0);

    EXPECT_EQ(timeinfo.tm_mon, 0);

    EXPECT_EQ(timeinfo.tm_mday, 0);

    EXPECT_EQ(timeinfo.tm_hour, 0);

    EXPECT_EQ(timeinfo.tm_min, 0);

    EXPECT_EQ(timeinfo.tm_sec, 0);

}



TEST(exifTimeTest_1155, PartialBoundaryCondition_MonthTooShort_ReturnsOneAndDoesNotModifyTmStruct_1155) {

    tm timeinfo = {0};

    int result = exifTime("2023:9:15 14:30:00", &timeinfo);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(timeinfo.tm_year, 0);

    EXPECT_EQ(timeinfo.tm_mon, 0);

    EXPECT_EQ(timeinfo.tm_mday, 0);

    EXPECT_EQ(timeinfo.tm_hour, 0);

    EXPECT_EQ(timeinfo.tm_min, 0);

    EXPECT_EQ(timeinfo.tm_sec, 0);

}



TEST(exifTimeTest_1155, PartialBoundaryCondition_DayTooShort_ReturnsOneAndDoesNotModifyTmStruct_1155) {

    tm timeinfo = {0};

    int result = exifTime("2023:09:5 14:30:00", &timeinfo);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(timeinfo.tm_year, 0);

    EXPECT_EQ(timeinfo.tm_mon, 0);

    EXPECT_EQ(timeinfo.tm_mday, 0);

    EXPECT_EQ(timeinfo.tm_hour, 0);

    EXPECT_EQ(timeinfo.tm_min, 0);

    EXPECT_EQ(timeinfo.tm_sec, 0);

}



TEST(exifTimeTest_1155, PartialBoundaryCondition_HourTooShort_ReturnsOneAndDoesNotModifyTmStruct_1155) {

    tm timeinfo = {0};

    int result = exifTime("2023:09:15 4:30:00", &timeinfo);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(timeinfo.tm_year, 0);

    EXPECT_EQ(timeinfo.tm_mon, 0);

    EXPECT_EQ(timeinfo.tm_mday, 0);

    EXPECT_EQ(timeinfo.tm_hour, 0);

    EXPECT_EQ(timeinfo.tm_min, 0);

    EXPECT_EQ(timeinfo.tm_sec, 0);

}



TEST(exifTimeTest_1155, PartialBoundaryCondition_MinuteTooShort_ReturnsOneAndDoesNotModifyTmStruct_1155) {

    tm timeinfo = {0};

    int result = exifTime("2023:09:15 14:0:00", &timeinfo);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(timeinfo.tm_year, 0);

    EXPECT_EQ(timeinfo.tm_mon, 0);

    EXPECT_EQ(timeinfo.tm_mday, 0);

    EXPECT_EQ(timeinfo.tm_hour, 0);

    EXPECT_EQ(timeinfo.tm_min, 0);

    EXPECT_EQ(timeinfo.tm_sec, 0);

}



TEST(exifTimeTest_1155, PartialBoundaryCondition_SecondTooShort_ReturnsOneAndDoesNotModifyTmStruct_1155) {

    tm timeinfo = {0};

    int result = exifTime("2023:09:15 14:30:0", &timeinfo);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(timeinfo.tm_year, 0);

    EXPECT_EQ(timeinfo.tm_mon, 0);

    EXPECT_EQ(timeinfo.tm_mday, 0);

    EXPECT_EQ(timeinfo.tm_hour, 0);

    EXPECT_EQ(timeinfo.tm_min, 0);

    EXPECT_EQ(timeinfo.tm_sec, 0);

}
