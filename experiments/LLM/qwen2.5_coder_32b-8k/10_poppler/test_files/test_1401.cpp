#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <QList>

#include "poppler-annotation.cc"

#include "Annot.h"



using namespace Poppler;



class MockAnnotQuadrilaterals : public AnnotQuadrilaterals {

public:

    MOCK_METHOD(int, getQuadrilateralsLength, (), (const));

    MOCK_METHOD(double, getX1, (int), (const));

    MOCK_METHOD(double, getY1, (int), (const));

    MOCK_METHOD(double, getX2, (int), (const));

    MOCK_METHOD(double, getY2, (int), (const));

    MOCK_METHOD(double, getX3, (int), (const));

    MOCK_METHOD(double, getY3, (int), (const));

    MOCK_METHOD(double, getX4, (int), (const));

    MOCK_METHOD(double, getY4, (int), (const));



    MockAnnotQuadrilaterals(int length) : AnnotQuadrilaterals(length) {}

};



class HighlightAnnotationPrivateTest : public ::testing::Test {

protected:

    HighlightAnnotationPrivate *subject;



    void SetUp() override {

        subject = new HighlightAnnotationPrivate();

    }



    void TearDown() override {

        delete subject;

    }

};



TEST_F(HighlightAnnotationPrivateTest_1401, FromQuadrilateralsReturnsEmptyListWhenNullPassed_1401) {

    AnnotQuadrilaterals* nullPtr = nullptr;

    QList<HighlightAnnotation::Quad> result = subject->fromQuadrilaterals(nullPtr);

    EXPECT_TRUE(result.isEmpty());

}



TEST_F(HighlightAnnotationPrivateTest_1401, FromQuadrilateralsReturnsEmptyListWhenZeroLength_1401) {

    MockAnnotQuadrilaterals mockQuads(0);

    EXPECT_CALL(mockQuads, getQuadrilateralsLength()).WillOnce(::testing::Return(0));



    QList<HighlightAnnotation::Quad> result = subject->fromQuadrilaterals(&mockQuads);

    EXPECT_TRUE(result.isEmpty());

}



TEST_F(HighlightAnnotationPrivateTest_1401, FromQuadrilateralsTransformsAndReturnsOneQuad_1401) {

    MockAnnotQuadrilaterals mockQuads(1);

    EXPECT_CALL(mockQuads, getQuadrilateralsLength()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mockQuads, getX1(0)).WillOnce(::testing::Return(1.0));

    EXPECT_CALL(mockQuads, getY1(0)).WillOnce(::testing::Return(2.0));

    EXPECT_CALL(mockQuads, getX2(0)).WillOnce(::testing::Return(3.0));

    EXPECT_CALL(mockQuads, getY2(0)).WillOnce(::testing::Return(4.0));

    EXPECT_CALL(mockQuads, getX3(0)).WillOnce(::testing::Return(5.0));

    EXPECT_CALL(mockQuads, getY3(0)).WillOnce(::testing::Return(6.0));

    EXPECT_CALL(mockQuads, getX4(0)).WillOnce(::testing::Return(7.0));

    EXPECT_CALL(mockQuads, getY4(0)).WillOnce(::testing::Return(8.0));



    QList<HighlightAnnotation::Quad> result = subject->fromQuadrilaterals(&mockQuads);

    EXPECT_EQ(result.size(), 1);

}



