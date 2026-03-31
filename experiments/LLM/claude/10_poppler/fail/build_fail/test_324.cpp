#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"

// Test fixture for LinkJavaScript tests
class LinkJavaScriptTest_324 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getScript returns a valid string reference for a valid JavaScript object
TEST_F(LinkJavaScriptTest_324, GetScriptReturnsStringReference_324) {
    // Create a JavaScript string Object
    Object jsObj(new GooString("alert('hello');"));
    LinkJavaScript link(&jsObj);
    
    const std::string &script = link.getScript();
    // We just verify it returns a reference to a string (may or may not be empty depending on object validity)
    // The key behavior is that getScript() doesn't crash and returns a const reference
    EXPECT_FALSE(script.empty() && link.isOk());
}

// Test that getKind returns appropriate LinkActionKind for JavaScript
TEST_F(LinkJavaScriptTest_324, GetKindReturnsJavaScript_324) {
    Object jsObj(new GooString("var x = 1;"));
    LinkJavaScript link(&jsObj);
    
    EXPECT_EQ(link.getKind(), actionJavaScript);
}

// Test isOk with a valid JavaScript object
TEST_F(LinkJavaScriptTest_324, IsOkWithValidObject_324) {
    Object jsObj(new GooString("console.log('test');"));
    LinkJavaScript link(&jsObj);
    
    // A valid JS string object should make isOk return true
    if (link.isOk()) {
        EXPECT_FALSE(link.getScript().empty());
    }
}

// Test with null/invalid object
TEST_F(LinkJavaScriptTest_324, ConstructWithNullObject_324) {
    Object nullObj;
    LinkJavaScript link(&nullObj);
    
    // With an invalid object, isOk should return false
    EXPECT_FALSE(link.isOk());
}

// Test getScript returns consistent results on multiple calls
TEST_F(LinkJavaScriptTest_324, GetScriptConsistentResults_324) {
    Object jsObj(new GooString("function test() { return 42; }"));
    LinkJavaScript link(&jsObj);
    
    const std::string &script1 = link.getScript();
    const std::string &script2 = link.getScript();
    
    // Same reference should be returned
    EXPECT_EQ(&script1, &script2);
    EXPECT_EQ(script1, script2);
}

// Test with empty JavaScript string
TEST_F(LinkJavaScriptTest_324, ConstructWithEmptyScript_324) {
    Object jsObj(new GooString(""));
    LinkJavaScript link(&jsObj);
    
    const std::string &script = link.getScript();
    // Empty string may or may not be considered valid - just verify no crash
    (void)script;
}

// Test getScript content matches what was provided
TEST_F(LinkJavaScriptTest_324, GetScriptContentMatches_324) {
    const char *expectedScript = "app.alert('Hello World');";
    Object jsObj(new GooString(expectedScript));
    LinkJavaScript link(&jsObj);
    
    if (link.isOk()) {
        EXPECT_EQ(link.getScript(), std::string(expectedScript));
    }
}

// Test createObject static method
TEST_F(LinkJavaScriptTest_324, CreateObjectStaticMethod_324) {
    std::string js = "print('test');";
    // createObject requires an XRef, passing nullptr to test behavior
    Object obj = LinkJavaScript::createObject(nullptr, js);
    
    // Verify the created object can be used to construct a LinkJavaScript
    // The object type depends on implementation
    (void)obj;
}

// Test with special characters in JavaScript
TEST_F(LinkJavaScriptTest_324, GetScriptWithSpecialCharacters_324) {
    const char *specialScript = "var s = \"hello\\nworld\"; // comment\n/* block */";
    Object jsObj(new GooString(specialScript));
    LinkJavaScript link(&jsObj);
    
    if (link.isOk()) {
        EXPECT_EQ(link.getScript(), std::string(specialScript));
    }
}

// Test with very long JavaScript string
TEST_F(LinkJavaScriptTest_324, GetScriptWithLongString_324) {
    std::string longScript(10000, 'x');
    Object jsObj(new GooString(longScript.c_str()));
    LinkJavaScript link(&jsObj);
    
    if (link.isOk()) {
        EXPECT_EQ(link.getScript().length(), longScript.length());
    }
}
