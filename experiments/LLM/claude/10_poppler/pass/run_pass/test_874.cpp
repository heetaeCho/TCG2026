#include <gtest/gtest.h>
#include "Form.h"

// Tests for encodeID and decodeID - these are static methods that don't require
// constructing a FormWidget object with its complex dependencies.

class FormWidgetStaticTest_874 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test encodeID and decodeID round-trip with normal values
TEST_F(FormWidgetStaticTest_874, EncodeDecodeID_NormalValues_874) {
    unsigned int pageNum = 5;
    unsigned int fieldNum = 10;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

// Test encodeID and decodeID with zero values
TEST_F(FormWidgetStaticTest_874, EncodeDecodeID_ZeroValues_874) {
    unsigned int pageNum = 0;
    unsigned int fieldNum = 0;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

// Test encodeID and decodeID with page=0, field=non-zero
TEST_F(FormWidgetStaticTest_874, EncodeDecodeID_ZeroPage_874) {
    unsigned int pageNum = 0;
    unsigned int fieldNum = 42;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

// Test encodeID and decodeID with page=non-zero, field=0
TEST_F(FormWidgetStaticTest_874, EncodeDecodeID_ZeroField_874) {
    unsigned int pageNum = 100;
    unsigned int fieldNum = 0;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

// Test encodeID produces different results for different inputs
TEST_F(FormWidgetStaticTest_874, EncodeID_DifferentInputsDifferentOutputs_874) {
    int encoded1 = FormWidget::encodeID(1, 2);
    int encoded2 = FormWidget::encodeID(2, 1);
    
    EXPECT_NE(encoded1, encoded2);
}

// Test encodeID and decodeID with larger values
TEST_F(FormWidgetStaticTest_874, EncodeDecodeID_LargerValues_874) {
    unsigned int pageNum = 255;
    unsigned int fieldNum = 255;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

// Test encodeID and decodeID round-trip with value 1,1
TEST_F(FormWidgetStaticTest_874, EncodeDecodeID_OneOne_874) {
    unsigned int pageNum = 1;
    unsigned int fieldNum = 1;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

// Test encodeID same page different fields produce different encodings
TEST_F(FormWidgetStaticTest_874, EncodeID_SamePageDifferentFields_874) {
    int encoded1 = FormWidget::encodeID(1, 0);
    int encoded2 = FormWidget::encodeID(1, 1);
    int encoded3 = FormWidget::encodeID(1, 2);
    
    EXPECT_NE(encoded1, encoded2);
    EXPECT_NE(encoded2, encoded3);
    EXPECT_NE(encoded1, encoded3);
}

// Test encodeID different pages same field produce different encodings
TEST_F(FormWidgetStaticTest_874, EncodeID_DifferentPagesSameField_874) {
    int encoded1 = FormWidget::encodeID(0, 5);
    int encoded2 = FormWidget::encodeID(1, 5);
    int encoded3 = FormWidget::encodeID(2, 5);
    
    EXPECT_NE(encoded1, encoded2);
    EXPECT_NE(encoded2, encoded3);
    EXPECT_NE(encoded1, encoded3);
}

// Test with moderately large page and field numbers
TEST_F(FormWidgetStaticTest_874, EncodeDecodeID_ModerateValues_874) {
    unsigned int pageNum = 1000;
    unsigned int fieldNum = 500;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage = 0;
    unsigned int decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

// Test encode/decode consistency across multiple round trips
TEST_F(FormWidgetStaticTest_874, EncodeDecodeID_MultipleRoundTrips_874) {
    for (unsigned int p = 0; p < 20; ++p) {
        for (unsigned int f = 0; f < 20; ++f) {
            int encoded = FormWidget::encodeID(p, f);
            unsigned int dp = 0, df = 0;
            FormWidget::decodeID(encoded, &dp, &df);
            EXPECT_EQ(dp, p) << "Failed for page=" << p << " field=" << f;
            EXPECT_EQ(df, f) << "Failed for page=" << p << " field=" << f;
        }
    }
}
