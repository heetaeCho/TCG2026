#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>
#include "JsonBox/Value.h"

using namespace JsonBox;

// Helper to create a temporary file with given content
class TempFile {
public:
    TempFile(const std::string& content, const std::string& filename = "test_temp.json")
        : filename_(filename) {
        std::ofstream ofs(filename_.c_str());
        ofs << content;
        ofs.close();
    }
    ~TempFile() {
        std::remove(filename_.c_str());
    }
    const std::string& path() const { return filename_; }
private:
    std::string filename_;
};

// ==================== Default Constructor ====================

TEST(ValueTest_64, DefaultConstructorCreatesNull_64) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_64, DefaultConstructorTypeIsNullValue_64) {
    Value v;
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

// ==================== String Constructor ====================

TEST(ValueTest_64, StringConstructor_64) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST(ValueTest_64, CStringConstructor_64) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST(ValueTest_64, EmptyStringConstructor_64) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

// ==================== Integer Constructor ====================

TEST(ValueTest_64, IntegerConstructor_64) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_64, IntegerConstructorNegative_64) {
    Value v(-100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -100);
}

TEST(ValueTest_64, IntegerConstructorZero_64) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

// ==================== Double Constructor ====================

TEST(ValueTest_64, DoubleConstructor_64) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueTest_64, DoubleConstructorNegative_64) {
    Value v(-2.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -2.5);
}

TEST(ValueTest_64, DoubleConstructorZero_64) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

// ==================== Boolean Constructor ====================

TEST(ValueTest_64, BooleanConstructorTrue_64) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_64, BooleanConstructorFalse_64) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

// ==================== Object Constructor ====================

TEST(ValueTest_64, ObjectConstructor_64) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueTest_64, EmptyObjectConstructor_64) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

// ==================== Array Constructor ====================

TEST(ValueTest_64, ArrayConstructor_64) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST(ValueTest_64, EmptyArrayConstructor_64) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}

// ==================== Copy Constructor ====================

TEST(ValueTest_64, CopyConstructorString_64) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST(ValueTest_64, CopyConstructorInteger_64) {
    Value original(42);
    Value copy(original);
    EXPECT_TRUE(copy.isInteger());
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST(ValueTest_64, CopyConstructorNull_64) {
    Value original;
    Value copy(original);
    EXPECT_TRUE(copy.isNull());
}

// ==================== Stream Constructor ====================

TEST(ValueTest_64, StreamConstructorWithJson_64) {
    std::istringstream iss("{\"key\": \"value\"}");
    Value v(iss);
    EXPECT_TRUE(v.isObject());
}

// ==================== Type Checking ====================

TEST(ValueTest_64, IsStringReturnsFalseForNonString_64) {
    Value v(42);
    EXPECT_FALSE(v.isString());
}

TEST(ValueTest_64, IsIntegerReturnsFalseForNonInteger_64) {
    Value v("hello");
    EXPECT_FALSE(v.isInteger());
}

TEST(ValueTest_64, IsDoubleReturnsFalseForNonDouble_64) {
    Value v(42);
    EXPECT_FALSE(v.isDouble());
}

TEST(ValueTest_64, IsObjectReturnsFalseForNonObject_64) {
    Value v(42);
    EXPECT_FALSE(v.isObject());
}

TEST(ValueTest_64, IsArrayReturnsFalseForNonArray_64) {
    Value v(42);
    EXPECT_FALSE(v.isArray());
}

TEST(ValueTest_64, IsBooleanReturnsFalseForNonBoolean_64) {
    Value v(42);
    EXPECT_FALSE(v.isBoolean());
}

TEST(ValueTest_64, IsNullReturnsFalseForNonNull_64) {
    Value v(42);
    EXPECT_FALSE(v.isNull());
}

TEST(ValueTest_64, IsNumericForInteger_64) {
    Value v(42);
    EXPECT_TRUE(v.isNumeric());
}

TEST(ValueTest_64, IsNumericForDouble_64) {
    Value v(3.14);
    EXPECT_TRUE(v.isNumeric());
}

TEST(ValueTest_64, IsNumericForString_64) {
    Value v("hello");
    EXPECT_FALSE(v.isNumeric());
}

TEST(ValueTest_64, IsStringableForString_64) {
    Value v("hello");
    EXPECT_TRUE(v.isStringable());
}

// ==================== Assignment Operators ====================

TEST(ValueTest_64, AssignmentFromValue_64) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST(ValueTest_64, AssignmentFromString_64) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST(ValueTest_64, AssignmentFromCString_64) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST(ValueTest_64, AssignmentFromInt_64) {
    Value v;
    v = 99;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST(ValueTest_64, AssignmentFromDouble_64) {
    Value v;
    v = 1.23;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23);
}

TEST(ValueTest_64, AssignmentFromObject_64) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST(ValueTest_64, AssignmentFromArray_64) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

TEST(ValueTest_64, AssignmentFromBool_64) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

// ==================== Setters ====================

TEST(ValueTest_64, SetString_64) {
    Value v;
    v.setString("new string");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "new string");
}

