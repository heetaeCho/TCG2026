// Object_isInt64_test_87.cpp
#include <gtest/gtest.h>

#include <limits>

#include "poppler/Object.h"

namespace {

class ObjectTest_87 : public ::testing::Test {};

TEST_F(ObjectTest_87, Int64ConstructedObjectReturnsTrue_87) {
  Object o(static_cast<long long>(0));
  EXPECT_TRUE(o.isInt64());
  EXPECT_TRUE(o.isInt64()); // repeated call should be stable
}

TEST_F(ObjectTest_87, Int64BoundaryValuesReturnTrue_87) {
  Object minObj(std::numeric_limits<long long>::min());
  Object maxObj(std::numeric_limits<long long>::max());

  EXPECT_TRUE(minObj.isInt64());
  EXPECT_TRUE(maxObj.isInt64());
}

TEST_F(ObjectTest_87, NonInt64ScalarTypesReturnFalse_87) {
  Object b(true);
  Object i(123);
  Object d(3.14159);

  EXPECT_FALSE(b.isInt64());
  EXPECT_FALSE(i.isInt64());
  EXPECT_FALSE(d.isInt64());
}

TEST_F(ObjectTest_87, SpecialSentinelObjectsReturnFalse_87) {
  Object n = Object::null();
  Object e = Object::eof();
  Object err = Object::error();

  EXPECT_FALSE(n.isInt64());
  EXPECT_FALSE(e.isInt64());
  EXPECT_FALSE(err.isInt64());
}

TEST_F(ObjectTest_87, IsInt64DoesNotChangeTypeObservedByGetType_87) {
  Object o(static_cast<long long>(42));
  const ObjType before = o.getType();

  (void)o.isInt64();

  const ObjType after = o.getType();
  EXPECT_EQ(before, after);
  EXPECT_EQ(after, objInt64);
}

} // namespace