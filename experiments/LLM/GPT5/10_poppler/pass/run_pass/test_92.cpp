// TEST_ID = 92
// Unit tests for Object::getInt() in poppler/Object.h

#include <gtest/gtest.h>

#include "poppler/Object.h"

namespace {

class ObjectGetIntTest_92 : public ::testing::Test {};

TEST_F(ObjectGetIntTest_92, ReturnsSameValueForTypicalInts_92) {
  Object o0(0);
  EXPECT_EQ(o0.getInt(), 0);

  Object o1(1);
  EXPECT_EQ(o1.getInt(), 1);

  Object on(-123);
  EXPECT_EQ(on.getInt(), -123);
}

TEST_F(ObjectGetIntTest_92, ReturnsSameValueForIntBoundaries_92) {
  Object omin(std::numeric_limits<int>::min());
  EXPECT_EQ(omin.getInt(), std::numeric_limits<int>::min());

  Object omax(std::numeric_limits<int>::max());
  EXPECT_EQ(omax.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectGetIntTest_92, PreservesValueAfterMoveConstruction_92) {
  Object src(42);
  Object moved(std::move(src));
  EXPECT_EQ(moved.getInt(), 42);
}

TEST_F(ObjectGetIntTest_92, PreservesValueAfterMoveAssignment_92) {
  Object src(-7);
  Object dst(1234);

  dst = std::move(src);
  EXPECT_EQ(dst.getInt(), -7);
}

// Error/exceptional behavior depends on how OBJECT_TYPE_CHECK is configured
// (e.g., assert/death in debug builds vs returning a default value in release).
TEST_F(ObjectGetIntTest_92, GetIntOnNonIntTriggersTypeCheck_92) {
#ifndef NDEBUG
  // In debug builds, many configurations use assertions/abort on type mismatch.
  ASSERT_DEATH_IF_SUPPORTED(
      {
        Object b(true);
        (void)b.getInt();
      },
      ".*");
  ASSERT_DEATH_IF_SUPPORTED(
      {
        Object n = Object::null();
        (void)n.getInt();
      },
      ".*");
#else
  // In release builds, many configurations return a default value (commonly 0).
  Object b(true);
  EXPECT_EQ(b.getInt(), 0);

  Object n = Object::null();
  EXPECT_EQ(n.getInt(), 0);
#endif
}

TEST_F(ObjectGetIntTest_92, GetIntOnRealTriggersTypeCheck_92) {
#ifndef NDEBUG
  ASSERT_DEATH_IF_SUPPORTED(
      {
        Object r(3.14159);
        (void)r.getInt();
      },
      ".*");
#else
  Object r(3.14159);
  EXPECT_EQ(r.getInt(), 0);
#endif
}

}  // namespace