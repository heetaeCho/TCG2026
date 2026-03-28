#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

#include "Lexer.h"
#include "Stream.h"
#include "Object.h"
#include "Dict.h"
#include "Array.h"
#include "XRef.h"
#include "PDFDoc.h"

// Helper to create a MemStream from a string buffer
class LexerTest_1457 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll create lexers per test as needed
    }

    void TearDown() override {
    }

    // Helper: create a Lexer from a C string
    std::unique_ptr<Lexer> createLexerFromString(const char *data, int len) {
        // MemStream takes ownership semantics vary; we need a persistent buffer
        char *buf = (char *)gmalloc(len + 1);
        memcpy(buf, data, len);
        buf[len] = '\0';

        Object dictObj(new Dict(nullptr));
        auto stream = std::make_unique<MemStream>(buf, 0, len, std::move(dictObj));
        stream->reset();
        return std::make_unique<Lexer>(nullptr, std::move(stream));
    }
};

// Test that Lexer can be constructed with a stream and parse a simple integer
TEST_F(LexerTest_1457, ParseSimpleInteger_1457) {
    const char *data = "42";
    auto lexer = createLexerFromString(data, strlen(data));
    ASSERT_NE(lexer, nullptr);

    Object obj = lexer->getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test parsing a negative integer
TEST_F(LexerTest_1457, ParseNegativeInteger_1457) {
    const char *data = "-7";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj = lexer->getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -7);
}

// Test parsing a real number
TEST_F(LexerTest_1457, ParseRealNumber_1457) {
    const char *data = "3.14";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj = lexer->getObj(0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_NEAR(obj.getReal(), 3.14, 0.001);
}

// Test parsing a simple name object
TEST_F(LexerTest_1457, ParseNameObject_1457) {
    const char *data = "/MyName";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj = lexer->getObj(0);
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "MyName");
}

// Test parsing a string in parentheses
TEST_F(LexerTest_1457, ParseStringObject_1457) {
    const char *data = "(Hello World)";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj = lexer->getObj(0);
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getString()->toStr(), "Hello World");
}

// Test parsing boolean true
TEST_F(LexerTest_1457, ParseBoolTrue_1457) {
    const char *data = "true";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj = lexer->getObj(0);
    EXPECT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBool());
}

