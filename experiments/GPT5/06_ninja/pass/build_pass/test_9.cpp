// File: lexer_readpath_test_9.cc

#include "lexer.h"
#include "eval_env.h"

#include <gtest/gtest.h>
#include <string>

class LexerReadPathTest_9 : public ::testing::Test {};

// Normal operation: single simple path terminated by newline.
TEST_F(LexerReadPathTest_9, ReadsSingleSimplePath_9) {
  Lexer lexer("out\n");
  EvalString path;
  std::string err;

  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(path.empty());
  // For a simple raw path, Serialize should contain the path text.
  EXPECT_EQ("[out]", path.Serialize());
}

// Normal operation: multiple whitespace-separated paths, then newline.
TEST_F(LexerReadPathTest_9, ReadsMultiplePathsSeparatedBySpace_9) {
  Lexer lexer("out1 out2\n");
  EvalString path;
  std::string err;

  // First path
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(path.empty());
  EXPECT_EQ("[out1]", path.Serialize());

  path.Clear();

  // Second path
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(path.empty());
  EXPECT_EQ("[out2]", path.Serialize());

  path.Clear();

  // After the last path, at the newline delimiter, ReadPath should
  // succeed but return an empty EvalString (used as loop terminator).
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_TRUE(path.empty());
}

// Boundary condition: delimiter (newline) appears immediately, so the
// returned path is empty but it's not an error.
TEST_F(LexerReadPathTest_9, ReturnsEmptyPathWhenNewlineIsFirst_9) {
  Lexer lexer("\n");
  EvalString path;
  std::string err;

  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_TRUE(path.empty());
}

// Normal operation with variable expansion: path contains a '$var'.
// We only check that parsing succeeds and the serialized form contains
// the variable reference somewhere.
TEST_F(LexerReadPathTest_9, ParsesPathWithVariableExpansion_9) {
  Lexer lexer("out$var\n");
  EvalString path;
  std::string err;

  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(path.empty());

  const std::string serialized = path.Serialize();
  EXPECT_NE(std::string::npos, serialized.find("out"));
  EXPECT_NE(std::string::npos, serialized.find("$var"));
}

// Error case: bad '$' escape must cause ReadPath to fail and write an error.
TEST_F(LexerReadPathTest_9, FailsOnBadDollarEscapeAndSetsError_9) {
  // This mirrors the existing error case used for ReadVarValue, but
  // exercises ReadPath instead.
  Lexer lexer("foo$\nbad $");
  EvalString path;
  std::string err;

  EXPECT_FALSE(lexer.ReadPath(&path, &err));
  EXPECT_FALSE(err.empty());

  // Don't depend on the exact formatting, just key parts of the message.
  EXPECT_NE(std::string::npos, err.find("bad $-escape"));
  EXPECT_NE(std::string::npos, err.find("bad $"));
}
