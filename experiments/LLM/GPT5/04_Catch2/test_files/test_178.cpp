// File: none_match_matcher_tests_178.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <list>
#include <string>

// Include the header that contains NoneMatchMatcher
// Adjust include path as needed for your project layout.
#include "catch2/matchers/catch_matchers_quantifiers.hpp"

using ::testing::Return;
using ::testing::_;
using ::testing::InSequence;

namespace {

// A mock matcher for int elements, exposing only the interface that
// NoneMatchMatcher relies on: describe() and match(T).
class MockIntMatcher {
public:
    MOCK_METHOD(std::string, describe, (), (const));
    MOCK_METHOD(bool, match, (int), (const));
};

// A mock matcher for std::string elements.
class MockStringMatcher {
public:
    MOCK_METHOD(std::string, describe, (), (const));
    MOCK_METHOD(bool, match, (const std::string&), (const));
};

} // namespace

// For brevity
namespace C = Catch::Matchers;

//
// describe()
//

TEST(NoneMatchMatcherTest_178, DescribePrefixesWithNoneMatch_178) {
    MockIntMatcher inner;
    EXPECT_CALL(inner, describe()).WillOnce(Return("is even"));

    C::NoneMatchMatcher<MockIntMatcher> none(inner);

    // Observable behavior: description text
    EXPECT_EQ(none.describe(), std::string("none match ") + "is even");
}

//
// match() with integer ranges
//

TEST(NoneMatchMatcherTest_178, Match_EmptyRange_ReturnsTrue_178) {
    MockIntMatcher inner;
    // Even if inner "matches anything", an empty range contains no matches.
    ON_CALL(inner, match(_)).WillByDefault(Return(true));

    C::NoneMatchMatcher<MockIntMatcher> none(inner);

    std::vector<int> empty;
    EXPECT_TRUE(none.match(empty));
}

TEST(NoneMatchMatcherTest_178, Match_NoElementsMatch_ReturnsTrue_178) {
    MockIntMatcher inner;
    // Define inner behavior: match only 42
    ON_CALL(inner, match(_)).WillByDefault(Return(false));
    ON_CALL(inner, match(42)).WillByDefault(Return(true));

    C::NoneMatchMatcher<MockIntMatcher> none(inner);

    std::vector<int> data{1, 2, 3, 5, 7}; // no 42 present
    EXPECT_TRUE(none.match(data));
}

TEST(NoneMatchMatcherTest_178, Match_AnyElementMatches_ReturnsFalse_178) {
    MockIntMatcher inner;
    // Inner matches 42, otherwise false
    ON_CALL(inner, match(_)).WillByDefault(Return(false));
    ON_CALL(inner, match(42)).WillByDefault(Return(true));

    C::NoneMatchMatcher<MockIntMatcher> none(inner);

    std::vector<int> data{0, 41, 42, 43};
    EXPECT_FALSE(none.match(data));
}

TEST(NoneMatchMatcherTest_178, Match_SingleElementRange_MatchingElement_ReturnsFalse_178) {
    MockIntMatcher inner;
    ON_CALL(inner, match(10)).WillByDefault(Return(true));

    C::NoneMatchMatcher<MockIntMatcher> none(inner);

    std::vector<int> data{10};
    EXPECT_FALSE(none.match(data));
}

TEST(NoneMatchMatcherTest_178, Match_SingleElementRange_NonMatchingElement_ReturnsTrue_178) {
    MockIntMatcher inner;
    ON_CALL(inner, match(11)).WillByDefault(Return(false));

    C::NoneMatchMatcher<MockIntMatcher> none(inner);

    std::vector<int> data{11};
    EXPECT_TRUE(none.match(data));
}

TEST(NoneMatchMatcherTest_178, Match_MatchingElementAtBeginning_ReturnsFalse_178) {
    MockIntMatcher inner;
    ON_CALL(inner, match(_)).WillByDefault(Return(false));
    ON_CALL(inner, match(99)).WillByDefault(Return(true));

    C::NoneMatchMatcher<MockIntMatcher> none(inner);

    std::vector<int> data{99, 1, 2, 3};
    EXPECT_FALSE(none.match(data));
}

TEST(NoneMatchMatcherTest_178, Match_MatchingElementAtEnd_ReturnsFalse_178) {
    MockIntMatcher inner;
    ON_CALL(inner, match(_)).WillByDefault(Return(false));
    ON_CALL(inner, match(77)).WillByDefault(Return(true));

    C::NoneMatchMatcher<MockIntMatcher> none(inner);

    std::vector<int> data{1, 2, 3, 77};
    EXPECT_FALSE(none.match(data));
}

//
// match() with non-vector ranges (interface should work with generic ranges)
//

TEST(NoneMatchMatcherTest_178, Match_WorksWithListOfStrings_NoMatches_ReturnsTrue_178) {
    MockStringMatcher inner;
    // Inner matcher matches exactly "ok"
    ON_CALL(inner, match(_)).WillByDefault(Return(false));
    ON_CALL(inner, match(std::string("ok"))).WillByDefault(Return(true));

    C::NoneMatchMatcher<MockStringMatcher> none(inner);

    std::list<std::string> items{"a", "b", "c"};
    EXPECT_TRUE(none.match(items));
}

TEST(NoneMatchMatcherTest_178, Match_WorksWithListOfStrings_WithMatch_ReturnsFalse_178) {
    MockStringMatcher inner;
    ON_CALL(inner, match(_)).WillByDefault(Return(false));
    ON_CALL(inner, match(std::string("ok"))).WillByDefault(Return(true));

    C::NoneMatchMatcher<MockStringMatcher> none(inner);

    std::list<std::string> items{"nope", "ok", "later"};
    EXPECT_FALSE(none.match(items));
}

//
// Cross-check that describe() composes strictly from inner.describe() text
//

TEST(NoneMatchMatcherTest_178, Describe_UsesInnerDescribeVerbatim_178) {
    MockStringMatcher inner;
    EXPECT_CALL(inner, describe()).WillOnce(Return("starts with X"));

    C::NoneMatchMatcher<MockStringMatcher> none(inner);

    EXPECT_EQ(none.describe(), "none match starts with X");
}

