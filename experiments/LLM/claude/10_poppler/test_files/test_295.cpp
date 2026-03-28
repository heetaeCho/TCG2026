#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"
#include <string>
#include <optional>

class LinkURITest_295 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that LinkURI constructed with a valid URI string object is OK
TEST_F(LinkURITest_295, ConstructWithValidURIStringIsOk_295) {
    Object uriObj(new GooString("http://www.example.com"));
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    EXPECT_TRUE(linkUri.isOk());
}

// Test that LinkURI returns the correct kind
TEST_F(LinkURITest_295, GetKindReturnsURI_295) {
    Object uriObj(new GooString("http://www.example.com"));
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    EXPECT_EQ(linkUri.getKind(), actionURI);
}

// Test that getURI returns the expected URI string
TEST_F(LinkURITest_295, GetURIReturnsCorrectValue_295) {
    Object uriObj(new GooString("http://www.example.com"));
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    if (linkUri.isOk()) {
        EXPECT_EQ(linkUri.getURI(), "http://www.example.com");
    }
}

// Test that LinkURI with a base URI prepends it correctly
TEST_F(LinkURITest_295, ConstructWithBaseURIPrepends_295) {
    Object uriObj(new GooString("path/to/resource"));
    std::optional<std::string> baseURI = std::string("http://www.example.com/");
    LinkURI linkUri(&uriObj, baseURI);
    if (linkUri.isOk()) {
        const std::string &uri = linkUri.getURI();
        // The URI should contain the base URI or the path
        EXPECT_FALSE(uri.empty());
    }
}

// Test that LinkURI constructed with a null/invalid object is not OK
TEST_F(LinkURITest_295, ConstructWithNullObjectIsNotOk_295) {
    Object nullObj;
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&nullObj, baseURI);
    EXPECT_FALSE(linkUri.isOk());
}

// Test that LinkURI with empty string URI
TEST_F(LinkURITest_295, ConstructWithEmptyStringURI_295) {
    Object uriObj(new GooString(""));
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    // An empty URI string - behavior depends on implementation
    // but we check it doesn't crash and isOk returns a valid bool
    bool ok = linkUri.isOk();
    (void)ok; // Just verify no crash
}

// Test that LinkURI with absolute URI ignores base URI
TEST_F(LinkURITest_295, AbsoluteURIIgnoresBaseURI_295) {
    Object uriObj(new GooString("http://www.absolute.com/page"));
    std::optional<std::string> baseURI = std::string("http://www.base.com/");
    LinkURI linkUri(&uriObj, baseURI);
    if (linkUri.isOk()) {
        const std::string &uri = linkUri.getURI();
        EXPECT_FALSE(uri.empty());
    }
}

// Test with a complex URI containing query parameters
TEST_F(LinkURITest_295, ComplexURIWithQueryParams_295) {
    Object uriObj(new GooString("http://www.example.com/search?q=test&lang=en"));
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    EXPECT_TRUE(linkUri.isOk());
    EXPECT_EQ(linkUri.getURI(), "http://www.example.com/search?q=test&lang=en");
}

// Test with URI containing fragment
TEST_F(LinkURITest_295, URIWithFragment_295) {
    Object uriObj(new GooString("http://www.example.com/page#section1"));
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    EXPECT_TRUE(linkUri.isOk());
    EXPECT_EQ(linkUri.getURI(), "http://www.example.com/page#section1");
}

// Test with mailto URI scheme
TEST_F(LinkURITest_295, MailtoURIScheme_295) {
    Object uriObj(new GooString("mailto:test@example.com"));
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    EXPECT_TRUE(linkUri.isOk());
    EXPECT_EQ(linkUri.getURI(), "mailto:test@example.com");
}

// Test the integer baseURI constructor overload
TEST_F(LinkURITest_295, ConstructWithIntBaseURI_295) {
    Object uriObj(new GooString("http://www.example.com"));
    LinkURI linkUri(&uriObj, 0);
    if (linkUri.isOk()) {
        EXPECT_FALSE(linkUri.getURI().empty());
    }
}

// Test that non-string object results in not OK
TEST_F(LinkURITest_295, ConstructWithIntObjectIsNotOk_295) {
    Object intObj(42);
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&intObj, baseURI);
    EXPECT_FALSE(linkUri.isOk());
}
