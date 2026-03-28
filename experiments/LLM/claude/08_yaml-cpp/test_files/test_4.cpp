#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

// Include the header under test
#include "token.h"

namespace {

using namespace YAML;

class TokenTest_4 : public ::testing::Test {
 protected:
  Mark defaultMark;
  
  TokenTest_4() : defaultMark() {}
};

// Test that a Token can be constructed with a type and mark
TEST_F(TokenTest_4, ConstructorSetsTypeAndMark_4) {
  Token token(Token::DIRECTIVE, defaultMark);
  EXPECT_EQ(Token::VALID, token.status);
  EXPECT_TRUE(token.value.empty());
  EXPECT_TRUE(token.params.empty());
}

// Test operator<< outputs correct token name for DIRECTIVE type
TEST_F(TokenTest_4, OutputDirectiveType_4) {
  Token token(Token::DIRECTIVE, defaultMark);
  token.value = "test_value";
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("DIRECTIVE: test_value", oss.str());
}

// Test operator<< outputs correct token name for DOC_START type
TEST_F(TokenTest_4, OutputDocStartType_4) {
  Token token(Token::DOC_START, defaultMark);
  token.value = "";
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("DOC_START: ", oss.str());
}

// Test operator<< outputs correct token name for DOC_END type
TEST_F(TokenTest_4, OutputDocEndType_4) {
  Token token(Token::DOC_END, defaultMark);
  token.value = "end";
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("DOC_END: end", oss.str());
}

// Test operator<< outputs correct token name for SCALAR type
TEST_F(TokenTest_4, OutputScalarType_4) {
  Token token(Token::SCALAR, defaultMark);
  token.value = "hello world";
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("SCALAR: hello world", oss.str());
}

// Test operator<< outputs correct token name for NON_PLAIN_SCALAR type
TEST_F(TokenTest_4, OutputNonPlainScalarType_4) {
  Token token(Token::NON_PLAIN_SCALAR, defaultMark);
  token.value = "quoted";
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("NON_PLAIN_SCALAR: quoted", oss.str());
}

// Test operator<< with params outputs params separated by spaces
TEST_F(TokenTest_4, OutputWithSingleParam_4) {
  Token token(Token::TAG, defaultMark);
  token.value = "tag_value";
  token.params.push_back("param1");
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("TAG: tag_value param1", oss.str());
}

// Test operator<< with multiple params
TEST_F(TokenTest_4, OutputWithMultipleParams_4) {
  Token token(Token::ANCHOR, defaultMark);
  token.value = "anchor_val";
  token.params.push_back("p1");
  token.params.push_back("p2");
  token.params.push_back("p3");
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("ANCHOR: anchor_val p1 p2 p3", oss.str());
}

// Test operator<< with empty value and no params
TEST_F(TokenTest_4, OutputEmptyValueNoParams_4) {
  Token token(Token::KEY, defaultMark);
  token.value = "";
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("KEY: ", oss.str());
}

// Test operator<< with empty value and params
TEST_F(TokenTest_4, OutputEmptyValueWithParams_4) {
  Token token(Token::VALUE, defaultMark);
  token.value = "";
  token.params.push_back("param_only");
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("VALUE:  param_only", oss.str());
}

// Test operator<< for BLOCK_SEQ_START
TEST_F(TokenTest_4, OutputBlockSeqStart_4) {
  Token token(Token::BLOCK_SEQ_START, defaultMark);
  token.value = "seq";
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("BLOCK_SEQ_START: seq", oss.str());
}

// Test operator<< for BLOCK_MAP_START
TEST_F(TokenTest_4, OutputBlockMapStart_4) {
  Token token(Token::BLOCK_MAP_START, defaultMark);
  token.value = "map";
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("BLOCK_MAP_START: map", oss.str());
}

// Test operator<< for FLOW_SEQ_START
TEST_F(TokenTest_4, OutputFlowSeqStart_4) {
  Token token(Token::FLOW_SEQ_START, defaultMark);
  token.value = "flow";
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("FLOW_SEQ_START: flow", oss.str());
}

// Test operator<< for FLOW_MAP_START
TEST_F(TokenTest_4, OutputFlowMapStart_4) {
  Token token(Token::FLOW_MAP_START, defaultMark);
  token.value = "";
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("FLOW_MAP_START: ", oss.str());
}

// Test operator<< for FLOW_SEQ_END
TEST_F(TokenTest_4, OutputFlowSeqEnd_4) {
  Token token(Token::FLOW_SEQ_END, defaultMark);
  token.value = "";
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("FLOW_SEQ_END: ", oss.str());
}

// Test operator<< for FLOW_MAP_END
TEST_F(TokenTest_4, OutputFlowMapEnd_4) {
  Token token(Token::FLOW_MAP_END, defaultMark);
  token.value = "";
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("FLOW_MAP_END: ", oss.str());
}

// Test operator<< for FLOW_MAP_COMPACT
TEST_F(TokenTest_4, OutputFlowMapCompact_4) {
  Token token(Token::FLOW_MAP_COMPACT, defaultMark);
  token.value = "compact";
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("FLOW_MAP_COMPACT: compact", oss.str());
}

// Test operator<< for FLOW_ENTRY
TEST_F(TokenTest_4, OutputFlowEntry_4) {
  Token token(Token::FLOW_ENTRY, defaultMark);
  token.value = "entry";
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("FLOW_ENTRY: entry", oss.str());
}

// Test operator<< for BLOCK_ENTRY
TEST_F(TokenTest_4, OutputBlockEntry_4) {
  Token token(Token::BLOCK_ENTRY, defaultMark);
  token.value = "block_entry";
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("BLOCK_ENTRY: block_entry", oss.str());
}

// Test operator<< for BLOCK_SEQ_END
TEST_F(TokenTest_4, OutputBlockSeqEnd_4) {
  Token token(Token::BLOCK_SEQ_END, defaultMark);
  token.value = "";
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("BLOCK_SEQ_END: ", oss.str());
}

// Test operator<< for BLOCK_MAP_END
TEST_F(TokenTest_4, OutputBlockMapEnd_4) {
  Token token(Token::BLOCK_MAP_END, defaultMark);
  token.value = "";
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("BLOCK_MAP_END: ", oss.str());
}

// Test operator<< for ALIAS
TEST_F(TokenTest_4, OutputAlias_4) {
  Token token(Token::ALIAS, defaultMark);
  token.value = "alias_name";
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("ALIAS: alias_name", oss.str());
}

// Test that operator<< returns the stream (chaining)
TEST_F(TokenTest_4, OutputStreamChaining_4) {
  Token token(Token::SCALAR, defaultMark);
  token.value = "val";
  
  std::ostringstream oss;
  oss << token << " extra";
  
  EXPECT_EQ("SCALAR: val extra", oss.str());
}

// Test value with special characters
TEST_F(TokenTest_4, OutputValueWithSpecialChars_4) {
  Token token(Token::SCALAR, defaultMark);
  token.value = "hello\nworld\ttab";
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("SCALAR: hello\nworld\ttab", oss.str());
}

// Test params with special characters
TEST_F(TokenTest_4, OutputParamsWithSpecialChars_4) {
  Token token(Token::DIRECTIVE, defaultMark);
  token.value = "dir";
  token.params.push_back("param with spaces");
  token.params.push_back("param\twith\ttabs");
  
  std::ostringstream oss;
  oss << token;
  
  EXPECT_EQ("DIRECTIVE: dir param with spaces param\twith\ttabs", oss.str());
}

// Test initial status is VALID
TEST_F(TokenTest_4, DefaultStatusIsValid_4) {
  Token token(Token::SCALAR, defaultMark);
  EXPECT_EQ(Token::VALID, token.status);
}

// Test params vector is initially empty
TEST_F(TokenTest_4, ParamsInitiallyEmpty_4) {
  Token token(Token::KEY, defaultMark);
  EXPECT_TRUE(token.params.empty());
  EXPECT_EQ(0u, token.params.size());
}

// Test value is initially empty
TEST_F(TokenTest_4, ValueInitiallyEmpty_4) {
  Token token(Token::VALUE, defaultMark);
  EXPECT_TRUE(token.value.empty());
}

// Test with large number of params
TEST_F(TokenTest_4, OutputWithManyParams_4) {
  Token token(Token::TAG, defaultMark);
  token.value = "v";
  for (int i = 0; i < 100; ++i) {
    token.params.push_back("p" + std::to_string(i));
  }
  
  std::ostringstream oss;
  oss << token;
  
  std::string result = oss.str();
  EXPECT_EQ(0u, result.find("TAG: v"));
  // Check the last param is present
  EXPECT_NE(std::string::npos, result.find("p99"));
}

}  // namespace