// Test parsing boolean false
TEST_F(LexerTest_1457, ParseBoolFalse_1457) {
    const char *data = "false";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj = lexer->getObj(0);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

// Test parsing null
TEST_F(LexerTest_1457, ParseNull_1457) {
    const char *data = "null";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj = lexer->getObj(0);
    EXPECT_TRUE(obj.isNull());
}

// Test parsing multiple tokens sequentially
TEST_F(LexerTest_1457, ParseMultipleTokens_1457) {
    const char *data = "42 /Name (string)";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj1 = lexer->getObj(0);
    EXPECT_TRUE(obj1.isInt());
    EXPECT_EQ(obj1.getInt(), 42);

    Object obj2 = lexer->getObj(0);
    EXPECT_TRUE(obj2.isName());
    EXPECT_STREQ(obj2.getName(), "Name");

    Object obj3 = lexer->getObj(0);
    EXPECT_TRUE(obj3.isString());
    EXPECT_EQ(obj3.getString()->toStr(), "string");
}

// Test parsing an empty stream returns EOF
TEST_F(LexerTest_1457, ParseEmptyStreamReturnsEOF_1457) {
    const char *data = "";
    auto lexer = createLexerFromString(data, 0);
    
    Object obj = lexer->getObj(0);
    EXPECT_TRUE(obj.isEOF());
}

// Test isSpace for common whitespace characters
TEST_F(LexerTest_1457, IsSpaceForWhitespace_1457) {
    EXPECT_TRUE(Lexer::isSpace(' '));
    EXPECT_TRUE(Lexer::isSpace('\t'));
    EXPECT_TRUE(Lexer::isSpace('\n'));
    EXPECT_TRUE(Lexer::isSpace('\r'));
    EXPECT_TRUE(Lexer::isSpace('\f'));
    EXPECT_TRUE(Lexer::isSpace('\0'));
}

// Test isSpace for non-whitespace characters
TEST_F(LexerTest_1457, IsSpaceForNonWhitespace_1457) {
    EXPECT_FALSE(Lexer::isSpace('a'));
    EXPECT_FALSE(Lexer::isSpace('Z'));
    EXPECT_FALSE(Lexer::isSpace('1'));
    EXPECT_FALSE(Lexer::isSpace('/'));
    EXPECT_FALSE(Lexer::isSpace('('));
}

// Test getStream returns non-null for a valid lexer
TEST_F(LexerTest_1457, GetStreamReturnsValidStream_1457) {
    const char *data = "123";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Stream *stream = lexer->getStream();
    EXPECT_NE(stream, nullptr);
}

// Test hasXRef returns false when constructed with null XRef
TEST_F(LexerTest_1457, HasXRefReturnsFalseWhenNull_1457) {
    const char *data = "123";
    auto lexer = createLexerFromString(data, strlen(data));
    
    EXPECT_FALSE(lexer->hasXRef());
}

// Test getXRef returns nullptr when constructed with null XRef
TEST_F(LexerTest_1457, GetXRefReturnsNullWhenNull_1457) {
    const char *data = "123";
    auto lexer = createLexerFromString(data, strlen(data));
    
    EXPECT_EQ(lexer->getXRef(), nullptr);
}

// Test parsing a hex string
TEST_F(LexerTest_1457, ParseHexString_1457) {
    const char *data = "<48656C6C6F>";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj = lexer->getObj(0);
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getString()->toStr(), "Hello");
}

// Test parsing array markers
TEST_F(LexerTest_1457, ParseArrayBrackets_1457) {
    const char *data = "[ 1 2 3 ]";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj1 = lexer->getObj(0);
    EXPECT_TRUE(obj1.isCmd());
    EXPECT_STREQ(obj1.getCmd(), "[");

    Object obj2 = lexer->getObj(0);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 1);

    Object obj3 = lexer->getObj(0);
    EXPECT_TRUE(obj3.isInt());
    EXPECT_EQ(obj3.getInt(), 2);

    Object obj4 = lexer->getObj(0);
    EXPECT_TRUE(obj4.isInt());
    EXPECT_EQ(obj4.getInt(), 3);

    Object obj5 = lexer->getObj(0);
    EXPECT_TRUE(obj5.isCmd());
    EXPECT_STREQ(obj5.getCmd(), "]");
}

// Test parsing dict markers
TEST_F(LexerTest_1457, ParseDictBrackets_1457) {
    const char *data = "<< /Key 42 >>";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj1 = lexer->getObj(0);
    EXPECT_TRUE(obj1.isCmd());
    EXPECT_STREQ(obj1.getCmd(), "<<");

    Object obj2 = lexer->getObj(0);
    EXPECT_TRUE(obj2.isName());
    EXPECT_STREQ(obj2.getName(), "Key");

    Object obj3 = lexer->getObj(0);
    EXPECT_TRUE(obj3.isInt());
    EXPECT_EQ(obj3.getInt(), 42);

    Object obj4 = lexer->getObj(0);
    EXPECT_TRUE(obj4.isCmd());
    EXPECT_STREQ(obj4.getCmd(), ">>");
}

