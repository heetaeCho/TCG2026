#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <cstring>

#include "Parser.h"
#include "Object.h"
#include "Stream.h"
#include "Decrypt.h"
#include "GooString.h"
#include "Lexer.h"
#include "XRef.h"

// Since decryptedString is a static function in Parser.cc, we cannot directly test it
// from outside the translation unit. Instead, we test the Parser class through its
// public interface.

// We'll test the Parser class which is the public interface defined in Parser.h

class ParserTest_1534 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Helper to create a Parser from a string buffer
static std::unique_ptr<Parser> createParserFromString(const char *data, size_t len, XRef *xref = nullptr) {
    Object strObj(std::make_unique<MemStream>(const_cast<char *>(data), 0, len, Object::null()));
    auto lexer = std::make_unique<Lexer>(xref, &strObj);
    return std::make_unique<Parser>(xref, std::move(lexer), false);
}

// Test parsing a simple integer
TEST_F(ParserTest_1534, ParseInteger_1534) {
    const char *data = "42";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test parsing a negative integer
TEST_F(ParserTest_1534, ParseNegativeInteger_1534) {
    const char *data = "-7";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -7);
}

// Test parsing a real number
TEST_F(ParserTest_1534, ParseReal_1534) {
    const char *data = "3.14";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isReal());
    EXPECT_NEAR(obj.getReal(), 3.14, 0.001);
}

// Test parsing a boolean true
TEST_F(ParserTest_1534, ParseBoolTrue_1534) {
    const char *data = "true";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBool());
}

// Test parsing a boolean false
TEST_F(ParserTest_1534, ParseBoolFalse_1534) {
    const char *data = "false";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

// Test parsing a name
TEST_F(ParserTest_1534, ParseName_1534) {
    const char *data = "/MyName";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "MyName");
}

// Test parsing a string literal
TEST_F(ParserTest_1534, ParseStringLiteral_1534) {
    const char *data = "(Hello World)";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getString()->toStr(), "Hello World");
}

// Test parsing a hex string
TEST_F(ParserTest_1534, ParseHexString_1534) {
    const char *data = "<48656C6C6F>";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getHexString()->toStr(), "Hello");
}

// Test parsing null
TEST_F(ParserTest_1534, ParseNull_1534) {
    const char *data = "null";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isNull());
}

// Test parsing an array
TEST_F(ParserTest_1534, ParseArray_1534) {
    const char *data = "[1 2 3]";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.arrayGetLength(), 3);
}

// Test parsing an empty array
TEST_F(ParserTest_1534, ParseEmptyArray_1534) {
    const char *data = "[]";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

// Test parsing a dictionary
TEST_F(ParserTest_1534, ParseDictionary_1534) {
    const char *data = "<< /Type /Catalog /Pages 3 0 R >>";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isDict());
}

// Test parsing an empty dictionary
TEST_F(ParserTest_1534, ParseEmptyDictionary_1534) {
    const char *data = "<< >>";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.dictGetLength(), 0);
}

// Test parsing an indirect reference
TEST_F(ParserTest_1534, ParseIndirectReference_1534) {
    const char *data = "10 0 R";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isRef());
    EXPECT_EQ(obj.getRefNum(), 10);
    EXPECT_EQ(obj.getRefGen(), 0);
}

// Test parsing multiple objects sequentially
TEST_F(ParserTest_1534, ParseMultipleObjects_1534) {
    const char *data = "42 (hello) /Name";
    auto parser = createParserFromString(data, strlen(data));
    
    Object obj1 = parser->getObj();
    EXPECT_TRUE(obj1.isInt());
    EXPECT_EQ(obj1.getInt(), 42);
    
    Object obj2 = parser->getObj();
    EXPECT_TRUE(obj2.isString());
    EXPECT_EQ(obj2.getString()->toStr(), "hello");
    
    Object obj3 = parser->getObj();
    EXPECT_TRUE(obj3.isName());
    EXPECT_STREQ(obj3.getName(), "Name");
}

// Test parsing EOF
TEST_F(ParserTest_1534, ParseEOF_1534) {
    const char *data = "";
    auto parser = createParserFromString(data, 0);
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isEOF());
}

// Test parsing a zero integer
TEST_F(ParserTest_1534, ParseZero_1534) {
    const char *data = "0";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

// Test parsing an empty string literal
TEST_F(ParserTest_1534, ParseEmptyStringLiteral_1534) {
    const char *data = "()";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getString()->toStr(), "");
}

// Test parsing an empty hex string
TEST_F(ParserTest_1534, ParseEmptyHexString_1534) {
    const char *data = "<>";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getHexString()->toStr(), "");
}

// Test parsing nested arrays
TEST_F(ParserTest_1534, ParseNestedArray_1534) {
    const char *data = "[[1 2] [3 4]]";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.arrayGetLength(), 2);
}

// Test parsing a dictionary with multiple entries
TEST_F(ParserTest_1534, ParseDictionaryMultipleEntries_1534) {
    const char *data = "<< /Key1 (Value1) /Key2 42 /Key3 true >>";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.dictGetLength(), 3);
}

// Test parsing a name with hex-encoded characters
TEST_F(ParserTest_1534, ParseNameWithHexEncoding_1534) {
    const char *data = "/A#42";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "AB");
}

// Test parsing a large integer
TEST_F(ParserTest_1534, ParseLargeInteger_1534) {
    const char *data = "2147483647";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    // Could be int or int64 depending on implementation
    EXPECT_TRUE(obj.isInt() || obj.isInt64());
}

// Test parsing string with escape sequences
TEST_F(ParserTest_1534, ParseStringWithEscapes_1534) {
    const char *data = "(Hello\\nWorld)";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getString()->toStr(), "Hello\nWorld");
}

// Test parsing an array with mixed types
TEST_F(ParserTest_1534, ParseMixedArray_1534) {
    const char *data = "[1 3.14 (hello) /Name true null]";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.arrayGetLength(), 6);
}

// Test that getPos works on the parser's stream
TEST_F(ParserTest_1534, ParserGetPos_1534) {
    const char *data = "42 100";
    auto parser = createParserFromString(data, strlen(data));
    
    Object obj1 = parser->getObj();
    EXPECT_TRUE(obj1.isInt());
    
    // After reading first object, position should have advanced
    Goffset pos = parser->getPos();
    EXPECT_GT(pos, 0);
}

// Test parsing a reference with higher generation number
TEST_F(ParserTest_1534, ParseReferenceHighGen_1534) {
    const char *data = "5 3 R";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isRef());
    EXPECT_EQ(obj.getRefNum(), 5);
    EXPECT_EQ(obj.getRefGen(), 3);
}

// Test parsing nested dictionaries
TEST_F(ParserTest_1534, ParseNestedDictionary_1534) {
    const char *data = "<< /Outer << /Inner 42 >> >>";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isDict());
    Object inner = obj.dictLookup("Outer");
    EXPECT_TRUE(inner.isDict());
}

// Test parsing string with parentheses
TEST_F(ParserTest_1534, ParseStringWithParentheses_1534) {
    const char *data = "(Hello (World))";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getString()->toStr(), "Hello (World)");
}

// Test parsing a real number with leading dot
TEST_F(ParserTest_1534, ParseRealLeadingDot_1534) {
    const char *data = ".5";
    auto parser = createParserFromString(data, strlen(data));
    Object obj = parser->getObj();
    EXPECT_TRUE(obj.isReal() || obj.isInt());
    if (obj.isReal()) {
        EXPECT_NEAR(obj.getReal(), 0.5, 0.001);
    }
}
