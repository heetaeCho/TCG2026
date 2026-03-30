#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/catch_test_case_info.hpp"



using namespace Catch;

using ::testing::Return;



class TestCaseInfoTest : public ::testing::Test {

protected:

    TestCaseInfo test_case_info{"TestClass", {"testName"}, SourceLineInfo{"filename.cpp", 1}};

};



TEST_F(TestCaseInfoTest, Throws_ReturnsTrue_996) {

    test_case_info.properties = TestCaseProperties::Throws;

    EXPECT_TRUE(test_case_info.throws());

}



TEST_F(TestCaseInfoTest, Throws_ReturnsFalse_996) {

    test_case_info.properties = TestCaseProperties::None;

    EXPECT_FALSE(test_case_info.throws());

}



TEST_F(TestCaseInfoTest, IsHidden_ReturnsTrue_996) {

    test_case_info.properties = TestCaseProperties::IsHidden;

    EXPECT_TRUE(test_case_info.isHidden());

}



TEST_F(TestCaseInfoTest, IsHidden_ReturnsFalse_996) {

    test_case_info.properties = TestCaseProperties::None;

    EXPECT_FALSE(test_case_info.isHidden());

}



TEST_F(TestCaseInfoTest, OkToFail_ReturnsTrue_996) {

    test_case_info.properties = TestCaseProperties::MayFail;

    EXPECT_TRUE(test_case_info.okToFail());

}



TEST_F(TestCaseInfoTest, OkToFail_ReturnsFalse_996) {

    test_case_info.properties = TestCaseProperties::None;

    EXPECT_FALSE(test_case_info.okToFail());

}



TEST_F(TestCaseInfoTest, ExpectedToFail_ReturnsTrue_996) {

    test_case_info.properties = TestCaseProperties::ShouldFail;

    EXPECT_TRUE(test_case_info.expectedToFail());

}



TEST_F(TestCaseInfoTest, ExpectedToFail_ReturnsFalse_996) {

    test_case_info.properties = TestCaseProperties::None;

    EXPECT_FALSE(test_case_info.expectedToFail());

}
