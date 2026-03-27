#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <string>

#include "catch2/internal/catch_string_manip.cpp"



using namespace Catch;



class StringManipTest : public ::testing::Test {

protected:

    std::string testString;

};



TEST_F(StringManipTest_589, EmptyString_NoChange_589) {

    testString = "";

    toLowerInPlace(testString);

    EXPECT_EQ(testString, "");

}



TEST_F(StringManipTest_589, AlreadyLowerCase_NoChange_589) {

    testString = "alreadylowercase";

    toLowerInPlace(testString);

    EXPECT_EQ(testString, "alreadylowercase");

}



TEST_F(StringManipTest_589, MixedCase_ConvertedToLower_589) {

    testString = "MiXeDcAsE";

    toLowerInPlace(testString);

    EXPECT_EQ(testString, "mixedcase");

}



TEST_F(StringManipTest_589, UpperCase_ConvertedToLower_589) {

    testString = "UPPERCASE";

    toLowerInPlace(testString);

    EXPECT_EQ(testString, "uppercase");

}



TEST_F(StringManipTest_589, SpecialCharacters_NoChange_589) {

    testString = "!@#$%^&*()";

    toLowerInPlace(testString);

    EXPECT_EQ(testString, "!@#$%^&*()");

}



TEST_F(StringManipTest_589, Numbers_NoChange_589) {

    testString = "1234567890";

    toLowerInPlace(testString);

    EXPECT_EQ(testString, "1234567890");

}



TEST_F(StringManipTest_589, MixedWithSpecialCharacters_ConvertedToLower_589) {

    testString = "MiXeD!@#cAsE$%^";

    toLowerInPlace(testString);

    EXPECT_EQ(testString, "mixed!@#case$%^");

}



TEST_F(StringManipTest_589, LongString_ConvertedToLower_589) {

    testString = "THISISALONGSTRINGWITHMIXEDCASEANDSPECIALCHARACTERS!@#$%^&*()";

    toLowerInPlace(testString);

    EXPECT_EQ(testString, "thisisalongstringwithmixedcaseandspecialcharacters!@#$%^&*()");

}
