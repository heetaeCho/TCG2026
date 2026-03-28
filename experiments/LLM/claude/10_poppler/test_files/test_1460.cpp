#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Lexer.h"
#include "Object.h"
#include "Stream.h"

// Mock Stream class for testing
class MockStream : public Stream {
public:
    MOCK_METHOD(StreamKind, getKind, (), (override));
    MOCK_METHOD(bool, rewind, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(int, getChar, (), (override));
    MOCK_METHOD(int, lookChar, (), (override));
    MOCK_METHOD(int, getRawChar, (), (override));
    MOCK_METHOD(void, getRawChars, (int nChars, int* buffer), (override));
    MOCK_METHOD(int, getUnfilteredChar, (), (override));
    MOCK_METHOD(bool, unfilteredRewind, (), (override));
    MOCK_METHOD(char*, getLine, (char* buf, int size), (override));
    MOCK_METHOD(unsigned int, discardChars, (unsigned int n), (override));
    MOCK_METHOD(Goffset, getPos, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char* indent), (override));
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
};

class LexerTest_1460 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test isSpace with space character
TEST_F(LexerTest_1460, IsSpaceWithSpaceChar_1460) {
    EXPECT_TRUE(Lexer::isSpace(' '));
}

// Test isSpace with tab character
TEST_F(LexerTest_1460, IsSpaceWithTabChar_1460) {
    EXPECT_TRUE(Lexer::isSpace('\t'));
}

// Test isSpace with newline character
TEST_F(LexerTest_1460, IsSpaceWithNewlineChar_1460) {
    EXPECT_TRUE(Lexer::isSpace('\n'));
}

// Test isSpace with carriage return
TEST_F(LexerTest_1460, IsSpaceWithCarriageReturn_1460) {
    EXPECT_TRUE(Lexer::isSpace('\r'));
}

// Test isSpace with form feed
TEST_F(LexerTest_1460, IsSpaceWithFormFeed_1460) {
    EXPECT_TRUE(Lexer::isSpace('\f'));
}

// Test isSpace with null character (PDF considers it whitespace)
TEST_F(LexerTest_1460, IsSpaceWithNullChar_1460) {
    EXPECT_TRUE(Lexer::isSpace('\0'));
}

// Test isSpace with non-space character 'A'
TEST_F(LexerTest_1460, IsSpaceWithNonSpaceCharA_1460) {
    EXPECT_FALSE(Lexer::isSpace('A'));
}

// Test isSpace with non-space character '0'
TEST_F(LexerTest_1460, IsSpaceWithDigitChar_1460) {
    EXPECT_FALSE(Lexer::isSpace('0'));
}

// Test isSpace with non-space character '/'
TEST_F(LexerTest_1460, IsSpaceWithSlash_1460) {
    EXPECT_FALSE(Lexer::isSpace('/'));
}

// Test isSpace with non-space character '%'
TEST_F(LexerTest_1460, IsSpaceWithPercent_1460) {
    EXPECT_FALSE(Lexer::isSpace('%'));
}

// Test isSpace with EOF marker (-1)
TEST_F(LexerTest_1460, IsSpaceWithEOF_1460) {
    EXPECT_FALSE(Lexer::isSpace(-1));
}

// Test isSpace with special PDF delimiter characters
TEST_F(LexerTest_1460, IsSpaceWithOpenParen_1460) {
    EXPECT_FALSE(Lexer::isSpace('('));
}

TEST_F(LexerTest_1460, IsSpaceWithCloseParen_1460) {
    EXPECT_FALSE(Lexer::isSpace(')'));
}

TEST_F(LexerTest_1460, IsSpaceWithOpenAngleBracket_1460) {
    EXPECT_FALSE(Lexer::isSpace('<'));
}

TEST_F(LexerTest_1460, IsSpaceWithCloseAngleBracket_1460) {
    EXPECT_FALSE(Lexer::isSpace('>'));
}

TEST_F(LexerTest_1460, IsSpaceWithOpenSquareBracket_1460) {
    EXPECT_FALSE(Lexer::isSpace('['));
}

TEST_F(LexerTest_1460, IsSpaceWithCloseSquareBracket_1460) {
    EXPECT_FALSE(Lexer::isSpace(']'));
}

TEST_F(LexerTest_1460, IsSpaceWithOpenCurlyBrace_1460) {
    EXPECT_FALSE(Lexer::isSpace('{'));
}

TEST_F(LexerTest_1460, IsSpaceWithCloseCurlyBrace_1460) {
    EXPECT_FALSE(Lexer::isSpace('}'));
}

