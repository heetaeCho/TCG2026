#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>
#include <thread>
#include <vector>

namespace re2 {

// Basic test that LazyRE2 can be initialized and used
TEST(LazyRE2Test_48, BasicInitialization_48) {
  static LazyRE2 re = {"hello"};
  ASSERT_NE(re.get(), nullptr);
  EXPECT_TRUE(RE2::FullMatch("hello", *re));
  EXPECT_FALSE(RE2::FullMatch("world", *re));
}

// Test that get() returns the same pointer on multiple calls
TEST(LazyRE2Test_48, GetReturnsSamePointer_48) {
  static LazyRE2 re = {"abc"};
  RE2* ptr1 = re.get();
  RE2* ptr2 = re.get();
  EXPECT_EQ(ptr1, ptr2);
}

// Test the dereference operator*
TEST(LazyRE2Test_48, DereferenceOperator_48) {
  static LazyRE2 re = {"[0-9]+"};
  RE2& ref = *re;
  EXPECT_TRUE(RE2::FullMatch("12345", ref));
  EXPECT_FALSE(RE2::FullMatch("abc", ref));
}

// Test the arrow operator->
TEST(LazyRE2Test_48, ArrowOperator_48) {
  static LazyRE2 re = {"test_pattern"};
  EXPECT_EQ(re->pattern(), "test_pattern");
}

// Test with a more complex regex pattern
TEST(LazyRE2Test_48, ComplexPattern_48) {
  static LazyRE2 re = {"^([a-z]+)@([a-z]+)\\.com$"};
  ASSERT_NE(re.get(), nullptr);
  EXPECT_TRUE(RE2::FullMatch("user@domain.com", *re));
  EXPECT_FALSE(RE2::FullMatch("user@domain.org", *re));
}

// Test that the pattern is accessible
TEST(LazyRE2Test_48, PatternAccessible_48) {
  static LazyRE2 re = {"foo|bar"};
  EXPECT_EQ(re->pattern(), "foo|bar");
}

// Test with empty pattern
TEST(LazyRE2Test_48, EmptyPattern_48) {
  static LazyRE2 re = {""};
  ASSERT_NE(re.get(), nullptr);
  EXPECT_TRUE(RE2::FullMatch("", *re));
  EXPECT_FALSE(RE2::FullMatch("nonempty", *re));
}

// Test that the regex is valid (ok() returns true for valid patterns)
TEST(LazyRE2Test_48, ValidPattern_48) {
  static LazyRE2 re = {"[a-z]+"};
  EXPECT_TRUE(re->ok());
}

// Test with a pattern that has special characters
TEST(LazyRE2Test_48, SpecialCharPattern_48) {
  static LazyRE2 re = {"\\d+\\.\\d+"};
  ASSERT_NE(re.get(), nullptr);
  EXPECT_TRUE(RE2::FullMatch("3.14", *re));
  EXPECT_FALSE(RE2::FullMatch("abc", *re));
}

// Test thread safety - multiple threads calling get() simultaneously
TEST(LazyRE2Test_48, ThreadSafety_48) {
  static LazyRE2 re = {"thread_safe"};
  
  std::vector<std::thread> threads;
  std::vector<RE2*> results(10, nullptr);
  
  for (int i = 0; i < 10; i++) {
    threads.emplace_back([&results, i]() {
      results[i] = re.get();
    });
  }
  
  for (auto& t : threads) {
    t.join();
  }
  
  // All threads should get the same pointer
  for (int i = 1; i < 10; i++) {
    EXPECT_EQ(results[0], results[i]);
  }
}

// Test partial match using LazyRE2
TEST(LazyRE2Test_48, PartialMatch_48) {
  static LazyRE2 re = {"world"};
  EXPECT_TRUE(RE2::PartialMatch("hello world", *re));
  EXPECT_FALSE(RE2::PartialMatch("hello earth", *re));
}

// Test with capture groups
TEST(LazyRE2Test_48, CaptureGroups_48) {
  static LazyRE2 re = {"(\\w+):(\\d+)"};
  std::string key;
  int value;
  EXPECT_TRUE(RE2::FullMatch("host:8080", *re, &key, &value));
  EXPECT_EQ(key, "host");
  EXPECT_EQ(value, 8080);
}

// Test NumberOfCapturingGroups via arrow operator
TEST(LazyRE2Test_48, NumberOfCapturingGroups_48) {
  static LazyRE2 re = {"(a)(b)(c)"};
  EXPECT_EQ(re->NumberOfCapturingGroups(), 3);
}

// Test with options (LazyRE2 supports pattern and options)
TEST(LazyRE2Test_48, WithOptions_48) {
  static LazyRE2 re = {"hello", RE2::Latin1};
  ASSERT_NE(re.get(), nullptr);
  EXPECT_TRUE(RE2::FullMatch("hello", *re));
}

// Test that operator* and get() return consistent results
TEST(LazyRE2Test_48, ConsistencyBetweenGetAndDeref_48) {
  static LazyRE2 re = {"consistency"};
  RE2* ptr = re.get();
  RE2& ref = *re;
  EXPECT_EQ(ptr, &ref);
}

// Test that operator-> and get() return consistent results
TEST(LazyRE2Test_48, ConsistencyBetweenGetAndArrow_48) {
  static LazyRE2 re = {"arrow_test"};
  RE2* ptr = re.get();
  EXPECT_EQ(ptr->pattern(), re->pattern());
}

}  // namespace re2
