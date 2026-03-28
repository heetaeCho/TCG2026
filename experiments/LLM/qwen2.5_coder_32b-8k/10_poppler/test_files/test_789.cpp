#include <gtest/gtest.h>

#include "poppler/Annot.h"



class AnnotTest_789 : public ::testing::Test {

protected:

    PDFDoc* mockDoc;

    std::unique_ptr<PDFRectangle> mockRect;

    Annot* annot;



    void SetUp() override {

        mockDoc = new PDFDoc();

        mockRect = std::make_unique<PDFRectangle>(0, 0, 100, 100);

        annot = new Annot(mockDoc, mockRect.get());

    }



    void TearDown() override {

        delete annot;

        delete mockDoc;

    }

};



TEST_F(AnnotTest_789, GetAppearStreams_ReturnsNonNullPointer_789) {

    EXPECT_NE(nullptr, annot->getAppearStreams());

}



TEST_F(AnnotTest_789, GetAppearStreams_ConsistentAcrossCalls_789) {

    AnnotAppearance* firstCall = annot->getAppearStreams();

    AnnotAppearance* secondCall = annot->getAppearStreams();

    EXPECT_EQ(firstCall, secondCall);

}
