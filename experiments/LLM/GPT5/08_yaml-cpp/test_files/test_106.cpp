// File: ./TestProjects/yaml-cpp/test/stringsource_test_106.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <string>

#include "stringsource.h"

namespace {

using YAML::StringCharSource;

class StringCharSourceTest_106 : public ::testing::Test {
protected:
  static StringCharSource Make(const char* s, std::size_t n) { return StringCharSource(s, n); }
  static StringCharSource Make(const std::string& s) { return StringCharSource(s.c_str(), s.size()); }
};

TEST_F(StringCharSourceTest_106, PrefixIncrementReturnsSameObject_106) {
  std::string s = "abc";
  auto src = Make(s);

  StringCharSource& ret = ++src;
  EXPECT_EQ(&ret, &src);
}

TEST_F(StringCharSourceTest_106, PrefixIncrementMatchesPlusOneView_106) {
  std::string s = "abcdef";
  auto src = Make(s);

  // Compare observable behavior via operator[] between ++src and src + 1.
  auto shifted = src + 1;
  ++src;

  // Validate a few indices that should be comparable within bounds.
  EXPECT_EQ(src[0], shifted[0]);
  EXPECT_EQ(src[1], shifted[1]);
  EXPECT_EQ(src[2], shifted[2]);
}

TEST_F(StringCharSourceTest_106, PrefixIncrementMatchesPlusEqualsOne_106) {
  std::string s = "abcdef";
  auto a = Make(s);
  auto b = Make(s);

  ++a;
  b += static_cast<std::size_t>(1);

  EXPECT_EQ(a[0], b[0]);
  EXPECT_EQ(a[1], b[1]);
  EXPECT_EQ(a[2], b[2]);
}

TEST_F(StringCharSourceTest_106, MultiplePrefixIncrementsEquivalentToPlusN_106) {
  std::string s = "0123456789";
  auto src = Make(s);

  auto plus3 = src + 3;
  ++src;
  ++src;
  ++src;

  EXPECT_EQ(src[0], plus3[0]);
  EXPECT_EQ(src[1], plus3[1]);
  EXPECT_EQ(src[2], plus3[2]);
}

TEST_F(StringCharSourceTest_106, BoolTransitionsAfterAdvancingToEnd_106) {
  std::string s = "xyz";
  auto src = Make(s);

  // At start, it should be usable as a source (common expectation for a non-empty source).
  EXPECT_TRUE(static_cast<bool>(src));
  EXPECT_FALSE(!src);

  // Advance exactly size times; expect it to become "exhausted" in an observable way.
  for (std::size_t i = 0; i < s.size(); ++i) {
    ++src;
  }

  EXPECT_FALSE(static_cast<bool>(src));
  EXPECT_TRUE(!src);
}

TEST_F(StringCharSourceTest_106, IncrementOnEmptySourceRemainsFalseAndDoesNotThrow_106) {
  std::string empty;
  auto src = Make(empty);

  EXPECT_FALSE(static_cast<bool>(src));
  EXPECT_TRUE(!src);

  // Should be safe to increment even when already exhausted.
  EXPECT_NO_THROW(++src);
  EXPECT_NO_THROW(++src);

  EXPECT_FALSE(static_cast<bool>(src));
  EXPECT_TRUE(!src);
}

TEST_F(StringCharSourceTest_106, IncrementPastEndStaysExhaustedAndDoesNotThrow_106) {
  std::string s = "hi";
  auto src = Make(s);

  // Move to end.
  ++src;
  ++src;

  EXPECT_FALSE(static_cast<bool>(src));
  EXPECT_TRUE(!src);

  // Extra increments should not throw and should keep the exhausted state.
  EXPECT_NO_THROW(++src);
  EXPECT_NO_THROW(++src);

  EXPECT_FALSE(static_cast<bool>(src));
  EXPECT_TRUE(!src);
}

}  // namespace
