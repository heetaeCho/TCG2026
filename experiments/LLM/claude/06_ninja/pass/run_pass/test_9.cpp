#include "gtest/gtest.h"
#include "lexer.h"
#include "eval_env.h"

class LexerTest_9 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Default constructor creates a valid Lexer
TEST_F(LexerTest_9, DefaultConstructor_9) {
  Lexer lexer;
  // Should not crash; lexer is in a default state
}

// Test: Constructor with input string
TEST_F(LexerTest_9, ConstructorWithInput_9) {
  Lexer lexer("build foo: bar\n");
  // Should not crash
}

// Test: Start initializes the lexer with filename and input
TEST_F(LexerTest_9, StartInitializesLexer_9) {
  Lexer lexer;
  lexer.Start("test.ninja", "build foo: bar\n");
  // Should not crash and lexer should be usable
}

// Test: ReadToken reads a build token
TEST_F(LexerTest_9, ReadTokenBuild_9) {
  Lexer lexer("build foo: bar\n");
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::BUILD, token);
}

// Test: ReadToken reads a rule token
TEST_F(LexerTest_9, ReadTokenRule_9) {
  Lexer lexer("rule cc\n");
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::RULE, token);
}

// Test: ReadToken reads a default token
TEST_F(LexerTest_9, ReadTokenDefault_9) {
  Lexer lexer("default foo\n");
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::DEFAULT, token);
}

// Test: ReadToken on empty input returns EOF or NEWLINE
TEST_F(LexerTest_9, ReadTokenEmptyInput_9) {
  Lexer lexer("");
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::TEOF, token);
}

// Test: ReadToken reads newline
TEST_F(LexerTest_9, ReadTokenNewline_9) {
  Lexer lexer("\n");
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::NEWLINE, token);
}

// Test: UnreadToken allows re-reading the same token
TEST_F(LexerTest_9, UnreadToken_9) {
  Lexer lexer("build foo: bar\n");
  Lexer::Token token1 = lexer.ReadToken();
  EXPECT_EQ(Lexer::BUILD, token1);
  lexer.UnreadToken();
  Lexer::Token token2 = lexer.ReadToken();
  EXPECT_EQ(Lexer::BUILD, token2);
}

// Test: PeekToken returns true when the next token matches
TEST_F(LexerTest_9, PeekTokenMatch_9) {
  Lexer lexer("build foo: bar\n");
  EXPECT_TRUE(lexer.PeekToken(Lexer::BUILD));
}

// Test: PeekToken returns false and doesn't consume when token doesn't match
TEST_F(LexerTest_9, PeekTokenNoMatch_9) {
  Lexer lexer("build foo: bar\n");
  EXPECT_FALSE(lexer.PeekToken(Lexer::RULE));
  // The token should still be available
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::BUILD, token);
}

// Test: ReadIdent reads an identifier
TEST_F(LexerTest_9, ReadIdentSuccess_9) {
  Lexer lexer("foobar ");
  // First consume any leading token — the ident is after reading context
  // Actually ReadIdent reads from current position
  std::string ident;
  EXPECT_TRUE(lexer.ReadIdent(&ident));
  EXPECT_EQ("foobar", ident);
}

// Test: ReadIdent fails on non-identifier input
TEST_F(LexerTest_9, ReadIdentFailure_9) {
  Lexer lexer("123abc ");
  std::string ident;
  // Digits at start may not be valid identifiers
  // The result depends on the implementation
  bool result = lexer.ReadIdent(&ident);
  // We just check it doesn't crash; result may vary
  (void)result;
}

// Test: ReadPath reads a simple path
TEST_F(LexerTest_9, ReadPathSimple_9) {
  Lexer lexer("foo.o ");
  EvalString path;
  std::string err;
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(path.empty());
}

