// File: match_all_of_generic_test_156.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the header under test (path as provided)
#include "Catch2/src/catch2/matchers/catch_matchers_templated.hpp"

using ::testing::Return;
using ::testing::_;
using ::testing::AnyNumber;
using ::testing::AtMost;
using ::testing::HasSubstr;

namespace {

// A strict interface for a "matcher-like" collaborator the class under test
// can interact with. We only rely on public, observable interactions:
//  - match(arg): returns bool
//  - describe(): returns std::string
struct MockMatcherInt {
  MOCK_METHOD(bool, match, (int), (const));
  MOCK_METHOD(std::string, describe, (), (const));
};

// Helper alias to shorten the fully-qualified type name.
// We only reference it via the public, templated constructor + methods.
template <typename... M>
using MatchAllOfT =
    Catch::Matchers::Detail::MatchAllOfGeneric<M...>;

} // namespace

// ---------- Normal operation ----------

TEST(MatchAllOfGenericTest_156, AllMatchersPass_ReturnsTrue_156) {
  MockMatcherInt m1, m2;

  // Both collaborators report success; verify result reflects that.
  EXPECT_CALL(m1, match(42)).WillOnce(Return(true));
  EXPECT_CALL(m2, match(42)).WillOnce(Return(true));

  MatchAllOfT<MockMatcherInt, MockMatcherInt> sut(m1, m2);

  EXPECT_TRUE(sut.match(42));
}

// ---------- Mixed outcomes ----------

TEST(MatchAllOfGenericTest_156, OneMatcherFails_ReturnsFalse_156) {
  MockMatcherInt m1, m2;

  // Do not assert short-circuiting behavior (black-box): allow the second
  // collaborator to be called at most once, but not required.
  EXPECT_CALL(m1, match(7)).WillOnce(Return(true));
  EXPECT_CALL(m2, match(7)).Times(AtMost(1)).WillRepeatedly(Return(false));

  MatchAllOfT<MockMatcherInt, MockMatcherInt> sut(m1, m2);

  EXPECT_FALSE(sut.match(7));
}

TEST(MatchAllOfGenericTest_156, FirstMatcherFails_ReturnsFalse_156) {
  MockMatcherInt m1, m2;

  EXPECT_CALL(m1, match(-3)).WillOnce(Return(false));
  // Don’t assume short-circuiting; allow zero or one invocation.
  EXPECT_CALL(m2, match(_)).Times(AtMost(1)).WillRepeatedly(Return(true));

  MatchAllOfT<MockMatcherInt, MockMatcherInt> sut(m1, m2);

  EXPECT_FALSE(sut.match(-3));
}

// ---------- Boundary-ish (single collaborator) ----------

TEST(MatchAllOfGenericTest_156, SingleMatcherTrue_ReturnsTrue_156) {
  MockMatcherInt m;

  EXPECT_CALL(m, match(100)).WillOnce(Return(true));

  MatchAllOfT<MockMatcherInt> sut(m);

  EXPECT_TRUE(sut.match(100));
}

TEST(MatchAllOfGenericTest_156, SingleMatcherFalse_ReturnsFalse_156) {
  MockMatcherInt m;

  EXPECT_CALL(m, match(0)).WillOnce(Return(false));

  MatchAllOfT<MockMatcherInt> sut(m);

  EXPECT_FALSE(sut.match(0));
}

// ---------- Description behavior (observable only) ----------

TEST(MatchAllOfGenericTest_156, Describe_IsNonEmptyAndReflectsCollaborators_156) {
  MockMatcherInt m1, m2;

  // We won’t assert the exact formatting, only that collaborator descriptions
  // can be reflected in the composed description (observable via interface).
  ON_CALL(m1, describe()).WillByDefault(Return("is positive"));
  ON_CALL(m2, describe()).WillByDefault(Return("is even"));

  MatchAllOfT<MockMatcherInt, MockMatcherInt> sut(m1, m2);

  const std::string d = sut.describe();
  // Observable constraints that do not infer internal formatting:
  EXPECT_FALSE(d.empty());
  EXPECT_THAT(d, HasSubstr("is positive"));
  EXPECT_THAT(d, HasSubstr("is even"));
}

// ---------- Argument forwarding / type handling (observable) ----------

TEST(MatchAllOfGenericTest_156, Match_ForwardsExactArgumentValue_156) {
  MockMatcherInt m1, m2;

  // Validate that the value given to match(arg) is the one observed by
  // collaborators; we don’t assert copies/moves—only visible value behavior.
  EXPECT_CALL(m1, match(123)).WillOnce(Return(true));
  EXPECT_CALL(m2, match(123)).WillOnce(Return(true));

  MatchAllOfT<MockMatcherInt, MockMatcherInt> sut(m1, m2);

  EXPECT_TRUE(sut.match(123));
}

