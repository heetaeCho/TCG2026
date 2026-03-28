#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Form.h"

// Test encodeID and decodeID as static utility functions (no instance needed)
TEST(FormWidgetStaticTest_875, EncodeDecodeID_Normal_875) {
    unsigned int pageNum = 5;
    unsigned int fieldNum = 10;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST(FormWidgetStaticTest_875, EncodeDecodeID_Zero_875) {
    unsigned int pageNum = 0;
    unsigned int fieldNum = 0;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 99;
    unsigned int decodedField = 99;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST(FormWidgetStaticTest_875, EncodeDecodeID_LargeValues_875) {
    unsigned int pageNum = 65535;
    unsigned int fieldNum = 65535;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST(FormWidgetStaticTest_875, EncodeDecodeID_PageOneFieldZero_875) {
    unsigned int pageNum = 1;
    unsigned int fieldNum = 0;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST(FormWidgetStaticTest_875, EncodeDecodeID_PageZeroFieldOne_875) {
    unsigned int pageNum = 0;
    unsigned int fieldNum = 1;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST(FormWidgetStaticTest_875, EncodeID_DifferentInputsProduceDifferentOutputs_875) {
    int encoded1 = FormWidget::encodeID(1, 2);
    int encoded2 = FormWidget::encodeID(2, 1);
    EXPECT_NE(encoded1, encoded2);
}

TEST(FormWidgetStaticTest_875, EncodeDecodeID_Symmetry_875) {
    for (unsigned int p = 0; p < 100; ++p) {
        for (unsigned int f = 0; f < 100; ++f) {
            int encoded = FormWidget::encodeID(p, f);
            unsigned int dp = 0, df = 0;
            FormWidget::decodeID(encoded, &dp, &df);
            EXPECT_EQ(dp, p) << "Failed for page=" << p << " field=" << f;
            EXPECT_EQ(df, f) << "Failed for page=" << p << " field=" << f;
        }
    }
}
