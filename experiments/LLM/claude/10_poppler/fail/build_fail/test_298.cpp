#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"

class LinkNamedTest_298 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that LinkNamed constructed with a valid name Object is OK
TEST_F(LinkNamedTest_298, ConstructWithValidNameObject_IsOk_298) {
    Object nameObj = Object(new GooString("GoBack"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_TRUE(linkNamed.isOk());
}

// Test that LinkNamed constructed with a valid name returns correct kind
TEST_F(LinkNamedTest_298, ConstructWithValidNameObject_KindIsNamed_298) {
    Object nameObj = Object(new GooString("GoBack"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_EQ(linkNamed.getKind(), actionNamed);
}

// Test that LinkNamed constructed with a valid name returns the name
TEST_F(LinkNamedTest_298, ConstructWithValidNameObject_GetName_298) {
    Object nameObj = Object(new GooString("GoBack"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_EQ(linkNamed.getName(), "GoBack");
}

// Test that LinkNamed constructed with null-type Object is not OK
TEST_F(LinkNamedTest_298, ConstructWithNullObject_IsNotOk_298) {
    Object nullObj;
    LinkNamed linkNamed(&nullObj);
    EXPECT_FALSE(linkNamed.isOk());
}

// Test that LinkNamed with integer object is not OK
TEST_F(LinkNamedTest_298, ConstructWithIntObject_IsNotOk_298) {
    Object intObj = Object(42);
    LinkNamed linkNamed(&intObj);
    EXPECT_FALSE(linkNamed.isOk());
}

// Test with empty string name
TEST_F(LinkNamedTest_298, ConstructWithEmptyStringName_298) {
    Object nameObj = Object(new GooString(""));
    LinkNamed linkNamed(&nameObj);
    // Even empty string is a valid name object, so isOk depends on implementation
    // We just verify it doesn't crash and getName returns empty
    if (linkNamed.isOk()) {
        EXPECT_TRUE(linkNamed.getName().empty());
    }
}

// Test with various known named actions
TEST_F(LinkNamedTest_298, ConstructWithNextPageName_298) {
    Object nameObj = Object(new GooString("NextPage"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_TRUE(linkNamed.isOk());
    EXPECT_EQ(linkNamed.getName(), "NextPage");
}

TEST_F(LinkNamedTest_298, ConstructWithPrevPageName_298) {
    Object nameObj = Object(new GooString("PrevPage"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_TRUE(linkNamed.isOk());
    EXPECT_EQ(linkNamed.getName(), "PrevPage");
}

TEST_F(LinkNamedTest_298, ConstructWithFirstPageName_298) {
    Object nameObj = Object(new GooString("FirstPage"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_TRUE(linkNamed.isOk());
    EXPECT_EQ(linkNamed.getName(), "FirstPage");
}

TEST_F(LinkNamedTest_298, ConstructWithLastPageName_298) {
    Object nameObj = Object(new GooString("LastPage"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_TRUE(linkNamed.isOk());
    EXPECT_EQ(linkNamed.getName(), "LastPage");
}

// Test with a non-standard name
TEST_F(LinkNamedTest_298, ConstructWithCustomName_298) {
    Object nameObj = Object(new GooString("CustomAction"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_TRUE(linkNamed.isOk());
    EXPECT_EQ(linkNamed.getName(), "CustomAction");
}

// Test getKind always returns actionNamed for valid objects
TEST_F(LinkNamedTest_298, GetKindReturnsActionNamed_298) {
    Object nameObj = Object(new GooString("Print"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_EQ(linkNamed.getKind(), actionNamed);
}

// Test with boolean object - should not be OK
TEST_F(LinkNamedTest_298, ConstructWithBoolObject_IsNotOk_298) {
    Object boolObj = Object(true);
    LinkNamed linkNamed(&boolObj);
    EXPECT_FALSE(linkNamed.isOk());
}

// Test with real number object - should not be OK
TEST_F(LinkNamedTest_298, ConstructWithRealObject_IsNotOk_298) {
    Object realObj = Object(3.14);
    LinkNamed linkNamed(&realObj);
    EXPECT_FALSE(linkNamed.isOk());
}
