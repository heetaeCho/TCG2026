// TEST_ID: 74
// File: test_object_isnum_74.cpp

#include <gtest/gtest.h>

#include "poppler/Object.h"

namespace {

class ObjectIsNumTest_74 : public ::testing::Test {};

TEST_F(ObjectIsNumTest_74, DefaultConstructedIsNotNum_74) {
  Object obj;
  EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectIsNumTest_74, BoolIsNotNum_74) {
  Object obj(true);
  EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectIsNumTest_74, IntIsNum_74) {
  Object obj(0);
  EXPECT_TRUE(obj.isNum());

  Object obj2(42);
  EXPECT_TRUE(obj2.isNum());

  Object obj3(-1);
  EXPECT_TRUE(obj3.isNum());
}

TEST_F(ObjectIsNumTest_74, RealIsNum_74) {
  Object obj(0.0);
  EXPECT_TRUE(obj.isNum());

  Object obj2(3.14159);
  EXPECT_TRUE(obj2.isNum());

  Object obj3(-2.5);
  EXPECT_TRUE(obj3.isNum());
}

TEST_F(ObjectIsNumTest_74, Int64IsNum_74) {
  Object obj(static_cast<long long>(0));
  EXPECT_TRUE(obj.isNum());

  Object obj2(static_cast<long long>(1));
  EXPECT_TRUE(obj2.isNum());

  Object obj3(static_cast<long long>(-1));
  EXPECT_TRUE(obj3.isNum());
}

TEST_F(ObjectIsNumTest_74, NullIsNotNum_74) {
  Object obj = Object::null();
  EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectIsNumTest_74, EofIsNotNum_74) {
  Object obj = Object::eof();
  EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectIsNumTest_74, ErrorIsNotNum_74) {
  Object obj = Object::error();
  EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectIsNumTest_74, MoveConstructedPreservesIsNumForNumbers_74) {
  Object srcInt(123);
  EXPECT_TRUE(srcInt.isNum());

  Object movedInt(std::move(srcInt));
  EXPECT_TRUE(movedInt.isNum());

  Object srcReal(9.25);
  EXPECT_TRUE(srcReal.isNum());

  Object movedReal(std::move(srcReal));
  EXPECT_TRUE(movedReal.isNum());

  Object srcI64(static_cast<long long>(1234567890123LL));
  EXPECT_TRUE(srcI64.isNum());

  Object movedI64(std::move(srcI64));
  EXPECT_TRUE(movedI64.isNum());
}

TEST_F(ObjectIsNumTest_74, MoveAssignmentPreservesIsNumForNumbers_74) {
  Object dst; // starts as objNone
  EXPECT_FALSE(dst.isNum());

  Object src(7);
  EXPECT_TRUE(src.isNum());

  dst = std::move(src);
  EXPECT_TRUE(dst.isNum());

  Object dst2(Object::null());
  EXPECT_FALSE(dst2.isNum());

  Object src2(1.5);
  EXPECT_TRUE(src2.isNum());

  dst2 = std::move(src2);
  EXPECT_TRUE(dst2.isNum());
}

TEST_F(ObjectIsNumTest_74, SetToNullMakesNotNum_74) {
  Object obj(10);
  ASSERT_TRUE(obj.isNum());

  obj.setToNull();
  EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectIsNumTest_74, NullThenAssignIntBecomesNum_74) {
  Object obj = Object::null();
  ASSERT_FALSE(obj.isNum());

  Object src(88);
  obj = std::move(src);
  EXPECT_TRUE(obj.isNum());
}

} // namespace