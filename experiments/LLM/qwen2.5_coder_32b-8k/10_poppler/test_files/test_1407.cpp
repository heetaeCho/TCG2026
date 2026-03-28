#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation-private.h"

#include "Page.h"

#include "DocumentData.h"



using namespace Poppler;

using ::testing::NiceMock;

using ::testing::_;



class MockPage : public Page {

public:

    MOCK_METHOD(PDFDoc*, getDoc, (), (override));

};



class MockDocumentData : public DocumentData {

public:

    MOCK_METHOD(void, notifyXRefReconstructed, (), (override));

};



class InkAnnotationPrivateTest : public ::testing::Test {

protected:

    void SetUp() override {

        mockPage = std::make_shared<MockPage>();

        mockDocData = std::make_shared<MockDocumentData>();

        inkAnnotPrivate = std::make_unique<InkAnnotationPrivate>();

    }



    std::shared_ptr<MockPage> mockPage;

    std::shared_ptr<MockDocumentData> mockDocData;

    std::unique_ptr<InkAnnotationPrivate> inkAnnotPrivate;

};



TEST_F(InkAnnotationPrivateTest, CreateNativeAnnot_ReturnsValidPointer_1407) {

    EXPECT_CALL(*mockPage, getDoc()).WillOnce(::testing::Return(new PDFDoc()));



    auto result = inkAnnotPrivate->createNativeAnnot(mockPage.get(), mockDocData.get());

    EXPECT_NE(result, nullptr);

}



TEST_F(InkAnnotationPrivateTest, CreateNativeAnnot_SetsPdfPageAndParentDoc_1407) {

    EXPECT_CALL(*mockPage, getDoc()).WillOnce(::testing::Return(new PDFDoc()));



    inkAnnotPrivate->createNativeAnnot(mockPage.get(), mockDocData.get());

    EXPECT_EQ(inkAnnotPrivate->pdfPage, mockPage.get());

    EXPECT_EQ(inkAnnotPrivate->parentDoc, mockDocData.get());

}



TEST_F(InkAnnotationPrivateTest, CreateNativeAnnot_ClearsInkPaths_1407) {

    EXPECT_CALL(*mockPage, getDoc()).WillOnce(::testing::Return(new PDFDoc()));

    inkAnnotPrivate->inkPaths = 5; // Setting some value to test clearing



    inkAnnotPrivate->createNativeAnnot(mockPage.get(), mockDocData.get());

    EXPECT_EQ(inkAnnotPrivate->inkPaths, 0);

}
