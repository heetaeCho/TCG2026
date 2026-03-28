#include <gtest/gtest.h>
#include "Link.h"
#include "Object.h"

class LinkHideTest_331 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that LinkHide constructed with a dictionary containing a "T" string entry
// reports hasTargetName() as true
TEST_F(LinkHideTest_331, HasTargetNameReturnsTrueWhenTargetNamePresent_331) {
    // Create an Object that represents a dictionary with a "T" (target name) entry
    Object dictObj;
    dictObj = Object(new Dict(nullptr));
    Object tVal = Object(new GooString("fieldName"));
    dictObj.dictSet("T", std::move(tVal));
    // Also set "H" for hide/show flag
    Object hVal = Object(true);
    dictObj.dictSet("H", std::move(hVal));

    LinkHide linkHide(&dictObj);
    EXPECT_TRUE(linkHide.hasTargetName());
}

// Test that LinkHide constructed with a simple string object
// reports hasTargetName() as true (string is the target name)
TEST_F(LinkHideTest_331, HasTargetNameWithStringObject_331) {
    Object strObj = Object(new GooString("someField"));
    LinkHide linkHide(&strObj);
    EXPECT_TRUE(linkHide.hasTargetName());
}

// Test that LinkHide returns the correct kind
TEST_F(LinkHideTest_331, GetKindReturnsHide_331) {
    Object strObj = Object(new GooString("testField"));
    LinkHide linkHide(&strObj);
    EXPECT_EQ(linkHide.getKind(), actionHide);
}

// Test that getTargetName returns the expected string
TEST_F(LinkHideTest_331, GetTargetNameReturnsCorrectValue_331) {
    Object strObj = Object(new GooString("myFieldName"));
    LinkHide linkHide(&strObj);
    if (linkHide.hasTargetName()) {
        EXPECT_EQ(linkHide.getTargetName(), "myFieldName");
    }
}

// Test isShowAction with dictionary where H is false (show action)
TEST_F(LinkHideTest_331, IsShowActionWhenHIsFalse_331) {
    Object dictObj;
    dictObj = Object(new Dict(nullptr));
    Object tVal = Object(new GooString("field1"));
    dictObj.dictSet("T", std::move(tVal));
    Object hVal = Object(false);
    dictObj.dictSet("H", std::move(hVal));

    LinkHide linkHide(&dictObj);
    EXPECT_TRUE(linkHide.isShowAction());
}

// Test isShowAction with dictionary where H is true (hide action, not show)
TEST_F(LinkHideTest_331, IsNotShowActionWhenHIsTrue_331) {
    Object dictObj;
    dictObj = Object(new Dict(nullptr));
    Object tVal = Object(new GooString("field2"));
    dictObj.dictSet("T", std::move(tVal));
    Object hVal = Object(true);
    dictObj.dictSet("H", std::move(hVal));

    LinkHide linkHide(&dictObj);
    EXPECT_FALSE(linkHide.isShowAction());
}

// Test with null-like object (no target name)
TEST_F(LinkHideTest_331, HasTargetNameReturnsFalseForNullObject_331) {
    Object nullObj;
    nullObj = Object(objNull);
    LinkHide linkHide(&nullObj);
    EXPECT_FALSE(linkHide.hasTargetName());
}

// Test hasTargetName consistency - calling it multiple times should return same result
TEST_F(LinkHideTest_331, HasTargetNameIsConsistent_331) {
    Object strObj = Object(new GooString("consistentField"));
    LinkHide linkHide(&strObj);
    bool first = linkHide.hasTargetName();
    bool second = linkHide.hasTargetName();
    EXPECT_EQ(first, second);
}

// Test with an array object (array of field names)
TEST_F(LinkHideTest_331, HasTargetNameFalseForArrayObject_331) {
    Object arrObj = Object(new Array(nullptr));
    Object elem = Object(new GooString("field1"));
    arrObj.arrayAdd(std::move(elem));

    LinkHide linkHide(&arrObj);
    // Array-based hide actions don't have a single target name
    EXPECT_FALSE(linkHide.hasTargetName());
}

// Test isOk method
TEST_F(LinkHideTest_331, IsOkForValidObject_331) {
    Object strObj = Object(new GooString("validField"));
    LinkHide linkHide(&strObj);
    // A valid string target should produce an ok LinkHide
    EXPECT_TRUE(linkHide.isOk());
}
