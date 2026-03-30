// TEST_ID: 93
// File: Object_getReal_unittest_93.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <utility>

#include "poppler/Object.h"

class ObjectGetRealTest_93 : public ::testing::Test {};

// Normal operation: constructed as real, getReal returns the same value.
TEST_F(ObjectGetRealTest_93, ReturnsStoredRealValue_93) {
  const double v = 3.141592653589793;
  const Object obj(v);

  EXPECT_TRUE(obj.isReal());
  EXPECT_EQ(obj.getType(), objReal);
  EXPECT_DOUBLE_EQ(obj.getReal(), v);
}

// Normal operation: const correctness.
TEST_F(ObjectGetRealTest_93, WorksOnConstObject_93) {
  const Object obj(2.5);
  EXPECT_TRUE(obj.isReal());
  EXPECT_DOUBLE_EQ(obj.getReal(), 2.5);
}

// Boundary: +0.0 and -0.0 are preserved by IEEE rules for signbit.
TEST_F(ObjectGetRealTest_93, HandlesPositiveAndNegativeZero_93) {
  const Object posZero(0.0);
  ASSERT_TRUE(posZero.isReal());
  EXPECT_DOUBLE_EQ(posZero.getReal(), 0.0);
  EXPECT_FALSE(std::signbit(posZero.getReal()));

  const Object negZero(-0.0);
  ASSERT_TRUE(negZero.isReal());
  EXPECT_DOUBLE_EQ(negZero.getReal(), 0.0);
  EXPECT_TRUE(std::signbit(negZero.getReal()));
}

// Boundary: extreme finite values.
TEST_F(ObjectGetRealTest_93, HandlesExtremeFiniteValues_93) {
  const double maxv = std::numeric_limits<double>::max();
  const double minPos = std::numeric_limits<double>::min(); // smallest positive normal
  const double denormMin = std::numeric_limits<double>::denorm_min();

  const Object oMax(maxv);
  ASSERT_TRUE(oMax.isReal());
  EXPECT_DOUBLE_EQ(oMax.getReal(), maxv);

  const Object oMin(minPos);
  ASSERT_TRUE(oMin.isReal());
  EXPECT_DOUBLE_EQ(oMin.getReal(), minPos);

  // denorm_min may be 0 on platforms without subnormals; still valid to test round-trip.
  const Object oDenorm(denormMin);
  ASSERT_TRUE(oDenorm.isReal());
  EXPECT_DOUBLE_EQ(oDenorm.getReal(), denormMin);
}

// Boundary: infinities.
TEST_F(ObjectGetRealTest_93, HandlesInfinity_93) {
  const double posInf = std::numeric_limits<double>::infinity();
  const double negInf = -std::numeric_limits<double>::infinity();

  const Object oPos(posInf);
  ASSERT_TRUE(oPos.isReal());
  EXPECT_TRUE(std::isinf(oPos.getReal()));
  EXPECT_GT(oPos.getReal(), 0.0);

  const Object oNeg(negInf);
  ASSERT_TRUE(oNeg.isReal());
  EXPECT_TRUE(std::isinf(oNeg.getReal()));
  EXPECT_LT(oNeg.getReal(), 0.0);
}

// Boundary: NaN round-trip (cannot compare with ==).
TEST_F(ObjectGetRealTest_93, HandlesNaN_93) {
  const double nanv = std::numeric_limits<double>::quiet_NaN();
  const Object obj(nanv);

  ASSERT_TRUE(obj.isReal());
  EXPECT_TRUE(std::isnan(obj.getReal()));
}

// Error/exceptional (observable via interface): when not constructed as real, isReal is false.
// We intentionally do NOT call getReal() in this case, because behavior is guarded by
// OBJECT_TYPE_CHECK and may be build-configuration dependent.
TEST_F(ObjectGetRealTest_93, IsRealIsFalseForNonRealObjects_93) {
  const Object intObj(42);
  EXPECT_FALSE(intObj.isReal());
  EXPECT_NE(intObj.getType(), objReal);

  const Object boolObj(true);
  EXPECT_FALSE(boolObj.isReal());
  EXPECT_NE(boolObj.getType(), objReal);

  const Object noneObj; // default ctor => objNone per provided declaration
  EXPECT_FALSE(noneObj.isReal());
  EXPECT_NE(noneObj.getType(), objReal);
}

// External interaction is not applicable here (no callbacks/dependencies).
// Still cover move behavior as an observable public operation.
TEST_F(ObjectGetRealTest_93, MoveConstructionPreservesRealValue_93) {
  Object src(1.25);
  Object dst(std::move(src));

  EXPECT_TRUE(dst.isReal());
  EXPECT_EQ(dst.getType(), objReal);
  EXPECT_DOUBLE_EQ(dst.getReal(), 1.25);
}