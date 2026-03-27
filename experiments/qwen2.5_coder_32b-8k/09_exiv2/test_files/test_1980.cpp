#include <gtest/gtest.h>

#include "XMP_Const.h"

extern "C" {

    XMP_Int32 GatherInt(XMP_StringPtr strValue, size_t * _pos, const char * errMsg);

}



class GatherIntTest_1980 : public ::testing::Test {

protected:

    size_t pos;

    const char* errorMessage = "Invalid integer format";



    void SetUp() override {

        pos = 0;

    }

};



TEST_F(GatherIntTest_1980, ValidIntegerAtStart_1980) {

    XMP_StringPtr strValue = "12345";

    EXPECT_EQ(GatherInt(strValue, &pos, errorMessage), 12345);

    EXPECT_EQ(pos, 5);

}



TEST_F(GatherIntTest_1980, ValidIntegerInMiddle_1980) {

    XMP_StringPtr strValue = "abc678def";

    pos = 3;

    EXPECT_EQ(GatherInt(strValue, &pos, errorMessage), 678);

    EXPECT_EQ(pos, 6);

}



TEST_F(GatherIntTest_1980, LeadingZeros_1980) {

    XMP_StringPtr strValue = "00045";

    EXPECT_EQ(GatherInt(strValue, &pos, errorMessage), 45);

    EXPECT_EQ(pos, 5);

}



TEST_F(GatherIntTest_1980, MaxInteger_1980) {

    XMP_StringPtr strValue = "2147483647";

    EXPECT_EQ(GatherInt(strValue, &pos, errorMessage), std::numeric_limits<XMP_Int32>::max());

    EXPECT_EQ(pos, 10);

}



TEST_F(GatherIntTest_1980, IntegerOverflow_1980) {

    XMP_StringPtr strValue = "2147483648";

    EXPECT_THROW({

        GatherInt(strValue, &pos, errorMessage);

    }, XMP_Error);

}



TEST_F(GatherIntTest_1980, NoDigits_1980) {

    XMP_StringPtr strValue = "abc";

    EXPECT_THROW({

        GatherInt(strValue, &pos, errorMessage);

    }, XMP_Error);

}



TEST_F(GatherIntTest_1980, NegativeNumber_1980) {

    XMP_StringPtr strValue = "-123";

    EXPECT_THROW({

        GatherInt(strValue, &pos, errorMessage);

    }, XMP_Error);

}



TEST_F(GatherIntTest_1980, EmptyString_1980) {

    XMP_StringPtr strValue = "";

    EXPECT_THROW({

        GatherInt(strValue, &pos, errorMessage);

    }, XMP_Error);

}
