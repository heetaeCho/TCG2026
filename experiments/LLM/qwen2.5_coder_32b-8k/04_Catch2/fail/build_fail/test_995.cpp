#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/Catch2/src/catch2/catch_test_case_info.hpp"



using namespace Catch;



class TestCaseInfoTest_995 : public ::testing::Test {

protected:

    TestCaseInfo test_case_info;

    

    TestCaseInfoTest_995() 

        : test_case_info("ClassName", {"TestCaseName"}, {"filename.cpp", 10}) {}

};



TEST_F(TestCaseInfoTest_995, IsHidden_ReturnsFalseByDefault_995) {

    EXPECT_FALSE(test_case_info.isHidden());

}



TEST_F(TestCaseInfoTest_995, Throws_ReturnsFalseByDefault_995) {

    EXPECT_FALSE(test_case_info.throws());

}



TEST_F(TestCaseInfoTest_995, OkToFail_ReturnsFalseByDefault_995) {

    EXPECT_FALSE(test_case_info.okToFail());

}



TEST_F(TestCaseInfoTest_995, ExpectedToFail_ReturnsFalseByDefault_995) {

    EXPECT_FALSE(test_case_info.expectedToFail());

}



TEST_F(TestCaseInfoTest_995, TagsAsString_ReturnsEmptyStringInitially_995) {

    EXPECT_EQ(test_case_info.tagsAsString(), "");

}



TEST_F(TestCaseInfoTest_995, AddFilenameTag_AddsFilenameTag_995) {

    test_case_info.addFilenameTag();

    EXPECT_TRUE(test_case_info.tagsAsString().find("[filename.cpp]") != std::string::npos);

}
