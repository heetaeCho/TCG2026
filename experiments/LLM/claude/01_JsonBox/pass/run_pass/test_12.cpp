#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "JsonBox/Value.h"

using namespace JsonBox;

// ============================================================
// Tests for escapeAllCharacters
// ============================================================

class ValueEscapeAllCharactersTest_12 : public ::testing::Test {
protected:
    // Helper to call the static method
    std::string escape(const std::string& str) {
        return Value::escapeAllCharacters(str);
    }
};

TEST_F(ValueEscapeAllCharactersTest_12, EmptyString_12) {
    EXPECT_EQ("", escape(""));
}

TEST_F(ValueEscapeAllCharactersTest_12, PlainAsciiText_12) {
    EXPECT_EQ("hello world", escape("hello world"));
}

TEST_F(ValueEscapeAllCharactersTest_12, QuotationMark_12) {
    EXPECT_EQ("\\\"", escape("\""));
}

TEST_F(ValueEscapeAllCharactersTest_12, ReverseSolidus_12) {
    EXPECT_EQ("\\\\", escape("\\"));
}

TEST_F(ValueEscapeAllCharactersTest_12, Solidus_12) {
    EXPECT_EQ("\\/", escape("/"));
}

TEST_F(ValueEscapeAllCharactersTest_12, Backspace_12) {
    EXPECT_EQ("\\b", escape("\b"));
}

TEST_F(ValueEscapeAllCharactersTest_12, FormFeed_12) {
    EXPECT_EQ("\\f", escape("\f"));
}

TEST_F(ValueEscapeAllCharactersTest_12, LineFeed_12) {
    EXPECT_EQ("\\n", escape("\n"));
}

TEST_F(ValueEscapeAllCharactersTest_12, CarriageReturn_12) {
    EXPECT_EQ("\\r", escape("\r"));
}

TEST_F(ValueEscapeAllCharactersTest_12, Tab_12) {
    EXPECT_EQ("\\t", escape("\t"));
}

TEST_F(ValueEscapeAllCharactersTest_12, ControlCharacterEscapedToUnicode_12) {
    // \x01 is a control character that should be escaped to unicode
    std::string input(1, '\x01');
    std::string result = escape(input);
    // Should start with \u00
    EXPECT_EQ(0u, result.find("\\u"));
    EXPECT_EQ(6u, result.size());
}

TEST_F(ValueEscapeAllCharactersTest_12, ControlCharacterNullEscapedToUnicode_12) {
    // Note: \x00 might or might not be handled depending on string construction
    // \x1f is the last control character before space
    std::string input(1, '\x1f');
    std::string result = escape(input);
    EXPECT_EQ(0u, result.find("\\u"));
    EXPECT_EQ(6u, result.size());
}

TEST_F(ValueEscapeAllCharactersTest_12, MultipleSpecialCharacters_12) {
    EXPECT_EQ("\\\"\\\\\\n\\t", escape("\"\\\n\t"));
}

TEST_F(ValueEscapeAllCharactersTest_12, MixedNormalAndSpecial_12) {
    EXPECT_EQ("hello\\nworld", escape("hello\nworld"));
}

TEST_F(ValueEscapeAllCharactersTest_12, AllSpecialCharsCombined_12) {
    std::string input = "\"\\/\b\f\n\r\t";
    std::string expected = "\\\"\\\\\\/\\b\\f\\n\\r\\t";
    EXPECT_EQ(expected, escape(input));
}

TEST_F(ValueEscapeAllCharactersTest_12, SpaceIsNotEscaped_12) {
    // Space (0x20) should NOT be escaped - it's above control character range
    EXPECT_EQ(" ", escape(" "));
}

TEST_F(ValueEscapeAllCharactersTest_12, PrintableAsciiNotEscaped_12) {
    std::string input = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    EXPECT_EQ(input, escape(input));
}

TEST_F(ValueEscapeAllCharactersTest_12, ControlChar0x02_12) {
    std::string input(1, '\x02');
    std::string result = escape(input);
    EXPECT_EQ(0u, result.find("\\u"));
}

TEST_F(ValueEscapeAllCharactersTest_12, ControlChar0x1e_12) {
    std::string input(1, '\x1e');
    std::string result = escape(input);
    EXPECT_EQ(0u, result.find("\\u"));
}

// ============================================================
// Tests for escapeMinimumCharacters
// ============================================================