TEST_F(HighlightAnnotationPrivateTest_1401, FromQuadrilateralsTransformsAndReturnsMultipleQuads_1401) {

    MockAnnotQuadrilaterals mockQuads(2);

    EXPECT_CALL(mockQuads, getQuadrilateralsLength()).WillOnce(::testing::Return(2));

    

    // Quad 1

    EXPECT_CALL(mockQuads, getX1(0)).WillOnce(::testing::Return(1.0));

    EXPECT_CALL(mockQuads, getY1(0)).WillOnce(::testing::Return(2.0));

    EXPECT_CALL(mockQuads, getX2(0)).WillOnce(::testing::Return(3.0));

    EXPECT_CALL(mockQuads, getY2(0)).WillOnce(::testing::Return(4.0));

    EXPECT_CALL(mockQuads, getX3(0)).WillOnce(::testing::Return(5.0));

    EXPECT_CALL(mockQuads, getY3(0)).WillOnce(::testing::Return(6.0));

    EXPECT_CALL(mockQuads, getX4(0)).WillOnce(::testing::Return(7.0));

    EXPECT_CALL(mockQuads, getY4(0)).WillOnce(::testing::Return(8.0));



    // Quad 2

    EXPECT_CALL(mockQuads, getX1(1)).WillOnce(::testing::Return(9.0));

    EXPECT_CALL(mockQuads, getY1(1)).WillOnce(::testing::Return(10.0));

    EXPECT_CALL(mockQuads, getX2(1)).WillOnce(::testing::Return(11.0));

    EXPECT_CALL(mockQuads, getY2(1)).WillOnce(::testing::Return(12.0));

    EXPECT_CALL(mockQuads, getX3(1)).WillOnce(::testing::Return(13.0));

    EXPECT_CALL(mockQuads, getY3(1)).WillOnce(::testing::Return(14.0));

    EXPECT_CALL(mockQuads, getX4(1)).WillOnce(::testing::Return(15.0));

    EXPECT_CALL(mockQuads, getY4(1)).WillOnce(::testing::Return(16.0));



    QList<HighlightAnnotation::Quad> result = subject->fromQuadrilaterals(&mockQuads);

    EXPECT_EQ(result.size(), 2);

}



TEST_F(HighlightAnnotationPrivateTest_1401, FromQuadrilateralsSetsCapStartAndCapEndToTrue_1401) {

    MockAnnotQuadrilaterals mockQuads(1);

    EXPECT_CALL(mockQuads, getQuadrilateralsLength()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mockQuads, getX1(0)).WillOnce(::testing::Return(1.0));

    EXPECT_CALL(mockQuads, getY1(0)).WillOnce(::testing::Return(2.0));

    EXPECT_CALL(mockQuads, getX2(0)).WillOnce(::testing::Return(3.0));

    EXPECT_CALL(mockQuads, getY2(0)).WillOnce(::testing::Return(4.0));

    EXPECT_CALL(mockQuads, getX3(0)).WillOnce(::testing::Return(5.0));

    EXPECT_CALL(mockQuads, getY3(0)).WillOnce(::testing::Return(6.0));

    EXPECT_CALL(mockQuads, getX4(0)).WillOnce(::testing::Return(7.0));

    EXPECT_CALL(mockQuads, getY4(0)).WillOnce(::testing::Return(8.0));



    QList<HighlightAnnotation::Quad> result = subject->fromQuadrilaterals(&mockQuads);

    EXPECT_EQ(result.size(), 1);

    EXPECT_TRUE(result[0].capStart);

    EXPECT_TRUE(result[0].capEnd);

}



TEST_F(HighlightAnnotationPrivateTest_1401, FromQuadrilateralsSetsFeatherToDefault_1401) {

    MockAnnotQuadrilaterals mockQuads(1);

    EXPECT_CALL(mockQuads, getQuadrilateralsLength()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mockQuads, getX1(0)).WillOnce(::testing::Return(1.0));

    EXPECT_CALL(mockQuads, getY1(0)).WillOnce(::testing::Return(2.0));

    EXPECT_CALL(mockQuads, getX2(0)).WillOnce(::testing::Return(3.0));

    EXPECT_CALL(mockQuads, getY2(0)).WillOnce(::testing::Return(4.0));

    EXPECT_CALL(mockQuads, getX3(0)).WillOnce(::testing::Return(5.0));

    EXPECT_CALL(mockQuads, getY3(0)).WillOnce(::testing::Return(6.0));

    EXPECT_CALL(mockQuads, getX4(0)).WillOnce(::testing::Return(7.0));

    EXPECT_CALL(mockQuads, getY4(0)).WillOnce(::testing::Return(8.0));



    QList<HighlightAnnotation::Quad> result = subject->fromQuadrilaterals(&mockQuads);

    EXPECT_EQ(result.size(), 1);

    EXPECT_DOUBLE_EQ(result[0].feather, 0.1);

}
