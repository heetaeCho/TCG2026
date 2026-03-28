#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Form.cc"  // Assuming Form.cc is in the include path or the same directory



using namespace testing;



TEST(setNextOffsetTest_1515, NormalOperation_1515) {

    char start[] = "Some data 9999999999 and more data";

    Goffset offset = 123456;

    char *result = setNextOffset(start, offset);

    EXPECT_STREQ(result, " 123456 ");

}



TEST(setNextOffsetTest_1515, BoundaryCondition_ZeroOffset_1515) {

    char start[] = "Some data 9999999999 and more data";

    Goffset offset = 0;

    char *result = setNextOffset(start, offset);

    EXPECT_STREQ(result, " 0 ");

}



TEST(setNextOffsetTest_1515, BoundaryCondition_MaxOffset_1515) {

    char start[] = "Some data 9999999999 and more data";

    Goffset offset = 9999999999;

    char *result = setNextOffset(start, offset);

    EXPECT_STREQ(result, " 9999999999 ");

}



TEST(setNextOffsetTest_1515, NotFoundMarker_1515) {

    char start[] = "Some data and more data";

    Goffset offset = 123456;

    char *result = setNextOffset(start, offset);

    EXPECT_EQ(result, nullptr);

}



TEST(setNextOffsetTest_1515, OverlappingMarker_1515) {

    char start[] = "Some data 99999999999 and more data";

    Goffset offset = 123456;

    char *result = setNextOffset(start, offset);

    EXPECT_STREQ(result, " 123456 ");

}



TEST(setNextOffsetTest_1515, MultipleMarkers_1515) {

    char start[] = "Some data 9999999999 and more data 9999999999";

    Goffset offset = 123456;

    char *result = setNextOffset(start, offset);

    EXPECT_STREQ(result, " 123456 ");

}
