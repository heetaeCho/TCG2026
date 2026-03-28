// File: eval_string_empty_test_20.cc

#include "gtest/gtest.h"

#include "eval_env.h"      // EvalString
#include "string_piece.h"  // StringPiece (assumed available in the project)

class EvalStringTest_20 : public ::testing::Test {
 protected:
  EvalString eval_string_;
};

// Verify that a default-constructed EvalString is empty.
TEST_F(EvalStringTest_20, InitiallyEmpty_20) {
  EXPECT_TRUE(eval_string_.empty());
}

// After adding normal text, EvalString should no longer be empty.
TEST_F(EvalStringTest_20, AddTextMakesNonEmpty_20) {
  eval_string_.AddText(StringPiece("hello"));
  EXPECT_FALSE(eval_string_.empty());
}

// After adding a special token, EvalString should no longer be empty.
TEST_F(EvalStringTest_20, AddSpecialMakesNonEmpty_20) {
  eval_string_.AddSpecial(StringPiece("$(var)"));
  EXPECT_FALSE(eval_string_.empty());
}

// After making it non-empty, Clear() should make EvalString empty again.
TEST_F(EvalStringTest_20, ClearMakesEmptyAgain_20) {
  eval_string_.AddText(StringPiece("hello"));
  ASSERT_FALSE(eval_string_.empty());

  eval_string_.Clear();
  EXPECT_TRUE(eval_string_.empty());
}

// Calling Clear() on an already empty EvalString should keep it empty.
TEST_F(EvalStringTest_20, ClearOnAlreadyEmptyKeepsEmpty_20) {
  ASSERT_TRUE(eval_string_.empty());

  eval_string_.Clear();
  EXPECT_TRUE(eval_string_.empty());
}
