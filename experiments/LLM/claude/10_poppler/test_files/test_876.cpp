#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Form.h"

// Test encodeID and decodeID as static methods - these don't require an instance
TEST(FormWidgetStaticTest_876, EncodeDecodeID_Zero_876) {
    unsigned int encoded = FormWidget::encodeID(0, 0);
    unsigned int pageNum = 0, fieldNum = 0;
    FormWidget::decodeID(encoded, &pageNum, &fieldNum);
    EXPECT_EQ(pageNum, 0u);
    EXPECT_EQ(fieldNum, 0u);
}

TEST(FormWidgetStaticTest_876, EncodeDecodeID_NonZero_876) {
    unsigned int encoded = FormWidget::encodeID(5, 10);
    unsigned int pageNum = 0, fieldNum = 0;
    FormWidget::decodeID(encoded, &pageNum, &fieldNum);
    EXPECT_EQ(pageNum, 5u);
    EXPECT_EQ(fieldNum, 10u);
}

TEST(FormWidgetStaticTest_876, EncodeDecodeID_LargeValues_876) {
    unsigned int encoded = FormWidget::encodeID(1000, 2000);
    unsigned int pageNum = 0, fieldNum = 0;
    FormWidget::decodeID(encoded, &pageNum, &fieldNum);
    EXPECT_EQ(pageNum, 1000u);
    EXPECT_EQ(fieldNum, 2000u);
}

TEST(FormWidgetStaticTest_876, EncodeDecodeID_OneZero_876) {
    unsigned int encoded = FormWidget::encodeID(1, 0);
    unsigned int pageNum = 0, fieldNum = 0;
    FormWidget::decodeID(encoded, &pageNum, &fieldNum);
    EXPECT_EQ(pageNum, 1u);
    EXPECT_EQ(fieldNum, 0u);
}

TEST(FormWidgetStaticTest_876, EncodeDecodeID_ZeroOne_876) {
    unsigned int encoded = FormWidget::encodeID(0, 1);
    unsigned int pageNum = 0, fieldNum = 0;
    FormWidget::decodeID(encoded, &pageNum, &fieldNum);
    EXPECT_EQ(pageNum, 0u);
    EXPECT_EQ(fieldNum, 1u);
}

TEST(FormWidgetStaticTest_876, EncodeID_DifferentInputsProduceDifferentOutputs_876) {
    unsigned int encoded1 = FormWidget::encodeID(1, 2);
    unsigned int encoded2 = FormWidget::encodeID(2, 1);
    EXPECT_NE(encoded1, encoded2);
}

TEST(FormWidgetStaticTest_876, EncodeDecodeID_MaxPage_876) {
    // Test with a moderately large page number
    unsigned int encoded = FormWidget::encodeID(65535, 0);
    unsigned int pageNum = 0, fieldNum = 0;
    FormWidget::decodeID(encoded, &pageNum, &fieldNum);
    EXPECT_EQ(pageNum, 65535u);
    EXPECT_EQ(fieldNum, 0u);
}

TEST(FormWidgetStaticTest_876, EncodeDecodeID_MaxField_876) {
    // Test with a moderately large field number
    unsigned int encoded = FormWidget::encodeID(0, 65535);
    unsigned int pageNum = 0, fieldNum = 0;
    FormWidget::decodeID(encoded, &pageNum, &fieldNum);
    EXPECT_EQ(pageNum, 0u);
    EXPECT_EQ(fieldNum, 65535u);
}

TEST(FormWidgetStaticTest_876, EncodeDecodeID_Roundtrip_Multiple_876) {
    for (unsigned int p = 0; p < 100; p++) {
        for (unsigned int f = 0; f < 100; f++) {
            unsigned int encoded = FormWidget::encodeID(p, f);
            unsigned int pageNum = 0, fieldNum = 0;
            FormWidget::decodeID(encoded, &pageNum, &fieldNum);
            EXPECT_EQ(pageNum, p) << "Failed for page=" << p << " field=" << f;
            EXPECT_EQ(fieldNum, f) << "Failed for page=" << p << " field=" << f;
        }
    }
}
