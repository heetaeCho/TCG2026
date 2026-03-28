#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"

#include <string>
#include <thread>
#include <vector>

namespace re2 {
namespace {

// Since RWLocker and DFA internals are not directly accessible through the
// public API, we test the DFA behavior through the RE2 public interface,
// which exercises the RWLocker indirectly through DFA search operations.

class DFARWLockerTest_450 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that basic DFA matching works (exercises RWLocker in read mode)
TEST_F(DFARWLockerTest_450, BasicMatchUsesRWLocker_450) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

// Test that repeated matches work correctly (RWLocker acquired/released multiple times)
TEST_F(DFARWLockerTest_450, RepeatedMatchesRWLockerReuse_450) {
  RE2 re("a+b+");
  ASSERT_TRUE(re.ok());
  for (int i = 0; i < 100; i++) {
    EXPECT_TRUE(RE2::FullMatch("aaabbb", re));
    EXPECT_FALSE(RE2::FullMatch("ccc", re));
  }
}

// Test concurrent access which exercises RWLocker's read locking
TEST_F(DFARWLockerTest_450, ConcurrentReadAccess_450) {
  RE2 re("(foo|bar|baz)+");
  ASSERT_TRUE(re.ok());

  std::vector<std::thread> threads;
  for (int i = 0; i < 8; i++) {
    threads.emplace_back([&re]() {
      for (int j = 0; j < 100; j++) {
        EXPECT_TRUE(RE2::PartialMatch("foobarbazbaz", re));
        EXPECT_FALSE(RE2::FullMatch("xyz", re));
      }
    });
  }
  for (auto& t : threads) {
    t.join();
  }
}

// Test that DFA state cache growth triggers write locking via LockForWriting
TEST_F(DFARWLockerTest_450, CacheGrowthTriggersWriteLock_450) {
  // Use a pattern that creates many DFA states to trigger cache operations
  RE2 re("[a-z]{1,10}[0-9]{1,5}");
  ASSERT_TRUE(re.ok());

  // Exercise many different input paths to force DFA state creation
  std::string inputs[] = {
    "a1", "ab12", "abc123", "abcd1234", "abcde12345",
    "z9", "zy98", "zyx987", "zyxw9876", "zyxwv98765"
  };
  for (const auto& input : inputs) {
    EXPECT_TRUE(RE2::FullMatch(input, re));
  }
  EXPECT_FALSE(RE2::FullMatch("123abc", re));
}

// Test with complex patterns that exercise DFA more thoroughly
TEST_F(DFARWLockerTest_450, ComplexPatternDFAExercise_450) {
  RE2 re("(a|b)*abb");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abb", re));
  EXPECT_TRUE(RE2::FullMatch("aabb", re));
  EXPECT_TRUE(RE2::FullMatch("babb", re));
  EXPECT_TRUE(RE2::FullMatch("abababb", re));
  EXPECT_FALSE(RE2::FullMatch("ab", re));
  EXPECT_FALSE(RE2::FullMatch("abc", re));
}

// Test concurrent read and pattern matching exercises RWLocker properly
TEST_F(DFARWLockerTest_450, ConcurrentDifferentPatterns_450) {
  RE2 re1("abc+");
  RE2 re2("x*yz");
  ASSERT_TRUE(re1.ok());
  ASSERT_TRUE(re2.ok());

  std::vector<std::thread> threads;
  for (int i = 0; i < 4; i++) {
    threads.emplace_back([&re1]() {
      for (int j = 0; j < 50; j++) {
        EXPECT_TRUE(RE2::FullMatch("abccc", re1));
      }
    });
    threads.emplace_back([&re2]() {
      for (int j = 0; j < 50; j++) {
        EXPECT_TRUE(RE2::FullMatch("xxyz", re2));
      }
    });
  }
  for (auto& t : threads) {
    t.join();
  }
}

// Test PartialMatch which also goes through DFA path with RWLocker
TEST_F(DFARWLockerTest_450, PartialMatchDFAPath_450) {
  RE2 re("needle");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("haystackneedlehaystack", re));
  EXPECT_FALSE(RE2::PartialMatch("haystack", re));
}

// Test empty pattern edge case
TEST_F(DFARWLockerTest_450, EmptyPatternDFA_450) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::PartialMatch("anything", re));
}

// Test long input to exercise DFA state transitions extensively
TEST_F(DFARWLockerTest_450, LongInputDFAExercise_450) {
  RE2 re("a*b");
  ASSERT_TRUE(re.ok());
  std::string long_input(10000, 'a');
  long_input += 'b';
  EXPECT_TRUE(RE2::FullMatch(long_input, re));

  std::string no_match(10000, 'a');
  EXPECT_FALSE(RE2::FullMatch(no_match, re));
}

// Test that DFA handles character classes (many state transitions)
TEST_F(DFARWLockerTest_450, CharacterClassDFA_450) {
  RE2 re("[[:alpha:]]+[[:digit:]]+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc123", re));
  EXPECT_FALSE(RE2::FullMatch("123abc", re));
  EXPECT_FALSE(RE2::FullMatch("", re));
}

}  // namespace
}  // namespace re2
