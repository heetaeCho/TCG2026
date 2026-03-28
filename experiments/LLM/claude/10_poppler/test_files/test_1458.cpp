#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Lexer.h"
#include "Object.h"
#include "Stream.h"
#include "Dict.h"
#include "XRef.h"

// Helper to create a MemStream from a string buffer
class LexerTest_1458 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a Lexer from a string
    std::unique_ptr<Lexer> createLexerFromString(const char* data, int len) {
        // Create a MemStream - note: the buffer must remain valid during the Lexer's lifetime
        Object dictObj = Object(new Dict(nullptr));
        auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
        return std::make_unique<Lexer>(nullptr, std::move(stream));
    }
};

// Test that getStream returns non-null when Lexer is constructed with a Stream
TEST_F(LexerTest_1458, GetStreamReturnsNonNullForStreamInput_1458) {
    const char* data = "123";
    int len = 3;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Stream* s = lexer.getStream();
    EXPECT_NE(s, nullptr);
}

// Test isSpace with space character
TEST_F(LexerTest_1458, IsSpaceWithSpaceChar_1458) {
    EXPECT_TRUE(Lexer::isSpace(' '));
}

// Test isSpace with tab character
TEST_F(LexerTest_1458, IsSpaceWithTabChar_1458) {
    EXPECT_TRUE(Lexer::isSpace('\t'));
}

// Test isSpace with newline character
TEST_F(LexerTest_1458, IsSpaceWithNewline_1458) {
    EXPECT_TRUE(Lexer::isSpace('\n'));
}

// Test isSpace with carriage return
TEST_F(LexerTest_1458, IsSpaceWithCarriageReturn_1458) {
    EXPECT_TRUE(Lexer::isSpace('\r'));
}

// Test isSpace with form feed
TEST_F(LexerTest_1458, IsSpaceWithFormFeed_1458) {
    EXPECT_TRUE(Lexer::isSpace('\f'));
}

// Test isSpace with null character (PDF considers \0 as whitespace)
TEST_F(LexerTest_1458, IsSpaceWithNullChar_1458) {
    EXPECT_TRUE(Lexer::isSpace('\0'));
}

// Test isSpace with non-space character
TEST_F(LexerTest_1458, IsSpaceWithNonSpaceChar_1458) {
    EXPECT_FALSE(Lexer::isSpace('a'));
}

// Test isSpace with digit
TEST_F(LexerTest_1458, IsSpaceWithDigit_1458) {
    EXPECT_FALSE(Lexer::isSpace('0'));
}

// Test isSpace with special character
TEST_F(LexerTest_1458, IsSpaceWithSpecialChar_1458) {
    EXPECT_FALSE(Lexer::isSpace('/'));
}

// Test isSpace with EOF
TEST_F(LexerTest_1458, IsSpaceWithEOF_1458) {
    // EOF is typically -1, should not be considered space
    EXPECT_FALSE(Lexer::isSpace(EOF));
}

// Test getObj returns integer object for integer token
TEST_F(LexerTest_1458, GetObjReturnsIntegerForIntegerToken_1458) {
    const char* data = "42";
    int len = 2;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj();
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test getObj returns real object for real token
TEST_F(LexerTest_1458, GetObjReturnsRealForRealToken_1458) {
    const char* data = "3.14";
    int len = 4;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj();
    EXPECT_TRUE(obj.isNum());
    EXPECT_NEAR(obj.getNum(), 3.14, 0.001);
}

// Test getObj returns name for name token
TEST_F(LexerTest_1458, GetObjReturnsNameForNameToken_1458) {
    const char* data = "/Name";
    int len = 5;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj();
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "Name");
}

// Test getObj returns string for string token
TEST_F(LexerTest_1458, GetObjReturnsStringForStringToken_1458) {
    const char* data = "(Hello)";
    int len = 7;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj();
    EXPECT_TRUE(obj.isString());
}

// Test getObj returns boolean true
TEST_F(LexerTest_1458, GetObjReturnsBoolTrue_1458) {
    const char* data = "true";
    int len = 4;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj();
    EXPECT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBool());
}

// Test getObj returns boolean false
TEST_F(LexerTest_1458, GetObjReturnsBoolFalse_1458) {
    const char* data = "false";
    int len = 5;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj();
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

// Test getObj returns null for null token
TEST_F(LexerTest_1458, GetObjReturnsNullForNullToken_1458) {
    const char* data = "null";
    int len = 4;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj();
    EXPECT_TRUE(obj.isNull());
}

// Test getObj returns EOF at end of stream
TEST_F(LexerTest_1458, GetObjReturnsEOFAtEndOfStream_1458) {
    const char* data = "";
    int len = 0;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj();
    EXPECT_TRUE(obj.isEOF());
}

// Test getObj with negative integer
TEST_F(LexerTest_1458, GetObjReturnsNegativeInteger_1458) {
    const char* data = "-10";
    int len = 3;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj();
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -10);
}

// Test getObj with hex string
TEST_F(LexerTest_1458, GetObjReturnsHexString_1458) {
    const char* data = "<48656C6C6F>";
    int len = 12;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj();
    EXPECT_TRUE(obj.isHexString());
}

