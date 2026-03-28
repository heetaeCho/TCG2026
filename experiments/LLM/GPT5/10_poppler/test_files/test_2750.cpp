// Object_int64_ctor_test_2750.cc
#include <gtest/gtest.h>

#include <limits>
#include <type_traits>
#include <utility>

#include "Object.h"

namespace {

class ObjectTest_2750 : public ::testing::Test {};

// Compile-time interface/ABI expectations for the int64 constructor.
TEST_F(ObjectTest_2750, Int64ConstructorIsExplicit_2750) {
  static_assert(std::is_constructible_v<Object, long long>,
                "Object should be constructible from long long");
  static_assert(!std::is_convertible_v<long long, Object>,
                "Object(long long) must be explicit (no implicit conversion)");
}

TEST_F(ObjectTest_2750, ConstructsInt64Zero_2750) {
  const long long v = 0LL;
  Object obj(v);

  EXPECT_EQ(obj.getType(), objInt64);
  EXPECT_TRUE(obj.isInt64());
  EXPECT_TRUE(obj.isIntOrInt64());
  EXPECT_EQ(obj.getInt64(), v);
  EXPECT_EQ(obj.getIntOrInt64(), v);
}

TEST_F(ObjectTest_2750, ConstructsInt64Positive_2750) {
  const long long v = 42LL;
  Object obj(v);

  EXPECT_EQ(obj.getType(), objInt64);
  EXPECT_TRUE(obj.isInt64());
  EXPECT_TRUE(obj.isIntOrInt64());
  EXPECT_EQ(obj.getInt64(), v);
  EXPECT_EQ(obj.getIntOrInt64(), v);
}

TEST_F(ObjectTest_2750, ConstructsInt64Negative_2750) {
  const long long v = -42LL;
  Object obj(v);

  EXPECT_EQ(obj.getType(), objInt64);
  EXPECT_TRUE(obj.isInt64());
  EXPECT_TRUE(obj.isIntOrInt64());
  EXPECT_EQ(obj.getInt64(), v);
  EXPECT_EQ(obj.getIntOrInt64(), v);
}

TEST_F(ObjectTest_2750, ConstructsInt64Max_2750) {
  const long long v = std::numeric_limits<long long>::max();
  Object obj(v);

  EXPECT_EQ(obj.getType(), objInt64);
  EXPECT_TRUE(obj.isInt64());
  EXPECT_TRUE(obj.isIntOrInt64());
  EXPECT_EQ(obj.getInt64(), v);
  EXPECT_EQ(obj.getIntOrInt64(), v);
}

TEST_F(ObjectTest_2750, ConstructsInt64Min_2750) {
  const long long v = std::numeric_limits<long long>::min();
  Object obj(v);

  EXPECT_EQ(obj.getType(), objInt64);
  EXPECT_TRUE(obj.isInt64());
  EXPECT_TRUE(obj.isIntOrInt64());
  EXPECT_EQ(obj.getInt64(), v);
  EXPECT_EQ(obj.getIntOrInt64(), v);
}

TEST_F(ObjectTest_2750, MoveConstructorPreservesInt64Observables_2750) {
  const long long v = 1234567890123LL;
  Object src(v);

  Object moved(std::move(src));

  EXPECT_EQ(moved.getType(), objInt64);
  EXPECT_TRUE(moved.isInt64());
  EXPECT_TRUE(moved.isIntOrInt64());
  EXPECT_EQ(moved.getInt64(), v);
  EXPECT_EQ(moved.getIntOrInt64(), v);
}

TEST_F(ObjectTest_2750, MoveAssignmentPreservesInt64Observables_2750) {
  const long long v = -9876543210LL;
  Object src(v);

  Object dst = Object::null();  // start from a different observable state
  dst = std::move(src);

  EXPECT_EQ(dst.getType(), objInt64);
  EXPECT_TRUE(dst.isInt64());
  EXPECT_TRUE(dst.isIntOrInt64());
  EXPECT_EQ(dst.getInt64(), v);
  EXPECT_EQ(dst.getIntOrInt64(), v);
}

}  // namespace