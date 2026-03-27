#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <vector>

#include <string>



using namespace Catch::Matchers;

using ::testing::Return;



// Mock class for MatcherBase if needed

template <typename T, typename Alloc>

class MockMatcherBase : public MatcherBase<std::vector<T, Alloc>> {

public:

    MOCK_METHOD(bool, match, (const std::vector<T, Alloc>& v), (const, override));

    MOCK_METHOD(std::string, describe, (), (const, override));

};



// Test fixture for VectorContainsElementMatcher

class VectorContainsElementMatcherTest_965 : public ::testing::Test {

protected:

    VectorContainsElementMatcher<int> matcher{42};

};



TEST_F(VectorContainsElementMatcherTest_965, Match_ReturnsTrueWhenElementExists_965) {

    std::vector<int> vec = {10, 20, 42, 30};

    EXPECT_TRUE(matcher.match(vec));

}



TEST_F(VectorContainsElementMatcherTest_965, Match_ReturnsFalseWhenElementDoesNotExist_965) {

    std::vector<int> vec = {10, 20, 30};

    EXPECT_FALSE(matcher.match(vec));

}



TEST_F(VectorContainsElementMatcherTest_965, Describe_ReturnsCorrectDescription_965) {

    EXPECT_EQ("Contains: 42", matcher.describe());

}



TEST_F(VectorContainsElementMatcherTest_965, Match_EmptyVector_ReturnsFalse_965) {

    std::vector<int> vec;

    EXPECT_FALSE(matcher.match(vec));

}



TEST_F(VectorContainsElementMatcherTest_965, Match_VectorWithOneMatchingElement_ReturnsTrue_965) {

    std::vector<int> vec = {42};

    EXPECT_TRUE(matcher.match(vec));

}
