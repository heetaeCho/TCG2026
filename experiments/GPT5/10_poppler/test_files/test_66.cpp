// TEST_ID: 66
// File: object_error_test_66.cpp

#include <gtest/gtest.h>

#include "poppler/Object.h"

namespace {

class ObjectErrorTest_66 : public ::testing::Test {};

TEST_F(ObjectErrorTest_66, ErrorCreatesErrorObject_66) {
  Object o = Object::error();
  EXPECT_TRUE(o.isError());
  EXPECT_EQ(o.getType(), objError);
  EXPECT_FALSE(o.isNone());
  EXPECT_FALSE(o.isEOF());
  EXPECT_FALSE(o.isNull());
}

TEST_F(ObjectErrorTest_66, ErrorFactoryReturnsIndependentObjects_66) {
  Object a = Object::error();
  Object b = Object::error();

  EXPECT_TRUE(a.isError());
  EXPECT_TRUE(b.isError());
  EXPECT_EQ(a.getType(), objError);
  EXPECT_EQ(b.getType(), objError);
}

TEST_F(ObjectErrorTest_66, ErrorObjectIsMovable_66) {
  Object src = Object::error();
  ASSERT_TRUE(src.isError());

  Object moved(std::move(src));
  EXPECT_TRUE(moved.isError());
  EXPECT_EQ(moved.getType(), objError);
}

TEST_F(ObjectErrorTest_66, ErrorObjectIsMoveAssignable_66) {
  Object dst;  // default constructed: observable as None via isNone()
  EXPECT_TRUE(dst.isNone());
  EXPECT_EQ(dst.getType(), objNone);

  Object src = Object::error();
  ASSERT_TRUE(src.isError());

  dst = std::move(src);
  EXPECT_TRUE(dst.isError());
  EXPECT_EQ(dst.getType(), objError);
}

TEST_F(ObjectErrorTest_66, ErrorObjectCanBeOverwrittenByMoveAssignment_66) {
  Object dst = Object::error();
  ASSERT_TRUE(dst.isError());

  Object src;  // None
  ASSERT_TRUE(src.isNone());

  dst = std::move(src);
  EXPECT_TRUE(dst.isNone());
  EXPECT_EQ(dst.getType(), objNone);
}

}  // namespace