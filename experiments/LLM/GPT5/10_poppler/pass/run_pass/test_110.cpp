// TEST_ID: 110
// File: Object_getNumWithDefaultValue_110_test.cpp

#include <gtest/gtest.h>

#include "poppler/Object.h"

namespace {

class ObjectGetNumWithDefaultValueTest_110 : public ::testing::Test {};

TEST_F(ObjectGetNumWithDefaultValueTest_110, ReturnsDefaultForNonNumericTypes_110) {
  const double def = 123.456;

  EXPECT_DOUBLE_EQ(Object().getNumWithDefaultValue(def), def);          // objNone
  EXPECT_DOUBLE_EQ(Object(true).getNumWithDefaultValue(def), def);      // objBool
  EXPECT_DOUBLE_EQ(Object::null().getNumWithDefaultValue(def), def);    // objNull
  EXPECT_DOUBLE_EQ(Object::eof().getNumWithDefaultValue(def), def);     // objEOF
  EXPECT_DOUBLE_EQ(Object::error().getNumWithDefaultValue(def), def);   // objError
}

TEST_F(ObjectGetNumWithDefaultValueTest_110, ReturnsUnderlyingValueForInt_110) {
  const double def = -999.0;

  EXPECT_DOUBLE_EQ(Object(0).getNumWithDefaultValue(def), 0.0);
  EXPECT_DOUBLE_EQ(Object(42).getNumWithDefaultValue(def), 42.0);
  EXPECT_DOUBLE_EQ(Object(-7).getNumWithDefaultValue(def), -7.0);
}

TEST_F(ObjectGetNumWithDefaultValueTest_110, ReturnsUnderlyingValueForReal_110) {
  const double def = 0.0;

  EXPECT_DOUBLE_EQ(Object(0.0).getNumWithDefaultValue(def), 0.0);
  EXPECT_DOUBLE_EQ(Object(3.25).getNumWithDefaultValue(def), 3.25);
  EXPECT_DOUBLE_EQ(Object(-1.5).getNumWithDefaultValue(def), -1.5);
}

TEST_F(ObjectGetNumWithDefaultValueTest_110, ReturnsUnderlyingValueForInt64_110) {
  const double def = 1.0;

  EXPECT_DOUBLE_EQ(Object(static_cast<long long>(0)).getNumWithDefaultValue(def), 0.0);
  EXPECT_DOUBLE_EQ(Object(static_cast<long long>(123456789LL)).getNumWithDefaultValue(def),
                   123456789.0);
  EXPECT_DOUBLE_EQ(Object(static_cast<long long>(-123456789LL)).getNumWithDefaultValue(def),
                   -123456789.0);
}

TEST_F(ObjectGetNumWithDefaultValueTest_110, DefaultValueIsReturnedExactly_110) {
  // Boundary-ish behavior: make sure the chosen default is returned unchanged
  // when the object isn't numeric, including uncommon doubles.
  const double defPos = 1.0e300;
  const double defNeg = -1.0e-300;

  EXPECT_DOUBLE_EQ(Object::null().getNumWithDefaultValue(defPos), defPos);
  EXPECT_DOUBLE_EQ(Object::error().getNumWithDefaultValue(defNeg), defNeg);
}

}  // namespace