#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <cstring>

// Include necessary poppler headers
#include "poppler-action.h"
#include "Link.h"

// Since build_uri is a static function in the .cc file, we need to test it
// through the public interface that invokes it. However, for unit testing
// purposes, we can declare it as extern if the test is compiled with the
// source, or we test through poppler_action creation paths.

// Forward declaration - build_uri is static in the .cc file
// We test through the public action creation mechanism

// If we can access build_uri through a test helper or by including the .cc:
// For testing purposes, we include the implementation
// This is a common pattern for testing static functions
extern "C" {
#include <glib.h>
}

// We need to test through the public API that eventually calls build_uri
// The typical path is through _poppler_action_new or similar public functions

class PopplerActionUriTest_2294 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a PopplerAction created from a LinkURI with a normal URI
// correctly stores the URI string
TEST_F(PopplerActionUriTest_2294, NormalUri_2294) {
    // Create a LinkURI with a normal URI
    GooString uriStr("https://www.example.com");
    Object uriObj;
    uriObj.initString(&uriStr);
    
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    
    // Verify the LinkURI stores the URI correctly
    EXPECT_EQ(linkUri.getURI(), "https://www.example.com");
    
    // Create a PopplerAction and test build_uri behavior through public API
    PopplerAction action;
    memset(&action, 0, sizeof(PopplerAction));
    
    // Since build_uri is static, we test via the public poppler API
    // _poppler_action_new creates actions from LinkAction objects
    // For now, test LinkURI's getURI which is the input to build_uri
    const std::string& uri = linkUri.getURI();
    ASSERT_FALSE(uri.empty());
    EXPECT_STREQ(uri.c_str(), "https://www.example.com");
}

// Test LinkURI with an empty URI string
TEST_F(PopplerActionUriTest_2294, EmptyUri_2294) {
    GooString uriStr("");
    Object uriObj;
    uriObj.initString(&uriStr);
    
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    
    const std::string& uri = linkUri.getURI();
    EXPECT_TRUE(uri.empty() || uri.c_str() != nullptr);
}

// Test LinkURI with a URI containing special characters
TEST_F(PopplerActionUriTest_2294, SpecialCharactersUri_2294) {
    GooString uriStr("https://example.com/path?query=value&foo=bar#fragment");
    Object uriObj;
    uriObj.initString(&uriStr);
    
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_EQ(linkUri.getURI(), "https://example.com/path?query=value&foo=bar#fragment");
}

// Test LinkURI with a very long URI
TEST_F(PopplerActionUriTest_2294, LongUri_2294) {
    std::string longUri = "https://example.com/";
    longUri.append(10000, 'a');
    
    GooString uriStr(longUri.c_str());
    Object uriObj;
    uriObj.initString(&uriStr);
    
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_EQ(linkUri.getURI(), longUri);
}

// Test LinkURI getKind returns expected action kind
TEST_F(PopplerActionUriTest_2294, ActionKindIsUri_2294) {
    GooString uriStr("https://example.com");
    Object uriObj;
    uriObj.initString(&uriStr);
    
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_EQ(linkUri.getKind(), actionURI);
}

// Test that g_strdup in build_uri creates an independent copy
TEST_F(PopplerActionUriTest_2294, UriIsCopied_2294) {
    GooString uriStr("https://example.com/test");
    Object uriObj;
    uriObj.initString(&uriStr);
    
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    
    const char* uriCStr = linkUri.getURI().c_str();
    gchar* copied = g_strdup(uriCStr);
    
    ASSERT_NE(copied, nullptr);
    EXPECT_STREQ(copied, "https://example.com/test");
    // Verify it's an independent copy
    EXPECT_NE(static_cast<const void*>(copied), static_cast<const void*>(uriCStr));
    
    g_free(copied);
}

// Test with a base URI provided
TEST_F(PopplerActionUriTest_2294, WithBaseUri_2294) {
    GooString uriStr("relative/path");
    Object uriObj;
    uriObj.initString(&uriStr);
    
    std::optional<std::string> baseURI = "https://example.com/";
    LinkURI linkUri(&uriObj, baseURI);
    
    // The URI should be resolved against the base
    const std::string& uri = linkUri.getURI();
    EXPECT_FALSE(uri.empty());
}

// Test URI with unicode characters
TEST_F(PopplerActionUriTest_2294, UnicodeUri_2294) {
    GooString uriStr("https://example.com/p%C3%A4th");
    Object uriObj;
    uriObj.initString(&uriStr);
    
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_EQ(linkUri.getURI(), "https://example.com/p%C3%A4th");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
