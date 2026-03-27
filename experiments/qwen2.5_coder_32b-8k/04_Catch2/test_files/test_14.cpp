#include <gtest/gtest.h>

#include "catch2/internal/catch_stringref.hpp"



class CatchStringRefTest_14 : public ::testing::Test {

protected:

    // Setup and teardown can be done here if needed.

};



TEST_F(CatchStringRefTest_14, DefaultConstructorCreatesEmptyString_14) {

    Catch::StringRef strRef;

    EXPECT_EQ(strRef.size(), 0);

    EXPECT_TRUE(strRef.empty());

}



TEST_F(CatchStringRefTest_14, ParameterizedConstructorInitializesCorrectly_14) {

    const char* testStr = "Hello";

    Catch::StringRef strRef(testStr, 5);

    EXPECT_EQ(strRef.size(), 5);

    EXPECT_FALSE(strRef.empty());

    EXPECT_STREQ(strRef.data(), testStr);

}



TEST_F(CatchStringRefTest_14, ParameterizedConstructorWithLiteralOperatorInitializesCorrectly_14) {

    auto strRef = "Hello"_catch_sr;

    EXPECT_EQ(strRef.size(), 5);

    EXPECT_FALSE(strRef.empty());

    EXPECT_STREQ(strRef.data(), "Hello");

}



TEST_F(CatchStringRefTest_14, EmptyStringHasZeroLength_14) {

    Catch::StringRef emptyStr("");

    EXPECT_EQ(emptyStr.size(), 0);

    EXPECT_TRUE(emptyStr.empty());

}



TEST_F(CatchStringRefTest_14, DataPointsToCorrectMemory_14) {

    const char* testStr = "World";

    Catch::StringRef strRef(testStr, 5);

    EXPECT_EQ(strRef.data(), testStr);

}



TEST_F(CatchStringRefTest_14, SubstrReturnsCorrectSubstring_14) {

    auto strRef = "HelloWorld"_catch_sr;

    auto subStrRef = strRef.substr(5, 5);

    EXPECT_EQ(subStrRef.size(), 5);

    EXPECT_STREQ(subStrRef.data(), "World");

}



TEST_F(CatchStringRefTest_14, SubstrHandlesBoundaryConditions_14) {

    auto strRef = "Hello"_catch_sr;

    auto subStrRef = strRef.substr(2, 3);

    EXPECT_EQ(subStrRef.size(), 3);

    EXPECT_STREQ(subStrRef.data(), "llo");



    auto emptySubStrRef = strRef.substr(5, 1);

    EXPECT_EQ(emptySubStrRef.size(), 0);

    EXPECT_TRUE(emptySubStrRef.empty());



    auto fullSubStrRef = strRef.substr(0, 5);

    EXPECT_EQ(fullSubStrRef.size(), 5);

    EXPECT_STREQ(fullSubStrRef.data(), "Hello");

}



TEST_F(CatchStringRefTest_14, SubstrWithInvalidLengthClampsToSize_14) {

    auto strRef = "Hello"_catch_sr;

    auto subStrRef = strRef.substr(2, 10);

    EXPECT_EQ(subStrRef.size(), 3);

    EXPECT_STREQ(subStrRef.data(), "llo");

}
