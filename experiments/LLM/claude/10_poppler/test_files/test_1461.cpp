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
class LexerTest_1461 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Helper to create a MemStream from a string buffer
static std::unique_ptr<Stream> makeMemStream(const char *data, int length) {
    // We need to create a stream from the data
    // MemStream takes ownership considerations vary; we copy the data
    char *buf = (char *)gmalloc(length + 1);
    memcpy(buf, data, length);
    buf[length] = '\0';
    Object dictObj(new Dict(nullptr));
    return std::make_unique<MemStream>(buf, 0, length, std::move(dictObj));
}

// Test that getXRef returns the XRef pointer passed during construction
TEST_F(LexerTest_1461, GetXRefReturnsCorrectPointer_1461) {
    const char *data = "123";
    auto stream = makeMemStream(data, strlen(data));
    XRef *xref = nullptr; // Using nullptr as XRef for simplicity
    Lexer lexer(xref, std::move(stream));
    EXPECT_EQ(lexer.getXRef(), xref);
}

// Test that hasXRef returns false when XRef is null
TEST_F(LexerTest_1461, HasXRefReturnsFalseWhenNull_1461) {
    const char *data = "test";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    EXPECT_FALSE(lexer.hasXRef());
}

// Test that getObj can parse an integer
TEST_F(LexerTest_1461, GetObjParsesInteger_1461) {
    const char *data = "42";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test that getObj can parse a negative integer
TEST_F(LexerTest_1461, GetObjParsesNegativeInteger_1461) {
    const char *data = "-7";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -7);
}

// Test that getObj can parse a real number
TEST_F(LexerTest_1461, GetObjParsesReal_1461) {
    const char *data = "3.14";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_NEAR(obj.getReal(), 3.14, 0.001);
}

// Test that getObj can parse a boolean true
TEST_F(LexerTest_1461, GetObjParsesBoolTrue_1461) {
    const char *data = "true";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBool());
}

// Test that getObj can parse a boolean false
TEST_F(LexerTest_1461, GetObjParsesBoolFalse_1461) {
    const char *data = "false";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

// Test that getObj can parse a name
TEST_F(LexerTest_1461, GetObjParsesName_1461) {
    const char *data = "/MyName";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "MyName");
}

// Test that getObj can parse a string in parentheses
TEST_F(LexerTest_1461, GetObjParsesString_1461) {
    const char *data = "(Hello World)";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isString());
}

// Test that getObj can parse a hex string
TEST_F(LexerTest_1461, GetObjParsesHexString_1461) {
    const char *data = "<48656C6C6F>";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isString());
}

// Test that getObj can parse null
TEST_F(LexerTest_1461, GetObjParsesNull_1461) {
    const char *data = "null";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isNull());
}

// Test that getObj returns EOF at end of stream
TEST_F(LexerTest_1461, GetObjReturnsEOFAtEnd_1461) {
    const char *data = "";
    auto stream = makeMemStream(data, 0);
    Lexer lexer(nullptr, std::move(stream));
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isEOF());
}

// Test parsing multiple objects sequentially
TEST_F(LexerTest_1461, GetObjParsesMultipleObjects_1461) {
    const char *data = "42 3.14 true";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));

    Object obj1 = lexer.getObj(0);
    EXPECT_TRUE(obj1.isInt());
    EXPECT_EQ(obj1.getInt(), 42);

    Object obj2 = lexer.getObj(0);
    EXPECT_TRUE(obj2.isReal());
    EXPECT_NEAR(obj2.getReal(), 3.14, 0.001);

    Object obj3 = lexer.getObj(0);
    EXPECT_TRUE(obj3.isBool());
    EXPECT_TRUE(obj3.getBool());
}

// Test that isSpace recognizes space characters
TEST_F(LexerTest_1461, IsSpaceRecognizesSpaceChars_1461) {
    EXPECT_TRUE(Lexer::isSpace(' '));
    EXPECT_TRUE(Lexer::isSpace('\t'));
    EXPECT_TRUE(Lexer::isSpace('\n'));
    EXPECT_TRUE(Lexer::isSpace('\r'));
    EXPECT_TRUE(Lexer::isSpace('\f'));
    EXPECT_TRUE(Lexer::isSpace('\0'));
}

// Test that isSpace returns false for non-space characters
TEST_F(LexerTest_1461, IsSpaceReturnsFalseForNonSpace_1461) {
    EXPECT_FALSE(Lexer::isSpace('a'));
    EXPECT_FALSE(Lexer::isSpace('1'));
    EXPECT_FALSE(Lexer::isSpace('/'));
    EXPECT_FALSE(Lexer::isSpace('('));
    EXPECT_FALSE(Lexer::isSpace(')'));
}

// Test that getStream returns a valid stream pointer
TEST_F(LexerTest_1461, GetStreamReturnsNonNull_1461) {
    const char *data = "test";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    Stream *s = lexer.getStream();
    EXPECT_NE(s, nullptr);
}

// Test skipToNextLine functionality
TEST_F(LexerTest_1461, SkipToNextLineSkipsContent_1461) {
    const char *data = "ignore this\n42";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    lexer.skipToNextLine();
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test skipToNextLine with carriage return
TEST_F(LexerTest_1461, SkipToNextLineWithCR_1461) {
    const char *data = "skip\r99";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    lexer.skipToNextLine();
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 99);
}

// Test parsing array-like tokens (open bracket)
TEST_F(LexerTest_1461, GetObjParsesArrayOpen_1461) {
    const char *data = "[";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isCmd());
}

// Test parsing a PDF command/operator
TEST_F(LexerTest_1461, GetObjParsesCommand_1461) {
    const char *data = "BT";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "BT");
}

// Test parsing with leading whitespace
TEST_F(LexerTest_1461, GetObjSkipsLeadingWhitespace_1461) {
    const char *data = "   100";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 100);
}

// Test parsing with comments
TEST_F(LexerTest_1461, GetObjSkipsComments_1461) {
    const char *data = "% this is a comment\n55";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 55);
}

// Test parsing zero
TEST_F(LexerTest_1461, GetObjParsesZero_1461) {
    const char *data = "0";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

// Test parsing an empty name
TEST_F(LexerTest_1461, GetObjParsesEmptyName_1461) {
    const char *data = "/ ";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isName());
}

// Test parsing a string with escape sequences
TEST_F(LexerTest_1461, GetObjParsesStringWithEscapes_1461) {
    const char *data = "(Hello\\nWorld)";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isString());
}

// Test parsing nested parentheses in string
TEST_F(LexerTest_1461, GetObjParsesNestedParenString_1461) {
    const char *data = "(Hello (World))";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isString());
}

// Test that isSpace returns false for EOF indicator
TEST_F(LexerTest_1461, IsSpaceReturnsFalseForEOF_1461) {
    EXPECT_FALSE(Lexer::isSpace(-1));
}

// Test large integer parsing
TEST_F(LexerTest_1461, GetObjParsesLargeInteger_1461) {
    const char *data = "999999";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 999999);
}

// Test getPos returns a valid position
TEST_F(LexerTest_1461, GetPosReturnsValidPosition_1461) {
    const char *data = "42 55";
    auto stream = makeMemStream(data, strlen(data));
    Lexer lexer(nullptr, std::move(stream));
    
    // Read first object
    Object obj1 = lexer.getObj(0);
    Goffset pos = lexer.getPos();
    // Position should have advanced past "42"
    EXPECT_GE(pos, 0);
}
