#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"
#include <string>
#include <optional>

class LinkURITest_296 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getKind() returns actionURI
TEST_F(LinkURITest_296, GetKindReturnsActionURI_296) {
    // Create a string object for the URI
    Object uriObj(new GooString("http://www.example.com"));
    std::optional<std::string> baseURI = std::nullopt;
    
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_EQ(linkUri.getKind(), actionURI);
}

// Test with a valid URI string and no base URI
TEST_F(LinkURITest_296, ValidURIWithNoBaseURI_296) {
    Object uriObj(new GooString("http://www.example.com"));
    std::optional<std::string> baseURI = std::nullopt;
    
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_TRUE(linkUri.isOk());
    EXPECT_EQ(linkUri.getURI(), "http://www.example.com");
}

// Test with a valid URI string and a base URI
TEST_F(LinkURITest_296, ValidURIWithBaseURI_296) {
    Object uriObj(new GooString("page.html"));
    std::optional<std::string> baseURI = std::string("http://www.example.com/");
    
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_TRUE(linkUri.isOk());
    // The URI should be combined with base URI
    const std::string &uri = linkUri.getURI();
    EXPECT_FALSE(uri.empty());
}

// Test with a full absolute URI and a base URI (absolute should take precedence)
TEST_F(LinkURITest_296, AbsoluteURIWithBaseURI_296) {
    Object uriObj(new GooString("http://www.other.com/page.html"));
    std::optional<std::string> baseURI = std::string("http://www.example.com/");
    
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_TRUE(linkUri.isOk());
    const std::string &uri = linkUri.getURI();
    EXPECT_FALSE(uri.empty());
}

// Test with empty URI string
TEST_F(LinkURITest_296, EmptyURIString_296) {
    Object uriObj(new GooString(""));
    std::optional<std::string> baseURI = std::nullopt;
    
    LinkURI linkUri(&uriObj, baseURI);
    
    // Even with empty string, check behavior
    LinkActionKind kind = linkUri.getKind();
    EXPECT_EQ(kind, actionURI);
}

// Test with null/non-string object
TEST_F(LinkURITest_296, NullObject_296) {
    Object uriObj;  // null object
    std::optional<std::string> baseURI = std::nullopt;
    
    LinkURI linkUri(&uriObj, baseURI);
    
    // Should not be ok with invalid object
    EXPECT_FALSE(linkUri.isOk());
    EXPECT_EQ(linkUri.getKind(), actionURI);
}

// Test with an empty base URI
TEST_F(LinkURITest_296, EmptyBaseURI_296) {
    Object uriObj(new GooString("http://www.example.com/test"));
    std::optional<std::string> baseURI = std::string("");
    
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_TRUE(linkUri.isOk());
    EXPECT_EQ(linkUri.getURI(), "http://www.example.com/test");
}

// Test with special characters in URI
TEST_F(LinkURITest_296, SpecialCharactersInURI_296) {
    Object uriObj(new GooString("http://www.example.com/path?query=value&foo=bar#fragment"));
    std::optional<std::string> baseURI = std::nullopt;
    
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_TRUE(linkUri.isOk());
    EXPECT_EQ(linkUri.getURI(), "http://www.example.com/path?query=value&foo=bar#fragment");
}

// Test with mailto URI scheme
TEST_F(LinkURITest_296, MailtoURI_296) {
    Object uriObj(new GooString("mailto:test@example.com"));
    std::optional<std::string> baseURI = std::nullopt;
    
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_TRUE(linkUri.isOk());
    EXPECT_EQ(linkUri.getURI(), "mailto:test@example.com");
    EXPECT_EQ(linkUri.getKind(), actionURI);
}

// Test with very long URI
TEST_F(LinkURITest_296, VeryLongURI_296) {
    std::string longUri = "http://www.example.com/";
    for (int i = 0; i < 1000; i++) {
        longUri += "segment/";
    }
    Object uriObj(new GooString(longUri));
    std::optional<std::string> baseURI = std::nullopt;
    
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_TRUE(linkUri.isOk());
    EXPECT_EQ(linkUri.getURI(), longUri);
}

// Test with integer constructor for baseURI
TEST_F(LinkURITest_296, IntegerBaseURIConstructor_296) {
    Object uriObj(new GooString("http://www.example.com"));
    int baseURI = 0;
    
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_EQ(linkUri.getKind(), actionURI);
    EXPECT_TRUE(linkUri.isOk());
}

// Test getKind is consistent across multiple calls
TEST_F(LinkURITest_296, GetKindConsistency_296) {
    Object uriObj(new GooString("http://www.example.com"));
    std::optional<std::string> baseURI = std::nullopt;
    
    LinkURI linkUri(&uriObj, baseURI);
    
    EXPECT_EQ(linkUri.getKind(), actionURI);
    EXPECT_EQ(linkUri.getKind(), actionURI);
    EXPECT_EQ(linkUri.getKind(), actionURI);
}

// Test getURI returns consistent results
TEST_F(LinkURITest_296, GetURIConsistency_296) {
    Object uriObj(new GooString("http://www.example.com/test"));
    std::optional<std::string> baseURI = std::nullopt;
    
    LinkURI linkUri(&uriObj, baseURI);
    
    const std::string &uri1 = linkUri.getURI();
    const std::string &uri2 = linkUri.getURI();
    EXPECT_EQ(uri1, uri2);
}
