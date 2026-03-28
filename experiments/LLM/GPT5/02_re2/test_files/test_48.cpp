// File: lazyre2_get_tests_48.cc
#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include <atomic>
#include "re2/re2.h"

using re2::RE2;
using re2::LazyRE2;

// Small helper to build a LazyRE2 via its public aggregate-friendly members.
static LazyRE2 MakeLazy(const char* pattern) {
  RE2::Options opts;
  // Keep logs quiet in tests; this does not affect matching semantics.
  opts.set_log_errors(false);
  return LazyRE2{pattern, RE2::CannedOptions(opts)};
}

// -------------------------------
// Normal operation
// -------------------------------

TEST(LazyRE2GetTest_48, ReturnsNonNullAndUsable_48) {
  auto lazy = MakeLazy("a+");
  RE2* ptr = lazy.get();

  ASSERT_NE(ptr, nullptr) << "get() should return a non-null compiled RE2 instance";
  // Use the returned RE2 in a visible way (observable via public API).
  EXPECT_TRUE(RE2::FullMatch("aaa", *ptr));
  EXPECT_FALSE(RE2::FullMatch("bbb", *ptr));
}

TEST(LazyRE2GetTest_48, SamePointerOnRepeatedCalls_48) {
  auto lazy = MakeLazy("abc|def");
  RE2* p1 = lazy.get();
  RE2* p2 = lazy.get();
  RE2* p3 = lazy.get();

  ASSERT_NE(p1, nullptr);
  EXPECT_EQ(p1, p2);
  EXPECT_EQ(p2, p3);
}

// -------------------------------
// Boundary conditions
// -------------------------------

TEST(LazyRE2GetTest_48, EmptyPattern_48) {
  auto lazy = MakeLazy("");
  RE2* ptr = lazy.get();
  ASSERT_NE(ptr, nullptr);

  // Empty pattern should match the empty string and also at position boundaries.
  EXPECT_TRUE(RE2::FullMatch("", *ptr));
  EXPECT_TRUE(RE2::PartialMatch("x", *ptr));  // observable: empty matches at boundary
}

// -------------------------------
// Exceptional / error cases (observable)
// -------------------------------

TEST(LazyRE2GetTest_48, InvalidPatternStillReturnsObjectButNotOk_48) {
  auto lazy = MakeLazy("(");  // Unbalanced paren is invalid.
  RE2* ptr = lazy.get();

  ASSERT_NE(ptr, nullptr) << "Even for invalid pattern, get() should return a RE2 object";
  // Observable via RE2's public API: compilation status and matching behavior.
  EXPECT_FALSE(ptr->ok());
  EXPECT_FALSE(RE2::FullMatch("anything", *ptr));
}

// -------------------------------
// Concurrency / call_once behavior
// -------------------------------

TEST(LazyRE2GetTest_48, ConcurrentCallsReturnSamePointer_48) {
  auto lazy = MakeLazy("\\d{3}-\\d{4}");

  constexpr int kThreads = 16;
  std::vector<std::thread> threads;
  std::vector<RE2*> results(kThreads, nullptr);

  for (int i = 0; i < kThreads; ++i) {
    threads.emplace_back([&lazy, &results, i]() {
      results[i] = lazy.get();
    });
  }
  for (auto& t : threads) t.join();

  // All results should be the same non-null pointer (initialized exactly once).
  ASSERT_NE(results[0], nullptr);
  for (int i = 1; i < kThreads; ++i) {
    EXPECT_EQ(results[0], results[i]) << "All get() calls should return the same RE2*";
  }

  // And it should be usable.
  EXPECT_TRUE(RE2::FullMatch("010-1234", *results[0]));
  EXPECT_FALSE(RE2::FullMatch("not-a-phone", *results[0]));
}

TEST(LazyRE2GetTest_48, InterleavedGetCallsRemainIdempotent_48) {
  auto lazy = MakeLazy("hello(world)?");

  RE2* main_ptr = lazy.get();
  ASSERT_NE(main_ptr, nullptr);

  // Interleave more calls across threads after first initialization.
  constexpr int kThreads = 8;
  std::vector<std::thread> threads;
  std::vector<RE2*> results(kThreads, nullptr);

  for (int i = 0; i < kThreads; ++i) {
    threads.emplace_back([&lazy, &results, i]() {
      results[i] = lazy.get();
    });
  }
  for (auto& t : threads) t.join();

  for (int i = 0; i < kThreads; ++i) {
    EXPECT_EQ(main_ptr, results[i]);
  }

  // Sanity: the compiled regex still works.
  EXPECT_TRUE(RE2::FullMatch("hello", *main_ptr));
  EXPECT_TRUE(RE2::FullMatch("helloworld", *main_ptr));
  EXPECT_FALSE(RE2::FullMatch("hi", *main_ptr));
}
