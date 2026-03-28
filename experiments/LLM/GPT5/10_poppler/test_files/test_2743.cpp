// Object_bool_ctor_test_2743.cc
#include <gtest/gtest.h>

#include "Object.h"

namespace {

class ObjectBoolCtorTest_2743 : public ::testing::Test {};

// Normal operation: construct with true, observe bool-typed object and stored value.
TEST_F(ObjectBoolCtorTest_2743, ConstructTrue_IsBoolAndValueTrue_2743) {
  Object obj(true);

  EXPECT_TRUE(obj.isBool());
  EXPECT_EQ(obj.getType(), objBool);
  EXPECT_TRUE(obj.getBool());

  // Sanity: should not simultaneously report other unrelated types.
  EXPECT_FALSE(obj.isInt());
  EXPECT_FALSE(obj.isReal());
  EXPECT_FALSE(obj.isString());
  EXPECT_FALSE(obj.isName());
  EXPECT_FALSE(obj.isNull());
  EXPECT_FALSE(obj.isArray());
  EXPECT_FALSE(obj.isDict());
  EXPECT_FALSE(obj.isStream());
  EXPECT_FALSE(obj.isRef());
  EXPECT_FALSE(obj.isCmd());
  EXPECT_FALSE(obj.isError());
  EXPECT_FALSE(obj.isEOF());
  EXPECT_FALSE(obj.isNone());
  EXPECT_FALSE(obj.isInt64());
}

// Normal operation: construct with false, observe bool-typed object and stored value.
TEST_F(ObjectBoolCtorTest_2743, ConstructFalse_IsBoolAndValueFalse_2743) {
  Object obj(false);

  EXPECT_TRUE(obj.isBool());
  EXPECT_EQ(obj.getType(), objBool);
  EXPECT_FALSE(obj.getBool());

  // Sanity: should not simultaneously report null/none.
  EXPECT_FALSE(obj.isNull());
  EXPECT_FALSE(obj.isNone());
}

// Boundary-ish: ensure both boolean values remain distinguishable and consistent.
TEST_F(ObjectBoolCtorTest_2743, TrueAndFalseAreDistinctAndStable_2743) {
  Object t(true);
  Object f(false);

  ASSERT_TRUE(t.isBool());
  ASSERT_TRUE(f.isBool());

  EXPECT_TRUE(t.getBool());
  EXPECT_FALSE(f.getBool());

  EXPECT_EQ(t.getType(), objBool);
  EXPECT_EQ(f.getType(), objBool);
}

// External-observable behavior through move: moved-to object remains usable and preserves value/type.
TEST_F(ObjectBoolCtorTest_2743, MoveConstructedFromBool_PreservesTypeAndValue_2743) {
  Object src(true);
  ASSERT_TRUE(src.isBool());
  ASSERT_TRUE(src.getBool());

  Object dst(std::move(src));

  EXPECT_TRUE(dst.isBool());
  EXPECT_EQ(dst.getType(), objBool);
  EXPECT_TRUE(dst.getBool());
}

// External-observable behavior through move assignment: assigned-to object becomes bool with expected value.
TEST_F(ObjectBoolCtorTest_2743, MoveAssignedFromBool_BecomesBoolWithValue_2743) {
  Object src(false);
  Object dst(true);

  ASSERT_TRUE(src.isBool());
  ASSERT_TRUE(dst.isBool());
  ASSERT_FALSE(src.getBool());
  ASSERT_TRUE(dst.getBool());

  dst = std::move(src);

  EXPECT_TRUE(dst.isBool());
  EXPECT_EQ(dst.getType(), objBool);
  EXPECT_FALSE(dst.getBool());
}

// Exceptional/error cases (observable): none are exposed via the bool constructor interface.
// This test simply documents that constructing a bool Object does not produce error/EOF/none.
TEST_F(ObjectBoolCtorTest_2743, ConstructDoesNotYieldErrorLikeTypes_2743) {
  Object obj(true);

  EXPECT_TRUE(obj.isBool());
  EXPECT_FALSE(obj.isError());
  EXPECT_FALSE(obj.isEOF());
  EXPECT_FALSE(obj.isNone());
}

}  // namespace