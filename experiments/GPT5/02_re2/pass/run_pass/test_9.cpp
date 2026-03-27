// File: re2_consume_tests_9.cc
#include <gtest/gtest.h>
#include "re2/re2.h"
#include "absl/strings/string_view.h"

using re2::RE2;

class RE2_ConsumeTest_9 : public ::testing::Test {};

// Normal operation: matches at the beginning, advances input, captures text.
TEST_F(RE2_ConsumeTest_9, Consume_AdvancesInputAndCaptures_9) {
  std::string backing = "abc123";
  absl::string_view input(backing);

  RE2 re("([a-z]+)");
  std::string word;

  ASSERT_TRUE(RE2::Consume(&input, re, &word));
  EXPECT_EQ(word, "abc");     // captured portion
  EXPECT_EQ(input, "123");    // input advanced past the match
}

// Boundary: no match at the beginning -> returns false and input unchanged.
TEST_F(RE2_ConsumeTest_9, Consume_NoMatch_DoesNotAdvance_9) {
  std::string backing = "abc123";
  absl::string_view input(backing);
  auto original = input;

  RE2 re("([0-9]+)");  // does not match at start
  std::string digits;

  ASSERT_FALSE(RE2::Consume(&input, re, &digits));
  EXPECT_EQ(input, original);  // must remain unchanged
  EXPECT_TRUE(digits.empty()); // no capture on failure (observable via value)
}

// Normal operation: multiple sequential consumes advance step-by-step.
TEST_F(RE2_ConsumeTest_9, Consume_SequentialCallsAdvance_9) {
  std::string backing = "abc123def";
  absl::string_view input(backing);

  RE2 letters("([a-z]+)");
  RE2 numbers("([0-9]+)");

  std::string w, d;

  ASSERT_TRUE(RE2::Consume(&input, letters, &w));
  EXPECT_EQ(w, "abc");
  EXPECT_EQ(input, "123def");

  ASSERT_TRUE(RE2::Consume(&input, numbers, &d));
  EXPECT_EQ(d, "123");
  EXPECT_EQ(input, "def");
}

// Boundary: empty pattern can match an empty prefix.
// Expect success but no advancement (observable via unchanged input).
TEST_F(RE2_ConsumeTest_9, Consume_EmptyPattern_SucceedsWithoutAdvancing_9) {
  std::string backing = "xyz";
  absl::string_view input(backing);
  auto original = input;

  RE2 empty_re("");   // empty pattern
  ASSERT_TRUE(RE2::Consume(&input, empty_re));
  EXPECT_EQ(input, original);  // zero-length consumption => no advancement
}

// Captures: multiple capture groups populated correctly on success.
TEST_F(RE2_ConsumeTest_9, Consume_CapturesMultipleGroups_9) {
  std::string backing = "foo-bar baz";
  absl::string_view input(backing);

  RE2 re("(\\w+)-(\\w+)");
  std::string left, right;

  ASSERT_TRUE(RE2::Consume(&input, re, &left, &right));
  EXPECT_EQ(left, "foo");
  EXPECT_EQ(right, "bar");
  EXPECT_EQ(input, " baz");  // advanced past "foo-bar"
}
