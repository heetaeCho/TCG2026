#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>

#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueTest_66 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(ValueTest_66, DefaultConstructor_IsNull_66) {
    Value v;
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(v.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_66, StringConstructor_CreatesString_66) {
    Value v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

TEST_F(ValueTest_66, CStringConstructor_CreatesString_66) {
    Value v("world");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "world");
}

TEST_F(ValueTest_66, IntConstructor_CreatesInteger_66) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_66, DoubleConstructor_CreatesDouble_66) {
    Value v(3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_66, BoolConstructor_CreatesBoolean_66) {
    Value vTrue(true);
    EXPECT_TRUE(vTrue.isBoolean());
    EXPECT_TRUE(vTrue.getBoolean());

    Value vFalse(false);
    EXPECT_TRUE(vFalse.isBoolean());
    EXPECT_FALSE(vFalse.getBoolean());
}

TEST_F(ValueTest_66, ObjectConstructor_CreatesObject_66) {
    Object obj;
    obj["key"] = Value("value");
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_66, ArrayConstructor_CreatesArray_66) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 2u);
}

TEST_F(ValueTest_66, CopyConstructor_CopiesValue_66) {
    Value original("test");
    Value copy(original);
    EXPECT_TRUE(copy.isString());
    EXPECT_EQ(copy.getString(), "test");
}

TEST_F(ValueTest_66, StreamConstructor_ParsesJSON_66) {
    std::istringstream ss("\"hello\"");
    Value v(ss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello");
}

// ==================== Type Query Tests ====================

TEST_F(ValueTest_66, IsString_ReturnsTrueForString_66) {
    Value v("test");
    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isInteger());
    EXPECT_FALSE(v.isDouble());
    EXPECT_FALSE(v.isBoolean());
    EXPECT_FALSE(v.isNull());
    EXPECT_FALSE(v.isObject());
    EXPECT_FALSE(v.isArray());
}

TEST_F(ValueTest_66, IsInteger_ReturnsTrueForInt_66) {
    Value v(10);
    EXPECT_TRUE(v.isInteger());
    EXPECT_TRUE(v.isNumeric());
    EXPECT_FALSE(v.isString());
}

TEST_F(ValueTest_66, IsDouble_ReturnsTrueForDouble_66) {
    Value v(1.5);
    EXPECT_TRUE(v.isDouble());
    EXPECT_TRUE(v.isNumeric());
    EXPECT_FALSE(v.isInteger());
}

TEST_F(ValueTest_66, IsNumeric_TrueForIntAndDouble_66) {
    Value vi(5);
    Value vd(5.0);
    EXPECT_TRUE(vi.isNumeric());
    EXPECT_TRUE(vd.isNumeric());

    Value vs("hello");
    EXPECT_FALSE(vs.isNumeric());
}

TEST_F(ValueTest_66, IsStringable_66) {
    Value vs("hello");
    EXPECT_TRUE(vs.isStringable());
    // Null might not be stringable depending on implementation
}

// ==================== Setter Tests ====================

TEST_F(ValueTest_66, SetString_ChangesTypeAndValue_66) {
    Value v;
    v.setString("newval");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "newval");
}

TEST_F(ValueTest_66, SetInteger_ChangesTypeAndValue_66) {
    Value v;
    v.setInteger(99);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 99);
}

TEST_F(ValueTest_66, SetDouble_ChangesTypeAndValue_66) {
    Value v;
    v.setDouble(2.718);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 2.718);
}

TEST_F(ValueTest_66, SetBoolean_ChangesTypeAndValue_66) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_66, SetNull_ChangesTypeToNull_66) {
    Value v(42);
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_66, SetObject_ChangesTypeAndValue_66) {
    Value v;
    Object obj;
    obj["a"] = Value(1);
    v.setObject(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 1u);
}

TEST_F(ValueTest_66, SetArray_ChangesTypeAndValue_66) {
    Value v;
    Array arr;
    arr.push_back(Value("x"));
    v.setArray(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 1u);
}

// ==================== Assignment Operator Tests ====================

