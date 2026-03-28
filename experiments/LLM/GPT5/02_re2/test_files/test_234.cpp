// File: set_match_forwarding_test_234.cc
#include <gtest/gtest.h>
#include <re2/re2.h>
#include <re2/set.h>

using ::testing::Test;

class RE2SetMatchTest_234 : public Test {
protected:
  RE2::Options opts_;
  RE2::Anchor anchor_ = RE2::UNANCHORED;
};

// [Normal operation] After adding patterns and compiling, the 2-arg Match
// should produce the same return value and matched indices as the 3-arg Match
// with nullptr error_info.
TEST_F(RE2SetMatchTest_234, TwoArgEqualsThreeArgAfterCompile_234) {
  RE2::Set set(opts_, anchor_);
  std::string err;
  ASSERT_GE(set.Add("foo", &err), 0);
  ASSERT_GE(set.Add("bar", &err), 0);
  ASSERT_TRUE(set.Compile());

  const absl::string_view text = "xxfoobarzz";

  std::vector<int> v_two, v_three;
  const bool r_two   = set.Match(text, &v_two);
  const bool r_three = set.Match(text, &v_three, /*error_info=*/nullptr);

  EXPECT_EQ(r_two, r_three);
  EXPECT_EQ(v_two, v_three);

  // Optional sanity: matched indices must be within range [0, added_patterns)
  for (int idx : v_two) {
    EXPECT_GE(idx, 0);
    EXPECT_LT(idx, 2);
  }
}

// [Boundary/behavioral parity] Calling Match before Compile should still have
// identical observable results between the two overloads (whatever they are).
TEST_F(RE2SetMatchTest_234, TwoArgEqualsThreeArgBeforeCompile_234) {
  RE2::Set set(opts_, anchor_);
  std::string err;
  ASSERT_GE(set.Add("foo", &err), 0);
  // Note: Intentionally not calling Compile().

  std::vector<int> v_two{42}, v_three{7};
  const bool r_two   = set.Match("foo", &v_two);
  const bool r_three = set.Match("foo", &v_three, /*error_info=*/nullptr);

  EXPECT_EQ(r_two, r_three);
  EXPECT_EQ(v_two, v_three);
}

// [Empty set] With no patterns added, both overloads should behave identically.
TEST_F(RE2SetMatchTest_234, TwoArgEqualsThreeArgWithNoPatterns_234) {
  RE2::Set set(opts_, anchor_);

  std::vector<int> v_two, v_three;
  const bool r_two   = set.Match("anything", &v_two);
  const bool r_three = set.Match("anything", &v_three, /*error_info=*/nullptr);

  EXPECT_EQ(r_two, r_three);
  EXPECT_EQ(v_two, v_three);
}

// [Vector contents handling] Ensure both overloads leave identical outputs even
// when the destination vectors start with different pre-filled contents.
TEST_F(RE2SetMatchTest_234, TwoArgAndThreeArgProduceIdenticalOutputVectors_234) {
  RE2::Set set(opts_, anchor_);
  std::string err;
  ASSERT_GE(set.Add("bar", &err), 0);
  ASSERT_TRUE(set.Compile());

  std::vector<int> v_two{1,2,3};
  std::vector<int> v_three{4,5,6};
  const bool r_two   = set.Match("bar", &v_two);
  const bool r_three = set.Match("bar", &v_three, /*error_info=*/nullptr);

  EXPECT_EQ(r_two, r_three);
  EXPECT_EQ(v_two, v_three);
}
