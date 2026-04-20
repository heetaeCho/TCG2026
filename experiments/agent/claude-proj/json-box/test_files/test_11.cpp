#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueEscapeMinimumCharactersTest_11 : public ::testing::Test {
protected:
};

// Test escaping quotation mark
TEST_F(ValueEscapeMinimumCharactersTest_11, EscapesQuotationMark_11) {
    std::string input = "hello\"world";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("hello\\\"world", result);
}

// Test escaping reverse solidus (backslash)
TEST_F(ValueEscapeMinimumCharactersTest_11, EscapesReverseSolidus_11) {
    std::string input = "hello\\world";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("hello\\\\world", result);
}

// Test escaping backspace
TEST_F(ValueEscapeMinimumCharactersTest_11, EscapesBackspace_11) {
    std::string input = "hello\bworld";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("hello\\bworld", result);
}

// Test escaping form feed
TEST_F(ValueEscapeMinimumCharactersTest_11, EscapesFormFeed_11) {
    std::string input = "hello\fworld";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("hello\\fworld", result);
}

// Test escaping line feed (newline)
TEST_F(ValueEscapeMinimumCharactersTest_11, EscapesLineFeed_11) {
    std::string input = "hello\nworld";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("hello\\nworld", result);
}

// Test escaping carriage return
TEST_F(ValueEscapeMinimumCharactersTest_11, EscapesCarriageReturn_11) {
    std::string input = "hello\rworld";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("hello\\rworld", result);
}

// Test escaping tab
TEST_F(ValueEscapeMinimumCharactersTest_11, EscapesTab_11) {
    std::string input = "hello\tworld";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("hello\\tworld", result);
}

// Test empty string
TEST_F(ValueEscapeMinimumCharactersTest_11, EmptyString_11) {
    std::string input = "";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("", result);
}

// Test string with no special characters
TEST_F(ValueEscapeMinimumCharactersTest_11, NoSpecialCharacters_11) {
    std::string input = "hello world";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("hello world", result);
}

// Test control characters in range 0x00-0x1f that are not explicitly handled get unicode escaped
TEST_F(ValueEscapeMinimumCharactersTest_11, EscapesControlCharacterToUnicode_11) {
    // \x01 is a control character not explicitly handled (not \b, \f, \n, \r, \t)
    std::string input(1, '\x01');
    std::string result = Value::escapeMinimumCharacters(input);
    // Should be escaped to unicode format like \u0001
    EXPECT_EQ("\\u0001", result);
}

// Test another control character (0x1f)
TEST_F(ValueEscapeMinimumCharactersTest_11, EscapesControlChar0x1f_11) {
    std::string input(1, '\x1f');
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("\\u001f", result);
}

// Test null character (0x00)
TEST_F(ValueEscapeMinimumCharactersTest_11, EscapesNullCharacter_11) {
    std::string input(1, '\0');
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("\\u0000", result);
}

// Test multiple special characters together
TEST_F(ValueEscapeMinimumCharactersTest_11, MultipleSpecialCharacters_11) {
    std::string input = "\"\\\n\t";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("\\\"\\\\\\n\\t", result);
}

// Test string with mixed regular and special characters
TEST_F(ValueEscapeMinimumCharactersTest_11, MixedRegularAndSpecialCharacters_11) {
    std::string input = "key\t:\t\"value\"";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("key\\t:\\t\\\"value\\\"", result);
}

// Test that regular printable ASCII characters pass through unchanged
TEST_F(ValueEscapeMinimumCharactersTest_11, PrintableAsciiUnchanged_11) {
    std::string input = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ(input, result);
}

// Test special symbols that should NOT be escaped
TEST_F(ValueEscapeMinimumCharactersTest_11, NonEscapedSymbols_11) {
    std::string input = "!@#$%^&*()_+-=[]{}|;':,./<>?";
    std::string result = Value::escapeMinimumCharacters(input);
    // Only the characters that match special cases should be escaped
    // Here backslash is not in the input, single quote and other symbols should pass through
    // Actually let's be careful: this input doesn't contain " or backslash
    // Wait, it does contain ' but not " - single quote is not escaped
    EXPECT_NE(std::string::npos, result.find("!"));
    EXPECT_NE(std::string::npos, result.find("@"));
}

// Test only quotation marks
TEST_F(ValueEscapeMinimumCharactersTest_11, OnlyQuotationMarks_11) {
    std::string input = "\"\"\"";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("\\\"\\\"\\\"", result);
}

// Test only backslashes
TEST_F(ValueEscapeMinimumCharactersTest_11, OnlyBackslashes_11) {
    std::string input = "\\\\\\";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("\\\\\\\\\\\\", result);
}

// Test control character 0x02
TEST_F(ValueEscapeMinimumCharactersTest_11, EscapesControlChar0x02_11) {
    std::string input(1, '\x02');
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("\\u0002", result);
}

// Test character right at boundary - space (0x20) should NOT be escaped
TEST_F(ValueEscapeMinimumCharactersTest_11, SpaceNotEscaped_11) {
    std::string input = " ";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ(" ", result);
}

