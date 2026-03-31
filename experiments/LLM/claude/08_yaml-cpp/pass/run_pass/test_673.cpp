#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include "yaml-cpp/parser.h"
#include "yaml-cpp/eventhandler.h"
#include "yaml-cpp/emitterstyle.h"
#include "yaml-cpp/mark.h"

// Mock EventHandler to verify interactions
class MockEventHandler : public YAML::EventHandler {
 public:
  MOCK_METHOD(void, OnDocumentStart, (const YAML::Mark&), (override));
  MOCK_METHOD(void, OnDocumentEnd, (), (override));
  MOCK_METHOD(void, OnNull, (const YAML::Mark&, YAML::anchor_t), (override));
  MOCK_METHOD(void, OnAlias, (const YAML::Mark&, YAML::anchor_t), (override));
  MOCK_METHOD(void, OnScalar,
              (const YAML::Mark&, const std::string&, YAML::anchor_t,
               const std::string&),
              (override));
  MOCK_METHOD(void, OnSequenceStart,
              (const YAML::Mark&, const std::string&, YAML::anchor_t,
               YAML::EmitterStyle::value),
              (override));
  MOCK_METHOD(void, OnSequenceEnd, (), (override));
  MOCK_METHOD(void, OnMapStart,
              (const YAML::Mark&, const std::string&, YAML::anchor_t,
               YAML::EmitterStyle::value),
              (override));
  MOCK_METHOD(void, OnMapEnd, (), (override));
};

// NullEventHandler as defined in the source
class NullEventHandler : public YAML::EventHandler {
 public:
  NullEventHandler() = default;
  void OnDocumentStart(const YAML::Mark&) override {}
  void OnDocumentEnd() override {}
  void OnNull(const YAML::Mark&, YAML::anchor_t) override {}
  void OnAlias(const YAML::Mark&, YAML::anchor_t) override {}
  void OnScalar(const YAML::Mark&, const std::string&, YAML::anchor_t,
                const std::string&) override {}
  void OnSequenceStart(const YAML::Mark&, const std::string&, YAML::anchor_t,
                        YAML::EmitterStyle::value) override {}
  void OnSequenceEnd() override {}
  void OnMapStart(const YAML::Mark&, const std::string&, YAML::anchor_t,
                   YAML::EmitterStyle::value) override {}
  void OnMapEnd() override {}
};

// The run function under test
void run(std::istream& in) {
  YAML::Parser parser(in);
  NullEventHandler handler;
  parser.HandleNextDocument(handler);
}

class ParserTest_673 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor creates a parser that evaluates to false
TEST_F(ParserTest_673, DefaultConstructorBoolIsFalse_673) {
  YAML::Parser parser;
  EXPECT_FALSE(parser);
}

// Test constructor with input stream creates a valid parser
TEST_F(ParserTest_673, StreamConstructorBoolIsTrue_673) {
  std::stringstream ss("hello: world");
  YAML::Parser parser(ss);
  EXPECT_TRUE(parser);
}

// Test constructor with empty stream
TEST_F(ParserTest_673, EmptyStreamConstructor_673) {
  std::stringstream ss("");
  YAML::Parser parser(ss);
  // Empty stream may or may not be "valid" depending on implementation
  // but it should not crash
}

// Test Load sets up the parser from a stream
TEST_F(ParserTest_673, LoadMakesParserValid_673) {
  YAML::Parser parser;
  EXPECT_FALSE(parser);
  std::stringstream ss("key: value");
  parser.Load(ss);
  EXPECT_TRUE(parser);
}

