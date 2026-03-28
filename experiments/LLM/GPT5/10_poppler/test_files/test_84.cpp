// File: Object_isError_test_84.cpp
#include <gtest/gtest.h>

#include "poppler/Object.h"

namespace {

class ObjectIsErrorTest_84 : public ::testing::Test {};

TEST_F(ObjectIsErrorTest_84, DefaultConstructedIsNotError_84) {
  Object obj;
  EXPECT_FALSE(obj.isError());
}

TEST_F(ObjectIsErrorTest_84, StaticErrorIsError_84) {
  Object obj = Object::error();
  EXPECT_TRUE(obj.isError());
}

TEST_F(ObjectIsErrorTest_84, StaticNullIsNotError_84) {
  Object obj = Object::null();
  EXPECT_FALSE(obj.isError());
}

TEST_F(ObjectIsErrorTest_84, StaticEofIsNotError_84) {
  Object obj = Object::eof();
  EXPECT_FALSE(obj.isError());
}

TEST_F(ObjectIsErrorTest_84, PrimitiveConstructorsAreNotError_84) {
  {
    Object b(true);
    EXPECT_FALSE(b.isError());
  }
  {
    Object i(0);
    EXPECT_FALSE(i.isError());
  }
  {
    Object r(0.0);
    EXPECT_FALSE(r.isError());
  }
  {
    Object i64(static_cast<long long>(0));
    EXPECT_FALSE(i64.isError());
  }
}

TEST_F(ObjectIsErrorTest_84, MoveConstructedFromErrorRemainsError_84) {
  Object src = Object::error();
  Object moved(std::move(src));
  EXPECT_TRUE(moved.isError());

  // Note: moved-from object state/validity is unspecified; do not inspect src.
}

}  // namespace