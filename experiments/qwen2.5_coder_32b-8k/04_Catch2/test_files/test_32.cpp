#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_test_spec.hpp"

#include <sstream>



using namespace Catch;



// Mock for TestCaseInfo to use in tests

class MockTestCaseInfo : public TestCaseInfo {

public:

    MOCK_CONST_METHOD0(getName, std::string());

};



TEST(TestPattern_32, ConstructorAndGetName_32) {

    Pattern pattern("test_name");

    EXPECT_EQ(pattern.name(), "test_name");

}



TEST(TestPattern_32, Matches_ReturnsTrueForMatchingTestCase_32) {

    MockTestCaseInfo testCase;

    EXPECT_CALL(testCase, getName()).WillRepeatedly(::testing::Return("matching_test_case"));



    Pattern pattern("matching_test_case");

    EXPECT_TRUE(pattern.matches(testCase));

}



TEST(TestPattern_32, Matches_ReturnsFalseForNonMatchingTestCase_32) {

    MockTestCaseInfo testCase;

    EXPECT_CALL(testCase, getName()).WillRepeatedly(::testing::Return("non_matching_test_case"));



    Pattern pattern("expected_test_case");

    EXPECT_FALSE(pattern.matches(testCase));

}



TEST(TestPattern_32, SerializeTo_OutputsName_32) {

    std::ostringstream oss;

    Pattern pattern("test_name");

    pattern.serializeTo(oss);

    EXPECT_EQ(oss.str(), "test_name");

}
