// File: StructElement_isListNumberingName_test_1766.cc

#include <gtest/gtest.h>

#include "Object.h"

// NOTE: `isListNumberingName` is a `static` helper in StructElement.cc (internal linkage).
// To test it via its provided signature, we include the implementation file here so the
// function is visible in this translation unit.
#include "StructElement.cc"

namespace {

class IsListNumberingNameTest_1766 : public ::testing::Test {};

TEST_F(IsListNumberingNameTest_1766, ReturnsTrueForAllRecognizedNames_1766)
{
  const char *kValidNames[] = {
      "None",       "Disc",      "Circle",    "Square",    "Decimal",
      "UpperRoman", "LowerRoman", "UpperAlpha","LowerAlpha"
  };

  for (const char *name : kValidNames) {
    Object obj(objName, name);
    EXPECT_TRUE(isListNumberingName(&obj)) << "Expected true for name: " << name;
  }
}

TEST_F(IsListNumberingNameTest_1766, ReturnsFalseForUnrecognizedName_1766)
{
  Object obj(objName, "NotAListStyle");
  EXPECT_FALSE(isListNumberingName(&obj));
}

TEST_F(IsListNumberingNameTest_1766, ReturnsFalseForCaseMismatch_1766)
{
  Object obj1(objName, "none");
  Object obj2(objName, "disc");
  Object obj3(objName, "UPPERROMAN");

  EXPECT_FALSE(isListNumberingName(&obj1));
  EXPECT_FALSE(isListNumberingName(&obj2));
  EXPECT_FALSE(isListNumberingName(&obj3));
}

TEST_F(IsListNumberingNameTest_1766, ReturnsFalseForEmptyName_1766)
{
  Object obj(objName, "");
  EXPECT_FALSE(isListNumberingName(&obj));
}

TEST_F(IsListNumberingNameTest_1766, ReturnsFalseWhenObjectIsNotNameType_1766)
{
  Object nullObj = Object::null();
  Object boolObj(true);
  Object intObj(123);
  Object realObj(1.25);

  EXPECT_FALSE(isListNumberingName(&nullObj));
  EXPECT_FALSE(isListNumberingName(&boolObj));
  EXPECT_FALSE(isListNumberingName(&intObj));
  EXPECT_FALSE(isListNumberingName(&realObj));
}

TEST_F(IsListNumberingNameTest_1766, ReturnsFalseForNameWithExtraWhitespace_1766)
{
  Object obj1(objName, "Disc ");
  Object obj2(objName, " Disc");
  Object obj3(objName, "\tDecimal");

  EXPECT_FALSE(isListNumberingName(&obj1));
  EXPECT_FALSE(isListNumberingName(&obj2));
  EXPECT_FALSE(isListNumberingName(&obj3));
}

} // namespace