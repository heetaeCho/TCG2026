#include <gtest/gtest.h>

#include <QPointF>

#include "poppler-annotation-helper.h"



using namespace Poppler;



class XPDFReaderTest_1361 : public ::testing::Test {

protected:

    XPDFReader xpdfReader;

};



TEST_F(XPDFReaderTest_1361, TransformIdentityMatrix_1361) {

    double M[] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    QPointF result;

    xpdfReader.transform(M, 5.0, 10.0, result);

    EXPECT_EQ(result.x(), 5.0);

    EXPECT_EQ(result.y(), 10.0);

}



TEST_F(XPDFReaderTest_1361, TransformTranslationMatrix_1361) {

    double M[] = {1.0, 0.0, 0.0, 1.0, 2.0, 3.0};

    QPointF result;

    xpdfReader.transform(M, 5.0, 10.0, result);

    EXPECT_EQ(result.x(), 7.0);

    EXPECT_EQ(result.y(), 13.0);

}



TEST_F(XPDFReaderTest_1361, TransformScalingMatrix_1361) {

    double M[] = {2.0, 0.0, 0.0, 2.0, 0.0, 0.0};

    QPointF result;

    xpdfReader.transform(M, 5.0, 10.0, result);

    EXPECT_EQ(result.x(), 10.0);

    EXPECT_EQ(result.y(), 20.0);

}



TEST_F(XPDFReaderTest_1361, TransformRotationMatrix90Degrees_1361) {

    double M[] = {0.0, -1.0, 1.0, 0.0, 0.0, 0.0};

    QPointF result;

    xpdfReader.transform(M, 5.0, 10.0, result);

    EXPECT_EQ(result.x(), -10.0);

    EXPECT_EQ(result.y(), 5.0);

}



TEST_F(XPDFReaderTest_1361, TransformBoundaryConditionZero_1361) {

    double M[] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    QPointF result;

    xpdfReader.transform(M, 0.0, 0.0, result);

    EXPECT_EQ(result.x(), 0.0);

    EXPECT_EQ(result.y(), 0.0);

}



TEST_F(XPDFReaderTest_1361, TransformLargeValues_1361) {

    double M[] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    QPointF result;

    xpdfReader.transform(M, 1e9, 1e9, result);

    EXPECT_EQ(result.x(), 1e9);

    EXPECT_EQ(result.y(), 1e9);

}



TEST_F(XPDFReaderTest_1361, TransformNegativeValues_1361) {

    double M[] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    QPointF result;

    xpdfReader.transform(M, -5.0, -10.0, result);

    EXPECT_EQ(result.x(), -5.0);

    EXPECT_EQ(result.y(), -10.0);

}
