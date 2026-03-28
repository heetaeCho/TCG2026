#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "catch2/internal/catch_string_manip.h"



class CatchStringManipTest_584 : public ::testing::Test {

protected:

    // No additional setup needed for this test class

};



TEST_F(CatchStringManipTest_584, StartsWith_EmptyPrefix_ReturnsTrue_584) {

    EXPECT_TRUE(Catch::startsWith("hello", ""));

}



TEST_F(CatchStringManipTest_584, StartsWith_PrefixMatchesExactly_ReturnsTrue_584) {

    EXPECT_TRUE(Catch::startsWith("hello", "hello"));

}



TEST_F(CatchStringManipTest_584, StartsWith_StringLongerThanPrefixButMatches_ReturnsTrue_584) {

    EXPECT_TRUE(Catch::startsWith("hello world", "hello"));

}



TEST_F(CatchStringManipTest_584, StartsWith_PrefixDoesNotMatch_ReturnsFalse_584) {

    EXPECT_FALSE(Catch::startsWith("hello", "world"));

}



TEST_F(CatchStringManipTest_584, StartsWith_StringShorterThanPrefix_ReturnsFalse_584) {

    EXPECT_FALSE(Catch::startsWith("hi", "hello"));

}



TEST_F(CatchStringManipTest_584, StartsWith_CaseSensitiveMatch_ReturnsTrue_584) {

    EXPECT_TRUE(Catch::startsWith("Hello", "Hello"));

}



TEST_F(CatchStringManipTest_584, StartsWith_CaseInsensitiveMismatch_ReturnsFalse_584) {

    EXPECT_FALSE(Catch::startsWith("Hello", "hello"));

}
