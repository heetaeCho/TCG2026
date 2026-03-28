// File: StructElement_isTextAlignName_test_1757.cc
#include <gtest/gtest.h>

// Poppler includes
#include "Object.h"

// NOTE:
// `isTextAlignName` is a file-local `static` helper in StructElement.cc.
// The most direct black-box way to unit test it is to include the .cc file
// into this test translation unit so the symbol is visible here.
//
// If your build setup already compiles StructElement.cc separately into a
// library and you cannot include .cc files in tests, you will need to expose
// this helper through a public/test hook instead. For this task, we follow
// the provided interface as-is.
#include "StructElement.cc"

namespace {

class IsTextAlignNameTest_1757 : public ::testing::Test {};

TEST_F(IsTextAlignNameTest_1757, ReturnsTrueForStart_1757)
{
  Object v(objName, "Start");
  EXPECT_TRUE(isTextAlignName(&v));
}

TEST_F(IsTextAlignNameTest_1757, ReturnsTrueForEnd_1757)
{
  Object v(objName, "End");
  EXPECT_TRUE(isTextAlignName(&v));
}

TEST_F(IsTextAlignNameTest_1757, ReturnsTrueForCenter_1757)
{
  Object v(objName, "Center");
  EXPECT_TRUE(isTextAlignName(&v));
}

TEST_F(IsTextAlignNameTest_1757, ReturnsTrueForJustify_1757)
{
  Object v(objName, "Justify");
  EXPECT_TRUE(isTextAlignName(&v));
}

TEST_F(IsTextAlignNameTest_1757, ReturnsFalseForOtherName_1757)
{
  Object v(objName, "Left");
  EXPECT_FALSE(isTextAlignName(&v));
}

TEST_F(IsTextAlignNameTest_1757, ReturnsFalseForCaseMismatch_1757)
{
  Object v1(objName, "start");
  Object v2(objName, "JUSTIFY");
  EXPECT_FALSE(isTextAlignName(&v1));
  EXPECT_FALSE(isTextAlignName(&v2));
}

TEST_F(IsTextAlignNameTest_1757, ReturnsFalseWhenNotAName_Int_1757)
{
  Object v(123);
  EXPECT_FALSE(isTextAlignName(&v));
}

TEST_F(IsTextAlignNameTest_1757, ReturnsFalseWhenNotAName_Bool_1757)
{
  Object v(true);
  EXPECT_FALSE(isTextAlignName(&v));
}

TEST_F(IsTextAlignNameTest_1757, ReturnsFalseWhenNotAName_String_1757)
{
  Object v(std::string("Start")); // string object, not a name object
  EXPECT_FALSE(isTextAlignName(&v));
}

TEST_F(IsTextAlignNameTest_1757, ReturnsFalseWhenNullObject_1757)
{
  Object v = Object::null();
  EXPECT_FALSE(isTextAlignName(&v));
}

} // namespace