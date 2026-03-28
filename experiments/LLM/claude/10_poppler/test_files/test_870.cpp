#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/Form.h"
#include "poppler/PDFDoc.h"
#include "poppler/Object.h"
#include "poppler/GlobalParams.h"
#include <memory>
#include <string>

class FormWidgetTest_870 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Tests for static encodeID and decodeID
TEST_F(FormWidgetTest_870, EncodeID_BasicValues_870) {
    int encoded = FormWidget::encodeID(1, 0);
    EXPECT_NE(encoded, 0);
}

TEST_F(FormWidgetTest_870, DecodeID_RoundTrip_870) {
    unsigned int pageNum = 5;
    unsigned int fieldNum = 10;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetTest_870, EncodeDecodeID_ZeroValues_870) {
    unsigned int pageNum = 0;
    unsigned int fieldNum = 0;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 99;
    unsigned int decodedField = 99;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetTest_870, EncodeDecodeID_PageOne_FieldZero_870) {
    unsigned int pageNum = 1;
    unsigned int fieldNum = 0;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetTest_870, EncodeDecodeID_PageZero_FieldOne_870) {
    unsigned int pageNum = 0;
    unsigned int fieldNum = 1;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetTest_870, EncodeDecodeID_LargerValues_870) {
    unsigned int pageNum = 100;
    unsigned int fieldNum = 200;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetTest_870, EncodeID_DifferentInputsProduceDifferentOutputs_870) {
    int encoded1 = FormWidget::encodeID(1, 2);
    int encoded2 = FormWidget::encodeID(2, 1);
    EXPECT_NE(encoded1, encoded2);
}

TEST_F(FormWidgetTest_870, EncodeID_SameInputsProduceSameOutput_870) {
    int encoded1 = FormWidget::encodeID(3, 7);
    int encoded2 = FormWidget::encodeID(3, 7);
    EXPECT_EQ(encoded1, encoded2);
}

TEST_F(FormWidgetTest_870, EncodeDecodeID_BoundarySmallValues_870) {
    unsigned int pageNum = 1;
    unsigned int fieldNum = 1;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetTest_870, EncodeDecodeID_MediumValues_870) {
    unsigned int pageNum = 255;
    unsigned int fieldNum = 255;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetTest_870, EncodeDecodeID_MaxFieldNum_870) {
    unsigned int pageNum = 0;
    unsigned int fieldNum = 65535;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetTest_870, EncodeDecodeID_MaxPageNum_870) {
    unsigned int pageNum = 65535;
    unsigned int fieldNum = 0;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}