class ValueEscapeMinimumCharactersTest_12 : public ::testing::Test {
protected:
    std::string escapeMin(const std::string& str) {
        return Value::escapeMinimumCharacters(str);
    }
};

TEST_F(ValueEscapeMinimumCharactersTest_12, EmptyString_12) {
    EXPECT_EQ("", escapeMin(""));
}

TEST_F(ValueEscapeMinimumCharactersTest_12, PlainText_12) {
    EXPECT_EQ("hello", escapeMin("hello"));
}

TEST_F(ValueEscapeMinimumCharactersTest_12, QuotationMark_12) {
    EXPECT_EQ("\\\"", escapeMin("\""));
}

TEST_F(ValueEscapeMinimumCharactersTest_12, ReverseSolidus_12) {
    EXPECT_EQ("\\\\", escapeMin("\\"));
}

TEST_F(ValueEscapeMinimumCharactersTest_12, LineFeed_12) {
    EXPECT_EQ("\\n", escapeMin("\n"));
}

TEST_F(ValueEscapeMinimumCharactersTest_12, CarriageReturn_12) {
    EXPECT_EQ("\\r", escapeMin("\r"));
}

TEST_F(ValueEscapeMinimumCharactersTest_12, Tab_12) {
    EXPECT_EQ("\\t", escapeMin("\t"));
}

// ============================================================
// Tests for escapeToUnicode
// ============================================================

class ValueEscapeToUnicodeTest_12 : public ::testing::Test {};

TEST_F(ValueEscapeToUnicodeTest_12, NullCharacter_12) {
    std::string result = Value::escapeToUnicode('\0');
    EXPECT_EQ("\\u0000", result);
}

TEST_F(ValueEscapeToUnicodeTest_12, ControlChar0x01_12) {
    std::string result = Value::escapeToUnicode('\x01');
    EXPECT_EQ("\\u0001", result);
}

TEST_F(ValueEscapeToUnicodeTest_12, ControlChar0x1f_12) {
    std::string result = Value::escapeToUnicode('\x1f');
    EXPECT_EQ("\\u001f", result);
}

TEST_F(ValueEscapeToUnicodeTest_12, ResultLength_12) {
    std::string result = Value::escapeToUnicode('\x0a');
    EXPECT_EQ(6u, result.size());
}

// ============================================================
// Tests for Value constructors and type checking
// ============================================================

class ValueConstructorTest_12 : public ::testing::Test {};

TEST_F(ValueConstructorTest_12, DefaultConstructorIsNull_12) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueConstructorTest_12, StringConstructor_12) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("hello", v.getString());
}

TEST_F(ValueConstructorTest_12, CStringConstructor_12) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("hello", v.getString());
}

TEST_F(ValueConstructorTest_12, IntConstructor_12) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(42, v.getInteger());
}

TEST_F(ValueConstructorTest_12, DoubleConstructor_12) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(3.14, v.getDouble());
}

TEST_F(ValueConstructorTest_12, BooleanConstructor_12) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueConstructorTest_12, BooleanConstructorFalse_12) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueConstructorTest_12, ObjectConstructor_12) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueConstructorTest_12, ArrayConstructor_12) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueConstructorTest_12, CopyConstructor_12) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(42, copy.getInteger());
}

// ============================================================
// Tests for type checking methods
// ============================================================

class ValueTypeCheckTest_12 : public ::testing::Test {};

TEST_F(ValueTypeCheckTest_12, NullIsNotString_12) {
    Value v;
    EXPECT_FALSE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTypeCheckTest_12, IntegerIsNumeric_12) {
    Value v(42);
    EXPECT_TRUE(v.isNumeric());
    EXPECT_TRUE(v.isInteger());
}

TEST_F(ValueTypeCheckTest_12, DoubleIsNumeric_12) {
    Value v(3.14);
    EXPECT_TRUE(v.isNumeric());
    EXPECT_TRUE(v.isDouble());
}

TEST_F(ValueTypeCheckTest_12, StringIsStringable_12) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

// ============================================================
// Tests for setters and getters
// ============================================================

class ValueSetGetTest_12 : public ::testing::Test {};

TEST_F(ValueSetGetTest_12, SetString_12) {
    Value v;
    v.setString("test");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("test", v.getString());
}

