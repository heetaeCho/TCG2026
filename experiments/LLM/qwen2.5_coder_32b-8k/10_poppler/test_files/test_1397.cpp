#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation-private.h"

#include "Catalog.h"

#include "Page.h"

#include "PDFDoc.h"



using namespace Poppler;

using namespace testing;



class TextAnnotationPrivateTest : public Test {

protected:

    void SetUp() override {

        // Mock objects

        pdfAnnot = std::make_shared<AnnotFreeText>();

        pageMock = new Page(nullptr, 0, Object(), Ref(), nullptr);

        catalogMock = new Catalog(nullptr);

        formMock = new Form();

        docMock = new PDFDoc(nullptr, std::nullopt, std::nullopt, nullptr);



        // Setup expectations

        EXPECT_CALL(*catalogMock, getCreateForm()).WillRepeatedly(Return(formMock));

        EXPECT_CALL(*pageMock, getDoc()).WillRepeatedly(Return(docMock));

        EXPECT_CALL(*docMock, getCatalog()).WillRepeatedly(Return(catalogMock));



        // Assign mocks to TextAnnotationPrivate instance

        textAnnotation = std::make_unique<TextAnnotationPrivate>();

        textAnnotation->pdfAnnot = pdfAnnot;

        textAnnotation->pdfPage = pageMock;

    }



    void TearDown() override {

        delete formMock;

        delete catalogMock;

        delete pageMock;

    }



    std::unique_ptr<TextAnnotationPrivate> textAnnotation;

    Mock<Form> *formMock;

    Mock<Catalog> *catalogMock;

    Mock<Page> *pageMock;

    Mock<PDFDoc> *docMock;

    std::shared_ptr<AnnotFreeText> pdfAnnot;

};



TEST_F(TextAnnotationPrivateTest, SetDefaultAppearanceToNative_NoFont) {

    // Arrange

    textAnnotation->textFont = nullptr;



    // Act

    textAnnotation->setDefaultAppearanceToNative();



    // Assert

    EXPECT_EQ(textAnnotation->pdfAnnot->getDefaultAppearance(), "Invalid font");

}



TEST_F(TextAnnotationPrivateTest, SetDefaultAppearanceToNative_WithFont) {

    // Arrange

    textAnnotation->textFont = 12; // Assuming 12 is a valid font ID for testing

    textAnnotation->textColor = QColor(Qt::red);



    // Act

    textAnnotation->setDefaultAppearanceToNative();



    // Assert

    EXPECT_EQ(textAnnotation->pdfAnnot->getDefaultAppearance(), "BT /F12 12 Tf 1 0 0 rg ET");

}



TEST_F(TextAnnotationPrivateTest, SetDefaultAppearanceToNative_InvalidFont) {

    // Arrange

    textAnnotation->textFont = -1; // Assuming -1 is an invalid font ID for testing

    textAnnotation->textColor = QColor(Qt::blue);



    // Act

    textAnnotation->setDefaultAppearanceToNative();



    // Assert

    EXPECT_EQ(textAnnotation->pdfAnnot->getDefaultAppearance(), "Invalid font");

}



TEST_F(TextAnnotationPrivateTest, SetDefaultAppearanceToNative_NullTextColor) {

    // Arrange

    textAnnotation->textFont = 12;

    textAnnotation->textColor = QColor();



    // Act

    textAnnotation->setDefaultAppearanceToNative();



    // Assert

    EXPECT_EQ(textAnnotation->pdfAnnot->getDefaultAppearance(), "BT /F12 12 Tf ET");

}



TEST_F(TextAnnotationPrivateTest, SetDefaultAppearanceToNative_ValidFontAndColor) {

    // Arrange

    textAnnotation->textFont = 14;

    textAnnotation->textColor = QColor(Qt::green);



    // Act

    textAnnotation->setDefaultAppearanceToNative();



    // Assert

    EXPECT_EQ(textAnnotation->pdfAnnot->getDefaultAppearance(), "BT /F14 14 Tf 0 1 0 rg ET");

}



TEST_F(TextAnnotationPrivateTest, SetDefaultAppearanceToNative_WithoutFont) {

    // Arrange

    textAnnotation->textFont = nullptr;



    // Act & Assert

    EXPECT_THROW(textAnnotation->setDefaultAppearanceToNative(), std::runtime_error);

}
