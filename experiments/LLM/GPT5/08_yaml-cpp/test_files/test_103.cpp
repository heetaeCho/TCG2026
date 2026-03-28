// File: ./TestProjects/yaml-cpp/test/stringsource_test_103.cpp

#include <gtest/gtest.h>

#include <cstddef>

#include "stringsource.h"

namespace {

class StringCharSourceTest_103 : public ::testing::Test {
protected:
  static YAML::StringCharSource Make(const char* s, std::size_t n) {
    return YAML::StringCharSource(s, n);
  }
};

TEST_F(StringCharSourceTest_103, IndexingReadsFromBeginning_103) {
  auto src = Make("abc", 3);
  EXPECT_EQ(src[0], 'a');
  EXPECT_EQ(src[1], 'b');
  EXPECT_EQ(src[2], 'c');
}

TEST_F(StringCharSourceTest_103, IndexingWithOffsetViaPlusReadsFromNewPosition_103) {
  auto src = Make("abcdef", 6);

  const auto shifted = src + 2;
  EXPECT_EQ(shifted[0], 'c');
  EXPECT_EQ(shifted[1], 'd');

  // operator+ should not mutate the original source.
  EXPECT_EQ(src[0], 'a');
  EXPECT_EQ(src[1], 'b');
}

TEST_F(StringCharSourceTest_103, PlusWithZeroBehavesLikeNoShift_103) {
  auto src = Make("xyz", 3);
  const auto same = src + 0;
  EXPECT_EQ(same[0], 'x');
  EXPECT_EQ(same[1], 'y');
  EXPECT_EQ(same[2], 'z');
}

TEST_F(StringCharSourceTest_103, PreIncrementAdvancesByOne_103) {
  auto src = Make("hello", 5);

  EXPECT_EQ(src[0], 'h');
  ++src;
  EXPECT_EQ(src[0], 'e');
  ++src;
  EXPECT_EQ(src[0], 'l');
}

TEST_F(StringCharSourceTest_103, PlusEqualsAdvancesByOffset_103) {
  auto src = Make("0123456789", 10);

  src += 3;
  EXPECT_EQ(src[0], '3');
  EXPECT_EQ(src[1], '4');

  src += 0;  // boundary: no-op offset
  EXPECT_EQ(src[0], '3');
}

TEST_F(StringCharSourceTest_103, CanReachLastCharacterUsingPlusEquals_103) {
  auto src = Make("abcd", 4);
  src += 3;
  EXPECT_EQ(src[0], 'd');
}

TEST_F(StringCharSourceTest_103, BoolAndNotOperatorsForEmptySource_103) {
  auto empty = Make("", 0);

  // Observable expectations for an "empty" source.
  EXPECT_FALSE(static_cast<bool>(empty));
  EXPECT_TRUE(!empty);
}

TEST_F(StringCharSourceTest_103, BoolTransitionsToFalseAfterAdvancingPastEnd_103) {
  auto src = Make("ab", 2);

  // Initially usable.
  EXPECT_TRUE(static_cast<bool>(src));
  EXPECT_FALSE(!src);

  // Advance to the end and then beyond; interface should reflect "no more data".
  src += 2;
  EXPECT_FALSE(static_cast<bool>(src));
  EXPECT_TRUE(!src);

  ++src;
  EXPECT_FALSE(static_cast<bool>(src));
  EXPECT_TRUE(!src);
}

TEST_F(StringCharSourceTest_103, PlusProducesIndependentCursorThatCanBeAdvancedSeparately_103) {
  auto src = Make("wxyz", 4);

  auto a = src + 1;
  auto b = src + 1;

  EXPECT_EQ(a[0], 'x');
  EXPECT_EQ(b[0], 'x');

  ++a;
  EXPECT_EQ(a[0], 'y');
  EXPECT_EQ(b[0], 'x');  // b should remain unaffected
  EXPECT_EQ(src[0], 'w'); // src should remain unaffected
}

}  // namespace
