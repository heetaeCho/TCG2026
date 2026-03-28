// File: all_match_matcher_tests_177.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_quantifiers.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;
using ::testing::InSequence;

namespace {

struct MockMatcher {
  // The AllMatchMatcher::match is const, so the inner matcher’s match must be const too.
  MOCK_METHOD(bool, match, (int elem), (const));
};

} // namespace

// ---------- Tests ----------

class AllMatchMatcherTest_177 : public ::testing::Test {};

// Normal operation: all elements satisfy the inner matcher → true
TEST_F(AllMatchMatcherTest_177, AllElementsMatch_ReturnsTrue_177) {
  StrictMock<MockMatcher> mock;
  // Build an AllMatchMatcher with our mock collaborator
  Catch::Matchers::AllMatchMatcher<StrictMock<MockMatcher>> under_test(mock);

  std::vector<int> v{1, 2, 3};
  InSequence s;  // Ensure order is the iteration order

  EXPECT_CALL(mock, match(1)).WillOnce(Return(true));
  EXPECT_CALL(mock, match(2)).WillOnce(Return(true));
  EXPECT_CALL(mock, match(3)).WillOnce(Return(true));

  EXPECT_TRUE(under_test.match(v));
}

// Boundary: empty range → vacuously true; no calls to inner matcher
TEST_F(AllMatchMatcherTest_177, EmptyRange_IsTrue_AndNoCalls_177) {
  StrictMock<MockMatcher> mock;
  Catch::Matchers::AllMatchMatcher<StrictMock<MockMatcher>> under_test(mock);

  std::vector<int> empty;
  EXPECT_CALL(mock, match(_)).Times(0);

  EXPECT_TRUE(under_test.match(empty));
}

// Error/exceptional (observable via return): first element fails → short-circuits and returns false
TEST_F(AllMatchMatcherTest_177, ShortCircuitsOnFirstFailure_177) {
  StrictMock<MockMatcher> mock;
  Catch::Matchers::AllMatchMatcher<StrictMock<MockMatcher>> under_test(mock);

  std::vector<int> v{10, 20, 30};

  EXPECT_CALL(mock, match(10)).WillOnce(Return(false));
  // After first failure, no further elements should be checked
  EXPECT_CALL(mock, match(_)).Times(0);

  EXPECT_FALSE(under_test.match(v));
}

// Error/exceptional: later element fails → stops at that element, later ones not checked
TEST_F(AllMatchMatcherTest_177, StopsAfterMiddleFailure_NoFurtherCalls_177) {
  StrictMock<MockMatcher> mock;
  Catch::Matchers::AllMatchMatcher<StrictMock<MockMatcher>> under_test(mock);

  std::vector<int> v{7, 8, 9};

  InSequence s;
  EXPECT_CALL(mock, match(7)).WillOnce(Return(true));
  EXPECT_CALL(mock, match(8)).WillOnce(Return(false));
  // 9 must not be checked
  EXPECT_CALL(mock, match(9)).Times(0);

  EXPECT_FALSE(under_test.match(v));
}

// Range type coverage: works with non-vector ranges (e.g., std::list)
TEST_F(AllMatchMatcherTest_177, SupportsDifferentRangeTypes_ListAllMatch_177) {
  StrictMock<MockMatcher> mock;
  Catch::Matchers::AllMatchMatcher<StrictMock<MockMatcher>> under_test(mock);

  std::list<int> lst{4, 5};

  InSequence s;
  EXPECT_CALL(mock, match(4)).WillOnce(Return(true));
  EXPECT_CALL(mock, match(5)).WillOnce(Return(true));

  EXPECT_TRUE(under_test.match(lst));
}
