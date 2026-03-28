#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLUtilTest_177 : public ::testing::Test {

protected:

    int64_t value;

};



TEST_F(XMLUtilTest_177, ToInt64_ValidDecimal_177) {

    const char* str = "12345";

    EXPECT_TRUE(XMLUtil::ToInt64(str, &value));

    EXPECT_EQ(value, 12345);

}



TEST_F(XMLUtilTest_177, ToInt64_ValidNegativeDecimal_177) {

    const char* str = "-12345";

    EXPECT_TRUE(XMLUtil::ToInt64(str, &value));

    EXPECT_EQ(value, -12345);

}



TEST_F(XMLUtilTest_177, ToInt64_ValidHex_177) {

    const char* str = "0x1A";

    EXPECT_TRUE(XMLUtil::ToInt64(str, &value));

    EXPECT_EQ(value, 26);

}



TEST_F(XMLUtilTest_177, ToInt64_ValidNegativeHex_177) {

    const char* str = "-0x1A";

    EXPECT_TRUE(XMLUtil::ToInt64(str, &value));

    EXPECT_EQ(value, -26);

}



TEST_F(XMLUtilTest_177, ToInt64_InvalidString_177) {

    const char* str = "abc";

    EXPECT_FALSE(XMLUtil::ToInt64(str, &value));

}



TEST_F(XMLUtilTest_177, ToInt64_EmptyString_177) {

    const char* str = "";

    EXPECT_FALSE(XMLUtil::ToInt64(str, &value));

}



TEST_F(XMLUtilTest_177, ToInt64_BoundaryMaxInt64_177) {

    const char* str = "9223372036854775807";

    EXPECT_TRUE(XMLUtil::ToInt64(str, &value));

    EXPECT_EQ(value, 9223372036854775807);

}



TEST_F(XMLUtilTest_177, ToInt64_BoundaryMinInt64_177) {

    const char* str = "-9223372036854775808";

    EXPECT_TRUE(XMLUtil::ToInt64(str, &value));

    EXPECT_EQ(value, -9223372036854775808);

}



TEST_F(XMLUtilTest_177, ToInt64_OutOfRangePositive_177) {

    const char* str = "9223372036854775808"; // 1 more than max int64

    EXPECT_FALSE(XMLUtil::ToInt64(str, &value));

}



TEST_F(XMLUtilTest_177, ToInt64_OutOfRangeNegative_177) {

    const char* str = "-9223372036854775809"; // 1 less than min int64

    EXPECT_FALSE(XMLUtil::ToInt64(str, &value));

}
