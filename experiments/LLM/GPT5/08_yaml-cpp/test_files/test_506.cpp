// File: ./TestProjects/yaml-cpp/test/parser_handle_next_document_test_506.cpp

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/eventhandler.h"
#include "yaml-cpp/parser.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::NiceMock;
using ::testing::StrictMock;

namespace {

class MockEventHandler_506 : public YAML::EventHandler {
public:
  MOCK_METHOD(void, OnDocumentStart, (const YAML::Mark& mark), (override));
  MOCK_METHOD(void, OnDocumentEnd, (), (override));

  MOCK_METHOD(void, OnNull, (const YAML::Mark& mark, YAML::anchor_t anchor), (override));
  MOCK_METHOD(void, OnAlias, (const YAML::Mark& mark, YAML::anchor_t anchor), (override));
  MOCK_METHOD(void,
              OnScalar,
              (const YAML::Mark& mark,
               const std::string& tag,
               YAML::anchor_t anchor,
               const std::string& value),
              (override));
  MOCK_METHOD(void,
              OnSequenceStart,
              (const YAML::Mark& mark,
               const std::string& tag,
               YAML::anchor_t anchor,
               YAML::EmitterStyle::value style),
              (override));
  MOCK_METHOD(void, OnSequenceEnd, (), (override));

  MOCK_METHOD(void,
              OnMapStart,
              (const YAML::Mark& mark,
               const std::string& tag,
               YAML::anchor_t anchor,
               YAML::EmitterStyle::value style),
              (override));
  MOCK_METHOD(void, OnMapEnd, (), (override));

  MOCK_METHOD(void, OnAnchor, (const YAML::Mark& mark, const std::string& anchor_name), (override));
};

class ParserHandleNextDocumentTest_506 : public ::testing::Test {
protected:
  static YAML::Parser MakeParserLoadedFromString(const std::string& input) {
    YAML::Parser parser;
    std::stringstream ss(input);
    parser.Load(ss);
    return parser;
  }
};

TEST_F(ParserHandleNextDocumentTest_506, DefaultConstructed_NoScanner_ReturnsFalse_506) {
  YAML::Parser parser;
  StrictMock<MockEventHandler_506> handler;

  // With no loaded stream, HandleNextDocument should report that no document was handled.
  EXPECT_FALSE(parser.HandleNextDocument(handler));
}

TEST_F(ParserHandleNextDocumentTest_506, LoadEmptyStream_ReturnsFalse_506) {
  YAML::Parser parser;
  StrictMock<MockEventHandler_506> handler;

  std::stringstream empty;
  parser.Load(empty);

  EXPECT_FALSE(parser.HandleNextDocument(handler));
}

TEST_F(ParserHandleNextDocumentTest_506, SimpleScalar_ReturnsTrue_EmitsScalarValue_506) {
  YAML::Parser parser = MakeParserLoadedFromString("hello\n");
  NiceMock<MockEventHandler_506> handler;

  // Verify key externally observable interactions (not assuming full call ordering/details).
  EXPECT_CALL(handler, OnDocumentStart(_)).Times(AtLeast(1));
  EXPECT_CALL(handler, OnScalar(_, _, _, "hello")).Times(AtLeast(1));
  EXPECT_CALL(handler, OnDocumentEnd()).Times(AtLeast(1));

  EXPECT_TRUE(parser.HandleNextDocument(handler));
}

TEST_F(ParserHandleNextDocumentTest_506, SimpleMap_ReturnsTrue_EmitsMapAndScalars_506) {
  YAML::Parser parser = MakeParserLoadedFromString("a: b\n");
  NiceMock<MockEventHandler_506> handler;

  EXPECT_CALL(handler, OnDocumentStart(_)).Times(AtLeast(1));
  EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(AtLeast(1));
  EXPECT_CALL(handler, OnScalar(_, _, _, "a")).Times(AtLeast(1));
  EXPECT_CALL(handler, OnScalar(_, _, _, "b")).Times(AtLeast(1));
  EXPECT_CALL(handler, OnMapEnd()).Times(AtLeast(1));
  EXPECT_CALL(handler, OnDocumentEnd()).Times(AtLeast(1));

  EXPECT_TRUE(parser.HandleNextDocument(handler));
}

TEST_F(ParserHandleNextDocumentTest_506, MultipleDocuments_TwoTrueThenFalse_506) {
  YAML::Parser parser = MakeParserLoadedFromString("---\nfoo\n---\nbar\n");

  {
    NiceMock<MockEventHandler_506> handler1;
    EXPECT_CALL(handler1, OnScalar(_, _, _, "foo")).Times(AtLeast(1));
    EXPECT_TRUE(parser.HandleNextDocument(handler1));
  }

  {
    NiceMock<MockEventHandler_506> handler2;
    EXPECT_CALL(handler2, OnScalar(_, _, _, "bar")).Times(AtLeast(1));
    EXPECT_TRUE(parser.HandleNextDocument(handler2));
  }

  // No more documents expected.
  NiceMock<MockEventHandler_506> handler3;
  EXPECT_FALSE(parser.HandleNextDocument(handler3));
}

TEST_F(ParserHandleNextDocumentTest_506, InvalidYaml_ReturnsFalseOrThrows_506) {
  YAML::Parser parser = MakeParserLoadedFromString("a: [\n");
  NiceMock<MockEventHandler_506> handler;

  bool result = false;
  try {
    result = parser.HandleNextDocument(handler);
  } catch (...) {
    // Error behavior is observable as an exception; accept it.
    SUCCEED();
    return;
  }

  // If no exception, then handling the document should not succeed.
  EXPECT_FALSE(result);
}

}  // namespace