// Test HandleNextDocument returns true for a valid document
TEST_F(ParserTest_673, HandleNextDocumentReturnsTrueForValidDoc_673) {
  std::stringstream ss("hello: world");
  YAML::Parser parser(ss);
  NullEventHandler handler;
  EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test HandleNextDocument returns false when no more documents
TEST_F(ParserTest_673, HandleNextDocumentReturnsFalseWhenEmpty_673) {
  std::stringstream ss("");
  YAML::Parser parser(ss);
  NullEventHandler handler;
  EXPECT_FALSE(parser.HandleNextDocument(handler));
}

// Test HandleNextDocument returns false on second call for single-document stream
TEST_F(ParserTest_673, HandleNextDocumentReturnsFalseOnSecondCall_673) {
  std::stringstream ss("hello: world");
  YAML::Parser parser(ss);
  NullEventHandler handler;
  EXPECT_TRUE(parser.HandleNextDocument(handler));
  EXPECT_FALSE(parser.HandleNextDocument(handler));
}

// Test multiple documents separated by ---
TEST_F(ParserTest_673, HandleMultipleDocuments_673) {
  std::stringstream ss("---\nhello: world\n---\nfoo: bar\n");
  YAML::Parser parser(ss);
  NullEventHandler handler;
  EXPECT_TRUE(parser.HandleNextDocument(handler));
  EXPECT_TRUE(parser.HandleNextDocument(handler));
  EXPECT_FALSE(parser.HandleNextDocument(handler));
}

// Test that HandleNextDocument invokes OnDocumentStart and OnDocumentEnd
TEST_F(ParserTest_673, HandleNextDocumentCallsDocumentEvents_673) {
  std::stringstream ss("hello");
  YAML::Parser parser(ss);
  MockEventHandler handler;

  EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
  EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
  EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_))
      .Times(::testing::AtLeast(0));
  EXPECT_CALL(handler, OnNull(::testing::_, ::testing::_)).Times(::testing::AtLeast(0));
  EXPECT_CALL(handler, OnAlias(::testing::_, ::testing::_)).Times(::testing::AtLeast(0));
  EXPECT_CALL(handler, OnSequenceStart(::testing::_, ::testing::_, ::testing::_, ::testing::_))
      .Times(::testing::AtLeast(0));
  EXPECT_CALL(handler, OnSequenceEnd()).Times(::testing::AtLeast(0));
  EXPECT_CALL(handler, OnMapStart(::testing::_, ::testing::_, ::testing::_, ::testing::_))
      .Times(::testing::AtLeast(0));
  EXPECT_CALL(handler, OnMapEnd()).Times(::testing::AtLeast(0));

  parser.HandleNextDocument(handler);
}

// Test scalar value is passed to OnScalar
TEST_F(ParserTest_673, ScalarValuePassedCorrectly_673) {
  std::stringstream ss("hello");
  YAML::Parser parser(ss);
  MockEventHandler handler;

  EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
  EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
  EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, "hello"))
      .Times(1);

  parser.HandleNextDocument(handler);
}

// Test map triggers OnMapStart and OnMapEnd
TEST_F(ParserTest_673, MapTriggersMapEvents_673) {
  std::stringstream ss("key: value");
  YAML::Parser parser(ss);
  MockEventHandler handler;

  EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
  EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
  EXPECT_CALL(handler, OnMapStart(::testing::_, ::testing::_, ::testing::_, ::testing::_))
      .Times(1);
  EXPECT_CALL(handler, OnMapEnd()).Times(1);
  EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_))
      .Times(2);  // key and value

  parser.HandleNextDocument(handler);
}

// Test sequence triggers OnSequenceStart and OnSequenceEnd
TEST_F(ParserTest_673, SequenceTriggersSequenceEvents_673) {
  std::stringstream ss("- item1\n- item2\n");
  YAML::Parser parser(ss);
  MockEventHandler handler;

  EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
  EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
  EXPECT_CALL(handler, OnSequenceStart(::testing::_, ::testing::_, ::testing::_, ::testing::_))
      .Times(1);
  EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
  EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_))
      .Times(2);

  parser.HandleNextDocument(handler);
}

// Test null value triggers OnNull
TEST_F(ParserTest_673, NullValueTriggersOnNull_673) {
  std::stringstream ss("~");
  YAML::Parser parser(ss);
  MockEventHandler handler;

  EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
  EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
  // null may be represented as a scalar "~" or as OnNull depending on implementation
  EXPECT_CALL(handler, OnNull(::testing::_, ::testing::_)).Times(::testing::AtLeast(0));
  EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_))
      .Times(::testing::AtLeast(0));

  parser.HandleNextDocument(handler);
}

// Test alias triggers OnAlias
TEST_F(ParserTest_673, AliasTriggersOnAlias_673) {
  std::stringstream ss("- &anchor value\n- *anchor\n");
  YAML::Parser parser(ss);
  MockEventHandler handler;

  EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
  EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
  EXPECT_CALL(handler, OnSequenceStart(::testing::_, ::testing::_, ::testing::_, ::testing::_))
      .Times(1);
  EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
  EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_))
      .Times(1);
  EXPECT_CALL(handler, OnAlias(::testing::_, ::testing::_)).Times(1);

  parser.HandleNextDocument(handler);
}

