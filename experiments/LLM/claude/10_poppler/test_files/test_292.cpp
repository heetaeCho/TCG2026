#include <gtest/gtest.h>
#include "Link.h"

// Test that getKind() returns actionLaunch
TEST(LinkLaunchTest_292, GetKindReturnsActionLaunch_292)
{
    // We need to construct a LinkLaunch object. Since it takes an Object*,
    // we can try with a nullptr or a minimal Object to test observable behavior.
    // Note: The constructor expects const Object*, passing nullptr may result
    // in isOk() returning false, but getKind() should still return actionLaunch.
    Object obj;
    LinkLaunch launch(&obj);
    EXPECT_EQ(launch.getKind(), actionLaunch);
}

// Test that isOk() returns false when constructed with an empty/invalid Object
TEST(LinkLaunchTest_292, IsOkReturnsFalseForInvalidObject_292)
{
    Object obj;
    LinkLaunch launch(&obj);
    EXPECT_FALSE(launch.isOk());
}

// Test that getFileName() returns nullptr for invalid/empty construction
TEST(LinkLaunchTest_292, GetFileNameReturnsNullForInvalidObject_292)
{
    Object obj;
    LinkLaunch launch(&obj);
    EXPECT_EQ(launch.getFileName(), nullptr);
}

// Test that getParams() returns nullptr for invalid/empty construction
TEST(LinkLaunchTest_292, GetParamsReturnsNullForInvalidObject_292)
{
    Object obj;
    LinkLaunch launch(&obj);
    EXPECT_EQ(launch.getParams(), nullptr);
}

// Test with a properly formed action dictionary containing /F key
TEST(LinkLaunchTest_292, ConstructWithValidLaunchDict_292)
{
    // Build a dictionary Object that looks like a Launch action
    // /S /Launch /F (somefile.pdf)
    Object fileSpec;
    fileSpec = Object(new GooString("testfile.pdf"));

    Object dict(new Dict(nullptr));
    dict.dictAdd("F", std::move(fileSpec));

    LinkLaunch launch(&dict);
    // getKind should always be actionLaunch regardless of validity
    EXPECT_EQ(launch.getKind(), actionLaunch);
}

// Test that getKind returns the correct enum value (actionLaunch == 2)
TEST(LinkLaunchTest_292, GetKindValueIsTwo_292)
{
    Object obj;
    LinkLaunch launch(&obj);
    EXPECT_EQ(static_cast<int>(launch.getKind()), 2);
}

// Test that actionLaunch enum value is correct
TEST(LinkLaunchTest_292, ActionLaunchEnumValue_292)
{
    EXPECT_EQ(actionLaunch, 2);
}
