#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"

class LinkNamedTest_300 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that LinkNamed constructed with a valid name string Object is ok
TEST_F(LinkNamedTest_300, ConstructWithValidNameString_IsOk_300) {
    Object nameObj = Object(new GooString("GoBack"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_TRUE(linkNamed.isOk());
}

// Test that getName returns the correct name when constructed with a valid string
TEST_F(LinkNamedTest_300, GetName_ReturnsCorrectName_300) {
    Object nameObj = Object(new GooString("GoBack"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_EQ(linkNamed.getName(), "GoBack");
}

// Test that getKind returns actionNamed
TEST_F(LinkNamedTest_300, GetKind_ReturnsActionNamed_300) {
    Object nameObj = Object(new GooString("GoForward"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_EQ(linkNamed.getKind(), actionNamed);
}

// Test with different named actions
TEST_F(LinkNamedTest_300, ConstructWithGoForward_300) {
    Object nameObj = Object(new GooString("GoForward"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_TRUE(linkNamed.isOk());
    EXPECT_EQ(linkNamed.getName(), "GoForward");
}

TEST_F(LinkNamedTest_300, ConstructWithPrint_300) {
    Object nameObj = Object(new GooString("Print"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_TRUE(linkNamed.isOk());
    EXPECT_EQ(linkNamed.getName(), "Print");
}

TEST_F(LinkNamedTest_300, ConstructWithQuit_300) {
    Object nameObj = Object(new GooString("Quit"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_TRUE(linkNamed.isOk());
    EXPECT_EQ(linkNamed.getName(), "Quit");
}

// Test construction with a non-string Object (e.g., null)
TEST_F(LinkNamedTest_300, ConstructWithNullObject_IsNotOk_300) {
    Object nullObj = Object(objNull);
    LinkNamed linkNamed(&nullObj);
    EXPECT_FALSE(linkNamed.isOk());
}

// Test that getName returns empty string when constructed with invalid object
TEST_F(LinkNamedTest_300, GetName_EmptyWhenInvalidObject_300) {
    Object nullObj = Object(objNull);
    LinkNamed linkNamed(&nullObj);
    EXPECT_TRUE(linkNamed.getName().empty());
}

// Test with empty string name
TEST_F(LinkNamedTest_300, ConstructWithEmptyString_300) {
    Object nameObj = Object(new GooString(""));
    LinkNamed linkNamed(&nameObj);
    EXPECT_EQ(linkNamed.getName(), "");
}

// Test with a long name string
TEST_F(LinkNamedTest_300, ConstructWithLongName_300) {
    std::string longName(1000, 'A');
    Object nameObj = Object(new GooString(longName.c_str()));
    LinkNamed linkNamed(&nameObj);
    EXPECT_EQ(linkNamed.getName(), longName);
}

// Test with integer Object type (not a string)
TEST_F(LinkNamedTest_300, ConstructWithIntObject_IsNotOk_300) {
    Object intObj = Object(42);
    LinkNamed linkNamed(&intObj);
    EXPECT_FALSE(linkNamed.isOk());
}

// Test that getKind always returns actionNamed regardless of validity
TEST_F(LinkNamedTest_300, GetKind_AlwaysReturnsActionNamed_300) {
    Object nullObj = Object(objNull);
    LinkNamed linkNamed(&nullObj);
    EXPECT_EQ(linkNamed.getKind(), actionNamed);
}

// Test with special characters in name
TEST_F(LinkNamedTest_300, ConstructWithSpecialCharacters_300) {
    Object nameObj = Object(new GooString("Go-Back_123!@#"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_EQ(linkNamed.getName(), "Go-Back_123!@#");
}

// Test with SaveAs named action
TEST_F(LinkNamedTest_300, ConstructWithSaveAs_300) {
    Object nameObj = Object(new GooString("SaveAs"));
    LinkNamed linkNamed(&nameObj);
    EXPECT_TRUE(linkNamed.isOk());
    EXPECT_EQ(linkNamed.getName(), "SaveAs");
}
