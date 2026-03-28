#include <gtest/gtest.h>

#include "catch_test_spec.hpp"

#include "catch_test_case_info.hpp"



using namespace Catch;



class TestSpecFilterTest_1005 : public ::testing::Test {

protected:

    TestSpec::Filter filter;

    TestCaseInfo testCaseInfo{"ClassName", {"TestCaseName", ""}, SourceLineInfo{"filename.cpp", 42}};



    void addRequiredPattern(const std::string& pattern) {

        filter.m_required.push_back(Detail::unique_ptr<Pattern>(new Pattern(pattern)));

    }



    void addForbiddenPattern(const std::string& pattern) {

        filter.m_forbidden.push_back(Detail::unique_ptr<Pattern>(new Pattern(pattern)));

    }

};



TEST_F(TestSpecFilterTest_1005, NoPatternsMatchesTrue_1005) {

    ASSERT_TRUE(filter.matches(testCaseInfo));

}



TEST_F(TestSpecFilterTest_1005, RequiredPatternMatchesTrue_1005) {

    addRequiredPattern("TestCaseName");

    ASSERT_TRUE(filter.matches(testCaseInfo));

}



TEST_F(TestSpecFilterTest_1005, RequiredPatternDoesNotMatchFalse_1005) {

    addRequiredPattern("NonMatchingPattern");

    ASSERT_FALSE(filter.matches(testCaseInfo));

}



TEST_F(TestSpecFilterTest_1005, ForbiddenPatternMatchesFalse_1005) {

    addForbiddenPattern("TestCaseName");

    ASSERT_FALSE(filter.matches(testCaseInfo));

}



TEST_F(TestSpecFilterTest_1005, ForbiddenPatternDoesNotMatchTrue_1005) {

    addForbiddenPattern("NonMatchingPattern");

    ASSERT_TRUE(filter.matches(testCaseInfo));

}



TEST_F(TestSpecFilterTest_1005, RequiredAndForbiddenPatternsBothMatchFalse_1005) {

    addRequiredPattern("TestCaseName");

    addForbiddenPattern("TestCaseName");

    ASSERT_FALSE(filter.matches(testCaseInfo));

}



TEST_F(TestSpecFilterTest_1005, RequiredAndForbiddenPatternsPartialMatchTrue_1005) {

    addRequiredPattern("TestCaseName");

    addForbiddenPattern("NonMatchingPattern");

    ASSERT_TRUE(filter.matches(testCaseInfo));

}



TEST_F(TestSpecFilterTest_1005, RequiredPatternMultipleMatchesTrue_1005) {

    addRequiredPattern("ClassName");

    addRequiredPattern("TestCaseName");

    ASSERT_TRUE(filter.matches(testCaseInfo));

}



TEST_F(TestSpecFilterTest_1005, ForbiddenPatternMultipleMatchesFalse_1005) {

    addForbiddenPattern("ClassName");

    addForbiddenPattern("TestCaseName");

    ASSERT_FALSE(filter.matches(testCaseInfo));

}
