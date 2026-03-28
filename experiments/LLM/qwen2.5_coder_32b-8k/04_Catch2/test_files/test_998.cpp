#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/catch_test_case_info.hpp"



using namespace Catch;

using namespace testing;



class TestCaseInfoTest_998 : public ::testing::Test {

protected:

    SourceLineInfo lineInfo = {"filename.cpp", 10};

    NameAndTags nameAndTags = {"testName", "tag1,tag2"};

    TestCaseInfo testCaseInfo = TestCaseInfo("ClassName", nameAndTags, lineInfo);

};



TEST_F(TestCaseInfoTest_998, ExpectedToFail_ReturnsFalseWhenNoPropertiesSet_998) {

    EXPECT_FALSE(testCaseInfo.expectedToFail());

}



TEST_F(TestCaseInfoTest_998, ExpectedToFail_ReturnsTrueWhenShouldFailPropertySet_998) {

    testCaseInfo.properties = TestCaseProperties::ShouldFail;

    EXPECT_TRUE(testCaseInfo.expectedToFail());

}



TEST_F(TestCaseInfoTest_998, IsHidden_ReturnsFalseWhenNoPropertiesSet_998) {

    EXPECT_FALSE(testCaseInfo.isHidden());

}



TEST_F(TestCaseInfoTest_998, IsHidden_ReturnsTrueWhenIsHiddenPropertySet_998) {

    testCaseInfo.properties = TestCaseProperties::IsHidden;

    EXPECT_TRUE(testCaseInfo.isHidden());

}



TEST_F(TestCaseInfoTest_998, Throws_ReturnsFalseWhenNoPropertiesSet_998) {

    EXPECT_FALSE(testCaseInfo.throws());

}



TEST_F(TestCaseInfoTest_998, Throws_ReturnsTrueWhenThrowsPropertySet_998) {

    testCaseInfo.properties = TestCaseProperties::Throws;

    EXPECT_TRUE(testCaseInfo.throws());

}



TEST_F(TestCaseInfoTest_998, OkToFail_ReturnsFalseWhenNoPropertiesSet_998) {

    EXPECT_FALSE(testCaseInfo.okToFail());

}



TEST_F(TestCaseInfoTest_998, OkToFail_ReturnsTrueWhenMayFailPropertySet_998) {

    testCaseInfo.properties = TestCaseProperties::MayFail;

    EXPECT_TRUE(testCaseInfo.okToFail());

}



TEST_F(TestCaseInfoTest_998, TagsAsString_ReturnsCommaSeparatedTags_998) {

    EXPECT_EQ(testCaseInfo.tagsAsString(), "tag1,tag2");

}



TEST_F(TestCaseInfoTest_998, AddFilenameTag_AddsFilenameAsTag_998) {

    testCaseInfo.addFilenameTag();

    EXPECT_TRUE(testCaseInfo.tagsAsString().find("filename.cpp") != std::string::npos);

}