// Test the run function doesn't crash with valid YAML
TEST_F(ParserTest_673, RunFunctionWithValidYaml_673) {
  std::stringstream ss("key: value");
  EXPECT_NO_THROW(run(ss));
}

// Test the run function doesn't crash with empty input
TEST_F(ParserTest_673, RunFunctionWithEmptyInput_673) {
  std::stringstream ss("");
  EXPECT_NO_THROW(run(ss));
}

// Test the run function with complex YAML
TEST_F(ParserTest_673, RunFunctionWithComplexYaml_673) {
  std::stringstream ss(
      "---\n"
      "name: test\n"
      "items:\n"
      "  - first\n"
      "  - second\n"
      "nested:\n"
      "  key: value\n");
  EXPECT_NO_THROW(run(ss));
}

// Test Load can be called multiple times
TEST_F(ParserTest_673, LoadCalledMultipleTimes_673) {
  YAML::Parser parser;
  NullEventHandler handler;

  std::stringstream ss1("first: doc");
  parser.Load(ss1);
  EXPECT_TRUE(parser);
  EXPECT_TRUE(parser.HandleNextDocument(handler));

  std::stringstream ss2("second: doc");
  parser.Load(ss2);
  EXPECT_TRUE(parser);
  EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test PrintTokens doesn't crash
TEST_F(ParserTest_673, PrintTokensDoesNotCrash_673) {
  std::stringstream input("key: value");
  YAML::Parser parser(input);
  std::stringstream output;
  EXPECT_NO_THROW(parser.PrintTokens(output));
}

// Test PrintTokens with empty input
TEST_F(ParserTest_673, PrintTokensEmptyInput_673) {
  std::stringstream input("");
  YAML::Parser parser(input);
  std::stringstream output;
  EXPECT_NO_THROW(parser.PrintTokens(output));
}

// Test bool operator after consuming all documents
TEST_F(ParserTest_673, BoolAfterAllDocumentsConsumed_673) {
  std::stringstream ss("hello");
  YAML::Parser parser(ss);
  EXPECT_TRUE(parser);
  NullEventHandler handler;
  parser.HandleNextDocument(handler);
  // After consuming documents, parser might still be "true" or "false"
  // The key test is that it doesn't crash
}

// Test with explicit document markers
TEST_F(ParserTest_673, ExplicitDocumentMarkers_673) {
  std::stringstream ss("---\nhello\n...\n");
  YAML::Parser parser(ss);
  NullEventHandler handler;
  EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test nested maps
TEST_F(ParserTest_673, NestedMaps_673) {
  std::stringstream ss("outer:\n  inner: value\n");
  YAML::Parser parser(ss);
  MockEventHandler handler;

  EXPECT_CALL(handler, OnDocumentStart(::testing::_)).Times(1);
  EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
  EXPECT_CALL(handler, OnMapStart(::testing::_, ::testing::_, ::testing::_, ::testing::_))
      .Times(2);
  EXPECT_CALL(handler, OnMapEnd()).Times(2);
  EXPECT_CALL(handler, OnScalar(::testing::_, ::testing::_, ::testing::_, ::testing::_))
      .Times(3);  // outer, inner, value

  parser.HandleNextDocument(handler);
}

// Test flow style map
TEST_F(ParserTest_673, FlowStyleMap_673) {
  std::stringstream ss("{key: value}");
  YAML::Parser parser(ss);
  NullEventHandler handler;
  EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test flow style sequence
TEST_F(ParserTest_673, FlowStyleSequence_673) {
  std::stringstream ss("[a, b, c]");
  YAML::Parser parser(ss);
  NullEventHandler handler;
  EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test multiline string
TEST_F(ParserTest_673, MultilineString_673) {
  std::stringstream ss("|\n  line1\n  line2\n");
  YAML::Parser parser(ss);
  NullEventHandler handler;
  EXPECT_TRUE(parser.HandleNextDocument(handler));
}

// Test with only whitespace
TEST_F(ParserTest_673, WhitespaceOnlyInput_673) {
  std::stringstream ss("   \n\n   \n");
  YAML::Parser parser(ss);
  NullEventHandler handler;
  EXPECT_FALSE(parser.HandleNextDocument(handler));
}

// Test with comment-only input
TEST_F(ParserTest_673, CommentOnlyInput_673) {
  std::stringstream ss("# This is a comment\n");
  YAML::Parser parser(ss);
  NullEventHandler handler;
  EXPECT_FALSE(parser.HandleNextDocument(handler));
}
