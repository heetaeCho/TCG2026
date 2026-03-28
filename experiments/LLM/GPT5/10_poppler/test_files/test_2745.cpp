// ObjectRealCtorTest_2745.cc
#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "poppler/Object.h"

namespace {

class ObjectTest_2745 : public ::testing::Test {};

// Normal operation: constructing a real Object exposes the expected observable behavior.
TEST_F(ObjectTest_2745, RealConstructorSetsTypeAndValue_2745)
{
    const double v = 3.141592653589793;
    Object obj(v);

    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_TRUE(obj.isReal());
    EXPECT_TRUE(obj.isNum());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isNull());

    EXPECT_DOUBLE_EQ(obj.getReal(), v);
    EXPECT_DOUBLE_EQ(obj.getNum(), v);

    bool ok = false;
    EXPECT_DOUBLE_EQ(obj.getNum(&ok), v);
    EXPECT_TRUE(ok);
}

// Boundary values: zero, negative, and large magnitude.
TEST_F(ObjectTest_2745, RealConstructorHandlesCommonBoundaries_2745)
{
    {
        const double v = 0.0;
        Object obj(v);
        EXPECT_TRUE(obj.isReal());
        EXPECT_DOUBLE_EQ(obj.getReal(), v);
        EXPECT_DOUBLE_EQ(obj.getNum(), v);
    }
    {
        const double v = -0.0;
        Object obj(v);
        EXPECT_TRUE(obj.isReal());
        // Preserve sign of zero if the implementation does.
        EXPECT_EQ(std::signbit(obj.getReal()), std::signbit(v));
        EXPECT_EQ(std::signbit(obj.getNum()), std::signbit(v));
    }
    {
        const double v = -12345.25;
        Object obj(v);
        EXPECT_TRUE(obj.isReal());
        EXPECT_DOUBLE_EQ(obj.getReal(), v);
        EXPECT_DOUBLE_EQ(obj.getNum(), v);
    }
    {
        const double v = std::numeric_limits<double>::max();
        Object obj(v);
        EXPECT_TRUE(obj.isReal());
        EXPECT_DOUBLE_EQ(obj.getReal(), v);
        EXPECT_DOUBLE_EQ(obj.getNum(), v);
    }
}

// Boundary values: infinity and NaN.
TEST_F(ObjectTest_2745, RealConstructorHandlesInfAndNaN_2745)
{
    {
        const double v = std::numeric_limits<double>::infinity();
        Object obj(v);
        EXPECT_TRUE(obj.isReal());
        EXPECT_TRUE(std::isinf(obj.getReal()));
        EXPECT_TRUE(std::isinf(obj.getNum()));
        EXPECT_GT(obj.getReal(), 0.0);
        EXPECT_GT(obj.getNum(), 0.0);

        bool ok = false;
        const double n = obj.getNum(&ok);
        EXPECT_TRUE(ok);
        EXPECT_TRUE(std::isinf(n));
    }
    {
        const double v = -std::numeric_limits<double>::infinity();
        Object obj(v);
        EXPECT_TRUE(obj.isReal());
        EXPECT_TRUE(std::isinf(obj.getReal()));
        EXPECT_TRUE(std::isinf(obj.getNum()));
        EXPECT_LT(obj.getReal(), 0.0);
        EXPECT_LT(obj.getNum(), 0.0);

        bool ok = false;
        const double n = obj.getNum(&ok);
        EXPECT_TRUE(ok);
        EXPECT_TRUE(std::isinf(n));
        EXPECT_LT(n, 0.0);
    }
    {
        const double v = std::numeric_limits<double>::quiet_NaN();
        Object obj(v);
        EXPECT_TRUE(obj.isReal());
        EXPECT_TRUE(std::isnan(obj.getReal()));
        EXPECT_TRUE(std::isnan(obj.getNum()));

        bool ok = false;
        const double n = obj.getNum(&ok);
        EXPECT_TRUE(ok);
        EXPECT_TRUE(std::isnan(n));
    }
}

// Observable behavior of copy/deepCopy for a real object (no assumptions about internal representation).
TEST_F(ObjectTest_2745, CopyAndDeepCopyPreserveRealValue_2745)
{
    const double v = 42.5;
    Object obj(v);

    const Object copied = obj.copy();
    EXPECT_EQ(copied.getType(), objReal);
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), v);

    const Object deep = obj.deepCopy();
    EXPECT_EQ(deep.getType(), objReal);
    EXPECT_TRUE(deep.isReal());
    EXPECT_DOUBLE_EQ(deep.getReal(), v);
}

// Transition to null should be observable and not crash.
TEST_F(ObjectTest_2745, SetToNullAfterRealConstruction_2745)
{
    Object obj(1.25);
    ASSERT_TRUE(obj.isReal());

    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isNum());
}

} // namespace