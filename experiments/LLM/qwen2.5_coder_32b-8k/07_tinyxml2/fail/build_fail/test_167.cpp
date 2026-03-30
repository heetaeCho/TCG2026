#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLUtilTest : public ::testing::Test {

protected:

    char buffer[10];

};



TEST_F(XMLUtilTest_167, ToStr_BoolTrue_DefaultSerialization_167) {

    XMLUtil::ToStr(true, buffer, sizeof(buffer));

    EXPECT_STREQ("true", buffer);

}



TEST_F(XMLUtilTest_167, ToStr_BoolFalse_DefaultSerialization_167) {

    XMLUtil::ToStr(false, buffer, sizeof(buffer));

    EXPECT_STREQ("false", buffer);

}



TEST_F(XMLUtilTest_167, ToStr_BoolTrue_CustomSerialization_167) {

    XMLUtil::SetBoolSerialization("yes", "no");

    XMLUtil::ToStr(true, buffer, sizeof(buffer));

    EXPECT_STREQ("yes", buffer);

}



TEST_F(XMLUtilTest_167, ToStr_BoolFalse_CustomSerialization_167) {

    XMLUtil::SetBoolSerialization("yes", "no");

    XMLUtil::ToStr(false, buffer, sizeof(buffer));

    EXPECT_STREQ("no", buffer);

}



TEST_F(XMLUtilTest_167, ToStr_BufferTooSmall_167) {

    XMLUtil::ToStr(true, buffer, 2); // Only space for 't' and '\0'

    EXPECT_STREQ("t", buffer);

}



TEST_F(XMLUtilTest_167, ToStr_EmptyBuffer_167) {

    XMLUtil::ToStr(true, buffer, 0); // No space at all

    EXPECT_STREQ("", buffer);

}
