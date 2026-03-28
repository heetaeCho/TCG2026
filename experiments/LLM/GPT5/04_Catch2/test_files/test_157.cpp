// File: match_all_of_generic_describe_tests_157.cpp

#include <gtest/gtest.h>
#include <string>
#include <utility>

// Include the header under test
// Adjust the include path to match your project layout.
#include "catch2/matchers/catch_matchers_templated.hpp"

using Catch::Matchers::Detail::MatchAllOfGeneric;

namespace {

// A tiny fake “matcher” type that conforms to the expectations of MatchAllOfGeneric.
// It exposes:
//   - template<typename Arg> bool match(Arg&&) const
//   - std::string describe() const
//
// We keep it as a strict *collaborator* for exercising the public API of
// MatchAllOfGeneric — no assumptions about internal state of the class under test.
struct FakeMatcher {
  // Each instance can be configured with a specific description and match result.
  std::string desc;
  bool result = true;

  // Optional counters to verify external interactions (calls to describe()).
  // Kept outside of the class under test.
  mutable int* describe_call_counter = nullptr;

  FakeMatcher(std::string d, bool r = true, int* counter = nullptr)
      : desc(std::move(d)), result(r), describe_call_counter(counter) {}

  template <typename Arg>
  bool match(Arg&&) const {
    // Return the configured result; this is observable behavior through
    // MatchAllOfGeneric::match, but these tests focus on describe().
    return result;
  }

  std::string describe() const {
    if (describe_call_counter) { ++(*describe_call_counter); }
    return desc;
  }
};

}  // namespace

// ---------------------------
// Test fixture (kept simple)
// ---------------------------
class MatchAllOfGenericTest_157 : public ::testing::Test {};

// Verifies that describe() concatenates two inner matcher descriptions with " and ",
// preserving order. This checks *observable* output only.
TEST_F(MatchAllOfGenericTest_157, DescribeWithTwoMatchers_157) {
  FakeMatcher m1{"is even"};
  FakeMatcher m2{"is positive"};

  MatchAllOfGeneric<FakeMatcher, FakeMatcher> all_of(m1, m2);
  const std::string d = all_of.describe();

  EXPECT_EQ(d, "is even and is positive");
}

// Verifies that describe() concatenates three inner matcher descriptions with " and ",
// preserving order.
TEST_F(MatchAllOfGenericTest_157, DescribeWithThreeMatchers_157) {
  FakeMatcher m1{"starts with A"};
  FakeMatcher m2{"ends with Z"};
  FakeMatcher m3{"has length 5"};

  MatchAllOfGeneric<FakeMatcher, FakeMatcher, FakeMatcher> all_of(m1, m2, m3);
  const std::string d = all_of.describe();

  EXPECT_EQ(d, "starts with A and ends with Z and has length 5");
}

// Verifies that describe() calls each inner matcher’s describe() exactly once.
// This checks external interaction without peeking into internal state.
TEST_F(MatchAllOfGenericTest_157, DescribeCallsEachInnerOnce_157) {
  int c1 = 0, c2 = 0, c3 = 0;

  FakeMatcher m1{"A", true, &c1};
  FakeMatcher m2{"B", true, &c2};
  FakeMatcher m3{"C", true, &c3};

  MatchAllOfGeneric<FakeMatcher, FakeMatcher, FakeMatcher> all_of(m1, m2, m3);
  (void)all_of.describe();

  EXPECT_EQ(c1, 1);
  EXPECT_EQ(c2, 1);
  EXPECT_EQ(c3, 1);
}

// Boundary-ish formatting case: empty descriptions are still concatenated with " and ".
// We do not make assumptions about trimming — we assert the visible output.
TEST_F(MatchAllOfGenericTest_157, DescribeWithEmptyInnerDescriptions_157) {
  FakeMatcher m1{""};
  FakeMatcher m2{""};

  MatchAllOfGeneric<FakeMatcher, FakeMatcher> all_of(m1, m2);
  const std::string d = all_of.describe();

  // Expect the literal join with " and " between two empty strings.
  EXPECT_EQ(d, " and ");
}

// Smoke check that describe() is callable on a const instance and returns a stable string.
// (This also exercises the const-qualification of the API.)
TEST_F(MatchAllOfGenericTest_157, DescribeIsConst_157) {
  const FakeMatcher m1{"left"};
  const FakeMatcher m2{"right"};

  const MatchAllOfGeneric<FakeMatcher, FakeMatcher> all_of(m1, m2);
  const std::string d = all_of.describe();

  EXPECT_EQ(d, "left and right");
}

//
// (Optional) Minimal coverage on match() to ensure it’s callable and returns the
// underlying fake results via the public API. We avoid re-implementing or relying on
// internal logic; we only assert observable behavior for our specific inputs.
//
TEST_F(MatchAllOfGenericTest_157, MatchIsCallableAndObservable_157) {
  FakeMatcher m1{"desc1", true};
  FakeMatcher m2{"desc2", true};

  MatchAllOfGeneric<FakeMatcher, FakeMatcher> all_true(m1, m2);
  EXPECT_TRUE(all_true.match(123));  // Arg type is arbitrary

  FakeMatcher f1{"desc3", false};
  FakeMatcher f2{"desc4", true};

  MatchAllOfGeneric<FakeMatcher, FakeMatcher> has_false(f1, f2);
  // We only assert the return value for this specific configuration of collaborators.
  EXPECT_FALSE(has_false.match("abc"));
}
