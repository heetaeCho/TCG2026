#include <gtest/gtest.h>

#include "poppler-annotation-private.h"

#include "Page.h"

#include "poppler-private.h"

#include "Error.h"



using namespace Poppler;



class AnnotationPrivateTest_1382 : public ::testing::Test {

protected:

    std::shared_ptr<Annot> mockAnnot;

    Page* mockPage;

    DocumentData* mockDoc;



    void SetUp() override {

        mockAnnot = std::make_shared<Annot>();

        mockPage = new Page(nullptr, 1, Object(), Ref(), std::unique_ptr<PageAttrs>(nullptr));

        mockDoc = new DocumentData(QString(""), std::optional<GooString>(), std::optional<GooString>());

    }



    void TearDown() override {

        delete mockPage;

        delete mockDoc;

    }

};



TEST_F(AnnotationPrivateTest_1382, TieToNativeAnnot_SuccessfulTie_1382) {

    AnnotationPrivate annotationPrivate;

    EXPECT_EQ(annotationPrivate.pdfAnnot, nullptr);

    annotationPrivate.tieToNativeAnnot(mockAnnot, mockPage, mockDoc);

    EXPECT_EQ(annotationPrivate.pdfAnnot, mockAnnot);

    EXPECT_EQ(annotationPrivate.pdfPage, mockPage);

    EXPECT_EQ(annotationPrivate.parentDoc, mockDoc);

}



TEST_F(AnnotationPrivateTest_1382, TieToNativeAnnot_AlreadyTiedError_1382) {

    AnnotationPrivate annotationPrivate;

    annotationPrivate.tieToNativeAnnot(mockAnnot, mockPage, mockDoc);

    EXPECT_EQ(annotationPrivate.pdfAnnot, mockAnnot);



    // Attempt to tie again

    annotationPrivate.tieToNativeAnnot(std::make_shared<Annot>(), mockPage, mockDoc);

    EXPECT_EQ(annotationPrivate.pdfAnnot, mockAnnot);  // Should remain the same

}



TEST_F(AnnotationPrivateTest_1382, TieToNativeAnnot_NullptrAnnot_1382) {

    AnnotationPrivate annotationPrivate;

    annotationPrivate.tieToNativeAnnot(nullptr, mockPage, mockDoc);

    EXPECT_EQ(annotationPrivate.pdfAnnot, nullptr);

    EXPECT_EQ(annotationPrivate.pdfPage, nullptr);

    EXPECT_EQ(annotationPrivate.parentDoc, nullptr);

}



TEST_F(AnnotationPrivateTest_1382, TieToNativeAnnot_NullptrPage_1382) {

    AnnotationPrivate annotationPrivate;

    annotationPrivate.tieToNativeAnnot(mockAnnot, nullptr, mockDoc);

    EXPECT_EQ(annotationPrivate.pdfAnnot, nullptr);

    EXPECT_EQ(annotationPrivate.pdfPage, nullptr);

    EXPECT_EQ(annotationPrivate.parentDoc, nullptr);

}



TEST_F(AnnotationPrivateTest_1382, TieToNativeAnnot_NullptrDocument_1382) {

    AnnotationPrivate annotationPrivate;

    annotationPrivate.tieToNativeAnnot(mockAnnot, mockPage, nullptr);

    EXPECT_EQ(annotationPrivate.pdfAnnot, nullptr);

    EXPECT_EQ(annotationPrivate.pdfPage, nullptr);

    EXPECT_EQ(annotationPrivate.parentDoc, nullptr);

}
