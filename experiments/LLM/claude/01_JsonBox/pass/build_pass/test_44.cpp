#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueGetToStringTest_44 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test getToString for a string value
TEST_F(ValueGetToStringTest_44, StringValueReturnsString_44) {
    Value v(std::string("hello world"));
    EXPECT_EQ("hello world", v.getToString());
}

// Test getToString for an empty string value
TEST_F(ValueGetToStringTest_44, EmptyStringValueReturnsEmptyString_44) {
    Value v(std::string(""));
    EXPECT_EQ("", v.getToString());
}

// Test getToString for a string constructed from const char*
TEST_F(ValueGetToStringTest_44, CStringValueReturnsString_44) {
    Value v("test string");
    EXPECT_EQ("test string", v.getToString());
}

// Test getToString for a positive integer value
TEST_F(ValueGetToStringTest_44, PositiveIntegerReturnsStringRepresentation_44) {
    Value v(42);
    EXPECT_EQ("42", v.getToString());
}

// Test getToString for zero integer value
TEST_F(ValueGetToStringTest_44, ZeroIntegerReturnsZeroString_44) {
    Value v(0);
    EXPECT_EQ("0", v.getToString());
}

// Test getToString for a negative integer value
TEST_F(ValueGetToStringTest_44, NegativeIntegerReturnsStringRepresentation_44) {
    Value v(-100);
    EXPECT_EQ("-100", v.getToString());
}

// Test getToString for a large integer value
TEST_F(ValueGetToStringTest_44, LargeIntegerReturnsStringRepresentation_44) {
    Value v(2147483647);
    EXPECT_EQ("2147483647", v.getToString());
}

// Test getToString for a double value
TEST_F(ValueGetToStringTest_44, DoubleValueReturnsStringRepresentation_44) {
    Value v(3.14);
    std::stringstream ss;
    ss << 3.14;
    EXPECT_EQ(ss.str(), v.getToString());
}

// Test getToString for zero double value
TEST_F(ValueGetToStringTest_44, ZeroDoubleReturnsStringRepresentation_44) {
    Value v(0.0);
    std::stringstream ss;
    ss << 0.0;
    EXPECT_EQ(ss.str(), v.getToString());
}

// Test getToString for a negative double value
TEST_F(ValueGetToStringTest_44, NegativeDoubleReturnsStringRepresentation_44) {
    Value v(-2.718);
    std::stringstream ss;
    ss << -2.718;
    EXPECT_EQ(ss.str(), v.getToString());
}

// Test getToString for boolean true
TEST_F(ValueGetToStringTest_44, BooleanTrueReturnsTrueString_44) {
    Value v(true);
    EXPECT_EQ("true", v.getToString());
}

// Test getToString for boolean false
TEST_F(ValueGetToStringTest_44, BooleanFalseReturnsFalseString_44) {
    Value v(false);
    EXPECT_EQ("false", v.getToString());
}

// Test getToString for null value
TEST_F(ValueGetToStringTest_44, NullValueReturnsNullString_44) {
    Value v;
    EXPECT_EQ("null", v.getToString());
}

// Test getToString for an empty object
TEST_F(ValueGetToStringTest_44, EmptyObjectReturnsObjectString_44) {
    Object obj;
    Value v(obj);
    std::string result = v.getToString();
    // The result should contain at least the object delimiters
    EXPECT_FALSE(result.empty());
}

// Test getToString for an object with entries
TEST_F(ValueGetToStringTest_44, ObjectWithEntriesReturnsNonEmptyString_44) {
    Object obj;
    obj["key"] = Value(std::string("value"));
    Value v(obj);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
    // Should contain the key somewhere in the output
    EXPECT_NE(std::string::npos, result.find("key"));
}

// Test getToString for an empty array
TEST_F(ValueGetToStringTest_44, EmptyArrayReturnsArrayString_44) {
    Array arr;
    Value v(arr);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

// Test getToString for an array with elements
TEST_F(ValueGetToStringTest_44, ArrayWithElementsReturnsNonEmptyString_44) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    arr.push_back(Value(3));
    Value v(arr);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
}

// Test getToString consistency - calling multiple times returns same result
TEST_F(ValueGetToStringTest_44, ConsistentResults_44) {
    Value v(42);
    std::string first = v.getToString();
    std::string second = v.getToString();
    EXPECT_EQ(first, second);
}

