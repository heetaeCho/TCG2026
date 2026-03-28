// TEST_ID: 1761
#include <gtest/gtest.h>

#include <limits>

#include "Object.h"

// We include the .cc directly to access the file-local helper (static) as a black-box.
// This avoids re-implementing any logic while still testing observable behavior.
#include "StructElement.cc"

namespace {

class StructElementIsLineHeightTest_1761 : public ::testing::Test {
protected:
  // Helper to create a PDF "name" Object (e.g., /Normal, /Auto) via the public Object interface.
  static Object MakeName(const char *name) { return Object(objName, name); }
};

TEST_F(StructElementIsLineHeightTest_1761, NameNormalIsLineHeight_1761)
{
  Object v = MakeName("Normal");
  EXPECT_TRUE(isLineHeight(&v));
}

TEST_F(StructElementIsLineHeightTest_1761, NameAutoIsLineHeight_1761)
{
  Object v = MakeName("Auto");
  EXPECT_TRUE(isLineHeight(&v));
}

TEST_F(StructElementIsLineHeightTest_1761, OtherNameIsNotLineHeight_1761)
{
  Object v = MakeName("SomethingElse");
  EXPECT_FALSE(isLineHeight(&v));
}

TEST_F(StructElementIsLineHeightTest_1761, IntegerValuesAreLineHeight_1761)
{
  Object zero(0);
  EXPECT_TRUE(isLineHeight(&zero));

  Object neg(-1);
  EXPECT_TRUE(isLineHeight(&neg));

  Object maxInt(std::numeric_limits<int>::max());
  EXPECT_TRUE(isLineHeight(&maxInt));

  Object minInt(std::numeric_limits<int>::min());
  EXPECT_TRUE(isLineHeight(&minInt));
}

TEST_F(StructElementIsLineHeightTest_1761, RealValuesAreLineHeight_1761)
{
  Object zero(0.0);
  EXPECT_TRUE(isLineHeight(&zero));

  Object neg(-123.5);
  EXPECT_TRUE(isLineHeight(&neg));

  Object big(1.0e9);
  EXPECT_TRUE(isLineHeight(&big));
}

TEST_F(StructElementIsLineHeightTest_1761, NonNumericNonNameObjectsAreNotLineHeight_1761)
{
  Object b(true);
  EXPECT_FALSE(isLineHeight(&b));

  Object n = Object::null();
  EXPECT_FALSE(isLineHeight(&n));

  Object e = Object::error();
  EXPECT_FALSE(isLineHeight(&e));

  Object eof = Object::eof();
  EXPECT_FALSE(isLineHeight(&eof));
}

} // namespace