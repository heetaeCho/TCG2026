#include <gtest/gtest.h>

#include "Page.h"

#include <gmock/gmock.h>



class PageAttrsTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary objects or mocks here if needed.

        Dict dict; // Assuming Dict is a default-constructible class

        pageAttrs = new PageAttrs(nullptr, &dict);

    }



    void TearDown() override {

        delete pageAttrs;

    }



    PageAttrs* pageAttrs;

};



TEST_F(PageAttrsTest_699, GetResourceDictObject_ReturnsNonNullPointer_699) {

    EXPECT_NE(pageAttrs->getResourceDictObject(), nullptr);

}



// Assuming normal operation for getMediaBox

TEST_F(PageAttrsTest_699, GetMediaBox_ReturnsNonNullPointer_699) {

    EXPECT_NE(pageAttrs->getMediaBox(), nullptr);

}



// Assuming normal operation for getCropBox

TEST_F(PageAttrsTest_699, GetCropBox_ReturnsNonNullPointer_699) {

    EXPECT_NE(pageAttrs->getCropBox(), nullptr);

}



// Boundary condition: Check if isCropped returns false initially (assuming no cropping by default)

TEST_F(PageAttrsTest_699, IsCropped_ReturnsFalseInitially_699) {

    EXPECT_FALSE(pageAttrs->isCropped());

}



// Assuming normal operation for getBleedBox

TEST_F(PageAttrsTest_699, GetBleedBox_ReturnsNonNullPointer_699) {

    EXPECT_NE(pageAttrs->getBleedBox(), nullptr);

}



// Assuming normal operation for getTrimBox

TEST_F(PageAttrsTest_699, GetTrimBox_ReturnsNonNullPointer_699) {

    EXPECT_NE(pageAttrs->getTrimBox(), nullptr);

}



// Assuming normal operation for getArtBox

TEST_F(PageAttrsTest_699, GetArtBox_ReturnsNonNullPointer_699) {

    EXPECT_NE(pageAttrs->getArtBox(), nullptr);

}



// Assuming normal operation for getRotate

TEST_F(PageAttrsTest_699, GetRotate_ReturnsZeroInitially_699) {

    EXPECT_EQ(pageAttrs->getRotate(), 0); // Assuming default rotation is 0 degrees

}



// Assuming normal operation for getLastModified

TEST_F(PageAttrsTest_699, GetLastModified_ReturnsNonNullPointer_699) {

    EXPECT_NE(pageAttrs->getLastModified(), nullptr);

}



// Assuming normal operation for getBoxColorInfo

TEST_F(PageAttrsTest_699, GetBoxColorInfo_ReturnsNonNullPointer_699) {

    EXPECT_NE(pageAttrs->getBoxColorInfo(), nullptr);

}



// Assuming normal operation for getGroup

TEST_F(PageAttrsTest_699, GetGroup_ReturnsNonNullPointer_699) {

    EXPECT_NE(pageAttrs->getGroup(), nullptr);

}



// Assuming normal operation for getMetadata (returns Stream*)

TEST_F(PageAttrsTest_699, GetMetadata_ReturnsNonNullPointer_699) {

    EXPECT_NE(pageAttrs->getMetadata(), nullptr);

}



// Assuming normal operation for getPieceInfo

TEST_F(PageAttrsTest_699, GetPieceInfo_ReturnsNonNullPointer_699) {

    EXPECT_NE(pageAttrs->getPieceInfo(), nullptr);

}



// Assuming normal operation for getSeparationInfo

TEST_F(PageAttrsTest_699, GetSeparationInfo_ReturnsNonNullPointer_699) {

    EXPECT_NE(pageAttrs->getSeparationInfo(), nullptr);

}



// Assuming normal operation for getResourceDict

TEST_F(PageAttrsTest_699, GetResourceDict_ReturnsNonNullPointer_699) {

    EXPECT_NE(pageAttrs->getResourceDict(), nullptr);

}
