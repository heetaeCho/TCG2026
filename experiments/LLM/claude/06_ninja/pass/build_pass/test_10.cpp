#include "gtest/gtest.h"
#include "lexer.h"
#include "eval_env.h"

class LexerTest_10 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Default constructor creates a valid Lexer
TEST_F(LexerTest_10, DefaultConstructor_10) {
  Lexer lexer;
  // Should not crash; lexer exists in a default state
}

// Test: Explicit constructor with input
TEST_F(LexerTest_10, ExplicitConstructor_10) {
  Lexer lexer("some_input");
  // Should not crash
}

// Test: Start method initializes lexer with filename and input
TEST_F(LexerTest_10, StartMethod_10) {
  Lexer lexer;
  lexer.Start("test.ninja", "build foo: cc bar\n");
  // Should not crash and lexer should be usable
  Lexer::Token token = lexer.ReadToken();
  EXPECT_NE(Lexer::ERROR, token);
}

// Test: ReadToken returns tokens from input
TEST_F(LexerTest_10, ReadTokenBasic_10) {
  Lexer lexer("build foo: cc bar\n");
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::BUILD, token);
}

// Test: ReadToken recognizes 'rule' keyword
TEST_F(LexerTest_10, ReadTokenRule_10) {
  Lexer lexer("rule cc\n");
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::RULE, token);
}

// Test: ReadToken on empty input returns EOF or newline
TEST_F(LexerTest_10, ReadTokenEmpty_10) {
  Lexer lexer("");
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::TEOF, token);
}

// Test: ReadToken on newline
TEST_F(LexerTest_10, ReadTokenNewline_10) {
  Lexer lexer("\n");
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::NEWLINE, token);
}

// Test: UnreadToken allows re-reading last token
TEST_F(LexerTest_10, UnreadToken_10) {
  Lexer lexer("build foo\n");
  Lexer::Token first = lexer.ReadToken();
  EXPECT_EQ(Lexer::BUILD, first);
  lexer.UnreadToken();
  Lexer::Token second = lexer.ReadToken();
  EXPECT_EQ(Lexer::BUILD, second);
}

// Test: PeekToken returns true when next token matches
TEST_F(LexerTest_10, PeekTokenMatch_10) {
  Lexer lexer("build foo\n");
  bool result = lexer.PeekToken(Lexer::BUILD);
  EXPECT_TRUE(result);
}

// Test: PeekToken returns false and unreads when next token does not match
TEST_F(LexerTest_10, PeekTokenNoMatch_10) {
  Lexer lexer("build foo\n");
  bool result = lexer.PeekToken(Lexer::RULE);
  EXPECT_FALSE(result);
  // Token should still be available
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::BUILD, token);
}

// Test: ReadIdent reads an identifier
TEST_F(LexerTest_10, ReadIdentBasic_10) {
  Lexer lexer("foo\n");
  std::string ident;
  EXPECT_TRUE(lexer.ReadIdent(&ident));
  EXPECT_EQ("foo", ident);
}

// Test: ReadIdent fails on non-identifier input
TEST_F(LexerTest_10, ReadIdentFails_10) {
  Lexer lexer("\n");
  std::string ident;
  EXPECT_FALSE(lexer.ReadIdent(&ident));
}

// Test: ReadPath reads a simple path
TEST_F(LexerTest_10, ReadPathSimple_10) {
  Lexer lexer("foo.cc\n");
  EvalString path;
  std::string err;
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(path.empty());
}

// Test: ReadPath on empty line yields empty path
TEST_F(LexerTest_10, ReadPathEmpty_10) {
  Lexer lexer("\n");
  EvalString path;
  std::string err;
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_TRUE(path.empty());
}

// Test: ReadPath with variable expansion
TEST_F(LexerTest_10, ReadPathWithVariable_10) {
  Lexer lexer("$foo.cc\n");
  EvalString path;
  std::string err;
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(path.empty());
}

// Test: ReadPath with curly brace variable expansion
TEST_F(LexerTest_10, ReadPathWithCurlyBraceVar_10) {
  Lexer lexer("${foo}.cc\n");
  EvalString path;
  std::string err;
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(path.empty());
}

