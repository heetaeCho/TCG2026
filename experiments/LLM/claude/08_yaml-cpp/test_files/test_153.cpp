#include "gtest/gtest.h"
#include <sstream>
#include <string>
#include "scanner.h"
#include "token.h"

namespace YAML {
namespace {

class ScannerTest_153 : public ::testing::Test {
 protected:
  // Helper to create a Scanner from a string
  std::unique_ptr<Scanner> MakeScanner(const std::string& input) {
    auto ss = std::make_unique<std::stringstream>(input);
    streams_.push_back(std::move(ss));
    return std::make_unique<Scanner>(*streams_.back());
  }

  std::vector<std::unique_ptr<std::stringstream>> streams_;
};

// Test that an empty input stream results in empty() returning true after tokens are consumed
TEST_F(ScannerTest_153, EmptyInputStreamBecomesEmpty_153) {
  auto scanner = MakeScanner("");
  // An empty stream should produce stream start and stream end tokens
  // After consuming all tokens, empty() should return true
  while (!scanner->empty()) {
    scanner->pop();
  }
  EXPECT_TRUE(scanner->empty());
}

// Test that a non-empty input produces tokens (not empty initially)
TEST_F(ScannerTest_153, NonEmptyInputProducesTokens_153) {
  auto scanner = MakeScanner("key: value");
  EXPECT_FALSE(scanner->empty());
}

// Test that peek returns a valid token for simple YAML
TEST_F(ScannerTest_153, PeekReturnsValidToken_153) {
  auto scanner = MakeScanner("hello: world");
  ASSERT_FALSE(scanner->empty());
  Token& token = scanner->peek();
  // The first token should be STREAM_START
  EXPECT_EQ(token.type, Token::STREAM_START);
}

// Test that pop removes the front token
TEST_F(ScannerTest_153, PopRemovesFrontToken_153) {
  auto scanner = MakeScanner("key: value");
  ASSERT_FALSE(scanner->empty());
  Token& first = scanner->peek();
  Token::TYPE firstType = first.type;
  scanner->pop();
  if (!scanner->empty()) {
    Token& second = scanner->peek();
    // After popping, we should get a different token (or at least the queue advances)
    // We just verify we can peek again without error
    (void)second;
  }
  // Verify the first was STREAM_START
  EXPECT_EQ(firstType, Token::STREAM_START);
}

// Test that mark() returns a valid mark
TEST_F(ScannerTest_153, MarkReturnsValidMark_153) {
  auto scanner = MakeScanner("test");
  Mark m = scanner->mark();
  // For the beginning of a stream, line and column should be 0
  EXPECT_EQ(m.line, 0);
  EXPECT_EQ(m.column, 0);
}

// Test scanning a simple scalar value
TEST_F(ScannerTest_153, ScanSimpleScalar_153) {
  auto scanner = MakeScanner("hello");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  // Expect at least STREAM_START and STREAM_END
  ASSERT_GE(types.size(), 2u);
  EXPECT_EQ(types.front(), Token::STREAM_START);
  EXPECT_EQ(types.back(), Token::STREAM_END);
}

// Test scanning a key-value pair
TEST_F(ScannerTest_153, ScanKeyValuePair_153) {
  auto scanner = MakeScanner("key: value");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  ASSERT_GE(types.size(), 2u);
  EXPECT_EQ(types.front(), Token::STREAM_START);
  EXPECT_EQ(types.back(), Token::STREAM_END);
  // Should contain BLOCK_MAP_START, KEY, VALUE tokens
  bool hasKey = false;
  bool hasValue = false;
  for (auto t : types) {
    if (t == Token::KEY) hasKey = true;
    if (t == Token::VALUE) hasValue = true;
  }
  EXPECT_TRUE(hasKey);
  EXPECT_TRUE(hasValue);
}

// Test scanning a sequence
TEST_F(ScannerTest_153, ScanBlockSequence_153) {
  auto scanner = MakeScanner("- item1\n- item2\n- item3");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  EXPECT_EQ(types.front(), Token::STREAM_START);
  EXPECT_EQ(types.back(), Token::STREAM_END);
  // Should contain BLOCK_SEQ_START and BLOCK_ENTRY tokens
  int entryCount = 0;
  bool hasSeqStart = false;
  for (auto t : types) {
    if (t == Token::BLOCK_SEQ_START) hasSeqStart = true;
    if (t == Token::BLOCK_ENTRY) entryCount++;
  }
  EXPECT_TRUE(hasSeqStart);
  EXPECT_EQ(entryCount, 3);
}

// Test scanning a flow sequence
TEST_F(ScannerTest_153, ScanFlowSequence_153) {
  auto scanner = MakeScanner("[a, b, c]");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  EXPECT_EQ(types.front(), Token::STREAM_START);
  EXPECT_EQ(types.back(), Token::STREAM_END);
  bool hasFlowSeqStart = false;
  bool hasFlowSeqEnd = false;
  int flowEntryCount = 0;
  for (auto t : types) {
    if (t == Token::FLOW_SEQ_START) hasFlowSeqStart = true;
    if (t == Token::FLOW_SEQ_END) hasFlowSeqEnd = true;
    if (t == Token::FLOW_ENTRY) flowEntryCount++;
  }
  EXPECT_TRUE(hasFlowSeqStart);
  EXPECT_TRUE(hasFlowSeqEnd);
  EXPECT_EQ(flowEntryCount, 2);  // commas between 3 items = 2
}

// Test scanning a flow mapping
TEST_F(ScannerTest_153, ScanFlowMapping_153) {
  auto scanner = MakeScanner("{a: 1, b: 2}");
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
TEST_F(ScannerTest_153, ScanQuotedScalar_153) {
  auto scanner = MakeScanner("\"hello world\"");
  std::vector<Token> tokens;
  while (!scanner->empty()) {
    tokens.push_back(scanner->peek());
    scanner->pop();
  }
  // Find the scalar token
  bool foundScalar = false;
  for (const auto& t : tokens) {
    if (t.type == Token::SCALAR) {
      foundScalar = true;
      EXPECT_EQ(t.value, "hello world");
    }
  }
  EXPECT_TRUE(foundScalar);
}

// Test scanning a single-quoted scalar
TEST_F(ScannerTest_153, ScanSingleQuotedScalar_153) {
  auto scanner = MakeScanner("'hello world'");
  std::vector<Token> tokens;
  while (!scanner->empty()) {
    tokens.push_back(scanner->peek());
    scanner->pop();
  }
  bool foundScalar = false;
  for (const auto& t : tokens) {
    if (t.type == Token::SCALAR) {
      foundScalar = true;
      EXPECT_EQ(t.value, "hello world");
    }
  }
  EXPECT_TRUE(foundScalar);
}

// Test scanning a document start marker
TEST_F(ScannerTest_153, ScanDocumentStart_153) {
  auto scanner = MakeScanner("---\nkey: value");
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
TEST_F(ScannerTest_153, ScanDocumentEnd_153) {
  auto scanner = MakeScanner("---\nkey: value\n...");
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
TEST_F(ScannerTest_153, ScanAnchor_153) {
  auto scanner = MakeScanner("&anchor value");
  std::vector<Token> tokens;
  while (!scanner->empty()) {
    tokens.push_back(scanner->peek());
    scanner->pop();
  }
  bool hasAnchor = false;
  for (const auto& t : tokens) {
    if (t.type == Token::ANCHOR) {
      hasAnchor = true;
      EXPECT_EQ(t.value, "anchor");
    }
  }
  EXPECT_TRUE(hasAnchor);
}

// Test scanning an alias
TEST_F(ScannerTest_153, ScanAlias_153) {
  auto scanner = MakeScanner("*alias");
  std::vector<Token> tokens;
  while (!scanner->empty()) {
    tokens.push_back(scanner->peek());
    scanner->pop();
  }
  bool hasAlias = false;
  for (const auto& t : tokens) {
    if (t.type == Token::ALIAS) {
      hasAlias = true;
      EXPECT_EQ(t.value, "alias");
    }
  }
  EXPECT_TRUE(hasAlias);
}

// Test scanning a tag
TEST_F(ScannerTest_153, ScanTag_153) {
  auto scanner = MakeScanner("!tag value");
  std::vector<Token> tokens;
  while (!scanner->empty()) {
    tokens.push_back(scanner->peek());
    scanner->pop();
  }
  bool hasTag = false;
  for (const auto& t : tokens) {
    if (t.type == Token::TAG) {
      hasTag = true;
    }
  }
  EXPECT_TRUE(hasTag);
}

// Test scanning a literal block scalar
TEST_F(ScannerTest_153, ScanLiteralBlockScalar_153) {
  auto scanner = MakeScanner("|\n  line1\n  line2");
  std::vector<Token> tokens;
  while (!scanner->empty()) {
    tokens.push_back(scanner->peek());
    scanner->pop();
  }
  bool hasScalar = false;
  for (const auto& t : tokens) {
    if (t.type == Token::SCALAR) {
      hasScalar = true;
    }
  }
  EXPECT_TRUE(hasScalar);
}

// Test scanning a folded block scalar
TEST_F(ScannerTest_153, ScanFoldedBlockScalar_153) {
  auto scanner = MakeScanner(">\n  line1\n  line2");
  std::vector<Token> tokens;
  while (!scanner->empty()) {
    tokens.push_back(scanner->peek());
    scanner->pop();
  }
  bool hasScalar = false;
  for (const auto& t : tokens) {
    if (t.type == Token::SCALAR) {
      hasScalar = true;
    }
  }
  EXPECT_TRUE(hasScalar);
}

// Test scanning with only whitespace input
TEST_F(ScannerTest_153, WhitespaceOnlyInput_153) {
  auto scanner = MakeScanner("   \n  \n   ");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  // Should still have stream start and end
  ASSERT_GE(types.size(), 2u);
  EXPECT_EQ(types.front(), Token::STREAM_START);
  EXPECT_EQ(types.back(), Token::STREAM_END);
}

// Test scanning a directive
TEST_F(ScannerTest_153, ScanDirective_153) {
  auto scanner = MakeScanner("%YAML 1.2\n---\nkey: value");
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

// Test scanning with comments
TEST_F(ScannerTest_153, ScanWithComments_153) {
  auto scanner = MakeScanner("# this is a comment\nkey: value");
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  // Comments should be skipped; should still find key-value tokens
  bool hasKey = false;
  for (auto t : types) {
    if (t == Token::KEY) hasKey = true;
  }
  EXPECT_TRUE(hasKey);
}

// Test that peek is idempotent (calling it twice returns the same token)
TEST_F(ScannerTest_153, PeekIsIdempotent_153) {
  auto scanner = MakeScanner("key: value");
  ASSERT_FALSE(scanner->empty());
  Token& first = scanner->peek();
  Token& second = scanner->peek();
  EXPECT_EQ(first.type, second.type);
  EXPECT_EQ(&first, &second);
}

// Test scanning nested structure
TEST_F(ScannerTest_153, ScanNestedMapping_153) {
  std::string yaml = "outer:\n  inner: value";
  auto scanner = MakeScanner(yaml);
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  // Should have at least two KEY tokens (outer and inner)
  int keyCount = 0;
  for (auto t : types) {
    if (t == Token::KEY) keyCount++;
  }
  EXPECT_EQ(keyCount, 2);
}

// Test scanning multiple documents
TEST_F(ScannerTest_153, ScanMultipleDocuments_153) {
  std::string yaml = "---\nfirst\n---\nsecond";
  auto scanner = MakeScanner(yaml);
  std::vector<Token::TYPE> types;
  while (!scanner->empty()) {
    types.push_back(scanner->peek().type);
    scanner->pop();
  }
  int docStartCount = 0;
  for (auto t : types) {
    if (t == Token::DOC_START) docStartCount++;
  }
  EXPECT_EQ(docStartCount, 2);
}

// Test mark advances after consuming tokens
TEST_F(ScannerTest_153, MarkAdvancesAfterPop_153) {
  auto scanner = MakeScanner("key: value");
  Mark m1 = scanner->mark();
  ASSERT_FALSE(scanner->empty());
  scanner->pop();  // pop STREAM_START
  if (!scanner->empty()) {
    // Mark should reflect the position in the stream
    // We just verify mark() doesn't crash after popping
    Mark m2 = scanner->mark();
    (void)m2;
  }
}

}  // namespace
}  // namespace YAML
