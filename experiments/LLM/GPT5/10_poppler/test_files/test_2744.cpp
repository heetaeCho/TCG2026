// Object_int_ctor_test_2744.cc
#include <gtest/gtest.h>

#include <climits>
#include <cmath>

#include "Object.h"

class ObjectTest_2744 : public ::testing::Test {};

// Normal operation: constructing from int yields an int object and preserves value.
TEST_F(ObjectTest_2744, IntCtor_SetsTypeAndValue_2744)
{
    Object obj(42);

    EXPECT_TRUE(obj.isInt());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isReal());
    EXPECT_TRUE(obj.isNum());

    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);

    // Numeric accessors should be consistent for an integer object.
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
    EXPECT_DOUBLE_EQ(obj.getReal(), 42.0); // if implemented to return numeric for ints
}

// Boundary: zero.
TEST_F(ObjectTest_2744, IntCtor_Zero_2744)
{
    Object obj(0);

    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 0);
    EXPECT_DOUBLE_EQ(obj.getNum(), 0.0);
}

// Boundary: INT_MAX.
TEST_F(ObjectTest_2744, IntCtor_IntMax_2744)
{
    Object obj(INT_MAX);

    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), INT_MAX);
    EXPECT_DOUBLE_EQ(obj.getNum(), static_cast<double>(INT_MAX));
}

// Boundary: INT_MIN.
TEST_F(ObjectTest_2744, IntCtor_IntMin_2744)
{
    Object obj(INT_MIN);

    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), INT_MIN);
    EXPECT_DOUBLE_EQ(obj.getNum(), static_cast<double>(INT_MIN));
}

// Observable behavior: copy() produces an object with the same observable int value/type.
TEST_F(ObjectTest_2744, Copy_PreservesIntObservableState_2744)
{
    Object original(-7);

    const Object copied = original.copy();

    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getType(), objInt);
    EXPECT_EQ(copied.getInt(), -7);
    EXPECT_DOUBLE_EQ(copied.getNum(), -7.0);

    // Also ensure original remains unchanged (observable).
    EXPECT_TRUE(original.isInt());
    EXPECT_EQ(original.getInt(), -7);
}

// Observable behavior: deepCopy() produces an object with the same observable int value/type.
TEST_F(ObjectTest_2744, DeepCopy_PreservesIntObservableState_2744)
{
    Object original(123456);

    const Object copied = original.deepCopy();

    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getType(), objInt);
    EXPECT_EQ(copied.getInt(), 123456);
    EXPECT_DOUBLE_EQ(copied.getNum(), 123456.0);

    EXPECT_TRUE(original.isInt());
    EXPECT_EQ(original.getInt(), 123456);
}

// Error/exceptional cases: not applicable/observable for this ctor via the public interface.
// (No external interactions to verify for this constructor.)