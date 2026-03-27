#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "value.cpp"



namespace Exiv2 {

    class DateValueTest_865 : public ::testing::Test {

    protected:

        DateValue dateValue;

    };

}



using namespace Exiv2;



TEST_F(DateValueTest_865, CopyWritesCorrectFormat_865) {

    byte buffer[9]; // 8 characters for the formatted date + null terminator

    memset(buffer, 0, sizeof(buffer));

    size_t length = dateValue.copy(buffer, ByteOrder::bigEndian);



    EXPECT_EQ(length, 8);

    std::string expectedDate = "20000101"; // Assuming default constructed date is year=2000, month=1, day=1

    EXPECT_STREQ(reinterpret_cast<const char*>(buffer), expectedDate.c_str());

}



TEST_F(DateValueTest_865, CopyReturnsCorrectLength_865) {

    byte buffer[9];

    memset(buffer, 0, sizeof(buffer));

    size_t length = dateValue.copy(buffer, ByteOrder::bigEndian);



    EXPECT_EQ(length, 8);

}



TEST_F(DateValueTest_865, CopyDoesNotWriteBeyondBuffer_865) {

    byte buffer[1]; // Buffer too small to hold the formatted date

    memset(buffer, 0xFF, sizeof(buffer));

    size_t length = dateValue.copy(buffer, ByteOrder::bigEndian);



    EXPECT_EQ(length, 8);

    EXPECT_NE(buffer[0], 0); // First byte should be overwritten

}



TEST_F(DateValueTest_865, CopyBoundaryConditionYearMax_865) {

    DateValue maxYearDate;

    maxYearDate.date_.year = 9999;

    maxYearDate.date_.month = 12;

    maxYearDate.date_.day = 31;



    byte buffer[9];

    memset(buffer, 0, sizeof(buffer));

    size_t length = maxYearDate.copy(buffer, ByteOrder::bigEndian);



    EXPECT_EQ(length, 8);

    std::string expectedDate = "99991231";

    EXPECT_STREQ(reinterpret_cast<const char*>(buffer), expectedDate.c_str());

}



TEST_F(DateValueTest_865, CopyBoundaryConditionYearMin_865) {

    DateValue minYearDate;

    minYearDate.date_.year = 0;

    minYearDate.date_.month = 1;

    minYearDate.date_.day = 1;



    byte buffer[9];

    memset(buffer, 0, sizeof(buffer));

    size_t length = minYearDate.copy(buffer, ByteOrder::bigEndian);



    EXPECT_EQ(length, 8);

    std::string expectedDate = "00000101";

    EXPECT_STREQ(reinterpret_cast<const char*>(buffer), expectedDate.c_str());

}



TEST_F(DateValueTest_865, CopyBoundaryConditionMonthMin_865) {

    DateValue minMonthDate;

    minMonthDate.date_.year = 2000;

    minMonthDate.date_.month = 1;

    minMonthDate.date_.day = 1;



    byte buffer[9];

    memset(buffer, 0, sizeof(buffer));

    size_t length = minMonthDate.copy(buffer, ByteOrder::bigEndian);



    EXPECT_EQ(length, 8);

    std::string expectedDate = "20000101";

    EXPECT_STREQ(reinterpret_cast<const char*>(buffer), expectedDate.c_str());

}



TEST_F(DateValueTest_865, CopyBoundaryConditionMonthMax_865) {

    DateValue maxMonthDate;

    maxMonthDate.date_.year = 2000;

    maxMonthDate.date_.month = 12;

    maxMonthDate.date_.day = 31;



    byte buffer[9];

    memset(buffer, 0, sizeof(buffer));

    size_t length = maxMonthDate.copy(buffer, ByteOrder::bigEndian);



    EXPECT_EQ(length, 8);

    std::string expectedDate = "20001231";

    EXPECT_STREQ(reinterpret_cast<const char*>(buffer), expectedDate.c_str());

}



TEST_F(DateValueTest_865, CopyBoundaryConditionDayMin_865) {

    DateValue minDayDate;

    minDayDate.date_.year = 2000;

    minDayDate.date_.month = 1;

    minDayDate.date_.day = 1;



    byte buffer[9];

    memset(buffer, 0, sizeof(buffer));

    size_t length = minDayDate.copy(buffer, ByteOrder::bigEndian);



    EXPECT_EQ(length, 8);

    std::string expectedDate = "20000101";

    EXPECT_STREQ(reinterpret_cast<const char*>(buffer), expectedDate.c_str());

}



TEST_F(DateValueTest_865, CopyBoundaryConditionDayMax_865) {

    DateValue maxDayDate;

    maxDayDate.date_.year = 2000;

    maxDayDate.date_.month = 12;

    maxDayDate.date_.day = 31;



    byte buffer[9];

    memset(buffer, 0, sizeof(buffer));

    size_t length = maxDayDate.copy(buffer, ByteOrder::bigEndian);



    EXPECT_EQ(length, 8);

    std::string expectedDate = "20001231";

    EXPECT_STREQ(reinterpret_cast<const char*>(buffer), expectedDate.c_str());

}
