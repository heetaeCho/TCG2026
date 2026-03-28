#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/qt5/src/poppler-annotation-private.h"

#include "./TestProjects/poppler/qt6/src/poppler-private.h"

#include "./TestProjects/poppler/Page.h"



using namespace Poppler;

using ::testing::_;

using ::testing::Return;

using ::testing::NiceMock;



class MockPage : public Page {

public:

    MOCK_METHOD(PDFDoc*, getDoc, (), (const override));

    MOCK_METHOD(bool, addAnnot, (const std::shared_ptr<Annot>&), (override));

};



class MockDocumentData : public DocumentData {

public:

    MockDocumentData() : DocumentData("dummyPath", {}, {}) {}

    MOCK_METHOD(PDFDoc*, getDoc, (), (const override));

};



class TextAnnotationPrivateTest : public ::testing::Test {

protected:

    void SetUp() override {

        mockPage = std::make_unique<NiceMock<MockPage>>();

        mockDocumentData = std::make_unique<MockDocumentData>();

        textAnnotationPrivate = std::make_unique<TextAnnotationPrivate>();

        textAnnotationPrivate->pdfPage = mockPage.get();

        textAnnotationPrivate->parentDoc = mockDocumentData.get();

    }



    void TearDown() override {

        textAnnotationPrivate.reset();

        mockDocumentData.reset();

        mockPage.reset();

    }



    std::unique_ptr<NiceMock<MockPage>> mockPage;

    std::unique_ptr<MockDocumentData> mockDocumentData;

    std::unique_ptr<TextAnnotationPrivate> textAnnotationPrivate;

};



TEST_F(TextAnnotationPrivateTest_1396, CreateNativeAnnot_ReturnsValidAnnot_1396) {

    auto annot = textAnnotationPrivate->createNativeAnnot(mockPage.get(), mockDocumentData.get());

    EXPECT_TRUE(annot != nullptr);

}



TEST_F(TextAnnotationPrivateTest_1396, CreateNativeAnnot_SetsCorrectBoundary_1396) {

    PDFRectangle expectedRect;

    // Assuming boundaryToPdfRectangle sets some specific values

    textAnnotationPrivate->boundary = QRectF(0, 0, 100, 100);

    auto annot = textAnnotationPrivate->createNativeAnnot(mockPage.get(), mockDocumentData.get());

    EXPECT_EQ(expectedRect, *static_cast<AnnotText*>(annot.get())->getBoundingRect());

}



TEST_F(TextAnnotationPrivateTest_1396, CreateNativeAnnot_LinksTypeCreatesLinkedAnnot_1396) {

    textAnnotationPrivate->textType = TextAnnotation::Linked;

    auto annot = textAnnotationPrivate->createNativeAnnot(mockPage.get(), mockDocumentData.get());

    EXPECT_NE(nullptr, std::dynamic_pointer_cast<AnnotText>(annot));

}



TEST_F(TextAnnotationPrivateTest_1396, CreateNativeAnnot_FreeTextTypeCreatesFreeTextAnnot_1396) {

    textAnnotationPrivate->textType = TextAnnotation::FreeText;

    auto annot = textAnnotationPrivate->createNativeAnnot(mockPage.get(), mockDocumentData.get());

    EXPECT_NE(nullptr, std::dynamic_pointer_cast<AnnotFreeText>(annot));

}



TEST_F(TextAnnotationPrivateTest_1396, CreateNativeAnnot_NegativeFontSizeLogsWarning_1396) {

    textAnnotationPrivate->textFont = -1;

    testing::internal::CaptureStderr();

    auto annot = textAnnotationPrivate->createNativeAnnot(mockPage.get(), mockDocumentData.get());

    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_TRUE(output.find("createNativeAnnot: font pointSize < 0") != std::string::npos);

}



TEST_F(TextAnnotationPrivateTest_1396, CreateNativeAnnot_SetsTextIconAndInplaceAlign_1396) {

    textAnnotationPrivate->textIcon = "Comment";

    textAnnotationPrivate->inplaceAlign = 1;

    auto annot = textAnnotationPrivate->createNativeAnnot(mockPage.get(), mockDocumentData.get());

    EXPECT_EQ(textAnnotationPrivate->textIcon, static_cast<TextAnnotation*>(annot.get())->getTextIcon());

    EXPECT_EQ(textAnnotationPrivate->inplaceAlign, static_cast<TextAnnotation*>(annot.get())->getInplaceAlign());

}



TEST_F(TextAnnotationPrivateTest_1396, CreateNativeAnnot_SetsDefaultAppearance_1396) {

    auto annot = textAnnotationPrivate->createNativeAnnot(mockPage.get(), mockDocumentData.get());

    EXPECT_TRUE(static_cast<Annot*>(annot.get())->getDefaultAppearance().isValid());

}