TEST_F(ValueTest_66, AssignmentFromValue_66) {
    Value v1(42);
    Value v2;
    v2 = v1;
    EXPECT_TRUE(v2.isInteger());
    EXPECT_EQ(v2.getInteger(), 42);
}

TEST_F(ValueTest_66, AssignmentFromString_66) {
    Value v;
    v = std::string("assigned");
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "assigned");
}

TEST_F(ValueTest_66, AssignmentFromCString_66) {
    Value v;
    v = "cstring";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "cstring");
}

TEST_F(ValueTest_66, AssignmentFromInt_66) {
    Value v;
    v = 123;
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 123);
}

TEST_F(ValueTest_66, AssignmentFromDouble_66) {
    Value v;
    v = 1.23;
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 1.23);
}

TEST_F(ValueTest_66, AssignmentFromBool_66) {
    Value v;
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_66, AssignmentFromObject_66) {
    Value v;
    Object obj;
    obj["key"] = Value(100);
    v = obj;
    EXPECT_TRUE(v.isObject());
}

TEST_F(ValueTest_66, AssignmentFromArray_66) {
    Value v;
    Array arr;
    arr.push_back(Value(1));
    v = arr;
    EXPECT_TRUE(v.isArray());
}

// ==================== Comparison Operator Tests ====================

TEST_F(ValueTest_66, EqualityOperator_SameValues_66) {
    Value v1(42);
    Value v2(42);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
}

TEST_F(ValueTest_66, EqualityOperator_DifferentValues_66) {
    Value v1(42);
    Value v2(43);
    EXPECT_FALSE(v1 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST_F(ValueTest_66, EqualityOperator_DifferentTypes_66) {
    Value v1(42);
    Value v2("42");
    EXPECT_FALSE(v1 == v2);
}

TEST_F(ValueTest_66, LessThanOperator_66) {
    Value v1(1);
    Value v2(2);
    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
}

TEST_F(ValueTest_66, LessThanOrEqual_66) {
    Value v1(1);
    Value v2(1);
    EXPECT_TRUE(v1 <= v2);
}

TEST_F(ValueTest_66, GreaterThanOperator_66) {
    Value v1(5);
    Value v2(3);
    EXPECT_TRUE(v1 > v2);
    EXPECT_FALSE(v2 > v1);
}

TEST_F(ValueTest_66, GreaterThanOrEqual_66) {
    Value v1(5);
    Value v2(5);
    EXPECT_TRUE(v1 >= v2);
}

// ==================== Index Operator Tests ====================

TEST_F(ValueTest_66, ObjectIndexOperator_StringKey_66) {
    Object obj;
    obj["name"] = Value("test");
    Value v(obj);
    EXPECT_EQ(v["name"].getString(), "test");
}

TEST_F(ValueTest_66, ObjectIndexOperator_CStringKey_66) {
    Object obj;
    obj["name"] = Value("test");
    Value v(obj);
    const char* key = "name";
    EXPECT_EQ(v[key].getString(), "test");
}

TEST_F(ValueTest_66, ArrayIndexOperator_66) {
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value(20));
    arr.push_back(Value(30));
    Value v(arr);
    EXPECT_EQ(v[(size_t)0].getInteger(), 10);
    EXPECT_EQ(v[(size_t)1].getInteger(), 20);
    EXPECT_EQ(v[(size_t)2].getInteger(), 30);
}

// ==================== Try Getters Tests ====================

TEST_F(ValueTest_66, TryGetString_ReturnsValueWhenString_66) {
    Value v("actual");
    EXPECT_EQ(v.tryGetString("default"), "actual");
}

TEST_F(ValueTest_66, TryGetString_ReturnsDefaultWhenNotString_66) {
    Value v(42);
    EXPECT_EQ(v.tryGetString("default"), "default");
}

TEST_F(ValueTest_66, TryGetInteger_ReturnsValueWhenInteger_66) {
    Value v(42);
    EXPECT_EQ(v.tryGetInteger(0), 42);
}

TEST_F(ValueTest_66, TryGetInteger_ReturnsDefaultWhenNotInteger_66) {
    Value v("hello");
    EXPECT_EQ(v.tryGetInteger(99), 99);
}

TEST_F(ValueTest_66, TryGetDouble_ReturnsValueWhenDouble_66) {
    Value v(3.14);
    EXPECT_DOUBLE_EQ(v.tryGetDouble(0.0), 3.14);
}

TEST_F(ValueTest_66, TryGetDouble_ReturnsDefaultWhenNotDouble_66) {
    Value v("hello");
    EXPECT_DOUBLE_EQ(v.tryGetDouble(1.0), 1.0);
}

TEST_F(ValueTest_66, TryGetFloat_ReturnsValueWhenDouble_66) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.tryGetFloat(0.0f), 2.5f);
}