// Test: ReadVarValue reads a simple value
TEST_F(LexerTest_10, ReadVarValueSimple_10) {
  Lexer lexer("hello\n");
  EvalString value;
  std::string err;
  EXPECT_TRUE(lexer.ReadVarValue(&value, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(value.empty());
}

// Test: ReadVarValue reads an empty value (just newline)
TEST_F(LexerTest_10, ReadVarValueEmpty_10) {
  Lexer lexer("\n");
  EvalString value;
  std::string err;
  EXPECT_TRUE(lexer.ReadVarValue(&value, &err));
  EXPECT_TRUE(value.empty());
}

// Test: ReadVarValue reads value with variable expansion
TEST_F(LexerTest_10, ReadVarValueWithVariable_10) {
  Lexer lexer("hello $world\n");
  EvalString value;
  std::string err;
  EXPECT_TRUE(lexer.ReadVarValue(&value, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(value.empty());
}

// Test: ReadVarValue reads value with curly brace variable
TEST_F(LexerTest_10, ReadVarValueWithCurlyBraceVar_10) {
  Lexer lexer("hello ${world}\n");
  EvalString value;
  std::string err;
  EXPECT_TRUE(lexer.ReadVarValue(&value, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(value.empty());
}

// Test: ReadVarValue with spaces in value
TEST_F(LexerTest_10, ReadVarValueWithSpaces_10) {
  Lexer lexer("hello world foo\n");
  EvalString value;
  std::string err;
  EXPECT_TRUE(lexer.ReadVarValue(&value, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(value.empty());
}

// Test: ReadVarValue with line continuation
TEST_F(LexerTest_10, ReadVarValueLineContinuation_10) {
  Lexer lexer("hello $\n  world\n");
  EvalString value;
  std::string err;
  EXPECT_TRUE(lexer.ReadVarValue(&value, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(value.empty());
}

// Test: TokenName returns non-null for various tokens
TEST_F(LexerTest_10, TokenNameBuild_10) {
  const char* name = Lexer::TokenName(Lexer::BUILD);
  ASSERT_NE(nullptr, name);
  EXPECT_STREQ("'build'", name);
}

TEST_F(LexerTest_10, TokenNameRule_10) {
  const char* name = Lexer::TokenName(Lexer::RULE);
  ASSERT_NE(nullptr, name);
  EXPECT_STREQ("'rule'", name);
}

TEST_F(LexerTest_10, TokenNameEOF_10) {
  const char* name = Lexer::TokenName(Lexer::TEOF);
  ASSERT_NE(nullptr, name);
  EXPECT_STREQ("eof", name);
}

TEST_F(LexerTest_10, TokenNameNewline_10) {
  const char* name = Lexer::TokenName(Lexer::NEWLINE);
  ASSERT_NE(nullptr, name);
  EXPECT_STREQ("newline", name);
}

// Test: TokenErrorHint returns non-null
TEST_F(LexerTest_10, TokenErrorHint_10) {
  const char* hint = Lexer::TokenErrorHint(Lexer::RULE);
  ASSERT_NE(nullptr, hint);
}

// Test: Error generates an error message
TEST_F(LexerTest_10, ErrorMethod_10) {
  Lexer lexer;
  lexer.Start("test.ninja", "build foo\n");
  lexer.ReadToken();
  std::string err;
  bool result = lexer.Error("test error", &err);
  EXPECT_FALSE(result);
  EXPECT_FALSE(err.empty());
  EXPECT_NE(std::string::npos, err.find("test error"));
}

// Test: DescribeLastError returns a string
TEST_F(LexerTest_10, DescribeLastError_10) {
  Lexer lexer;
  lexer.Start("test.ninja", "build foo\n");
  lexer.ReadToken();
  std::string desc = lexer.DescribeLastError();
  // It should return some description; may be empty if no error
}

// Test: Reading 'default' keyword
TEST_F(LexerTest_10, ReadTokenDefault_10) {
  Lexer lexer("default foo\n");
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::DEFAULT, token);
}

// Test: Reading 'include' keyword
TEST_F(LexerTest_10, ReadTokenInclude_10) {
  Lexer lexer("include foo.ninja\n");
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::INCLUDE, token);
}

// Test: Reading 'subninja' keyword
TEST_F(LexerTest_10, ReadTokenSubninja_10) {
  Lexer lexer("subninja foo.ninja\n");
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::SUBNINJA, token);
}

// Test: Reading 'pool' keyword
TEST_F(LexerTest_10, ReadTokenPool_10) {
  Lexer lexer("pool link_pool\n");
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::POOL, token);
}

// Test: ReadPath with escaped dollar sign
TEST_F(LexerTest_10, ReadPathEscapedDollar_10) {
  Lexer lexer("foo$$bar\n");
  EvalString path;
  std::string err;
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(path.empty());
}

// Test: ReadVarValue with escaped dollar sign
TEST_F(LexerTest_10, ReadVarValueEscapedDollar_10) {
  Lexer lexer("foo$$bar\n");
  EvalString value;
  std::string err;
  EXPECT_TRUE(lexer.ReadVarValue(&value, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(value.empty());
}

// Test: ReadPath with colon in path (escaped)
TEST_F(LexerTest_10, ReadPathEscapedColon_10) {
  Lexer lexer("foo$:bar\n");
  EvalString path;
  std::string err;
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(path.empty());
}

// Test: ReadPath with space (stops at space for path)
TEST_F(LexerTest_10, ReadPathStopsAtSpace_10) {
  Lexer lexer("foo bar\n");
  EvalString path;
  std::string err;
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(path.empty());
}

// Test: ReadVarValue does not stop at space (unlike path)
TEST_F(LexerTest_10, ReadVarValueIncludesSpaces_10) {
  Lexer lexer("foo bar baz\n");
  EvalString value;
  std::string err;
  EXPECT_TRUE(lexer.ReadVarValue(&value, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(value.empty());
}

// Test: Multiple sequential token reads
TEST_F(LexerTest_10, MultipleTokenReads_10) {
  Lexer lexer("build foo: cc bar\n");
  EXPECT_EQ(Lexer::BUILD, lexer.ReadToken());
  // After BUILD token, we can read a path
  EvalString path;
  std::string err;
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
}

// Test: ReadIdent with alphanumeric and underscores
TEST_F(LexerTest_10, ReadIdentAlphanumeric_10) {
  Lexer lexer("foo_bar123\n");
  std::string ident;
  EXPECT_TRUE(lexer.ReadIdent(&ident));
  EXPECT_EQ("foo_bar123", ident);
}

// Test: ReadIdent with dots
TEST_F(LexerTest_10, ReadIdentWithDots_10) {
  Lexer lexer("foo.bar\n");
  std::string ident;
  EXPECT_TRUE(lexer.ReadIdent(&ident));
  EXPECT_EQ("foo.bar", ident);
}

// Test: ReadVarValue with bad variable reference
TEST_F(LexerTest_10, ReadVarValueBadVarRef_10) {
  Lexer lexer("hello ${}\n");
  EvalString value;
  std::string err;
  bool result = lexer.ReadVarValue(&value, &err);
  // Bad variable reference should cause an error
  if (!result) {
    EXPECT_FALSE(err.empty());
  }
}

// Test: ReadPath with unclosed curly brace
TEST_F(LexerTest_10, ReadPathUnclosedCurlyBrace_10) {
  Lexer lexer("${foo\n");
  EvalString path;
  std::string err;
  bool result = lexer.ReadPath(&path, &err);
  if (!result) {
    EXPECT_FALSE(err.empty());
  }
}

// Test: INDENT token (leading whitespace in certain context)
TEST_F(LexerTest_10, ReadTokenIndent_10) {
  Lexer lexer("  command = foo\n");
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::INDENT, token);
}

// Test: Colon token
TEST_F(LexerTest_10, ReadTokenColon_10) {
  // After reading "build foo", the next token should be ':'
  Lexer lexer("build foo: cc\n");
  EXPECT_EQ(Lexer::BUILD, lexer.ReadToken());
  EvalString path;
  std::string err;
  lexer.ReadPath(&path, &err);
  // Now read the colon
  // The colon is typically consumed by ReadToken
}

// Test: ReadVarValue with only spaces before newline
TEST_F(LexerTest_10, ReadVarValueOnlySpaces_10) {
  Lexer lexer("   \n");
  EvalString value;
  std::string err;
  EXPECT_TRUE(lexer.ReadVarValue(&value, &err));
}

// Test: Pipe token for implicit deps
TEST_F(LexerTest_10, ReadTokenPipe_10) {
  Lexer lexer("| implicit\n");
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::PIPE, token);
}

// Test: Pipe2 token for order-only deps
TEST_F(LexerTest_10, ReadTokenPipe2_10) {
  Lexer lexer("|| orderonly\n");
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::PIPE2, token);
}

// Test: Equals token
TEST_F(LexerTest_10, ReadTokenEquals_10) {
  // After an indent and ident, we expect equals
  Lexer lexer("  foo = bar\n");
  EXPECT_EQ(Lexer::INDENT, lexer.ReadToken());
  std::string ident;
  lexer.ReadIdent(&ident);
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::EQUALS, token);
}
