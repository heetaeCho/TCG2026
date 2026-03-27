#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Page.h"

#include "Object.h"



using namespace testing;



class PageAttrsTest : public Test {

protected:

    Dict* dict;

    std::unique_ptr<PageAttrs> pageAttrs;



    void SetUp() override {

        dict = new Dict();

        pageAttrs.reset(new PageAttrs(nullptr, dict));

    }



    void TearDown() override {

        delete dict;

    }

};



TEST_F(PageAttrsTest_692, GetLastModified_ReturnsNullWhenNotSet_692) {

    EXPECT_EQ(pageAttrs->getLastModified(), nullptr);

}



TEST_F(PageAttrsTest_692, GetLastModified_ReturnsStringValue_692) {

    std::unique_ptr<GooString> lastModifiedString(new GooString("2023-10-01T12:00:00Z"));

    Object lastModifiedObj(std::move(lastModifiedString));

    dict->dictSet("LastModified", std::move(lastModifiedObj));



    EXPECT_STREQ(pageAttrs->getLastModified()->getCString(), "2023-10-01T12:00:00Z");

}



TEST_F(PageAttrsTest_692, GetMediaBox_ReturnsNullByDefault_692) {

    EXPECT_EQ(pageAttrs->getMediaBox(), nullptr);

}



TEST_F(PageAttrsTest_692, GetCropBox_ReturnsNullWhenNotSet_692) {

    EXPECT_EQ(pageAttrs->getCropBox(), nullptr);

}



TEST_F(PageAttrsTest_692, IsCropped_ReturnsFalseByDefault_692) {

    EXPECT_FALSE(pageAttrs->isCropped());

}



TEST_F(PageAttrsTest_692, GetBleedBox_ReturnsNullByDefault_692) {

    EXPECT_EQ(pageAttrs->getBleedBox(), nullptr);

}



TEST_F(PageAttrsTest_692, GetTrimBox_ReturnsNullByDefault_692) {

    EXPECT_EQ(pageAttrs->getTrimBox(), nullptr);

}



TEST_F(PageAttrsTest_692, GetArtBox_ReturnsNullByDefault_692) {

    EXPECT_EQ(pageAttrs->getArtBox(), nullptr);

}



TEST_F(PageAttrsTest_692, GetRotate_ReturnsZeroByDefault_692) {

    EXPECT_EQ(pageAttrs->getRotate(), 0);

}
