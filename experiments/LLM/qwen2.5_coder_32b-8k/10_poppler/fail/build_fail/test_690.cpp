#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Page.h"



class PageAttrsTest : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Assuming Dict and PDFRectangle are properly constructed and passed.

        // For testing, we create a mock Dict object if necessary, but here we assume default construction suffices for these tests.

        dict = new Dict();  // Proper setup would be required in actual use

        attrs = new PageAttrs(nullptr, dict);

    }



    virtual void TearDown() {

        delete attrs;

        delete dict;

    }



    Dict* dict;

    PageAttrs* attrs;

};



TEST_F(PageAttrsTest_690, GetArtBox_ReturnsValidPointer_690) {

    const PDFRectangle* artBox = attrs->getArtBox();

    EXPECT_NE(artBox, nullptr);

}



// Additional tests for boundary conditions and error cases are limited by the provided interface.

// Since there are no parameters or states to manipulate in these getter methods, further specific tests aren't feasible without additional context.



TEST_F(PageAttrsTest_690, GetMediaBox_ReturnsValidPointer_690) {

    const PDFRectangle* mediaBox = attrs->getMediaBox();

    EXPECT_NE(mediaBox, nullptr);

}



TEST_F(PageAttrsTest_690, GetCropBox_ReturnsValidPointer_690) {

    const PDFRectangle* cropBox = attrs->getCropBox();

    EXPECT_NE(cropBox, nullptr);

}



TEST_F(PageAttrsTest_690, IsCropped_ReturnsFalseWhenNoCropBox_690) {

    bool isCropped = attrs->isCropped();

    EXPECT_FALSE(isCropped);

}



// Assuming that the presence of cropBox can be tested by setting it up in Dict.

// However, since we cannot modify internal state directly, this test assumes default behavior.

TEST_F(PageAttrsTest_690, GetBleedBox_ReturnsValidPointer_690) {

    const PDFRectangle* bleedBox = attrs->getBleedBox();

    EXPECT_NE(bleedBox, nullptr);

}



TEST_F(PageAttrsTest_690, GetTrimBox_ReturnsValidPointer_690) {

    const PDFRectangle* trimBox = attrs->getTrimBox();

    EXPECT_NE(trimBox, nullptr);

}
