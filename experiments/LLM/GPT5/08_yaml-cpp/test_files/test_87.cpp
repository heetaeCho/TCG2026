// TEST_ID: 87
#include <gtest/gtest.h>

#include <string>

// Include the header under test.
#include "yaml-cpp/exceptions.h"

namespace {

class ErrorMsgTest_87 : public ::testing::Test {};

TEST_F(ErrorMsgTest_87, BadSubscriptWithKey_FormatsMessageWithKey_87) {
  const char* key = "abc";
  const std::string msg = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);

  // Exact formatting is observable via the interface and the provided constant.
  EXPECT_EQ(std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"abc\")", msg);
}

TEST_F(ErrorMsgTest_87, BadSubscriptWithKey_AllowsEmptyKey_87) {
  const char* key = "";
  const std::string msg = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);

  EXPECT_EQ(std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"\")", msg);
}

TEST_F(ErrorMsgTest_87, BadSubscriptWithKey_PreservesWhitespace_87) {
  const char* key = "  spaced key  ";
  const std::string msg = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);

  EXPECT_EQ(std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"  spaced key  \")", msg);
}

TEST_F(ErrorMsgTest_87, BadSubscriptWithKey_DoesNotEscapeQuotesInKey_87) {
  // The interface accepts a C-string; behavior is observable in the returned message.
  const char* key = "a\"b";
  const std::string msg = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);

  EXPECT_EQ(std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"a\"b\")", msg);
}

TEST_F(ErrorMsgTest_87, BadSubscriptWithKey_HandlesLongKey_87) {
  const std::string long_key(4096, 'x');
  const std::string msg = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(long_key.c_str());

  EXPECT_EQ(std::string(YAML::ErrorMsg::BAD_SUBSCRIPT) + " (key: \"" + long_key + "\")", msg);
  // Sanity: starts with the known prefix.
  EXPECT_TRUE(msg.rfind(YAML::ErrorMsg::BAD_SUBSCRIPT, 0) == 0);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(ErrorMsgTest_87, BadSubscriptWithKey_NullptrKey_DeathOrCrash_87) {
  // Passing nullptr to a function that streams a const char* may be undefined.
  // If the implementation crashes, this test captures it as an observable error case.
  EXPECT_DEATH(
      {
        (void)YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(nullptr);
      },
      ".*");
}
#endif

}  // namespace
