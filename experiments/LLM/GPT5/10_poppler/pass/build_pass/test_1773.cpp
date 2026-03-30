//===----------------------------------------------------------------------===//
//
// Unit tests for StructElement.cc (static helper: isNumberOrAuto)
//
// TEST_ID: 1773
//
// NOTE:
// - The function under test is a TU-local `static` in StructElement.cc.
// - To test it without re-implementing logic, we include the implementation file
//   directly so the tests compile in the same translation unit.
//
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include "poppler/Object.h"

// Include the implementation file to access the TU-local static helper.
// This is intentional for testing file-local statics as a black box.
#include "poppler/StructElement.cc"

namespace {

class StructElement_IsNumberOrAutoTest_1773 : public ::testing::Test {};

TEST_F(StructElement_IsNumberOrAutoTest_1773, ReturnsTrueForInt_1773)
{
    Object v(123);
    EXPECT_TRUE(isNumberOrAuto(&v));
}

TEST_F(StructElement_IsNumberOrAutoTest_1773, ReturnsTrueForReal_1773)
{
    Object v(3.14159);
    EXPECT_TRUE(isNumberOrAuto(&v));
}

TEST_F(StructElement_IsNumberOrAutoTest_1773, ReturnsTrueForInt64_1773)
{
    Object v(static_cast<long long>(9223372036854775807LL));
    EXPECT_TRUE(isNumberOrAuto(&v));
}

TEST_F(StructElement_IsNumberOrAutoTest_1773, ReturnsTrueForNameAuto_1773)
{
    Object v(objName, "Auto");
    EXPECT_TRUE(isNumberOrAuto(&v));
}

TEST_F(StructElement_IsNumberOrAutoTest_1773, ReturnsFalseForDifferentName_1773)
{
    Object v(objName, "NotAuto");
    EXPECT_FALSE(isNumberOrAuto(&v));
}

TEST_F(StructElement_IsNumberOrAutoTest_1773, ReturnsFalseForNameCaseMismatch_1773)
{
    Object v(objName, "auto"); // case-sensitive name match
    EXPECT_FALSE(isNumberOrAuto(&v));
}

TEST_F(StructElement_IsNumberOrAutoTest_1773, ReturnsFalseForBool_1773)
{
    Object v(true);
    EXPECT_FALSE(isNumberOrAuto(&v));
}

TEST_F(StructElement_IsNumberOrAutoTest_1773, ReturnsFalseForNull_1773)
{
    Object v = Object::null();
    EXPECT_FALSE(isNumberOrAuto(&v));
}

} // namespace