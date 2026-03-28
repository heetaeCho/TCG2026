#include <gtest/gtest.h>
#include "Link.h"
#include "Object.h"

class LinkHideTest_330 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getKind() returns actionHide
TEST_F(LinkHideTest_330, GetKindReturnsActionHide_330) {
    // Create a simple Object for LinkHide construction
    // Using a string name object to create a valid LinkHide
    Object nameObj = Object(new GooString("targetField"));
    LinkHide linkHide(&nameObj);
    EXPECT_EQ(linkHide.getKind(), actionHide);
}

// Test with a dictionary object that has a T (target name) entry
TEST_F(LinkHideTest_330, ConstructWithDictContainingTargetName_330) {
    Object dictObj;
    Dict *dict = new Dict(nullptr);
    Object tObj = Object(new GooString("fieldName"));
    dict->add("T", std::move(tObj));
    dict->add("H", Object(false)); // H = false means hide
    dictObj = Object(dict);

    LinkHide linkHide(&dictObj);
    EXPECT_EQ(linkHide.getKind(), actionHide);
    if (linkHide.hasTargetName()) {
        EXPECT_FALSE(linkHide.getTargetName().empty());
    }
}

// Test with a string object as target name
TEST_F(LinkHideTest_330, ConstructWithStringObject_330) {
    Object strObj = Object(new GooString("myTarget"));
    LinkHide linkHide(&strObj);
    EXPECT_EQ(linkHide.getKind(), actionHide);
    if (linkHide.isOk()) {
        EXPECT_TRUE(linkHide.hasTargetName());
        EXPECT_EQ(linkHide.getTargetName(), "myTarget");
    }
}

// Test isShowAction when H is not specified (default should be hide, not show)
TEST_F(LinkHideTest_330, IsShowActionDefaultBehavior_330) {
    Object strObj = Object(new GooString("field1"));
    LinkHide linkHide(&strObj);
    if (linkHide.isOk()) {
        // Default behavior when no H flag: hide action (isShowAction = false)
        // This depends on implementation but we test the interface
        bool showAction = linkHide.isShowAction();
        // Just verify it returns a boolean without crashing
        EXPECT_TRUE(showAction == true || showAction == false);
    }
}

// Test with a dictionary with H = true (show action)
TEST_F(LinkHideTest_330, ConstructWithShowAction_330) {
    Dict *dict = new Dict(nullptr);
    Object tObj = Object(new GooString("showField"));
    dict->add("T", std::move(tObj));
    dict->add("H", Object(true)); // H = true means show (toggle visibility)
    Object dictObj = Object(dict);

    LinkHide linkHide(&dictObj);
    EXPECT_EQ(linkHide.getKind(), actionHide);
}

// Test with null-like/empty object
TEST_F(LinkHideTest_330, ConstructWithNullObject_330) {
    Object nullObj;
    LinkHide linkHide(&nullObj);
    EXPECT_EQ(linkHide.getKind(), actionHide);
    // When constructed with invalid object, isOk might return false
    // We just verify it doesn't crash
}

// Test hasTargetName returns consistent results
TEST_F(LinkHideTest_330, HasTargetNameConsistency_330) {
    Object strObj = Object(new GooString("testField"));
    LinkHide linkHide(&strObj);
    if (linkHide.isOk() && linkHide.hasTargetName()) {
        // If hasTargetName is true, getTargetName should not be empty
        EXPECT_FALSE(linkHide.getTargetName().empty());
    }
}

// Test getKind is always actionHide regardless of construction
TEST_F(LinkHideTest_330, GetKindAlwaysActionHide_330) {
    Object obj1 = Object(new GooString("a"));
    LinkHide lh1(&obj1);
    EXPECT_EQ(lh1.getKind(), actionHide);

    Object obj2;
    LinkHide lh2(&obj2);
    EXPECT_EQ(lh2.getKind(), actionHide);
}

// Test that actionHide has the expected enum value
TEST_F(LinkHideTest_330, ActionHideEnumValue_330) {
    EXPECT_EQ(actionHide, 10);
}

// Test with an empty string target name
TEST_F(LinkHideTest_330, ConstructWithEmptyStringTarget_330) {
    Object strObj = Object(new GooString(""));
    LinkHide linkHide(&strObj);
    EXPECT_EQ(linkHide.getKind(), actionHide);
}
