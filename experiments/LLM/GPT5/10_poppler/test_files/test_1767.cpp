// Copyright (C) 2026
// Unit tests for isFieldRoleName(Object*) in StructElement.cc
//
// TEST_ID: 1767

#include <gtest/gtest.h>

#include "poppler/Object.h"

// NOTE:
// isFieldRoleName is a file-static function in StructElement.cc.
// To test it as a black box without re-implementing logic, we include the .cc
// so the function is compiled into this test translation unit.
#include "poppler/StructElement.cc"

namespace {

class IsFieldRoleNameTest_1767 : public ::testing::Test {};

TEST_F(IsFieldRoleNameTest_1767, ReturnsTrueForRecognizedRoleNames_1767)
{
    Object rb(objName, "rb");
    Object cb(objName, "cb");
    Object pb(objName, "pb");
    Object tv(objName, "tv");

    EXPECT_TRUE(isFieldRoleName(&rb));
    EXPECT_TRUE(isFieldRoleName(&cb));
    EXPECT_TRUE(isFieldRoleName(&pb));
    EXPECT_TRUE(isFieldRoleName(&tv));
}

TEST_F(IsFieldRoleNameTest_1767, ReturnsFalseForOtherNameValues_1767)
{
    Object empty(objName, "");
    Object upperRB(objName, "RB");
    Object prefix(objName, "r");
    Object longer(objName, "rbb");
    Object spaced(objName, "r b");
    Object similar(objName, "tb"); // close to "tv" but not equal

    EXPECT_FALSE(isFieldRoleName(&empty));
    EXPECT_FALSE(isFieldRoleName(&upperRB));
    EXPECT_FALSE(isFieldRoleName(&prefix));
    EXPECT_FALSE(isFieldRoleName(&longer));
    EXPECT_FALSE(isFieldRoleName(&spaced));
    EXPECT_FALSE(isFieldRoleName(&similar));
}

TEST_F(IsFieldRoleNameTest_1767, ReturnsFalseWhenObjectIsNotAName_1767)
{
    Object asNull = Object::null();
    Object asBool(true);
    Object asInt(42);
    Object asReal(3.14);
    Object asString(std::string("rb")); // string, not name

    EXPECT_FALSE(isFieldRoleName(&asNull));
    EXPECT_FALSE(isFieldRoleName(&asBool));
    EXPECT_FALSE(isFieldRoleName(&asInt));
    EXPECT_FALSE(isFieldRoleName(&asReal));
    EXPECT_FALSE(isFieldRoleName(&asString));
}

TEST_F(IsFieldRoleNameTest_1767, BoundaryNameValuesAreCaseSensitive_1767)
{
    Object lower(objName, "tv");
    Object mixed(objName, "tV");
    Object upper(objName, "TV");

    EXPECT_TRUE(isFieldRoleName(&lower));
    EXPECT_FALSE(isFieldRoleName(&mixed));
    EXPECT_FALSE(isFieldRoleName(&upper));
}

} // namespace