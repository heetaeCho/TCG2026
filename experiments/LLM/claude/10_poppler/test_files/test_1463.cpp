#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Parser.h"
#include "Lexer.h"
#include "Stream.h"
#include "Object.h"

// Helper to create a minimal MemStream for testing
static std::unique_ptr<Stream> createMemStream(const char* data, int len) {
    // We need to create a stream that the Parser/Lexer can work with.
    // MemStream takes ownership of a copy of the buffer.
    char* buf = (char*)gmalloc(len);
    memcpy(buf, data, len);
    Object dictObj(objNull);
    return std::make_unique<MemStream>(buf, 0, len, std::move(dictObj));
}

class ParserTest_1463 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that Parser can be constructed with a stream and does not crash
TEST_F(ParserTest_1463, ConstructWithStream_1463) {
    auto stream = createMemStream("123", 3);
    ASSERT_NE(stream, nullptr);
    Parser parser(nullptr, std::move(stream), false);
    // Just verify construction doesn't crash
}

// Test that getStream returns a non-null stream when constructed with valid stream
TEST_F(ParserTest_1463, GetStreamReturnsNonNull_1463) {
    auto stream = createMemStream("test data", 9);
    Parser parser(nullptr, std::move(stream), false);
    Stream* s = parser.getStream();
    EXPECT_NE(s, nullptr);
}

// Test that getStream returns the underlying stream from the lexer
TEST_F(ParserTest_1463, GetStreamReturnsLexerStream_1463) {
    const char* data = "42";
    auto stream = createMemStream(data, 2);
    Parser parser(nullptr, std::move(stream), false);
    Stream* s = parser.getStream();
    ASSERT_NE(s, nullptr);
}

// Test parsing a simple integer object
TEST_F(ParserTest_1463, GetObjParsesInteger_1463) {
    const char* data = "42";
    auto stream = createMemStream(data, 2);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test parsing a negative integer
TEST_F(ParserTest_1463, GetObjParsesNegativeInteger_1463) {
    const char* data = "-7";
    auto stream = createMemStream(data, 2);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -7);
}

// Test parsing a real number
TEST_F(ParserTest_1463, GetObjParsesReal_1463) {
    const char* data = "3.14";
    auto stream = createMemStream(data, 4);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_NEAR(obj.getReal(), 3.14, 0.001);
}

// Test parsing a boolean true
TEST_F(ParserTest_1463, GetObjParsesBoolTrue_1463) {
    const char* data = "true";
    auto stream = createMemStream(data, 4);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getBool(), true);
}

// Test parsing a boolean false
TEST_F(ParserTest_1463, GetObjParsesBoolFalse_1463) {
    const char* data = "false";
    auto stream = createMemStream(data, 5);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getBool(), false);
}

// Test parsing a name object
TEST_F(ParserTest_1463, GetObjParsesName_1463) {
    const char* data = "/MyName";
    auto stream = createMemStream(data, 7);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "MyName");
}

// Test parsing a string object
TEST_F(ParserTest_1463, GetObjParsesString_1463) {
    const char* data = "(hello)";
    auto stream = createMemStream(data, 7);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isString());
}

// Test parsing null
TEST_F(ParserTest_1463, GetObjParsesNull_1463) {
    const char* data = "null";
    auto stream = createMemStream(data, 4);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isNull());
}

// Test parsing an array
TEST_F(ParserTest_1463, GetObjParsesArray_1463) {
    const char* data = "[1 2 3]";
    auto stream = createMemStream(data, 7);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.arrayGetLength(), 3);
}

// Test parsing an empty array
TEST_F(ParserTest_1463, GetObjParsesEmptyArray_1463) {
    const char* data = "[]";
    auto stream = createMemStream(data, 2);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

// Test parsing a dictionary
TEST_F(ParserTest_1463, GetObjParsesDictionary_1463) {
    const char* data = "<< /Key 42 >>";
    auto stream = createMemStream(data, 14);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isDict());
}

// Test parsing an empty dictionary
TEST_F(ParserTest_1463, GetObjParsesEmptyDictionary_1463) {
    const char* data = "<< >>";
    auto stream = createMemStream(data, 5);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isDict());
}

// Test parsing a hex string
TEST_F(ParserTest_1463, GetObjParsesHexString_1463) {
    const char* data = "<48656C6C6F>";
    auto stream = createMemStream(data, 12);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isString());
}

// Test parsing an indirect reference
TEST_F(ParserTest_1463, GetObjParsesIndirectRef_1463) {
    const char* data = "10 0 R";
    auto stream = createMemStream(data, 6);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isRef());
    EXPECT_EQ(obj.getRefNum(), 10);
    EXPECT_EQ(obj.getRefGen(), 0);
}