TEST_F(ValueSetGetTest_12, SetInteger_12) {
    Value v;
    v.setInteger(100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(100, v.getInteger());
}

TEST_F(ValueSetGetTest_12, SetDouble_12) {
    Value v;
    v.setDouble(2.718);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(2.718, v.getDouble());
}

TEST_F(ValueSetGetTest_12, SetBoolean_12) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueSetGetTest_12, SetNull_12) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueSetGetTest_12, SetObject_12) {
    Value v;
    Object obj;
    obj["key"] = Value("value");
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueSetGetTest_12, SetArray_12) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
}

TEST_F(ValueSetGetTest_12, GetFloat_12) {
    Value v(3.14);
    EXPECT_FLOAT_EQ(3.14f, v.getFloat());
}

// ============================================================
// Tests for try methods with default values
// ============================================================

class ValueTryGetTest_12 : public ::testing::Test {};

TEST_F(ValueTryGetTest_12, TryGetStringWhenString_12) {
    Value v("hello");
    EXPECT_EQ("hello", v.tryGetString("default"));
}

TEST_F(ValueTryGetTest_12, TryGetStringWhenNotString_12) {
    Value v(42);
    EXPECT_EQ("default", v.tryGetString("default"));
}

TEST_F(ValueTryGetTest_12, TryGetIntegerWhenInteger_12) {
    Value v(42);
    EXPECT_EQ(42, v.tryGetInteger(0));
}

TEST_F(ValueTryGetTest_12, TryGetIntegerWhenNotInteger_12) {
    Value v("hello");
    EXPECT_EQ(99, v.tryGetInteger(99));
}

TEST_F(ValueTryGetTest_12, TryGetDoubleWhenDouble_12) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(3.14, v.tryGetDouble(0.0));
}

TEST_F(ValueTryGetTest_12, TryGetDoubleWhenNotDouble_12) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(1.0, v.tryGetDouble(1.0));
}

TEST_F(ValueTryGetTest_12, TryGetBooleanWhenBoolean_12) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTryGetTest_12, TryGetBooleanWhenNotBoolean_12) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

TEST_F(ValueTryGetTest_12, TryGetFloatWhenDouble_12) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(2.5f, v.tryGetFloat(0.0f));
}

TEST_F(ValueTryGetTest_12, TryGetFloatWhenNotDouble_12) {
    Value v("hello");
    EXPECT_FLOAT_EQ(1.5f, v.tryGetFloat(1.5f));
}

// ============================================================
// Tests for assignment operators
// ============================================================

class ValueAssignmentTest_12 : public ::testing::Test {};

TEST_F(ValueAssignmentTest_12, AssignValue_12) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(42, v2.getInteger());
}

TEST_F(ValueAssignmentTest_12, AssignString_12) {
    Value v;
    v = std::string("test");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("test", v.getString());
}

TEST_F(ValueAssignmentTest_12, AssignCString_12) {
    Value v;
    v = "test";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("test", v.getString());
}

TEST_F(ValueAssignmentTest_12, AssignInt_12) {
    Value v;
    v = 42;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(42, v.getInteger());
}

TEST_F(ValueAssignmentTest_12, AssignDouble_12) {
    Value v;
    v = 3.14;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(3.14, v.getDouble());
}

TEST_F(ValueAssignmentTest_12, AssignBool_12) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueAssignmentTest_12, AssignObject_12) {
    Value v;
    Object obj;
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueAssignmentTest_12, AssignArray_12) {
    Value v;
    Array arr;
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ============================================================
// Tests for comparison operators
// ============================================================

class ValueComparisonTest_12 : public ::testing::Test {};

TEST_F(ValueComparisonTest_12, EqualIntegers_12) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueComparisonTest_12, NotEqualIntegers_12) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueComparisonTest_12, LessThanIntegers_12) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_TRUE(v1 <= v2);
    EXPECT_FALSE(v1 > v2);
    EXPECT_FALSE(v1 >= v2);
}

TEST_F(ValueComparisonTest_12, GreaterThanIntegers_12) {
    Value v1(10);
    Value v2(5);
    EXPECT_TRUE(v1 > v2);
    EXPECT_TRUE(v1 >= v2);
    EXPECT_FALSE(v1 < v2);
    EXPECT_FALSE(v1 <= v2);
}

TEST_F(ValueComparisonTest_12, EqualStrings_12) {
    Value v1("abc");
    Value v2("abc");
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueComparisonTest_12, EqualNulls_12) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

