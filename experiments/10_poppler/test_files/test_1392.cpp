#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation-private.h"

#include "Page.h"

#include "DocumentData.h"



using namespace Poppler;

using namespace ::testing;



class AnnotationPrivateTest : public Test {

protected:

    MockAnnotation mockAnnotation;

    NiceMock<MockPage> mockPage;

    DocumentData mockDoc;

};



TEST_F(AnnotationPrivateTest, AddAnnotationToPage_Success_1392) {

    EXPECT_CALL(mockPage, addAnnot(_)).WillOnce(Return(true));



    AnnotationPrivate annPrivate;

    annPrivate.pdfAnnot = nullptr;



    annPrivate.addAnnotationToPage(&mockPage, &mockDoc, &mockAnnotation);



    EXPECT_NE(annPrivate.pdfAnnot.get(), nullptr);

}



TEST_F(AnnotationPrivateTest, AddAnnotationToPage_AlreadyTied_1392) {

    AnnotationPrivate annPrivate;

    annPrivate.pdfAnnot = std::make_shared<Annot>();



    EXPECT_CALL(mockPage, addAnnot(_)).Times(0);



    annPrivate.addAnnotationToPage(&mockPage, &mockDoc, &mockAnnotation);

}



TEST_F(AnnotationPrivateTest, AddAnnotationToPage_CreateNativeAnnotFailure_1392) {

    AnnotationPrivate annPrivate;

    annPrivate.pdfAnnot = nullptr;



    EXPECT_CALL(mockPage, addAnnot(_)).Times(0);



    // Assuming createNativeAnnot can return a null pointer

    EXPECT_CALL(mockAnnotation, d_ptr)

        .WillOnce(Return(&annPrivate))

        .WillOnce(Invoke([&]() {

            annPrivate.pdfAnnot.reset();

            return &annPrivate;

        }));



    annPrivate.addAnnotationToPage(&mockPage, &mockDoc, &mockAnnotation);



    EXPECT_EQ(annPrivate.pdfAnnot.get(), nullptr);

}



TEST_F(AnnotationPrivateTest, AddAnnotationToPage_WithAppearanceStream_1392) {

    AnnotationPrivate annPrivate;

    annPrivate.pdfAnnot = nullptr;



    EXPECT_CALL(mockPage, addAnnot(_)).WillOnce(Return(true));

    EXPECT_CALL(mockAnnotation, d_ptr)

        .WillRepeatedly(Return(&annPrivate));



    Object mockObject;

    EXPECT_CALL(annPrivate.annotationAppearance, isStream())

        .WillOnce(Return(true));

    EXPECT_CALL(annPrivate.annotationAppearance, copy())

        .WillOnce(Return(mockObject));



    annPrivate.addAnnotationToPage(&mockPage, &mockDoc, &mockAnnotation);



    EXPECT_NE(annPrivate.pdfAnnot.get(), nullptr);

}



class MockAnnotation {

public:

    MOCK_CONST_METHOD0(d_ptr, AnnotationPrivate*());

};



TEST_F(AnnotationPrivateTest, AddAnnotationToPage_ErrorHandling_1392) {

    AnnotationPrivate annPrivate;

    annPrivate.pdfAnnot = nullptr;



    EXPECT_CALL(mockPage, addAnnot(_)).WillOnce(Return(false));

    EXPECT_CALL(mockAnnotation, d_ptr())

        .WillRepeatedly(Return(&annPrivate));



    testing::internal::CaptureStderr();

    annPrivate.addAnnotationToPage(&mockPage, &mockDoc, &mockAnnotation);

    std::string output = testing::internal::GetCapturedStderr();



    EXPECT_NE(output.find("Annotation is already tied"), std::string::npos);

}



class MockPage {

public:

    MOCK_METHOD1(addAnnot, bool(const std::shared_ptr<Annot>&));

};



TEST_F(AnnotationPrivateTest, AddAnnotationToPage_PageAddAnnotFailure_1392) {

    AnnotationPrivate annPrivate;

    annPrivate.pdfAnnot = nullptr;



    EXPECT_CALL(mockPage, addAnnot(_)).WillOnce(Return(false));



    annPrivate.addAnnotationToPage(&mockPage, &mockDoc, &mockAnnotation);



    // Verify that pdfAnnot is still null after a failed add

    EXPECT_EQ(annPrivate.pdfAnnot.get(), nullptr);

}
