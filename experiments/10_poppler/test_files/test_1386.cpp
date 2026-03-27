#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation-private.h"

#include "PDFRectangle.h"



using namespace Poppler;



class AnnotationPrivateTest_1386 : public ::testing::Test {

protected:

    AnnotationPrivate* annotationPrivate;

    

    void SetUp() override {

        annotationPrivate = new AnnotationPrivate();

    }



    void TearDown() override {

        delete annotationPrivate;

    }

};



TEST_F(AnnotationPrivateTest_1386, FromPdfRectangle_NormalOperation_1386) {

    PDFRectangle pdfRect(1.0, 2.0, 3.0, 4.0);

    QRectF result = annotationPrivate->fromPdfRectangle(pdfRect);



    // Assuming no transformation for simplicity, the result should be the same as input

    EXPECT_EQ(result.topLeft(), QPointF(1.0, 2.0));

    EXPECT_EQ(result.bottomRight(), QPointF(3.0, 4.0));

}



TEST_F(AnnotationPrivateTest_1386, FromPdfRectangle_BoundaryConditions_1386) {

    PDFRectangle pdfRect(0.0, 0.0, 0.0, 0.0);

    QRectF result = annotationPrivate->fromPdfRectangle(pdfRect);



    EXPECT_EQ(result.topLeft(), QPointF(0.0, 0.0));

    EXPECT_EQ(result.bottomRight(), QPointF(0.0, 0.0));



    PDFRectangle pdfRectNegative(-1.0, -2.0, -3.0, -4.0);

    result = annotationPrivate->fromPdfRectangle(pdfRectNegative);



    EXPECT_EQ(result.topLeft(), QPointF(-3.0, -4.0));

    EXPECT_EQ(result.bottomRight(), QPointF(-1.0, -2.0));



    PDFRectangle pdfRectMixed(1.0, 4.0, 3.0, 2.0);

    result = annotationPrivate->fromPdfRectangle(pdfRectMixed);



    EXPECT_EQ(result.topLeft(), QPointF(1.0, 2.0));

    EXPECT_EQ(result.bottomRight(), QPointF(3.0, 4.0));

}



TEST_F(AnnotationPrivateTest_1386, FromPdfRectangle_ExceptionalCases_1386) {

    // Assuming fromPdfRectangle does not throw exceptions under normal circumstances

    // We can't test for exceptions without specific error conditions in the function



    // If there are known invalid states that could be passed to fromPdfRectangle,

    // we would need those details to create meaningful exceptional case tests.

}
