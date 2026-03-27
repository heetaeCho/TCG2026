// File: tests/Value_IsBoolean_Test_40.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueIsBooleanTest_40 : public ::testing::Test {};

// --- Normal operation ---

TEST_F(ValueIsBooleanTest_40, DefaultIsNotBoolean_40) {
    Value v;
    EXPECT_FALSE(v.isBoolean());
}

TEST_F(ValueIsBooleanTest_40, ConstructTrueIsBoolean_40) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());  // observable behavior: returns stored bool when boolean
}

TEST_F(ValueIsBooleanTest_40, ConstructFalseIsBoolean_40) {
    Value v(false);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_FALSE(v.getBoolean());
}

TEST_F(ValueIsBooleanTest_40, SetBooleanMakesItBoolean_40) {
    Value v;
    v.setBoolean(true);
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

// --- Type transitions ---

TEST_F(ValueIsBooleanTest_40, AssignBoolTogglesToBoolean_40) {
    Value v(std::string("x"));
    ASSERT_FALSE(v.isBoolean());
    v = true;
    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());
}

TEST_F(ValueIsBooleanTest_40, AssignNonBoolClearsBooleanStatus_40) {
    Value v(true);
    ASSERT_TRUE(v.isBoolean());
    v = std::string("not-bool");
    EXPECT_FALSE(v.isBoolean());

    v = 123;         // integer
    EXPECT_FALSE(v.isBoolean());

    v = 1.5;         // double
    EXPECT_FALSE(v.isBoolean());

    Value::Array arr;
    v = arr;         // array
    EXPECT_FALSE(v.isBoolean());

    Value::Object obj;
    v = obj;         // object
    EXPECT_FALSE(v.isBoolean());
}

TEST_F(ValueIsBooleanTest_40, SetNullClearsBooleanStatus_40) {
    Value v(false);
    ASSERT_TRUE(v.isBoolean());
    v.setNull();
    EXPECT_FALSE(v.isBoolean());
}

// --- Copy semantics ---

TEST_F(ValueIsBooleanTest_40, CopyConstructorPreservesBooleanType_40) {
    Value src(true);
    Value copy(src);
    EXPECT_TRUE(copy.isBoolean());
    EXPECT_TRUE(copy.getBoolean());
}

TEST_F(ValueIsBooleanTest_40, CopyAssignPreservesBooleanType_40) {
    Value a(false);
    Value b(std::string("s"));
    b = a;
    EXPECT_TRUE(b.isBoolean());
    EXPECT_FALSE(b.getBoolean());
}

// --- Boundary / exceptional (observable via API) ---

TEST_F(ValueIsBooleanTest_40, TryGetBooleanRespectsDefaultWhenNotBoolean_40) {
    Value v(std::string("nope"));
    EXPECT_FALSE(v.isBoolean());
    EXPECT_TRUE(v.tryGetBoolean(true));
    EXPECT_FALSE(v.tryGetBoolean(false));
}

TEST_F(ValueIsBooleanTest_40, TryGetBooleanReturnsStoredWhenBoolean_40) {
    Value v(true);
    EXPECT_TRUE(v.isBoolean());
    // Should ignore default because it's already a boolean
    EXPECT_TRUE(v.tryGetBoolean(false));
    v.setBoolean(false);
    EXPECT_FALSE(v.tryGetBoolean(true));
}

// --- Cross-type constructors sanity ---

TEST_F(ValueIsBooleanTest_40, ConstructOtherTypesAreNotBoolean_40) {
    Value vi(42);
    EXPECT_FALSE(vi.isBoolean());

    Value vd(3.14);
    EXPECT_FALSE(vd.isBoolean());

    Value vs("hello");
    EXPECT_FALSE(vs.isBoolean());

    Value::Array arr;
    Value va(arr);
    EXPECT_FALSE(va.isBoolean());

    Value::Object obj;
    Value vo(obj);
    EXPECT_FALSE(vo.isBoolean());
}
