#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation-private.h"

#include "Page.h"



using namespace Poppler;

using ::testing::_;

using ::testing::NiceMock;



class MockPage : public Page {

public:

    MOCK_METHOD(void, removeAnnot, (const std::shared_ptr<Annot>& annot), (override));

};



class AnnotationPrivateTest : public ::testing::Test {

protected:

    NiceMock<MockPage> mockPage;

    std::shared_ptr<Annot> pdfAnnot = std::make_shared<Annot>();

    AnnotationPrivate annotationPrivate;



    void SetUp() override {

        annotationPrivate.pdfAnnot = pdfAnnot;

        annotationPrivate.pdfPage = &mockPage;

    }

};



TEST_F(AnnotationPrivateTest_1393, RemoveAnnotationFromPage_Success_1393) {

    EXPECT_CALL(mockPage, removeAnnot(pdfAnnot));

    Annotation annotation(&annotationPrivate);

    annotationPrivate.removeAnnotationFromPage(&mockPage, &annotation);

}



TEST_F(AnnotationPrivateTest_1393, RemoveAnnotationFromPage_NullptrPdfAnnot_1393) {

    annotationPrivate.pdfAnnot = nullptr;

    EXPECT_CALL(mockPage, removeAnnot(_)).Times(0);

    Annotation annotation(&annotationPrivate);

    annotationPrivate.removeAnnotationFromPage(&mockPage, &annotation);

}



TEST_F(AnnotationPrivateTest_1393, RemoveAnnotationFromPage_WrongPdfPage_1393) {

    Page otherPage(nullptr, 0, Object(), Ref(), std::make_unique<PageAttrs>());

    EXPECT_CALL(mockPage, removeAnnot(_)).Times(0);

    Annotation annotation(&annotationPrivate);

    annotationPrivate.removeAnnotationFromPage(&otherPage, &annotation);

}



TEST_F(AnnotationPrivateTest_1393, RemoveAnnotationFromPage_DeleteAnnotation_1393) {

    EXPECT_CALL(mockPage, removeAnnot(pdfAnnot));

    Annotation* annotation = new Annotation(&annotationPrivate);

    annotationPrivate.removeAnnotationFromPage(&mockPage, annotation);

    // The annotation should be deleted after removal

}
