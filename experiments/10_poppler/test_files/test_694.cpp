#include <gtest/gtest.h>

#include "Page.h"

#include "Object.h"



class PageAttrsTest : public ::testing::Test {

protected:

    Dict* dict;

    PageAttrs* pageAttrs;



    void SetUp() override {

        dict = new Dict();

        pageAttrs = new PageAttrs(nullptr, dict);

    }



    void TearDown() override {

        delete pageAttrs;

        delete dict;

    }

};



TEST_F(PageAttrsTest_694, GetGroup_ReturnsNullWhenNotADict_694) {

    Object nonDict(Object::objInt, 42);

    pageAttrs->group = nonDict;



    EXPECT_EQ(pageAttrs->getGroup(), nullptr);

}



TEST_F(PageAttrsTest_694, GetGroup_ReturnsDictPointerWhenIsDict_694) {

    Dict* groupDict = new Dict();

    Object dictObject(groupDict);

    pageAttrs->group = dictObject;



    EXPECT_EQ(pageAttrs->getGroup(), groupDict);



    delete groupDict;

}



TEST_F(PageAttrsTest_694, GetGroup_ReturnsNullWhenDictIsEmpty_694) {

    Dict* emptyDict = new Dict();

    Object dictObject(emptyDict);

    pageAttrs->group = dictObject;



    EXPECT_EQ(pageAttrs->getGroup(), emptyDict);



    delete emptyDict;

}