// ============================================================
// Tests for operator[]
// ============================================================

class ValueIndexOperatorTest_12 : public ::testing::Test {};

TEST_F(ValueIndexOperatorTest_12, ObjectKeyAccess_12) {
    Value v;
    Object obj;
    obj["name"] = Value("John");
    v.setObject(obj);
    EXPECT_EQ("John", v["name"].getString());
}

TEST_F(ValueIndexOperatorTest_12, ObjectCStringKeyAccess_12) {
    Value v;
    Object obj;
    obj["age"] = Value(30);
    v.setObject(obj);
    const char* key = "age";
    EXPECT_EQ(30, v[key].getInteger());
}

TEST_F(ValueIndexOperatorTest_12, ArrayIndexAccess_12) {
    Value v;
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    v.setArray(arr);
    EXPECT_EQ(10, v[(size_t)0].getInteger());
    EXPECT_EQ(20, v[(size_t)1].getInteger());
    EXPECT_EQ(30, v[(size_t)2].getInteger());
}

// ============================================================
// Tests for loadFromString
// ============================================================

class ValueLoadTest_12 : public ::testing::Test {};

TEST_F(ValueLoadTest_12, LoadInteger_12) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(42, v.getInteger());
}

TEST_F(ValueLoadTest_12, LoadString_12) {
    Value v;
    v.loadFromString("\"hello\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("hello", v.getString());
}

TEST_F(ValueLoadTest_12, LoadBoolean_12) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueLoadTest_12, LoadNull_12) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueLoadTest_12, LoadDouble_12) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(3.14, v.getDouble());
}

TEST_F(ValueLoadTest_12, LoadArray_12) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(3u, v.getArray().size());
}

TEST_F(ValueLoadTest_12, LoadObject_12) {
    Value v;
    v.loadFromString("{\"key\": \"value\"}");
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueLoadTest_12, LoadFromStream_12) {
    Value v;
    std::istringstream iss("42");
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(42, v.getInteger());
}

TEST_F(ValueLoadTest_12, LoadNegativeInteger_12) {
    Value v;
    v.loadFromString("-10");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(-10, v.getInteger());
}

// ============================================================
// Tests for writeToStream
// ============================================================

class ValueWriteTest_12 : public ::testing::Test {};

TEST_F(ValueWriteTest_12, WriteInteger_12) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ("42", oss.str());
}

TEST_F(ValueWriteTest_12, WriteString_12) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ("\"hello\"", oss.str());
}

TEST_F(ValueWriteTest_12, WriteBoolTrue_12) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ("true", oss.str());
}

TEST_F(ValueWriteTest_12, WriteBoolFalse_12) {
    Value v(false);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ("false", oss.str());
}

TEST_F(ValueWriteTest_12, WriteNull_12) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_EQ("null", oss.str());
}

TEST_F(ValueWriteTest_12, WriteStringWithEscapeAll_12) {
    Value v("a/b");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string result = oss.str();
    // With escapeAll, solidus should be escaped
    EXPECT_NE(std::string::npos, result.find("\\/"));
}

TEST_F(ValueWriteTest_12, StreamOperator_12) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ============================================================
// Tests for getToString
// ============================================================

class ValueGetToStringTest_12 : public ::testing::Test {};

TEST_F(ValueGetToStringTest_12, IntegerToString_12) {
    Value v(42);
    EXPECT_EQ("42", v.getToString());
}

TEST_F(ValueGetToStringTest_12, StringToString_12) {
    Value v("hello");
    EXPECT_EQ("hello", v.getToString());
}

