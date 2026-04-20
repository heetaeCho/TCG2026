#include <gtest/gtest.h>
#include "JsonBox/Value.h"
#include <sstream>

using namespace JsonBox;

TEST(ValueTest_14, DefaultConstructor_CreatesNullValue_14) {
    Value value;
    EXPECT_TRUE(value.isNull());
}

TEST(ValueTest_14, StringConstructor_SetsStringValue_14) {
    Value value("test");
    EXPECT_EQ(value.getString(), "test");
}

TEST(ValueTest_14, CStringConstructor_SetsStringValue_14) {
    Value value("test");
    EXPECT_EQ(value.getString(), "test");
}

TEST(ValueTest_14, IntConstructor_SetsIntValue_14) {
    Value value(42);
    EXPECT_EQ(value.getInteger(), 42);
}

TEST(ValueTest_14, DoubleConstructor_SetsDoubleValue_14) {
    Value value(3.14);
    EXPECT_DOUBLE_EQ(value.getDouble(), 3.14);
}

TEST(ValueTest_14, ObjectConstructor_SetsObjectValue_14) {
    Object obj = {{"key", "value"}};
    Value value(obj);
    EXPECT_TRUE(value.isObject());
    EXPECT_EQ(value.getObject().at("key").getString(), "value");
}

TEST(ValueTest_14, ArrayConstructor_SetsArrayValue_14) {
    Array arr = {"element"};
    Value value(arr);
    EXPECT_TRUE(value.isArray());
    EXPECT_EQ(value.getArray()[0].getString(), "element");
}

TEST(ValueTest_14, BoolConstructor_SetsBoolValue_14) {
    Value value(true);
    EXPECT_TRUE(value.getBoolean());
}

TEST(ValueTest_14, CopyConstructor_CopiesStringValue_14) {
    Value original("test");
    Value copy(original);
    EXPECT_EQ(copy.getString(), "test");
}

TEST(ValueTest_14, AssignmentOperator_SetsStringValue_14) {
    Value value;
    value = "test";
    EXPECT_EQ(value.getString(), "test");
}

TEST(ValueTest_14, AssignmentOperator_SetsIntValue_14) {
    Value value;
    value = 42;
    EXPECT_EQ(value.getInteger(), 42);
}

TEST(ValueTest_14, AssignmentOperator_SetsDoubleValue_14) {
    Value value;
    value = 3.14;
    EXPECT_DOUBLE_EQ(value.getDouble(), 3.14);
}

TEST(ValueTest_14, AssignmentOperator_SetsObjectValue_14) {
    Value value;
    Object obj = {{"key", "value"}};
    value = obj;
    EXPECT_TRUE(value.isObject());
    EXPECT_EQ(value.getObject().at("key").getString(), "value");
}

TEST(ValueTest_14, AssignmentOperator_SetsArrayValue_14) {
    Value value;
    Array arr = {"element"};
    value = arr;
    EXPECT_TRUE(value.isArray());
    EXPECT_EQ(value.getArray()[0].getString(), "element");
}

TEST(ValueTest_14, AssignmentOperator_SetsBoolValue_14) {
    Value value;
    value = true;
    EXPECT_TRUE(value.getBoolean());
}

TEST(ValueTest_14, EqualityOperator_ReturnsTrueForEqualValues_14) {
    Value value1("test");
    Value value2("test");
    EXPECT_TRUE(value1 == value2);
}

TEST(ValueTest_14, EqualityOperator_ReturnsFalseForDifferentValues_14) {
    Value value1("test");
    Value value2("different");
    EXPECT_FALSE(value1 == value2);
}

TEST(ValueTest_14, InequalityOperator_ReturnsTrueForDifferentValues_14) {
    Value value1("test");
    Value value2("different");
    EXPECT_TRUE(value1 != value2);
}

TEST(ValueTest_14, InequalityOperator_ReturnsFalseForEqualValues_14) {
    Value value1("test");
    Value value2("test");
    EXPECT_FALSE(value1 != value2);
}

TEST(ValueTest_14, LoadFromString_SetsStringValue_14) {
    Value value;
    value.loadFromString("\"test\"");
    EXPECT_EQ(value.getString(), "test");
}

TEST(ValueTest_14, WriteToStream_WritesStringValue_14) {
    Value value("test");
    std::ostringstream oss;
    value.writeToStream(oss, false, false);
    EXPECT_EQ(oss.str(), "\"test\"");
}

TEST(ValueTest_14, TryGetString_ReturnsDefaultValueForNonString_14) {
    Value value(42);
    EXPECT_EQ(value.tryGetString("default"), "default");
}

TEST(ValueTest_14, TryGetInteger_ReturnsDefaultValueForNonInt_14) {
    Value value("test");
    EXPECT_EQ(value.tryGetInteger(42), 42);
}

TEST(ValueTest_14, TryGetDouble_ReturnsDefaultValueForNonDouble_14) {
    Value value("test");
    EXPECT_DOUBLE_EQ(value.tryGetDouble(3.14), 3.14);
}

TEST(ValueTest_14, TryGetFloat_ReturnsDefaultValueForNonFloat_14) {
    Value value("test");
    EXPECT_FLOAT_EQ(value.tryGetFloat(2.71f), 2.71f);
}

TEST(ValueTest_14, TryGetBoolean_ReturnsDefaultValueForNonBool_14) {
    Value value("test");
    EXPECT_TRUE(value.tryGetBoolean(true));
}