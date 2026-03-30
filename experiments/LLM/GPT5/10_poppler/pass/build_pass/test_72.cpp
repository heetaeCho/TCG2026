// TEST_ID: 72
//
// Unit tests for poppler::Object::isInt()
// File under test: ./TestProjects/poppler/poppler/Object.h
//
// Constraints honored:
// - Treat Object implementation as a black box
// - Only test observable behavior via public interface
// - No private state access, no internal logic assumptions

#include <gtest/gtest.h>

#include "poppler/Object.h"

namespace {

class ObjectIsIntTest_72 : public ::testing::Test {};

// Normal operation: Object constructed from int should report isInt() == true.
TEST_F(ObjectIsIntTest_72, IntConstructedObjectReportsIsIntTrue_72) {
  Object o(123);
  EXPECT_TRUE(o.isInt());
}

// Boundary-ish: negative int should still be an int.
TEST_F(ObjectIsIntTest_72, NegativeIntConstructedObjectReportsIsIntTrue_72) {
  Object o(-1);
  EXPECT_TRUE(o.isInt());
}

// Boundary-ish: zero should still be an int.
TEST_F(ObjectIsIntTest_72, ZeroIntConstructedObjectReportsIsIntTrue_72) {
  Object o(0);
  EXPECT_TRUE(o.isInt());
}

// Non-int types: bool should not be int.
TEST_F(ObjectIsIntTest_72, BoolConstructedObjectReportsIsIntFalse_72) {
  Object o(true);
  EXPECT_FALSE(o.isInt());
}

// Non-int types: double (real) should not be int.
TEST_F(ObjectIsIntTest_72, RealConstructedObjectReportsIsIntFalse_72) {
  Object o(3.14159);
  EXPECT_FALSE(o.isInt());
}

// Non-int types: null object should not be int.
TEST_F(ObjectIsIntTest_72, NullObjectReportsIsIntFalse_72) {
  Object o = Object::null();
  EXPECT_FALSE(o.isInt());
}

// Non-int types: error object should not be int.
TEST_F(ObjectIsIntTest_72, ErrorObjectReportsIsIntFalse_72) {
  Object o = Object::error();
  EXPECT_FALSE(o.isInt());
}

// Non-int types: EOF object should not be int.
TEST_F(ObjectIsIntTest_72, EofObjectReportsIsIntFalse_72) {
  Object o = Object::eof();
  EXPECT_FALSE(o.isInt());
}

// Move behavior (observable): moved-to object preserves "int-ness".
TEST_F(ObjectIsIntTest_72, MoveConstructedFromIntPreservesIsIntOnDestination_72) {
  Object src(77);
  Object dst(std::move(src));
  EXPECT_TRUE(dst.isInt());
}

// Assignment move behavior: destination becomes int after move-assign from int object.
TEST_F(ObjectIsIntTest_72, MoveAssignmentFromIntMakesDestinationIsIntTrue_72) {
  Object src(88);
  Object dst = Object::null();  // start as non-int
  EXPECT_FALSE(dst.isInt());

  dst = std::move(src);
  EXPECT_TRUE(dst.isInt());
}

// State change via public API: setToNull should make isInt() false after being int.
TEST_F(ObjectIsIntTest_72, SetToNullMakesPreviouslyIntObjectReportIsIntFalse_72) {
  Object o(999);
  ASSERT_TRUE(o.isInt());

  o.setToNull();
  EXPECT_FALSE(o.isInt());
}

// Distinguish int64 from int (based purely on public interface expectation):
// Object constructed from long long should not necessarily be "int" (it has isInt64/isIntOrInt64 APIs).
// We verify isInt() is false for an int64-constructed object.
TEST_F(ObjectIsIntTest_72, Int64ConstructedObjectReportsIsIntFalse_72) {
  Object o(static_cast<long long>(1));
  EXPECT_FALSE(o.isInt());
}

}  // namespace