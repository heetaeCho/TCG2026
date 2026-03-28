// File: StructElement_isRubyPositionName_1764_test.cc
#include <gtest/gtest.h>

#include "Object.h"

// NOTE:
// isRubyPositionName is a file-local (static) function in StructElement.cc.
// To test it as a black box via its real implementation, we include the .cc
// directly into this test translation unit.
#include "StructElement.cc"

namespace {

TEST(StructElementTest_1764, IsRubyPositionName_ReturnsTrueForBefore_1764)
{
    Object v(objName, "Before");
    EXPECT_TRUE(isRubyPositionName(&v));
}

TEST(StructElementTest_1764, IsRubyPositionName_ReturnsTrueForAfter_1764)
{
    Object v(objName, "After");
    EXPECT_TRUE(isRubyPositionName(&v));
}

TEST(StructElementTest_1764, IsRubyPositionName_ReturnsTrueForWarichu_1764)
{
    Object v(objName, "Warichu");
    EXPECT_TRUE(isRubyPositionName(&v));
}

TEST(StructElementTest_1764, IsRubyPositionName_ReturnsTrueForInline_1764)
{
    Object v(objName, "Inline");
    EXPECT_TRUE(isRubyPositionName(&v));
}

TEST(StructElementTest_1764, IsRubyPositionName_ReturnsFalseForOtherName_1764)
{
    Object v(objName, "NotARubyPosition");
    EXPECT_FALSE(isRubyPositionName(&v));
}

TEST(StructElementTest_1764, IsRubyPositionName_IsCaseSensitive_1764)
{
    Object v1(objName, "before");
    Object v2(objName, "AFTER");
    Object v3(objName, "warichu");
    Object v4(objName, "INLINE");

    EXPECT_FALSE(isRubyPositionName(&v1));
    EXPECT_FALSE(isRubyPositionName(&v2));
    EXPECT_FALSE(isRubyPositionName(&v3));
    EXPECT_FALSE(isRubyPositionName(&v4));
}

TEST(StructElementTest_1764, IsRubyPositionName_ReturnsFalseForNonNameObjects_1764)
{
    Object b(true);
    Object i(1);
    Object r(1.25);
    Object s(std::string("Before")); // string object, not a Name
    Object n = Object::null();

    EXPECT_FALSE(isRubyPositionName(&b));
    EXPECT_FALSE(isRubyPositionName(&i));
    EXPECT_FALSE(isRubyPositionName(&r));
    EXPECT_FALSE(isRubyPositionName(&s));
    EXPECT_FALSE(isRubyPositionName(&n));
}

} // namespace