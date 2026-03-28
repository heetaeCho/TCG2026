#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/Form.h"
#include "poppler/PDFDoc.h"
#include "poppler/Object.h"
#include "poppler/Annot.h"
#include "poppler/Link.h"
#include "poppler/GooString.h"

// Test encodeID and decodeID static methods - these are pure utility functions
// that don't require a FormWidget instance

class FormWidgetStaticTest_872 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(FormWidgetStaticTest_872, EncodeDecodeID_ZeroValues_872) {
    unsigned int pageNum = 0;
    unsigned int fieldNum = 0;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_872, EncodeDecodeID_SmallValues_872) {
    unsigned int pageNum = 1;
    unsigned int fieldNum = 1;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_872, EncodeDecodeID_DifferentValues_872) {
    unsigned int pageNum = 5;
    unsigned int fieldNum = 10;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_872, EncodeDecodeID_LargerValues_872) {
    unsigned int pageNum = 100;
    unsigned int fieldNum = 200;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_872, EncodeDecodeID_PageZeroFieldNonZero_872) {
    unsigned int pageNum = 0;
    unsigned int fieldNum = 42;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_872, EncodeDecodeID_PageNonZeroFieldZero_872) {
    unsigned int pageNum = 42;
    unsigned int fieldNum = 0;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_872, EncodeID_DifferentInputsProduceDifferentOutputs_872) {
    int encoded1 = FormWidget::encodeID(1, 2);
    int encoded2 = FormWidget::encodeID(2, 1);
    
    EXPECT_NE(encoded1, encoded2);
}

TEST_F(FormWidgetStaticTest_872, EncodeDecodeID_Symmetric_872) {
    // Test multiple round-trips
    for (unsigned int p = 0; p < 20; ++p) {
        for (unsigned int f = 0; f < 20; ++f) {
            int encoded = FormWidget::encodeID(p, f);
            unsigned int dp, df;
            FormWidget::decodeID(encoded, &dp, &df);
            EXPECT_EQ(dp, p) << "Failed for pageNum=" << p << ", fieldNum=" << f;
            EXPECT_EQ(df, f) << "Failed for pageNum=" << p << ", fieldNum=" << f;
        }
    }
}

TEST_F(FormWidgetStaticTest_872, EncodeDecodeID_BoundaryMaxField_872) {
    // Test with boundary-like values
    unsigned int pageNum = 0xFFFF;
    unsigned int fieldNum = 0;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

TEST_F(FormWidgetStaticTest_872, EncodeDecodeID_BoundaryMaxPage_872) {
    unsigned int pageNum = 0;
    unsigned int fieldNum = 0xFFFF;
    int encoded = FormWidget::encodeID(pageNum, fieldNum);
    
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, pageNum);
    EXPECT_EQ(decodedField, fieldNum);
}

// Tests that require a FormWidget instance - need a valid PDFDoc context
// Since FormWidget requires PDFDoc, Object, Ref, FormField, we test what we can
// through the static interface and getObj accessor

class FormWidgetGetObjTest_872 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Note: Testing getObj() requires a constructed FormWidget, which in turn
// requires a PDFDoc, FormField, etc. Without being able to construct one
// easily, we focus on the static utility methods that are independently testable.

// Test that encodeID produces consistent results for same inputs
TEST_F(FormWidgetStaticTest_872, EncodeID_Deterministic_872) {
    int encoded1 = FormWidget::encodeID(3, 7);
    int encoded2 = FormWidget::encodeID(3, 7);
    
    EXPECT_EQ(encoded1, encoded2);
}

// Test encode/decode with equal page and field numbers
TEST_F(FormWidgetStaticTest_872, EncodeDecodeID_EqualPageAndField_872) {
    unsigned int val = 50;
    int encoded = FormWidget::encodeID(val, val);
    
    unsigned int decodedPage, decodedField;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    
    EXPECT_EQ(decodedPage, val);
    EXPECT_EQ(decodedField, val);
}
