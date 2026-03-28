#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <cstring>

// Include necessary headers
#include "poppler-action.h"
#include "Link.h"
#include "GooString.h"

// We need to mock LinkJavaScript since it's an external dependency
// However, LinkJavaScript has virtual methods we can leverage

// Since build_javascript is a static function in the .cc file, we need to
// understand how to access it. It's likely called internally by poppler.
// For testing purposes, we'll need to either:
// 1. Test through the public API that calls build_javascript
// 2. Or if it's accessible, call it directly

// Since build_javascript is static (file-local), we can't call it directly.
// We need to test through the public interface that invokes it.
// The typical entry point is poppler_action_copy or the action construction.

// However, given the constraints, let's test what we can observe through
// the poppler GLib API.

// For the purpose of this test, we'll assume we can test through
// poppler_action_new / poppler_action_copy or similar public APIs.
// If build_javascript is exposed indirectly, we test that path.

// Since we're dealing with GLib-based poppler, the typical way to create
// a PopplerAction with JavaScript is through document link processing.

// Let's create a minimal test fixture that tests the observable behavior
// of JavaScript actions in PopplerAction.

extern "C" {
#include <glib.h>
}

// Forward declare the internal function if it's accessible for testing
// In practice, build_javascript is static, but we can test through
// the public poppler_action API

class BuildJavascriptTest_2298 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a PopplerAction with javascript type has the script field set
// when created from a valid LinkJavaScript
TEST_F(BuildJavascriptTest_2298, ValidJavascriptLinkSetsScript_2298)
{
    // Create a JavaScript Object for LinkJavaScript
    // We need a valid JS object - typically a string object
    Object jsObj;
    std::string jsCode = "app.alert('Hello');";
    jsObj = Object(new GooString(jsCode));

    LinkJavaScript link(&jsObj);

    // Verify the link is valid
    EXPECT_TRUE(link.isOk());
    EXPECT_EQ(link.getScript(), jsCode);
}

// Test LinkJavaScript with empty script
TEST_F(BuildJavascriptTest_2298, EmptyScriptLinkJavaScript_2298)
{
    Object jsObj;
    std::string jsCode = "";
    jsObj = Object(new GooString(jsCode));

    LinkJavaScript link(&jsObj);

    // Check if empty script is considered ok
    if (link.isOk()) {
        EXPECT_EQ(link.getScript(), "");
    }
}

// Test LinkJavaScript getScript returns the correct string
TEST_F(BuildJavascriptTest_2298, GetScriptReturnsCorrectString_2298)
{
    std::string jsCode = "this.print();";
    Object jsObj;
    jsObj = Object(new GooString(jsCode));

    LinkJavaScript link(&jsObj);

    if (link.isOk()) {
        EXPECT_EQ(link.getScript(), jsCode);
    }
}

// Test with unicode content in JavaScript
TEST_F(BuildJavascriptTest_2298, UnicodeScriptContent_2298)
{
    std::string jsCode = "var x = '\xC3\xA9\xC3\xA0\xC3\xBC';"; // UTF-8 encoded
    Object jsObj;
    jsObj = Object(new GooString(jsCode));

    LinkJavaScript link(&jsObj);

    if (link.isOk()) {
        EXPECT_EQ(link.getScript(), jsCode);
    }
}

// Test with a long JavaScript string
TEST_F(BuildJavascriptTest_2298, LongScriptContent_2298)
{
    std::string jsCode(10000, 'a'); // Very long script
    Object jsObj;
    jsObj = Object(new GooString(jsCode));

    LinkJavaScript link(&jsObj);

    if (link.isOk()) {
        EXPECT_EQ(link.getScript().length(), 10000u);
        EXPECT_EQ(link.getScript(), jsCode);
    }
}

// Test with special characters in JavaScript
TEST_F(BuildJavascriptTest_2298, SpecialCharactersInScript_2298)
{
    std::string jsCode = "var x = \"hello\\nworld\\t!\";";
    Object jsObj;
    jsObj = Object(new GooString(jsCode));

    LinkJavaScript link(&jsObj);

    if (link.isOk()) {
        EXPECT_EQ(link.getScript(), jsCode);
    }
}

// Test GooString to UTF8 conversion helper with basic ASCII
TEST_F(BuildJavascriptTest_2298, GooStringBasicASCII_2298)
{
    GooString str("Hello World");
    EXPECT_EQ(str.toStr(), "Hello World");
}

// Test GooString construction with length
TEST_F(BuildJavascriptTest_2298, GooStringWithLength_2298)
{
    GooString str("Hello World", 5);
    EXPECT_EQ(str.toStr(), "Hello");
}

// Test GooString with null pointer
TEST_F(BuildJavascriptTest_2298, GooStringNullPtr_2298)
{
    const char *nullStr = nullptr;
    GooString str(nullStr);
    EXPECT_EQ(str.toStr(), "");
}

// Test PopplerAction javascript field initialization
TEST_F(BuildJavascriptTest_2298, PopplerActionJavascriptFieldExists_2298)
{
    PopplerAction action;
    memset(&action, 0, sizeof(PopplerAction));

    // The javascript member should be accessible
    action.javascript.script = nullptr;
    EXPECT_EQ(action.javascript.script, nullptr);
}

// Test that LinkJavaScript getKind returns correct kind
TEST_F(BuildJavascriptTest_2298, LinkJavaScriptKind_2298)
{
    std::string jsCode = "app.alert('test');";
    Object jsObj;
    jsObj = Object(new GooString(jsCode));

    LinkJavaScript link(&jsObj);

    if (link.isOk()) {
        EXPECT_EQ(link.getKind(), actionJavaScript);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