// Test Lexer construction with stream and basic operations
TEST_F(LexerTest_1460, ConstructWithStreamAndGetXRef_1460) {
    // Create a MemStream or use a mock for basic construction test
    // Since we need a valid stream, we'll use a simple memory-based approach
    auto stream = std::make_unique<MockStream>();
    
    // Set up expectations for stream operations during Lexer construction
    EXPECT_CALL(*stream, rewind()).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*stream, getChar()).WillRepeatedly(testing::Return(-1));
    EXPECT_CALL(*stream, lookChar()).WillRepeatedly(testing::Return(-1));
    EXPECT_CALL(*stream, getDict()).WillRepeatedly(testing::Return(nullptr));
    EXPECT_CALL(*stream, getDictObject()).WillRepeatedly(testing::Return(nullptr));
    EXPECT_CALL(*stream, getKind()).WillRepeatedly(testing::Return(strWeird));
    EXPECT_CALL(*stream, close()).Times(testing::AnyNumber());
    EXPECT_CALL(*stream, getPos()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*stream, setPos(testing::_, testing::_)).Times(testing::AnyNumber());
    EXPECT_CALL(*stream, getBaseStream()).WillRepeatedly(testing::Return(nullptr));

    // nullptr XRef is acceptable for basic testing
    Lexer lexer(nullptr, std::move(stream));
    
    EXPECT_FALSE(lexer.hasXRef());
    EXPECT_EQ(lexer.getXRef(), nullptr);
}

// Test isSpace boundary - value 127
TEST_F(LexerTest_1460, IsSpaceWithHighAscii_1460) {
    EXPECT_FALSE(Lexer::isSpace(127));
}

// Test isSpace with printable character
TEST_F(LexerTest_1460, IsSpaceWithPrintableChar_1460) {
    EXPECT_FALSE(Lexer::isSpace('z'));
}

// Test isSpace with negative values other than -1
TEST_F(LexerTest_1460, IsSpaceWithNegativeValue_1460) {
    EXPECT_FALSE(Lexer::isSpace(-2));
}

// Test getObj returns EOF on empty stream
TEST_F(LexerTest_1460, GetObjReturnsEOFOnEmptyStream_1460) {
    auto stream = std::make_unique<MockStream>();
    
    EXPECT_CALL(*stream, rewind()).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*stream, getChar()).WillRepeatedly(testing::Return(-1));
    EXPECT_CALL(*stream, lookChar()).WillRepeatedly(testing::Return(-1));
    EXPECT_CALL(*stream, getDict()).WillRepeatedly(testing::Return(nullptr));
    EXPECT_CALL(*stream, getDictObject()).WillRepeatedly(testing::Return(nullptr));
    EXPECT_CALL(*stream, getKind()).WillRepeatedly(testing::Return(strWeird));
    EXPECT_CALL(*stream, close()).Times(testing::AnyNumber());
    EXPECT_CALL(*stream, getPos()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*stream, setPos(testing::_, testing::_)).Times(testing::AnyNumber());
    EXPECT_CALL(*stream, getBaseStream()).WillRepeatedly(testing::Return(nullptr));

    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isEOF());
}

// Test setPos calls stream setPos
TEST_F(LexerTest_1460, SetPosCallsStreamSetPos_1460) {
    auto stream = std::make_unique<MockStream>();
    
    EXPECT_CALL(*stream, rewind()).WillRepeatedly(testing::Return(true));
    EXPECT_CALL(*stream, getChar()).WillRepeatedly(testing::Return(-1));
    EXPECT_CALL(*stream, lookChar()).WillRepeatedly(testing::Return(-1));
    EXPECT_CALL(*stream, getDict()).WillRepeatedly(testing::Return(nullptr));
    EXPECT_CALL(*stream, getDictObject()).WillRepeatedly(testing::Return(nullptr));
    EXPECT_CALL(*stream, getKind()).WillRepeatedly(testing::Return(strWeird));
    EXPECT_CALL(*stream, close()).Times(testing::AnyNumber());
    EXPECT_CALL(*stream, getPos()).WillRepeatedly(testing::Return(0));
    EXPECT_CALL(*stream, setPos(testing::_, testing::_)).Times(testing::AnyNumber());
    EXPECT_CALL(*stream, getBaseStream()).WillRepeatedly(testing::Return(nullptr));

    Lexer lexer(nullptr, std::move(stream));
    
    // setPos should work without crashing
    lexer.setPos(100);
}
