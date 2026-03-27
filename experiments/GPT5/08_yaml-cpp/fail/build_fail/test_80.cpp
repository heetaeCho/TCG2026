// TEST_ID: 80
#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/traits.h"

namespace {

struct NotStreamableKey {
  int value = 0;
  // Intentionally no operator<< overload.
};

}  // namespace

// The provided partial implementation is:
// static std::string impl(const Key&) { return ""; }
//
// This matches the non-streamable specialization in yaml-cpp's traits helpers.
class TraitsTest_80 : public ::testing::Test {};

TEST_F(TraitsTest_80, StreamableToStringFalseAlwaysReturnsEmpty_80) {
  const NotStreamableKey k1{123};
  const NotStreamableKey k2{-1};

  const std::string s1 = YAML::streamable_to_string<NotStreamableKey, false>::impl(k1);
  const std::string s2 = YAML::streamable_to_string<NotStreamableKey, false>::impl(k2);

  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s2.empty());
}

TEST_F(TraitsTest_80, StreamableToStringFalseAcceptsDefaultConstructedKey_80) {
  const NotStreamableKey k{};

  const std::string s = YAML::streamable_to_string<NotStreamableKey, false>::impl(k);

  EXPECT_EQ(s, "");
}

TEST_F(TraitsTest_80, StreamableToStringFalseDoesNotThrow_80) {
  const NotStreamableKey k{999};

  EXPECT_NO_THROW({
    const std::string s = YAML::streamable_to_string<NotStreamableKey, false>::impl(k);
    EXPECT_EQ(s, "");
  });
}
