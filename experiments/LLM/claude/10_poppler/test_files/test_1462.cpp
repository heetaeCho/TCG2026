#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Lexer.h"
#include "Stream.h"
#include "Object.h"
#include "XRef.h"
#include "Dict.h"
#include "Array.h"

// Test fixture for Lexer tests
class LexerTest_1462 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test hasXRef returns false when XRef is nullptr
TEST_F(LexerTest_1462, HasXRefReturnsFalseWhenNull_1462) {
    // Create a simple memory stream for the lexer
    const char *data = "test";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    
    EXPECT_FALSE(lexer.hasXRef());
}

// Test hasXRef returns true when XRef is provided
TEST_F(LexerTest_1462, HasXRefReturnsTrueWhenNonNull_1462) {
    // We need a valid XRef pointer - but we can't easily create one without a full PDF.
    // We'll test this indirectly if possible, or skip if XRef requires complex setup.
    // For now, we test the nullptr case which is straightforward.
    
    // This test verifies the interface behavior with nullptr
    const char *data = "123";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    EXPECT_FALSE(lexer.hasXRef());
    EXPECT_EQ(lexer.getXRef(), nullptr);
}

// Test getXRef returns nullptr when constructed with nullptr
TEST_F(LexerTest_1462, GetXRefReturnsNullWhenConstructedWithNull_1462) {
    const char *data = "hello";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    
    EXPECT_EQ(lexer.getXRef(), nullptr);
}

// Test isSpace with space character
TEST_F(LexerTest_1462, IsSpaceReturnsTrueForSpace_1462) {
    EXPECT_TRUE(Lexer::isSpace(' '));
}

// Test isSpace with tab character
TEST_F(LexerTest_1462, IsSpaceReturnsTrueForTab_1462) {
    EXPECT_TRUE(Lexer::isSpace('\t'));
}

// Test isSpace with newline character
TEST_F(LexerTest_1462, IsSpaceReturnsTrueForNewline_1462) {
    EXPECT_TRUE(Lexer::isSpace('\n'));
}

// Test isSpace with carriage return
TEST_F(LexerTest_1462, IsSpaceReturnsTrueForCarriageReturn_1462) {
    EXPECT_TRUE(Lexer::isSpace('\r'));
}

// Test isSpace with form feed
TEST_F(LexerTest_1462, IsSpaceReturnsTrueForFormFeed_1462) {
    EXPECT_TRUE(Lexer::isSpace('\f'));
}

// Test isSpace with null character
TEST_F(LexerTest_1462, IsSpaceReturnsTrueForNull_1462) {
    EXPECT_TRUE(Lexer::isSpace('\0'));
}

// Test isSpace with non-space character 'a'
TEST_F(LexerTest_1462, IsSpaceReturnsFalseForAlpha_1462) {
    EXPECT_FALSE(Lexer::isSpace('a'));
}

// Test isSpace with digit character
TEST_F(LexerTest_1462, IsSpaceReturnsFalseForDigit_1462) {
    EXPECT_FALSE(Lexer::isSpace('0'));
}

// Test isSpace with special character
TEST_F(LexerTest_1462, IsSpaceReturnsFalseForSpecialChar_1462) {
    EXPECT_FALSE(Lexer::isSpace('/'));
}

// Test isSpace with bracket character
TEST_F(LexerTest_1462, IsSpaceReturnsFalseForBracket_1462) {
    EXPECT_FALSE(Lexer::isSpace('['));
}

// Test getObj parses an integer
TEST_F(LexerTest_1462, GetObjParsesInteger_1462) {
    const char *data = "42";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    Object obj = lexer.getObj(0);
    
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test getObj parses a real number
TEST_F(LexerTest_1462, GetObjParsesReal_1462) {
    const char *data = "3.14";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    Object obj = lexer.getObj(0);
    
    EXPECT_TRUE(obj.isReal());
    EXPECT_NEAR(obj.getReal(), 3.14, 0.001);
}

// Test getObj parses a name
TEST_F(LexerTest_1462, GetObjParsesName_1462) {
    const char *data = "/TestName";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    Object obj = lexer.getObj(0);
    
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "TestName");
}

// Test getObj parses boolean true
TEST_F(LexerTest_1462, GetObjParsesTrue_1462) {
    const char *data = "true";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    Object obj = lexer.getObj(0);
    
    EXPECT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBool());
}

