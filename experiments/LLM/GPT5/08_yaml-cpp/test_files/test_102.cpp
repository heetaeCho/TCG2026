// TEST_ID: 102
#include <gtest/gtest.h>

#include <cstddef>
#include <string>

#include "stringsource.h"

namespace {

using YAML::StringCharSource;

class StringCharSourceTest_102 : public ::testing::Test {
 protected:
  static StringCharSource Make(const char* s, std::size_t n) { return StringCharSource(s, n); }
};

TEST_F(StringCharSourceTest_102, BoolConversionEmptyIsFalse_102) {
  auto src = Make("", 0);
  EXPECT_FALSE(static_cast<bool>(src));
  EXPECT_TRUE(!src);
}

TEST_F(StringCharSourceTest_102, BoolConversionNonEmptyIsTrue_102) {
  const char data[] = "abc";
  auto src = Make(data, 3);
  EXPECT_TRUE(static_cast<bool>(src));
  EXPECT_FALSE(!src);
}

TEST_F(StringCharSourceTest_102, IndexAccessReturnsExpectedCharacters_102) {
  const char data[] = "xyz";
  auto src = Make(data, 3);

  EXPECT_EQ(src[0], 'x');
  EXPECT_EQ(src[1], 'y');
  EXPECT_EQ(src[2], 'z');
}

TEST_F(StringCharSourceTest_102, NotOperatorMatchesBoolConversion_102) {
  const char data[] = "hi";
  auto src = Make(data, 2);

  EXPECT_EQ(!src, !static_cast<bool>(src));
  ++src;  // advance
  EXPECT_EQ(!src, !static_cast<bool>(src));
  ++src;  // advance to end
  EXPECT_EQ(!src, !static_cast<bool>(src));
}

TEST_F(StringCharSourceTest_102, PreIncrementAdvancesAndEventuallyBecomesFalse_102) {
  const char data[] = "ab";
  auto src = Make(data, 2);

  ASSERT_TRUE(static_cast<bool>(src));

  ++src;
  EXPECT_TRUE(static_cast<bool>(src)) << "After 1 increment with size=2, source should still be truthy";

  ++src;
  EXPECT_FALSE(static_cast<bool>(src)) << "After 2 increments with size=2, source should be exhausted";
  EXPECT_TRUE(!src);
}

TEST_F(StringCharSourceTest_102, PlusOperatorProducesAdvancedCopyWithoutMutatingOriginal_102) {
  const char data[] = "abcd";
  auto src = Make(data, 4);

  auto advanced = src + 2;

  // Original should remain usable and index from the start.
  EXPECT_TRUE(static_cast<bool>(src));
  EXPECT_EQ(src[0], 'a');
  EXPECT_EQ(src[1], 'b');

  // Advanced source should see later characters at index 0/1.
  EXPECT_TRUE(static_cast<bool>(advanced));
  EXPECT_EQ(advanced[0], 'c');
  EXPECT_EQ(advanced[1], 'd');
}

TEST_F(StringCharSourceTest_102, PlusOperatorCanYieldExhaustedSourceAtOrPastEnd_102) {
  const char data[] = "abcd";
  auto src = Make(data, 4);

  auto at_end = src + 4;
  EXPECT_FALSE(static_cast<bool>(at_end));
  EXPECT_TRUE(!at_end);

  auto past_end = src + 5;
  EXPECT_FALSE(static_cast<bool>(past_end));
  EXPECT_TRUE(!past_end);
}

TEST_F(StringCharSourceTest_102, PlusEqualAdvancesByOffset_102) {
  const char data[] = "hello";
  auto src = Make(data, 5);

  src += static_cast<std::size_t>(1);
  EXPECT_TRUE(static_cast<bool>(src));
  EXPECT_EQ(src[0], 'e');

  src += static_cast<std::size_t>(2);
  EXPECT_TRUE(static_cast<bool>(src));
  EXPECT_EQ(src[0], 'l');  // "lo" starts at index 3 in original

  src += static_cast<std::size_t>(2);
  EXPECT_FALSE(static_cast<bool>(src));
  EXPECT_TRUE(!src);
}

TEST_F(StringCharSourceTest_102, PlusEqualBeyondEndRemainsExhausted_102) {
  const char data[] = "hi";
  auto src = Make(data, 2);

  src += static_cast<std::size_t>(100);
  EXPECT_FALSE(static_cast<bool>(src));
  EXPECT_TRUE(!src);

  // Further operations should keep it exhausted (observable via bool/!).
  ++src;
  EXPECT_FALSE(static_cast<bool>(src));
  EXPECT_TRUE(!src);

  src += static_cast<std::size_t>(1);
  EXPECT_FALSE(static_cast<bool>(src));
  EXPECT_TRUE(!src);
}

}  // namespace
