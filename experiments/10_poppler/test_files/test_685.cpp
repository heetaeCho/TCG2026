#include <gtest/gtest.h>

#include "poppler/Page.h"



// Mock class for PDFRectangle if needed (not required in this case as it's a simple struct)

// Mock classes for external collaborators if any



class PageAttrsTest : public ::testing::Test {

protected:

    PageAttrs* pageAttrs;



    virtual void SetUp() {

        // Assuming default constructor is available or mock dependencies if necessary

        pageAttrs = new PageAttrs(nullptr, nullptr);

    }



    virtual void TearDown() {

        delete pageAttrs;

    }

};



TEST_F(PageAttrsTest_685, GetMediaBox_ReturnsValidPointer_685) {

    const PDFRectangle* mediaBox = pageAttrs->getMediaBox();

    EXPECT_NE(mediaBox, nullptr);

}



// Assuming there is a way to test boundary conditions for the boxes

// Since we don't have details on how these are set or initialized, basic tests are provided



TEST_F(PageAttrsTest_685, GetCropBox_ReturnsValidPointer_685) {

    const PDFRectangle* cropBox = pageAttrs->getCropBox();

    EXPECT_NE(cropBox, nullptr);

}



TEST_F(PageAttrsTest_685, IsCropped_ReturnsFalseByDefault_685) {

    bool isCropped = pageAttrs->isCropped();

    EXPECT_FALSE(isCropped);

}



TEST_F(PageAttrsTest_685, GetBleedBox_ReturnsValidPointer_685) {

    const PDFRectangle* bleedBox = pageAttrs->getBleedBox();

    EXPECT_NE(bleedBox, nullptr);

}



TEST_F(PageAttrsTest_685, GetTrimBox_ReturnsValidPointer_685) {

    const PDFRectangle* trimBox = pageAttrs->getTrimBox();

    EXPECT_NE(trimBox, nullptr);

}



TEST_F(PageAttrsTest_685, GetArtBox_ReturnsValidPointer_685) {

    const PDFRectangle* artBox = pageAttrs->getArtBox();

    EXPECT_NE(artBox, nullptr);

}



TEST_F(PageAttrsTest_685, GetRotate_DefaultValueIsZero_685) {

    int rotation = pageAttrs->getRotate();

    EXPECT_EQ(rotation, 0);

}



TEST_F(PageAttrsTest_685, GetLastModified_ReturnsNullptrByDefault_685) {

    const GooString* lastModified = pageAttrs->getLastModified();

    EXPECT_EQ(lastModified, nullptr);

}



// Assuming Dict and Stream are classes that can be mocked or have default behavior

TEST_F(PageAttrsTest_685, GetBoxColorInfo_ReturnsNullptrByDefault_685) {

    Dict* boxColorInfo = pageAttrs->getBoxColorInfo();

    EXPECT_EQ(boxColorInfo, nullptr);

}



TEST_F(PageAttrsTest_685, GetGroup_ReturnsNullptrByDefault_685) {

    Dict* group = pageAttrs->getGroup();

    EXPECT_EQ(group, nullptr);

}



TEST_F(PageAttrsTest_685, GetMetadata_ReturnsNullptrByDefault_685) {

    Stream* metadata = pageAttrs->getMetadata();

    EXPECT_EQ(metadata, nullptr);

}



TEST_F(PageAttrsTest_685, GetPieceInfo_ReturnsNullptrByDefault_685) {

    Dict* pieceInfo = pageAttrs->getPieceInfo();

    EXPECT_EQ(pieceInfo, nullptr);

}



TEST_F(PageAttrsTest_685, GetSeparationInfo_ReturnsNullptrByDefault_685) {

    Dict* separationInfo = pageAttrs->getSeparationInfo();

    EXPECT_EQ(separationInfo, nullptr);

}



TEST_F(PageAttrsTest_685, GetResourceDict_ReturnsNullptrByDefault_685) {

    Dict* resourceDict = pageAttrs->getResourceDict();

    EXPECT_EQ(resourceDict, nullptr);

}



TEST_F(PageAttrsTest_685, GetResourceDictObject_ReturnsNullptrByDefault_685) {

    Object* resourceDictObj = pageAttrs->getResourceDictObject();

    EXPECT_EQ(resourceDictObj, nullptr);

}
