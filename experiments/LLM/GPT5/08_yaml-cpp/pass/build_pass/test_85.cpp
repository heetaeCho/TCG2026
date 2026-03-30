// TEST_ID 85
#include <gtest/gtest.h>

#include <string>
#include <type_traits>
#include <utility>

#include "yaml-cpp/exceptions.h"

namespace {

using YAML::ErrorMsg::BAD_SUBSCRIPT;
using YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY;

// Detection idiom: checks whether BAD_SUBSCRIPT_WITH_KEY(T const&) is a valid expression.
template <typename T, typename = void>
struct IsBadSubscriptWithKeyInvocable : std::false_type {};

template <typename T>
struct IsBadSubscriptWithKeyInvocable<
    T, std::void_t<decltype(BAD_SUBSCRIPT_WITH_KEY(std::declval<const T&>()))>> : std::true_type {};

// A clearly non-numeric custom key type.
struct CustomKey {
  int v = 0;
};

}  // namespace

TEST(ErrorMsgExceptionsTest_85, IsInvocableForNonNumericTypes_85) {
  static_assert(IsBadSubscriptWithKeyInvocable<std::string>::value,
                "BAD_SUBSCRIPT_WITH_KEY should be invocable for std::string keys");
  static_assert(IsBadSubscriptWithKeyInvocable<const char*>::value,
                "BAD_SUBSCRIPT_WITH_KEY should be invocable for C-string keys");
  static_assert(IsBadSubscriptWithKeyInvocable<CustomKey>::value,
                "BAD_SUBSCRIPT_WITH_KEY should be invocable for custom non-numeric keys");
}

TEST(ErrorMsgExceptionsTest_85, ReturnsBadSubscriptForStringKey_85) {
  const std::string key = "abc";
  const std::string msg = BAD_SUBSCRIPT_WITH_KEY(key);
  EXPECT_EQ(msg, BAD_SUBSCRIPT);
}

TEST(ErrorMsgExceptionsTest_85, ReturnsBadSubscriptForEmptyStringKey_85) {
  const std::string key;
  const std::string msg = BAD_SUBSCRIPT_WITH_KEY(key);
  EXPECT_EQ(msg, BAD_SUBSCRIPT);
}

TEST(ErrorMsgExceptionsTest_85, ReturnsBadSubscriptForCStringKey_85) {
  const char* key = "k";
  const std::string msg = BAD_SUBSCRIPT_WITH_KEY(key);
  EXPECT_EQ(msg, BAD_SUBSCRIPT);
}

TEST(ErrorMsgExceptionsTest_85, ReturnsBadSubscriptForNullCStringKey_85) {
  const char* key = nullptr;
  const std::string msg = BAD_SUBSCRIPT_WITH_KEY(key);
  EXPECT_EQ(msg, BAD_SUBSCRIPT);
}

TEST(ErrorMsgExceptionsTest_85, ReturnsBadSubscriptForCustomKeyType_85) {
  const CustomKey key{123};
  const std::string msg = BAD_SUBSCRIPT_WITH_KEY(key);
  EXPECT_EQ(msg, BAD_SUBSCRIPT);
}
