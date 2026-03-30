#include <gtest/gtest.h>

#include "tinyxml2/tinyxml2.h"



using namespace tinyxml2;



TEST(IsPrefixHexTest_39, NormalOperation_HexPrefixLowerCase_39) {

    const char* input = " 0x1A";

    EXPECT_TRUE(XMLUtil::IsPrefixHex(input));

}



TEST(IsPrefixHexTest_39, NormalOperation_HexPrefixUpperCase_39) {

    const char* input = " 0X1A";

    EXPECT_TRUE(XMLUtil::IsPrefixHex(input));

}



TEST(IsPrefixHexTest_39, BoundaryCondition_NoLeadingWhitespace_39) {

    const char* input = "0x1A";

    EXPECT_TRUE(XMLUtil::IsPrefixHex(input));

}



TEST(IsPrefixHexTest_39, BoundaryCondition_EmptyString_39) {

    const char* input = "";

    EXPECT_FALSE(XMLUtil::IsPrefixHex(input));

}



TEST(IsPrefixHexTest_39, BoundaryCondition_SingleZero_39) {

    const char* input = "0";

    EXPECT_FALSE(XMLUtil::IsPrefixHex(input));

}



TEST(IsPrefixHexTest_39, BoundaryCondition_ZeroFollowedByXButNoNumber_39) {

    const char* input = "0x";

    EXPECT_FALSE(XMLUtil::IsPrefixHex(input));

}



TEST(IsPrefixHexTest_39, ExceptionalCase_InvalidHexPrefix_39) {

    const char* input = " 0y1A";

    EXPECT_FALSE(XMLUtil::IsPrefixHex(input));

}



TEST(IsPrefixHexTest_39, ExceptionalCase_NonNumericAfterPrefix_39) {

    const char* input = " 0xABG";

    EXPECT_TRUE(XMLUtil::IsPrefixHex(input)); // This should be true as it checks only the prefix

}
