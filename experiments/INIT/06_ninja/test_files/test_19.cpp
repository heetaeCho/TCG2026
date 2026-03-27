#include "gtest/gtest.h"

#include "eval_env.h"
#include "string_piece.h"

class EvalStringTest_19 : public ::testing::Test {
 protected:
  EvalString eval_string_;
};

// TEST_ID 19
// Clear on a default-constructed (empty) EvalString should be idempotent.
TEST_F(EvalStringTest_19, ClearOnEmptyEvalString_Idempotent_19) {
  EvalString fresh;

  // Capture the observable state of a fresh object.
  bool empty_before = fresh.empty();
  std::string unparse_before = fresh.Unparse();
  std::string serialize_before = fresh.Serialize();

  // Call Clear on the fresh object.
  fresh.Clear();

  // After Clear, observable state should remain the same.
  EXPECT_EQ(empty_before, fresh.empty());
  EXPECT_EQ(unparse_before, fresh.Unparse());
  EXPECT_EQ(serialize_before, fresh.Serialize());
}

// TEST_ID 19
// Clear after AddText should reset EvalString to its default observable state.
TEST_F(EvalStringTest_19, ClearAfterAddText_ResetsToDefaultState_19) {
  EvalString fresh;  // Default reference state.

  EvalString modified;
  modified.AddText(StringPiece("hello"));
  // Normal operation: after adding text, it should no longer be empty.
  EXPECT_FALSE(modified.empty());

  // Call Clear and ensure it matches the default state.
  modified.Clear();

  EXPECT_TRUE(modified.empty());
  EXPECT_EQ(fresh.Unparse(), modified.Unparse());
  EXPECT_EQ(fresh.Serialize(), modified.Serialize());
}

// TEST_ID 19
// Clear after AddSpecial should reset EvalString to its default observable state.
TEST_F(EvalStringTest_19, ClearAfterAddSpecial_ResetsToDefaultState_19) {
  EvalString fresh;  // Default reference state.

  EvalString modified;
  modified.AddSpecial(StringPiece("$var"));
  // Normal operation: after adding a special token, it should no longer be empty.
  EXPECT_FALSE(modified.empty());

  // Call Clear and ensure it matches the default state.
  modified.Clear();

  EXPECT_TRUE(modified.empty());
  EXPECT_EQ(fresh.Unparse(), modified.Unparse());
  EXPECT_EQ(fresh.Serialize(), modified.Serialize());
}

// TEST_ID 19
// Clear after a mixture of AddText and AddSpecial calls should reset to default.
TEST_F(EvalStringTest_19, ClearAfterMixedAdds_ResetsToDefaultState_19) {
  EvalString fresh;  // Default reference state.

  EvalString modified;
  modified.AddText(StringPiece("prefix "));
  modified.AddSpecial(StringPiece("$var"));
  modified.AddText(StringPiece(" suffix"));
  EXPECT_FALSE(modified.empty());  // Normal operation: content has been added.

  modified.Clear();

  EXPECT_TRUE(modified.empty());
  EXPECT_EQ(fresh.Unparse(), modified.Unparse());
  EXPECT_EQ(fresh.Serialize(), modified.Serialize());
}

// TEST_ID 19
// Clear after building a large EvalString should not crash and should reset to default.
TEST_F(EvalStringTest_19, ClearAfterLargeContent_DoesNotCrashAndResets_19) {
  EvalString fresh;  // Default reference state.

  EvalString modified;
  // Boundary/large-case: add a large amount of text.
  std::string large_text(10000, 'a');
  modified.AddText(StringPiece(large_text));
  EXPECT_FALSE(modified.empty());

  // Also add some special tokens.
  modified.AddSpecial(StringPiece("$very_long_variable_name"));
  EXPECT_FALSE(modified.empty());

  modified.Clear();

  EXPECT_TRUE(modified.empty());
  EXPECT_EQ(fresh.Unparse(), modified.Unparse());
  EXPECT_EQ(fresh.Serialize(), modified.Serialize());
}
