// TEST_ID: 509
#include <gtest/gtest.h>

#include "scanner.h"
#include "token.h"

namespace {

class SimpleKeyTest_509 : public ::testing::Test {
 protected:
  static YAML::Mark AnyMark() {
    // yaml-cpp Mark is typically default-constructible; if not, this will still compile
    // only if Mark has a default ctor in this codebase.
    return YAML::Mark();
  }

  static YAML::Token MakeToken_509() {
    // Avoid depending on specific token TYPE enumerators: cast 0 to the TYPE.
    return YAML::Token(static_cast<YAML::Token::TYPE>(0), AnyMark());
  }

  static YAML::Scanner::IndentMarker MakeIndent_509() {
    // Avoid depending on specific INDENT_TYPE enumerators: cast 0 to the INDENT_TYPE.
    return YAML::Scanner::IndentMarker(0, static_cast<YAML::Scanner::INDENT_TYPE>(0));
  }
};

TEST_F(SimpleKeyTest_509, ValidateWithNoPointersDoesNotThrow_509) {
  YAML::Scanner::SimpleKey key(AnyMark(), /*flowLevel=*/0);
  EXPECT_NO_THROW(key.Validate());
}

TEST_F(SimpleKeyTest_509, ValidateSetsIndentMarkerStatusToValid_509) {
  YAML::Scanner::SimpleKey key(AnyMark(), /*flowLevel=*/0);

  YAML::Scanner::IndentMarker indent = MakeIndent_509();
  indent.status = YAML::Token::INVALID;

  key.pIndent = &indent;

  key.Validate();

  EXPECT_EQ(indent.status, YAML::Token::VALID);
}

TEST_F(SimpleKeyTest_509, ValidateSetsMapStartTokenStatusToValid_509) {
  YAML::Scanner::SimpleKey key(AnyMark(), /*flowLevel=*/0);

  YAML::Token mapStart = MakeToken_509();
  mapStart.status = YAML::Token::UNVERIFIED;

  key.pMapStart = &mapStart;

  key.Validate();

  EXPECT_EQ(mapStart.status, YAML::Token::VALID);
}

TEST_F(SimpleKeyTest_509, ValidateSetsKeyTokenStatusToValid_509) {
  YAML::Scanner::SimpleKey key(AnyMark(), /*flowLevel=*/0);

  YAML::Token tok = MakeToken_509();
  tok.status = YAML::Token::INVALID;

  key.pKey = &tok;

  key.Validate();

  EXPECT_EQ(tok.status, YAML::Token::VALID);
}

TEST_F(SimpleKeyTest_509, ValidateSetsAllReferencedStatusesToValid_509) {
  YAML::Scanner::SimpleKey key(AnyMark(), /*flowLevel=*/0);

  YAML::Scanner::IndentMarker indent = MakeIndent_509();
  YAML::Token mapStart = MakeToken_509();
  YAML::Token tok = MakeToken_509();

  indent.status = YAML::Token::INVALID;
  mapStart.status = YAML::Token::UNVERIFIED;
  tok.status = YAML::Token::INVALID;

  key.pIndent = &indent;
  key.pMapStart = &mapStart;
  key.pKey = &tok;

  key.Validate();

  EXPECT_EQ(indent.status, YAML::Token::VALID);
  EXPECT_EQ(mapStart.status, YAML::Token::VALID);
  EXPECT_EQ(tok.status, YAML::Token::VALID);
}

TEST_F(SimpleKeyTest_509, ValidateKeepsAlreadyValidStatusesValid_509) {
  YAML::Scanner::SimpleKey key(AnyMark(), /*flowLevel=*/0);

  YAML::Scanner::IndentMarker indent = MakeIndent_509();
  YAML::Token mapStart = MakeToken_509();
  YAML::Token tok = MakeToken_509();

  indent.status = YAML::Token::VALID;
  mapStart.status = YAML::Token::VALID;
  tok.status = YAML::Token::VALID;

  key.pIndent = &indent;
  key.pMapStart = &mapStart;
  key.pKey = &tok;

  key.Validate();

  EXPECT_EQ(indent.status, YAML::Token::VALID);
  EXPECT_EQ(mapStart.status, YAML::Token::VALID);
  EXPECT_EQ(tok.status, YAML::Token::VALID);
}

}  // namespace