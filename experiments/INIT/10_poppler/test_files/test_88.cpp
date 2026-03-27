// TEST_ID: 88
// File: Object_isIntOrInt64_test_88.cpp

#include <gtest/gtest.h>

#include "poppler/Object.h"

namespace {

// This fixture doesn't assume anything about Object internals.
// We only use public constructors and public query methods.
class ObjectIsIntOrInt64Test_88 : public ::testing::Test {};

} // namespace

// Normal operation: int constructor should be recognized as int-or-int64.
TEST_F(ObjectIsIntOrInt64Test_88, IntObjectReturnsTrue_88) {
  Object o(123);
  EXPECT_TRUE(o.isIntOrInt64());
}

// Normal operation: int64 constructor should be recognized as int-or-int64.
TEST_F(ObjectIsIntOrInt64Test_88, Int64ObjectReturnsTrue_88) {
  Object o(static_cast<long long>(1234567890123LL));
  EXPECT_TRUE(o.isIntOrInt64());
}

// Boundary: int minimum value.
TEST_F(ObjectIsIntOrInt64Test_88, IntMinReturnsTrue_88) {
  Object o(std::numeric_limits<int>::min());
  EXPECT_TRUE(o.isIntOrInt64());
}

// Boundary: int maximum value.
TEST_F(ObjectIsIntOrInt64Test_88, IntMaxReturnsTrue_88) {
  Object o(std::numeric_limits<int>::max());
  EXPECT_TRUE(o.isIntOrInt64());
}

// Boundary: int64 minimum value.
TEST_F(ObjectIsIntOrInt64Test_88, Int64MinReturnsTrue_88) {
  Object o(std::numeric_limits<long long>::min());
  EXPECT_TRUE(o.isIntOrInt64());
}

// Boundary: int64 maximum value.
TEST_F(ObjectIsIntOrInt64Test_88, Int64MaxReturnsTrue_88) {
  Object o(std::numeric_limits<long long>::max());
  EXPECT_TRUE(o.isIntOrInt64());
}

// Non-int types: bool should return false.
TEST_F(ObjectIsIntOrInt64Test_88, BoolObjectReturnsFalse_88) {
  Object o(true);
  EXPECT_FALSE(o.isIntOrInt64());
}

// Non-int types: real should return false.
TEST_F(ObjectIsIntOrInt64Test_88, RealObjectReturnsFalse_88) {
  Object o(3.14159);
  EXPECT_FALSE(o.isIntOrInt64());
}

// Non-int types: null should return false.
TEST_F(ObjectIsIntOrInt64Test_88, NullObjectReturnsFalse_88) {
  Object o = Object::null();
  EXPECT_FALSE(o.isIntOrInt64());
}

// Non-int types: error and EOF should return false (observable state objects).
TEST_F(ObjectIsIntOrInt64Test_88, ErrorAndEofReturnFalse_88) {
  Object err = Object::error();
  Object eof = Object::eof();

  EXPECT_FALSE(err.isIntOrInt64());
  EXPECT_FALSE(eof.isIntOrInt64());
}

// Move behavior: moved-to object preserves the observable classification.
TEST_F(ObjectIsIntOrInt64Test_88, MoveConstructedIntPreservesTrue_88) {
  Object src(77);
  Object dst(std::move(src));
  EXPECT_TRUE(dst.isIntOrInt64());
}

// Consistency: if isIntOrInt64() is true, getIntOrInt64() should be callable and stable.
TEST_F(ObjectIsIntOrInt64Test_88, TrueImpliesGetIntOrInt64MatchesValue_88) {
  const int v = 42;
  Object o(v);

  ASSERT_TRUE(o.isIntOrInt64());
  EXPECT_EQ(o.getIntOrInt64(), static_cast<long long>(v));
}