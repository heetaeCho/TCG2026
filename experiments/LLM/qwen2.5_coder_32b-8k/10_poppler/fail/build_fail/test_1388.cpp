#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation-private.h"



using namespace Poppler;



class AnnotationPrivateTest : public ::testing::Test {

protected:

    std::shared_ptr<Annot> mockPdfAnnot = std::make_shared<Annot>();

    ::Page* mockPdfPage = nullptr;

    DocumentData* mockDocumentData = nullptr;

    QRectF testRect = QRectF(0, 0, 100, 100);

    int testFlags = 0;



    AnnotationPrivate* annotationPrivate;



    void SetUp() override {

        annotationPrivate = new AnnotationPrivate();

        annotationPrivate->tieToNativeAnnot(mockPdfAnnot, mockPdfPage, mockDocumentData);

    }



    void TearDown() override {

        delete annotationPrivate;

    }

};



TEST_F(AnnotationPrivateTest_1388, BoundaryToPdfRectangle_NormalOperation_1388) {

    PDFRectangle pdfRect = annotationPrivate->boundaryToPdfRectangle(testRect, testFlags);

    // Assuming some checks can be done on the returned PDFRectangle

    EXPECT_EQ(pdfRect.x1, 0.0);  // Example check, replace with actual logic if possible

    EXPECT_EQ(pdfRect.y1, 0.0);

    EXPECT_EQ(pdfRect.x2, 100.0);

    EXPECT_EQ(pdfRect.y2, 100.0);

}



TEST_F(AnnotationPrivateTest_1388, BoundaryToPdfRectangle_BoundaryConditions_1388) {

    QRectF zeroRect = QRectF(0, 0, 0, 0);

    PDFRectangle pdfZeroRect = annotationPrivate->boundaryToPdfRectangle(zeroRect, testFlags);

    EXPECT_EQ(pdfZeroRect.x1, 0.0);

    EXPECT_EQ(pdfZeroRect.y1, 0.0);

    EXPECT_EQ(pdfZeroRect.x2, 0.0);

    EXPECT_EQ(pdfZeroRect.y2, 0.0);



    QRectF negativeRect = QRectF(-50, -50, 100, 100);

    PDFRectangle pdfNegativeRect = annotationPrivate->boundaryToPdfRectangle(negativeRect, testFlags);

    EXPECT_EQ(pdfNegativeRect.x1, -50.0);

    EXPECT_EQ(pdfNegativeRect.y1, -50.0);

    EXPECT_EQ(pdfNegativeRect.x2, 50.0);

    EXPECT_EQ(pdfNegativeRect.y2, 50.0);

}



// Assuming no direct exception handling in boundaryToPdfRectangle

// If there are observable error cases, tests can be added accordingly



TEST_F(AnnotationPrivateTest_1388, BoundaryToPdfRectangle_ExternalInteraction_1388) {

    // No external collaborators are involved directly in this function,

    // so no Google Mock is needed here.

    PDFRectangle pdfRect = annotationPrivate->boundaryToPdfRectangle(testRect, testFlags);

    EXPECT_EQ(pdfRect.x1, 0.0);  // Example check, replace with actual logic if possible

    EXPECT_EQ(pdfRect.y1, 0.0);

    EXPECT_EQ(pdfRect.x2, 100.0);

    EXPECT_EQ(pdfRect.y2, 100.0);

}
