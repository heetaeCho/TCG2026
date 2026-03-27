#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Link.h"

#include <optional>



using namespace std;



class LinkURITest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup for tests, if needed

    }



    void TearDown() override {

        // Cleanup after tests, if needed

    }

};



TEST_F(LinkURITest_297, GetURI_ReturnsCorrectValue_297) {

    LinkURI linkUri(new Object(), "http://example.com");

    EXPECT_EQ(linkUri.getURI(), "http://example.com");

}



TEST_F(LinkURITest_297, IsOk_ReturnsTrueForValidURI_297) {

    LinkURI linkUri(new Object(), "http://example.com");

    EXPECT_TRUE(linkUri.isOk());

}



TEST_F(LinkURITest_297, GetKind_ReturnsCorrectLinkActionKind_297) {

    LinkURI linkUri(new Object(), "http://example.com");

    EXPECT_EQ(linkUri.getKind(), LinkActionKind::uri);

}



TEST_F(LinkURITest_297, BoundaryCondition_EmptyBaseURI_297) {

    LinkURI linkUri(new Object(), "");

    EXPECT_TRUE(linkUri.isOk());

    EXPECT_EQ(linkUri.getURI(), ""); // Assuming getURI returns an empty string if baseURI is empty

}



TEST_F(LinkURITest_297, BoundaryCondition_NullBaseURI_297) {

    LinkURI linkUri(nullptr, "http://example.com");

    EXPECT_TRUE(linkUri.isOk());

    EXPECT_EQ(linkUri.getURI(), ""); // Assuming getURI returns an empty string if uriObj is nullptr

}



TEST_F(LinkURITest_297, ExceptionalCase_InvalidURIObject_297) {

    LinkURI linkUri(new Object(), "invalid://uri");

    EXPECT_FALSE(linkUri.isOk());

}



TEST_F(LinkURITest_297, ExceptionalCase_EmptyURI_297) {

    LinkURI linkUri(new Object(), "");

    EXPECT_TRUE(linkUri.isOk()); // Assuming an empty URI is considered valid

    EXPECT_EQ(linkUri.getURI(), "");

}
