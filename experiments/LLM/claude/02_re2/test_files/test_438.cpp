#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "absl/hash/hash.h"
#include "absl/container/flat_hash_set.h"

#include <atomic>
#include <cstring>
#include <memory>
#include <vector>

// Since DFA and its internal structures are defined in dfa.cc (not exposed in headers),
// we test DFA behavior indirectly through RE2's public interface which exercises the DFA,
// including state hashing and state set operations.

namespace re2 {

class DFAStateHashTest_438 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that DFA-based matching works correctly for simple patterns,
// which exercises state creation, hashing, and lookup.
TEST_F(DFAStateHashTest_438, SimpleMatch_438) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

// Test that DFA handles alternation patterns, creating multiple states
// that need distinct hashes.
TEST_F(DFAStateHashTest_438, AlternationPattern_438) {
  RE2 re("(abc|def|ghi)");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_TRUE(RE2::FullMatch("def", re));
  EXPECT_TRUE(RE2::FullMatch("ghi", re));
  EXPECT_FALSE(RE2::FullMatch("xyz", re));
}

// Test DFA with character classes which generate various states with different
// instruction sets that must hash differently.
TEST_F(DFAStateHashTest_438, CharacterClassPattern_438) {
  RE2 re("[a-z]+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abcdef", re));
  EXPECT_FALSE(RE2::FullMatch("ABC", re));
  EXPECT_FALSE(RE2::FullMatch("123", re));
}

// Test DFA with repetition which exercises state caching and hashing
// for states that may be revisited.
TEST_F(DFAStateHashTest_438, RepetitionPattern_438) {
  RE2 re("a*b*c*");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("aaabbbccc", re));
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_TRUE(RE2::FullMatch("bbb", re));
  EXPECT_TRUE(RE2::FullMatch("ccc", re));
}

// Test DFA partial match which uses different match semantics
// and exercises state flag differences in hashing.
TEST_F(DFAStateHashTest_438, PartialMatch_438) {
  RE2 re("world");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("hello world", re));
  EXPECT_FALSE(RE2::PartialMatch("hello earth", re));
}

// Test with a complex pattern that creates many DFA states,
// stressing the state hash set with potential collisions.
TEST_F(DFAStateHashTest_438, ComplexPattern_438) {
  RE2 re("(a[bc]d|e[fg]h|i[jk]l)+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abd", re));
  EXPECT_TRUE(RE2::FullMatch("efh", re));
  EXPECT_TRUE(RE2::FullMatch("ijl", re));
  EXPECT_TRUE(RE2::FullMatch("abdefhijl", re));
  EXPECT_FALSE(RE2::FullMatch("xyz", re));
}

// Test empty pattern - boundary condition for state hashing.
TEST_F(DFAStateHashTest_438, EmptyPattern_438) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_FALSE(RE2::FullMatch("a", re));
}

// Test single character pattern - minimal DFA state set.
TEST_F(DFAStateHashTest_438, SingleCharPattern_438) {
  RE2 re("x");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("x", re));
  EXPECT_FALSE(RE2::FullMatch("y", re));
  EXPECT_FALSE(RE2::FullMatch("xx", re));
}

// Test with long input to exercise DFA state transitions and caching extensively.
TEST_F(DFAStateHashTest_438, LongInput_438) {
  RE2 re("[ab]*");
  ASSERT_TRUE(re.ok());
  std::string long_input(10000, 'a');
  EXPECT_TRUE(RE2::FullMatch(long_input, re));
  long_input[5000] = 'c';
  EXPECT_FALSE(RE2::FullMatch(long_input, re));
}

// Test deterministic behavior - same pattern matched multiple times
// should produce consistent results, verifying hash consistency.
TEST_F(DFAStateHashTest_438, DeterministicBehavior_438) {
  RE2 re("(foo|bar|baz)+");
  ASSERT_TRUE(re.ok());
  for (int i = 0; i < 100; i++) {
    EXPECT_TRUE(RE2::FullMatch("foobarbaz", re));
    EXPECT_FALSE(RE2::FullMatch("qux", re));
  }
}

}  // namespace re2