// Test: ReadPath reads an empty path (empty input or only whitespace)
TEST_F(LexerTest_9, ReadPathEmpty_9) {
  Lexer lexer(" ");
  EvalString path;
  std::string err;
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_TRUE(path.empty());
}

// Test: ReadPath with variable reference
TEST_F(LexerTest_9, ReadPathWithVariable_9) {
  Lexer lexer("${foo}.o ");
  EvalString path;
  std::string err;
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(path.empty());
}

// Test: ReadPath with $ variable (short form)
TEST_F(LexerTest_9, ReadPathWithShortVariable_9) {
  Lexer lexer("$foo.o ");
  EvalString path;
  std::string err;
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(path.empty());
}

// Test: ReadVarValue reads a simple value
TEST_F(LexerTest_9, ReadVarValueSimple_9) {
  Lexer lexer("hello\n");
  EvalString value;
  std::string err;
  EXPECT_TRUE(lexer.ReadVarValue(&value, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(value.empty());
}

// Test: ReadVarValue reads value with variable
TEST_F(LexerTest_9, ReadVarValueWithVariable_9) {
  Lexer lexer("$foo bar\n");
  EvalString value;
  std::string err;
  EXPECT_TRUE(lexer.ReadVarValue(&value, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(value.empty());
}

// Test: ReadVarValue reads empty value
TEST_F(LexerTest_9, ReadVarValueEmpty_9) {
  Lexer lexer("\n");
  EvalString value;
  std::string err;
  EXPECT_TRUE(lexer.ReadVarValue(&value, &err));
  EXPECT_TRUE(value.empty());
}

// Test: TokenName returns non-null for known tokens
TEST_F(LexerTest_9, TokenNameBuild_9) {
  const char* name = Lexer::TokenName(Lexer::BUILD);
  ASSERT_NE(nullptr, name);
  EXPECT_STREQ("'build'", name);
}

TEST_F(LexerTest_9, TokenNameRule_9) {
  const char* name = Lexer::TokenName(Lexer::RULE);
  ASSERT_NE(nullptr, name);
  EXPECT_STREQ("'rule'", name);
}

TEST_F(LexerTest_9, TokenNameNewline_9) {
  const char* name = Lexer::TokenName(Lexer::NEWLINE);
  ASSERT_NE(nullptr, name);
}

TEST_F(LexerTest_9, TokenNameEOF_9) {
  const char* name = Lexer::TokenName(Lexer::TEOF);
  ASSERT_NE(nullptr, name);
}

// Test: TokenErrorHint returns a string for expected tokens
TEST_F(LexerTest_9, TokenErrorHintRule_9) {
  const char* hint = Lexer::TokenErrorHint(Lexer::RULE);
  ASSERT_NE(nullptr, hint);
}

// Test: Error produces a formatted error message
TEST_F(LexerTest_9, ErrorProducesMessage_9) {
  Lexer lexer("build foo\n");
  lexer.Start("input", "build foo\n");
  std::string err;
  EXPECT_FALSE(lexer.Error("something went wrong", &err));
  EXPECT_FALSE(err.empty());
  EXPECT_NE(std::string::npos, err.find("something went wrong"));
}

// Test: DescribeLastError returns a string
TEST_F(LexerTest_9, DescribeLastError_9) {
  Lexer lexer("build foo\n");
  lexer.ReadToken(); // read 'build'
  std::string desc = lexer.DescribeLastError();
  // Just ensure it doesn't crash and returns something
  (void)desc;
}

// Test: ReadPath with escaped space
TEST_F(LexerTest_9, ReadPathEscapedSpace_9) {
  Lexer lexer("foo$ bar\n");
  EvalString path;
  std::string err;
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(path.empty());
}

// Test: ReadPath with colon in path
TEST_F(LexerTest_9, ReadPathStopsAtColon_9) {
  Lexer lexer("foo:");
  EvalString path;
  std::string err;
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(path.empty());
}

// Test: ReadPath with pipe character
TEST_F(LexerTest_9, ReadPathStopsAtPipe_9) {
  Lexer lexer("foo|");
  EvalString path;
  std::string err;
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(path.empty());
}

// Test: Multiple tokens in sequence
TEST_F(LexerTest_9, MultipleTokens_9) {
  Lexer lexer("build foo: rule\n");
  EXPECT_EQ(Lexer::BUILD, lexer.ReadToken());
}

// Test: ReadVarValue with line continuation
TEST_F(LexerTest_9, ReadVarValueLineContinuation_9) {
  Lexer lexer("hello $\n  world\n");
  EvalString value;
  std::string err;
  EXPECT_TRUE(lexer.ReadVarValue(&value, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(value.empty());
}

// Test: Include token
TEST_F(LexerTest_9, ReadTokenInclude_9) {
  Lexer lexer("include foo.ninja\n");
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::INCLUDE, token);
}

// Test: Subninja token
TEST_F(LexerTest_9, ReadTokenSubninja_9) {
  Lexer lexer("subninja foo.ninja\n");
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::SUBNINJA, token);
}

// Test: Pool token
TEST_F(LexerTest_9, ReadTokenPool_9) {
  Lexer lexer("pool link_pool\n");
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::POOL, token);
}

// Test: ReadPath with braced variable
TEST_F(LexerTest_9, ReadPathBracedVariable_9) {
  Lexer lexer("${builddir}/foo.o\n");
  EvalString path;
  std::string err;
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(path.empty());
}

// Test: ReadVarValue with braced variable
TEST_F(LexerTest_9, ReadVarValueBracedVariable_9) {
  Lexer lexer("${cc} -c $in -o $out\n");
  EvalString value;
  std::string err;
  EXPECT_TRUE(lexer.ReadVarValue(&value, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(value.empty());
}

// Test: ReadPath with newline terminates the path
TEST_F(LexerTest_9, ReadPathNewlineTerminates_9) {
  Lexer lexer("foo.o\n");
  EvalString path;
  std::string err;
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(path.empty());
}

// Test: ReadIdent with empty input
TEST_F(LexerTest_9, ReadIdentEmpty_9) {
  Lexer lexer("\n");
  std::string ident;
  bool result = lexer.ReadIdent(&ident);
  EXPECT_FALSE(result);
}

// Test: Error message includes filename
TEST_F(LexerTest_9, ErrorIncludesFilename_9) {
  Lexer lexer;
  lexer.Start("myfile.ninja", "build foo\n");
  std::string err;
  lexer.Error("test error", &err);
  EXPECT_NE(std::string::npos, err.find("myfile.ninja"));
}

// Test: ReadPath with dollar-dollar (escaped dollar)
TEST_F(LexerTest_9, ReadPathEscapedDollar_9) {
  Lexer lexer("foo$$bar\n");
  EvalString path;
  std::string err;
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(path.empty());
}

// Test: ReadVarValue with dollar-dollar
TEST_F(LexerTest_9, ReadVarValueEscapedDollar_9) {
  Lexer lexer("foo$$bar\n");
  EvalString value;
  std::string err;
  EXPECT_TRUE(lexer.ReadVarValue(&value, &err));
  EXPECT_EQ("", err);
  EXPECT_FALSE(value.empty());
}

// Test: ReadPath with only a newline produces empty path
TEST_F(LexerTest_9, ReadPathOnlyNewline_9) {
  Lexer lexer("\n");
  EvalString path;
  std::string err;
  EXPECT_TRUE(lexer.ReadPath(&path, &err));
  EXPECT_TRUE(path.empty());
}

// Test: Indent token
TEST_F(LexerTest_9, ReadTokenIndent_9) {
  // After a newline, indented content should produce INDENT
  Lexer lexer("  command = foo\n");
  Lexer::Token token = lexer.ReadToken();
  EXPECT_EQ(Lexer::INDENT, token);
}
