#include "gtest/gtest.h"
#include <sstream>
#include <string>

// Include necessary headers for the Scanner class
#include "scanner.h"
#include "token.h"

namespace YAML {

class ScannerTest_156 : public ::testing::Test {
 protected:
  // Helper to create a scanner from a string
  std::unique_ptr<Scanner> CreateScanner(const std::string& input) {
    streams_.emplace_back(std::make_unique<std::istringstream>(input));
    return std::make_unique<Scanner>(*streams_.back());
  }

  std::vector<std::unique_ptr<std::istringstream>> streams_;
};

// Test that an empty input stream results in the scanner being empty after consuming all tokens
TEST_F(ScannerTest_156, EmptyInputBecomesEmpty_156) {
  auto scanner = CreateScanner("");
  // Consume all tokens
  while (!scanner->empty()) {
    scanner->pop();
  }
  EXPECT_TRUE(scanner->empty());
}

// Test that mark() returns a valid initial mark for an empty stream
TEST_F(ScannerTest_156, MarkOnEmptyStream_156) {
  auto scanner = CreateScanner("");
  Mark m = scanner->mark();
  EXPECT_GE(m.line, 0);
  EXPECT_GE(m.column, 0);
}

// Test that mark() returns initial position at start
TEST_F(ScannerTest_156, MarkAtStart_156) {
  auto scanner = CreateScanner("key: value");
  Mark m = scanner->mark();
  EXPECT_EQ(m.line, 0);
  EXPECT_EQ(m.column, 0);
}

// Test that the scanner is not empty for non-empty input
TEST_F(ScannerTest_156, NonEmptyInputNotEmpty_156) {
  auto scanner = CreateScanner("key: value");
  EXPECT_FALSE(scanner->empty());
}

// Test that peek() returns a token without consuming it
TEST_F(ScannerTest_156, PeekDoesNotConsume_156) {
  auto scanner = CreateScanner("key: value");
  ASSERT_FALSE(scanner->empty());
  Token& tok1 = scanner->peek();
  Token& tok2 = scanner->peek();
  // Peeking twice should return the same token type
  EXPECT_EQ(tok1.type, tok2.type);
}

// Test that pop() advances to the next token
TEST_F(ScannerTest_156, PopAdvancesToken_156) {
  auto scanner = CreateScanner("key: value");
  ASSERT_FALSE(scanner->empty());
  Token::TYPE firstType = scanner->peek().type;
  scanner->pop();
  // After popping, scanner might still have tokens or be different
  if (!scanner->empty()) {
    // The next token could be different or same, but we just verify pop doesn't crash
    scanner->peek();
  }
}

// Test that the first token from a YAML stream is STREAM_START
TEST_F(ScannerTest_156, FirstTokenIsStreamStart_156) {
  auto scanner = CreateScanner("hello");
  ASSERT_FALSE(scanner->empty());
  Token& tok = scanner->peek();
  EXPECT_EQ(tok.type, Token::STREAM_START);
}

// Test that the last token from a YAML stream is STREAM_END
TEST_F(ScannerTest_156, LastTokenIsStreamEnd_156) {
  auto scanner = CreateScanner("");
  Token::TYPE lastType = Token::STREAM_START;
  while (!scanner->empty()) {
    lastType = scanner->peek().type;
    scanner->pop();
  }
  EXPECT_EQ(lastType, Token::STREAM_END);
}

// Test scanning a simple key-value pair produces expected token sequence
TEST_F(ScannerTest_156, SimpleKeyValueTokenSequence_156) {
  auto scanner = CreateScanner("key: value");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  // Expected: STREAM_START, BLOCK_MAP_START, KEY, SCALAR, VALUE, SCALAR, BLOCK_END, STREAM_END
  ASSERT_GE(types.size(), 2u);
  EXPECT_EQ(types.front(), Token::STREAM_START);
  EXPECT_EQ(types.back(), Token::STREAM_END);
}

// Test scanning a sequence
TEST_F(ScannerTest_156, SequenceTokens_156) {
  auto scanner = CreateScanner("- item1\n- item2");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  ASSERT_GE(types.size(), 2u);
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
TEST_F(ScannerTest_156, FlowSequenceTokens_156) {
  auto scanner = CreateScanner("[a, b, c]");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  ASSERT_GE(types.size(), 2u);
  EXPECT_EQ(types.front(), Token::STREAM_START);
  EXPECT_EQ(types.back(), Token::STREAM_END);
  // Should contain FLOW_SEQ_START and FLOW_SEQ_END
  bool hasFlowSeqStart = false;
  bool hasFlowSeqEnd = false;
  for (auto t : types) {
    if (t == Token::FLOW_SEQ_START) hasFlowSeqStart = true;
    if (t == Token::FLOW_SEQ_END) hasFlowSeqEnd = true;
  }
  EXPECT_TRUE(hasFlowSeqStart);
  EXPECT_TRUE(hasFlowSeqEnd);
}

// Test scanning a flow mapping
TEST_F(ScannerTest_156, FlowMappingTokens_156) {
  auto scanner = CreateScanner("{a: b, c: d}");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  bool hasFlowMapStart = false;
  bool hasFlowMapEnd = false;
  for (auto t : types) {
    if (t == Token::FLOW_MAP_START) hasFlowMapStart = true;
    if (t == Token::FLOW_MAP_END) hasFlowMapEnd = true;
  }
  EXPECT_TRUE(hasFlowMapStart);
  EXPECT_TRUE(hasFlowMapEnd);
}

// Test scanning a quoted scalar
TEST_F(ScannerTest_156, QuotedScalarToken_156) {
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

// Test scanning a single-quoted scalar
TEST_F(ScannerTest_156, SingleQuotedScalarToken_156) {
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

// Test scanning a document start marker
TEST_F(ScannerTest_156, DocumentStartToken_156) {
  auto scanner = CreateScanner("---\nkey: value");
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

// Test scanning a document end marker
TEST_F(ScannerTest_156, DocumentEndToken_156) {
  auto scanner = CreateScanner("---\nkey: value\n...");
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

// Test scanning an anchor
TEST_F(ScannerTest_156, AnchorToken_156) {
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
TEST_F(ScannerTest_156, AliasToken_156) {
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
TEST_F(ScannerTest_156, TagToken_156) {
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

// Test scanning a directive
TEST_F(ScannerTest_156, DirectiveToken_156) {
  auto scanner = CreateScanner("%YAML 1.2\n---\nvalue");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  bool hasDirective = false;
  for (auto t : types) {
    if (t == Token::DIRECTIVE) hasDirective = true;
  }
  EXPECT_TRUE(hasDirective);
}

// Test scanning a block scalar (literal)
TEST_F(ScannerTest_156, BlockLiteralScalar_156) {
  auto scanner = CreateScanner("|\n  line1\n  line2");
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

// Test scanning a block scalar (folded)
TEST_F(ScannerTest_156, BlockFoldedScalar_156) {
  auto scanner = CreateScanner(">\n  line1\n  line2");
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

// Test scanning only whitespace
TEST_F(ScannerTest_156, WhitespaceOnlyInput_156) {
  auto scanner = CreateScanner("   \n  \n  ");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  ASSERT_GE(types.size(), 2u);
  EXPECT_EQ(types.front(), Token::STREAM_START);
  EXPECT_EQ(types.back(), Token::STREAM_END);
}

// Test scanning a comment-only input
TEST_F(ScannerTest_156, CommentOnlyInput_156) {
  auto scanner = CreateScanner("# this is a comment");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  ASSERT_GE(types.size(), 2u);
  EXPECT_EQ(types.front(), Token::STREAM_START);
  EXPECT_EQ(types.back(), Token::STREAM_END);
}

// Test that mark advances as tokens are consumed
TEST_F(ScannerTest_156, MarkAdvancesWithPop_156) {
  auto scanner = CreateScanner("key: value\nother: data");
  Mark initial = scanner->mark();
  // Consume some tokens
  if (!scanner->empty()) {
    scanner->pop(); // STREAM_START
  }
  if (!scanner->empty()) {
    scanner->pop(); // BLOCK_MAP_START
  }
  if (!scanner->empty()) {
    scanner->pop(); // KEY
  }
  // Mark might have advanced
  // We just check it doesn't crash and returns valid mark
  Mark after = scanner->mark();
  EXPECT_GE(after.line, 0);
  EXPECT_GE(after.column, 0);
}

// Test scanning nested mapping
TEST_F(ScannerTest_156, NestedMapping_156) {
  auto scanner = CreateScanner("outer:\n  inner: value");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  // Should have KEY tokens for both outer and inner
  int keyCount = 0;
  for (auto t : types) {
    if (t == Token::KEY) keyCount++;
  }
  EXPECT_GE(keyCount, 2);
}

// Test scanning multiple documents
TEST_F(ScannerTest_156, MultipleDocuments_156) {
  auto scanner = CreateScanner("---\nfirst\n---\nsecond");
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

// Test scanning a scalar token value
TEST_F(ScannerTest_156, ScalarTokenValue_156) {
  auto scanner = CreateScanner("hello");
  std::string scalarValue;
  while (!scanner->empty()) {
    Token& tok = scanner->peek();
    if (tok.type == Token::SCALAR) {
      scalarValue = tok.value;
    }
    scanner->pop();
  }
  EXPECT_EQ(scalarValue, "hello");
}

// Test scanning key-value pair scalar values
TEST_F(ScannerTest_156, KeyValueScalarValues_156) {
  auto scanner = CreateScanner("mykey: myvalue");
  std::vector<std::string> scalars;
  while (!scanner->empty()) {
    Token& tok = scanner->peek();
    if (tok.type == Token::SCALAR) {
      scalars.push_back(tok.value);
    }
    scanner->pop();
  }
  ASSERT_EQ(scalars.size(), 2u);
  EXPECT_EQ(scalars[0], "mykey");
  EXPECT_EQ(scalars[1], "myvalue");
}

// Test that empty() returns true after consuming all tokens
TEST_F(ScannerTest_156, EmptyAfterAllConsumed_156) {
  auto scanner = CreateScanner("simple");
  while (!scanner->empty()) {
    scanner->pop();
  }
  EXPECT_TRUE(scanner->empty());
}

// Test scanning flow entry with commas
TEST_F(ScannerTest_156, FlowEntryTokens_156) {
  auto scanner = CreateScanner("[a, b]");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  bool hasFlowEntry = false;
  for (auto t : types) {
    if (t == Token::FLOW_ENTRY) hasFlowEntry = true;
  }
  EXPECT_TRUE(hasFlowEntry);
}

}  // namespace YAML