TEST_F(ValueTest_66, TryGetFloat_ReturnsDefaultWhenNotDouble_66) {
    Value v("hello");
    EXPECT_FLOAT_EQ(v.tryGetFloat(1.0f), 1.0f);
}

TEST_F(ValueTest_66, TryGetBoolean_ReturnsValueWhenBoolean_66) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));
}

TEST_F(ValueTest_66, TryGetBoolean_ReturnsDefaultWhenNotBoolean_66) {
    Value v(42);
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// ==================== GetFloat Tests ====================

TEST_F(ValueTest_66, GetFloat_ReturnsFloatFromDouble_66) {
    Value v(2.5);
    EXPECT_FLOAT_EQ(v.getFloat(), 2.5f);
}

// ==================== GetToString Tests ====================

TEST_F(ValueTest_66, GetToString_FromString_66) {
    Value v("hello");
    EXPECT_EQ(v.getToString(), "hello");
}

// ==================== Load/Write Stream Tests ====================

TEST_F(ValueTest_66, LoadFromStream_ParsesInteger_66) {
    std::istringstream ss("42");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 42);
}

TEST_F(ValueTest_66, LoadFromStream_ParsesString_66) {
    std::istringstream ss("\"hello world\"");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "hello world");
}

TEST_F(ValueTest_66, LoadFromStream_ParsesObject_66) {
    std::istringstream ss("{\"key\": 123}");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["key"].getInteger(), 123);
}

TEST_F(ValueTest_66, LoadFromStream_ParsesArray_66) {
    std::istringstream ss("[1, 2, 3]");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 3u);
}

TEST_F(ValueTest_66, LoadFromStream_ParsesBoolean_66) {
    std::istringstream ss("true");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueTest_66, LoadFromStream_ParsesNull_66) {
    std::istringstream ss("null");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_66, LoadFromStream_ParsesDouble_66) {
    std::istringstream ss("3.14");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 3.14);
}

