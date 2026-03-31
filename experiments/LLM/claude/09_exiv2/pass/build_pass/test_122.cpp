#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "pentaxmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PentaxMakerNoteTest_122 : public ::testing::Test {
protected:
    std::ostringstream os;
    ExifData exifData;
};

// --- tagList tests ---

TEST_F(PentaxMakerNoteTest_122, TagListIsNotNull_122) {
    auto tagList = PentaxMakerNote::tagList();
    ASSERT_NE(tagList, nullptr);
}

TEST_F(PentaxMakerNoteTest_122, TagListFirstEntryHasValidTag_122) {
    auto tagList = PentaxMakerNote::tagList();
    // The first entry should have a valid tag (tag number >= 0)
    EXPECT_GE(tagList[0].tag_, 0);
}

// --- printVersion tests ---

TEST_F(PentaxMakerNoteTest_122, PrintVersionWithFourBytes_122) {
    DataValue value(unsignedByte);
    value.read("48 49 50 51");
    PentaxMakerNote::printVersion(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(PentaxMakerNoteTest_122, PrintVersionWithEmptyValue_122) {
    DataValue value(unsignedByte);
    PentaxMakerNote::printVersion(os, value, &exifData);
    std::string result = os.str();
    // Should produce some output even if empty
    EXPECT_TRUE(true); // Just ensure no crash
}

TEST_F(PentaxMakerNoteTest_122, PrintVersionWithSingleByte_122) {
    DataValue value(unsignedByte);
    value.read("1");
    PentaxMakerNote::printVersion(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// --- printResolution tests ---

TEST_F(PentaxMakerNoteTest_122, PrintResolutionNormal_122) {
    ULongValue value;
    value.read("3008");
    PentaxMakerNote::printResolution(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(PentaxMakerNoteTest_122, PrintResolutionZero_122) {
    ULongValue value;
    value.read("0");
    PentaxMakerNote::printResolution(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// --- printDate tests ---

TEST_F(PentaxMakerNoteTest_122, PrintDateWithSixBytes_122) {
    DataValue value(unsignedByte);
    // year(2 bytes) month day: 2023/06/15 => 07 E7 06 0F
    value.read("7 231 6 15");
    PentaxMakerNote::printDate(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(PentaxMakerNoteTest_122, PrintDateWithEmptyValue_122) {
    DataValue value(unsignedByte);
    PentaxMakerNote::printDate(os, value, &exifData);
    // Should not crash
    EXPECT_TRUE(true);
}

TEST_F(PentaxMakerNoteTest_122, PrintDateWithInsufficientBytes_122) {
    DataValue value(unsignedByte);
    value.read("7 231");
    PentaxMakerNote::printDate(os, value, &exifData);
    std::string result = os.str();
    // Should handle gracefully
    EXPECT_TRUE(true);
}

// --- printTime tests ---

TEST_F(PentaxMakerNoteTest_122, PrintTimeWithThreeBytes_122) {
    DataValue value(unsignedByte);
    // hour minute second: 14:30:45
    value.read("14 30 45");
    PentaxMakerNote::printTime(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(PentaxMakerNoteTest_122, PrintTimeWithEmptyValue_122) {
    DataValue value(unsignedByte);
    PentaxMakerNote::printTime(os, value, &exifData);
    EXPECT_TRUE(true); // No crash
}

// --- printExposure tests ---

TEST_F(PentaxMakerNoteTest_122, PrintExposureNormal_122) {
    ULongValue value;
    value.read("100");
    PentaxMakerNote::printExposure(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(PentaxMakerNoteTest_122, PrintExposureZero_122) {
    ULongValue value;
    value.read("0");
    PentaxMakerNote::printExposure(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(PentaxMakerNoteTest_122, PrintExposureLargeValue_122) {
    ULongValue value;
    value.read("1000000");
    PentaxMakerNote::printExposure(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// --- printFValue tests ---

TEST_F(PentaxMakerNoteTest_122, PrintFValueNormal_122) {
    ULongValue value;
    value.read("28");
    PentaxMakerNote::printFValue(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(PentaxMakerNoteTest_122, PrintFValueZero_122) {
    ULongValue value;
    value.read("0");
    PentaxMakerNote::printFValue(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// --- printFocalLength tests ---

TEST_F(PentaxMakerNoteTest_122, PrintFocalLengthNormal_122) {
    ULongValue value;
    value.read("500");
    PentaxMakerNote::printFocalLength(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(PentaxMakerNoteTest_122, PrintFocalLengthZero_122) {
    ULongValue value;
    value.read("0");
    PentaxMakerNote::printFocalLength(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// --- printCompensation tests ---

TEST_F(PentaxMakerNoteTest_122, PrintCompensationPositive_122) {
    ULongValue value;
    value.read("50");
    PentaxMakerNote::printCompensation(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(PentaxMakerNoteTest_122, PrintCompensationZero_122) {
    ULongValue value;
    value.read("0");
    PentaxMakerNote::printCompensation(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(PentaxMakerNoteTest_122, PrintCompensationHighValue_122) {
    ULongValue value;
    value.read("255");
    PentaxMakerNote::printCompensation(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// --- printTemperature tests ---

TEST_F(PentaxMakerNoteTest_122, PrintTemperatureNormal_122) {
    ULongValue value;
    value.read("75");
    PentaxMakerNote::printTemperature(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(PentaxMakerNoteTest_122, PrintTemperatureZero_122) {
    ULongValue value;
    value.read("0");
    PentaxMakerNote::printTemperature(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(PentaxMakerNoteTest_122, PrintTemperatureMax_122) {
    ULongValue value;
    value.read("255");
    PentaxMakerNote::printTemperature(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// --- printFlashCompensation tests ---

TEST_F(PentaxMakerNoteTest_122, PrintFlashCompensationNormal_122) {
    ULongValue value;
    value.read("50");
    PentaxMakerNote::printFlashCompensation(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(PentaxMakerNoteTest_122, PrintFlashCompensationZero_122) {
    ULongValue value;
    value.read("0");
    PentaxMakerNote::printFlashCompensation(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// --- printBracketing tests ---

TEST_F(PentaxMakerNoteTest_122, PrintBracketingNormal_122) {
    DataValue value(unsignedByte);
    value.read("10");
    PentaxMakerNote::printBracketing(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(PentaxMakerNoteTest_122, PrintBracketingZero_122) {
    DataValue value(unsignedByte);
    value.read("0");
    PentaxMakerNote::printBracketing(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// --- printShutterCount tests ---

TEST_F(PentaxMakerNoteTest_122, PrintShutterCountNormal_122) {
    DataValue value(unsignedByte);
    value.read("0 0 39 16");
    PentaxMakerNote::printShutterCount(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(PentaxMakerNoteTest_122, PrintShutterCountZero_122) {
    DataValue value(unsignedByte);
    value.read("0 0 0 0");
    PentaxMakerNote::printShutterCount(os, value, &exifData);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(PentaxMakerNoteTest_122, PrintShutterCountWithNullExifData_122) {
    DataValue value(unsignedByte);
    value.read("0 0 39 16");
    PentaxMakerNote::printShutterCount(os, value, nullptr);
    std::string result = os.str();
    // Should handle null exifData gracefully
    EXPECT_FALSE(result.empty());
}

// --- Return value tests (os reference) ---

TEST_F(PentaxMakerNoteTest_122, PrintVersionReturnsSameStream_122) {
    DataValue value(unsignedByte);
    value.read("1 2 3 4");
    std::ostream& returned = PentaxMakerNote::printVersion(os, value, &exifData);
    EXPECT_EQ(&returned, &os);
}

TEST_F(PentaxMakerNoteTest_122, PrintResolutionReturnsSameStream_122) {
    ULongValue value;
    value.read("3008");
    std::ostream& returned = PentaxMakerNote::printResolution(os, value, &exifData);
    EXPECT_EQ(&returned, &os);
}

TEST_F(PentaxMakerNoteTest_122, PrintDateReturnsSameStream_122) {
    DataValue value(unsignedByte);
    value.read("7 231 6 15");
    std::ostream& returned = PentaxMakerNote::printDate(os, value, &exifData);
    EXPECT_EQ(&returned, &os);
}

TEST_F(PentaxMakerNoteTest_122, PrintTimeReturnsSameStream_122) {
    DataValue value(unsignedByte);
    value.read("14 30 45");
    std::ostream& returned = PentaxMakerNote::printTime(os, value, &exifData);
    EXPECT_EQ(&returned, &os);
}

TEST_F(PentaxMakerNoteTest_122, PrintExposureReturnsSameStream_122) {
    ULongValue value;
    value.read("100");
    std::ostream& returned = PentaxMakerNote::printExposure(os, value, &exifData);
    EXPECT_EQ(&returned, &os);
}

TEST_F(PentaxMakerNoteTest_122, PrintFValueReturnsSameStream_122) {
    ULongValue value;
    value.read("28");
    std::ostream& returned = PentaxMakerNote::printFValue(os, value, &exifData);
    EXPECT_EQ(&returned, &os);
}

TEST_F(PentaxMakerNoteTest_122, PrintFocalLengthReturnsSameStream_122) {
    ULongValue value;
    value.read("500");
    std::ostream& returned = PentaxMakerNote::printFocalLength(os, value, &exifData);
    EXPECT_EQ(&returned, &os);
}

TEST_F(PentaxMakerNoteTest_122, PrintCompensationReturnsSameStream_122) {
    ULongValue value;
    value.read("50");
    std::ostream& returned = PentaxMakerNote::printCompensation(os, value, &exifData);
    EXPECT_EQ(&returned, &os);
}

TEST_F(PentaxMakerNoteTest_122, PrintTemperatureReturnsSameStream_122) {
    ULongValue value;
    value.read("75");
    std::ostream& returned = PentaxMakerNote::printTemperature(os, value, &exifData);
    EXPECT_EQ(&returned, &os);
}

TEST_F(PentaxMakerNoteTest_122, PrintFlashCompensationReturnsSameStream_122) {
    ULongValue value;
    value.read("50");
    std::ostream& returned = PentaxMakerNote::printFlashCompensation(os, value, &exifData);
    EXPECT_EQ(&returned, &os);
}

TEST_F(PentaxMakerNoteTest_122, PrintBracketingReturnsSameStream_122) {
    DataValue value(unsignedByte);
    value.read("10");
    std::ostream& returned = PentaxMakerNote::printBracketing(os, value, &exifData);
    EXPECT_EQ(&returned, &os);
}

TEST_F(PentaxMakerNoteTest_122, PrintShutterCountReturnsSameStream_122) {
    DataValue value(unsignedByte);
    value.read("0 0 39 16");
    std::ostream& returned = PentaxMakerNote::printShutterCount(os, value, &exifData);
    EXPECT_EQ(&returned, &os);
}

// --- Boundary: single byte value for multi-byte expected inputs ---

TEST_F(PentaxMakerNoteTest_122, PrintShutterCountSingleByte_122) {
    DataValue value(unsignedByte);
    value.read("5");
    PentaxMakerNote::printShutterCount(os, value, &exifData);
    // Should handle gracefully without crash
    EXPECT_TRUE(true);
}

TEST_F(PentaxMakerNoteTest_122, PrintDateSingleByte_122) {
    DataValue value(unsignedByte);
    value.read("7");
    PentaxMakerNote::printDate(os, value, &exifData);
    EXPECT_TRUE(true); // No crash
}

TEST_F(PentaxMakerNoteTest_122, PrintTimeSingleByte_122) {
    DataValue value(unsignedByte);
    value.read("14");
    PentaxMakerNote::printTime(os, value, &exifData);
    EXPECT_TRUE(true); // No crash
}

// --- Multiple calls to same function ---

TEST_F(PentaxMakerNoteTest_122, PrintVersionMultipleCalls_122) {
    DataValue value1(unsignedByte);
    value1.read("1 2 3 4");
    PentaxMakerNote::printVersion(os, value1, &exifData);
    std::string firstResult = os.str();

    std::ostringstream os2;
    DataValue value2(unsignedByte);
    value2.read("1 2 3 4");
    PentaxMakerNote::printVersion(os2, value2, &exifData);
    std::string secondResult = os2.str();

    EXPECT_EQ(firstResult, secondResult);
}
