// Object_ctor_name_cmd_test_2749.cc
#include <gtest/gtest.h>

#include <string>
#include <string_view>

#include "Object.h"

class ObjectTest_2749 : public ::testing::Test {};

// Normal operation: objName stores type and string content.
TEST_F(ObjectTest_2749, ConstructObjNameStoresTypeAndValue_2749)
{
    const std::string v = "MyName";
    Object obj(objName, std::string_view(v));

    EXPECT_EQ(obj.getType(), objName);
    EXPECT_TRUE(obj.isName());
    EXPECT_FALSE(obj.isCmd());

    // Observable via public accessor.
    EXPECT_STREQ(obj.getName(), v.c_str());
}

// Normal operation: objCmd stores type and string content.
TEST_F(ObjectTest_2749, ConstructObjCmdStoresTypeAndValue_2749)
{
    const std::string v = "MyCmd";
    Object obj(objCmd, std::string_view(v));

    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_TRUE(obj.isCmd());
    EXPECT_FALSE(obj.isName());

    EXPECT_STREQ(obj.getCmd(), v.c_str());
}

// Boundary: empty string for objName should be accepted and retrievable.
TEST_F(ObjectTest_2749, ConstructObjNameWithEmptyString_2749)
{
    Object obj(objName, std::string_view(""));

    EXPECT_EQ(obj.getType(), objName);
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

// Boundary: large string should be copied and retrievable intact.
TEST_F(ObjectTest_2749, ConstructObjNameWithLargeString_2749)
{
    const std::string v(4096, 'a');
    Object obj(objName, std::string_view(v));

    EXPECT_EQ(obj.getType(), objName);
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), v.c_str());
}

// Normal operation: const char* overload should behave the same as string_view ctor.
TEST_F(ObjectTest_2749, ConstructFromCStringOverload_2749)
{
    Object nameObj(objName, "LiteralName");
    EXPECT_EQ(nameObj.getType(), objName);
    EXPECT_TRUE(nameObj.isName());
    EXPECT_STREQ(nameObj.getName(), "LiteralName");

    Object cmdObj(objCmd, "LiteralCmd");
    EXPECT_EQ(cmdObj.getType(), objCmd);
    EXPECT_TRUE(cmdObj.isCmd());
    EXPECT_STREQ(cmdObj.getCmd(), "LiteralCmd");
}

// Exceptional/error case (observable): invalid ObjType should trigger an assertion
// in debug builds. In release builds, assert() is typically compiled out.
#if GTEST_HAS_DEATH_TEST
#ifndef NDEBUG
TEST_F(ObjectTest_2749, DeathOnInvalidType_2749)
{
    EXPECT_DEATH(
        {
            Object obj(objInt, std::string_view("not allowed"));
            (void)obj;
        },
        ".*");
}
#endif
#endif