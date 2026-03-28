#include <gtest/gtest.h>
#include "Form.h"

// Test the static encodeID/decodeID methods which don't require object construction
class FormWidgetStaticTest_868 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(FormWidgetStaticTest_868, EncodeDecodeID_BasicValues_868) {
    unsigned int pageNum = 5;
    unsigned int fieldNum = 10;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_868, EncodeDecodeID_ZeroValues_868) {
    unsigned int pageNum = 0;
    unsigned int fieldNum = 0;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_868, EncodeDecodeID_PageZeroFieldNonZero_868) {
    unsigned int pageNum = 0;
    unsigned int fieldNum = 42;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_868, EncodeDecodeID_PageNonZeroFieldZero_868) {
    unsigned int pageNum = 100;
    unsigned int fieldNum = 0;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_868, EncodeDecodeID_LargePageNum_868) {
    unsigned int pageNum = 1000;
    unsigned int fieldNum = 1;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_868, EncodeDecodeID_LargeFieldNum_868) {
    unsigned int pageNum = 1;
    unsigned int fieldNum = 1000;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_868, EncodeDecodeID_BothLargeValues_868) {
    unsigned int pageNum = 500;
    unsigned int fieldNum = 500;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_868, EncodeID_DifferentInputsProduceDifferentOutputs_868) {
    int encoded1 = FormWidget::encodeID(1, 2);
    int encoded2 = FormWidget::encodeID(2, 1);
    
    EXPECT_NE(encoded1, encoded2);
}

TEST_F(FormWidgetStaticTest_868, EncodeID_SameInputsProduceSameOutput_868) {
    int encoded1 = FormWidget::encodeID(3, 7);
    int encoded2 = FormWidget::encodeID(3, 7);
    
    EXPECT_EQ(encoded1, encoded2);
}

TEST_F(FormWidgetStaticTest_868, EncodeDecodeID_OneAndOne_868) {
    unsigned int pageNum = 1;
    unsigned int fieldNum = 1;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_868, EncodeDecodeID_MaxReasonableValues_868) {
    // Test with values that would be typical maximums for page/field numbers
    unsigned int pageNum = 65535;
    unsigned int fieldNum = 65535;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_868, EncodeDecodeID_MultipleRoundTrips_868) {
    // Verify consistency across multiple encode/decode cycles
    for (unsigned int p = 0; p < 50; p++) {
        for (unsigned int f = 0; f < 50; f++) {
            int encoded = FormWidget::encodeID(p, f);
            unsigned int decodedPage, decodedField;
            FormWidget::decodeID(encoded, &decodedPage, &decodedField);
            EXPECT_EQ(decodedPage, p) << "Failed for page=" << p << " field=" << f;
            EXPECT_EQ(decodedField, f) << "Failed for page=" << p << " field=" << f;
        }
    }
}
