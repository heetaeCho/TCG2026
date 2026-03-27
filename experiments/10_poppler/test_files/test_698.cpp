#include <gtest/gtest.h>

#include "Page.h"



class PageAttrsTest_698 : public ::testing::Test {

protected:

    Dict* dict;

    Object resources;



    void SetUp() override {

        dict = new Dict();

        resources = Object(new Dict());

        dict->dictAdd("Resources", std::move(resources));

    }



    void TearDown() override {

        delete dict;

    }

};



TEST_F(PageAttrsTest_698, GetResourceDict_ReturnsNonNullWhenDictExists_698) {

    PageAttrs pageAttrs(nullptr, dict);

    EXPECT_NE(pageAttrs.getResourceDict(), nullptr);

}



TEST_F(PageAttrsTest_698, GetResourceDict_ReturnsNullWhenNoDict_698) {

    Dict emptyDict;

    PageAttrs pageAttrs(nullptr, &emptyDict);

    EXPECT_EQ(pageAttrs.getResourceDict(), nullptr);

}



TEST_F(PageAttrsTest_698, BoundaryCondition_EmptyResourcesDict_698) {

    Dict* emptyResourcesDict = new Dict();

    dict->dictSet("Resources", Object(emptyResourcesDict));

    PageAttrs pageAttrs(nullptr, dict);

    EXPECT_NE(pageAttrs.getResourceDict(), nullptr);

}



TEST_F(PageAttrsTest_698, BoundaryCondition_MissingKeyInDict_698) {

    dict->dictRemove("Resources");

    PageAttrs pageAttrs(nullptr, dict);

    EXPECT_EQ(pageAttrs.getResourceDict(), nullptr);

}
