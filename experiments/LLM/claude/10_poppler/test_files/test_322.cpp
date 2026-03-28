#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"
#include "PDFDoc.h"

class LinkJavaScriptTest_322 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that LinkJavaScript constructed with a valid JavaScript string Object is ok
TEST_F(LinkJavaScriptTest_322, ConstructWithValidJSObject_IsOk_322) {
    Object jsObj = Object(new GooString("alert('hello');"));
    LinkJavaScript link(&jsObj);
    EXPECT_TRUE(link.isOk());
}

// Test that LinkJavaScript constructed with a null/invalid Object is not ok
TEST_F(LinkJavaScriptTest_322, ConstructWithNullObject_IsNotOk_322) {
    Object nullObj;
    LinkJavaScript link(&nullObj);
    EXPECT_FALSE(link.isOk());
}

// Test that getKind returns actionJavaScript
TEST_F(LinkJavaScriptTest_322, GetKind_ReturnsJavaScript_322) {
    Object jsObj = Object(new GooString("var x = 1;"));
    LinkJavaScript link(&jsObj);
    EXPECT_EQ(link.getKind(), actionJavaScript);
}

// Test that getScript returns the correct JavaScript string
TEST_F(LinkJavaScriptTest_322, GetScript_ReturnsCorrectScript_322) {
    const char *scriptText = "app.alert('test');";
    Object jsObj = Object(new GooString(scriptText));
    LinkJavaScript link(&jsObj);
    if (link.isOk()) {
        const std::string &script = link.getScript();
        EXPECT_EQ(script, scriptText);
    }
}

// Test that LinkJavaScript with empty string object
TEST_F(LinkJavaScriptTest_322, ConstructWithEmptyStringObject_322) {
    Object jsObj = Object(new GooString(""));
    LinkJavaScript link(&jsObj);
    // Even empty string might be considered valid JS
    if (link.isOk()) {
        const std::string &script = link.getScript();
        EXPECT_EQ(script, "");
    }
}

// Test that constructing with non-string object type results in not ok
TEST_F(LinkJavaScriptTest_322, ConstructWithIntObject_IsNotOk_322) {
    Object intObj = Object(42);
    LinkJavaScript link(&intObj);
    EXPECT_FALSE(link.isOk());
}

// Test that constructing with a dict object results in not ok
TEST_F(LinkJavaScriptTest_322, ConstructWithDictObject_IsNotOk_322) {
    Object dictObj = Object(new Dict(nullptr));
    LinkJavaScript link(&dictObj);
    EXPECT_FALSE(link.isOk());
}

// Test createObject static method
TEST_F(LinkJavaScriptTest_322, CreateObject_ReturnsValidObject_322) {
    std::string jsCode = "print('hello');";
    Object obj = LinkJavaScript::createObject(nullptr, jsCode);
    // The created object should be a dictionary containing JS action
    EXPECT_TRUE(obj.isDict());
}

// Test that a long JavaScript string is handled correctly
TEST_F(LinkJavaScriptTest_322, ConstructWithLongScript_322) {
    std::string longScript(10000, 'x');
    Object jsObj = Object(new GooString(longScript.c_str()));
    LinkJavaScript link(&jsObj);
    if (link.isOk()) {
        const std::string &script = link.getScript();
        EXPECT_EQ(script.length(), 10000u);
    }
}

// Test that script with special characters works
TEST_F(LinkJavaScriptTest_322, ConstructWithSpecialCharsScript_322) {
    const char *specialScript = "var s = \"hello\\nworld\"; // comment\n/* block */";
    Object jsObj = Object(new GooString(specialScript));
    LinkJavaScript link(&jsObj);
    if (link.isOk()) {
        const std::string &script = link.getScript();
        EXPECT_EQ(script, specialScript);
    }
}

// Test boolean object results in not ok
TEST_F(LinkJavaScriptTest_322, ConstructWithBoolObject_IsNotOk_322) {
    Object boolObj = Object(true);
    LinkJavaScript link(&boolObj);
    EXPECT_FALSE(link.isOk());
}
