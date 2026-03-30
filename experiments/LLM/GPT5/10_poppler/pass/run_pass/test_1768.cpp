// TEST_ID: 1768
#include <gtest/gtest.h>

// Include the implementation file to access the internal-linkage helper.
// This keeps the test black-box w.r.t. implementation details while still
// letting us exercise the observable behavior of this translation unit.
#include "StructElement.cc"

#include "Object.h"

namespace {

class StructElementTest_1768 : public ::testing::Test {};

TEST_F(StructElementTest_1768, ReturnsTrueForOnName_1768)
{
  Object v(objName, "on");
  EXPECT_TRUE(isFieldCheckedName(&v));
}

TEST_F(StructElementTest_1768, ReturnsTrueForOffName_1768)
{
  Object v(objName, "off");
  EXPECT_TRUE(isFieldCheckedName(&v));
}

TEST_F(StructElementTest_1768, ReturnsTrueForNeutralName_1768)
{
  Object v(objName, "neutral");
  EXPECT_TRUE(isFieldCheckedName(&v));
}

TEST_F(StructElementTest_1768, ReturnsFalseForOtherName_1768)
{
  Object v(objName, "yes");
  EXPECT_FALSE(isFieldCheckedName(&v));

  Object v2(objName, "");
  EXPECT_FALSE(isFieldCheckedName(&v2));

  Object v3(objName, "On"); // boundary: case sensitivity
  EXPECT_FALSE(isFieldCheckedName(&v3));
}

TEST_F(StructElementTest_1768, ReturnsFalseForNonNameTypes_1768)
{
  Object b(true);
  EXPECT_FALSE(isFieldCheckedName(&b));

  Object i(1);
  EXPECT_FALSE(isFieldCheckedName(&i));

  Object r(1.25);
  EXPECT_FALSE(isFieldCheckedName(&r));

  Object n = Object::null();
  EXPECT_FALSE(isFieldCheckedName(&n));

  Object e = Object::error();
  EXPECT_FALSE(isFieldCheckedName(&e));

  Object eof = Object::eof();
  EXPECT_FALSE(isFieldCheckedName(&eof));
}

#if GTEST_HAS_DEATH_TEST
TEST_F(StructElementTest_1768, DiesOnNullPointer_1768)
{
  // Exceptional/error case: passing a null pointer is invalid for this API.
  // The implementation dereferences `value`, so we assert it crashes.
  EXPECT_DEATH({ (void)isFieldCheckedName(nullptr); }, ".*");
}
#endif

} // namespace