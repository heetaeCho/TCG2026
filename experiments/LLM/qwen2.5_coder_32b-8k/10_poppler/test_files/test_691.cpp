#include <gtest/gtest.h>

#include "Page.h"



class PageAttrsTest_691 : public ::testing::Test {

protected:

    Dict dict;

    PageAttrs pageAttrs;



    PageAttrsTest_691() : pageAttrs(&pageAttrs, &dict) {}

};



TEST_F(PageAttrsTest_691, GetMediaBox_ReturnsNonNullPointer_691) {

    EXPECT_NE(pageAttrs.getMediaBox(), nullptr);

}



TEST_F(PageAttrsTest_691, GetCropBox_ReturnsNonNullPointer_691) {

    EXPECT_NE(pageAttrs.getCropBox(), nullptr);

}



TEST_F(PageAttrsTest_691, IsCropped_ReturnsFalseByDefault_691) {

    EXPECT_FALSE(pageAttrs.isCropped());

}



TEST_F(PageAttrsTest_691, GetBleedBox_ReturnsNonNullPointer_691) {

    EXPECT_NE(pageAttrs.getBleedBox(), nullptr);

}



TEST_F(PageAttrsTest_691, GetTrimBox_ReturnsNonNullPointer_691) {

    EXPECT_NE(pageAttrs.getTrimBox(), nullptr);

}



TEST_F(PageAttrsTest_691, GetArtBox_ReturnsNonNullPointer_691) {

    EXPECT_NE(pageAttrs.getArtBox(), nullptr);

}



TEST_F(PageAttrsTest_691, GetRotate_ReturnsZeroByDefault_691) {

    EXPECT_EQ(pageAttrs.getRotate(), 0);

}



TEST_F(PageAttrsTest_691, GetLastModified_ReturnsNonNullPointer_691) {

    EXPECT_NE(pageAttrs.getLastModified(), nullptr);

}



TEST_F(PageAttrsTest_691, GetBoxColorInfo_ReturnsNonNullPointer_691) {

    EXPECT_NE(pageAttrs.getBoxColorInfo(), nullptr);

}



TEST_F(PageAttrsTest_691, GetGroup_ReturnsNonNullPointer_691) {

    EXPECT_NE(pageAttrs.getGroup(), nullptr);

}



TEST_F(PageAttrsTest_691, GetMetadata_ReturnsNonNullPointer_691) {

    EXPECT_NE(pageAttrs.getMetadata(), nullptr);

}



TEST_F(PageAttrsTest_691, GetPieceInfo_ReturnsNonNullPointer_691) {

    EXPECT_NE(pageAttrs.getPieceInfo(), nullptr);

}



TEST_F(PageAttrsTest_691, GetSeparationInfo_ReturnsNonNullPointer_691) {

    EXPECT_NE(pageAttrs.getSeparationInfo(), nullptr);

}



TEST_F(PageAttrsTest_691, GetResourceDict_ReturnsNonNullPointer_691) {

    EXPECT_NE(pageAttrs.getResourceDict(), nullptr);

}



TEST_F(PageAttrsTest_691, GetResourceDictObject_ReturnsNonNullPointer_691) {

    EXPECT_NE(pageAttrs.getResourceDictObject(), nullptr);

}
