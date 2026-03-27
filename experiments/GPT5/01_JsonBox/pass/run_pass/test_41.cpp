// tests/value_isNull_41_test.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueIsNullTest_41 : public ::testing::Test {};

TEST_F(ValueIsNullTest_41, DefaultCtor_IsNull_41) {
    Value v;
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueIsNullTest_41, StringCtor_IsNotNull_41) {
    Value v1(std::string("hello"));
    Value v2("world");
    EXPECT_FALSE(v1.isNull());
    EXPECT_FALSE(v2.isNull());
}

TEST_F(ValueIsNullTest_41, IntegerCtor_IsNotNull_41) {
    Value v(123);
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueIsNullTest_41, DoubleCtor_IsNotNull_41) {
    Value v(3.14);
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueIsNullTest_41, BooleanCtor_IsNotNull_41) {
    Value vt(true);
    Value vf(false);
    EXPECT_FALSE(vt.isNull());
    EXPECT_FALSE(vf.isNull());
}

TEST_F(ValueIsNullTest_41, ObjectCtor_IsNotNull_41) {
    Value::Object o;
    o.insert(std::make_pair(std::string("k"), Value(1)));
    Value v(o);
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueIsNullTest_41, ArrayCtor_IsNotNull_41) {
    Value::Array a;
    a.push_back(Value(1));
    a.push_back(Value("x"));
    Value v(a);
    EXPECT_FALSE(v.isNull());
}

TEST_F(ValueIsNullTest_41, SetNull_FromNonNull_BecomesNull_41) {
    Value v("not null");
    ASSERT_FALSE(v.isNull());  // precondition via public API
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueIsNullTest_41, SetNull_Idempotent_WhenAlreadyNull_41) {
    Value v;                   // default-constructed is null
    ASSERT_TRUE(v.isNull());
    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueIsNullTest_41, CopyCtor_PreservesNullness_41) {
    Value n;                   // null
    Value nn("x");             // not null
    Value c1(n);
    Value c2(nn);
    EXPECT_TRUE(c1.isNull());
    EXPECT_FALSE(c2.isNull());
}

TEST_F(ValueIsNullTest_41, CopyAssign_ChangesNullness_ToMatchSource_41) {
    Value dst("x");            // not null
    Value srcNull;             // null
    dst = srcNull;
    EXPECT_TRUE(dst.isNull());

    Value srcNonNull(42);
    dst = srcNonNull;
    EXPECT_FALSE(dst.isNull());
}

TEST_F(ValueIsNullTest_41, AssignPrimitiveTypes_AffectNullness_41) {
    Value v;                   // null
    ASSERT_TRUE(v.isNull());

    v = 7;
    EXPECT_FALSE(v.isNull());

    v = 2.5;
    EXPECT_FALSE(v.isNull());

    v = std::string("str");
    EXPECT_FALSE(v.isNull());

    v = true;
    EXPECT_FALSE(v.isNull());

    Value::Object o;
    v = o;
    EXPECT_FALSE(v.isNull());

    Value::Array a;
    v = a;
    EXPECT_FALSE(v.isNull());

    v.setNull();
    EXPECT_TRUE(v.isNull());
}

TEST_F(ValueIsNullTest_41, MixedAssignments_AndSetNull_ToggleNullness_41) {
    Value v("start");
    EXPECT_FALSE(v.isNull());

    v.setNull();
    EXPECT_TRUE(v.isNull());

    v = "again";
    EXPECT_FALSE(v.isNull());

    v.setNull();
    EXPECT_TRUE(v.isNull());
}
