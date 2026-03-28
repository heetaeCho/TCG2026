// File: singledocparser_test_94.cpp
// TEST_ID: 94

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>
#include <string>

// yaml-cpp internal headers (as laid out in the prompt)
#include "directives.h"
#include "scanner.h"
#include "singledocparser.h"

#include "yaml-cpp/eventhandler.h"

using ::testing::_;
using ::testing::InSequence;
using ::testing::StrEq;

namespace YAML {

class MockEventHandler_94 : public EventHandler {
 public:
  MOCK_METHOD(void, OnDocumentStart, (const Mark& mark), (override));
  MOCK_METHOD(void, OnDocumentEnd, (), (override));

  MOCK_METHOD(void, OnNull, (const Mark& mark, anchor_t anchor), (override));
  MOCK_METHOD(void, OnAlias, (const Mark& mark, anchor_t anchor), (override));
  MOCK_METHOD(void,
              OnScalar,
              (const Mark& mark, const std::string& tag, anchor_t anchor,
               const std::string& value),
              (override));
  MOCK_METHOD(void,
              OnSequenceStart,
              (const Mark& mark, const std::string& tag, anchor_t anchor,
               EmitterStyle::value style),
              (override));
  MOCK_METHOD(void, OnSequenceEnd, (), (override));
  MOCK_METHOD(void,
              OnMapStart,
              (const Mark& mark, const std::string& tag, anchor_t anchor,
               EmitterStyle::value style),
              (override));
  MOCK_METHOD(void, OnMapEnd, (), (override));

  MOCK_METHOD(void, OnAnchor, (const Mark& mark, const std::string& anchor_name), (override));
};

// Helpers to build the parser from input.
static SingleDocParser MakeParser_94(const std::string& yaml, std::unique_ptr<Scanner>& outScanner) {
  auto iss = std::make_unique<std::istringstream>(yaml);
  outScanner = std::make_unique<Scanner>(*iss);

  // Keep the stream alive by storing it in a static list attached to the scanner lifetime.
  // Scanner stores Stream INPUT by value (per prompt), so this is safe even if iss is destroyed,
  // but to avoid relying on that detail, we keep iss alive here via a leak-safe static container.
  // NOTE: This does not introspect parser internals; it only preserves test input lifetime.
  static std::vector<std::unique_ptr<std::istringstream>> s_inputs_94;
  s_inputs_94.push_back(std::move(iss));

  Directives directives;
  return SingleDocParser(*outScanner, directives);
}

class SingleDocParserTest_94 : public ::testing::Test {
 protected:
  MockEventHandler_94 handler_;
};

TEST_F(SingleDocParserTest_94, HandleDocument_EmitsDocumentStartScalarEnd_ForPlainScalar_94) {
  std::unique_ptr<Scanner> scanner;
  auto parser = MakeParser_94("a\n", scanner);

  InSequence seq;
  EXPECT_CALL(handler_, OnDocumentStart(_)).Times(1);
  EXPECT_CALL(handler_, OnScalar(_, _, _, StrEq("a"))).Times(1);
  EXPECT_CALL(handler_, OnDocumentEnd()).Times(1);

  parser.HandleDocument(handler_);
}

TEST_F(SingleDocParserTest_94, HandleDocument_HandlesExplicitDocStartAndEnd_MaintainsEventOrder_94) {
  std::unique_ptr<Scanner> scanner;
  auto parser = MakeParser_94("---\na\n...\n", scanner);

  InSequence seq;
  EXPECT_CALL(handler_, OnDocumentStart(_)).Times(1);
  EXPECT_CALL(handler_, OnScalar(_, _, _, StrEq("a"))).Times(1);
  EXPECT_CALL(handler_, OnDocumentEnd()).Times(1);

  parser.HandleDocument(handler_);
}

TEST_F(SingleDocParserTest_94, HandleDocument_PopsTrailingDocEndTokens_LeavesScannerEmpty_94) {
  std::unique_ptr<Scanner> scanner;
  auto parser = MakeParser_94("a\n...\n...\n", scanner);

  // We only verify observable behavior:
  // - document start/end emitted
  // - trailing DOC_END tokens are consumed such that scanner can become empty
  InSequence seq;
  EXPECT_CALL(handler_, OnDocumentStart(_)).Times(1);
  EXPECT_CALL(handler_, OnScalar(_, _, _, StrEq("a"))).Times(1);
  EXPECT_CALL(handler_, OnDocumentEnd()).Times(1);

  parser.HandleDocument(handler_);

  // Observable post-condition via public Scanner API.
  EXPECT_TRUE(scanner->empty());
}

#if GTEST_HAS_DEATH_TEST
TEST_F(SingleDocParserTest_94, HandleDocument_DeathWhenScannerEmpty_94) {
  // Create a scanner and exhaust it, then call HandleDocument to hit the observable assert.
  std::istringstream iss("");
  Scanner scanner(iss);
  Directives directives;
  SingleDocParser parser(scanner, directives);

  while (!scanner.empty()) {
    scanner.pop();
  }

  MockEventHandler_94 handler;
  EXPECT_DEATH_IF_SUPPORTED(parser.HandleDocument(handler), ".*");
}
#endif

}  // namespace YAML
