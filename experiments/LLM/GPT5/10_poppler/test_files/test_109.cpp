// Object_getIntOrInt64_109_test.cpp
#include <gtest/gtest.h>

#include <climits>
#include <limits>

#include "poppler/Object.h"

namespace {

class ObjectGetIntOrInt64Test_109 : public ::testing::Test {};

TEST_F(ObjectGetIntOrInt64Test_109, ReturnsSameValueWhenConstructedFromInt_109)
{
  const int v = 12345;
  Object o(v);

  ASSERT_TRUE(o.isIntOrInt64());
  EXPECT_EQ(o.getIntOrInt64(), static_cast<long long>(v));
}

TEST_F(ObjectGetIntOrInt64Test_109, ReturnsSameValueWhenConstructedFromInt64_109)
{
  const long long v = 1234567890123LL;
  Object o(v);

  ASSERT_TRUE(o.isIntOrInt64());
  EXPECT_EQ(o.getIntOrInt64(), v);
}

TEST_F(ObjectGetIntOrInt64Test_109, HandlesIntBoundaryValues_109)
{
  {
    const int v = std::numeric_limits<int>::min();
    Object o(v);
    ASSERT_TRUE(o.isIntOrInt64());
    EXPECT_EQ(o.getIntOrInt64(), static_cast<long long>(v));
  }
  {
    const int v = std::numeric_limits<int>::max();
    Object o(v);
    ASSERT_TRUE(o.isIntOrInt64());
    EXPECT_EQ(o.getIntOrInt64(), static_cast<long long>(v));
  }
}

TEST_F(ObjectGetIntOrInt64Test_109, HandlesInt64BoundaryValues_109)
{
  {
    const long long v = std::numeric_limits<long long>::min();
    Object o(v);
    ASSERT_TRUE(o.isIntOrInt64());
    EXPECT_EQ(o.getIntOrInt64(), v);
  }
  {
    const long long v = std::numeric_limits<long long>::max();
    Object o(v);
    ASSERT_TRUE(o.isIntOrInt64());
    EXPECT_EQ(o.getIntOrInt64(), v);
  }
}

TEST_F(ObjectGetIntOrInt64Test_109, PreservesValueAfterMoveConstruction_109)
{
  const long long v = 0x123456789ABCDEFLL;
  Object src(v);
  ASSERT_TRUE(src.isIntOrInt64());

  Object moved(std::move(src));
  ASSERT_TRUE(moved.isIntOrInt64());
  EXPECT_EQ(moved.getIntOrInt64(), v);
}

TEST_F(ObjectGetIntOrInt64Test_109, PreservesValueAfterMoveAssignment_109)
{
  const long long v = -987654321098765LL;
  Object src(v);
  ASSERT_TRUE(src.isIntOrInt64());

  Object dst; // objNone
  dst = std::move(src);

  ASSERT_TRUE(dst.isIntOrInt64());
  EXPECT_EQ(dst.getIntOrInt64(), v);
}

TEST_F(ObjectGetIntOrInt64Test_109, ReportsFalseForNonIntegerTypes_109)
{
  EXPECT_FALSE(Object().isIntOrInt64());        // objNone
  EXPECT_FALSE(Object(true).isIntOrInt64());    // objBool
  EXPECT_FALSE(Object(3.14).isIntOrInt64());    // objReal
  EXPECT_FALSE(Object::null().isIntOrInt64());  // objNull
  EXPECT_FALSE(Object::eof().isIntOrInt64());   // objEOF
  EXPECT_FALSE(Object::error().isIntOrInt64()); // objError
}

#ifndef NDEBUG
// In debug builds, Poppler's OBJECT_*_CHECK macros typically assert/abort on type mismatch.
// We only run death tests when assertions are expected to be active.
TEST_F(ObjectGetIntOrInt64Test_109, DiesWhenCalledOnWrongTypeInDebug_109)
{
  Object o(true);
  ASSERT_FALSE(o.isIntOrInt64());

  EXPECT_DEATH_IF_SUPPORTED(
      {
        // NOLINTNEXTLINE: intentional bad call to verify contract enforcement
        (void)o.getIntOrInt64();
      },
      "");
}
#endif

} // namespace