TEST(ValueTest_64, SetInteger_64) {
    Value v;
    v.setInteger(77);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 77);
}

TEST(ValueTest_64, SetDouble_64) {
    Value v;
    v.setDouble(9.99);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 9.99);
}

TEST(ValueTest_64, SetBoolean_64) {
    Value v;
    v.setBoolean(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTest_64, SetObject_64) {
    Value v;
    Object obj;
    obj["x"] = Value(10);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST(ValueTest_64, SetArray_64) {
    Value v;
    Array arr;
    arr.push_back(Value("item"));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

TEST(ValueTest_64, SetNull_64) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// ==================== Type Transitions ====================

TEST(ValueTest_64, SetStringOverwritesInteger_64) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("overwritten");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "overwritten");
}

TEST(ValueTest_64, SetIntegerOverwritesString_64) {
    Value v("hello");
    EXPECT_TRUE(v.isString());
    v.setInteger(100);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 100);
}

// ==================== tryGet Methods ====================

TEST(ValueTest_64, TryGetStringReturnsValueWhenString_64) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST(ValueTest_64, TryGetStringReturnsDefaultWhenNotString_64) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST(ValueTest_64, TryGetIntegerReturnsValueWhenInteger_64) {
    Value v(42);
    EXPECT_EQ(v.tryGetInteger(0), 42);
}

TEST(ValueTest_64, TryGetIntegerReturnsDefaultWhenNotInteger_64) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(99), 99);
}

TEST(ValueTest_64, TryGetDoubleReturnsValueWhenDouble_64) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST(ValueTest_64, TryGetDoubleReturnsDefaultWhenNotDouble_64) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.5), 1.5);
}

TEST(ValueTest_64, TryGetFloatReturnsValueWhenDouble_64) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST(ValueTest_64, TryGetFloatReturnsDefaultWhenNotDouble_64) {
    Value v("hello");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.0f), 1.0f);
}

TEST(ValueTest_64, TryGetBooleanReturnsValueWhenBoolean_64) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST(ValueTest_64, TryGetBooleanReturnsDefaultWhenNotBoolean_64) {
    Value v(42);
    EXPECT_TRUE(v.tryGetBoolean(true));
}

// ==================== getFloat ====================

TEST(ValueTest_64, GetFloat_64) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 2.5f);
}

// ==================== Comparison Operators ====================

TEST(ValueTest_64, EqualityOperatorSameValues_64) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
}

TEST(ValueTest_64, EqualityOperatorDifferentValues_64) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
}

TEST(ValueTest_64, InequalityOperator_64) {
    Value v1(42);
    Value v2(43);
    EXPECT_TRUE(v1 != v2);
}

TEST(ValueTest_64, LessThanOperator_64) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
}

TEST(ValueTest_64, LessThanOrEqualOperator_64) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST(ValueTest_64, GreaterThanOperator_64) {
    Value v1(2);
    Value v2(1);
    EXPECT_TRUE(v1 > v2);
}

TEST(ValueTest_64, GreaterThanOrEqualOperator_64) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 >= v2);
}

TEST(ValueTest_64, EqualityOperatorDifferentTypes_64) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST(ValueTest_64, EqualityNullValues_64) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

// ==================== Subscript Operator ====================

TEST(ValueTest_64, SubscriptOperatorStringKey_64) {
    Value v;
    Object obj;
    obj["key"] = Value("val");
    v.setObject(obj);
    EXPECT_TRUE(v["key"].isString());
    EXPECT_EQ(v["key"].getString(), "val");
}

TEST(ValueTest_64, SubscriptOperatorCStringKey_64) {
    Value v;
    Object obj;
    obj["key"] = Value(10);
    v.setObject(obj);
    EXPECT_TRUE(v["key"].isInteger());
    EXPECT_EQ(v["key"].getInteger(), 10);
}

TEST(ValueTest_64, SubscriptOperatorArrayIndex_64) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    v.setArray(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 1);
    EXPECT_EQ(v[(size_t)1].getInteger(), 2);
    EXPECT_EQ(v[(size_t)2].getInteger(), 3);
}

// ==================== loadFromString ====================

