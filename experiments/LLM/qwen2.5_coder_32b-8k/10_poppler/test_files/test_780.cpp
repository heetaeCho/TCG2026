#include <gtest/gtest.h>

#include "Annot.h"

#include <memory>



// Test fixture for Annot tests

class AnnotTest_780 : public ::testing::Test {

protected:

    PDFDoc* mock_doc;

    std::unique_ptr<PDFRectangle> mock_rect;



    void SetUp() override {

        mock_doc = new PDFDoc();

        mock_rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);

    }



    void TearDown() override {

        delete mock_doc;

    }

};



// Test if getRef returns a valid Ref object

TEST_F(AnnotTest_780, GetRef_ReturnsValidRef_780) {

    Annot annot(mock_doc, mock_rect.get());

    EXPECT_TRUE(annot.getRef().isValid());

}



// Test if isOk() returns true for a properly initialized Annot

TEST_F(AnnotTest_780, IsOk_ReturnsTrueForValidAnnot_780) {

    Annot annot(mock_doc, mock_rect.get());

    EXPECT_TRUE(annot.isOk());

}



// Test if match() correctly identifies the same Ref

TEST_F(AnnotTest_780, Match_ReturnsTrueForSameRef_780) {

    Annot annot(mock_doc, mock_rect.get());

    Ref ref = annot.getRef();

    EXPECT_TRUE(annot.match(&ref));

}



// Test if getPageNum() returns a valid page number

TEST_F(AnnotTest_780, GetPageNum_ReturnsValidPageNumber_780) {

    Annot annot(mock_doc, mock_rect.get());

    EXPECT_GE(annot.getPageNum(), 0);

}



// Test if getRect() returns the correct rectangle coordinates

TEST_F(AnnotTest_780, GetRect_ReturnsCorrectCoordinates_780) {

    Annot annot(mock_doc, mock_rect.get());

    double x1, y1, x2, y2;

    annot.getRect(&x1, &y1, &x2, &y2);

    EXPECT_EQ(x1, 0);

    EXPECT_EQ(y1, 0);

    EXPECT_EQ(x2, 100);

    EXPECT_EQ(y2, 100);

}



// Test if setContents and getContents work correctly

TEST_F(AnnotTest_780, SetAndGetContents_WorksCorrectly_780) {

    Annot annot(mock_doc, mock_rect.get());

    auto contents = std::make_unique<GooString>("Sample Content");

    annot.setContents(std::move(contents));

    EXPECT_STREQ(annot.getContents()->getCString(), "Sample Content");

}



// Test if setModified and getModified work correctly

TEST_F(AnnotTest_780, SetAndGetModified_WorksCorrectly_780) {

    Annot annot(mock_doc, mock_rect.get());

    auto modified = std::make_unique<GooString>("2023-10-01");

    annot.setModified(std::move(modified));

    EXPECT_STREQ(annot.getModified()->getCString(), "2023-10-01");

}



// Test if setName and getName work correctly

TEST_F(AnnotTest_780, SetAndGetName_WorksCorrectly_780) {

    Annot annot(mock_doc, mock_rect.get());

    GooString name("Sample Name");

    annot.setName(&name);

    EXPECT_STREQ(annot.getName()->getCString(), "Sample Name");

}



// Test if setFlags and getFlags work correctly

TEST_F(AnnotTest_780, SetAndGetFlags_WorksCorrectly_780) {

    Annot annot(mock_doc, mock_rect.get());

    unsigned int flags = 123;

    annot.setFlags(flags);

    EXPECT_EQ(annot.getFlags(), flags);

}



// Test if getDoc() returns the correct document pointer

TEST_F(AnnotTest_780, GetDoc_ReturnsCorrectPointer_780) {

    Annot annot(mock_doc, mock_rect.get());

    EXPECT_EQ(annot.getDoc(), mock_doc);

}