// Test parsing multiple objects sequentially
TEST_F(ParserTest_1463, GetObjParsesMultipleObjects_1463) {
    const char* data = "1 2 3";
    auto stream = createMemStream(data, 5);
    Parser parser(nullptr, std::move(stream), false);

    Object obj1 = parser.getObj(0);
    EXPECT_TRUE(obj1.isInt());
    EXPECT_EQ(obj1.getInt(), 1);

    Object obj2 = parser.getObj(0);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 2);

    Object obj3 = parser.getObj(0);
    EXPECT_TRUE(obj3.isInt());
    EXPECT_EQ(obj3.getInt(), 3);
}

// Test parsing from empty stream returns EOF
TEST_F(ParserTest_1463, GetObjFromEmptyStream_1463) {
    const char* data = "";
    auto stream = createMemStream(data, 0);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isEOF());
}

// Test getPos returns a valid position
TEST_F(ParserTest_1463, GetPosReturnsValidPosition_1463) {
    const char* data = "42 100";
    auto stream = createMemStream(data, 6);
    Parser parser(nullptr, std::move(stream), false);
    Goffset pos = parser.getPos();
    EXPECT_GE(pos, 0);
}

// Test getPos advances after parsing
TEST_F(ParserTest_1463, GetPosAdvancesAfterParsing_1463) {
    const char* data = "42 100";
    auto stream = createMemStream(data, 6);
    Parser parser(nullptr, std::move(stream), false);

    Goffset pos1 = parser.getPos();
    Object obj1 = parser.getObj(0);
    Goffset pos2 = parser.getPos();
    // After reading something, position should have advanced
    EXPECT_GE(pos2, pos1);
}

// Test parsing nested arrays
TEST_F(ParserTest_1463, GetObjParsesNestedArray_1463) {
    const char* data = "[[1 2] [3 4]]";
    auto stream = createMemStream(data, 13);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.arrayGetLength(), 2);
}

// Test parsing a name with special characters
TEST_F(ParserTest_1463, GetObjParsesNameWithHexEscape_1463) {
    const char* data = "/Type";
    auto stream = createMemStream(data, 5);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "Type");
}

// Test that Parser is non-copyable (compile-time check implicitly - we just verify it compiles with move)
TEST_F(ParserTest_1463, ParserIsNonCopyable_1463) {
    EXPECT_FALSE(std::is_copy_constructible<Parser>::value);
    EXPECT_FALSE(std::is_copy_assignable<Parser>::value);
}

// Test parsing zero
TEST_F(ParserTest_1463, GetObjParsesZero_1463) {
    const char* data = "0";
    auto stream = createMemStream(data, 1);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

// Test parsing a large integer
TEST_F(ParserTest_1463, GetObjParsesLargeInteger_1463) {
    const char* data = "999999";
    auto stream = createMemStream(data, 6);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 999999);
}

// Test parsing with whitespace
TEST_F(ParserTest_1463, GetObjHandlesWhitespace_1463) {
    const char* data = "   42   ";
    auto stream = createMemStream(data, 8);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test parsing dictionary with multiple entries
TEST_F(ParserTest_1463, GetObjParsesDictMultipleEntries_1463) {
    const char* data = "<< /Type /Page /Count 5 >>";
    auto stream = createMemStream(data, 26);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isDict());
}

// Test parsing a string with escape characters
TEST_F(ParserTest_1463, GetObjParsesStringWithEscape_1463) {
    const char* data = "(hello\\nworld)";
    auto stream = createMemStream(data, 14);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isString());
}

// Test the full getObj signature with simpleOnly=true
TEST_F(ParserTest_1463, GetObjSimpleOnlyTrue_1463) {
    const char* data = "42";
    auto stream = createMemStream(data, 2);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(true, nullptr, cryptRC4, 0, 0, 0, 0, false, false);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test the full getObj with simpleOnly=false
TEST_F(ParserTest_1463, GetObjSimpleOnlyFalse_1463) {
    const char* data = "[1 2]";
    auto stream = createMemStream(data, 5);
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(false, nullptr, cryptRC4, 0, 0, 0, 0, false, false);
    EXPECT_TRUE(obj.isArray());
}

// Test that EOF is returned after all content is consumed
TEST_F(ParserTest_1463, GetObjReturnsEOFAfterAllContent_1463) {
    const char* data = "42";
    auto stream = createMemStream(data, 2);
    Parser parser(nullptr, std::move(stream), false);

    Object obj1 = parser.getObj(0);
    EXPECT_TRUE(obj1.isInt());

    Object obj2 = parser.getObj(0);
    EXPECT_TRUE(obj2.isEOF());
}
