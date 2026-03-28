#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_test_case_info.hpp"



using namespace Catch;

using namespace testing;



class TestCaseInfoTest_997 : public Test {

protected:

    NameAndTags nameAndTags;

    SourceLineInfo lineInfo;

    std::string className = "TestClass";



    void SetUp() override {

        nameAndTags.name = "testName";

        nameAndTags.tags = "";

        lineInfo.file = "file.cpp";

        lineInfo.line = 42;

    }



    TestCaseInfo makeTestCaseInfo() {

        return TestCaseInfo(className, nameAndTags, lineInfo);

    }

};



TEST_F(TestCaseInfoTest_997, IsHidden_ReturnsFalseByDefault_997) {

    auto testCaseInfo = makeTestCaseInfo();

    EXPECT_FALSE(testCaseInfo.isHidden());

}



TEST_F(TestCaseInfoTest_997, Throws_ReturnsFalseByDefault_997) {

    auto testCaseInfo = makeTestCaseInfo();

    EXPECT_FALSE(testCaseInfo.throws());

}



TEST_F(TestCaseInfoTest_997, OkToFail_ReturnsFalseByDefault_997) {

    auto testCaseInfo = makeTestCaseInfo();

    EXPECT_FALSE(testCaseInfo.okToFail());

}



TEST_F(TestCaseInfoTest_997, ExpectedToFail_ReturnsFalseByDefault_997) {

    auto testCaseInfo = makeTestCaseInfo();

    EXPECT_FALSE(testCaseInfo.expectedToFail());

}



TEST_F(TestCaseInfoTest_997, TagsAsString_ReturnsEmptyStringWhenNoTags_997) {

    auto testCaseInfo = makeTestCaseInfo();

    EXPECT_EQ("", testCaseInfo.tagsAsString());

}



TEST_F(TestCaseInfoTest_997, AddFilenameTag_AddsFilenameAsTag_997) {

    auto testCaseInfo = makeTestCaseInfo();

    testCaseInfo.addFilenameTag();

    EXPECT_THAT(testCaseInfo.tagsAsString(), ContainsRegex("file.cpp"));

}



TEST_F(TestCaseInfoTest_997, OkToFail_ReturnsTrueWhenShouldFailPropertySet_997) {

    auto testCaseInfo = makeTestCaseInfo();

    testCaseInfo.properties = TestCaseProperties::ShouldFail;

    EXPECT_TRUE(testCaseInfo.okToFail());

}



TEST_F(TestCaseInfoTest_997, OkToFail_ReturnsTrueWhenMayFailPropertySet_997) {

    auto testCaseInfo = makeTestCaseInfo();

    testCaseInfo.properties = TestCaseProperties::MayFail;

    EXPECT_TRUE(testCaseInfo.okToFail());

}



TEST_F(TestCaseInfoTest_997, Throws_ReturnsTrueWhenThrowsPropertySet_997) {

    auto testCaseInfo = makeTestCaseInfo();

    testCaseInfo.properties = TestCaseProperties::Throws;

    EXPECT_TRUE(testCaseInfo.throws());

}
