// File: Value_setArray_tests_57.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using JsonBox::Value;
using JsonBox::Array;

class ValueSetArrayTest_57 : public ::testing::Test {};

// Normal operation: setting an array on a null value produces an array with identical contents.
TEST_F(ValueSetArrayTest_57, SetArray_FromNullToArray_CorrectTypeAndContents_57) {
    Value v; // default-constructed (NULL_VALUE per interface)
    Array input = { Value(1), Value(2), Value(3) };

    v.setArray(input);

    EXPECT_TRUE(v.isArray());
    ASSERT_EQ(v.getArray().size(), input.size());
    EXPECT_EQ(v.getArray(), input);  // relies on Value::operator==
    EXPECT_FALSE(v.isNull());
}

// Normal operation: overwriting an existing array replaces its contents (observable via getArray()).
TEST_F(ValueSetArrayTest_57, SetArray_OverwritesExistingArrayContents_57) {
    Array initial = { Value(10), Value(20) };
    Value v(initial);  // construct as ARRAY

    Array replacement = { Value(99) };
    v.setArray(replacement);

    EXPECT_TRUE(v.isArray());
    ASSERT_EQ(v.getArray().size(), replacement.size());
    EXPECT_EQ(v.getArray(), replacement);
}

// Boundary: setting an empty array results in an array type with size 0.
TEST_F(ValueSetArrayTest_57, SetArray_EmptyArrayHandled_57) {
    Value v;
    Array empty;

    v.setArray(empty);

    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}

// Observable copy semantics: mutating the input after setArray() does not change the stored array.
TEST_F(ValueSetArrayTest_57, SetArray_DoesNotAliasInput_57) {
    Value v;
    Array input = { Value(1) };

    v.setArray(input);
    // mutate the original container after setting
    input.push_back(Value(2));

    // stored value should not reflect the mutation
    ASSERT_EQ(v.getArray().size(), 1u);
    EXPECT_EQ(v.getArray(), Array({ Value(1) }));
}

// Mixed types & nesting: structure and values are preserved.
TEST_F(ValueSetArrayTest_57, SetArray_WithNestedValues_PreservesStructure_57) {
    Array nested = { Value("inner"), Value(42) };
    Array input = { Value("text"), Value(7), Value(true), Value(nested) };

    Value v;
    v.setArray(input);

    EXPECT_TRUE(v.isArray());
    ASSERT_EQ(v.getArray().size(), input.size());
    EXPECT_EQ(v.getArray(), input);
}

// Multiple sequential sets: final state matches the last input given.
TEST_F(ValueSetArrayTest_57, SetArray_MultipleSequentialSets_FinalStateMatchesLast_57) {
    Value v;

    Array first = { Value(1), Value(2) };
    Array second = { Value(3) };
    Array third; // empty

    v.setArray(first);
    EXPECT_EQ(v.getArray(), first);

    v.setArray(second);
    EXPECT_EQ(v.getArray(), second);

    v.setArray(third);
    EXPECT_EQ(v.getArray(), third);
    EXPECT_TRUE(v.isArray());
    EXPECT_EQ(v.getArray().size(), 0u);
}
