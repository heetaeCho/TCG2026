#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"

// We need access to DFA internals for testing RWLocker.
// Since RWLocker is a nested class within DFA which is internal to re2,
// we test it indirectly through DFA's public search interface,
// which exercises the RWLocker internally.

namespace re2 {

// Test that DFA-based matching works correctly, which exercises RWLocker
// during state cache operations.
class RWLockerTest_449 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Normal operation: DFA search with a simple pattern exercises RWLocker
TEST_F(RWLockerTest_449, BasicDFASearchWorks_449) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

// Multiple searches exercise the RWLocker lock/unlock cycle repeatedly
TEST_F(RWLockerTest_449, RepeatedDFASearches_449) {
  RE2 re("a+b+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("aabb", re));
  EXPECT_TRUE(RE2::FullMatch("ab", re));
  EXPECT_TRUE(RE2::FullMatch("aaabbb", re));
  EXPECT_FALSE(RE2::FullMatch("ba", re));
  EXPECT_FALSE(RE2::FullMatch("", re));
}

// Complex pattern that may trigger cache writes (LockForWriting)
TEST_F(RWLockerTest_449, ComplexPatternTriggersCacheWrites_449) {
  RE2 re("(a|b)*c(d|e)+f?");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abacdef", re));
  EXPECT_TRUE(RE2::FullMatch("cde", re));
  EXPECT_TRUE(RE2::FullMatch("cd", re));
  EXPECT_FALSE(RE2::FullMatch("abf", re));
}

// Concurrent-like usage: many different inputs to stress RWLocker transitions
TEST_F(RWLockerTest_449, ManyDistinctInputsStressCacheLocking_449) {
  RE2 re("[a-z]+[0-9]+");
  ASSERT_TRUE(re.ok());
  for (int i = 0; i < 100; i++) {
    std::string input = "abc" + std::to_string(i);
    EXPECT_TRUE(RE2::FullMatch(input, re));
  }
}

// Boundary: empty pattern
TEST_F(RWLockerTest_449, EmptyPatternDFASearch_449) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_FALSE(RE2::FullMatch("a", re));
}

// Boundary: single character pattern
TEST_F(RWLockerTest_449, SingleCharPatternDFASearch_449) {
  RE2 re("x");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("x", re));
  EXPECT_FALSE(RE2::FullMatch("xx", re));
  EXPECT_FALSE(RE2::FullMatch("", re));
}

// PartialMatch also exercises DFA and RWLocker
TEST_F(RWLockerTest_449, PartialMatchExercisesRWLocker_449) {
  RE2 re("needle");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("haystackneedlehaystack", re));
  EXPECT_FALSE(RE2::PartialMatch("haystack", re));
}

// Large input to potentially trigger multiple state cache expansions
TEST_F(RWLockerTest_449, LargeInputExercisesLockForWriting_449) {
  RE2 re("a*b");
  ASSERT_TRUE(re.ok());
  std::string large_input(10000, 'a');
  large_input += "b";
  EXPECT_TRUE(RE2::FullMatch(large_input, re));
}

// Pattern with many states to exercise cache growth and LockForWriting
TEST_F(RWLockerTest_449, ManyStatesPatternExercisesWriteLock_449) {
  // Alternation creates many DFA states
  RE2 re("(abc|def|ghi|jkl|mno|pqr|stu|vwx|yz0)+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abcdefghijkl", re));
  EXPECT_FALSE(RE2::FullMatch("123", re));
}

}  // namespace re2
