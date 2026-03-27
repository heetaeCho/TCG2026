// Test file for StructElement.cc (static helper)
// Focus: isBlockAlignName(Object *value)
//
// NOTE: isBlockAlignName is a static function in StructElement.cc (internal linkage).
// To test it as a black box without re-implementing it, we include the .cc directly
// so the tests are compiled in the same translation unit.

#include <gtest/gtest.h>

#include "Object.h"

// Include the production implementation to access the static function.
#include "StructElement.cc"

namespace {

TEST(IsBlockAlignNameTest_1758, ReturnsTrueForBefore_1758)
{
  Object v(objName, "Before");
  EXPECT_TRUE(isBlockAlignName(&v));
}

TEST(IsBlockAlignNameTest_1758, ReturnsTrueForMiddle_1758)
{
  Object v(objName, "Middle");
  EXPECT_TRUE(isBlockAlignName(&v));
}

TEST(IsBlockAlignNameTest_1758, ReturnsTrueForAfter_1758)
{
  Object v(objName, "After");
  EXPECT_TRUE(isBlockAlignName(&v));
}

TEST(IsBlockAlignNameTest_1758, ReturnsTrueForJustify_1758)
{
  Object v(objName, "Justify");
  EXPECT_TRUE(isBlockAlignName(&v));
}

TEST(IsBlockAlignNameTest_1758, ReturnsFalseForOtherName_1758)
{
  Object v(objName, "Start");
  EXPECT_FALSE(isBlockAlignName(&v));
}

TEST(IsBlockAlignNameTest_1758, ReturnsFalseForEmptyName_1758)
{
  Object v(objName, "");
  EXPECT_FALSE(isBlockAlignName(&v));
}

TEST(IsBlockAlignNameTest_1758, ReturnsFalseForCaseMismatch_1758)
{
  Object v1(objName, "before");
  Object v2(objName, "MIDDLE");
  Object v3(objName, "after");
  Object v4(objName, "justify");

  EXPECT_FALSE(isBlockAlignName(&v1));
  EXPECT_FALSE(isBlockAlignName(&v2));
  EXPECT_FALSE(isBlockAlignName(&v3));
  EXPECT_FALSE(isBlockAlignName(&v4));
}

TEST(IsBlockAlignNameTest_1758, ReturnsFalseForSubstringOrWhitespaceVariants_1758)
{
  Object v1(objName, "Before ");   // trailing space
  Object v2(objName, " Before");   // leading space
  Object v3(objName, "JustifyX");  // suffix
  Object v4(objName, "Mid");       // substring

  EXPECT_FALSE(isBlockAlignName(&v1));
  EXPECT_FALSE(isBlockAlignName(&v2));
  EXPECT_FALSE(isBlockAlignName(&v3));
  EXPECT_FALSE(isBlockAlignName(&v4));
}

TEST(IsBlockAlignNameTest_1758, ReturnsFalseForNonNameTypes_1758)
{
  Object b(true);
  Object i(1);
  Object r(1.25);
  Object s(std::string("Before")); // string object, not a name object
  Object n = Object::null();
  Object e = Object::error();
  Object f = Object::eof();

  EXPECT_FALSE(isBlockAlignName(&b));
  EXPECT_FALSE(isBlockAlignName(&i));
  EXPECT_FALSE(isBlockAlignName(&r));
  EXPECT_FALSE(isBlockAlignName(&s));
  EXPECT_FALSE(isBlockAlignName(&n));
  EXPECT_FALSE(isBlockAlignName(&e));
  EXPECT_FALSE(isBlockAlignName(&f));
}

TEST(IsBlockAlignNameTest_1758, DoesNotChangeObservablesOnInputObject_1758)
{
  Object v(objName, "Before");
  ASSERT_TRUE(v.isName("Before"));

  const bool result = isBlockAlignName(&v);

  EXPECT_TRUE(result);
  // Observable property should remain consistent (no reliance on private state).
  EXPECT_TRUE(v.isName("Before"));
}

} // namespace