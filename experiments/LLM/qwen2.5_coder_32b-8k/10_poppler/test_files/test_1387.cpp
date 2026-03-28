#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/qt5/src/poppler-annotation.cc"

#include "TestProjects/poppler/poppler/Page.h"



using namespace Poppler;

using ::testing::Return;



class MockPage : public Page {

public:

    MOCK_METHOD(double, getCropWidth, (), (const));

    MOCK_METHOD(double, getCropHeight, (), (const));

    MOCK_METHOD(int, getRotate, (), (const));

};



TEST_F(PopplerAnnotationTest_1387, NormalOperation_Landscape_NoRotation_1387) {

    MockPage mockPage;

    EXPECT_CALL(mockPage, getCropWidth()).WillOnce(Return(595.0));

    EXPECT_CALL(mockPage, getCropHeight()).WillOnce(Return(842.0));

    EXPECT_CALL(mockPage, getRotate()).WillOnce(Return(0));



    QRectF rect(100, 200, 300, 400);

    PDFRectangle result = boundaryToPdfRectangle(&mockPage, rect, Annotation::NoRotation);



    EXPECT_DOUBLE_EQ(result.x1, 100.0);

    EXPECT_DOUBLE_EQ(result.y1, 442.0); // 842 - 400

    EXPECT_DOUBLE_EQ(result.x2, 400.0);

    EXPECT_DOUBLE_EQ(result.y2, 642.0); // 842 - 200

}



TEST_F(PopplerAnnotationTest_1387, NormalOperation_Portrait_NoRotation_1387) {

    MockPage mockPage;

    EXPECT_CALL(mockPage, getCropWidth()).WillOnce(Return(595.0));

    EXPECT_CALL(mockPage, getCropHeight()).WillOnce(Return(842.0));

    EXPECT_CALL(mockPage, getRotate()).WillOnce(Return(0));



    QRectF rect(100, 200, 300, 400);

    PDFRectangle result = boundaryToPdfRectangle(&mockPage, rect, Annotation::NoRotation);



    EXPECT_DOUBLE_EQ(result.x1, 100.0);

    EXPECT_DOUBLE_EQ(result.y1, 442.0); // 842 - 400

    EXPECT_DOUBLE_EQ(result.x2, 400.0);

    EXPECT_DOUBLE_EQ(result.y2, 642.0); // 842 - 200

}



TEST_F(PopplerAnnotationTest_1387, NormalOperation_Landscape_Rotate90_1387) {

    MockPage mockPage;

    EXPECT_CALL(mockPage, getCropWidth()).WillOnce(Return(595.0));

    EXPECT_CALL(mockPage, getCropHeight()).WillOnce(Return(842.0));

    EXPECT_CALL(mockPage, getRotate()).WillOnce(Return(90));



    QRectF rect(100, 200, 300, 400);

    PDFRectangle result = boundaryToPdfRectangle(&mockPage, rect, Annotation::FixedRotation);



    EXPECT_DOUBLE_EQ(result.x1, 100.0);

    EXPECT_DOUBLE_EQ(result.y1, -300); // 442 - (300 * aspect ratio)

    EXPECT_DOUBLE_EQ(result.x2, 742.0); // 100 + (400 * aspect ratio)

    EXPECT_DOUBLE_EQ(result.y2, 442.0);

}



TEST_F(PopplerAnnotationTest_1387, NormalOperation_Portrait_Rotate90_1387) {

    MockPage mockPage;

    EXPECT_CALL(mockPage, getCropWidth()).WillOnce(Return(595.0));

    EXPECT_CALL(mockPage, getCropHeight()).WillOnce(Return(842.0));

    EXPECT_CALL(mockPage, getRotate()).WillOnce(Return(90));



    QRectF rect(100, 200, 300, 400);

    PDFRectangle result = boundaryToPdfRectangle(&mockPage, rect, Annotation::FixedRotation);



    EXPECT_DOUBLE_EQ(result.x1, 100.0);

    EXPECT_DOUBLE_EQ(result.y1, -300); // 442 - (300 * aspect ratio)

    EXPECT_DOUBLE_EQ(result.x2, 742.0); // 100 + (400 * aspect ratio)

    EXPECT_DOUBLE_EQ(result.y2, 442.0);

}



TEST_F(PopplerAnnotationTest_1387, BoundaryCondition_ZeroCropWidth_1387) {

    MockPage mockPage;

    EXPECT_CALL(mockPage, getCropWidth()).WillOnce(Return(0.0));

    EXPECT_CALL(mockPage, getCropHeight()).WillOnce(Return(842.0));

    EXPECT_CALL(mockPage, getRotate()).WillOnce(Return(0));



    QRectF rect(100, 200, 300, 400);

    PDFRectangle result = boundaryToPdfRectangle(&mockPage, rect, Annotation::NoRotation);



    EXPECT_TRUE(result.x1 == 0 && result.y1 == 0 && result.x2 == 0 && result.y2 == 0);

}



TEST_F(PopplerAnnotationTest_1387, BoundaryCondition_ZeroCropHeight_1387) {

    MockPage mockPage;

    EXPECT_CALL(mockPage, getCropWidth()).WillOnce(Return(595.0));

    EXPECT_CALL(mockPage, getCropHeight()).WillOnce(Return(0.0));

    EXPECT_CALL(mockPage, getRotate()).WillOnce(Return(0));



    QRectF rect(100, 200, 300, 400);

    PDFRectangle result = boundaryToPdfRectangle(&mockPage, rect, Annotation::NoRotation);



    EXPECT_TRUE(result.x1 == 0 && result.y1 == 0 && result.x2 == 0 && result.y2 == 0);

}



TEST_F(PopplerAnnotationTest_1387, BoundaryCondition_NegativeCoordinates_1387) {

    MockPage mockPage;

    EXPECT_CALL(mockPage, getCropWidth()).WillOnce(Return(595.0));

    EXPECT_CALL(mockPage, getCropHeight()).WillOnce(Return(842.0));

    EXPECT_CALL(mockPage, getRotate()).WillOnce(Return(0));



    QRectF rect(-100, -200, 300, 400);

    PDFRectangle result = boundaryToPdfRectangle(&mockPage, rect, Annotation::NoRotation);



    EXPECT_DOUBLE_EQ(result.x1, -100.0);

    EXPECT_DOUBLE_EQ(result.y1, 642.0); // 842 - (-200)

    EXPECT_DOUBLE_EQ(result.x2, 200.0); // -100 + 300

    EXPECT_DOUBLE_EQ(result.y2, 842.0); // 842 - (-200) + 400

}
