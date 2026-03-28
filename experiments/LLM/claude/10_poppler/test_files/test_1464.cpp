#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Parser.h"
#include "Lexer.h"
#include "Stream.h"
#include "Object.h"

// Helper to create a MemStream from a string buffer
class ParserTest_1464 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a Parser from a string
    std::unique_ptr<Parser> createParserFromString(const char* data, int len) {
        // Create a MemStream from the data
        // Note: MemStream does not take ownership of the buffer, so we need to keep it alive
        Object obj(new MemStream(const_cast<char*>(data), 0, len, Object(objNull)));
        auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, Object(objNull));
        return std::make_unique<Parser>(nullptr, std::move(stream), false);
    }
};

// Test that Parser can be constructed with a stream and does not crash
TEST_F(ParserTest_1464, ConstructWithStream_1464) {
    const char data[] = "123";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    ASSERT_NO_THROW({
        Parser parser(nullptr, std::move(stream), false);
    });
}

// Test that getPos returns a valid position (non-negative) after construction
TEST_F(ParserTest_1464, GetPosAfterConstruction_1464) {
    const char data[] = "42 0 obj\n<< >>\nendobj";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Goffset pos = parser.getPos();
    EXPECT_GE(pos, 0);
}

// Test getObj with simple integer
TEST_F(ParserTest_1464, GetObjSimpleInteger_1464) {
    const char data[] = "42";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test getObj with simple real number
TEST_F(ParserTest_1464, GetObjSimpleReal_1464) {
    const char data[] = "3.14";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_NEAR(obj.getReal(), 3.14, 0.001);
}

// Test getObj with boolean true
TEST_F(ParserTest_1464, GetObjBoolTrue_1464) {
    const char data[] = "true";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBool());
}

// Test getObj with boolean false
TEST_F(ParserTest_1464, GetObjBoolFalse_1464) {
    const char data[] = "false";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

// Test getObj with a name object
TEST_F(ParserTest_1464, GetObjName_1464) {
    const char data[] = "/Type";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "Type");
}

// Test getObj with a string
TEST_F(ParserTest_1464, GetObjString_1464) {
    const char data[] = "(Hello World)";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isString());
}

// Test getObj with null
TEST_F(ParserTest_1464, GetObjNull_1464) {
    const char data[] = "null";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isNull());
}

// Test getObj with an array
TEST_F(ParserTest_1464, GetObjArray_1464) {
    const char data[] = "[1 2 3]";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.arrayGetLength(), 3);
}

// Test getObj with a dictionary
TEST_F(ParserTest_1464, GetObjDict_1464) {
    const char data[] = "<< /Key /Value >>";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isDict());
}

// Test getObj returns EOF at end of stream
TEST_F(ParserTest_1464, GetObjEOF_1464) {
    const char data[] = "";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, 0, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isEOF());
}

// Test multiple getObj calls
TEST_F(ParserTest_1464, GetObjMultipleCalls_1464) {
    const char data[] = "1 2 3";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
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

// Test getPos changes after parsing objects
TEST_F(ParserTest_1464, GetPosChangesAfterParsing_1464) {
    const char data[] = "100 200 300";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);

    Goffset pos1 = parser.getPos();
    parser.getObj(0);
    Goffset pos2 = parser.getPos();
    // After parsing, position should have advanced
    EXPECT_GE(pos2, pos1);
}

// Test getObj with negative integer
TEST_F(ParserTest_1464, GetObjNegativeInteger_1464) {
    const char data[] = "-42";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -42);
}

// Test getObj with hex string
TEST_F(ParserTest_1464, GetObjHexString_1464) {
    const char data[] = "<48656C6C6F>";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isString());
}

// Test getObj with nested array
TEST_F(ParserTest_1464, GetObjNestedArray_1464) {
    const char data[] = "[[1 2] [3 4]]";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.arrayGetLength(), 2);
}

// Test getObj with empty array
TEST_F(ParserTest_1464, GetObjEmptyArray_1464) {
    const char data[] = "[]";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

// Test getObj with empty dictionary
TEST_F(ParserTest_1464, GetObjEmptyDict_1464) {
    const char data[] = "<< >>";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isDict());
}

// Test getObj with zero
TEST_F(ParserTest_1464, GetObjZero_1464) {
    const char data[] = "0";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

// Test allowStreams parameter set to true
TEST_F(ParserTest_1464, ConstructWithAllowStreamsTrue_1464) {
    const char data[] = "42";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    ASSERT_NO_THROW({
        Parser parser(nullptr, std::move(stream), true);
    });
}

// Test getStream returns a non-null stream
TEST_F(ParserTest_1464, GetStreamReturnsNonNull_1464) {
    const char data[] = "42";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Stream* s = parser.getStream();
    EXPECT_NE(s, nullptr);
}

// Test mixed types in sequence
TEST_F(ParserTest_1464, GetObjMixedTypes_1464) {
    const char data[] = "42 3.14 /Name (string) true";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);

    Object obj1 = parser.getObj(0);
    EXPECT_TRUE(obj1.isInt());
    EXPECT_EQ(obj1.getInt(), 42);

    Object obj2 = parser.getObj(0);
    EXPECT_TRUE(obj2.isReal());

    Object obj3 = parser.getObj(0);
    EXPECT_TRUE(obj3.isName());

    Object obj4 = parser.getObj(0);
    EXPECT_TRUE(obj4.isString());

    Object obj5 = parser.getObj(0);
    EXPECT_TRUE(obj5.isBool());
}

// Test indirect reference
TEST_F(ParserTest_1464, GetObjIndirectRef_1464) {
    const char data[] = "10 0 R";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isRef());
    EXPECT_EQ(obj.getRefNum(), 10);
    EXPECT_EQ(obj.getRefGen(), 0);
}

// Test getObj with large integer
TEST_F(ParserTest_1464, GetObjLargeInteger_1464) {
    const char data[] = "999999";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 999999);
}

// Test dictionary with multiple keys
TEST_F(ParserTest_1464, GetObjDictMultipleKeys_1464) {
    const char data[] = "<< /Type /Catalog /Pages 3 0 R >>";
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, sizeof(data) - 1, Object(objNull));
    Parser parser(nullptr, std::move(stream), false);
    Object obj = parser.getObj(0);
    EXPECT_TRUE(obj.isDict());
}