// Test getObj with command token
TEST_F(LexerTest_1458, GetObjReturnsCmdForCommandToken_1458) {
    const char* data = "BT";
    int len = 2;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj();
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "BT");
}

// Test multiple tokens in sequence
TEST_F(LexerTest_1458, GetObjMultipleTokens_1458) {
    const char* data = "42 3.14 /Name";
    int len = 13;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj1 = lexer.getObj();
    EXPECT_TRUE(obj1.isInt());
    EXPECT_EQ(obj1.getInt(), 42);
    
    Object obj2 = lexer.getObj();
    EXPECT_TRUE(obj2.isNum());
    EXPECT_NEAR(obj2.getNum(), 3.14, 0.001);
    
    Object obj3 = lexer.getObj();
    EXPECT_TRUE(obj3.isName());
    EXPECT_STREQ(obj3.getName(), "Name");
}

// Test hasXRef returns false when constructed with null XRef
TEST_F(LexerTest_1458, HasXRefReturnsFalseForNullXRef_1458) {
    const char* data = "test";
    int len = 4;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    EXPECT_FALSE(lexer.hasXRef());
}

// Test getXRef returns null when constructed with null XRef
TEST_F(LexerTest_1458, GetXRefReturnsNullForNullXRef_1458) {
    const char* data = "test";
    int len = 4;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    EXPECT_EQ(lexer.getXRef(), nullptr);
}

// Test getObj with array delimiters
TEST_F(LexerTest_1458, GetObjReturnsArrayDelimiters_1458) {
    const char* data = "[ 1 2 ]";
    int len = 7;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj1 = lexer.getObj();
    EXPECT_TRUE(obj1.isCmd());
    EXPECT_STREQ(obj1.getCmd(), "[");
}

// Test skipToNextLine
TEST_F(LexerTest_1458, SkipToNextLineSkipsToNewline_1458) {
    const char* data = "first line\n42";
    int len = 13;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    lexer.skipToNextLine();
    Object obj = lexer.getObj();
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test getObj with whitespace-only input returns EOF
TEST_F(LexerTest_1458, GetObjReturnsEOFForWhitespaceOnlyInput_1458) {
    const char* data = "   \t\n  ";
    int len = 7;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj();
    EXPECT_TRUE(obj.isEOF());
}

// Test getObj with comment
TEST_F(LexerTest_1458, GetObjSkipsComment_1458) {
    const char* data = "% this is a comment\n42";
    int len = 22;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj();
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test getObj with zero
TEST_F(LexerTest_1458, GetObjReturnsZeroInteger_1458) {
    const char* data = "0";
    int len = 1;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj();
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

// Test getObj with empty name
TEST_F(LexerTest_1458, GetObjReturnsEmptyName_1458) {
    const char* data = "/ ";
    int len = 2;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj();
    EXPECT_TRUE(obj.isName());
}

// Test isSpace boundary values
TEST_F(LexerTest_1458, IsSpaceWithVariousNonSpaceChars_1458) {
    EXPECT_FALSE(Lexer::isSpace('A'));
    EXPECT_FALSE(Lexer::isSpace('Z'));
    EXPECT_FALSE(Lexer::isSpace('('));
    EXPECT_FALSE(Lexer::isSpace(')'));
    EXPECT_FALSE(Lexer::isSpace('<'));
    EXPECT_FALSE(Lexer::isSpace('>'));
    EXPECT_FALSE(Lexer::isSpace('['));
    EXPECT_FALSE(Lexer::isSpace(']'));
    EXPECT_FALSE(Lexer::isSpace('{'));
    EXPECT_FALSE(Lexer::isSpace('}'));
    EXPECT_FALSE(Lexer::isSpace('%'));
}

// Test getObj with nested parentheses in string
TEST_F(LexerTest_1458, GetObjReturnsStringWithNestedParens_1458) {
    const char* data = "(Hello (World))";
    int len = 15;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj();
    EXPECT_TRUE(obj.isString());
}

// Test getObj with negative real
TEST_F(LexerTest_1458, GetObjReturnsNegativeReal_1458) {
    const char* data = "-3.14";
    int len = 5;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj();
    EXPECT_TRUE(obj.isNum());
    EXPECT_NEAR(obj.getNum(), -3.14, 0.001);
}

// Test getPos returns a position
TEST_F(LexerTest_1458, GetPosReturnsPosition_1458) {
    const char* data = "42 hello";
    int len = 8;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Goffset pos = lexer.getPos();
    // Position should be >= 0
    EXPECT_GE(pos, 0);
}

// Test that reading a token advances position
TEST_F(LexerTest_1458, GetObjAdvancesPosition_1458) {
    const char* data = "42 hello";
    int len = 8;
    Object dictObj = Object(new Dict(nullptr));
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    Lexer lexer(nullptr, std::move(stream));
    
    Goffset posBefore = lexer.getPos();
    Object obj = lexer.getObj();
    Goffset posAfter = lexer.getPos();
    
    EXPECT_GT(posAfter, posBefore);
}
