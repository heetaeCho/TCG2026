// TEST_ID: 104
#include <gtest/gtest.h>

#include "stringsource.h"  // ./TestProjects/yaml-cpp/src/stringsource.h

namespace {

class StringCharSourceTest_104 : public ::testing::Test {};

TEST_F(StringCharSourceTest_104, NotOperatorIsNegationOfBoolConversion_104) {
  const char kText[] = "abc";
  YAML::StringCharSource src(kText, 3);

  // operator! is defined as: !static_cast<bool>(*this)
  const bool as_bool = static_cast<bool>(src);
  EXPECT_EQ(!src, !as_bool);
}

TEST_F(StringCharSourceTest_104, DoubleNegationMatchesBoolConversion_104) {
  const char kText[] = "hello";
  YAML::StringCharSource src(kText, 5);

  // !!src should be equivalent to static_cast<bool>(src) for any instance.
  const bool as_bool = static_cast<bool>(src);
  EXPECT_EQ(!!src, as_bool);
}

TEST_F(StringCharSourceTest_104, EmptySizeStillMatchesBoolNegationLaw_104) {
  const char kText[] = "ignored";
  YAML::StringCharSource src(kText, 0);

  const bool as_bool = static_cast<bool>(src);
  EXPECT_EQ(!src, !as_bool);
  EXPECT_EQ(!!src, as_bool);
}

TEST_F(StringCharSourceTest_104, NotOperatorDoesNotThrow_104) {
  const char kText[] = "x";
  YAML::StringCharSource src(kText, 1);

  EXPECT_NO_THROW({
    (void)!src;
    (void)static_cast<bool>(src);
    (void)!!src;
  });
}

}  // namespace
