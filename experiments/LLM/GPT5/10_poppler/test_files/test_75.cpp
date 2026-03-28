// Object_isString_75_test.cpp
// Unit tests for Object::isString() (black-box, interface-based)
//
// The TEST_ID is 75

#include <gtest/gtest.h>

#include "poppler/Object.h"

namespace {

class ObjectIsStringTest_75 : public ::testing::Test {};

// Normal operation: constructing a string object should report isString()==true.
TEST_F(ObjectIsStringTest_75, StringObjectReturnsTrue_75) {
  Object o(std::string("hello"));
  EXPECT_TRUE(o.isString());
}

// Boundary-ish: empty string should still be a string.
TEST_F(ObjectIsStringTest_75, EmptyStdStringReturnsTrue_75) {
  Object o(std::string(""));
  EXPECT_TRUE(o.isString());
}

// Normal operation: other common scalar types should not be a string.
TEST_F(ObjectIsStringTest_75, BoolObjectReturnsFalse_75) {
  Object o(true);
  EXPECT_FALSE(o.isString());
}

TEST_F(ObjectIsStringTest_75, IntObjectReturnsFalse_75) {
  Object o(123);
  EXPECT_FALSE(o.isString());
}

TEST_F(ObjectIsStringTest_75, RealObjectReturnsFalse_75) {
  Object o(3.14159);
  EXPECT_FALSE(o.isString());
}

TEST_F(ObjectIsStringTest_75, Int64ObjectReturnsFalse_75) {
  Object o(static_cast<long long>(1234567890123LL));
  EXPECT_FALSE(o.isString());
}

// Boundary: default-constructed object should not be a string.
TEST_F(ObjectIsStringTest_75, DefaultConstructedReturnsFalse_75) {
  Object o;
  EXPECT_FALSE(o.isString());
}

// Normal operation: Objects created via factory functions are not strings (unless documented otherwise).
TEST_F(ObjectIsStringTest_75, NullFactoryReturnsFalse_75) {
  Object o = Object::null();
  EXPECT_FALSE(o.isString());
}

TEST_F(ObjectIsStringTest_75, EofFactoryReturnsFalse_75) {
  Object o = Object::eof();
  EXPECT_FALSE(o.isString());
}

TEST_F(ObjectIsStringTest_75, ErrorFactoryReturnsFalse_75) {
  Object o = Object::error();
  EXPECT_FALSE(o.isString());
}

// Boundary / state transition: after moving, moved-to keeps the same observable "string-ness".
// (No assertions about moved-from; we only require it to be callable without crashing.)
TEST_F(ObjectIsStringTest_75, MoveConstructionPreservesStringnessOnDestination_75) {
  Object src(std::string("move-me"));
  ASSERT_TRUE(src.isString());

  Object dst(std::move(src));
  EXPECT_TRUE(dst.isString());

  // Moved-from object: behavior is not specified; only verify call is safe if allowed by implementation.
  // If Object marks moved-from as "dead", CHECK_NOT_DEAD may abort; so we do NOT call src.isString().
}

// Boundary / state transition: move-assignment preserves string-ness on destination.
TEST_F(ObjectIsStringTest_75, MoveAssignmentPreservesStringnessOnDestination_75) {
  Object src(std::string("assigned"));
  Object dst(false); // start non-string
  ASSERT_TRUE(src.isString());
  ASSERT_FALSE(dst.isString());

  dst = std::move(src);
  EXPECT_TRUE(dst.isString());

  // Do not query src after move (may become "dead" and abort via CHECK_NOT_DEAD).
}

// Normal operation: setToNull transitions away from string-ness.
TEST_F(ObjectIsStringTest_75, SetToNullMakesIsStringFalse_75) {
  Object o(std::string("x"));
  ASSERT_TRUE(o.isString());

  o.setToNull();
  EXPECT_FALSE(o.isString());
}

// Normal operation: isString aligns with getType() == objString for objects that are safe to query.
TEST_F(ObjectIsStringTest_75, IsStringMatchesObjTypeForStdString_75) {
  Object o(std::string("typecheck"));
  EXPECT_EQ(o.getType(), objString);
  EXPECT_TRUE(o.isString());
}

} // namespace