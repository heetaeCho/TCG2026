#include <gtest/gtest.h>
#include "poppler/Link.h"
#include "poppler/Object.h"

class LinkNamedTest_299 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getKind() returns actionNamed
TEST_F(LinkNamedTest_299, GetKindReturnsActionNamed_299) {
    Object nameObj;
    nameObj.initString(new GooString("NextPage"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_EQ(linkNamed.getKind(), actionNamed);
}

// Test that a valid name string makes isOk() return true
TEST_F(LinkNamedTest_299, ValidNameIsOk_299) {
    Object nameObj;
    nameObj.initString(new GooString("NextPage"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_TRUE(linkNamed.isOk());
}

// Test that getName() returns the correct name string
TEST_F(LinkNamedTest_299, GetNameReturnsCorrectName_299) {
    Object nameObj;
    nameObj.initString(new GooString("NextPage"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_EQ(linkNamed.getName(), "NextPage");
}

// Test with different named action strings
TEST_F(LinkNamedTest_299, GetNamePrevPage_299) {
    Object nameObj;
    nameObj.initString(new GooString("PrevPage"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_TRUE(linkNamed.isOk());
    EXPECT_EQ(linkNamed.getName(), "PrevPage");
}

TEST_F(LinkNamedTest_299, GetNameFirstPage_299) {
    Object nameObj;
    nameObj.initString(new GooString("FirstPage"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_TRUE(linkNamed.isOk());
    EXPECT_EQ(linkNamed.getName(), "FirstPage");
}

TEST_F(LinkNamedTest_299, GetNameLastPage_299) {
    Object nameObj;
    nameObj.initString(new GooString("LastPage"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_TRUE(linkNamed.isOk());
    EXPECT_EQ(linkNamed.getName(), "LastPage");
}

// Test with a null/invalid object - should not be ok
TEST_F(LinkNamedTest_299, NullObjectNotOk_299) {
    Object nameObj;
    nameObj.initNull();
    LinkNamed linkNamed(&nameObj);
    EXPECT_FALSE(linkNamed.isOk());
}

// Test that even with invalid object, getKind still returns actionNamed
TEST_F(LinkNamedTest_299, InvalidObjectStillReturnsActionNamed_299) {
    Object nameObj;
    nameObj.initNull();
    LinkNamed linkNamed(&nameObj);
    EXPECT_EQ(linkNamed.getKind(), actionNamed);
}

// Test with empty string name
TEST_F(LinkNamedTest_299, EmptyStringName_299) {
    Object nameObj;
    nameObj.initString(new GooString(""));
    LinkNamed linkNamed(&nameObj);
    // Even an empty string is still a valid string object
    EXPECT_EQ(linkNamed.getKind(), actionNamed);
}

// Test with a name object (PDF Name type)
TEST_F(LinkNamedTest_299, NameObjectType_299) {
    Object nameObj;
    nameObj.initName("GoBack");
    LinkNamed linkNamed(&nameObj);
    EXPECT_EQ(linkNamed.getKind(), actionNamed);
}

// Test with Print named action
TEST_F(LinkNamedTest_299, GetNamePrint_299) {
    Object nameObj;
    nameObj.initString(new GooString("Print"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_TRUE(linkNamed.isOk());
    EXPECT_EQ(linkNamed.getName(), "Print");
}

// Test with GoBack named action
TEST_F(LinkNamedTest_299, GetNameGoBack_299) {
    Object nameObj;
    nameObj.initString(new GooString("GoBack"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_TRUE(linkNamed.isOk());
    EXPECT_EQ(linkNamed.getName(), "GoBack");
}

// Test that actionNamed has the expected enum value
TEST_F(LinkNamedTest_299, ActionNamedEnumValue_299) {
    EXPECT_EQ(actionNamed, 4);
}
