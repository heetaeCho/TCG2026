#include <gtest/gtest.h>

#include "poppler-annotation-private.h"

#include "Object.h"



using namespace Poppler;



class AnnotationPrivateTest : public ::testing::Test {

protected:

    std::shared_ptr<Annot> pdfAnnot;

    Page* pdfPage = nullptr;

    DocumentData* parentDoc = nullptr;

    AnnotationPrivate* annotationPrivate;



    void SetUp() override {

        annotationPrivate = new AnnotationPrivate();

    }



    void TearDown() override {

        delete annotationPrivate;

    }

};



TEST_F(AnnotationPrivateTest_1391, PdfObjectReference_ReturnsInvalidRef_WhenPdfAnnotIsNull_1391) {

    EXPECT_EQ(annotationPrivate->pdfObjectReference(), Ref::INVALID());

}



TEST_F(AnnotationPrivateTest_1391, PdfObjectReference_ReturnsValidRef_WhenPdfAnnotIsNotNull_1391) {

    pdfAnnot = std::make_shared<Annot>();

    annotationPrivate->tieToNativeAnnot(pdfAnnot, pdfPage, parentDoc);

    EXPECT_NE(annotationPrivate->pdfObjectReference(), Ref::INVALID());

}



TEST_F(AnnotationPrivateTest_1391, TieToNativeAnnot_SetsPdfAnnot_PdfPage_AndParentDoc_1391) {

    pdfAnnot = std::make_shared<Annot>();

    annotationPrivate->tieToNativeAnnot(pdfAnnot, pdfPage, parentDoc);

    EXPECT_EQ(annotationPrivate->pdfAnnot, pdfAnnot);

    EXPECT_EQ(annotationPrivate->pdfPage, pdfPage);

    EXPECT_EQ(annotationPrivate->parentDoc, parentDoc);

}



TEST_F(AnnotationPrivateTest_1391, CreateNativeAnnot_ReturnsNonNullPointer_WhenCalled_1391) {

    Page* destPage = nullptr;

    DocumentData* doc = nullptr;

    std::shared_ptr<Annot> nativeAnnot = annotationPrivate->createNativeAnnot(destPage, doc);

    EXPECT_NE(nativeAnnot, nullptr);

}