// Test getToString for a string with special characters
TEST_F(ValueGetToStringTest_44, StringWithSpecialCharacters_44) {
    Value v(std::string("hello\nworld"));
    std::string result = v.getToString();
    EXPECT_EQ("hello\nworld", result);
}

// Test getToString for a string with unicode-like content
TEST_F(ValueGetToStringTest_44, StringWithUnicodeContent_44) {
    Value v(std::string("abc\\u0041"));
    std::string result = v.getToString();
    EXPECT_EQ("abc\\u0041", result);
}

// Test getToString after setNull
TEST_F(ValueGetToStringTest_44, SetNullThenGetToStringReturnsNull_44) {
    Value v(42);
    EXPECT_EQ("42", v.getToString());
    v.setNull();
    EXPECT_EQ("null", v.getToString());
}

// Test getToString after changing type via assignment
TEST_F(ValueGetToStringTest_44, AssignStringAfterIntegerChangesOutput_44) {
    Value v(42);
    EXPECT_EQ("42", v.getToString());
    v = std::string("now a string");
    EXPECT_EQ("now a string", v.getToString());
}

// Test getToString after changing from string to boolean
TEST_F(ValueGetToStringTest_44, AssignBoolAfterStringChangesOutput_44) {
    Value v(std::string("test"));
    EXPECT_EQ("test", v.getToString());
    v = true;
    EXPECT_EQ("true", v.getToString());
}

// Test getToString for integer set via setInteger
TEST_F(ValueGetToStringTest_44, SetIntegerThenGetToString_44) {
    Value v;
    v.setInteger(999);
    EXPECT_EQ("999", v.getToString());
}

// Test getToString for double set via setDouble
TEST_F(ValueGetToStringTest_44, SetDoubleThenGetToString_44) {
    Value v;
    v.setDouble(1.5);
    std::stringstream ss;
    ss << 1.5;
    EXPECT_EQ(ss.str(), v.getToString());
}

// Test getToString for boolean set via setBoolean
TEST_F(ValueGetToStringTest_44, SetBooleanTrueThenGetToString_44) {
    Value v;
    v.setBoolean(true);
    EXPECT_EQ("true", v.getToString());
}

// Test getToString for boolean set via setBoolean (false)
TEST_F(ValueGetToStringTest_44, SetBooleanFalseThenGetToString_44) {
    Value v;
    v.setBoolean(false);
    EXPECT_EQ("false", v.getToString());
}

// Test getToString for a copied value
TEST_F(ValueGetToStringTest_44, CopiedValueHasSameGetToString_44) {
    Value original(42);
    Value copy(original);
    EXPECT_EQ(original.getToString(), copy.getToString());
}

// Test getToString for a value assigned from another
TEST_F(ValueGetToStringTest_44, AssignedValueHasSameGetToString_44) {
    Value original(std::string("assigned"));
    Value target;
    target = original;
    EXPECT_EQ("assigned", target.getToString());
}

// Test getToString for negative integer boundary
TEST_F(ValueGetToStringTest_44, MinNegativeIntegerReturnsString_44) {
    Value v(-2147483647);
    EXPECT_EQ("-2147483647", v.getToString());
}

// Test getToString for a very small double
TEST_F(ValueGetToStringTest_44, VerySmallDoubleReturnsString_44) {
    Value v(0.000001);
    std::stringstream ss;
    ss << 0.000001;
    EXPECT_EQ(ss.str(), v.getToString());
}

// Test getToString for a nested array in object
TEST_F(ValueGetToStringTest_44, NestedArrayInObjectReturnsNonEmpty_44) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Object obj;
    obj["numbers"] = Value(arr);
    Value v(obj);
    std::string result = v.getToString();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(std::string::npos, result.find("numbers"));
}

// Test that getToString on object matches operator<< output
TEST_F(ValueGetToStringTest_44, ObjectGetToStringMatchesStreamOutput_44) {
    Object obj;
    obj["a"] = Value(1);
    Value v(obj);
    std::stringstream ss;
    ss << v;
    EXPECT_EQ(ss.str(), v.getToString());
}

// Test that getToString on array matches operator<< output
TEST_F(ValueGetToStringTest_44, ArrayGetToStringMatchesStreamOutput_44) {
    Array arr;
    arr.push_back(Value(std::string("x")));
    Value v(arr);
    std::stringstream ss;
    ss << v;
    EXPECT_EQ(ss.str(), v.getToString());
}
