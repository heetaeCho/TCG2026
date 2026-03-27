// File: test_value_try_get_boolean_59.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using JsonBox::Value;

// Test fixture (kept simple for clarity/consistency)
class ValueTryGetBooleanTest_59 : public ::testing::Test {};

// Normal operation: when the Value actually holds a boolean `true`, it should return true.
TEST_F(ValueTryGetBooleanTest_59, ReturnsStoredTrueWhenTypeIsBoolean_59) {
    Value v(true);
    EXPECT_TRUE(v.tryGetBoolean(false));  // default ignored; stored true should be returned
    EXPECT_TRUE(v.tryGetBoolean(true));   // still true
}

// Normal operation: when the Value actually holds a boolean `false`, it should return false.
TEST_F(ValueTryGetBooleanTest_59, ReturnsStoredFalseWhenTypeIsBoolean_59) {
    Value v(false);
    EXPECT_FALSE(v.tryGetBoolean(true));   // default ignored; stored false should be returned
    EXPECT_FALSE(v.tryGetBoolean(false));  // still false
}

// Boundary/exceptional (observable): for a non-boolean value (e.g., integer),
// the current implementation returns an EMPTY default (false), not the provided default.
TEST_F(ValueTryGetBooleanTest_59, NonBooleanIntegerReturnsFalseRegardlessOfDefault_59) {
    Value v(123);
    EXPECT_FALSE(v.tryGetBoolean(true));   // despite default=true, implementation returns false
    EXPECT_FALSE(v.tryGetBoolean(false));  // remains false
}

// Boundary/exceptional (observable): for a string value, behavior matches non-boolean path.
TEST_F(ValueTryGetBooleanTest_59, NonBooleanStringReturnsFalseRegardlessOfDefault_59) {
    Value v(std::string("hello"));
    EXPECT_FALSE(v.tryGetBoolean(true));
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// Boundary/exceptional (observable): default-constructed (null) value follows non-boolean path.
TEST_F(ValueTryGetBooleanTest_59, NullValueReturnsFalseRegardlessOfDefault_59) {
    Value v;  // NULL_VALUE
    EXPECT_FALSE(v.tryGetBoolean(true));
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// Boundary/exceptional (observable): array value follows non-boolean path.
TEST_F(ValueTryGetBooleanTest_59, ArrayValueReturnsFalseRegardlessOfDefault_59) {
    JsonBox::Array arr;            // empty array is fine
    arr.push_back(Value(1));       // any content; type is ARRAY
    Value v(arr);
    EXPECT_FALSE(v.tryGetBoolean(true));
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// Boundary/exceptional (observable): object value follows non-boolean path.
TEST_F(ValueTryGetBooleanTest_59, ObjectValueReturnsFalseRegardlessOfDefault_59) {
    JsonBox::Object obj;
    obj["k"] = Value("v");
    Value v(obj);
    EXPECT_FALSE(v.tryGetBoolean(true));
    EXPECT_FALSE(v.tryGetBoolean(false));
}

// Boundary/exceptional (observable): double value follows non-boolean path.
TEST_F(ValueTryGetBooleanTest_59, DoubleValueReturnsFalseRegardlessOfDefault_59) {
    Value v(3.14);
    EXPECT_FALSE(v.tryGetBoolean(true));
    EXPECT_FALSE(v.tryGetBoolean(false));
}
