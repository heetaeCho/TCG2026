#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>

namespace re2 {
namespace {

// Test that LazyRE2 can be initialized and dereferenced
TEST(LazyRE2Test_46, DereferenceOperator_46) {
  static LazyRE2 re = {"hello"};
  // Dereference operator should return a valid RE2 reference
  RE2& ref = *re;
  EXPECT_EQ(ref.pattern(), "hello");
}

TEST(LazyRE2Test_46, ArrowOperator_46) {
  static LazyRE2 re = {"world"};
  // Arrow operator should allow calling RE2 methods
  EXPECT_EQ(re->pattern(), "world");
}

TEST(LazyRE2Test_46, GetReturnsValidPointer_46) {
  static LazyRE2 re = {"test"};
  RE2* ptr = re.get();
  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(ptr->pattern(), "test");
}

TEST(LazyRE2Test_46, ValidPattern_46) {
  static LazyRE2 re = {"[a-z]+"};
  EXPECT_TRUE(re->ok());
  EXPECT_EQ(re->pattern(), "[a-z]+");
}

TEST(LazyRE2Test_46, InvalidPattern_46) {
  static LazyRE2 re = {"[invalid"};
  // An invalid pattern should result in ok() returning false
  EXPECT_FALSE(re->ok());
}

TEST(LazyRE2Test_46, EmptyPattern_46) {
  static LazyRE2 re = {""};
  EXPECT_TRUE(re->ok());
  EXPECT_EQ(re->pattern(), "");
}

TEST(LazyRE2Test_46, MultipleDereferences_46) {
  static LazyRE2 re = {"abc"};
  // Multiple dereferences should return the same object
  RE2* ptr1 = re.get();
  RE2* ptr2 = re.get();
  EXPECT_EQ(ptr1, ptr2);
}

TEST(LazyRE2Test_46, FullMatchWithLazyRE2_46) {
  static LazyRE2 re = {"\\d+"};
  EXPECT_TRUE(RE2::FullMatch("12345", *re));
  EXPECT_FALSE(RE2::FullMatch("abc", *re));
}

TEST(LazyRE2Test_46, PartialMatchWithLazyRE2_46) {
  static LazyRE2 re = {"\\d+"};
  EXPECT_TRUE(RE2::PartialMatch("abc123def", *re));
  EXPECT_FALSE(RE2::PartialMatch("abcdef", *re));
}

TEST(LazyRE2Test_46, ComplexPattern_46) {
  static LazyRE2 re = {"(\\w+)@(\\w+\\.\\w+)"};
  EXPECT_TRUE(re->ok());
  std::string user, domain;
  EXPECT_TRUE(RE2::FullMatch("user@example.com", *re, &user, &domain));
  EXPECT_EQ(user, "user");
  EXPECT_EQ(domain, "example.com");
}

TEST(LazyRE2Test_46, NumberOfCapturingGroups_46) {
  static LazyRE2 re = {"(a)(b)(c)"};
  EXPECT_EQ(re->NumberOfCapturingGroups(), 3);
}

TEST(LazyRE2Test_46, DereferenceAndGetConsistency_46) {
  static LazyRE2 re = {"foo"};
  RE2& ref = *re;
  RE2* ptr = re.get();
  EXPECT_EQ(&ref, ptr);
}

TEST(LazyRE2Test_46, ArrowAndGetConsistency_46) {
  static LazyRE2 re = {"bar"};
  // Arrow operator and get() should point to the same object
  EXPECT_EQ(&(re->pattern()), &(re.get()->pattern()));
}

TEST(LazyRE2Test_46, PatternWithSpecialChars_46) {
  static LazyRE2 re = {"a\\.b\\*c"};
  EXPECT_TRUE(re->ok());
  EXPECT_TRUE(RE2::FullMatch("a.b*c", *re));
  EXPECT_FALSE(RE2::FullMatch("aXbXc", *re));
}

TEST(LazyRE2Test_46, ThreadSafeInitialization_46) {
  // LazyRE2 should be safe to use from the same thread multiple times
  static LazyRE2 re = {"thread_safe"};
  for (int i = 0; i < 100; ++i) {
    EXPECT_TRUE(re->ok());
    EXPECT_EQ(re->pattern(), "thread_safe");
  }
}

}  // namespace
}  // namespace re2
