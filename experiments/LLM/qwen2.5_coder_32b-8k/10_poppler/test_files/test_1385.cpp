#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation-private.h"

#include "Page.h"



using namespace Poppler;

using ::testing::Return;

using ::testing::_;



class MockPage : public Page {

public:

    MOCK_CONST_METHOD0(getRotate, int());

};



class AnnotationPrivateTest : public ::testing::Test {

protected:

    void SetUp() override {

        mockPage = std::make_unique<MockPage>();

        annotationPrivate = std::make_unique<AnnotationPrivate>();

        annotationPrivate->tieToNativeAnnot(nullptr, mockPage.get(), nullptr);

    }



    std::unique_ptr<MockPage> mockPage;

    std::unique_ptr<AnnotationPrivate> annotationPrivate;

};



TEST_F(AnnotationPrivateTest_1385, FillTransformationMTX_NoRotation_NoNoRotateFlag_1385) {

    double MTX[6] = {0};

    EXPECT_CALL(*mockPage, getRotate()).WillOnce(Return(0));

    annotationPrivate->fillTransformationMTX(MTX);

    // Assuming fillNormalizationMTX sets some values in MTX which we can verify

    EXPECT_NE(MTX[0], 0); // Just an example check, actual values depend on implementation

}



TEST_F(AnnotationPrivateTest_1385, FillTransformationMTX_NoRotation_WithNoRotateFlag_1385) {

    double MTX[6] = {0};

    annotationPrivate->flags |= Annot::flagNoRotate;

    EXPECT_CALL(*mockPage, getRotate()).WillOnce(Return(0));

    annotationPrivate->fillTransformationMTX(MTX);

    // Assuming fillNormalizationMTX sets some values in MTX which we can verify

    EXPECT_NE(MTX[0], 0); // Just an example check, actual values depend on implementation

}



TEST_F(AnnotationPrivateTest_1385, FillTransformationMTX_Rotation_NoNoRotateFlag_1385) {

    double MTX[6] = {0};

    EXPECT_CALL(*mockPage, getRotate()).WillOnce(Return(90));

    annotationPrivate->fillTransformationMTX(MTX);

    // Assuming fillNormalizationMTX sets some values in MTX which we can verify

    EXPECT_NE(MTX[0], 0); // Just an example check, actual values depend on implementation

}



TEST_F(AnnotationPrivateTest_1385, FillTransformationMTX_Rotation_WithNoRotateFlag_1385) {

    double MTX[6] = {0};

    annotationPrivate->flags |= Annot::flagNoRotate;

    EXPECT_CALL(*mockPage, getRotate()).WillOnce(Return(90));

    annotationPrivate->fillTransformationMTX(MTX);

    // Assuming fillNormalizationMTX sets some values in MTX which we can verify

    EXPECT_NE(MTX[0], 0); // Just an example check, actual values depend on implementation

}



TEST_F(AnnotationPrivateTest_1385, FillTransformationMTX_PageNull_1385) {

    double MTX[6] = {0};

    annotationPrivate->tieToNativeAnnot(nullptr, nullptr, nullptr);

    EXPECT_DEATH({ annotationPrivate->fillTransformationMTX(MTX); }, ".*");

}



TEST_F(AnnotationPrivateTest_1385, FillTransformationMTX_AnnotationNull_1385) {

    double MTX[6] = {0};

    annotationPrivate->pdfAnnot.reset();

    EXPECT_DEATH({ annotationPrivate->fillTransformationMTX(MTX); }, ".*");

}
