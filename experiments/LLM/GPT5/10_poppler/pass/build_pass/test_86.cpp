// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for poppler::Object::isNone()
// File under test: ./TestProjects/poppler/poppler/Object.h
//
// NOTE: We treat Object as a black box and only test observable behavior
// via its public constructors / static factories and isNone().

#include <gtest/gtest.h>

#include "Object.h"

namespace {

class ObjectIsNoneTest_86 : public ::testing::Test {};

TEST_F(ObjectIsNoneTest_86, DefaultConstructedIsNone_86) {
  Object o;
  EXPECT_TRUE(o.isNone());
}

TEST_F(ObjectIsNoneTest_86, NullFactoryIsNotNone_86) {
  Object o = Object::null();
  EXPECT_FALSE(o.isNone());
}

TEST_F(ObjectIsNoneTest_86, EofFactoryIsNotNone_86) {
  Object o = Object::eof();
  EXPECT_FALSE(o.isNone());
}

TEST_F(ObjectIsNoneTest_86, ErrorFactoryIsNotNone_86) {
  Object o = Object::error();
  EXPECT_FALSE(o.isNone());
}

TEST_F(ObjectIsNoneTest_86, BoolConstructedIsNotNone_86) {
  Object oTrue(true);
  Object oFalse(false);
  EXPECT_FALSE(oTrue.isNone());
  EXPECT_FALSE(oFalse.isNone());
}

TEST_F(ObjectIsNoneTest_86, IntConstructedIsNotNone_86) {
  Object o0(0);
  Object oNeg(-1);
  Object oMax(2147483647);
  EXPECT_FALSE(o0.isNone());
  EXPECT_FALSE(oNeg.isNone());
  EXPECT_FALSE(oMax.isNone());
}

TEST_F(ObjectIsNoneTest_86, RealConstructedIsNotNone_86) {
  Object o0(0.0);
  Object oNeg(-1.25);
  Object oBig(1e300);
  EXPECT_FALSE(o0.isNone());
  EXPECT_FALSE(oNeg.isNone());
  EXPECT_FALSE(oBig.isNone());
}

TEST_F(ObjectIsNoneTest_86, StdStringMoveConstructedIsNotNone_86) {
  std::string s = "hello";
  Object o(std::move(s));
  EXPECT_FALSE(o.isNone());
}

TEST_F(ObjectIsNoneTest_86, Int64ConstructedIsNotNone_86) {
  Object o0(static_cast<long long>(0));
  Object oNeg(static_cast<long long>(-1));
  Object oBig(static_cast<long long>(9223372036854775807LL));
  EXPECT_FALSE(o0.isNone());
  EXPECT_FALSE(oNeg.isNone());
  EXPECT_FALSE(oBig.isNone());
}

TEST_F(ObjectIsNoneTest_86, MovedFromIntoNewObjectPreservesDestinationNotNone_86) {
  Object src(true);
  Object dst(std::move(src));
  EXPECT_FALSE(dst.isNone());
}

TEST_F(ObjectIsNoneTest_86, AfterSetToNullIsNotNone_86) {
  Object o;
  ASSERT_TRUE(o.isNone());  // sanity check of starting state
  o.setToNull();
  EXPECT_FALSE(o.isNone());
}

TEST_F(ObjectIsNoneTest_86, AssignmentMoveResultsInDestinationNotNone_86) {
  Object src(42);
  Object dst;
  ASSERT_TRUE(dst.isNone());
  dst = std::move(src);
  EXPECT_FALSE(dst.isNone());
}

}  // namespace