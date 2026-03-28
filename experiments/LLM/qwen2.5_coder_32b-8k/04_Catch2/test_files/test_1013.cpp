#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.cpp"

#include "catch_interfaces_config.hpp"

#include "catch_test_case_info.hpp"



using namespace Catch;

using ::testing::Return;

using ::testing::NiceMock;



class MockConfig : public IConfig {

public:

    MOCK_METHOD(bool, allowThrows, (), (const, override));

    MOCK_METHOD(StringRef, name, (), (const, override));

    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));

    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));

    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));

    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));

    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));

    MOCK_METHOD(int, abortAfter, (), (const, override));

    MOCK_METHOD(bool, showInvisibles, (), (const, override));

    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));

    MOCK_METHOD(double, minDuration, (), (const, override));

    MOCK_METHOD(const TestSpec&, testSpec, (), (const, override));

    MOCK_METHOD(bool, hasTestFilters, (), (const, override));

    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const, override));

    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));

    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));

    MOCK_METHOD(unsigned int, shardCount, (), (const, override));

    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));

    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));

    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const, override));

    MOCK_METHOD(Verbosity, verbosity, (), (const, override));

    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));

    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));

    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));

    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));

    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));

    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));

};



class TestCaseInfoTest : public ::testing::Test {

protected:

    NiceMock<MockConfig> mockConfig;

    TestCaseInfo testCaseInfo{"ClassName", {"TestCaseName"}, SourceLineInfo{"filename.cpp", 1}};

};



TEST_F(TestCaseInfoTest_1013, Throws_ReturnsFalseWhenNoThrowTagPresent_1013) {

    EXPECT_FALSE(testCaseInfo.throws());

}



TEST_F(TestCaseInfoTest_1013, Throws_ReturnsTrueWhenThrowTagPresent_1013) {

    testCaseInfo.internalAppendTag("[throws]");

    EXPECT_TRUE(testCaseInfo.throws());

}



TEST_F(TestCaseInfoTest_1013, IsHidden_ReturnsFalseByDefault_1013) {

    EXPECT_FALSE(testCaseInfo.isHidden());

}



TEST_F(TestCaseInfoTest_1013, TagsAsString_ReturnsEmptyStringWhenNoTagsPresent_1013) {

    EXPECT_EQ(testCaseInfo.tagsAsString(), "");

}



TEST_F(TestCaseInfoTest_1013, TagsAsString_ReturnsConcatenatedTagStrings_1013) {

    testCaseInfo.internalAppendTag("[tag1]");

    testCaseInfo.internalAppendTag("[tag2]");

    EXPECT_EQ(testCaseInfo.tagsAsString(), "[tag1][tag2]");

}



TEST_F(TestCaseInfoTest_1013, IsHidden_ReturnsTrueWhenHiddenTagPresent_1013) {

    testCaseInfo.internalAppendTag("[.hidden]");

    EXPECT_TRUE(testCaseInfo.isHidden());

}



TEST_F(TestCaseInfoTest_1013, OkToFail_ReturnsFalseByDefault_1013) {

    EXPECT_FALSE(testCaseInfo.okToFail());

}



TEST_F(TestCaseInfoTest_1013, OkToFail_ReturnsTrueWhenFailingTagPresent_1013) {

    testCaseInfo.internalAppendTag("[failing]");

    EXPECT_TRUE(testCaseInfo.okToFail());

}



TEST_F(TestCaseInfoTest_1013, ExpectedToFail_ReturnsFalseByDefault_1013) {

    EXPECT_FALSE(testCaseInfo.expectedToFail());

}



TEST_F(TestCaseInfoTest_1013, ExpectedToFail_ReturnsTrueWhenExpectedFailureTagPresent_1013) {

    testCaseInfo.internalAppendTag("[shouldfail]");

    EXPECT_TRUE(testCaseInfo.expectedToFail());

}



class TestCaseHandleTest : public ::testing::Test {

protected:

    NiceMock<MockConfig> mockConfig;

    TestCaseInfo testCaseInfo{"ClassName", {"TestCaseName"}, SourceLineInfo{"filename.cpp", 1}};

    TestCaseHandle testCaseHandle{&testCaseInfo, nullptr};

};



TEST_F(TestCaseHandleTest_1013, GetTestCaseInfo_ReturnsCorrectTestCaseInfoReference_1013) {

    EXPECT_EQ(&testCaseHandle.getTestCaseInfo(), &testCaseInfo);

}



TEST_F(TestCaseHandleTest_1013, PrepareTestCase_DoesNotThrowForValidTestCase_1013) {

    EXPECT_NO_THROW(testCaseHandle.prepareTestCase());

}



TEST_F(TestCaseHandleTest_1013, TearDownTestCase_DoesNotThrowForValidTestCase_1013) {

    EXPECT_NO_THROW(testCaseHandle.tearDownTestCase());

}



TEST_F(TestCaseHandleTest_1013, Invoke_DoesNotThrowForValidTestCase_1013) {

    EXPECT_NO_THROW(testCaseHandle.invoke());

}
