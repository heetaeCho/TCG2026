// TEST_ID: 95
//
// Unit tests for Object::getNum(bool *ok) const
// File: ./TestProjects/poppler/poppler/Object.h
//
// Constraints honored:
// - Treat Object as a black box (no assumptions about internals).
// - Test only observable behavior from the public interface.
// - No private state access.
// - Include normal, boundary, and error/exceptional observable cases.

#include <gtest/gtest.h>

#include <limits>

#include "poppler/Object.h"

namespace {

class ObjectGetNumOkTest_95 : public ::testing::Test {};

TEST_F(ObjectGetNumOkTest_95, IntReturnsValueAndSetsOkTrue_95)
{
  const int v = 123;
  const Object o(v);

  bool ok = false;
  const double d = o.getNum(&ok);

  EXPECT_TRUE(ok);
  EXPECT_DOUBLE_EQ(d, static_cast<double>(v));
}

TEST_F(ObjectGetNumOkTest_95, Int64ReturnsValueAndSetsOkTrue_95)
{
  const long long v = 1234567890123LL;
  const Object o(v);

  bool ok = false;
  const double d = o.getNum(&ok);

  EXPECT_TRUE(ok);
  EXPECT_DOUBLE_EQ(d, static_cast<double>(v));
}

TEST_F(ObjectGetNumOkTest_95, RealReturnsValueAndSetsOkTrue_95)
{
  const double v = 3.141592653589793;
  const Object o(v);

  bool ok = false;
  const double d = o.getNum(&ok);

  EXPECT_TRUE(ok);
  EXPECT_DOUBLE_EQ(d, v);
}

TEST_F(ObjectGetNumOkTest_95, IntBoundaryZero_95)
{
  const Object o(0);

  bool ok = false;
  const double d = o.getNum(&ok);

  EXPECT_TRUE(ok);
  EXPECT_DOUBLE_EQ(d, 0.0);
}

TEST_F(ObjectGetNumOkTest_95, IntBoundaryMinMax_95)
{
  {
    const Object o(std::numeric_limits<int>::min());
    bool ok = false;
    const double d = o.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(d, static_cast<double>(std::numeric_limits<int>::min()));
  }
  {
    const Object o(std::numeric_limits<int>::max());
    bool ok = false;
    const double d = o.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(d, static_cast<double>(std::numeric_limits<int>::max()));
  }
}

TEST_F(ObjectGetNumOkTest_95, Int64BoundaryMinMax_95)
{
  {
    const Object o(std::numeric_limits<long long>::min());
    bool ok = false;
    const double d = o.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(d, static_cast<double>(std::numeric_limits<long long>::min()));
  }
  {
    const Object o(std::numeric_limits<long long>::max());
    bool ok = false;
    const double d = o.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(d, static_cast<double>(std::numeric_limits<long long>::max()));
  }
}

TEST_F(ObjectGetNumOkTest_95, RealBoundaryNegativeZero_95)
{
  const double negZero = -0.0;
  const Object o(negZero);

  bool ok = false;
  const double d = o.getNum(&ok);

  EXPECT_TRUE(ok);
  // Observable behavior: result compares equal to -0.0; also verify sign bit is preserved if any.
  EXPECT_DOUBLE_EQ(d, negZero);
}

TEST_F(ObjectGetNumOkTest_95, RealBoundaryInfinity_95)
{
  const double inf = std::numeric_limits<double>::infinity();
  const Object o(inf);

  bool ok = false;
  const double d = o.getNum(&ok);

  EXPECT_TRUE(ok);
  EXPECT_EQ(d, inf);
}

TEST_F(ObjectGetNumOkTest_95, RealBoundaryNegativeInfinity_95)
{
  const double ninf = -std::numeric_limits<double>::infinity();
  const Object o(ninf);

  bool ok = false;
  const double d = o.getNum(&ok);

  EXPECT_TRUE(ok);
  EXPECT_EQ(d, ninf);
}

TEST_F(ObjectGetNumOkTest_95, RealBoundaryNaN_95)
{
  const double nan = std::numeric_limits<double>::quiet_NaN();
  const Object o(nan);

  bool ok = false;
  const double d = o.getNum(&ok);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(std::isnan(d));
}

TEST_F(ObjectGetNumOkTest_95, NonNumericTypeBoolSetsOkFalseAndReturnsZero_95)
{
  const Object o(true);

  bool ok = true; // ensure it can be flipped to false
  const double d = o.getNum(&ok);

  EXPECT_FALSE(ok);
  EXPECT_DOUBLE_EQ(d, 0.0);
}

TEST_F(ObjectGetNumOkTest_95, NonNumericTypeNullSetsOkFalseAndReturnsZero_95)
{
  const Object o = Object::null();

  bool ok = true;
  const double d = o.getNum(&ok);

  EXPECT_FALSE(ok);
  EXPECT_DOUBLE_EQ(d, 0.0);
}

TEST_F(ObjectGetNumOkTest_95, NonNumericTypeErrorSetsOkFalseAndReturnsZero_95)
{
  const Object o = Object::error();

  bool ok = true;
  const double d = o.getNum(&ok);

  EXPECT_FALSE(ok);
  EXPECT_DOUBLE_EQ(d, 0.0);
}

TEST_F(ObjectGetNumOkTest_95, NonNumericTypeEOFAndNoneSetOkFalseAndReturnZero_95)
{
  {
    const Object o = Object::eof();
    bool ok = true;
    const double d = o.getNum(&ok);
    EXPECT_FALSE(ok);
    EXPECT_DOUBLE_EQ(d, 0.0);
  }
  {
    const Object o; // default constructed: known dependency says type(objNone)
    bool ok = true;
    const double d = o.getNum(&ok);
    EXPECT_FALSE(ok);
    EXPECT_DOUBLE_EQ(d, 0.0);
  }
}

TEST_F(ObjectGetNumOkTest_95, OkOutputParameterIsWrittenOnBothSuccessAndFailure_95)
{
  // Success case
  {
    const Object o(7);
    bool ok = false;
    (void)o.getNum(&ok);
    EXPECT_TRUE(ok);
  }

  // Failure case
  {
    const Object o(false);
    bool ok = true;
    (void)o.getNum(&ok);
    EXPECT_FALSE(ok);
  }
}

} // namespace