TEST(ValueTest_64, LoadFromStringSimpleObject_64) {
    Value v;
    v.loadFromString("{\"name\": \"test\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["name"].getString(), "test");
}

TEST(ValueTest_64, LoadFromStringSimpleArray_64) {
    Value v;
    v.loadFromString("[1, 2, 3]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST(ValueTest_64, LoadFromStringInteger_64) {
    Value v;
    v.loadFromString("42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_64, LoadFromStringDouble_64) {
    Value v;
    v.loadFromString("3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST(ValueTest_64, LoadFromStringBooleanTrue_64) {
    Value v;
    v.loadFromString("true");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST(ValueTest_64, LoadFromStringBooleanFalse_64) {
    Value v;
    v.loadFromString("false");
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST(ValueTest_64, LoadFromStringNull_64) {
    Value v;
    v.loadFromString("null");
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_64, LoadFromStringNestedObject_64) {
    Value v;
    v.loadFromString("{\"outer\": {\"inner\": 42}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["outer"].isObject());
    EXPECT_EQ(v["outer"]["inner"].getInteger(), 42);
}

TEST(ValueTest_64, LoadFromStringQuotedString_64) {
    Value v;
    v.loadFromString("\"hello world\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello world");
}

// ==================== loadFromStream ====================

TEST(ValueTest_64, LoadFromStream_64) {
    Value v;
    std::istringstream iss("{\"a\": 1}");
    v.loadFromStream(iss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["a"].getInteger(), 1);
}

// ==================== loadFromFile ====================

TEST(ValueTest_64, LoadFromFileValid_64) {
    TempFile tmp("{\"key\": \"value\"}");
    Value v;
    v.loadFromFile(tmp.path());
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getString(), "value");
}

TEST(ValueTest_64, LoadFromFileNonExistent_64) {
    Value v;
    EXPECT_THROW(v.loadFromFile("nonexistent_file_12345.json"), std::invalid_argument);
}

TEST(ValueTest_64, LoadFromFileEmptyPath_64) {
    Value v;
    EXPECT_THROW(v.loadFromFile(""), std::invalid_argument);
}

// ==================== writeToStream ====================

TEST(ValueTest_64, WriteToStreamInteger_64) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_FALSE(oss.str().empty());
    EXPECT_NE(oss.str().find("42"), std::string::npos);
}

TEST(ValueTest_64, WriteToStreamString_64) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("hello"), std::string::npos);
}

TEST(ValueTest_64, WriteToStreamObject_64) {
    Value v;
    Object obj;
    obj["key"] = Value("val");
    v.setObject(obj);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string output = oss.str();
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("val"), std::string::npos);
}

TEST(ValueTest_64, WriteToStreamWithIndent_64) {
    Value v;
    Object obj;
    obj["key"] = Value("val");
    v.setObject(obj);
    std::ostringstream oss;
    v.writeToStream(oss, true, false);
    std::string output = oss.str();
    // Indented output should contain newlines/tabs
    EXPECT_NE(output.find("\n"), std::string::npos);
}

TEST(ValueTest_64, WriteToStreamNull_64) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("null"), std::string::npos);
}

TEST(ValueTest_64, WriteToStreamBoolean_64) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("true"), std::string::npos);
}

// ==================== writeToFile ====================

TEST(ValueTest_64, WriteToFileAndReadBack_64) {
    Value v;
    Object obj;
    obj["test"] = Value(123);
    v.setObject(obj);
    
    std::string filename = "test_write_64.json";
    v.writeToFile(filename, false, false);
    
    Value v2;
    v2.loadFromFile(filename);
    EXPECT_TRUE(v2.isObject());
    EXPECT_EQ(v2["test"].getInteger(), 123);
    
    std::remove(filename.c_str());
}

// ==================== operator<< ====================

TEST(ValueTest_64, StreamOutputOperator_64) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_NE(oss.str().find("42"), std::string::npos);
}

// ==================== escapeMinimumCharacters ====================

