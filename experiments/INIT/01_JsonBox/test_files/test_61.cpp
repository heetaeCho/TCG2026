// File: tests/ValueSetNullTest_61.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueSetNullTest_61 : public ::testing::Test {};

// Normal: setNull() marks the value as null
TEST_F(ValueSetNullTest_61, SetNull_MarksValueAsNull_61) {
    Value v("hello");
    ASSERT_FALSE(v.isNull());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

// Normal: getType() becomes NULL_VALUE after setNull()
TEST_F(ValueSetNullTest_61, SetNull_SetsTypeToNull_61) {
    Value v(123);
    v.setNull();
    EXPECT_EQ(Value::Type::NULL_VALUE, v.getType());
}

// Boundary: calling setNull() multiple times remains null (idempotent)
TEST_F(ValueSetNullTest_61, SetNull_IsIdempotent_61) {
    Value v(true);
    v.setNull();
    EXPECT_TRUE(v.isNull());
    v.setNull();
    EXPECT_TRUE(v.isNull());
    EXPECT_EQ(Value::Type::NULL_VALUE, v.getType());
}

// Observable behavior: tryGet* return provided defaults when value is null
TEST_F(ValueSetNullTest_61, SetNull_MakesTryGetReturnDefaults_61) {
    Value v("anything");
    v.setNull();

    const std::string sDefault = "default";
    EXPECT_EQ(sDefault, v.tryGetString(sDefault));

    const int iDefault = 42;
    EXPECT_EQ(iDefault, v.tryGetInteger(iDefault));

    const double dDefault = 3.14;
    EXPECT_DOUBLE_EQ(dDefault, v.tryGetDouble(dDefault));

    const float fDefault = 2.718f;
    EXPECT_FLOAT_EQ(fDefault, v.tryGetFloat(fDefault));

    const bool bDefault = true;
    EXPECT_EQ(bDefault, v.tryGetBoolean(bDefault));
}

// Post-condition: after setNull(), setting to another type works as normal
TEST_F(ValueSetNullTest_61, SetNull_ThenSetString_Works_61) {
    Value v(99);
    v.setNull();
    ASSERT_TRUE(v.isNull());

    const std::string newVal = "now-string";
    v.setString(newVal);

    EXPECT_TRUE(v.isString());
    EXPECT_FALSE(v.isNull());
    EXPECT_EQ(Value::Type::STRING, v.getType());
    EXPECT_EQ(newVal, v.getString());
}
