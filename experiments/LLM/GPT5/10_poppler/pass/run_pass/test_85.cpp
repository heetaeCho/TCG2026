// TEST_ID = 85
//
// Unit tests for Object::isEOF()
// File under test: ./TestProjects/poppler/poppler/Object.h
//
// Partial interface provided:
//   class Object { public: bool isEOF() const { CHECK_NOT_DEAD; return type == objEOF; } };
//
// These tests treat Object as a black box and only validate observable behavior via the public API.

#include <gtest/gtest.h>

#include "poppler/Object.h"

namespace {

class ObjectIsEOFTest_85 : public ::testing::Test {};

TEST_F(ObjectIsEOFTest_85, EofFactoryReturnsTrue_85) {
  const Object o = Object::eof();
  EXPECT_TRUE(o.isEOF());
}

TEST_F(ObjectIsEOFTest_85, DefaultConstructedIsNotEof_85) {
  Object o;
  EXPECT_FALSE(o.isEOF());
}

TEST_F(ObjectIsEOFTest_85, NullFactoryIsNotEof_85) {
  const Object o = Object::null();
  EXPECT_FALSE(o.isEOF());
}

TEST_F(ObjectIsEOFTest_85, ErrorFactoryIsNotEof_85) {
  const Object o = Object::error();
  EXPECT_FALSE(o.isEOF());
}

TEST_F(ObjectIsEOFTest_85, PrimitiveBoolIsNotEof_85) {
  const Object o_true(true);
  const Object o_false(false);
  EXPECT_FALSE(o_true.isEOF());
  EXPECT_FALSE(o_false.isEOF());
}

TEST_F(ObjectIsEOFTest_85, PrimitiveIntIsNotEof_85) {
  const Object o0(0);
  const Object o1(1);
  const Object oNeg(-123);
  EXPECT_FALSE(o0.isEOF());
  EXPECT_FALSE(o1.isEOF());
  EXPECT_FALSE(oNeg.isEOF());
}

TEST_F(ObjectIsEOFTest_85, PrimitiveRealIsNotEof_85) {
  const Object o0(0.0);
  const Object oPi(3.14159);
  const Object oNeg(-0.25);
  EXPECT_FALSE(o0.isEOF());
  EXPECT_FALSE(oPi.isEOF());
  EXPECT_FALSE(oNeg.isEOF());
}

TEST_F(ObjectIsEOFTest_85, PrimitiveInt64IsNotEof_85) {
  const Object o0(static_cast<long long>(0));
  const Object oBig(static_cast<long long>(1) << 40);
  const Object oNeg(static_cast<long long>(-1));
  EXPECT_FALSE(o0.isEOF());
  EXPECT_FALSE(oBig.isEOF());
  EXPECT_FALSE(oNeg.isEOF());
}

TEST_F(ObjectIsEOFTest_85, MoveConstructedFromEofPreservesEofStateInDestination_85) {
  Object src = Object::eof();
  Object dst(std::move(src));
  EXPECT_TRUE(dst.isEOF());
}

TEST_F(ObjectIsEOFTest_85, MoveAssignedFromEofMakesDestinationEof_85) {
  Object dst;                // not EOF
  Object src = Object::eof();
  dst = std::move(src);
  EXPECT_TRUE(dst.isEOF());
}

TEST_F(ObjectIsEOFTest_85, BoundaryRepeatedCallsAreStable_85) {
  const Object o = Object::eof();
  EXPECT_TRUE(o.isEOF());
  EXPECT_TRUE(o.isEOF());
  EXPECT_TRUE(o.isEOF());
}

TEST_F(ObjectIsEOFTest_85, SwitchingToNullMakesNotEof_85) {
  Object o = Object::eof();
  ASSERT_TRUE(o.isEOF());

  o.setToNull();
  EXPECT_FALSE(o.isEOF());
}

}  // namespace