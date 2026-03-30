// TEST_ID: 73
// File: Object_isReal_test_73.cpp
//
// Unit tests for poppler::Object::isReal() based strictly on the public interface.
// We treat Object as a black box and only validate observable behavior via constructors/getType/isReal.
// No private state access, no internal logic inference.

#include <gtest/gtest.h>

#include "poppler/Object.h"

namespace {

class ObjectIsRealTest_73 : public ::testing::Test {};

TEST_F(ObjectIsRealTest_73, DefaultConstructedIsNotReal_73)
{
  Object obj; // default: objNone (per header declaration)
  EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectIsRealTest_73, DoubleConstructedIsReal_73)
{
  Object obj(3.141592653589793);
  EXPECT_TRUE(obj.isReal());
}

TEST_F(ObjectIsRealTest_73, ZeroDoubleConstructedIsReal_73)
{
  Object obj(0.0);
  EXPECT_TRUE(obj.isReal());
}

TEST_F(ObjectIsRealTest_73, NegativeDoubleConstructedIsReal_73)
{
  Object obj(-12.5);
  EXPECT_TRUE(obj.isReal());
}

TEST_F(ObjectIsRealTest_73, IntConstructedIsNotReal_73)
{
  Object obj(123);
  EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectIsRealTest_73, BoolConstructedIsNotReal_73)
{
  Object obj(true);
  EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectIsRealTest_73, NullStaticIsNotReal_73)
{
  Object obj = Object::null();
  EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectIsRealTest_73, ErrorStaticIsNotReal_73)
{
  Object obj = Object::error();
  EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectIsRealTest_73, EofStaticIsNotReal_73)
{
  Object obj = Object::eof();
  EXPECT_FALSE(obj.isReal());
}

TEST_F(ObjectIsRealTest_73, MovePreservesRealClassification_73)
{
  Object src(2.5);
  ASSERT_TRUE(src.isReal());

  Object moved(std::move(src));
  EXPECT_TRUE(moved.isReal());
}

TEST_F(ObjectIsRealTest_73, MoveAssignmentPreservesRealClassification_73)
{
  Object src(9.75);
  Object dst; // start as non-real
  ASSERT_TRUE(src.isReal());
  ASSERT_FALSE(dst.isReal());

  dst = std::move(src);
  EXPECT_TRUE(dst.isReal());
}

TEST_F(ObjectIsRealTest_73, IsRealConsistentWithGetTypeForReal_73)
{
  Object obj(1.25);
  EXPECT_TRUE(obj.isReal());
  EXPECT_EQ(obj.getType(), objReal);
}

TEST_F(ObjectIsRealTest_73, IsRealConsistentWithGetTypeForNonReal_73)
{
  Object obj(42);
  EXPECT_FALSE(obj.isReal());
  EXPECT_NE(obj.getType(), objReal);
}

TEST_F(ObjectIsRealTest_73, SetToNullClearsRealClassification_73)
{
  Object obj(6.5);
  ASSERT_TRUE(obj.isReal());

  obj.setToNull();
  EXPECT_FALSE(obj.isReal());
  EXPECT_TRUE(obj.isNull());
}

} // namespace