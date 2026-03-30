#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_test_spec.hpp"

#include "catch_test_case_info.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;



class TestSpecTest_1008 : public ::testing::Test {

protected:

    TestSpec testSpec;

};



TEST_F(TestSpecTest_1008, HasFilters_NoFilters_1008) {

    EXPECT_FALSE(testSpec.hasFilters());

}



TEST_F(TestSpecTest_1008, Matches_NoFilters_ReturnsTrue_1008) {

    TestCaseInfo testCase("ClassName", {"TestCaseName", ""}, SourceLineInfo("", 1));

    EXPECT_TRUE(testSpec.matches(testCase));

}



TEST_F(TestSpecTest_1008, GetInvalidSpecs_Empty_ReturnsEmptyVector_1008) {

    const auto& invalidSpecs = testSpec.getInvalidSpecs();

    EXPECT_TRUE(invalidSpecs.empty());

}



class MockFilter : public TestSpec::Filter {

public:

    MOCK_CONST_METHOD1(matches, bool(const TestCaseInfo& testCase));

};



TEST_F(TestSpecTest_1008, Matches_WithMockFilter_ReturnsFilteredResult_1008) {

    MockFilter mockFilter;

    std::vector<Detail::unique_ptr<TestSpec::Filter>> filters;

    filters.push_back(Detail::make_unique<MockFilter>(mockFilter));

    testSpec.m_filters = std::move(filters);



    TestCaseInfo testCase("ClassName", {"TestCaseName", ""}, SourceLineInfo("", 1));



    EXPECT_CALL(mockFilter, matches(testCase))

        .WillOnce(Return(true));



    EXPECT_TRUE(testSpec.matches(testCase));

}



TEST_F(TestSpecTest_1008, MatchesByFilter_NoFilters_ReturnsAllTests_1008) {

    std::vector<TestCaseHandle> testCases;

    TestSpec::Matches result = testSpec.matchesByFilter(testCases, IConfig());

    EXPECT_EQ(result.size(), 0);

}



TEST_F(TestSpecTest_1008, MatchesByFilter_WithMockFilters_ReturnsFilteredTests_1008) {

    MockFilter mockFilter1;

    MockFilter mockFilter2;



    std::vector<Detail::unique_ptr<TestSpec::Filter>> filters;

    filters.push_back(Detail::make_unique<MockFilter>(mockFilter1));

    filters.push_back(Detail::make_unique<MockFilter>(mockFilter2));



    testSpec.m_filters = std::move(filters);



    TestCaseHandle testCase1;

    TestCaseInfo info1("ClassName", {"TestCaseName1", ""}, SourceLineInfo("", 1));

    testCase1.setTestCaseInfo(info1);



    TestCaseHandle testCase2;

    TestCaseInfo info2("ClassName", {"TestCaseName2", ""}, SourceLineInfo("", 1));

    testCase2.setTestCaseInfo(info2);



    std::vector<TestCaseHandle> testCases = {testCase1, testCase2};



    EXPECT_CALL(mockFilter1, matches(testCase1.getTestCaseInfo()))

        .WillOnce(Return(true));



    EXPECT_CALL(mockFilter1, matches(testCase2.getTestCaseInfo()))

        .WillOnce(Return(false));



    EXPECT_CALL(mockFilter2, matches(testCase1.getTestCaseInfo()))

        .WillOnce(Return(true));



    TestSpec::Matches result = testSpec.matchesByFilter(testCases, IConfig());



    EXPECT_EQ(result.size(), 1);

    EXPECT_EQ(result[0].getTestCaseInfo().name, "TestCaseName1");

}
