#include <gtest/gtest.h>

#include "Page.h"

#include "Object.h"



using namespace poppler;



class PageAttrsTest_693 : public ::testing::Test {

protected:

    Dict* dict;

    Object boxColorInfo;

    PageAttrs* pageAttrs;



    void SetUp() override {

        dict = new Dict();

        boxColorInfo = Object(new Dict());

        dict->dictSet("BoxColorInfo", std::move(boxColorInfo));

        pageAttrs = new PageAttrs(nullptr, dict);

    }



    void TearDown() override {

        delete pageAttrs;

        delete dict;

    }

};



TEST_F(PageAttrsTest_693, GetBoxColorInfo_ReturnsDict_693) {

    Dict* result = pageAttrs->getBoxColorInfo();

    EXPECT_NE(result, nullptr);

}



TEST_F(PageAttrsTest_693, GetBoxColorInfo_ReturnsNullWhenNotSet_693) {

    dict->dictRemove("BoxColorInfo");

    Dict* result = pageAttrs->getBoxColorInfo();

    EXPECT_EQ(result, nullptr);

}



TEST_F(PageAttrsTest_693, GetBoxColorInfo_ReturnsSameDict_693) {

    Dict* initialDict = boxColorInfo.getDict();

    Dict* result = pageAttrs->getBoxColorInfo();

    EXPECT_EQ(initialDict, result);

}
