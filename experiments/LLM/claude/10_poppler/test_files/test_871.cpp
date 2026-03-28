#include <gtest/gtest.h>
#include "Form.h"

// Test the static encodeID and decodeID methods which don't require object construction
class FormWidgetStaticTest_871 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test encodeID with zero values
TEST_F(FormWidgetStaticTest_871, EncodeID_ZeroValues_871) {
    int encoded = FormWidget::encodeID(0, 0);
    unsigned int pageNum = 0, fieldNum = 0;
    FormWidget::decodeID(encoded, &pageNum, &fieldNum);
    EXPECT_EQ(pageNum, 0u);
    EXPECT_EQ(fieldNum, 0u);
}

// Test encodeID and decodeID roundtrip with typical values
TEST_F(FormWidgetStaticTest_871, EncodeDecodeID_RoundTrip_871) {
    unsigned int originalPage = 5;
    unsigned int originalField = 10;
    int encoded = FormWidget::encodeID(originalPage, originalField);
    unsigned int decodedPage = 0, decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    EXPECT_EQ(decodedPage, originalPage);
    EXPECT_EQ(decodedField, originalField);
}

// Test encodeID and decodeID with page=1, field=0
TEST_F(FormWidgetStaticTest_871, EncodeDecodeID_PageOneFieldZero_871) {
    unsigned int originalPage = 1;
    unsigned int originalField = 0;
    int encoded = FormWidget::encodeID(originalPage, originalField);
    unsigned int decodedPage = 0, decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    EXPECT_EQ(decodedPage, originalPage);
    EXPECT_EQ(decodedField, originalField);
}

// Test encodeID and decodeID with page=0, field=1
TEST_F(FormWidgetStaticTest_871, EncodeDecodeID_PageZeroFieldOne_871) {
    unsigned int originalPage = 0;
    unsigned int originalField = 1;
    int encoded = FormWidget::encodeID(originalPage, originalField);
    unsigned int decodedPage = 0, decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    EXPECT_EQ(decodedPage, originalPage);
    EXPECT_EQ(decodedField, originalField);
}

// Test encodeID and decodeID with larger values
TEST_F(FormWidgetStaticTest_871, EncodeDecodeID_LargerValues_871) {
    unsigned int originalPage = 100;
    unsigned int originalField = 200;
    int encoded = FormWidget::encodeID(originalPage, originalField);
    unsigned int decodedPage = 0, decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    EXPECT_EQ(decodedPage, originalPage);
    EXPECT_EQ(decodedField, originalField);
}

// Test that different page/field combinations produce different encoded IDs
TEST_F(FormWidgetStaticTest_871, EncodeID_DifferentInputsDifferentOutputs_871) {
    int encoded1 = FormWidget::encodeID(1, 2);
    int encoded2 = FormWidget::encodeID(2, 1);
    EXPECT_NE(encoded1, encoded2);
}

// Test encodeID and decodeID with equal page and field numbers
TEST_F(FormWidgetStaticTest_871, EncodeDecodeID_EqualPageAndField_871) {
    unsigned int originalPage = 42;
    unsigned int originalField = 42;
    int encoded = FormWidget::encodeID(originalPage, originalField);
    unsigned int decodedPage = 0, decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    EXPECT_EQ(decodedPage, originalPage);
    EXPECT_EQ(decodedField, originalField);
}

// Test encodeID with boundary-like values (e.g., 0xFFFF range)
TEST_F(FormWidgetStaticTest_871, EncodeDecodeID_BoundaryValues_871) {
    unsigned int originalPage = 0xFFFF;
    unsigned int originalField = 0xFFFF;
    int encoded = FormWidget::encodeID(originalPage, originalField);
    unsigned int decodedPage = 0, decodedField = 0;
    FormWidget::decodeID(encoded, &decodedPage, &decodedField);
    EXPECT_EQ(decodedPage, originalPage);
    EXPECT_EQ(decodedField, originalField);
}

// Test multiple roundtrips produce consistent results
TEST_F(FormWidgetStaticTest_871, EncodeDecodeID_ConsistentResults_871) {
    for (unsigned int p = 0; p < 50; p++) {
        for (unsigned int f = 0; f < 50; f++) {
            int encoded = FormWidget::encodeID(p, f);
            unsigned int decodedPage = 0, decodedField = 0;
            FormWidget::decodeID(encoded, &decodedPage, &decodedField);
            EXPECT_EQ(decodedPage, p) << "Failed for page=" << p << " field=" << f;
            EXPECT_EQ(decodedField, f) << "Failed for page=" << p << " field=" << f;
        }
    }
}

// Test that encoding the same values twice gives the same result
TEST_F(FormWidgetStaticTest_871, EncodeID_Deterministic_871) {
    int encoded1 = FormWidget::encodeID(7, 13);
    int encoded2 = FormWidget::encodeID(7, 13);
    EXPECT_EQ(encoded1, encoded2);
}
