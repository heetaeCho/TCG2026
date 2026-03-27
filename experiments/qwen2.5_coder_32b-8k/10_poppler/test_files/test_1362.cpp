#include <gtest/gtest.h>

#include "poppler-annotation-helper.h"



using namespace Poppler;



class XPDFReaderTest_1362 : public ::testing::Test {

protected:

    XPDFReader reader;

};



TEST_F(XPDFReaderTest_1362, invTransform_NonSingularMatrix_1362) {

    const double M[] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    QPointF p(1.0, 1.0);

    double x, y;

    reader.invTransform(M, p, x, y);

    EXPECT_DOUBLE_EQ(x, 1.0);

    EXPECT_DOUBLE_EQ(y, 1.0);

}



TEST_F(XPDFReaderTest_1362, invTransform_SingularMatrix_1362) {

    const double M[] = {0.0, 1.0, 1.0, 0.0, 0.0, 0.0};

    QPointF p(1.0, 1.0);

    double x, y;

    reader.invTransform(M, p, x, y);

    EXPECT_DOUBLE_EQ(x, 0.0);

    EXPECT_DOUBLE_EQ(y, 0.0);

}



TEST_F(XPDFReaderTest_1362, invTransform_TranslationOnly_1362) {

    const double M[] = {1.0, 0.0, 0.0, 1.0, 1.0, 1.0};

    QPointF p(2.0, 2.0);

    double x, y;

    reader.invTransform(M, p, x, y);

    EXPECT_DOUBLE_EQ(x, 1.0);

    EXPECT_DOUBLE_EQ(y, 1.0);

}



TEST_F(XPDFReaderTest_1362, invTransform_RotationOnly_1362) {

    const double M[] = {0.0, -1.0, 1.0, 0.0, 0.0, 0.0};

    QPointF p(1.0, 0.0);

    double x, y;

    reader.invTransform(M, p, x, y);

    EXPECT_DOUBLE_EQ(x, 0.0);

    EXPECT_DOUBLE_EQ(y, -1.0);

}



TEST_F(XPDFReaderTest_1362, invTransform_ScaleOnly_1362) {

    const double M[] = {2.0, 0.0, 0.0, 2.0, 0.0, 0.0};

    QPointF p(4.0, 4.0);

    double x, y;

    reader.invTransform(M, p, x, y);

    EXPECT_DOUBLE_EQ(x, 2.0);

    EXPECT_DOUBLE_EQ(y, 2.0);

}
