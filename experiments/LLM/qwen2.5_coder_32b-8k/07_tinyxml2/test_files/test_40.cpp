#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLUtilTest : public ::testing::Test {

protected:

    // No setup or teardown needed for this class

};



TEST_F(XMLUtilTest_40, StringEqual_SameStrings_40) {

    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hello"));

}



TEST_F(XMLUtilTest_40, StringEqual_DifferentStrings_40) {

    EXPECT_FALSE(XMLUtil::StringEqual("hello", "world"));

}



TEST_F(XMLUtilTest_40, StringEqual_SamePointers_40) {

    const char* str = "test";

    EXPECT_TRUE(XMLUtil::StringEqual(str, str));

}



TEST_F(XMLUtilTest_40, StringEqual_NullStrings_40) {

    EXPECT_THROW(XMLUtil::StringEqual(nullptr, nullptr), std::exception);

}



TEST_F(XMLUtilTest_40, StringEqual_FirstNull_40) {

    EXPECT_THROW(XMLUtil::StringEqual(nullptr, "test"), std::exception);

}



TEST_F(XMLUtilTest_40, StringEqual_SecondNull_40) {

    EXPECT_THROW(XMLUtil::StringEqual("test", nullptr), std::exception);

}



TEST_F(XMLUtilTest_40, StringEqual_SubstringMatch_40) {

    EXPECT_TRUE(XMLUtil::StringEqual("hello", "hellotest", 5));

}



TEST_F(XMLUtilTest_40, StringEqual_EmptyStrings_40) {

    EXPECT_TRUE(XMLUtil::StringEqual("", ""));

}



TEST_F(XMLUtilTest_40, StringEqual_DifferentLengths_40) {

    EXPECT_FALSE(XMLUtil::StringEqual("short", "a bit longer string"));

}



TEST_F(XMLUtilTest_40, StringEqual_LargeNChar_40) {

    const char* longStr = "averylongstringthatwilltestthenumberofcharacters";

    EXPECT_TRUE(XMLUtil::StringEqual(longStr, longStr, 100));

}
