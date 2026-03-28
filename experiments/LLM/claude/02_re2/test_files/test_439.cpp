#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "absl/container/flat_hash_set.h"

#include <memory>
#include <string>
#include <vector>

// Since DFA, State, and StateEqual are internal to re2's implementation
// and not directly exposed through public headers, we test their behavior
// indirectly through the public RE2 interface which exercises DFA matching.
// The DFA StateEqual is used internally by the StateSet (flat_hash_set).

namespace re2 {
namespace {

// Test that DFA-based matching works correctly, which exercises
// State equality comparison internally through the StateSet.
class DFAStateEqualTest_439 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Normal operation: simple pattern matching exercises DFA state management
TEST_F(DFAStateEqualTest_439, BasicMatchExercisesDFAStates_439) {
  RE2 re("abc");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_FALSE(RE2::FullMatch("abd", re));
}

// Multiple matches: DFA state caching relies on StateEqual for deduplication
TEST_F(DFAStateEqualTest_439, RepeatedMatchesUseCachedStates_439) {
  RE2 re("(a+)(b+)");
  ASSERT_TRUE(re.ok());
  for (int i = 0; i < 100; i++) {
    EXPECT_TRUE(RE2::FullMatch("aaabbb", re));
  }
}

// Alternation creates multiple DFA states that must be compared
TEST_F(DFAStateEqualTest_439, AlternationCreatesDifferentStates_439) {
  RE2 re("abc|def|ghi");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_TRUE(RE2::FullMatch("def", re));
  EXPECT_TRUE(RE2::FullMatch("ghi", re));
  EXPECT_FALSE(RE2::FullMatch("xyz", re));
}

// Complex patterns with many states exercise StateEqual heavily
TEST_F(DFAStateEqualTest_439, ComplexPatternManyStates_439) {
  RE2 re("[a-z]+[0-9]+[a-z]+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc123def", re));
  EXPECT_FALSE(RE2::FullMatch("123", re));
  EXPECT_FALSE(RE2::FullMatch("abc", re));
}

// Empty string boundary condition
TEST_F(DFAStateEqualTest_439, EmptyStringMatch_439) {
  RE2 re("a*");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
}

// PartialMatch exercises different DFA paths
TEST_F(DFAStateEqualTest_439, PartialMatchDFAPaths_439) {
  RE2 re("needle");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("haystackneedlehaystack", re));
  EXPECT_FALSE(RE2::PartialMatch("haystack", re));
}

// Repetition with different quantifiers
TEST_F(DFAStateEqualTest_439, QuantifiersDFAStates_439) {
  RE2 re("a{3,5}b{2,4}");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("aaabb", re));
  EXPECT_TRUE(RE2::FullMatch("aaaaabbbb", re));
  EXPECT_FALSE(RE2::FullMatch("ab", re));
}

// Character classes that lead to equivalent DFA states
TEST_F(DFAStateEqualTest_439, CharacterClassEquivalentStates_439) {
  RE2 re("[abc][abc][abc]");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_TRUE(RE2::FullMatch("cba", re));
  EXPECT_FALSE(RE2::FullMatch("aad", re));
}

// Long input string exercises DFA state transitions extensively
TEST_F(DFAStateEqualTest_439, LongInputStateTransitions_439) {
  RE2 re("(ab)*");
  ASSERT_TRUE(re.ok());
  std::string long_input;
  for (int i = 0; i < 1000; i++) {
    long_input += "ab";
  }
  EXPECT_TRUE(RE2::FullMatch(long_input, re));
}

// Nested groups and backreference-free patterns
TEST_F(DFAStateEqualTest_439, NestedGroupsDFA_439) {
  RE2 re("((a|b)(c|d))+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("acbd", re));
  EXPECT_TRUE(RE2::FullMatch("ac", re));
  EXPECT_FALSE(RE2::FullMatch("ab", re));
}

}  // namespace
}  // namespace re2
