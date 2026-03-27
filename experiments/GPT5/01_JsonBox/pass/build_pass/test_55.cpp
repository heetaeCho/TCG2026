// File: ValueSetObjectTest_55.cpp

#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using namespace JsonBox;

namespace {

// Small helpers to keep tests tidy
Object MakeObject(std::initializer_list<std::pair<const std::string, Value>> init) {
    return Object(init);
}

} // namespace

// Normal operation: set on a null Value
TEST(ValueSetObjectTest_55, SetObject_FromNull_SetsTypeAndStoresCopy_55) {
    Value v; // default is NULL
    Object obj = MakeObject({{"a", 1}, {"b", "str"}, {"c", true}});

    v.setObject(obj);

    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(Value::OBJECT, v.getType());
    const Object& stored = v.getObject();
    EXPECT_EQ(stored, obj);
}

// From another type (STRING) -> OBJECT
TEST(ValueSetObjectTest_55, SetObject_FromString_ReplacesTypeAndValue_55) {
    Value v("hello");
    Object obj = MakeObject({{"k1", 42}, {"k2", 3.14}});

    v.setObject(obj);

    EXPECT_TRUE(v.isObject());
    EXPECT_EQ(Value::OBJECT, v.getType());
    EXPECT_EQ(v.getObject(), obj);
}

// From OBJECT -> OBJECT (overwrite existing contents, not append/merge)
TEST(ValueSetObjectTest_55, SetObject_FromObject_OverwritesExistingContents_55) {
    Value v(MakeObject({{"x", 1}, {"y", 2}}));
    Object replacement = MakeObject({{"y", 999}, {"z", "new"}});

    v.setObject(replacement);

    ASSERT_TRUE(v.isObject());
    const Object& stored = v.getObject();

    // Should exactly match replacement: "x" removed, "y" replaced, "z" added.
    EXPECT_EQ(stored, replacement);
}

// Boundary: empty object
TEST(ValueSetObjectTest_55, SetObject_InputEmptyObject_ResultsInEmptyObject_55) {
    Value v; // NULL
    Object empty;

    v.setObject(empty);

    ASSERT_TRUE(v.isObject());
    EXPECT_TRUE(v.getObject().empty());
}

// Independence from source after call (copy semantics)
TEST(ValueSetObjectTest_55, SetObject_CopyIndependence_ChangesToSourceDoNotAffectStored_55) {
    Value v;
    Object src = MakeObject({{"a", 1}});

    v.setObject(src);

    // Mutate the source after setting
    src["a"] = 2;
    src["b"] = "added";

    // Stored value should remain as it was at setObject time
    const Object& stored = v.getObject();
    EXPECT_EQ(stored, MakeObject({{"a", 1}}));
}

// Subsequent calls replace (not append), even across multiple prior types
TEST(ValueSetObjectTest_55, SetObject_SubsequentCallsReplaceNotAppend_55) {
    Value v(true); // start as BOOLEAN

    Object first = MakeObject({{"k1", "v1"}});
    v.setObject(first);
    ASSERT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject(), first);

    Object second = MakeObject({{"k2", 123}});
    v.setObject(second);
    ASSERT_TRUE(v.isObject());
    // Expect exactly the second map, no remnants from the first
    EXPECT_EQ(v.getObject(), second);
    EXPECT_EQ(v.getObject().count("k1"), 0u);
}

// Nested structure round-trip (object with nested object/array)
TEST(ValueSetObjectTest_55, SetObject_WithNestedValues_Preserved_55) {
    Object nestedInner = MakeObject({{"ni", -7}});
    Array arr;
    arr.push_back(Value(10));
    arr.push_back(Value("text"));
    arr.push_back(Value(false));

    Object complex = MakeObject({
        {"inner", Value(nestedInner)},
        {"arr", Value(arr)},
        {"num", Value(3.5)}
    });

    Value v;
    v.setObject(complex);

    ASSERT_TRUE(v.isObject());
    EXPECT_EQ(v.getObject(), complex);
}