TEST_F(ValueTest_66, LoadFromString_ParsesJSON_66) {
    Value v;
    v.loadFromString("{\"name\": \"test\"}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["name"].getString(), "test");
}

TEST_F(ValueTest_66, WriteToStream_Integer_66) {
    Value v(42);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(ValueTest_66, WriteToStream_String_66) {
    Value v("hello");
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(ValueTest_66, WriteToStream_Object_66) {
    Object obj;
    obj["key"] = Value("val");
    Value v(obj);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_NE(result.find("key"), std::string::npos);
    EXPECT_NE(result.find("val"), std::string::npos);
}

TEST_F(ValueTest_66, WriteToStream_WithIndent_66) {
    Object obj;
    obj["key"] = Value("val");
    Value v(obj);
    std::ostringstream ossIndent;
    v.writeToStream(ossIndent, true, false);
    std::ostringstream ossNoIndent;
    v.writeToStream(ossNoIndent, false, false);
    // Indented version should generally be longer or contain newlines/tabs
    EXPECT_NE(ossIndent.str(), ossNoIndent.str());
}

TEST_F(ValueTest_66, WriteToStream_Null_66) {
    Value v;
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("null"), std::string::npos);
}

TEST_F(ValueTest_66, WriteToStream_Boolean_66) {
    Value v(true);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    EXPECT_NE(oss.str().find("true"), std::string::npos);
}

TEST_F(ValueTest_66, WriteToStream_Array_66) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value v(arr);
    std::ostringstream oss;
    v.writeToStream(oss, false, false);
    std::string result = oss.str();
    EXPECT_NE(result.find("["), std::string::npos);
    EXPECT_NE(result.find("]"), std::string::npos);
}

// ==================== File I/O Tests ====================

TEST_F(ValueTest_66, WriteToFile_CreatesFile_66) {
    const std::string filePath = "test_write_66.json";
    Value v(42);
    v.writeToFile(filePath, false, false);

    std::ifstream file(filePath);
    EXPECT_TRUE(file.is_open());
    std::string content;
    std::getline(file, content);
    file.close();
    EXPECT_FALSE(content.empty());

    std::remove(filePath.c_str());
}

TEST_F(ValueTest_66, WriteToFile_AndLoadFromFile_RoundTrip_66) {
    const std::string filePath = "test_roundtrip_66.json";
    Object obj;
    obj["name"] = Value("test");
    obj["number"] = Value(42);
    Value v(obj);
    v.writeToFile(filePath, false, false);

    Value loaded;
    loaded.loadFromFile(filePath);
    EXPECT_TRUE(loaded.isObject());
    EXPECT_EQ(loaded["name"].getString(), "test");
    EXPECT_EQ(loaded["number"].getInteger(), 42);

    std::remove(filePath.c_str());
}

TEST_F(ValueTest_66, WriteToFile_InvalidPath_ThrowsException_66) {
    Value v(42);
    // Attempt to write to an invalid path
    EXPECT_THROW(v.writeToFile("/nonexistent_directory_66/file.json", false, false), std::exception);
}

TEST_F(ValueTest_66, LoadFromFile_NonexistentFile_66) {
    Value v;
    // Loading from a non-existent file should throw
    EXPECT_THROW(v.loadFromFile("nonexistent_file_66.json"), std::exception);
}

// ==================== Escape Tests ====================

TEST_F(ValueTest_66, EscapeMinimumCharacters_BasicString_66) {
    std::string result = Value::escapeMinimumCharacters("hello");
    EXPECT_EQ(result, "hello");
}

TEST_F(ValueTest_66, EscapeMinimumCharacters_WithQuotes_66) {
    std::string input = "he\"llo";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result.find("\\\""), std::string::npos);
}

TEST_F(ValueTest_66, EscapeMinimumCharacters_WithBackslash_66) {
    std::string input = "he\\llo";
    std::string result = Value::escapeMinimumCharacters(input);
    EXPECT_NE(result.find("\\\\"), std::string::npos);
}

TEST_F(ValueTest_66, EscapeAllCharacters_BasicString_66) {
    std::string result = Value::escapeAllCharacters("hello");
    // All characters should be escaped to unicode
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTest_66, EscapeToUnicode_66) {
    std::string result = Value::escapeToUnicode('A');
    EXPECT_FALSE(result.empty());
    // Should contain \\u prefix
    EXPECT_NE(result.find("\\u"), std::string::npos);
}

// ==================== Stream Operator Test ====================

TEST_F(ValueTest_66, StreamOutputOperator_66) {
    Value v(42);
    std::ostringstream oss;
    oss << v;
    EXPECT_FALSE(oss.str().empty());
}

// ==================== Boundary & Edge Cases ====================

TEST_F(ValueTest_66, EmptyString_66) {
    Value v(std::string(""));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "");
}

TEST_F(ValueTest_66, EmptyObject_66) {
    Object obj;
    Value v(obj);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_66, EmptyArray_66) {
    Array arr;
    Value v(arr);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

TEST_F(ValueTest_66, IntegerZero_66) {
    Value v(0);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), 0);
}

TEST_F(ValueTest_66, NegativeInteger_66) {
    Value v(-42);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -42);
}

TEST_F(ValueTest_66, NegativeDouble_66) {
    Value v(-3.14);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -3.14);
}

TEST_F(ValueTest_66, DoubleZero_66) {
    Value v(0.0);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), 0.0);
}

