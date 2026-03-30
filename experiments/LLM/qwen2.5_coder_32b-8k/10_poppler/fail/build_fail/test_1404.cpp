#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation-private.h"

#include "Page.h"



using namespace Poppler;

using ::testing::_;

using ::testing::Return;

using ::testing::NiceMock;



class MockPage : public Page {

public:

    MOCK_METHOD(PDFDoc*, getDoc, (), (const override));

};



class MockDocumentData : public DocumentData {

public:

    MockDocumentData() : DocumentData("") {}

    MOCK_METHOD(void, notifyXRefReconstructed, (), (override));

};



class StampAnnotationPrivateTest : public ::testing::Test {

protected:

    void SetUp() override {

        mockPage = std::make_unique<NiceMock<MockPage>>();

        mockDoc = std::make_unique<NiceMock<MockDocumentData>>();

        stampAnnotPriv = std::make_unique<StampAnnotationPrivate>();

    }



    void TearDown() override {

        stampAnnotPriv.reset();

        mockDoc.reset();

        mockPage.reset();

    }



    std::unique_ptr<StampAnnotationPrivate> stampAnnotPriv;

    std::unique_ptr<NiceMock<MockPage>> mockPage;

    std::unique_ptr<NiceMock<MockDocumentData>> mockDoc;

};



TEST_F(StampAnnotationPrivateTest, CreateNativeAnnot_ReturnsValidPointer_1404) {

    EXPECT_CALL(*mockPage, getDoc()).WillOnce(Return(mockDoc->getDoc()));

    auto result = stampAnnotPriv->createNativeAnnot(mockPage.get(), mockDoc.get());

    ASSERT_NE(result, nullptr);

}



TEST_F(StampAnnotationPrivateTest, CreateNativeAnnot_SetsPdfPageAndParentDoc_1404) {

    EXPECT_CALL(*mockPage, getDoc()).WillOnce(Return(mockDoc->getDoc()));

    auto result = stampAnnotPriv->createNativeAnnot(mockPage.get(), mockDoc.get());

    EXPECT_EQ(stampAnnotPriv->pdfPage, mockPage.get());

    EXPECT_EQ(stampAnnotPriv->parentDoc, mockDoc.get());

}



TEST_F(StampAnnotationPrivateTest, CreateNativeAnnot_InitializesPdfAnnot_1404) {

    EXPECT_CALL(*mockPage, getDoc()).WillOnce(Return(mockDoc->getDoc()));

    auto result = stampAnnotPriv->createNativeAnnot(mockPage.get(), mockDoc.get());

    ASSERT_NE(stampAnnotPriv->pdfAnnot, nullptr);

}



TEST_F(StampAnnotationPrivateTest, CreateNativeAnnot_SetsStampIconName_1404) {

    EXPECT_CALL(*mockPage, getDoc()).WillOnce(Return(mockDoc->getDoc()));

    stampAnnotPriv->stampIconName = "CustomIcon";

    auto result = stampAnnotPriv->createNativeAnnot(mockPage.get(), mockDoc.get());

    EXPECT_EQ(result->asStamp()->icon().toStdString(), "CustomIcon");

}



TEST_F(StampAnnotationPrivateTest, CreateNativeAnnot_ClearsStampIconName_1404) {

    EXPECT_CALL(*mockPage, getDoc()).WillOnce(Return(mockDoc->getDoc()));

    stampAnnotPriv->stampIconName = "CustomIcon";

    auto result = stampAnnotPriv->createNativeAnnot(mockPage.get(), mockDoc.get());

    EXPECT_TRUE(stampAnnotPriv->stampIconName.isEmpty());

}



TEST_F(StampAnnotationPrivateTest, CreateNativeAnnot_WithEmptyIconName_SetsDefault_1404) {

    EXPECT_CALL(*mockPage, getDoc()).WillOnce(Return(mockDoc->getDoc()));

    stampAnnotPriv->stampIconName.clear();

    auto result = stampAnnotPriv->createNativeAnnot(mockPage.get(), mockDoc.get());

    EXPECT_EQ(result->asStamp()->icon().toStdString(), "Draft");

}
