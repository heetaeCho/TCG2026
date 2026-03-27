// File: filtered_re2_move_test.cc

#include "re2/filtered_re2.h"
#include "re2/re2.h"
#include "gtest/gtest.h"

using re2::FilteredRE2;

class FilteredRE2MoveTest_606 : public ::testing::Test {
protected:
  RE2::Options opts_;  // Default options are fine for black-box tests
};

// Verifies that regexps added to the source object continue to match
// the same way after move-construction into the destination.
TEST_F(FilteredRE2MoveTest_606, MoveConstructorTransfersRegexps_606) {
  FilteredRE2 src;
  int id_foo = -1;
  int id_bar = -1;

  // Add two simple patterns and capture their observable IDs.
  EXPECT_EQ(RE2::NoError, src.Add("foo", opts_, &id_foo));
  EXPECT_EQ(RE2::NoError, src.Add("bar", opts_, &id_bar));
  ASSERT_GE(id_foo, 0);
  ASSERT_GE(id_bar, 0);

  // Baseline behavior before move: SlowFirstMatch should return one of the IDs.
  // Choose inputs that clearly distinguish patterns.
  EXPECT_EQ(id_foo, src.SlowFirstMatch("food"));
  EXPECT_EQ(id_bar, src.SlowFirstMatch("bargain"));

  // Move-construct the destination from the source.
  FilteredRE2 dst(std::move(src));

  // Destination preserves observable behavior.
  EXPECT_EQ(id_foo, dst.SlowFirstMatch("seafood foo truck"));
  EXPECT_EQ(id_bar, dst.SlowFirstMatch("best bargain bar"));

  // Moved-from object should be in a valid but "empty" state w.r.t. public API.
  // We can only check observable effects: NumRegexps should be zero
  // and there should be no match for previous inputs.
  EXPECT_EQ(0, src.NumRegexps());
  EXPECT_LT(src.SlowFirstMatch("foo"), 0);
  EXPECT_LT(src.SlowFirstMatch("bar"), 0);
}

// Verifies that the moved-from object remains usable via the public API:
// we can add new patterns and get coherent IDs and matches again.
TEST_F(FilteredRE2MoveTest_606, MovedFromObjectCanBeReused_606) {
  FilteredRE2 src;

  int id_a = -1;
  ASSERT_EQ(RE2::NoError, src.Add("a+", opts_, &id_a));
  FilteredRE2 dst(std::move(src));

  // Reuse the moved-from object: add a fresh pattern and observe behavior.
  int id_new = -1;
  EXPECT_EQ(RE2::NoError, src.Add("baz", opts_, &id_new));
  // NumRegexps should reflect only the newly added pattern(s) post-move.
  EXPECT_GE(id_new, 0);
  EXPECT_EQ(1, src.NumRegexps());

  // SlowFirstMatch should return the new ID for matching text.
  EXPECT_EQ(id_new, src.SlowFirstMatch("bazooka"));
  // Non-matching text should not return a valid ID.
  EXPECT_LT(src.SlowFirstMatch("qux"), 0);

  // The destination still carries the original pattern(s).
  EXPECT_LT(dst.SlowFirstMatch("qux"), 0);           // doesn't match old "a+" or others
  EXPECT_GE(dst.SlowFirstMatch("aaaa"), 0);          // matches something that looks like original "a+"
}

// If the source was used pre-move (added multiple patterns), the destination
// should still be consistent across multiple inputs post-move.
TEST_F(FilteredRE2MoveTest_606, MovePreservesMultiplePatternBehavior_606) {
  FilteredRE2 src;

  int id_num = -1;
  int id_word = -1;
  ASSERT_EQ(RE2::NoError, src.Add("[0-9]+", opts_, &id_num));
  ASSERT_EQ(RE2::NoError, src.Add("[A-Za-z]+", opts_, &id_word));

  // Confirm baseline observable behavior with distinct probes.
  EXPECT_EQ(id_num,  src.SlowFirstMatch("there are 123 apples"));
  EXPECT_EQ(id_word, src.SlowFirstMatch("!!! hello 42"));

  FilteredRE2 dst(std::move(src));

  // After move, the destination should produce the same observable outcomes.
  EXPECT_EQ(id_num,  dst.SlowFirstMatch("version 2.0 has 9876 fixes"));
  EXPECT_EQ(id_word, dst.SlowFirstMatch("***world***"));

  // Moved-from should behave empty for previous probes.
  EXPECT_EQ(0, src.NumRegexps());
  EXPECT_LT(src.SlowFirstMatch("123"), 0);
  EXPECT_LT(src.SlowFirstMatch("abc"), 0);
}
