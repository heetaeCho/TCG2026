#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLUtilTest_161 : public ::testing::Test {

protected:

    XMLUtil xmlUtil;

};



TEST_F(XMLUtilTest_161, SetBoolSerialization_DefaultValues_161) {

    char bufferTrue[5];

    char bufferFalse[6];

    xmlUtil.ToStr(true, bufferTrue, 5);

    xmlUtil.ToStr(false, bufferFalse, 6);

    EXPECT_STREQ(bufferTrue, "true");

    EXPECT_STREQ(bufferFalse, "false");

}



TEST_F(XMLUtilTest_161, SetBoolSerialization_CustomValues_161) {

    const char* customTrue = "yes";

    const char* customFalse = "no";

    xmlUtil.SetBoolSerialization(customTrue, customFalse);



    char bufferTrue[4];

    char bufferFalse[3];

    xmlUtil.ToStr(true, bufferTrue, 4);

    xmlUtil.ToStr(false, bufferFalse, 3);

    EXPECT_STREQ(bufferTrue, "yes");

    EXPECT_STREQ(bufferFalse, "no");

}



TEST_F(XMLUtilTest_161, SetBoolSerialization_NullValues_161) {

    xmlUtil.SetBoolSerialization(nullptr, nullptr);



    char bufferTrue[5];

    char bufferFalse[6];

    xmlUtil.ToStr(true, bufferTrue, 5);

    xmlUtil.ToStr(false, bufferFalse, 6);

    EXPECT_STREQ(bufferTrue, "true");

    EXPECT_STREQ(bufferFalse, "false");

}



TEST_F(XMLUtilTest_161, SetBoolSerialization_PartialNullValues_161) {

    const char* customTrue = "yes";

    xmlUtil.SetBoolSerialization(customTrue, nullptr);



    char bufferTrue[4];

    char bufferFalse[6];

    xmlUtil.ToStr(true, bufferTrue, 4);

    xmlUtil.ToStr(false, bufferFalse, 6);

    EXPECT_STREQ(bufferTrue, "yes");

    EXPECT_STREQ(bufferFalse, "false");

}



TEST_F(XMLUtilTest_161, SetBoolSerialization_PartialNullValues2_161) {

    const char* customFalse = "no";

    xmlUtil.SetBoolSerialization(nullptr, customFalse);



    char bufferTrue[5];

    char bufferFalse[3];

    xmlUtil.ToStr(true, bufferTrue, 5);

    xmlUtil.ToStr(false, bufferFalse, 3);

    EXPECT_STREQ(bufferTrue, "true");

    EXPECT_STREQ(bufferFalse, "no");

}
