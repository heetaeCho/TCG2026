// TEST_ID: 72
#include <gtest/gtest.h>

#include <sstream>
#include <type_traits>

#include "stream.h"

namespace {

// Compile-time interface checks (observable via type traits).
static_assert(!std::is_copy_constructible_v<YAML::Stream>, "Stream must not be copy-constructible");
static_assert(!std::is_move_constructible_v<YAML::Stream>, "Stream must not be move-constructible");
static_assert(!std::is_copy_assignable_v<YAML::Stream>, "Stream must not be copy-assignable");
static_assert(!std::is_move_assignable_v<YAML::Stream>, "Stream must not be move-assignable");

class StreamOperatorNotTest_72 : public ::testing::Test {};

TEST_F(StreamOperatorNotTest_72, OperatorNotMatchesNegatedBool_72) {
  std::istringstream input("abc");
  YAML::Stream s(input);

  const bool as_bool = static_cast<bool>(s);
  const bool as_not = (!s);

  EXPECT_EQ(as_not, !as_bool);
}

TEST_F(StreamOperatorNotTest_72, OperatorNotMatchesNegatedBoolOnEmptyInput_72) {
  std::istringstream input("");
  YAML::Stream s(input);

  EXPECT_EQ((!s), !static_cast<bool>(s));
}

TEST_F(StreamOperatorNotTest_72, OperatorNotRemainsConsistentAfterSomeReads_72) {
  std::istringstream input("hello");
  YAML::Stream s(input);

  // Perform some observable operations; we do not assume how they work internally.
  (void)s.peek();
  (void)s.get();
  (void)s.get(2);

  EXPECT_EQ((!s), !static_cast<bool>(s));
}

TEST_F(StreamOperatorNotTest_72, OperatorNotBecomesTrueWhenBoolBecomesFalseAfterConsuming_72) {
  std::istringstream input("xyz");
  YAML::Stream s(input);

  // Consume characters until the stream reports false (or until a safe cap).
  // We only assert the relationship between operator! and operator bool.
  bool last_bool = static_cast<bool>(s);
  for (int i = 0; i < 1024 && last_bool; ++i) {
    (void)s.get();
    last_bool = static_cast<bool>(s);
    EXPECT_EQ((!s), !last_bool);
  }

  // If it ever becomes false, operator! must be true (per the interface definition).
  if (!last_bool) {
    EXPECT_TRUE(!s);
  }
}

TEST_F(StreamOperatorNotTest_72, OperatorNotConsistentWhenUnderlyingIstreamIsInFailState_72) {
  std::istringstream input("data");
  input.setstate(std::ios::failbit);

  YAML::Stream s(input);

  EXPECT_EQ((!s), !static_cast<bool>(s));
}

}  // namespace
