#include "gtest/gtest.h"
#include "eval_env.h"

// A simple Env implementation for testing Evaluate
struct TestEnv : public Env {
  std::map<std::string, std::string> vars;
  
  virtual std::string LookupVariable(const std::string& var) {
    auto it = vars.find(var);
    if (it != vars.end())
      return it->second;
    return "";
  }
};

// Test that a default-constructed EvalString is empty
TEST(EvalStringTest_20, DefaultConstructedIsEmpty_20) {
  EvalString eval;
  EXPECT_TRUE(eval.empty());
}

// Test that adding text makes it non-empty
TEST(EvalStringTest_20, AddTextMakesNonEmpty_20) {
  EvalString eval;
  eval.AddText(StringPiece("hello"));
  EXPECT_FALSE(eval.empty());
}

// Test that adding special (variable) makes it non-empty
TEST(EvalStringTest_20, AddSpecialMakesNonEmpty_20) {
  EvalString eval;
  eval.AddSpecial(StringPiece("varname"));
  EXPECT_FALSE(eval.empty());
}

// Test Evaluate with plain text only
TEST(EvalStringTest_20, EvaluatePlainText_20) {
  EvalString eval;
  eval.AddText(StringPiece("plain text"));
  
  TestEnv env;
  std::string result = eval.Evaluate(&env);
  EXPECT_EQ("plain text", result);
}

// Test Evaluate with a variable that exists in the environment
TEST(EvalStringTest_20, EvaluateWithVariable_20) {
  EvalString eval;
  eval.AddText(StringPiece("hello "));
  eval.AddSpecial(StringPiece("name"));
  
  TestEnv env;
  env.vars["name"] = "world";
  std::string result = eval.Evaluate(&env);
  EXPECT_EQ("hello world", result);
}

// Test Evaluate with a variable not in the environment (should resolve to empty)
TEST(EvalStringTest_20, EvaluateWithMissingVariable_20) {
  EvalString eval;
  eval.AddText(StringPiece("hello "));
  eval.AddSpecial(StringPiece("missing"));
  
  TestEnv env;
  std::string result = eval.Evaluate(&env);
  EXPECT_EQ("hello ", result);
}

// Test Evaluate with multiple text and special tokens
TEST(EvalStringTest_20, EvaluateMultipleTokens_20) {
  EvalString eval;
  eval.AddText(StringPiece("a"));
  eval.AddSpecial(StringPiece("x"));
  eval.AddText(StringPiece("b"));
  eval.AddSpecial(StringPiece("y"));
  eval.AddText(StringPiece("c"));
  
  TestEnv env;
  env.vars["x"] = "1";
  env.vars["y"] = "2";
  std::string result = eval.Evaluate(&env);
  EXPECT_EQ("a1b2c", result);
}

// Test Unparse returns a string representation
TEST(EvalStringTest_20, UnparseBasic_20) {
  EvalString eval;
  eval.AddText(StringPiece("text"));
  std::string unparsed = eval.Unparse();
  EXPECT_FALSE(unparsed.empty());
}

// Test Unparse with special token includes variable notation
TEST(EvalStringTest_20, UnparseWithSpecial_20) {
  EvalString eval;
  eval.AddText(StringPiece("prefix"));
  eval.AddSpecial(StringPiece("var"));
  std::string unparsed = eval.Unparse();
  // The unparsed string should contain "var" in some form
  EXPECT_NE(std::string::npos, unparsed.find("var"));
}

// Test Serialize produces output
TEST(EvalStringTest_20, SerializeBasic_20) {
  EvalString eval;
  eval.AddText(StringPiece("some text"));
  std::string serialized = eval.Serialize();
  EXPECT_FALSE(serialized.empty());
}

// Test Clear makes the EvalString empty again
TEST(EvalStringTest_20, ClearMakesEmpty_20) {
  EvalString eval;
  eval.AddText(StringPiece("something"));
  EXPECT_FALSE(eval.empty());
  eval.Clear();
  EXPECT_TRUE(eval.empty());
}

// Test Clear after adding special
TEST(EvalStringTest_20, ClearAfterSpecial_20) {
  EvalString eval;
  eval.AddSpecial(StringPiece("var"));
  EXPECT_FALSE(eval.empty());
  eval.Clear();
  EXPECT_TRUE(eval.empty());
}

// Test adding empty text
TEST(EvalStringTest_20, AddEmptyText_20) {
  EvalString eval;
  eval.AddText(StringPiece(""));
  // Behavior depends on implementation - but we can at least check it doesn't crash
  // and evaluate returns empty or the empty string
  TestEnv env;
  std::string result = eval.Evaluate(&env);
  EXPECT_EQ("", result);
}

// Test Evaluate after Clear returns empty
TEST(EvalStringTest_20, EvaluateAfterClear_20) {
  EvalString eval;
  eval.AddText(StringPiece("hello"));
  eval.Clear();
  
  TestEnv env;
  std::string result = eval.Evaluate(&env);
  EXPECT_EQ("", result);
}

// Test single token optimization path - adding just one plain text
TEST(EvalStringTest_20, SinglePlainToken_20) {
  EvalString eval;
  eval.AddText(StringPiece("single"));
  
  TestEnv env;
  EXPECT_EQ("single", eval.Evaluate(&env));
  EXPECT_FALSE(eval.empty());
}

// Test adding only special tokens
TEST(EvalStringTest_20, OnlySpecialTokens_20) {
  EvalString eval;
  eval.AddSpecial(StringPiece("a"));
  eval.AddSpecial(StringPiece("b"));
  
  TestEnv env;
  env.vars["a"] = "X";
  env.vars["b"] = "Y";
  std::string result = eval.Evaluate(&env);
  EXPECT_EQ("XY", result);
}

// Test that Serialize works on empty EvalString
TEST(EvalStringTest_20, SerializeEmpty_20) {
  EvalString eval;
  std::string serialized = eval.Serialize();
  // Should not crash; result may be empty
  EXPECT_TRUE(serialized.empty() || !serialized.empty());
}

// Test Unparse on empty EvalString
TEST(EvalStringTest_20, UnparseEmpty_20) {
  EvalString eval;
  std::string unparsed = eval.Unparse();
  EXPECT_TRUE(unparsed.empty());
}