TEST(ValueTest_64, EscapeMinimumCharactersQuote_64) {
    std::string result = Value::escapeMinimumCharacters("he\"llo");
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST(ValueTest_64, EscapeMinimumCharactersBackslash_64) {
    std::string result = Value::escapeMinimumCharacters("he\\llo");
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST(ValueTest_64, EscapeMinimumCharactersNewline_64) {
    std::string result = Value::escapeMinimumCharacters("he\nllo");
    EXPECT_NE(result.find("\\n"), std::string::npos);
}

TEST(ValueTest_64, EscapeMinimumCharactersEmpty_64) {
    std::string result = Value::escapeMinimumCharacters("");
    EXPECT_EQ(result, "");
}

TEST(ValueTest_64, EscapeMinimumCharactersNoEscapeNeeded_64) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

// ==================== escapeAllCharacters ====================

TEST(ValueTest_64, EscapeAllCharactersBasic_64) {
    std::string result = Value::escapeAllCharacters("a");
    // Should produce a unicode escape for 'a'
    EXPECT_FALSE(result.empty());
}

// ==================== escapeToUnicode ====================

TEST(ValueTest_64, EscapeToUnicode_64) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ==================== getToString ====================

TEST(ValueTest_64, GetToStringFromInteger_64) {
    Value v(42);
    std::string s = v.getToString();
    EXPECT_EQ(s, "42");
}

TEST(ValueTest_64, GetToStringFromString_64) {
    Value v("hello");
    std::string s = v.getToString();
    EXPECT_EQ(s, "hello");
}

TEST(ValueTest_64, GetToStringFromDouble_64) {
    Value v(3.5);
    std::string s = v.getToString();
    EXPECT_FALSE(s.empty());
}

TEST(ValueTest_64, GetToStringFromBoolean_64) {
    Value v(true);
    std::string s = v.getToString();
    EXPECT_FALSE(s.empty());
}

// ==================== Round-trip tests ====================

TEST(ValueTest_64, RoundTripObjectThroughStream_64) {
    Value original;
    Object obj;
    obj["name"] = Value("test");
    obj["count"] = Value(5);
    obj["valid"] = Value(true);
    original.setObject(obj);
    
    std::ostringstream oss;
    original.writeToStream(oss, false, false);
    
    Value parsed;
    parsed.loadFromString(oss.str());
    
    EXPECT_TRUE(parsed.isObject());
    EXPECT_EQ(parsed["name"].getString(), "test");
    EXPECT_EQ(parsed["count"].getInteger(), 5);
    EXPECT_TRUE(parsed["valid"].getBoolean());
}

TEST(ValueTest_64, RoundTripArrayThroughStream_64) {
    Value original;
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value("two"));
    arr.push_back(Value(3.0));
    original.setArray(arr);
    
    std::ostringstream oss;
    original.writeToStream(oss, false, false);
    
    Value parsed;
    parsed.loadFromString(oss.str());
    
    EXPECT_TRUE(parsed.isArray());
    EXPECT_EQ(parsed.getArray().size(), 3u);
}

// ==================== Complex / Edge Cases ====================

TEST(ValueTest_64, LoadFromStringEmptyObject_64) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

TEST(ValueTest_64, LoadFromStringEmptyArray_64) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v.getArray().empty());
}

TEST(ValueTest_64, LoadFromStringNegativeNumber_64) {
    Value v;
    v.loadFromString("-42");
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST(ValueTest_64, LoadFromStringNegativeDouble_64) {
    Value v;
    v.loadFromString("-3.14");
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}

TEST(ValueTest_64, LoadFromStringStringWithEscapes_64) {
    Value v;
    v.loadFromString("\"hello\\nworld\"");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello\nworld");
}

TEST(ValueTest_64, SubscriptCreatesNewKeyInObject_64) {
    Value v;
    Object obj;
    v.setObject(obj);
    v["newkey"] = Value(42);
    EXPECT_EQ(v["newkey"].getInteger(), 42);
}

TEST(ValueTest_64, SelfAssignment_64) {
    Value v(42);
    v = v;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST(ValueTest_64, MultipleTypeChanges_64) {
    Value v;
    EXPECT_TRUE(v.isNull());
    v.setInteger(42);
    EXPECT_TRUE(v.isInteger());
    v.setString("hello");
    EXPECT_TRUE(v.isString());
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    v.setDouble(3.14);
    EXPECT_TRUE(v.isDouble());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST(ValueTest_64, LargeNestedStructure_64) {
    Value v;
    v.loadFromString("{\"a\":{\"b\":{\"c\":[1,2,{\"d\":true}]}}}");
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["a"].isObject());
    EXPECT_TRUE(v["a"]["b"].isObject());
    EXPECT_TRUE(v["a"]["b"]["c"].isArray());
    EXPECT_EQ(v["a"]["b"]["c"].getArray().size(), 3u);
}

TEST(ValueTest_64, WriteToStreamEscapeAll_64) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, true);
    std::string output = oss.str();
    // With escapeAll=true, characters should be escaped to unicode
    EXPECT_FALSE(output.empty());
}

TEST(ValueTest_64, LoadFromFileWithArray_64) {
    TempFile tmp("[1, 2, 3, 4, 5]");
    Value v;
    v.loadFromFile(tmp.path());
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 5u);
}

TEST(ValueTest_64, ComparisonBooleanValues_64) {
    Value vt(true);
    Value vf(false);
    EXPECT_TRUE(vt != vf);
    EXPECT_TRUE(vf < vt);
}

TEST(ValueTest_64, ComparisonStringValues_64) {
    Value v1("abc");
    Value v2("def");
    EXPECT_TRUE(v1 < v2);
    EXPECT_TRUE(v2 > v1);
}
