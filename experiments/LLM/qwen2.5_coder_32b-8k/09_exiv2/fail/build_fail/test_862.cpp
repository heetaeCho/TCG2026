#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/value.cpp"



using namespace Exiv2;

using namespace testing;



class DateValueTest_862 : public ::testing::Test {

protected:

    DateValue dateValue;

};



TEST_F(DateValueTest_862, ReadValidDate_862) {

    const char* buf = "2023:10:05 14:30:00";

    size_t len = strlen(buf);

    EXPECT_EQ(dateValue.read(reinterpret_cast<const byte*>(buf), len, littleEndian), 0);

}



TEST_F(DateValueTest_862, ReadEmptyString_862) {

    const char* buf = "";

    size_t len = strlen(buf);

    EXPECT_EQ(dateValue.read(reinterpret_cast<const byte*>(buf), len, littleEndian), 0);

}



TEST_F(DateValueTest_862, ReadBoundaryLength_862) {

    const char* buf = "A";

    size_t len = strlen(buf);

    EXPECT_EQ(dateValue.read(reinterpret_cast<const byte*>(buf), len, littleEndian), 0);

}



TEST_F(DateValueTest_862, ReadInvalidDate_862) {

    const char* buf = "InvalidDate";

    size_t len = strlen(buf);

    EXPECT_EQ(dateValue.read(reinterpret_cast<const byte*>(buf), len, littleEndian), 0);

}
