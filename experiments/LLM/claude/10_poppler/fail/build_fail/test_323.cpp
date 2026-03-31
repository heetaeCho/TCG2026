#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/Link.h"
#include "poppler/Object.h"

class LinkJavaScriptTest_323 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getKind returns actionJavaScript
TEST_F(LinkJavaScriptTest_323, GetKindReturnsActionJavaScript_323) {
    // Create a JavaScript string object
    Object jsObj(new GooString("alert('hello');"));
    LinkJavaScript link(&jsObj);
    EXPECT_EQ(link.getKind(), actionJavaScript);
}

// Test that a valid JavaScript object creates a valid LinkJavaScript
TEST_F(LinkJavaScriptTest_323, ValidJsObjectIsOk_323) {
    Object jsObj(new GooString("var x = 1;"));
    LinkJavaScript link(&jsObj);
    EXPECT_TRUE(link.isOk());
}

// Test that getScript returns the correct script string
TEST_F(LinkJavaScriptTest_323, GetScriptReturnsCorrectScript_323) {
    const char *scriptText = "alert('test');";
    Object jsObj(new GooString(scriptText));
    LinkJavaScript link(&jsObj);
    if (link.isOk()) {
        EXPECT_EQ(link.getScript(), std::string(scriptText));
    }
}

// Test with a null/none object
TEST_F(LinkJavaScriptTest_323, NullObjectIsNotOk_323) {
    Object nullObj;
    LinkJavaScript link(&nullObj);
    EXPECT_FALSE(link.isOk());
}

// Test with an empty string
TEST_F(LinkJavaScriptTest_323, EmptyStringScript_323) {
    Object jsObj(new GooString(""));
    LinkJavaScript link(&jsObj);
    // Even an empty string is technically a valid string object
    if (link.isOk()) {
        EXPECT_EQ(link.getScript(), std::string(""));
    }
}

// Test getKind even when object is invalid
TEST_F(LinkJavaScriptTest_323, GetKindAlwaysReturnsJavaScript_323) {
    Object nullObj;
    LinkJavaScript link(&nullObj);
    // getKind should always return actionJavaScript regardless of validity
    EXPECT_EQ(link.getKind(), actionJavaScript);
}

// Test with a non-string object (e.g., integer)
TEST_F(LinkJavaScriptTest_323, NonStringObjectIsNotOk_323) {
    Object intObj(42);
    LinkJavaScript link(&intObj);
    EXPECT_FALSE(link.isOk());
}

// Test with a longer script
TEST_F(LinkJavaScriptTest_323, LongScriptString_323) {
    std::string longScript(10000, 'x');
    Object jsObj(new GooString(longScript.c_str()));
    LinkJavaScript link(&jsObj);
    if (link.isOk()) {
        EXPECT_EQ(link.getScript(), longScript);
    }
}

// Test with special characters in script
TEST_F(LinkJavaScriptTest_323, SpecialCharactersInScript_323) {
    const char *scriptText = "var x = \"hello\\nworld\"; // comment\t\r\n";
    Object jsObj(new GooString(scriptText));
    LinkJavaScript link(&jsObj);
    if (link.isOk()) {
        EXPECT_EQ(link.getScript(), std::string(scriptText));
    }
}

// Test createObject static method
TEST_F(LinkJavaScriptTest_323, CreateObjectStaticMethod_323) {
    std::string js = "alert('created');";
    Object obj = LinkJavaScript::createObject(nullptr, js);
    // The created object should be usable to construct a LinkJavaScript
    // We verify it's a valid object (not null/none type that would fail)
    // This tests the static factory method
    EXPECT_TRUE(obj.isDict() || obj.isString() || obj.isStream() || obj.isName() || obj.isArray());
}

// Test that actionJavaScript has expected enum value
TEST_F(LinkJavaScriptTest_323, ActionJavaScriptEnumValue_323) {
    EXPECT_EQ(actionJavaScript, 8);
}

// Test with unicode-like content
TEST_F(LinkJavaScriptTest_323, UnicodeContentScript_323) {
    const char *scriptText = "var \xC3\xA9 = 'caf\xC3\xA9';";
    Object jsObj(new GooString(scriptText));
    LinkJavaScript link(&jsObj);
    if (link.isOk()) {
        EXPECT_FALSE(link.getScript().empty());
    }
}
