#include <gtest/gtest.h>

#include "Annot.h"

#include <memory>



class AnnotTest_784 : public ::testing::Test {

protected:

    std::unique_ptr<GooString> contents;

    PDFDoc* mockPDFDoc = nullptr; // Assuming PDFDoc is a dependency that needs to be mocked

    std::unique_ptr<Annot> annot;



    void SetUp() override {

        contents = std::make_unique<GooString>("Test Contents");

        annot = std::make_unique<Annot>(mockPDFDoc, new PDFRectangle(0, 0, 100, 100));

        annot->setContents(std::move(contents));

    }



    void TearDown() override {

        // Clean up if necessary

    }

};



TEST_F(AnnotTest_784, GetContents_ReturnsSetContent_784) {

    const GooString* retrievedContents = annot->getContents();

    EXPECT_STREQ(retrievedContents->getCString(), "Test Contents");

}



TEST_F(AnnotTest_784, GetContents_ReturnsNullWhenNotSet_784) {

    contents.reset();

    Annot emptyAnnot(mockPDFDoc, new PDFRectangle(0, 0, 100, 100));

    const GooString* retrievedContents = emptyAnnot.getContents();

    EXPECT_EQ(retrievedContents, nullptr);

}



TEST_F(AnnotTest_784, SetContents_ChangesContent_784) {

    std::unique_ptr<GooString> newContents = std::make_unique<GooString>("Updated Contents");

    annot->setContents(std::move(newContents));

    const GooString* retrievedContents = annot->getContents();

    EXPECT_STREQ(retrievedContents->getCString(), "Updated Contents");

}



TEST_F(AnnotTest_784, IsOk_ReturnsTrueForValidAnnot_784) {

    EXPECT_TRUE(annot->isOk());

}
