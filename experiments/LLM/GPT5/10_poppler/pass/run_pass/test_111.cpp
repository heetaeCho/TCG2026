// Object_getBoolWithDefaultValue_111_test.cpp

#include <gtest/gtest.h>

#include "poppler/Object.h"

namespace {

class ObjectTest_111 : public ::testing::Test {};

TEST_F(ObjectTest_111, ReturnsStoredBoolWhenTypeIsBoolTrue_111)
{
  const Object obj(true);
  EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
  EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_111, ReturnsStoredBoolWhenTypeIsBoolFalse_111)
{
  const Object obj(false);
  EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
  // Boundary-ish: default is opposite of stored value.
  EXPECT_FALSE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_111, ReturnsDefaultWhenTypeIsInt_111)
{
  const Object obj(123);
  EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
  EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_111, ReturnsDefaultWhenTypeIsReal_111)
{
  const Object obj(3.14159);
  EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
  EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_111, ReturnsDefaultWhenTypeIsNull_111)
{
  const Object obj = Object::null();
  EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
  EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_111, ReturnsDefaultWhenTypeIsEOF_111)
{
  const Object obj = Object::eof();
  EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
  EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_111, ReturnsDefaultWhenTypeIsError_111)
{
  const Object obj = Object::error();
  EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
  EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_111, ReturnsDefaultWhenTypeIsDefaultConstructedNone_111)
{
  const Object obj;
  EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
  EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

} // namespace