TEST_F(ValueGetToStringTest_12, DoubleToString_12) {
    Value v(3.0);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueGetToStringTest_12, BooleanToString_12) {
    Value v(true);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

// ============================================================
// Tests for boundary conditions for escapeAllCharacters
// ============================================================

class ValueEscapeBoundaryTest_12 : public ::testing::Test {};

TEST_F(ValueEscapeBoundaryTest_12, SingleCharacterString_12) {
    EXPECT_EQ("a", Value::escapeAllCharacters("a"));
}

TEST_F(ValueEscapeBoundaryTest_12, LongString_12) {
    std::string longStr(10000, 'a');
    EXPECT_EQ(longStr, Value::escapeAllCharacters(longStr));
}

TEST_F(ValueEscapeBoundaryTest_12, AllControlCharacters_12) {
    // Test all control characters from 0x01 to 0x1f 
    // (excluding special ones that have their own escape)
    for (char c = '\x01'; c <= '\x1f'; ++c) {
        if (c == '\b' || c == '\f' || c == '\n' || c == '\r' || c == '\t') {
            continue; // These have named escapes
        }
        std::string input(1, c);
        std::string result = Value::escapeAllCharacters(input);
        EXPECT_EQ(0u, result.find("\\u")) << "Failed for character 0x" << std::hex << (int)c;
        EXPECT_EQ(6u, result.size()) << "Failed for character 0x" << std::hex << (int)c;
    }
}

TEST_F(ValueEscapeBoundaryTest_12, CharacterJustAboveControlRange_12) {
    // Space (0x20) should not be escaped
    EXPECT_EQ(" ", Value::escapeAllCharacters(" "));
}

TEST_F(ValueEscapeBoundaryTest_12, HighAsciiCharacter_12) {
    // Characters above 0x7E (like 0x7F DEL, or extended ASCII)
    // These should pass through as-is since the function only escapes <= 0x1f
    std::string input(1, '~'); // 0x7E
    EXPECT_EQ("~", Value::escapeAllCharacters(input));
}

TEST_F(ValueEscapeBoundaryTest_12, MultipleConsecutiveEscapes_12) {
    EXPECT_EQ("\\n\\n\\n", Value::escapeAllCharacters("\n\n\n"));
}

TEST_F(ValueEscapeBoundaryTest_12, InterleavedNormalAndSpecial_12) {
    EXPECT_EQ("a\\nb\\tc", Value::escapeAllCharacters("a\nb\tc"));
}

// ============================================================
// Tests for Value constructed from stream
// ============================================================

class ValueStreamConstructorTest_12 : public ::testing::Test {};

TEST_F(ValueStreamConstructorTest_12, ConstructFromStream_12) {
    std::istringstream iss("42");
    Value v(iss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(42, v.getInteger());
}

TEST_F(ValueStreamConstructorTest_12, ConstructFromStreamString_12) {
    std::istringstream iss("\"hello\"");
    Value v(iss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("hello", v.getString());
}

// ============================================================
// Tests for changing type via setter
// ============================================================

class ValueTypeChangeTest_12 : public ::testing::Test {};

TEST_F(ValueTypeChangeTest_12, IntegerToString_12) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("hello");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("hello", v.getString());
}

TEST_F(ValueTypeChangeTest_12, StringToNull_12) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTypeChangeTest_12, NullToBoolean_12) {
    Value v;
    EXPECT_TRUE(v.isNull());
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
}

TEST_F(ValueTypeChangeTest_12, BooleanToDouble_12) {
    Value v(true);
    v.setDouble(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(1.5, v.getDouble());
}

// ============================================================
// Tests for integer boundary values
// ============================================================

class ValueIntegerBoundaryTest_12 : public ::testing::Test {};

TEST_F(ValueIntegerBoundaryTest_12, ZeroInteger_12) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(0, v.getInteger());
}

TEST_F(ValueIntegerBoundaryTest_12, NegativeInteger_12) {
    Value v(-1);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(-1, v.getInteger());
}

TEST_F(ValueIntegerBoundaryTest_12, LargeInteger_12) {
    Value v(2147483647);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(2147483647, v.getInteger());
}

TEST_F(ValueIntegerBoundaryTest_12, MinInteger_12) {
    Value v(-2147483647);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(-2147483647, v.getInteger());
}

// ============================================================
// Tests for double boundary values
// ============================================================

class ValueDoubleBoundaryTest_12 : public ::testing::Test {};

TEST_F(ValueDoubleBoundaryTest_12, ZeroDouble_12) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(0.0, v.getDouble());
}

TEST_F(ValueDoubleBoundaryTest_12, NegativeDouble_12) {
    Value v(-1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(-1.5, v.getDouble());
}

TEST_F(ValueDoubleBoundaryTest_12, VerySmallDouble_12) {
    Value v(0.0001);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(0.0001, v.getDouble());
}

// ============================================================
// Tests for empty string
// ============================================================

class ValueEmptyStringTest_12 : public ::testing::Test {};

TEST_F(ValueEmptyStringTest_12, EmptyStringValue_12) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("", v.getString());
}

TEST_F(ValueEmptyStringTest_12, EmptyCStringValue_12) {
    Value v("");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ("", v.getString());
}
