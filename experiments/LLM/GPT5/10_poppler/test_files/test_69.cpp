// TEST_ID = 69
//
// Unit tests for poppler::Object::setToNull()
// File: ./TestProjects/poppler/poppler/Object_setToNull_test.cpp

#include <gtest/gtest.h>

#include "poppler/Object.h"

namespace {

class ObjectSetToNullTest_69 : public ::testing::Test {};

TEST_F(ObjectSetToNullTest_69, DefaultConstructedBecomesNull_69) {
  Object obj;  // starts as objNone per provided interface snippet
  EXPECT_TRUE(obj.isNone());

  obj.setToNull();

  EXPECT_TRUE(obj.isNull());
  EXPECT_EQ(obj.getType(), objNull);
  EXPECT_FALSE(obj.isNone());
}

TEST_F(ObjectSetToNullTest_69, BoolObjectBecomesNull_69) {
  Object obj(true);
  EXPECT_TRUE(obj.isBool());

  obj.setToNull();

  EXPECT_TRUE(obj.isNull());
  EXPECT_EQ(obj.getType(), objNull);
  EXPECT_FALSE(obj.isBool());
}

TEST_F(ObjectSetToNullTest_69, IntObjectBecomesNull_69) {
  Object obj(123);
  EXPECT_TRUE(obj.isInt());

  obj.setToNull();

  EXPECT_TRUE(obj.isNull());
  EXPECT_EQ(obj.getType(), objNull);
  EXPECT_FALSE(obj.isInt());
}

TEST_F(ObjectSetToNullTest_69, RealObjectBecomesNull_69) {
  Object obj(3.14159);
  EXPECT_TRUE(obj.isReal());
  EXPECT_TRUE(obj.isNum());

  obj.setToNull();

  EXPECT_TRUE(obj.isNull());
  EXPECT_EQ(obj.getType(), objNull);
  EXPECT_FALSE(obj.isReal());
  EXPECT_FALSE(obj.isNum());
}

TEST_F(ObjectSetToNullTest_69, Int64ObjectBecomesNull_69) {
  Object obj(static_cast<long long>(-9223372036854775807LL));
  EXPECT_TRUE(obj.isInt64());
  EXPECT_TRUE(obj.isIntOrInt64());

  obj.setToNull();

  EXPECT_TRUE(obj.isNull());
  EXPECT_EQ(obj.getType(), objNull);
  EXPECT_FALSE(obj.isInt64());
  EXPECT_FALSE(obj.isIntOrInt64());
}

TEST_F(ObjectSetToNullTest_69, SetToNullIsIdempotent_69) {
  Object obj = Object::null();
  ASSERT_TRUE(obj.isNull());
  ASSERT_EQ(obj.getType(), objNull);

  obj.setToNull();
  EXPECT_TRUE(obj.isNull());
  EXPECT_EQ(obj.getType(), objNull);

  obj.setToNull();
  EXPECT_TRUE(obj.isNull());
  EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectSetToNullTest_69, TransitionFromErrorToNull_69) {
  Object obj = Object::error();
  ASSERT_TRUE(obj.isError());
  ASSERT_EQ(obj.getType(), objError);

  obj.setToNull();

  EXPECT_TRUE(obj.isNull());
  EXPECT_EQ(obj.getType(), objNull);
  EXPECT_FALSE(obj.isError());
}

TEST_F(ObjectSetToNullTest_69, TransitionFromEofToNull_69) {
  Object obj = Object::eof();
  ASSERT_TRUE(obj.isEOF());
  ASSERT_EQ(obj.getType(), objEOF);

  obj.setToNull();

  EXPECT_TRUE(obj.isNull());
  EXPECT_EQ(obj.getType(), objNull);
  EXPECT_FALSE(obj.isEOF());
}

TEST_F(ObjectSetToNullTest_69, MoveThenSetToNullOnMovedToObject_69) {
  Object src(7);
  ASSERT_TRUE(src.isInt());

  Object dst(std::move(src));
  // Don't assume anything about moved-from 'src' other than it remains destructible.
  EXPECT_TRUE(dst.isInt());

  dst.setToNull();
  EXPECT_TRUE(dst.isNull());
  EXPECT_EQ(dst.getType(), objNull);
  EXPECT_FALSE(dst.isInt());
}

TEST_F(ObjectSetToNullTest_69, SetToNullDoesNotThrow_69) {
  Object obj(1);
  EXPECT_NO_THROW(obj.setToNull());
  EXPECT_TRUE(obj.isNull());
  EXPECT_EQ(obj.getType(), objNull);
}

}  // namespace