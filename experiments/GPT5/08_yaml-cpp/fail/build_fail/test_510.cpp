// TEST_ID: 510
#include <gtest/gtest.h>

#include "scanner.h"
#include "token.h"

namespace {

using YAML::Mark;
using YAML::Scanner;
using YAML::Token;

class SimpleKeyTest_510 : public ::testing::Test {
 protected:
  static Mark MakeMark() {
    // yaml-cpp Mark typically has a default constructor; if not, this will fail
    // and should be adjusted to whatever the project provides.
    return Mark();
  }
};

TEST_F(SimpleKeyTest_510, Invalidate_AllPointersSet_MarksAllInvalid_510) {
  const Mark mark = MakeMark();

  Scanner::SimpleKey key(mark, /*flowLevel*/ 0);

  // Prepare collaborators
  Scanner::IndentMarker indent(/*column*/ 0, static_cast<Scanner::INDENT_TYPE>(0));
  Token mapStart(static_cast<Token::TYPE>(0), mark);
  Token keyTok(static_cast<Token::TYPE>(0), mark);

  // Precondition: not already invalid (best-effort; constructor may set VALID)
  EXPECT_NE(indent.status, Scanner::IndentMarker::INVALID);
  EXPECT_NE(mapStart.status, Token::INVALID);
  EXPECT_NE(keyTok.status, Token::INVALID);

  key.pIndent = &indent;
  key.pMapStart = &mapStart;
  key.pKey = &keyTok;

  key.Invalidate();

  EXPECT_EQ(indent.status, Scanner::IndentMarker::INVALID);
  EXPECT_EQ(mapStart.status, Token::INVALID);
  EXPECT_EQ(keyTok.status, Token::INVALID);
}

TEST_F(SimpleKeyTest_510, Invalidate_NullPointers_DoesNotCrash_510) {
  const Mark mark = MakeMark();
  Scanner::SimpleKey key(mark, /*flowLevel*/ 0);

  key.pIndent = nullptr;
  key.pMapStart = nullptr;
  key.pKey = nullptr;

  // Observable behavior: should be safe to call (no crash).
  EXPECT_NO_THROW(key.Invalidate());
}

TEST_F(SimpleKeyTest_510, Invalidate_OnlyIndentSet_OnlyIndentInvalidated_510) {
  const Mark mark = MakeMark();
  Scanner::SimpleKey key(mark, /*flowLevel*/ 0);

  Scanner::IndentMarker indent(/*column*/ 2, static_cast<Scanner::INDENT_TYPE>(0));
  key.pIndent = &indent;
  key.pMapStart = nullptr;
  key.pKey = nullptr;

  EXPECT_NE(indent.status, Scanner::IndentMarker::INVALID);

  key.Invalidate();

  EXPECT_EQ(indent.status, Scanner::IndentMarker::INVALID);
}

TEST_F(SimpleKeyTest_510, Invalidate_OnlyTokensSet_OnlyTokensInvalidated_510) {
  const Mark mark = MakeMark();
  Scanner::SimpleKey key(mark, /*flowLevel*/ 0);

  Token mapStart(static_cast<Token::TYPE>(0), mark);
  Token keyTok(static_cast<Token::TYPE>(0), mark);

  key.pIndent = nullptr;
  key.pMapStart = &mapStart;
  key.pKey = &keyTok;

  EXPECT_NE(mapStart.status, Token::INVALID);
  EXPECT_NE(keyTok.status, Token::INVALID);

  key.Invalidate();

  EXPECT_EQ(mapStart.status, Token::INVALID);
  EXPECT_EQ(keyTok.status, Token::INVALID);
}

TEST_F(SimpleKeyTest_510, Invalidate_CalledTwice_RemainsInvalid_510) {
  const Mark mark = MakeMark();
  Scanner::SimpleKey key(mark, /*flowLevel*/ 0);

  Scanner::IndentMarker indent(/*column*/ 0, static_cast<Scanner::INDENT_TYPE>(0));
  Token mapStart(static_cast<Token::TYPE>(0), mark);
  Token keyTok(static_cast<Token::TYPE>(0), mark);

  key.pIndent = &indent;
  key.pMapStart = &mapStart;
  key.pKey = &keyTok;

  key.Invalidate();
  EXPECT_EQ(indent.status, Scanner::IndentMarker::INVALID);
  EXPECT_EQ(mapStart.status, Token::INVALID);
  EXPECT_EQ(keyTok.status, Token::INVALID);

  // Second call should be safe and keep them invalid.
  EXPECT_NO_THROW(key.Invalidate());
  EXPECT_EQ(indent.status, Scanner::IndentMarker::INVALID);
  EXPECT_EQ(mapStart.status, Token::INVALID);
  EXPECT_EQ(keyTok.status, Token::INVALID);
}

}  // namespace