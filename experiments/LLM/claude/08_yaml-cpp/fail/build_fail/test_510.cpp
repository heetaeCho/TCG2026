#include "gtest/gtest.h"
#include "scanner.h"
#include "token.h"

namespace YAML {

class SimpleKeyTest_510 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a newly constructed SimpleKey has nullptr for pIndent, pMapStart, pKey
TEST_F(SimpleKeyTest_510, ConstructorInitializesPointersToNull_510) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);
    EXPECT_EQ(sk.pIndent, nullptr);
    EXPECT_EQ(sk.pMapStart, nullptr);
    EXPECT_EQ(sk.pKey, nullptr);
}

// Test that constructor stores the flow level
TEST_F(SimpleKeyTest_510, ConstructorStoresFlowLevel_510) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 5);
    EXPECT_EQ(sk.flowLevel, 5u);
}

// Test Invalidate when all pointers are null (should not crash)
TEST_F(SimpleKeyTest_510, InvalidateWithAllNullPointers_510) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);
    EXPECT_NO_THROW(sk.Invalidate());
}

// Test Invalidate sets pIndent status to INVALID
TEST_F(SimpleKeyTest_510, InvalidateSetsIndentStatusToInvalid_510) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);

    Scanner::IndentMarker indent(0, Scanner::IndentMarker::MAP);
    indent.status = Scanner::IndentMarker::VALID;
    sk.pIndent = &indent;

    sk.Invalidate();
    EXPECT_EQ(indent.status, Scanner::IndentMarker::INVALID);
}

// Test Invalidate sets pMapStart status to INVALID
TEST_F(SimpleKeyTest_510, InvalidateSetsMapStartStatusToInvalid_510) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);

    Token token(Token::KEY, mark);
    token.status = Token::VALID;
    sk.pMapStart = &token;

    sk.Invalidate();
    EXPECT_EQ(token.status, Token::INVALID);
}

// Test Invalidate sets pKey status to INVALID
TEST_F(SimpleKeyTest_510, InvalidateSetsPKeyStatusToInvalid_510) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);

    Token token(Token::KEY, mark);
    token.status = Token::VALID;
    sk.pKey = &token;

    sk.Invalidate();
    EXPECT_EQ(token.status, Token::INVALID);
}

// Test Invalidate sets all three statuses to INVALID when all pointers are set
TEST_F(SimpleKeyTest_510, InvalidateSetsAllStatusesToInvalid_510) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);

    Scanner::IndentMarker indent(0, Scanner::IndentMarker::MAP);
    indent.status = Scanner::IndentMarker::VALID;

    Token mapStartToken(Token::BLOCK_MAP_START, mark);
    mapStartToken.status = Token::VALID;

    Token keyToken(Token::KEY, mark);
    keyToken.status = Token::VALID;

    sk.pIndent = &indent;
    sk.pMapStart = &mapStartToken;
    sk.pKey = &keyToken;

    sk.Invalidate();

    EXPECT_EQ(indent.status, Scanner::IndentMarker::INVALID);
    EXPECT_EQ(mapStartToken.status, Token::INVALID);
    EXPECT_EQ(keyToken.status, Token::INVALID);
}

// Test Invalidate with only pIndent set, others null
TEST_F(SimpleKeyTest_510, InvalidateWithOnlyIndentSet_510) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);

    Scanner::IndentMarker indent(3, Scanner::IndentMarker::SEQ);
    indent.status = Scanner::IndentMarker::VALID;
    sk.pIndent = &indent;

    EXPECT_NO_THROW(sk.Invalidate());
    EXPECT_EQ(indent.status, Scanner::IndentMarker::INVALID);
}

// Test Invalidate with only pMapStart set, others null
TEST_F(SimpleKeyTest_510, InvalidateWithOnlyMapStartSet_510) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);

    Token mapStart(Token::BLOCK_MAP_START, mark);
    mapStart.status = Token::VALID;
    sk.pMapStart = &mapStart;

    EXPECT_NO_THROW(sk.Invalidate());
    EXPECT_EQ(mapStart.status, Token::INVALID);
}

// Test Invalidate with only pKey set, others null
TEST_F(SimpleKeyTest_510, InvalidateWithOnlyPKeySet_510) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);

    Token key(Token::KEY, mark);
    key.status = Token::VALID;
    sk.pKey = &key;

    EXPECT_NO_THROW(sk.Invalidate());
    EXPECT_EQ(key.status, Token::INVALID);
}

// Test that Invalidate on already INVALID tokens doesn't crash
TEST_F(SimpleKeyTest_510, InvalidateOnAlreadyInvalidTokens_510) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);

    Scanner::IndentMarker indent(0, Scanner::IndentMarker::MAP);
    indent.status = Scanner::IndentMarker::INVALID;

    Token mapStart(Token::BLOCK_MAP_START, mark);
    mapStart.status = Token::INVALID;

    Token key(Token::KEY, mark);
    key.status = Token::INVALID;

    sk.pIndent = &indent;
    sk.pMapStart = &mapStart;
    sk.pKey = &key;

    EXPECT_NO_THROW(sk.Invalidate());
    EXPECT_EQ(indent.status, Scanner::IndentMarker::INVALID);
    EXPECT_EQ(mapStart.status, Token::INVALID);
    EXPECT_EQ(key.status, Token::INVALID);
}

// Test constructor with different flow levels
TEST_F(SimpleKeyTest_510, ConstructorWithZeroFlowLevel_510) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);
    EXPECT_EQ(sk.flowLevel, 0u);
}

TEST_F(SimpleKeyTest_510, ConstructorWithLargeFlowLevel_510) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 999999);
    EXPECT_EQ(sk.flowLevel, 999999u);
}

// Test Invalidate changes UNVERIFIED status tokens to INVALID
TEST_F(SimpleKeyTest_510, InvalidateChangesUnverifiedToInvalid_510) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);

    Token key(Token::KEY, mark);
    key.status = Token::UNVERIFIED;
    sk.pKey = &key;

    sk.Invalidate();
    EXPECT_EQ(key.status, Token::INVALID);
}

// Test that calling Invalidate multiple times is safe
TEST_F(SimpleKeyTest_510, InvalidateCalledMultipleTimes_510) {
    Mark mark;
    Scanner::SimpleKey sk(mark, 0);

    Token key(Token::KEY, mark);
    key.status = Token::VALID;
    sk.pKey = &key;

    sk.Invalidate();
    EXPECT_EQ(key.status, Token::INVALID);

    // Call again - should still be INVALID and not crash
    sk.Invalidate();
    EXPECT_EQ(key.status, Token::INVALID);
}

}  // namespace YAML
