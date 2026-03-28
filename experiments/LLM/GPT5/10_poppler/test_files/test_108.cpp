// Object_getInt64_ut_108.cpp
#include <gtest/gtest.h>

#include <climits>
#include <utility>

#include "poppler/Object.h"

namespace {

class ObjectGetInt64Test_108 : public ::testing::Test {
protected:
  void SetUp() override {
#if GTEST_HAS_DEATH_TEST
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
#endif
  }
};

TEST_F(ObjectGetInt64Test_108, ReturnsSameValueForZero_108) {
  Object o(0LL);
  EXPECT_TRUE(o.isInt64());
  EXPECT_EQ(o.getInt64(), 0LL);
  // Calling multiple times should be stable/observable.
  EXPECT_EQ(o.getInt64(), 0LL);
}

TEST_F(ObjectGetInt64Test_108, ReturnsSameValueForPositive_108) {
  const long long v = 1234567890123LL;
  Object o(v);
  EXPECT_TRUE(o.isInt64());
  EXPECT_EQ(o.getInt64(), v);
}

TEST_F(ObjectGetInt64Test_108, ReturnsSameValueForNegative_108) {
  const long long v = -9876543210LL;
  Object o(v);
  EXPECT_TRUE(o.isInt64());
  EXPECT_EQ(o.getInt64(), v);
}

TEST_F(ObjectGetInt64Test_108, ReturnsSameValueForLongLongExtremes_108) {
  {
    Object o(LLONG_MAX);
    EXPECT_TRUE(o.isInt64());
    EXPECT_EQ(o.getInt64(), LLONG_MAX);
  }
  {
    Object o(LLONG_MIN);
    EXPECT_TRUE(o.isInt64());
    EXPECT_EQ(o.getInt64(), LLONG_MIN);
  }
}

#if GTEST_HAS_DEATH_TEST
TEST_F(ObjectGetInt64Test_108, DeathOnWrongType_DefaultConstructedNone_108) {
  Object o; // objNone
  EXPECT_FALSE(o.isInt64());
  EXPECT_DEATH({ (void)o.getInt64(); }, ".*");
}

TEST_F(ObjectGetInt64Test_108, DeathOnWrongType_Int_108) {
  Object o(7);
  EXPECT_FALSE(o.isInt64());
  EXPECT_DEATH({ (void)o.getInt64(); }, ".*");
}

TEST_F(ObjectGetInt64Test_108, DeathOnWrongType_Bool_108) {
  Object o(true);
  EXPECT_FALSE(o.isInt64());
  EXPECT_DEATH({ (void)o.getInt64(); }, ".*");
}

TEST_F(ObjectGetInt64Test_108, DeathOnWrongType_Real_108) {
  Object o(3.25);
  EXPECT_FALSE(o.isInt64());
  EXPECT_DEATH({ (void)o.getInt64(); }, ".*");
}

TEST_F(ObjectGetInt64Test_108, DeathOnWrongType_NullFactory_108) {
  Object o = Object::null();
  EXPECT_FALSE(o.isInt64());
  EXPECT_DEATH({ (void)o.getInt64(); }, ".*");
}

TEST_F(ObjectGetInt64Test_108, DeathOnWrongType_ErrorFactory_108) {
  Object o = Object::error();
  EXPECT_FALSE(o.isInt64());
  EXPECT_DEATH({ (void)o.getInt64(); }, ".*");
}

TEST_F(ObjectGetInt64Test_108, DeathOnWrongType_EofFactory_108) {
  Object o = Object::eof();
  EXPECT_FALSE(o.isInt64());
  EXPECT_DEATH({ (void)o.getInt64(); }, ".*");
}
#endif  // GTEST_HAS_DEATH_TEST

} // namespace