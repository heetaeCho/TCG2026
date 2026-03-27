#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation.cc"

#include "Page.h"

#include "DocumentData.h"



using namespace Poppler;

using ::testing::_;

using ::testing::NiceMock;



class MockPage : public Page {

public:

    MOCK_METHOD(bool, addAnnot, (const std::shared_ptr<Annot> &annot), (override));

    MOCK_METHOD(PDFDoc*, getDoc, (), (override));

};



class MockDocumentData : public DocumentData {

public:

    MockDocumentData() : DocumentData("", nullptr, nullptr) {}

};



class GeomAnnotationPrivateTest : public ::testing::Test {

protected:

    std::unique_ptr<MockPage> mockPage;

    std::shared_ptr<MockDocumentData> mockDoc;

    std::unique_ptr<GeomAnnotationPrivate> geomAnnotPriv;



    void SetUp() override {

        mockPage = std::make_unique<NiceMock<MockPage>>();

        mockDoc = std::make_shared<MockDocumentData>();

        geomAnnotPriv = std::make_unique<GeomAnnotationPrivate>();

        geomAnnotPriv->boundary = QRectF(10, 20, 30, 40);

        geomAnnotPriv->geomType = GeomAnnotation::InscribedSquare;

    }

};



TEST_F(GeomAnnotationPrivateTest_1400, CreateNativeAnnot_ReturnsValidPointer_1400) {

    EXPECT_CALL(*mockPage, getDoc()).WillOnce(::testing::Return(mockDoc.get()));



    std::shared_ptr<Annot> nativeAnnot = geomAnnotPriv->createNativeAnnot(mockPage.get(), mockDoc.get());

    EXPECT_NE(nativeAnnot, nullptr);

}



TEST_F(GeomAnnotationPrivateTest_1400, CreateNativeAnnot_SetsCorrectTypeForSquare_1400) {

    EXPECT_CALL(*mockPage, getDoc()).WillOnce(::testing::Return(mockDoc.get()));



    std::shared_ptr<Annot> nativeAnnot = geomAnnotPriv->createNativeAnnot(mockPage.get(), mockDoc.get());

    EXPECT_EQ(nativeAnnot->type, Annot::typeSquare);

}



TEST_F(GeomAnnotationPrivateTest_1400, CreateNativeAnnot_SetsCorrectTypeForCircle_1400) {

    geomAnnotPriv->geomType = GeomAnnotation::InscribedCircle;

    EXPECT_CALL(*mockPage, getDoc()).WillOnce(::testing::Return(mockDoc.get()));



    std::shared_ptr<Annot> nativeAnnot = geomAnnotPriv->createNativeAnnot(mockPage.get(), mockDoc.get());

    EXPECT_EQ(nativeAnnot->type, Annot::typeCircle);

}



TEST_F(GeomAnnotationPrivateTest_1400, CreateNativeAnnot_SetsCorrectBoundaryForSquare_1400) {

    EXPECT_CALL(*mockPage, getDoc()).WillOnce(::testing::Return(mockDoc.get()));



    std::shared_ptr<Annot> nativeAnnot = geomAnnotPriv->createNativeAnnot(mockPage.get(), mockDoc.get());

    PDFRectangle rect = geomAnnotPriv->boundaryToPdfRectangle(geomAnnotPriv->boundary, geomAnnotPriv->flags);

    EXPECT_EQ(nativeAnnot->getRect(), rect);

}



TEST_F(GeomAnnotationPrivateTest_1400, CreateNativeAnnot_SetsCorrectBoundaryForCircle_1400) {

    geomAnnotPriv->geomType = GeomAnnotation::InscribedCircle;

    EXPECT_CALL(*mockPage, getDoc()).WillOnce(::testing::Return(mockDoc.get()));



    std::shared_ptr<Annot> nativeAnnot = geomAnnotPriv->createNativeAnnot(mockPage.get(), mockDoc.get());

    PDFRectangle rect = geomAnnotPriv->boundaryToPdfRectangle(geomAnnotPriv->boundary, geomAnnotPriv->flags);

    EXPECT_EQ(nativeAnnot->getRect(), rect);

}
