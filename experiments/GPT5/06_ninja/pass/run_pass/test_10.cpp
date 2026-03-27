#include <gtest/gtest.h>

#include "lexer.h"
#include "eval_env.h"

class LexerTest_10 : public ::testing::Test {};

// Normal operation: plain text + variable references.
TEST_F(LexerTest_10, ReadVarValue_ParsesPlainTextAndVariables_10) {
  Lexer lexer("plain text $var $VaR ${x}\n");
  EvalString value;
  std::string err;

  bool ok = lexer.ReadVarValue(&value, &err);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(err.empty());
  // Check that EvalString captured the structure of text and variables.
  EXPECT_EQ("[plain text ][$var][ ][$VaR][ ][$x]", value.Serialize());
}

// Boundary: empty value (just newline) should succeed and produce empty EvalString.
TEST_F(LexerTest_10, ReadVarValue_EmptyLineProducesEmptyEvalString_10) {
  Lexer lexer("\n");
  EvalString value;
  std::string err;

  bool ok = lexer.ReadVarValue(&value, &err);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(err.empty());
  EXPECT_TRUE(value.empty());
}

// Error case: malformed variable expansion should fail and set an error message.
TEST_F(LexerTest_10, ReadVarValue_MalformedVariableReportsError_10) {
  // Missing closing '}' for the variable expansion.
  Lexer lexer("${unclosed\n");
  EvalString value;
  std::string err;

  bool ok = lexer.ReadVarValue(&value, &err);

  EXPECT_FALSE(ok);
  EXPECT_FALSE(err.empty());
}