// Test skipToNextLine moves past the current line
TEST_F(LexerTest_1457, SkipToNextLine_1457) {
    const char *data = "ignorethis\n42";
    auto lexer = createLexerFromString(data, strlen(data));
    
    lexer->skipToNextLine();
    
    Object obj = lexer->getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test skipChar advances position
TEST_F(LexerTest_1457, SkipCharAdvancesPosition_1457) {
    const char *data = "  42";
    auto lexer = createLexerFromString(data, strlen(data));
    
    // Skip the first two spaces
    lexer->skipChar();
    lexer->skipChar();
    
    Object obj = lexer->getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test parsing a zero value
TEST_F(LexerTest_1457, ParseZeroInteger_1457) {
    const char *data = "0";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj = lexer->getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

// Test parsing a reference-like pattern (e.g., "1 0 R")
TEST_F(LexerTest_1457, ParseReferenceTokens_1457) {
    const char *data = "1 0 R";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj1 = lexer->getObj(0);
    EXPECT_TRUE(obj1.isInt());
    EXPECT_EQ(obj1.getInt(), 1);

    Object obj2 = lexer->getObj(0);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 0);

    Object obj3 = lexer->getObj(0);
    EXPECT_TRUE(obj3.isCmd());
    EXPECT_STREQ(obj3.getCmd(), "R");
}

// Test parsing an empty hex string
TEST_F(LexerTest_1457, ParseEmptyHexString_1457) {
    const char *data = "<>";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj = lexer->getObj(0);
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getString()->toStr(), "");
}

// Test parsing an empty parenthesized string
TEST_F(LexerTest_1457, ParseEmptyParenString_1457) {
    const char *data = "()";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj = lexer->getObj(0);
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getString()->toStr(), "");
}

// Test parsing a string with escaped characters
TEST_F(LexerTest_1457, ParseStringWithEscapes_1457) {
    const char *data = "(Hello\\nWorld)";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj = lexer->getObj(0);
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getString()->toStr(), "Hello\nWorld");
}

// Test parsing name with hex escape
TEST_F(LexerTest_1457, ParseNameWithHexEscape_1457) {
    const char *data = "/Name#20Space";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj = lexer->getObj(0);
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "Name Space");
}

// Test parsing with comments (% to end of line)
TEST_F(LexerTest_1457, ParseWithComment_1457) {
    const char *data = "%this is a comment\n42";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj = lexer->getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test isSpace returns false for EOF sentinel
TEST_F(LexerTest_1457, IsSpaceForEOF_1457) {
    EXPECT_FALSE(Lexer::isSpace(-1));
}

// Test parsing large integer
TEST_F(LexerTest_1457, ParseLargeInteger_1457) {
    const char *data = "2147483647";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj = lexer->getObj(0);
    // Could be int or int64 depending on implementation
    EXPECT_TRUE(obj.isInt() || obj.isInt64());
}

// Test getPos returns a valid position
TEST_F(LexerTest_1457, GetPosReturnsValidPosition_1457) {
    const char *data = "42 100";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Goffset pos1 = lexer->getPos();
    EXPECT_GE(pos1, 0);
    
    Object obj = lexer->getObj(0);
    Goffset pos2 = lexer->getPos();
    // After reading a token, position should have advanced
    EXPECT_GE(pos2, pos1);
}

// Test parsing nested parentheses in strings
TEST_F(LexerTest_1457, ParseStringWithNestedParens_1457) {
    const char *data = "(Hello (nested) World)";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj = lexer->getObj(0);
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getString()->toStr(), "Hello (nested) World");
}

// Test consecutive EOF returns
TEST_F(LexerTest_1457, ConsecutiveEOFReturns_1457) {
    const char *data = "";
    auto lexer = createLexerFromString(data, 0);
    
    Object obj1 = lexer->getObj(0);
    EXPECT_TRUE(obj1.isEOF());
    
    Object obj2 = lexer->getObj(0);
    EXPECT_TRUE(obj2.isEOF());
}

// Test parsing only whitespace returns EOF
TEST_F(LexerTest_1457, ParseOnlyWhitespaceReturnsEOF_1457) {
    const char *data = "   \t\n\r  ";
    auto lexer = createLexerFromString(data, strlen(data));
    
    Object obj = lexer->getObj(0);
    EXPECT_TRUE(obj.isEOF());
}
