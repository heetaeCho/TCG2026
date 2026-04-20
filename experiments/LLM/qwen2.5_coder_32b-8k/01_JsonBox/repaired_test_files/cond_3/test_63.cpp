#include <gtest/gtest.h>
#include <sstream>
#include "JsonBox/Value.h"
using namespace JsonBox;

// Assuming JsonParsingError is defined in a header file that needs to be included.
// For the sake of this example, we will include it from a hypothetical location.
// If it's defined elsewhere, adjust the include path accordingly.
#include "JsonBox/JsonParsingError.h"

TEST(ValueTest_63, LoadFromStream_ValidString_63) {
    std::istringstream input("\"valid_string\"");
    Value value;
    EXPECT_NO_THROW(value.loadFromStream(input));
    EXPECT_TRUE(value.isString());
    EXPECT_EQ("valid_string", value.getString());
}

TEST(ValueTest_63, LoadFromStream_EmptyObject_63) {
    std::istringstream input("{}");
    Value value;
    EXPECT_NO_THROW(value.loadFromStream(input));
    EXPECT_TRUE(value.isObject());
    EXPECT_EQ(0u, value.getObject().size());
}

TEST(ValueTest_63, LoadFromStream_ValidNumber_63) {
    std::istringstream input("12345");
    Value value;
    EXPECT_NO_THROW(value.loadFromStream(input));
    EXPECT_TRUE(value.isInteger());
    EXPECT_EQ(12345, value.getInteger());
}

TEST(ValueTest_63, LoadFromStream_ValidBooleanTrue_63) {
    std::istringstream input("true");
    Value value;
    EXPECT_NO_THROW(value.loadFromStream(input));
    EXPECT_TRUE(value.isBoolean());
    EXPECT_TRUE(value.getBoolean());
}

TEST(ValueTest_63, LoadFromStream_ValidBooleanFalse_63) {
    std::istringstream input("false");
    Value value;
    EXPECT_NO_THROW(value.loadFromStream(input));
    EXPECT_TRUE(value.isBoolean());
    EXPECT_FALSE(value.getBoolean());
}

TEST(ValueTest_63, LoadFromStream_NullValue_63) {
    std::istringstream input("null");
    Value value;
    EXPECT_NO_THROW(value.loadFromStream(input));
    EXPECT_TRUE(value.isNull());
}

TEST(ValueTest_63, LoadFromStream_ValidArray_63) {
    std::istringstream input("[1, 2, 3]");
    Value value;
    EXPECT_NO_THROW(value.loadFromStream(input));
    EXPECT_TRUE(value.isArray());
    const Array& array = value.getArray();
    EXPECT_EQ(3u, array.size());
    EXPECT_TRUE(array[0].isInteger() && array[0].getInteger() == 1);
    EXPECT_TRUE(array[1].isInteger() && array[1].getInteger() == 2);
    EXPECT_TRUE(array[2].isInteger() && array[2].getInteger() == 3);
}

TEST(ValueTest_63, LoadFromStream_UTF8EncodingError_63) {
    std::istringstream input("\x80\x80");
    Value value;
    EXPECT_THROW(value.loadFromStream(input), std::invalid_argument);
}

TEST(ValueTest_63, LoadFromStream_InvalidCharacterError_63) {
    std::istringstream input("{ invalid }");
    Value value;
    EXPECT_THROW(value.loadFromStream(input), JsonParsingError);
}

TEST(ValueTest_63, LoadFromStream_TruncatedInputString_63) {
    std::istringstream input("\"truncated");
    Value value;
    EXPECT_THROW(value.loadFromStream(input), JsonParsingError);
}

TEST(ValueTest_63, LoadFromStream_TruncatedObject_63) {
    std::istringstream input("{ \"key\": ");
    Value value;
    EXPECT_THROW(value.loadFromStream(input), JsonParsingError);
}

TEST(ValueTest_63, LoadFromStream_EmptyInput_63) {
    std::istringstream input("");
    Value value;
    EXPECT_THROW(value.loadFromStream(input), JsonParsingError);
}

TEST(ValueTest_63, LoadFromStream_EndsIncorrectly_63) {
    std::istringstream input("12345,");
    Value value;
    EXPECT_THROW(value.loadFromStream(input), JsonParsingError);
}