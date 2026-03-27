#include <gtest/gtest.h>

#include "catch2/internal/catch_string_manip.h"



using namespace Catch;



TEST_F(StringManipTest_587, EndsWidth_ReturnsTrue_WhenStringEndsWithSuffix_587) {

    EXPECT_TRUE(endsWith("hello!", '!'));

}



TEST_F(StringManipTest_587, EndsWidth_ReturnsFalse_WhenStringDoesNotEndWithSuffix_587) {

    EXPECT_FALSE(endsWith("hello", '!'));

}



TEST_F(StringManipTest_587, EndsWidth_ReturnsFalse_ForEmptyString_587) {

    EXPECT_FALSE(endsWith("", '!'));

}



TEST_F(StringManipTest_587, EndsWidth_HandlesSingleCharacterMatch_587) {

    EXPECT_TRUE(endsWith("!", '!'));

}



TEST_F(StringManipTest_587, EndsWidth_HandlesSingleCharacterNoMatch_587) {

    EXPECT_FALSE(endsWith("!", '?'));

}
