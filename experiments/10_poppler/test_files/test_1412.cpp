#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/qt5/src/poppler-annotation-private.h"

#include "./TestProjects/poppler/Page.h"

#include "./TestProjects/poppler/qt6/src/poppler-private.h"



using namespace Poppler;

using ::testing::_;

using ::testing::NiceMock;



// Mocking Page and DocumentData

class MockPage : public Page {

public:

    MOCK_METHOD(PDFDoc*, getDoc, (), (const));

};



class MockDocumentData : public DocumentData {

public:

    MOCK_METHOD(void, notifyXRefReconstructed, (), ());

};



class CaretAnnotationPrivateTest : public ::testing::Test {

protected:

    void SetUp() override {

        mockPage = new NiceMock<MockPage>();

        mockDocData = new NiceMock<MockDocumentData>();

        caretAnnotPrivate = new CaretAnnotationPrivate();

    }



    void TearDown() override {

        delete caretAnnotPrivate;

        delete mockPage;

        delete mockDocData;

    }



    MockPage* mockPage;

    MockDocumentData* mockDocData;

    CaretAnnotationPrivate* caretAnnotPrivate;

};



TEST_F(CaretAnnotationPrivateTest, CreateNativeAnnot_ReturnsNonNullPointer_1412) {

    EXPECT_CALL(*mockPage, getDoc()).WillOnce(::testing::Return(new PDFDoc()));

    auto result = caretAnnotPrivate->createNativeAnnot(mockPage, mockDocData);

    EXPECT_NE(result, nullptr);

}



TEST_F(CaretAnnotationPrivateTest, CreateNativeAnnot_SetsPdfPage_1412) {

    EXPECT_CALL(*mockPage, getDoc()).WillOnce(::testing::Return(new PDFDoc()));

    caretAnnotPrivate->createNativeAnnot(mockPage, mockDocData);

    EXPECT_EQ(caretAnnotPrivate->pdfPage, mockPage);

}



TEST_F(CaretAnnotationPrivateTest, CreateNativeAnnot_SetsParentDoc_1412) {

    EXPECT_CALL(*mockPage, getDoc()).WillOnce(::testing::Return(new PDFDoc()));

    caretAnnotPrivate->createNativeAnnot(mockPage, mockDocData);

    EXPECT_EQ(caretAnnotPrivate->parentDoc, mockDocData);

}



TEST_F(CaretAnnotationPrivateTest, CreateNativeAnnot_CallsBoundaryToPdfRectangle_1412) {

    EXPECT_CALL(*mockPage, getDoc()).WillOnce(::testing::Return(new PDFDoc()));

    using ::testing::InvokeWithoutArgs;

    EXPECT_CALL(*caretAnnotPrivate, boundaryToPdfRectangle(caretAnnotPrivate->boundary, caretAnnotPrivate->flags))

        .WillOnce(InvokeWithoutArgs([]() { return PDFRectangle(); }));

    caretAnnotPrivate->createNativeAnnot(mockPage, mockDocData);

}



TEST_F(CaretAnnotationPrivateTest, CreateNativeAnnot_CallsFlushBaseAnnotationProperties_1412) {

    EXPECT_CALL(*mockPage, getDoc()).WillOnce(::testing::Return(new PDFDoc()));

    using ::testing::InvokeWithoutArgs;

    EXPECT_CALL(*caretAnnotPrivate, boundaryToPdfRectangle(caretAnnotPrivate->boundary, caretAnnotPrivate->flags))

        .WillOnce(InvokeWithoutArgs([]() { return PDFRectangle(); }));

    EXPECT_CALL(*caretAnnotPrivate, flushBaseAnnotationProperties()).Times(1);

    caretAnnotPrivate->createNativeAnnot(mockPage, mockDocData);

}



TEST_F(CaretAnnotationPrivateTest, CreateNativeAnnot_SetsCaretSymbol_1412) {

    EXPECT_CALL(*mockPage, getDoc()).WillOnce(::testing::Return(new PDFDoc()));

    using ::testing::InvokeWithoutArgs;

    EXPECT_CALL(*caretAnnotPrivate, boundaryToPdfRectangle(caretAnnotPrivate->boundary, caretAnnotPrivate->flags))

        .WillOnce(InvokeWithoutArgs([]() { return PDFRectangle(); }));

    auto result = caretAnnotPrivate->createNativeAnnot(mockPage, mockDocData);

    EXPECT_EQ(result->getCaretSymbol(), caretAnnotPrivate->symbol);

}