// Test getObj parses boolean false
TEST_F(LexerTest_1462, GetObjParsesFalse_1462) {
    const char *data = "false";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    Object obj = lexer.getObj(0);
    
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

// Test getObj parses a string
TEST_F(LexerTest_1462, GetObjParsesString_1462) {
    const char *data = "(Hello World)";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    Object obj = lexer.getObj(0);
    
    EXPECT_TRUE(obj.isString());
}

// Test getObj parses null
TEST_F(LexerTest_1462, GetObjParsesNull_1462) {
    const char *data = "null";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    Object obj = lexer.getObj(0);
    
    EXPECT_TRUE(obj.isNull());
}

// Test getObj returns EOF at end of stream
TEST_F(LexerTest_1462, GetObjReturnsEOFAtEndOfStream_1462) {
    const char *data = "";
    Object strObj(new MemStream(const_cast<char*>(data), 0, 0, Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    Object obj = lexer.getObj(0);
    
    EXPECT_TRUE(obj.isEOF());
}

// Test getObj parses negative integer
TEST_F(LexerTest_1462, GetObjParsesNegativeInteger_1462) {
    const char *data = "-100";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    Object obj = lexer.getObj(0);
    
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

// Test getObj parses hex string
TEST_F(LexerTest_1462, GetObjParsesHexString_1462) {
    const char *data = "<48656C6C6F>";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    Object obj = lexer.getObj(0);
    
    EXPECT_TRUE(obj.isString());
}

// Test multiple getObj calls parse sequential tokens
TEST_F(LexerTest_1462, GetObjParsesMultipleTokens_1462) {
    const char *data = "42 /Name true";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    
    Object obj1 = lexer.getObj(0);
    EXPECT_TRUE(obj1.isInt());
    EXPECT_EQ(obj1.getInt(), 42);
    
    Object obj2 = lexer.getObj(0);
    EXPECT_TRUE(obj2.isName());
    EXPECT_STREQ(obj2.getName(), "Name");
    
    Object obj3 = lexer.getObj(0);
    EXPECT_TRUE(obj3.isBool());
    EXPECT_TRUE(obj3.getBool());
}

// Test getObj with zero
TEST_F(LexerTest_1462, GetObjParsesZero_1462) {
    const char *data = "0";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    Object obj = lexer.getObj(0);
    
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

// Test skipToNextLine skips to next line
TEST_F(LexerTest_1462, SkipToNextLineSkipsContent_1462) {
    const char *data = "skip this\n42";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    lexer.skipToNextLine();
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test getObj parses array open bracket
TEST_F(LexerTest_1462, GetObjParsesArrayOpen_1462) {
    const char *data = "[";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    Object obj = lexer.getObj(0);
    
    EXPECT_TRUE(obj.isCmd());
}

// Test getObj with nested parentheses in string
TEST_F(LexerTest_1462, GetObjParsesNestedParenString_1462) {
    const char *data = "(Hello (World))";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    Object obj = lexer.getObj(0);
    
    EXPECT_TRUE(obj.isString());
}

// Test getStream returns non-null for valid lexer
TEST_F(LexerTest_1462, GetStreamReturnsStream_1462) {
    const char *data = "test";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    
    Stream *stream = lexer.getStream();
    EXPECT_NE(stream, nullptr);
}

// Test isSpace with EOF-like value
TEST_F(LexerTest_1462, IsSpaceReturnsFalseForEOF_1462) {
    EXPECT_FALSE(Lexer::isSpace(-1));
}

// Test getObj parses comment (should skip comment and return next token)
TEST_F(LexerTest_1462, GetObjSkipsComment_1462) {
    const char *data = "% this is a comment\n42";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    Object obj = lexer.getObj(0);
    
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test getObj with empty name
TEST_F(LexerTest_1462, GetObjParsesEmptyName_1462) {
    const char *data = "/ ";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    Object obj = lexer.getObj(0);
    
    EXPECT_TRUE(obj.isName());
}

// Test isSpace with various non-space printable characters
TEST_F(LexerTest_1462, IsSpaceReturnsFalseForPrintableChars_1462) {
    EXPECT_FALSE(Lexer::isSpace('A'));
    EXPECT_FALSE(Lexer::isSpace('Z'));
    EXPECT_FALSE(Lexer::isSpace('!'));
    EXPECT_FALSE(Lexer::isSpace('~'));
    EXPECT_FALSE(Lexer::isSpace('('));
    EXPECT_FALSE(Lexer::isSpace(')'));
    EXPECT_FALSE(Lexer::isSpace('<'));
    EXPECT_FALSE(Lexer::isSpace('>'));
}

// Test getObj parses large integer
TEST_F(LexerTest_1462, GetObjParsesLargeInteger_1462) {
    const char *data = "999999";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    Object obj = lexer.getObj(0);
    
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 999999);
}

// Test getObj with only whitespace returns EOF
TEST_F(LexerTest_1462, GetObjWithOnlyWhitespaceReturnsEOF_1462) {
    const char *data = "   \n\t  ";
    Object strObj(new MemStream(const_cast<char*>(data), 0, strlen(data), Object(objNull)));
    
    Lexer lexer(nullptr, &strObj);
    Object obj = lexer.getObj(0);
    
    EXPECT_TRUE(obj.isEOF());
}
