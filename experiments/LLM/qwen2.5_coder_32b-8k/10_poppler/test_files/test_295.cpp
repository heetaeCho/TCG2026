#include <gtest/gtest.h>

#include "Link.h"

#include <optional>



class LinkURITest_295 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be used to initialize objects if necessary

    }



    void TearDown() override {

        // Teardown can be used to clean up after tests if necessary

    }

};



TEST_F(LinkURITest_295, IsOk_ReturnsTrueWhenURIFlagIsSet_295) {

    Object dummyObject; // Assuming Object is a valid class in your codebase

    LinkURI linkURI(&dummyObject, std::optional<std::string>("http://example.com"));

    EXPECT_TRUE(linkURI.isOk());

}



TEST_F(LinkURITest_295, IsOk_ReturnsFalseWhenURIFlagIsNotSet_295) {

    Object dummyObject; // Assuming Object is a valid class in your codebase

    LinkURI linkURI(&dummyObject, std::optional<std::string>());

    EXPECT_FALSE(linkURI.isOk());

}



TEST_F(LinkURITest_295, GetKind_ReturnsCorrectLinkActionKind_295) {

    Object dummyObject; // Assuming Object is a valid class in your codebase

    LinkURI linkURI(&dummyObject, std::optional<std::string>("http://example.com"));

    EXPECT_EQ(linkURI.getKind(), LinkActionKind::Uri); // Assuming Uri is the correct kind for URI links

}



TEST_F(LinkURITest_295, GetURI_ReturnsCorrectURI_295) {

    Object dummyObject; // Assuming Object is a valid class in your codebase

    std::string testURI = "http://example.com";

    LinkURI linkURI(&dummyObject, std::optional<std::string>(testURI));

    EXPECT_EQ(linkURI.getURI(), testURI);

}



TEST_F(LinkURITest_295, GetURI_ReturnsEmptyStringWhenNoURIProvided_295) {

    Object dummyObject; // Assuming Object is a valid class in your codebase

    LinkURI linkURI(&dummyObject, std::optional<std::string>());

    EXPECT_EQ(linkURI.getURI(), "");

}



TEST_F(LinkURITest_295, ConstructorWithBaseURIString_HandlesValidURI_295) {

    Object dummyObject; // Assuming Object is a valid class in your codebase

    LinkURI linkURI(&dummyObject, std::optional<std::string>("http://example.com"), "http://base.com");

    EXPECT_TRUE(linkURI.isOk());

}



TEST_F(LinkURITest_295, ConstructorWithBaseURIInt_HandlesValidURI_295) {

    Object dummyObject; // Assuming Object is a valid class in your codebase

    LinkURI linkURI(&dummyObject, std::optional<std::string>("http://example.com"), 80);

    EXPECT_TRUE(linkURI.isOk());

}

```


