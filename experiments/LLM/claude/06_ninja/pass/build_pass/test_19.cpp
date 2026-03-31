#include "gtest/gtest.h"
#include "eval_env.h"

// A simple Env implementation for testing Evaluate
struct TestEnv : public Env {
  std::map<std::string, std::string> vars;
  
  std::string LookupVariable(const std::string& var) override {
    auto it = vars.find(var);
    if (it != vars.end())
      return it->second;
    return "";
  }
};

class EvalStringTest_19 : public ::testing::Test {
protected:
  EvalString eval_;
  TestEnv env_;
};

// Test that a default-constructed EvalString is empty
TEST_F(EvalStringTest_19, DefaultConstructedIsEmpty_19) {
  EXPECT_TRUE(eval_.empty());
}

// Test that Clear makes the EvalString empty
TEST_F(EvalStringTest_19, ClearMakesEmpty_19) {
  eval_.AddText("hello");
  EXPECT_FALSE(eval_.empty());
  eval_.Clear();
  EXPECT_TRUE(eval_.empty());
}

// Test AddText then Evaluate returns the plain text
TEST_F(EvalStringTest_19, AddTextEvaluatesAsPlainText_19) {
  eval_.AddText("hello world");
  std::string result = eval_.Evaluate(&env_);
  EXPECT_EQ("hello world", result);
}

// Test AddSpecial evaluates by looking up in the environment
TEST_F(EvalStringTest_19, AddSpecialEvaluatesFromEnv_19) {
  env_.vars["foo"] = "bar";
  eval_.AddSpecial("foo");
  std::string result = eval_.Evaluate(&env_);
  EXPECT_EQ("bar", result);
}

// Test mixed text and special tokens
TEST_F(EvalStringTest_19, MixedTextAndSpecial_19) {
  env_.vars["name"] = "world";
  eval_.AddText("hello ");
  eval_.AddSpecial("name");
  eval_.AddText("!");
  std::string result = eval_.Evaluate(&env_);
  EXPECT_EQ("hello world!", result);
}

// Test that empty after AddText is false
TEST_F(EvalStringTest_19, NotEmptyAfterAddText_19) {
  eval_.AddText("something");
  EXPECT_FALSE(eval_.empty());
}

// Test that empty after AddSpecial is false
TEST_F(EvalStringTest_19, NotEmptyAfterAddSpecial_19) {
  eval_.AddSpecial("var");
  EXPECT_FALSE(eval_.empty());
}

// Test Evaluate with missing variable returns empty for that variable
TEST_F(EvalStringTest_19, EvaluateMissingVarReturnsEmpty_19) {
  eval_.AddText("prefix_");
  eval_.AddSpecial("nonexistent");
  eval_.AddText("_suffix");
  std::string result = eval_.Evaluate(&env_);
  EXPECT_EQ("prefix__suffix", result);
}

// Test Clear after adding multiple tokens
TEST_F(EvalStringTest_19, ClearAfterMultipleTokens_19) {
  eval_.AddText("a");
  eval_.AddSpecial("b");
  eval_.AddText("c");
  eval_.Clear();
  EXPECT_TRUE(eval_.empty());
  std::string result = eval_.Evaluate(&env_);
  EXPECT_EQ("", result);
}

// Test Unparse on plain text
TEST_F(EvalStringTest_19, UnparsePlainText_19) {
  eval_.AddText("hello");
  std::string unparsed = eval_.Unparse();
  // Plain text should appear as-is in unparse
  EXPECT_FALSE(unparsed.empty());
  EXPECT_NE(std::string::npos, unparsed.find("hello"));
}

// Test Unparse on special token contains the variable reference
TEST_F(EvalStringTest_19, UnparseSpecialContainsVariable_19) {
  eval_.AddSpecial("varname");
  std::string unparsed = eval_.Unparse();
  EXPECT_NE(std::string::npos, unparsed.find("varname"));
}

// Test Serialize returns a non-empty string after AddText
TEST_F(EvalStringTest_19, SerializeAfterAddText_19) {
  eval_.AddText("data");
  std::string serialized = eval_.Serialize();
  EXPECT_FALSE(serialized.empty());
}

// Test Serialize on empty EvalString
TEST_F(EvalStringTest_19, SerializeEmpty_19) {
  std::string serialized = eval_.Serialize();
  // An empty EvalString serialized should produce some result (possibly empty)
  // Just ensure it doesn't crash
  SUCCEED();
}

// Test adding empty text
TEST_F(EvalStringTest_19, AddEmptyText_19) {
  eval_.AddText("");
  // Adding empty text may or may not make it non-empty depending on implementation
  std::string result = eval_.Evaluate(&env_);
  EXPECT_EQ("", result);
}

// Test multiple special tokens in sequence
TEST_F(EvalStringTest_19, MultipleSpecialTokens_19) {
  env_.vars["a"] = "hello";
  env_.vars["b"] = " ";
  env_.vars["c"] = "world";
  eval_.AddSpecial("a");
  eval_.AddSpecial("b");
  eval_.AddSpecial("c");
  std::string result = eval_.Evaluate(&env_);
  EXPECT_EQ("hello world", result);
}

// Test Clear then re-add tokens
TEST_F(EvalStringTest_19, ClearThenReuse_19) {
  eval_.AddText("first");
  eval_.Clear();
  eval_.AddText("second");
  std::string result = eval_.Evaluate(&env_);
  EXPECT_EQ("second", result);
}

// Test Evaluate with only special and env returns correct value
TEST_F(EvalStringTest_19, EvaluateOnlySpecial_19) {
  env_.vars["key"] = "value";
  eval_.AddSpecial("key");
  EXPECT_EQ("value", eval_.Evaluate(&env_));
}

// Test that single token optimization works (adding one text)
TEST_F(EvalStringTest_19, SingleTokenText_19) {
  eval_.AddText("single");
  EXPECT_EQ("single", eval_.Evaluate(&env_));
  EXPECT_FALSE(eval_.empty());
}

// Test long string handling
TEST_F(EvalStringTest_19, LongStringText_19) {
  std::string longStr(10000, 'x');
  eval_.AddText(longStr);
  std::string result = eval_.Evaluate(&env_);
  EXPECT_EQ(longStr, result);
}

// Test special characters in text
TEST_F(EvalStringTest_19, SpecialCharactersInText_19) {
  eval_.AddText("path/to/file.cc -I../include");
  std::string result = eval_.Evaluate(&env_);
  EXPECT_EQ("path/to/file.cc -I../include", result);
}
