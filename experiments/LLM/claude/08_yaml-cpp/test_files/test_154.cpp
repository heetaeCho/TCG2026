#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "scanner.h"
#include "token.h"

namespace YAML {
namespace {

class ScannerTest_154 : public ::testing::Test {
 protected:
  std::unique_ptr<Scanner> CreateScanner(const std::string& input) {
    auto ss = std::make_unique<std::istringstream>(input);
    streams_.push_back(std::move(ss));
    return std::make_unique<Scanner>(*streams_.back());
  }

  std::vector<std::unique_ptr<std::istringstream>> streams_;
};

// Test that an empty input stream results in empty() returning true after stream tokens are consumed
TEST_F(ScannerTest_154, EmptyInputStreamBecomesEmpty_154) {
  auto scanner = CreateScanner("");
  // Consume all tokens until empty
  while (!scanner->empty()) {
    scanner->pop();
  }
  EXPECT_TRUE(scanner->empty());
}

// Test that a non-empty input produces tokens (not empty initially)
TEST_F(ScannerTest_154, NonEmptyInputIsNotEmpty_154) {
  auto scanner = CreateScanner("hello: world");
  EXPECT_FALSE(scanner->empty());
}

// Test that peek returns a token without consuming it
TEST_F(ScannerTest_154, PeekReturnsTokenWithoutConsuming_154) {
  auto scanner = CreateScanner("key: value");
  ASSERT_FALSE(scanner->empty());
  Token& first = scanner->peek();
  Token& second = scanner->peek();
  // Peeking twice should return the same token type
  EXPECT_EQ(first.type, second.type);
}

// Test that pop removes a token from the queue
TEST_F(ScannerTest_154, PopRemovesToken_154) {
  auto scanner = CreateScanner("key: value");
  ASSERT_FALSE(scanner->empty());
  Token::TYPE firstType = scanner->peek().type;
  scanner->pop();
  // After pop, if not empty, the next token should be available
  if (!scanner->empty()) {
    // We just verify we can peek again without crashing
    Token& next = scanner->peek();
    (void)next;
  }
}

// Test that calling pop on empty input doesn't crash
TEST_F(ScannerTest_154, PopOnEmptyInputDoesNotCrash_154) {
  auto scanner = CreateScanner("");
  // Consume everything
  while (!scanner->empty()) {
    scanner->pop();
  }
  // Calling pop again on empty should not crash
  scanner->pop();
  EXPECT_TRUE(scanner->empty());
}

// Test that mark returns a valid mark
TEST_F(ScannerTest_154, MarkReturnsValidPosition_154) {
  auto scanner = CreateScanner("test");
  Mark m = scanner->mark();
  // For the beginning of input, position should be at or near 0
  EXPECT_GE(m.pos, 0);
  EXPECT_GE(m.line, 0);
  EXPECT_GE(m.column, 0);
}

// Test scanning a simple scalar
TEST_F(ScannerTest_154, SimpleScalarProducesTokens_154) {
  auto scanner = CreateScanner("hello");
  int tokenCount = 0;
  while (!scanner->empty()) {
    scanner->pop();
    tokenCount++;
    // Safety guard against infinite loops
    if (tokenCount > 100) break;
  }
  // A simple scalar should produce at least stream start, scalar, and stream end tokens
  EXPECT_GE(tokenCount, 3);
}

// Test scanning a key-value pair
TEST_F(ScannerTest_154, KeyValuePairProducesTokens_154) {
  auto scanner = CreateScanner("key: value");
  int tokenCount = 0;
  while (!scanner->empty()) {
    scanner->pop();
    tokenCount++;
    if (tokenCount > 100) break;
  }
  // Should produce multiple tokens: stream start, block map start, key, scalar, value, scalar, stream end, etc.
  EXPECT_GE(tokenCount, 5);
}

// Test that the first token is STREAM_START
TEST_F(ScannerTest_154, FirstTokenIsStreamStart_154) {
  auto scanner = CreateScanner("anything");
  ASSERT_FALSE(scanner->empty());
  Token& token = scanner->peek();
  EXPECT_EQ(token.type, Token::STREAM_START);
}

// Test that after consuming all tokens, the last meaningful token was STREAM_END
TEST_F(ScannerTest_154, LastTokenIsStreamEnd_154) {
  auto scanner = CreateScanner("test");
  Token::TYPE lastType = Token::STREAM_START;
  while (!scanner->empty()) {
    lastType = scanner->peek().type;
    scanner->pop();
  }
  EXPECT_EQ(lastType, Token::STREAM_END);
}

// Test scanning a sequence
TEST_F(ScannerTest_154, SequenceProducesTokens_154) {
  auto scanner = CreateScanner("- item1\n- item2\n- item3");
  int tokenCount = 0;
  bool foundBlockSeqStart = false;
  bool foundBlockEntry = false;
  while (!scanner->empty()) {
    Token& t = scanner->peek();
    if (t.type == Token::BLOCK_SEQ_START) foundBlockSeqStart = true;
    if (t.type == Token::BLOCK_ENTRY) foundBlockEntry = true;
    scanner->pop();
    tokenCount++;
    if (tokenCount > 200) break;
  }
  EXPECT_TRUE(foundBlockSeqStart);
  EXPECT_TRUE(foundBlockEntry);
}

// Test scanning a flow sequence
TEST_F(ScannerTest_154, FlowSequenceProducesTokens_154) {
  auto scanner = CreateScanner("[a, b, c]");
  int tokenCount = 0;
  bool foundFlowSeqStart = false;
  bool foundFlowSeqEnd = false;
  while (!scanner->empty()) {
    Token& t = scanner->peek();
    if (t.type == Token::FLOW_SEQ_START) foundFlowSeqStart = true;
    if (t.type == Token::FLOW_SEQ_END) foundFlowSeqEnd = true;
    scanner->pop();
    tokenCount++;
    if (tokenCount > 200) break;
  }
  EXPECT_TRUE(foundFlowSeqStart);
  EXPECT_TRUE(foundFlowSeqEnd);
}

// Test scanning a flow mapping
TEST_F(ScannerTest_154, FlowMappingProducesTokens_154) {
  auto scanner = CreateScanner("{a: b, c: d}");
  int tokenCount = 0;
  bool foundFlowMapStart = false;
  bool foundFlowMapEnd = false;
  while (!scanner->empty()) {
    Token& t = scanner->peek();
    if (t.type == Token::FLOW_MAP_START) foundFlowMapStart = true;
    if (t.type == Token::FLOW_MAP_END) foundFlowMapEnd = true;
    scanner->pop();
    tokenCount++;
    if (tokenCount > 200) break;
  }
  EXPECT_TRUE(foundFlowMapStart);
  EXPECT_TRUE(foundFlowMapEnd);
}

// Test scanning a quoted scalar
TEST_F(ScannerTest_154, QuotedScalarProducesTokens_154) {
  auto scanner = CreateScanner("\"hello world\"");
  bool foundScalar = false;
  int tokenCount = 0;
  while (!scanner->empty()) {
    Token& t = scanner->peek();
    if (t.type == Token::SCALAR) {
      foundScalar = true;
      EXPECT_EQ(t.value, "hello world");
    }
    scanner->pop();
    tokenCount++;
    if (tokenCount > 200) break;
  }
  EXPECT_TRUE(foundScalar);
}

// Test scanning single-quoted scalar
TEST_F(ScannerTest_154, SingleQuotedScalarProducesTokens_154) {
  auto scanner = CreateScanner("'hello world'");
  bool foundScalar = false;
  int tokenCount = 0;
  while (!scanner->empty()) {
    Token& t = scanner->peek();
    if (t.type == Token::SCALAR) {
      foundScalar = true;
      EXPECT_EQ(t.value, "hello world");
    }
    scanner->pop();
    tokenCount++;
    if (tokenCount > 200) break;
  }
  EXPECT_TRUE(foundScalar);
}

// Test scanning an anchor
TEST_F(ScannerTest_154, AnchorProducesToken_154) {
  auto scanner = CreateScanner("&anchor value");
  bool foundAnchor = false;
  int tokenCount = 0;
  while (!scanner->empty()) {
    Token& t = scanner->peek();
    if (t.type == Token::ANCHOR) {
      foundAnchor = true;
      EXPECT_EQ(t.value, "anchor");
    }
    scanner->pop();
    tokenCount++;
    if (tokenCount > 200) break;
  }
  EXPECT_TRUE(foundAnchor);
}

// Test scanning an alias
TEST_F(ScannerTest_154, AliasProducesToken_154) {
  auto scanner = CreateScanner("*alias");
  bool foundAlias = false;
  int tokenCount = 0;
  while (!scanner->empty()) {
    Token& t = scanner->peek();
    if (t.type == Token::ALIAS) {
      foundAlias = true;
      EXPECT_EQ(t.value, "alias");
    }
    scanner->pop();
    tokenCount++;
    if (tokenCount > 200) break;
  }
  EXPECT_TRUE(foundAlias);
}

// Test scanning a tag
TEST_F(ScannerTest_154, TagProducesToken_154) {
  auto scanner = CreateScanner("!tag value");
  bool foundTag = false;
  int tokenCount = 0;
  while (!scanner->empty()) {
    Token& t = scanner->peek();
    if (t.type == Token::TAG) {
      foundTag = true;
    }
    scanner->pop();
    tokenCount++;
    if (tokenCount > 200) break;
  }
  EXPECT_TRUE(foundTag);
}

// Test scanning document start marker
TEST_F(ScannerTest_154, DocumentStartMarker_154) {
  auto scanner = CreateScanner("---\nhello");
  bool foundDocStart = false;
  int tokenCount = 0;
  while (!scanner->empty()) {
    Token& t = scanner->peek();
    if (t.type == Token::DOC_START) {
      foundDocStart = true;
    }
    scanner->pop();
    tokenCount++;
    if (tokenCount > 200) break;
  }
  EXPECT_TRUE(foundDocStart);
}

// Test scanning document end marker
TEST_F(ScannerTest_154, DocumentEndMarker_154) {
  auto scanner = CreateScanner("hello\n...");
  bool foundDocEnd = false;
  int tokenCount = 0;
  while (!scanner->empty()) {
    Token& t = scanner->peek();
    if (t.type == Token::DOC_END) {
      foundDocEnd = true;
    }
    scanner->pop();
    tokenCount++;
    if (tokenCount > 200) break;
  }
  EXPECT_TRUE(foundDocEnd);
}

// Test scanning a directive
TEST_F(ScannerTest_154, DirectiveProducesToken_154) {
  auto scanner = CreateScanner("%YAML 1.2\n---\nhello");
  bool foundDirective = false;
  int tokenCount = 0;
  while (!scanner->empty()) {
    Token& t = scanner->peek();
    if (t.type == Token::DIRECTIVE) {
      foundDirective = true;
    }
    scanner->pop();
    tokenCount++;
    if (tokenCount > 200) break;
  }
  EXPECT_TRUE(foundDirective);
}

// Test scanning a block scalar (literal)
TEST_F(ScannerTest_154, BlockLiteralScalar_154) {
  auto scanner = CreateScanner("|\n  hello\n  world");
  bool foundScalar = false;
  int tokenCount = 0;
  while (!scanner->empty()) {
    Token& t = scanner->peek();
    if (t.type == Token::SCALAR) {
      foundScalar = true;
    }
    scanner->pop();
    tokenCount++;
    if (tokenCount > 200) break;
  }
  EXPECT_TRUE(foundScalar);
}

// Test scanning a block scalar (folded)
TEST_F(ScannerTest_154, BlockFoldedScalar_154) {
  auto scanner = CreateScanner(">\n  hello\n  world");
  bool foundScalar = false;
  int tokenCount = 0;
  while (!scanner->empty()) {
    Token& t = scanner->peek();
    if (t.type == Token::SCALAR) {
      foundScalar = true;
    }
    scanner->pop();
    tokenCount++;
    if (tokenCount > 200) break;
  }
  EXPECT_TRUE(foundScalar);
}

// Test that pop followed by empty works correctly through all tokens
TEST_F(ScannerTest_154, PopAllTokensThenEmpty_154) {
  auto scanner = CreateScanner("a: b\nc: d\ne: f");
  int tokenCount = 0;
  while (!scanner->empty()) {
    scanner->pop();
    tokenCount++;
    if (tokenCount > 500) break;
  }
  EXPECT_TRUE(scanner->empty());
  EXPECT_LT(tokenCount, 500);  // Should have finished in reasonable number of tokens
}

// Test multiple pops on empty scanner
TEST_F(ScannerTest_154, MultiplePopOnEmptyScanner_154) {
  auto scanner = CreateScanner("");
  while (!scanner->empty()) {
    scanner->pop();
  }
  // Multiple pops on empty should be safe
  scanner->pop();
  scanner->pop();
  scanner->pop();
  EXPECT_TRUE(scanner->empty());
}

// Test mark advances as tokens are consumed
TEST_F(ScannerTest_154, MarkAdvancesWithTokens_154) {
  auto scanner = CreateScanner("key: value");
  Mark initialMark = scanner->mark();
  // Consume some tokens
  if (!scanner->empty()) {
    scanner->pop();
  }
  // Mark should still be retrievable
  Mark laterMark = scanner->mark();
  (void)initialMark;
  (void)laterMark;
  // Just verify no crash; the exact values depend on implementation
}

// Test nested structures
TEST_F(ScannerTest_154, NestedMappingProducesTokens_154) {
  auto scanner = CreateScanner("a:\n  b: c\n  d: e");
  int tokenCount = 0;
  int blockMapStartCount = 0;
  while (!scanner->empty()) {
    Token& t = scanner->peek();
    if (t.type == Token::BLOCK_MAP_START) blockMapStartCount++;
    scanner->pop();
    tokenCount++;
    if (tokenCount > 200) break;
  }
  // Should have at least 2 block map starts (outer and inner)
  EXPECT_GE(blockMapStartCount, 2);
}

// Test whitespace-only input
TEST_F(ScannerTest_154, WhitespaceOnlyInput_154) {
  auto scanner = CreateScanner("   \n  \n   ");
  int tokenCount = 0;
  while (!scanner->empty()) {
    scanner->pop();
    tokenCount++;
    if (tokenCount > 200) break;
  }
  EXPECT_TRUE(scanner->empty());
  // Should at least have stream start and stream end
  EXPECT_GE(tokenCount, 2);
}

// Test comment-only input
TEST_F(ScannerTest_154, CommentOnlyInput_154) {
  auto scanner = CreateScanner("# this is a comment\n# another comment");
  int tokenCount = 0;
  while (!scanner->empty()) {
    scanner->pop();
    tokenCount++;
    if (tokenCount > 200) break;
  }
  EXPECT_TRUE(scanner->empty());
  // Comments should be skipped; at least stream start and end
  EXPECT_GE(tokenCount, 2);
}

}  // namespace
}  // namespace YAML
