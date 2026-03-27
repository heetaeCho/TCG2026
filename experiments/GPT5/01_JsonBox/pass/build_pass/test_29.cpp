// File: Value_IndexByKey_Test_29.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueIndexKeyTest_29 : public ::testing::Test {};

// Creates an object when indexing a non-object (default/null) value.
TEST_F(ValueIndexKeyTest_29, BecomesObjectAndCreatesKey_29) {
    Value v; // default-constructed (non-object)
    std::string key = "k";

    Value &slot = v[key];           // should convert to OBJECT and create entry
    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(Value::OBJECT, v.getType());
    ASSERT_EQ(1u, v.getObject().count(key));

    // Writing through the returned reference must reflect in the object map.
    slot = 42;
    ASSERT_TRUE(v.getObject().at(key).isInteger());
    EXPECT_EQ(42, v.getObject().at(key).getInteger());
}

// Indexing an already-object value with an existing key should return a reference
// to the existing entry (mutation via the ref updates the map entry, size unchanged).
TEST_F(ValueIndexKeyTest_29, ReturnsReferenceToExistingEntry_29) {
    Object o;
    o["x"] = Value(7);
    Value v(o);

    std::string key = "x";
    size_t beforeSize = v.getObject().size();

    Value &ref = v[key];
    ASSERT_TRUE(ref.isInteger());
    EXPECT_EQ(7, ref.getInteger());

    ref = 9;
    EXPECT_EQ(beforeSize, v.getObject().size()); // no new keys
    ASSERT_TRUE(v.getObject().at(key).isInteger());
    EXPECT_EQ(9, v.getObject().at(key).getInteger());
}

// Indexing an already-object value with a new key should insert that key.
TEST_F(ValueIndexKeyTest_29, InsertsNewKeyWhenMissing_29) {
    Object o;
    o["a"] = Value("hello");
    Value v(o);

    std::string newKey = "b";
    ASSERT_EQ(0u, v.getObject().count(newKey));

    Value &slot = v[newKey];  // should create entry
    // Assign something observable
    slot = true;

    ASSERT_EQ(1u, v.getObject().count(newKey));
    ASSERT_TRUE(v.getObject().at(newKey).isBoolean());
    EXPECT_TRUE(v.getObject().at(newKey).getBoolean());
}

// Indexing a non-object numeric value should convert it to an object and set the key.
TEST_F(ValueIndexKeyTest_29, ConvertsNonObjectToObjectOnIndex_29) {
    Value v(123); // INTEGER initially
    std::string key = "num";

    v[key] = "str";
    EXPECT_TRUE(v.isObject());
    ASSERT_EQ(1u, v.getObject().count(key));
    ASSERT_TRUE(v.getObject().at(key).isString());
    EXPECT_EQ(std::string("str"), v.getObject().at(key).getString());
}

// Supports empty-string key as a boundary case.
TEST_F(ValueIndexKeyTest_29, SupportsEmptyStringKey_29) {
    Value v;
    std::string emptyKey = "";

    v[emptyKey] = 1;
    EXPECT_TRUE(v.isObject());
    ASSERT_EQ(1u, v.getObject().count(emptyKey));
    ASSERT_TRUE(v.getObject().at(emptyKey).isInteger());
    EXPECT_EQ(1, v.getObject().at(emptyKey).getInteger());
}

// Supports special characters in keys.
TEST_F(ValueIndexKeyTest_29, SupportsSpecialCharacterKeys_29) {
    Value v;
    std::string key = "weird key!@#$%^&*()[]{}:/\\?<>|~`";

    v[key] = 3.14;
    EXPECT_TRUE(v.isObject());
    ASSERT_EQ(1u, v.getObject().count(key));
    ASSERT_TRUE(v.getObject().at(key).isDouble());
    EXPECT_DOUBLE_EQ(3.14, v.getObject().at(key).getDouble());
}

// Chaining: indexing creates nested objects via returned references.
TEST_F(ValueIndexKeyTest_29, ChainedIndexingCreatesNestedObjects_29) {
    Value v;

    v[std::string("outer")][std::string("inner")] = 5;

    ASSERT_TRUE(v.isObject());
    ASSERT_EQ(1u, v.getObject().count("outer"));
    const Value &outer = v.getObject().at("outer");
    ASSERT_TRUE(outer.isObject());
    ASSERT_EQ(1u, outer.getObject().count("inner"));
    const Value &inner = outer.getObject().at("inner");
    ASSERT_TRUE(inner.isInteger());
    EXPECT_EQ(5, inner.getInteger());
}