TEST_F(ValueTest_66, OverwriteValue_TypeChanges_66) {
    Value v(42);
    EXPECT_TRUE(v.isInteger());
    v = "now a string";
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.getString(), "now a string");
    v = true;
    EXPECT_TRUE(v.isBoolean());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueTest_66, NestedObject_66) {
    Object inner;
    inner["innerKey"] = Value(100);
    Object outer;
    outer["nested"] = Value(inner);
    Value v(outer);
    EXPECT_TRUE(v.isObject());
    EXPECT_TRUE(v["nested"].isObject());
    EXPECT_EQ(v["nested"]["innerKey"].getInteger(), 100);
}

TEST_F(ValueTest_66, NestedArray_66) {
    Array inner;
    inner.push_back(Value(1));
    inner.push_back(Value(2));
    Array outer;
    outer.push_back(Value(inner));
    Value v(outer);
    EXPECT_TRUE(v.isArray());
    EXPECT_TRUE(v[(size_t)0].isArray());
    EXPECT_EQ(v[(size_t)0].getArray().size(), 2u);
}

TEST_F(ValueTest_66, ComplexJSON_LoadFromString_66) {
    std::string json = "{\"name\": \"John\", \"age\": 30, \"active\": true, \"scores\": [90, 85, 92], \"address\": null}";
    Value v;
    v.loadFromString(json);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["name"].getString(), "John");
    EXPECT_EQ(v["age"].getInteger(), 30);
    EXPECT_TRUE(v["active"].getBoolean());
    EXPECT_TRUE(v["scores"].isArray());
    EXPECT_EQ(v["scores"].getArray().size(), 3u);
    EXPECT_TRUE(v["address"].isNull());
}

TEST_F(ValueTest_66, WriteToFile_WithIndent_66) {
    const std::string filePath = "test_indent_66.json";
    Object obj;
    obj["key"] = Value("val");
    Value v(obj);
    v.writeToFile(filePath, true, false);

    std::ifstream file(filePath);
    EXPECT_TRUE(file.is_open());
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();
    // Indented output should contain newlines
    EXPECT_NE(content.find("\n"), std::string::npos);

    std::remove(filePath.c_str());
}

TEST_F(ValueTest_66, WriteToFile_WithEscapeAll_66) {
    const std::string filePath = "test_escapeall_66.json";
    Value v("hello");
    v.writeToFile(filePath, false, true);

    std::ifstream file(filePath);
    EXPECT_TRUE(file.is_open());
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();
    // With escapeAll, characters should be unicode escaped
    EXPECT_NE(content.find("\\u"), std::string::npos);

    std::remove(filePath.c_str());
}

TEST_F(ValueTest_66, ObjectSubscriptOperator_CreatesNewKey_66) {
    Object obj;
    Value v(obj);
    v["newkey"] = Value(42);
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v["newkey"].getInteger(), 42);
}

TEST_F(ValueTest_66, CopyConstructor_IntegerDeepCopy_66) {
    Value original(100);
    Value copy(original);
    copy = 200;
    EXPECT_EQ(original.getInteger(), 100);
    EXPECT_EQ(copy.getInteger(), 200);
}

TEST_F(ValueTest_66, NullEquality_66) {
    Value v1;
    Value v2;
    EXPECT_TRUE(v1 == v2);
}

TEST_F(ValueTest_66, BooleanFalse_66) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueTest_66, LoadFromStream_NegativeNumber_66) {
    std::istringstream ss("-123");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isInteger());
    EXPECT_EQ(v.getInteger(), -123);
}

TEST_F(ValueTest_66, LoadFromStream_NegativeDouble_66) {
    std::istringstream ss("-1.5");
    Value v;
    v.loadFromStream(ss);
    EXPECT_TRUE(v.isDouble());
    EXPECT_DOUBLE_EQ(v.getDouble(), -1.5);
}

TEST_F(ValueTest_66, LoadFromString_EmptyObject_66) {
    Value v;
    v.loadFromString("{}");
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject().size(), 0u);
}

TEST_F(ValueTest_66, LoadFromString_EmptyArray_66) {
    Value v;
    v.loadFromString("[]");
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}