// Test all control characters from 0x00 to 0x1f that are not explicitly handled
TEST_F(ValueEscapeMinimumCharactersTest_11, AllNonExplicitControlCharsEscapedToUnicode_11) {
    // Characters that have explicit handling: \b(0x08), \f(0x0c), \n(0x0a), \r(0x0d), \t(0x09)
    // All others in 0x00-0x1f should be escaped to \uXXXX
    for (char c = '\x00'; c <= '\x1f'; ++c) {
        std::string input(1, c);
        std::string result = Value::escapeMinimumCharacters(input);
        // Result should not equal the raw character (everything in this range is escaped)
        EXPECT_NE(input, result) << "Character 0x" << std::hex << (int)(unsigned char)c << " was not escaped";
    }
}

// ========================
// Tests for Value class general functionality
// ========================

class ValueTest_11 : public ::testing::Test {
protected:
};

// Test default constructor creates null value
TEST_F(ValueTest_11, DefaultConstructorCreatesNull_11) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

// Test string constructor
TEST_F(ValueTest_11, StringConstructor_11) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("hello", v.getString());
}

// Test std::string constructor
TEST_F(ValueTest_11, StdStringConstructor_11) {
    std::string s = "world";
    Value v(s);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("world", v.getString());
}

// Test integer constructor
TEST_F(ValueTest_11, IntegerConstructor_11) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(42, v.getInteger());
}

// Test double constructor
TEST_F(ValueTest_11, DoubleConstructor_11) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(3.14, v.getDouble());
}

// Test boolean constructor
TEST_F(ValueTest_11, BooleanConstructorTrue_11) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_11, BooleanConstructorFalse_11) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

// Test copy constructor
TEST_F(ValueTest_11, CopyConstructor_11) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ("test", copy.getString());
}

// Test assignment from string
TEST_F(ValueTest_11, AssignmentFromString_11) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("assigned", v.getString());
}

// Test assignment from int
TEST_F(ValueTest_11, AssignmentFromInt_11) {
    Value v;
    v = 100;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(100, v.getInteger());
}

// Test assignment from double
TEST_F(ValueTest_11, AssignmentFromDouble_11) {
    Value v;
    v = 2.718;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(2.718, v.getDouble());
}

// Test assignment from bool
TEST_F(ValueTest_11, AssignmentFromBool_11) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

// Test setNull
TEST_F(ValueTest_11, SetNull_11) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// Test setString
TEST_F(ValueTest_11, SetString_11) {
    Value v;
    v.setString("new_string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("new_string", v.getString());
}

// Test setInteger
TEST_F(ValueTest_11, SetInteger_11) {
    Value v;
    v.setInteger(99);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(99, v.getInteger());
}

// Test setDouble
TEST_F(ValueTest_11, SetDouble_11) {
    Value v;
    v.setDouble(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(1.5, v.getDouble());
}

// Test setBoolean
TEST_F(ValueTest_11, SetBoolean_11) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

// Test isNumeric for integer
TEST_F(ValueTest_11, IsNumericForInteger_11) {
    Value v(10);
    EXPECT_TRUE(v.isNumeric());
}

// Test isNumeric for double
TEST_F(ValueTest_11, IsNumericForDouble_11) {
    Value v(1.0);
    EXPECT_TRUE(v.isNumeric());
}

// Test isNumeric for non-numeric
TEST_F(ValueTest_11, IsNumericForString_11) {
    Value v("not a number");
    EXPECT_FALSE(v.isNumeric());
}

// Test equality operator
TEST_F(ValueTest_11, EqualityOperator_11) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

// Test inequality operator
TEST_F(ValueTest_11, InequalityOperator_11) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

// Test object construction and access
TEST_F(ValueTest_11, ObjectConstructorAndAccess_11) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ("value", v["key"].getString());
}

// Test array construction and access
TEST_F(ValueTest_11, ArrayConstructorAndAccess_11) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(1, v[static_cast<size_t>(0)].getInteger());
    EXPECT_EQ(3, v[static_cast<size_t>(2)].getInteger());
}

// Test tryGetString with correct type
TEST_F(ValueTest_11, TryGetStringWithCorrectType_11) {
    Value v("hello");
    EXPECT_EQ("hello", v.tryGetString("default"));
}

// Test tryGetString with wrong type returns default
TEST_F(ValueTest_11, TryGetStringWithWrongType_11) {
    Value v(42);
    EXPECT_EQ("default", v.tryGetString("default"));
}

// Test tryGetInteger with correct type
TEST_F(ValueTest_11, TryGetIntegerWithCorrectType_11) {
    Value v(42);
    EXPECT_EQ(42, v.tryGetInteger(0));
}

// Test tryGetInteger with wrong type returns default
TEST_F(ValueTest_11, TryGetIntegerWithWrongType_11) {
    Value v("hello");
    EXPECT_EQ(-1, v.tryGetInteger(-1));
}

// Test tryGetDouble with correct type
TEST_F(ValueTest_11, TryGetDoubleWithCorrectType_11) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(3.14, v.tryGetDouble(0.0));
}

// Test tryGetBoolean with correct type
TEST_F(ValueTest_11, TryGetBooleanWithCorrectType_11) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

