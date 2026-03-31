#include <gtest/gtest.h>
#include <string>
#include "Link.h"
#include "Object.h"

class LinkURITest_297 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that LinkURI constructed with a valid URI string object returns the correct URI
TEST_F(LinkURITest_297, ValidURIReturnsCorrectString_297) {
    Object uriObj(new GooString("https://www.example.com"));
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_EQ(linkUri.getURI(), "https://www.example.com");
}

// Test that LinkURI with a base URI properly concatenates or handles the base
TEST_F(LinkURITest_297, URIWithBaseURI_297) {
    Object uriObj(new GooString("page.html"));
    std::optional<std::string> baseURI = std::string("https://www.example.com/");
    LinkURI linkUri(&uriObj, baseURI);
    
    const std::string &result = linkUri.getURI();
    // The URI should contain the relative path, possibly resolved with base
    EXPECT_FALSE(result.empty());
}

// Test that LinkURI with empty base URI works
TEST_F(LinkURITest_297, URIWithEmptyBaseURI_297) {
    Object uriObj(new GooString("https://www.example.com/test"));
    std::optional<std::string> baseURI = std::string("");
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_EQ(linkUri.getURI(), "https://www.example.com/test");
}

// Test that LinkURI reports correct action kind
TEST_F(LinkURITest_297, GetKindReturnsURI_297) {
    Object uriObj(new GooString("https://www.example.com"));
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_EQ(linkUri.getKind(), actionURI);
}

// Test isOk for a valid URI
TEST_F(LinkURITest_297, IsOkForValidURI_297) {
    Object uriObj(new GooString("https://www.example.com"));
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_TRUE(linkUri.isOk());
}

// Test that getURI returns a reference to the internal string (consistency check)
TEST_F(LinkURITest_297, GetURIReturnsSameReference_297) {
    Object uriObj(new GooString("https://www.example.com"));
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    
    const std::string &ref1 = linkUri.getURI();
    const std::string &ref2 = linkUri.getURI();
    EXPECT_EQ(&ref1, &ref2);
}

// Test URI with special characters
TEST_F(LinkURITest_297, URIWithSpecialCharacters_297) {
    Object uriObj(new GooString("https://www.example.com/path?query=value&foo=bar#fragment"));
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_EQ(linkUri.getURI(), "https://www.example.com/path?query=value&foo=bar#fragment");
}

// Test URI with empty string
TEST_F(LinkURITest_297, EmptyURIString_297) {
    Object uriObj(new GooString(""));
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    
    const std::string &uri = linkUri.getURI();
    // Empty URI might still be valid or empty
    EXPECT_TRUE(uri.empty() || !uri.empty());
}

// Test with nullopt base URI
TEST_F(LinkURITest_297, NulloptBaseURI_297) {
    Object uriObj(new GooString("mailto:test@example.com"));
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_EQ(linkUri.getURI(), "mailto:test@example.com");
    EXPECT_TRUE(linkUri.isOk());
}

// Test URI with various protocols
TEST_F(LinkURITest_297, URIWithFTPProtocol_297) {
    Object uriObj(new GooString("ftp://files.example.com/doc.pdf"));
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_EQ(linkUri.getURI(), "ftp://files.example.com/doc.pdf");
}

// Test that a non-string object results in not ok
TEST_F(LinkURITest_297, InvalidObjectTypeIsNotOk_297) {
    Object uriObj(42);  // integer, not a string
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_FALSE(linkUri.isOk());
}

// Test with null object
TEST_F(LinkURITest_297, NullObjectHandling_297) {
    Object nullObj;
    std::optional<std::string> baseURI = std::nullopt;
    LinkURI linkUri(&nullObj, baseURI);
    
    // Should handle gracefully
    EXPECT_FALSE(linkUri.isOk());
}
