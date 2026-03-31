#include "re2/re2.h"
#include "re2/prog.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <thread>
#include <string>
#include <vector>

namespace re2 {
namespace {

// Since RWLocker is an internal implementation detail of DFA,
// and DFA is accessed through RE2's public interface,
// we test the DFA's thread-safety behavior (which relies on RWLocker)
// through RE2's public matching interface.

class DFARWLockerTest_604 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that basic RE2 matching works (DFA with RWLocker is used internally)
TEST_F(DFARWLockerTest_604, BasicMatchUsesRWLocker_604) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

// Test concurrent reads - RWLocker should allow multiple readers
TEST_F(DFARWLockerTest_604, ConcurrentReadsAreThreadSafe_604) {
  RE2 re("(\\d+)-(\\w+)");
  ASSERT_TRUE(re.ok());

  const int kNumThreads = 8;
  const int kNumIterations = 1000;
  std::vector<std::thread> threads;
  std::atomic<int> errors{0};

  for (int i = 0; i < kNumThreads; i++) {
    threads.emplace_back([&re, &errors, kNumIterations]() {
      for (int j = 0; j < kNumIterations; j++) {
        std::string num, word;
        bool matched = RE2::FullMatch("123-abc", re, &num, &word);
        if (!matched || num != "123" || word != "abc") {
          errors++;
        }
      }
    });
  }

  for (auto& t : threads) {
    t.join();
  }

  EXPECT_EQ(errors.load(), 0);
}

// Test concurrent reads and pattern that triggers DFA state transitions
TEST_F(DFARWLockerTest_604, ConcurrentReadsWithComplexPattern_604) {
  RE2 re("a{1,50}b");
  ASSERT_TRUE(re.ok());

  const int kNumThreads = 4;
  const int kNumIterations = 500;
  std::vector<std::thread> threads;
  std::atomic<int> errors{0};

  for (int i = 0; i < kNumThreads; i++) {
    threads.emplace_back([&re, &errors, kNumIterations]() {
      for (int j = 0; j < kNumIterations; j++) {
        bool matched = RE2::FullMatch("aaaaab", re);
        if (!matched) {
          errors++;
        }
        bool not_matched = RE2::FullMatch("b", re);
        if (not_matched) {
          errors++;
        }
      }
    });
  }

  for (auto& t : threads) {
    t.join();
  }

  EXPECT_EQ(errors.load(), 0);
}

// Test that DFA correctly handles new states being built under concurrent access
// This exercises the LockForWriting path of RWLocker
TEST_F(DFARWLockerTest_604, ConcurrentAccessBuildsDFAStates_604) {
  RE2 re("[a-z]+@[a-z]+\\.[a-z]{2,4}");
  ASSERT_TRUE(re.ok());

  const int kNumThreads = 8;
  std::vector<std::thread> threads;
  std::atomic<int> match_count{0};
  std::atomic<int> no_match_count{0};

  std::vector<std::string> inputs = {
    "user@example.com",
    "test@host.org",
    "invalid",
    "no@dots",
    "a@b.cc",
  };

  for (int i = 0; i < kNumThreads; i++) {
    threads.emplace_back([&]() {
      for (const auto& input : inputs) {
        if (RE2::FullMatch(input, re)) {
          match_count++;
        } else {
          no_match_count++;
        }
      }
    });
  }

  for (auto& t : threads) {
    t.join();
  }

  // "user@example.com", "test@host.org", "a@b.cc" should match
  EXPECT_EQ(match_count.load(), 3 * kNumThreads);
  // "invalid", "no@dots" should not match
  EXPECT_EQ(no_match_count.load(), 2 * kNumThreads);
}

// Test single-threaded use - ensure RWLocker doesn't cause issues
TEST_F(DFARWLockerTest_604, SingleThreadedRepeatedUse_604) {
  RE2 re("(foo|bar|baz)+");
  ASSERT_TRUE(re.ok());

  for (int i = 0; i < 1000; i++) {
    EXPECT_TRUE(RE2::PartialMatch("xfoobary", re));
    EXPECT_FALSE(RE2::FullMatch("xyz", re));
  }
}

// Test with PartialMatch which also goes through DFA
TEST_F(DFARWLockerTest_604, ConcurrentPartialMatch_604) {
  RE2 re("\\b\\w+\\b");
  ASSERT_TRUE(re.ok());

  const int kNumThreads = 4;
  const int kNumIterations = 500;
  std::vector<std::thread> threads;
  std::atomic<int> errors{0};

  for (int i = 0; i < kNumThreads; i++) {
    threads.emplace_back([&re, &errors, kNumIterations]() {
      for (int j = 0; j < kNumIterations; j++) {
        std::string word;
        bool matched = RE2::PartialMatch("hello world", re, &word);
        if (!matched) {
          errors++;
        }
      }
    });
  }

  for (auto& t : threads) {
    t.join();
  }

  EXPECT_EQ(errors.load(), 0);
}

// Test empty pattern - boundary case
TEST_F(DFARWLockerTest_604, EmptyPatternConcurrent_604) {
  RE2 re("");
  ASSERT_TRUE(re.ok());

  const int kNumThreads = 4;
  std::vector<std::thread> threads;
  std::atomic<int> errors{0};

  for (int i = 0; i < kNumThreads; i++) {
    threads.emplace_back([&re, &errors]() {
      for (int j = 0; j < 100; j++) {
        if (!RE2::PartialMatch("anything", re)) {
          errors++;
        }
      }
    });
  }

  for (auto& t : threads) {
    t.join();
  }

  EXPECT_EQ(errors.load(), 0);
}

}  // namespace
}  // namespace re2
