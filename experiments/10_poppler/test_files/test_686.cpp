#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Page.h"



using ::testing::Test;



class PageAttrsTest : public Test {

protected:

    Dict* dict = nullptr;

    PageAttrs* pageAttrs = nullptr;



    void SetUp() override {

        dict = new Dict();

        pageAttrs = new PageAttrs(nullptr, dict);

    }



    void TearDown() override {

        delete pageAttrs;

        delete dict;

    }

};



TEST_F(PageAttrsTest_686, GetMediaBox_ReturnsValidPointer_686) {

    EXPECT_NE(pageAttrs->getMediaBox(), nullptr);

}



TEST_F(PageAttrsTest_686, GetCropBox_ReturnsValidPointer_686) {

    EXPECT_NE(pageAttrs->getCropBox(), nullptr);

}



TEST_F(PageAttrsTest_686, IsCropped_ReturnsFalseWhenNoCropBox_686) {

    EXPECT_FALSE(pageAttrs->isCropped());

}



TEST_F(PageAttrsTest_686, GetBleedBox_ReturnsValidPointer_686) {

    EXPECT_NE(pageAttrs->getBleedBox(), nullptr);

}



TEST_F(PageAttrsTest_686, GetTrimBox_ReturnsValidPointer_686) {

    EXPECT_NE(pageAttrs->getTrimBox(), nullptr);

}



TEST_F(PageAttrsTest_686, GetArtBox_ReturnsValidPointer_686) {

    EXPECT_NE(pageAttrs->getArtBox(), nullptr);

}



TEST_F(PageAttrsTest_686, GetRotate_ReturnsZeroByDefault_686) {

    EXPECT_EQ(pageAttrs->getRotate(), 0);

}



TEST_F(PageAttrsTest_686, GetLastModified_ReturnsNullWhenNotSet_686) {

    EXPECT_EQ(pageAttrs->getLastModified(), nullptr);

}



TEST_F(PageAttrsTest_686, GetBoxColorInfo_ReturnsNullByDefault_686) {

    EXPECT_EQ(pageAttrs->getBoxColorInfo(), nullptr);

}



TEST_F(PageAttrsTest_686, GetGroup_ReturnsNullByDefault_686) {

    EXPECT_EQ(pageAttrs->getGroup(), nullptr);

}



TEST_F(PageAttrsTest_686, GetMetadata_ReturnsNullByDefault_686) {

    EXPECT_EQ(pageAttrs->getMetadata(), nullptr);

}



TEST_F(PageAttrsTest_686, GetPieceInfo_ReturnsNullByDefault_686) {

    EXPECT_EQ(pageAttrs->getPieceInfo(), nullptr);

}



TEST_F(PageAttrsTest_686, GetSeparationInfo_ReturnsNullByDefault_686) {

    EXPECT_EQ(pageAttrs->getSeparationInfo(), nullptr);

}



TEST_F(PageAttrsTest_686, GetResourceDict_ReturnsValidPointer_686) {

    EXPECT_NE(pageAttrs->getResourceDict(), nullptr);

}



TEST_F(PageAttrsTest_686, GetResourceDictObject_ReturnsValidPointer_686) {

    EXPECT_NE(pageAttrs->getResourceDictObject(), nullptr);

}
