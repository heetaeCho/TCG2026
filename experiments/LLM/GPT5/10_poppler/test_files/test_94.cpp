// TEST_ID: 94
// File: object_getnum_test_94.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "poppler/Object.h"

namespace {

class ObjectGetNumTest_94 : public ::testing::Test {};

TEST_F(ObjectGetNumTest_94, IntConvertsToDouble_94) {
  const int v = 42;
  const Object o(v);

  EXPECT_TRUE(o.isInt());
  EXPECT_TRUE(o.isNum());
  EXPECT_DOUBLE_EQ(o.getNum(), static_cast<double>(v));
}

TEST_F(ObjectGetNumTest_94, Int64ConvertsToDouble_94) {
  const long long v = 1234567890123LL;
  const Object o(v);

  EXPECT_TRUE(o.isInt64());
  EXPECT_TRUE(o.isNum());
  EXPECT_DOUBLE_EQ(o.getNum(), static_cast<double>(v));
}

TEST_F(ObjectGetNumTest_94, RealReturnsSameValue_94) {
  const double v = 3.141592653589793;
  const Object o(v);

  EXPECT_TRUE(o.isReal());
  EXPECT_TRUE(o.isNum());
  EXPECT_DOUBLE_EQ(o.getNum(), v);
}

TEST_F(ObjectGetNumTest_94, IntBoundaryValuesConvertToDouble_94) {
  const int minV = std::numeric_limits<int>::min();
  const int maxV = std::numeric_limits<int>::max();

  const Object omin(minV);
  const Object omax(maxV);

  EXPECT_TRUE(omin.isInt());
  EXPECT_TRUE(omax.isInt());

  EXPECT_DOUBLE_EQ(omin.getNum(), static_cast<double>(minV));
  EXPECT_DOUBLE_EQ(omax.getNum(), static_cast<double>(maxV));
}

TEST_F(ObjectGetNumTest_94, Int64BoundaryValuesConvertToDouble_94) {
  const long long minV = std::numeric_limits<long long>::min();
  const long long maxV = std::numeric_limits<long long>::max();

  const Object omin(minV);
  const Object omax(maxV);

  EXPECT_TRUE(omin.isInt64());
  EXPECT_TRUE(omax.isInt64());

  // Note: large int64 values may not be exactly representable as double.
  // We compare to the same cast the API is expected to produce.
  EXPECT_DOUBLE_EQ(omin.getNum(), static_cast<double>(minV));
  EXPECT_DOUBLE_EQ(omax.getNum(), static_cast<double>(maxV));
}

TEST_F(ObjectGetNumTest_94, RealSpecialValuesPropagate_94) {
  const double inf = std::numeric_limits<double>::infinity();
  const double negInf = -std::numeric_limits<double>::infinity();
  const double nanV = std::numeric_limits<double>::quiet_NaN();

  const Object oinf(inf);
  const Object onegInf(negInf);
  const Object onan(nanV);

  EXPECT_TRUE(oinf.isReal());
  EXPECT_TRUE(onegInf.isReal());
  EXPECT_TRUE(onan.isReal());

  EXPECT_TRUE(std::isinf(oinf.getNum()));
  EXPECT_TRUE(std::isinf(onegInf.getNum()));
  EXPECT_LT(onegInf.getNum(), 0.0);

  const double gotNaN = onan.getNum();
  EXPECT_TRUE(std::isnan(gotNaN));
}

// Exceptional/error behavior for getNum() on non-number types is typically enforced
// via internal checks (often assertions). Since that behavior can differ by build
// configuration, keep the test to debug-like builds where death tests are meaningful.
#if GTEST_HAS_DEATH_TEST && !defined(NDEBUG)
TEST_F(ObjectGetNumTest_94, NonNumericTypeTriggersCheckInDebug_94) {
  const Object ob(true);  // bool, not a numeric objInt/objInt64/objReal
  ASSERT_TRUE(ob.isBool());
  ASSERT_FALSE(ob.isNum());

  EXPECT_DEATH({ (void)ob.getNum(); }, "");
}
#endif

}  // namespace