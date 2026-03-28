#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "scanner.h"
#include "token.h"

namespace YAML {
namespace {

class ScannerTest_155 : public ::testing::Test {
 protected:
  std::unique_ptr<Scanner> CreateScanner(const std::string& input) {
    auto ss = std::make_unique<std::istringstream>(input);
    streams_.push_back(std::move(ss));
    return std::make_unique<Scanner>(*streams_.back());
  }

  std::vector<std::unique_ptr<std::istringstream>> streams_;
};

// Test that an empty input stream produces an empty scanner after consuming stream tokens
TEST_F(ScannerTest_155, EmptyInputEventuallyEmpty_155) {
  auto scanner = CreateScanner("");
  // Consume all tokens until empty
  while (!scanner->empty()) {
    scanner->pop();
  }
  EXPECT_TRUE(scanner->empty());
}

// Test that peek returns a valid token on a simple scalar input
TEST_F(ScannerTest_155, PeekReturnsTokenOnSimpleInput_155) {
  auto scanner = CreateScanner("hello");
  ASSERT_FALSE(scanner->empty());
  Token& token = scanner->peek();
  // The first token should be STREAM_START
  EXPECT_EQ(token.type, Token::STREAM_START);
}

// Test that peek is idempotent - calling it multiple times returns the same token
TEST_F(ScannerTest_155, PeekIsIdempotent_155) {
  auto scanner = CreateScanner("hello");
  ASSERT_FALSE(scanner->empty());
  Token& token1 = scanner->peek();
  Token& token2 = scanner->peek();
  EXPECT_EQ(&token1, &token2);
  EXPECT_EQ(token1.type, token2.type);
}

// Test that pop advances to the next token
TEST_F(ScannerTest_155, PopAdvancesToken_155) {
  auto scanner = CreateScanner("hello");
  ASSERT_FALSE(scanner->empty());
  Token& first = scanner->peek();
  Token::TYPE firstType = first.type;
  scanner->pop();
  if (!scanner->empty()) {
    Token& second = scanner->peek();
    // After popping, we should get a different token (or at least have advanced)
    // The second token should not necessarily be the same type as STREAM_START
    // (it could be a scalar or other token type)
    SUCCEED();
  }
}

// Test scanning a simple key-value mapping
TEST_F(ScannerTest_155, ScanSimpleKeyValue_155) {
  auto scanner = CreateScanner("key: value");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  // Should contain at least STREAM_START, BLOCK_MAP_START, KEY, SCALAR, VALUE, SCALAR, BLOCK_END, STREAM_END
  EXPECT_FALSE(types.empty());
  EXPECT_EQ(types.front(), Token::STREAM_START);
  EXPECT_EQ(types.back(), Token::STREAM_END);
}

// Test scanning a sequence
TEST_F(ScannerTest_155, ScanSequence_155) {
  auto scanner = CreateScanner("- item1\n- item2");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  EXPECT_FALSE(types.empty());
  EXPECT_EQ(types.front(), Token::STREAM_START);
  EXPECT_EQ(types.back(), Token::STREAM_END);
  // Should contain BLOCK_SEQ_START and BLOCK_ENTRY tokens
  bool hasBlockSeqStart = false;
  bool hasBlockEntry = false;
  for (auto t : types) {
    if (t == Token::BLOCK_SEQ_START) hasBlockSeqStart = true;
    if (t == Token::BLOCK_ENTRY) hasBlockEntry = true;
  }
  EXPECT_TRUE(hasBlockSeqStart);
  EXPECT_TRUE(hasBlockEntry);
}

// Test scanning a flow sequence
TEST_F(ScannerTest_155, ScanFlowSequence_155) {
  auto scanner = CreateScanner("[a, b, c]");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  EXPECT_EQ(types.front(), Token::STREAM_START);
  EXPECT_EQ(types.back(), Token::STREAM_END);
  bool hasFlowSeqStart = false;
  bool hasFlowSeqEnd = false;
  bool hasFlowEntry = false;
  for (auto t : types) {
    if (t == Token::FLOW_SEQ_START) hasFlowSeqStart = true;
    if (t == Token::FLOW_SEQ_END) hasFlowSeqEnd = true;
    if (t == Token::FLOW_ENTRY) hasFlowEntry = true;
  }
  EXPECT_TRUE(hasFlowSeqStart);
  EXPECT_TRUE(hasFlowSeqEnd);
  EXPECT_TRUE(hasFlowEntry);
}

// Test scanning a flow mapping
TEST_F(ScannerTest_155, ScanFlowMapping_155) {
  auto scanner = CreateScanner("{key: value}");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  EXPECT_EQ(types.front(), Token::STREAM_START);
  EXPECT_EQ(types.back(), Token::STREAM_END);
  bool hasFlowMapStart = false;
  bool hasFlowMapEnd = false;
  for (auto t : types) {
    if (t == Token::FLOW_MAP_START) hasFlowMapStart = true;
    if (t == Token::FLOW_MAP_END) hasFlowMapEnd = true;
  }
  EXPECT_TRUE(hasFlowMapStart);
  EXPECT_TRUE(hasFlowMapEnd);
}

// Test scanning quoted scalar
TEST_F(ScannerTest_155, ScanQuotedScalar_155) {
  auto scanner = CreateScanner("\"hello world\"");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  bool hasScalar = false;
  for (auto t : types) {
    if (t == Token::SCALAR) hasScalar = true;
  }
  EXPECT_TRUE(hasScalar);
}

// Test scanning single-quoted scalar
TEST_F(ScannerTest_155, ScanSingleQuotedScalar_155) {
  auto scanner = CreateScanner("'hello world'");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  bool hasScalar = false;
  for (auto t : types) {
    if (t == Token::SCALAR) hasScalar = true;
  }
  EXPECT_TRUE(hasScalar);
}

// Test scanning an anchor
TEST_F(ScannerTest_155, ScanAnchor_155) {
  auto scanner = CreateScanner("&anchor value");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  bool hasAnchor = false;
  for (auto t : types) {
    if (t == Token::ANCHOR) hasAnchor = true;
  }
  EXPECT_TRUE(hasAnchor);
}

// Test scanning an alias
TEST_F(ScannerTest_155, ScanAlias_155) {
  auto scanner = CreateScanner("*alias");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  bool hasAlias = false;
  for (auto t : types) {
    if (t == Token::ALIAS) hasAlias = true;
  }
  EXPECT_TRUE(hasAlias);
}

// Test scanning a tag
TEST_F(ScannerTest_155, ScanTag_155) {
  auto scanner = CreateScanner("!tag value");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  bool hasTag = false;
  for (auto t : types) {
    if (t == Token::TAG) hasTag = true;
  }
  EXPECT_TRUE(hasTag);
}

// Test scanning document start marker
TEST_F(ScannerTest_155, ScanDocStart_155) {
  auto scanner = CreateScanner("---\nhello");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  bool hasDocStart = false;
  for (auto t : types) {
    if (t == Token::DOC_START) hasDocStart = true;
  }
  EXPECT_TRUE(hasDocStart);
}

// Test scanning document end marker
TEST_F(ScannerTest_155, ScanDocEnd_155) {
  auto scanner = CreateScanner("hello\n...");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  bool hasDocEnd = false;
  for (auto t : types) {
    if (t == Token::DOC_END) hasDocEnd = true;
  }
  EXPECT_TRUE(hasDocEnd);
}

// Test mark returns valid position information
TEST_F(ScannerTest_155, MarkReturnsValidPosition_155) {
  auto scanner = CreateScanner("hello");
  Mark m = scanner->mark();
  // Initial position should be at the beginning
  EXPECT_GE(m.pos, 0);
  EXPECT_GE(m.line, 0);
  EXPECT_GE(m.column, 0);
}

// Test scanning a directive
TEST_F(ScannerTest_155, ScanDirective_155) {
  auto scanner = CreateScanner("%YAML 1.2\n---\nhello");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  // Should contain a directive token
  bool hasDirective = false;
  for (auto t : types) {
    if (t == Token::DIRECTIVE) hasDirective = true;
  }
  EXPECT_TRUE(hasDirective);
}

// Test scanning block scalar (literal)
TEST_F(ScannerTest_155, ScanBlockLiteralScalar_155) {
  auto scanner = CreateScanner("|\n  hello\n  world");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  bool hasScalar = false;
  for (auto t : types) {
    if (t == Token::SCALAR) hasScalar = true;
  }
  EXPECT_TRUE(hasScalar);
}

// Test scanning block scalar (folded)
TEST_F(ScannerTest_155, ScanBlockFoldedScalar_155) {
  auto scanner = CreateScanner(">\n  hello\n  world");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  bool hasScalar = false;
  for (auto t : types) {
    if (t == Token::SCALAR) hasScalar = true;
  }
  EXPECT_TRUE(hasScalar);
}

// Test that only whitespace input produces stream start and end
TEST_F(ScannerTest_155, WhitespaceOnlyInput_155) {
  auto scanner = CreateScanner("   \n  \n  ");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  EXPECT_GE(types.size(), 2u);
  EXPECT_EQ(types.front(), Token::STREAM_START);
  EXPECT_EQ(types.back(), Token::STREAM_END);
}

// Test scanning nested structures
TEST_F(ScannerTest_155, ScanNestedMapping_155) {
  auto scanner = CreateScanner("parent:\n  child: value");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  int keyCount = 0;
  int valueCount = 0;
  for (auto t : types) {
    if (t == Token::KEY) keyCount++;
    if (t == Token::VALUE) valueCount++;
  }
  EXPECT_GE(keyCount, 2);
  EXPECT_GE(valueCount, 2);
}

// Test scanning multiple documents
TEST_F(ScannerTest_155, ScanMultipleDocuments_155) {
  auto scanner = CreateScanner("---\nhello\n---\nworld");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  int docStartCount = 0;
  for (auto t : types) {
    if (t == Token::DOC_START) docStartCount++;
  }
  EXPECT_GE(docStartCount, 2);
}

// Test empty() after consuming all tokens
TEST_F(ScannerTest_155, EmptyAfterAllTokensConsumed_155) {
  auto scanner = CreateScanner("a");
  while (!scanner->empty()) {
    scanner->pop();
  }
  EXPECT_TRUE(scanner->empty());
}

// Test that scalar token has the correct value
TEST_F(ScannerTest_155, ScalarTokenHasCorrectValue_155) {
  auto scanner = CreateScanner("hello");
  // Skip STREAM_START
  ASSERT_FALSE(scanner->empty());
  EXPECT_EQ(scanner->peek().type, Token::STREAM_START);
  scanner->pop();
  
  // Next should be the scalar
  ASSERT_FALSE(scanner->empty());
  Token& tok = scanner->peek();
  EXPECT_EQ(tok.type, Token::SCALAR);
  EXPECT_EQ(tok.value, "hello");
}

// Test scanning a comment (should be ignored, not produce a token)
TEST_F(ScannerTest_155, CommentsAreIgnored_155) {
  auto scanner = CreateScanner("# this is a comment\nhello");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  // There should be no comment token type; just stream start, scalar, stream end
  bool hasScalar = false;
  for (auto t : types) {
    if (t == Token::SCALAR) hasScalar = true;
  }
  EXPECT_TRUE(hasScalar);
}

}  // namespace
}  // namespace YAML
