// TEST_ID: 68
// File: object_move_assignment_test_68.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>
#include <string>

#include "poppler/Object.h"

namespace {

class ObjectMoveAssignmentTest_68 : public ::testing::Test {};

TEST_F(ObjectMoveAssignmentTest_68, MoveAssignmentIsNoexcept_68) {
  static_assert(noexcept(std::declval<Object &>() = std::declval<Object &&>()),
                "Object move assignment must be noexcept");
}

TEST_F(ObjectMoveAssignmentTest_68, MoveAssignFromIntTransfersValueAndKillsSource_68) {
  Object src(42);
  Object dst; // default constructed

  dst = std::move(src);

  EXPECT_TRUE(dst.isInt());
  EXPECT_EQ(dst.getInt(), 42);
  EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectMoveAssignmentTest_68, MoveAssignOverwritesPreviousValue_68) {
  Object dst(true);
  Object src(3.5);

  dst = std::move(src);

  EXPECT_TRUE(dst.isReal());
  EXPECT_DOUBLE_EQ(dst.getReal(), 3.5);
  EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectMoveAssignmentTest_68, MoveAssignPreservesNameString_68) {
  Object src(objName, std::string_view("MyName"));
  Object dst = Object::null();

  ASSERT_TRUE(dst.isNull());

  dst = std::move(src);

  EXPECT_TRUE(dst.isName());
  EXPECT_EQ(dst.getNameString(), "MyName");
  EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectMoveAssignmentTest_68, MoveAssignFromNoneReplacesDestinationType_68) {
  Object src;      // objNone
  Object dst(123); // objInt

  ASSERT_TRUE(dst.isInt());

  dst = std::move(src);

  EXPECT_TRUE(dst.isNone());
  EXPECT_EQ(dst.getType(), objNone);
  EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectMoveAssignmentTest_68, MoveAssignFromErrorTransfersErrorType_68) {
  Object src = Object::error();
  Object dst(false);

  ASSERT_TRUE(dst.isBool());

  dst = std::move(src);

  EXPECT_TRUE(dst.isError());
  EXPECT_EQ(dst.getType(), objError);
  EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectMoveAssignmentTest_68, MoveAssignmentReturnsLvalueReferenceToDestination_68) {
  Object src(7);
  Object dst;

  Object *ret = &(dst = std::move(src));

  EXPECT_EQ(ret, &dst);
  EXPECT_TRUE(dst.isInt());
  EXPECT_EQ(dst.getInt(), 7);
  EXPECT_EQ(src.getType(), objDead);
}

} // namespace