// Test tryGetBoolean with wrong type returns default
TEST_F(ValueTest_11, TryGetBooleanWithWrongType_11) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// Test loadFromString
TEST_F(ValueTest_11, LoadFromString_11) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ("value", v["key"].getString());
}

// Test loadFromString with integer
TEST_F(ValueTest_11, LoadFromStringInteger_11) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(42, v.getInteger());
}

// Test loadFromString with array
TEST_F(ValueTest_11, LoadFromStringArray_11) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(3u, v.getArray().size());
}

// Test loadFromString with boolean
TEST_F(ValueTest_11, LoadFromStringBoolean_11) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

// Test loadFromString with null
TEST_F(ValueTest_11, LoadFromStringNull_11) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

// Test loadFromStream
TEST_F(ValueTest_11, LoadFromStream_11) {
    Value v;
    std::istringstream stream("{\"a\": 1}");
    v.loadFromStream(stream);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(1, v["a"].getInteger());
}

// Test writeToStream
TEST_F(ValueTest_11, WriteToStream_11) {
    Value v(42);
    std::ostringstream output;
    v.writeToStream(output, false, false);
    EXPECT_EQ("42", output.str());
}

// Test writeToStream with string
TEST_F(ValueTest_11, WriteToStreamString_11) {
    Value v("hello");
    std::ostringstream output;
    v.writeToStream(output, false, false);
    EXPECT_EQ("\"hello\"", output.str());
}

// Test escapeToUnicode
TEST_F(ValueTest_11, EscapeToUnicode_11) {
    std::string result = Value::escapeToUnicode('\x01');
    EXPECT_EQ("\\u0001", result);
}

TEST_F(ValueTest_11, EscapeToUnicodeNull_11) {
    std::string result = Value::escapeToUnicode('\0');
    EXPECT_EQ("\\u0000", result);
}

// Test integer boundary: negative number
TEST_F(ValueTest_11, NegativeInteger_11) {
    Value v(-1);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(-1, v.getInteger());
}

// Test integer boundary: zero
TEST_F(ValueTest_11, ZeroInteger_11) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(0, v.getInteger());
}

// Test double boundary: zero
TEST_F(ValueTest_11, ZeroDouble_11) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(0.0, v.getDouble());
}

// Test negative double
TEST_F(ValueTest_11, NegativeDouble_11) {
    Value v(-99.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(-99.5, v.getDouble());
}

// Test getFloat
TEST_F(ValueTest_11, GetFloat_11) {
    Value v(1.5);
    EXPECT_FLOAT_EQ(1.5f, v.getFloat());
}

// Test comparison operators
TEST_F(ValueTest_11, LessThanOperator_11) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_11, LessThanOrEqualOperator_11) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_11, GreaterThanOperator_11) {
    Value v1(2);
    Value v2(1);
    EXPECT_TRUE(v1 > v2);
}

TEST_F(ValueTest_11, GreaterThanOrEqualOperator_11) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 >= v2);
}

// Test empty object
TEST_F(ValueTest_11, EmptyObject_11) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

// Test empty array
TEST_F(ValueTest_11, EmptyArray_11) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}

// Test setObject
TEST_F(ValueTest_11, SetObject_11) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(10, v["x"].getInteger());
}

// Test setArray
TEST_F(ValueTest_11, SetArray_11) {
    Value v;
    Array arr;
    arr.push_back(Value("item"));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ("item", v[static_cast<size_t>(0)].getString());
}

// Test isStringable
TEST_F(ValueTest_11, IsStringableForString_11) {
    Value v("test");
    EXPECT_TRUE(v.isStringable());
}

// Test operator<< (stream output)
TEST_F(ValueTest_11, StreamOutputOperator_11) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// Test escapeAllCharacters - normal ASCII should get unicode escaped
TEST_F(ValueTest_11, EscapeAllCharactersBasic_11) {
    std::string result = Value::escapeAllCharacters("a");
    // escapeAllCharacters should escape everything beyond the basic escapes
    // At minimum, control characters and possibly all non-ASCII
    EXPECT_FALSE(result.empty());
}

// Test escapeMinimumCharacters with high ASCII characters (>= 0x20, non-special)
TEST_F(ValueEscapeMinimumCharactersTest_11, HighAsciiPassThrough_11) {
    std::string input = "~"; // 0x7e
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("~", result);
}

// Test long string with multiple escape types
TEST_F(ValueEscapeMinimumCharactersTest_11, LongMixedString_11) {
    std::string input = "line1\nline2\ttab\r\nend\"quoted\"\\slash";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("line1\\nline2\\ttab\\r\\nend\\\"quoted\\\"\\\\slash", result);
}

// Test single character strings
TEST_F(ValueEscapeMinimumCharactersTest_11, SingleQuotationMark_11) {
    std::string input = "\"";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("\\\"", result);
}

TEST_F(ValueEscapeMinimumCharactersTest_11, SingleBackslash_11) {
    std::string input = "\\";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("\\\\", result);
}

TEST_F(ValueEscapeMinimumCharactersTest_11, SingleNewline_11) {
    std::string input = "\n";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_EQ("\\n", result);
}
