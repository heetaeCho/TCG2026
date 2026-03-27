// StructElement_isWritingModeName_tests_1755.cc
#include <gtest/gtest.h>

#include "Object.h"

// NOTE:
// The function under test has internal linkage (static) in StructElement.cc.
// To test it as a black box through its declared interface, we include the
// implementation file here so the symbol is visible in this translation unit.
#include "StructElement.cc"

namespace {

class StructElementIsWritingModeNameTest_1755 : public ::testing::Test {};

TEST_F(StructElementIsWritingModeNameTest_1755, ReturnsTrueForLrTb_1755)
{
  Object v(objName, "LrTb");
  EXPECT_TRUE(isWritingModeName(&v));
}

TEST_F(StructElementIsWritingModeNameTest_1755, ReturnsTrueForRlTb_1755)
{
  Object v(objName, "RlTb");
  EXPECT_TRUE(isWritingModeName(&v));
}

TEST_F(StructElementIsWritingModeNameTest_1755, ReturnsTrueForTbRl_1755)
{
  Object v(objName, "TbRl");
  EXPECT_TRUE(isWritingModeName(&v));
}

TEST_F(StructElementIsWritingModeNameTest_1755, ReturnsFalseForOtherName_1755)
{
  Object v(objName, "LRtb"); // close but not equal
  EXPECT_FALSE(isWritingModeName(&v));

  Object v2(objName, ""); // boundary: empty name
  EXPECT_FALSE(isWritingModeName(&v2));

  Object v3(objName, "SomethingElse");
  EXPECT_FALSE(isWritingModeName(&v3));
}

TEST_F(StructElementIsWritingModeNameTest_1755, ReturnsFalseForNonNameObjects_1755)
{
  Object b(true);
  EXPECT_FALSE(isWritingModeName(&b));

  Object i(123);
  EXPECT_FALSE(isWritingModeName(&i));

  Object r(1.25);
  EXPECT_FALSE(isWritingModeName(&r));

  Object n = Object::null();
  EXPECT_FALSE(isWritingModeName(&n));

  Object e = Object::error();
  EXPECT_FALSE(isWritingModeName(&e));

  Object eof = Object::eof();
  EXPECT_FALSE(isWritingModeName(&eof));
}

} // namespace