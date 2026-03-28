#include "gtest/gtest.h"
#include "scanner.h"
#include "token.h"

namespace YAML {

class SimpleKeyValidateTest_509 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that Validate on a default-constructed SimpleKey (all pointers null) does not crash
TEST_F(SimpleKeyValidateTest_509, ValidateWithAllNullPointers_509) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);
    // All pointers should be null by default
    EXPECT_EQ(sk.pIndent, nullptr);
    EXPECT_EQ(sk.pMapStart, nullptr);
    EXPECT_EQ(sk.pKey, nullptr);
    // Should not crash
    ASSERT_NO_THROW(sk.Validate());
}

// Test that Validate sets pIndent->status to VALID
TEST_F(SimpleKeyValidateTest_509, ValidateSetsIndentStatusToValid_509) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);

    Scanner::IndentMarker indent(0, Scanner::IndentMarker::MAP);
    indent.status = Scanner::IndentMarker::INVALID;
    sk.pIndent = &indent;

    sk.Validate();

    EXPECT_EQ(indent.status, Scanner::IndentMarker::VALID);
}

// Test that Validate sets pMapStart->status to VALID
TEST_F(SimpleKeyValidateTest_509, ValidateSetsMapStartStatusToValid_509) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);

    Token mapStart(Token::BLOCK_MAP_START, mark);
    mapStart.status = Token::INVALID;
    sk.pMapStart = &mapStart;

    sk.Validate();

    EXPECT_EQ(mapStart.status, Token::VALID);
}

// Test that Validate sets pKey->status to VALID
TEST_F(SimpleKeyValidateTest_509, ValidateSetsKeyStatusToValid_509) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);

    Token key(Token::KEY, mark);
    key.status = Token::INVALID;
    sk.pKey = &key;

    sk.Validate();

    EXPECT_EQ(key.status, Token::VALID);
}

// Test that Validate sets all three statuses to VALID when all pointers are set
TEST_F(SimpleKeyValidateTest_509, ValidateSetsAllStatusesToValid_509) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);

    Scanner::IndentMarker indent(0, Scanner::IndentMarker::MAP);
    indent.status = Scanner::IndentMarker::INVALID;
    sk.pIndent = &indent;

    Token mapStart(Token::BLOCK_MAP_START, mark);
    mapStart.status = Token::INVALID;
    sk.pMapStart = &mapStart;

    Token key(Token::KEY, mark);
    key.status = Token::INVALID;
    sk.pKey = &key;

    sk.Validate();

    EXPECT_EQ(indent.status, Scanner::IndentMarker::VALID);
    EXPECT_EQ(mapStart.status, Token::VALID);
    EXPECT_EQ(key.status, Token::VALID);
}

// Test that Validate changes UNVERIFIED status to VALID
TEST_F(SimpleKeyValidateTest_509, ValidateChangesUnverifiedToValid_509) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);

    Token key(Token::KEY, mark);
    key.status = Token::UNVERIFIED;
    sk.pKey = &key;

    Token mapStart(Token::BLOCK_MAP_START, mark);
    mapStart.status = Token::UNVERIFIED;
    sk.pMapStart = &mapStart;

    sk.Validate();

    EXPECT_EQ(key.status, Token::VALID);
    EXPECT_EQ(mapStart.status, Token::VALID);
}

// Test Validate with only pIndent set, others null
TEST_F(SimpleKeyValidateTest_509, ValidateWithOnlyIndentSet_509) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);

    Scanner::IndentMarker indent(5, Scanner::IndentMarker::MAP);
    indent.status = Scanner::IndentMarker::INVALID;
    sk.pIndent = &indent;

    ASSERT_NO_THROW(sk.Validate());
    EXPECT_EQ(indent.status, Scanner::IndentMarker::VALID);
}

// Test Validate with only pMapStart set, others null
TEST_F(SimpleKeyValidateTest_509, ValidateWithOnlyMapStartSet_509) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);

    Token mapStart(Token::BLOCK_MAP_START, mark);
    mapStart.status = Token::INVALID;
    sk.pMapStart = &mapStart;

    ASSERT_NO_THROW(sk.Validate());
    EXPECT_EQ(mapStart.status, Token::VALID);
}

// Test Validate with only pKey set, others null
TEST_F(SimpleKeyValidateTest_509, ValidateWithOnlyKeySet_509) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);

    Token key(Token::KEY, mark);
    key.status = Token::INVALID;
    sk.pKey = &key;

    ASSERT_NO_THROW(sk.Validate());
    EXPECT_EQ(key.status, Token::VALID);
}

// Test that Validate on already VALID tokens keeps them VALID
TEST_F(SimpleKeyValidateTest_509, ValidateOnAlreadyValidTokens_509) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);

    Scanner::IndentMarker indent(0, Scanner::IndentMarker::MAP);
    indent.status = Scanner::IndentMarker::VALID;
    sk.pIndent = &indent;

    Token mapStart(Token::BLOCK_MAP_START, mark);
    mapStart.status = Token::VALID;
    sk.pMapStart = &mapStart;

    Token key(Token::KEY, mark);
    key.status = Token::VALID;
    sk.pKey = &key;

    sk.Validate();

    EXPECT_EQ(indent.status, Scanner::IndentMarker::VALID);
    EXPECT_EQ(mapStart.status, Token::VALID);
    EXPECT_EQ(key.status, Token::VALID);
}

// Test SimpleKey constructor initializes pointers to null
TEST_F(SimpleKeyValidateTest_509, ConstructorInitializesPointersToNull_509) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 3);

    EXPECT_EQ(sk.pIndent, nullptr);
    EXPECT_EQ(sk.pMapStart, nullptr);
    EXPECT_EQ(sk.pKey, nullptr);
    EXPECT_EQ(sk.flowLevel, 3u);
}

// Test SimpleKey with different flow levels
TEST_F(SimpleKeyValidateTest_509, ValidateWithDifferentFlowLevels_509) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 10);

    Token key(Token::KEY, mark);
    key.status = Token::INVALID;
    sk.pKey = &key;

    sk.Validate();

    EXPECT_EQ(key.status, Token::VALID);
    EXPECT_EQ(sk.flowLevel, 10u);
}

// Test calling Validate multiple times is idempotent
TEST_F(SimpleKeyValidateTest_509, ValidateMultipleCalls_509) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);

    Token key(Token::KEY, mark);
    key.status = Token::INVALID;
    sk.pKey = &key;

    sk.Validate();
    EXPECT_EQ(key.status, Token::VALID);

    sk.Validate();
    EXPECT_EQ(key.status, Token::VALID);

    sk.Validate();
    EXPECT_EQ(key.status, Token::VALID);
}

}  // namespace YAML
