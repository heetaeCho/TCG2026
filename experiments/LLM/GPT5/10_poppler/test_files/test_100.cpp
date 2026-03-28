// TEST_ID: 100
// Unit tests for Object::getNameString()
// File: Object_getNameString_test_100.cpp

#include <gtest/gtest.h>

#include <string>
#include <string_view>
#include <utility>

// Adjust include path if needed for your build (e.g., <poppler/Object.h>)
#include "poppler/Object.h"

namespace {

// A simple fixture (kept for consistent naming / future expansion).
class ObjectGetNameStringTest_100 : public ::testing::Test {};

TEST_F(ObjectGetNameStringTest_100, ReturnsSameStringWhenConstructedFromConstChar_100)
{
    Object nameObj(objName, "MyName");
    const std::string s = nameObj.getNameString();
    EXPECT_EQ(s, "MyName");
    EXPECT_EQ(s.size(), std::string("MyName").size());
}

TEST_F(ObjectGetNameStringTest_100, ReturnsSameStringWhenConstructedFromStringView_100)
{
    std::string backing = "NameFromView";
    std::string_view v(backing);

    Object nameObj(objName, v);
    EXPECT_EQ(nameObj.getNameString(), "NameFromView");
}

TEST_F(ObjectGetNameStringTest_100, ReturnsSameStringWhenConstructedFromRvalueString_100)
{
    std::string src = "MovedName";
    Object nameObj(objName, std::move(src));

    // We only validate the observable output.
    EXPECT_EQ(nameObj.getNameString(), "MovedName");
}

TEST_F(ObjectGetNameStringTest_100, EmptyNameIsSupported_100)
{
    Object nameObj(objName, "");
    const std::string s = nameObj.getNameString();
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s, "");
}

TEST_F(ObjectGetNameStringTest_100, LongNameIsPreserved_100)
{
    std::string longName(4096, 'a');
    Object nameObj(objName, std::string_view(longName));

    const std::string s = nameObj.getNameString();
    EXPECT_EQ(s.size(), longName.size());
    EXPECT_EQ(s, longName);
}

TEST_F(ObjectGetNameStringTest_100, WorksAfterMoveConstruction_100)
{
    Object original(objName, "AfterMove");
    Object moved(std::move(original));

    EXPECT_EQ(moved.getNameString(), "AfterMove");
}

TEST_F(ObjectGetNameStringTest_100, WorksAfterMoveAssignment_100)
{
    Object a(objName, "First");
    Object b(objName, "Second");

    b = std::move(a);

    EXPECT_EQ(b.getNameString(), "First");
}

#ifndef NDEBUG
// In many Poppler builds, OBJECT_TYPE_CHECK(...) is an assert-like check.
// These death tests are only enabled in debug builds to avoid false failures
// when type checks are compiled out.
TEST_F(ObjectGetNameStringTest_100, DeathOnNonNameTypeBool_100)
{
    Object o(true);
    EXPECT_DEATH_IF_SUPPORTED(
        {
            (void)o.getNameString();
        },
        "");
}

TEST_F(ObjectGetNameStringTest_100, DeathOnNonNameTypeInt_100)
{
    Object o(123);
    EXPECT_DEATH_IF_SUPPORTED(
        {
            (void)o.getNameString();
        },
        "");
}

TEST_F(ObjectGetNameStringTest_100, DeathOnNullObject_100)
{
    Object o = Object::null();
    EXPECT_DEATH_IF_SUPPORTED(
        {
            (void)o.getNameString();
        },
        "");
}
#endif

} // namespace